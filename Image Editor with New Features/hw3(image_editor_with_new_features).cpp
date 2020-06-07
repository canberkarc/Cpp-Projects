
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// States which are used to track menu screens
const int MAIN_MENU_STATE = 0;
const int OPEN_IMAGE_MENU_STATE = 10;
const int SAVE_IMAGE_DATA_MENU_STATE = 20;
const int SCRIPTS_MENU_STATE = 30;
const int IMAGE_SELECTION_MENU_STATE = 300;
const int CONVERT_GRAYSCALE_MENU_STATE = 3000;

/*****************************************************************************/

// Image Class
class Image
{
public:
    // Constructor
    Image();
    // Copy Constructor
    Image(const Image& image);
    // Destructor
    ~Image();
    
    // operator+ overload
    Image operator+(const Image& image);
    
    // Get the width of the image
    int getWidth();
    // Set the width of the image
    void setWidth(int width);
    
    // Get the height of the image
    int getHeight();
    // Set the height of the image
    void setHeight(int height);
    
    // Get the max value of the image
    int getMaxVal();
    // Set the max value of the image
    void setMaxVal(int maxval);
    
    // Get the data of the image
    int ***getData();
    // Set the data of the image
    void setData(int ***data);
    
    // Get the format of the image
    string& getFormat();
    // Set the format of the image
    void setFormat(string& format);

    // Free the memory allocated
    void free();
    
    // Allocate memory for data
    void alloc();
    
private:
    // Width of the image
    int m_width;
    
    // Heigh of the image
    int m_height;
    
    // Max value of image pixel data
    int m_maxval;
    
    // Holds width x height x 3 image data
    int ***m_data;
    
    // PPM fromat: P3
    string m_format;
 

};

// Constructor
Image::Image()
{
    this->m_width = 0;
    this->m_height = 0;
    this->m_maxval = 0;
    this->m_data = NULL;
    this->m_format = "";
}

// Copy Constructor
Image::Image(const Image& image)
{
    this->free();
    
    this->m_width = image.m_width;
    this->m_height = image.m_height;
    this->m_maxval = image.m_maxval;
    this->m_format = image.m_format;
    
    this->alloc();
    
    // Read image data to the 3D array from file
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            for (int k = 0; k < 3; k++) {
                m_data[i][j][k] = image.m_data[i][j][k];
            }
        }
    }
}

// Destructor
Image::~Image()
{
    this->free();
    
    this->m_width = 0;
    this->m_height = 0;
    this->m_maxval = 0;
    this->m_data = NULL;
    this->m_format = "";
}

// operator+ overload
Image Image::operator+(const Image& image)
{
    Image newImage;
    
    newImage.m_width = this->m_width;
    newImage.m_height = this->m_height;
    newImage.m_maxval = this->m_maxval;
    newImage.m_format = this->m_format;
    
    newImage.alloc();
    
    // Read image data to the 3D array from file
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            for (int k = 0; k < 3; k++) {
                int value = image.m_data[i][j][k] + m_data[i][j][k];
                
                if (value > 255)
                    newImage.m_data[i][j][k] = 255;
                else
                    newImage.m_data[i][j][k] = value;
            }
        }
    }
    
    return newImage;
}

// Get the width of the image
int Image::getWidth()
{
    return this->m_width;
}

// Set the width of the image
void Image::setWidth(int width)
{
    this->m_width = width;
}

// Get the height of the image
int Image::getHeight()
{
    return this->m_height;
}

// Set the height of the image
void Image::setHeight(int height)
{
    this->m_height = height;
}

// Get the max value of the image
int Image::getMaxVal()
{
    return this->m_maxval;
}

// Set the max value of the image
void Image::setMaxVal(int maxval)
{
    this->m_maxval = maxval;
}

// Get the data of the image
int ***Image::getData()
{
    return this->m_data;
}

// Set the data of the image
void Image::setData(int ***data)
{
    this->m_data = data;
}    

// Get the format of the image
string& Image::getFormat()
{
    return this->m_format;
}

// Set the format of the image
void Image::setFormat(string& format)
{
    this->m_format = format;
}

// Free the memory allocated
void Image::free()
{
    if (m_data != NULL) {
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                delete[] m_data[i][j];
            }
            
            delete[] m_data[i];
        }
        
        delete[] m_data;
        m_data = NULL;
    }
}

// Allocate memory for data
void Image::alloc()
{
    m_data = new int**[m_height];
        
    for (int i = 0; i < m_height; i++) {
        m_data[i] = new int*[m_width];
        
        for (int j = 0; j < m_width; j++) {
            m_data[i][j] = new int[3];
        }
    }
}
    
/*****************************************************************************/

// ImageEditor Class
class ImageEditor {
public:
    // Constructor
    ImageEditor();
    
    // Deconstructor
    ~ImageEditor();
    
    // Run method which loops until user exits
    void run();
    
private:
    // Read from image file
    void readImage(const char *filename, int image_index);
    
    // Write to image file
    void writeImage(const string filename, int image_index);
    
    // Write to image file
    void writeImage(const string filename, Image& image);
    
    // Convert image to grayscale
    void convertToGrayscaleImage(int image_index, float cr, float cg, float cb);
    
    // Print main menu
    void printMainMenu();

    // Print open a image menu
    void printOpenImageMenu();

    // Print save image data menu
    void printSaveImageDataMenu();

    // Print scripts menu
    void printScriptsMenu();
    
    // Print image selection menu
    void printImageSelectionMenu();

    // Print convert to grayscale menu
    void printConvertGrayscaleMenu();
    
    // If cin failed clear error
    void cinFailed(int& selection);
    
private:
    // First image
    Image m_image1;
    
    // Second image
    Image m_image2;
};

// Constructor
ImageEditor::ImageEditor()
{
}

// Destructor
ImageEditor::~ImageEditor()
{
}

// Run method which loops until user exits
void ImageEditor::run()
{
    // Holds input filename
    char inputFilename[256] = { 0 };
    
    // Holds output filename
    char outputFilename[256] = { 0 };
    
    // Holds menu state
    int state = 0;

    //File name to be saved
    string saveFileName;
    
    // cr, cg, cb coefficients
    float cr = 0.0;
    float cg = 0.0;
    float cb = 0.0;
    
    // Selected image
    int selected_image = 0;
    
    while(true) {
        // Hold which option selected
        int selection = -1;
        
        switch (state) {
            case MAIN_MENU_STATE:
                // Print main menu
                printMainMenu();
                
                // Get selected option from user
                cin >> selection;
                
                this->cinFailed(selection);
                
                switch (selection) {
                    case 0:
                        return;
                    case 1:
                        state = OPEN_IMAGE_MENU_STATE;
                        break;
                    case 2:
                        state = SAVE_IMAGE_DATA_MENU_STATE;
                        break;
                    case 3:
                        state = SCRIPTS_MENU_STATE;
                        break;
                    default:
                        exit(1);
                        break;
                }
                break;
            case OPEN_IMAGE_MENU_STATE:
                // Print open image menu
                printOpenImageMenu();
                
                // Get selected option from user
                cin >> selection;
                
                this->cinFailed(selection);
                
                switch (selection) {
                    case 0:
                        state = MAIN_MENU_STATE;
                        break;
                    case 1:
                        state = OPEN_IMAGE_MENU_STATE;
                        
                        // Get input file name from the user
                        cin >> inputFilename;
                        
                        // Read first image from the given file
                        this->readImage(inputFilename, 1);
                        
                        break;
                    case 2:
                        state = OPEN_IMAGE_MENU_STATE;
                        
                        // Get input file name from the user
                        cin >> inputFilename;
                        
                        // Read second image from the given file
                        this->readImage(inputFilename, 2);
                        
                        break;
                    default:
                        exit(1);
                        break;
                }
                break;
            case SAVE_IMAGE_DATA_MENU_STATE:
                // Print save image data menu
                printSaveImageDataMenu();
                
                // Get selected option from user
                cin >> selection;
                
                this->cinFailed(selection);
                
                switch (selection) {
                    case 0:
                        state = MAIN_MENU_STATE;
                        break;
                    case 1:
                    case 2:
                        // Get output file name from the user
                        cin >> outputFilename;
                        
                        // Write image to the given file
                        this->writeImage(outputFilename, selection);
                        
                        state = SAVE_IMAGE_DATA_MENU_STATE;
                        break;
                    default:
                        state = SAVE_IMAGE_DATA_MENU_STATE;
                        break;
                }
                break;
            case SCRIPTS_MENU_STATE:
                // Print scripts menu
                printScriptsMenu();
                
                // Get selected option from user
                cin >> selection;
                
                this->cinFailed(selection);
                
                switch (selection) {
                    case 0:
                        state = MAIN_MENU_STATE;
                        break;
                    case 1:
                        state = IMAGE_SELECTION_MENU_STATE;
                        break;
                    case 2:
                        {
                            Image image = m_image1 + m_image2;
                            cout << "Please enter file name to be saved:";
                            cin >> saveFileName;
                            this->writeImage(saveFileName, image);
                            
                            state = SCRIPTS_MENU_STATE;
                        }
                        break;
                    default:
                        exit(1);
                        break;
                }
                break;
            case IMAGE_SELECTION_MENU_STATE:
                // Print image selection menu
                printImageSelectionMenu();
                
                // Get selected option from user
                cin >> selection;
                
                this->cinFailed(selection);
                
                switch (selection) {
                    case 0:
                        state = SCRIPTS_MENU_STATE;
                        break;
                    case 1:
                    case 2:
                        selected_image = selection;
                        state = CONVERT_GRAYSCALE_MENU_STATE;
                        break;
                    default:
                        exit(1);
                        break;
                }
                break;
            case CONVERT_GRAYSCALE_MENU_STATE:
                // Print convert to grayscale menu
                printConvertGrayscaleMenu();
                
                // Get selected option from user
                cin >> selection;
                
                this->cinFailed(selection);
                
                switch (selection) {
                    case 0:
                        state = SCRIPTS_MENU_STATE;
                        break;
                    case 1:
                        state = CONVERT_GRAYSCALE_MENU_STATE;
                        
                        // Get cr, cg and cb values from the user
                        cin >> cr >> cg >> cb;
                        
                        // Check if cr value is valid
                        if (cr < 0 && cr >= 1.0)
                            exit(1); 
                        // Check if cg value is valid
                        if (cg < 0 && cg >= 1.0) 
                            exit(1);
                        // Check if cb value is valid
                        if (cb < 0 && cb >= 1.0) 
                            exit(1);
                        
                        
                        this->cinFailed(selection);
                        // Convert image to grayscale
                        this->convertToGrayscaleImage(selected_image, cr, cg, cb);
                        
                        break;
                    default:
                        exit(1);
                        break;
                }
                break;
            default:
                break;
        }
    }
}

// Read from image file
void ImageEditor::readImage(const char *filename, int image_index)
{
    int width = 0;
    int height = 0;
    int maxval = 0;
    int ***data = NULL;
    string format = "";
    
    Image *image;
    
    if (image_index <= 0 || image_index > 2)
        return;
    
    // Open file to read
    ifstream infile(filename);
    
    if (infile.is_open()) {
        // Read format, width, height and maxval from file
        infile >> format;
        if(format != "P3")
            exit(1);
        infile >> width >> height;
        if(width <= 0 || height <= 0)
            exit(1);
        infile >> maxval;
        if(maxval <= 0)
            exit(1);
        
        // Allocate memory of height x width x 3 3D integer array
        data = new int**[height];
        
        for (int i = 0; i < height; i++) {
            data[i] = new int*[width];
            
            for (int j = 0; j < width; j++) {
                data[i][j] = new int[3];
            }
        }
        
        // Read image data to the 3D array from file
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int k = 0; k < 3; k++) {
                    infile >> data[i][j][k];
                }
            }
        }
    
        switch (image_index) {
            case 1:
                image = &this->m_image1;
                break;
            case 2:
                image = &this->m_image2;
                break;
        }
        
        image->free();
        image->setWidth(width);
        image->setHeight(height);
        image->setMaxVal(maxval);
        image->setData(data);
        image->setFormat(format);
    } else {
        exit(1);
    }
}

// Write to image file
void ImageEditor::writeImage(const string filename, int image_index)
{
    int width = 0;
    int height = 0;
    int maxval = 0;
    int ***data = NULL;
    string format = "";
    
    Image *image;
    
    if (image_index <= 0 || image_index > 2)
        return;
    
    switch (image_index) {
        case 1:
            image = &this->m_image1;
            break;
        case 2:
            image = &this->m_image2;
            break;
    }
    
    width = image->getWidth();
    height = image->getHeight();
    maxval = image->getMaxVal();
    data = image->getData();
    format = image->getFormat();
    
    if (data == NULL) {
        return;
    }
 
    // Open file to write
    ofstream outfile(filename);
    
    if (outfile.is_open()) {
        // Write format, width, height and maxval to file
        outfile << format << endl;
        outfile << width << " " << height << endl;
        outfile << maxval << endl;
        
        // Write image data from the 3D array to file
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int k = 0; k < 3; k++) {
                    outfile << data[i][j][k] << " ";
                }
            }
            outfile << endl;
        }
    } else {
        exit(1);
    }
}

// Write to image file
void ImageEditor::writeImage(const string filename, Image& image)
{
    int width = 0;
    int height = 0;
    int maxval = 0;
    int ***data = NULL;
    string format = "";
    
    width = image.getWidth();
    height = image.getHeight();
    maxval = image.getMaxVal();
    data = image.getData();
    format = image.getFormat();
    
    if (data == NULL) {
        return;
    }
 
    // Open file to write
    ofstream outfile(filename);
    
    if (outfile.is_open()) {
        // Write format, width, height and maxval to file
        outfile << format << endl;
        outfile << width << " " << height << endl;
        outfile << maxval << endl;
        
        // Write image data from the 3D array to file
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int k = 0; k < 3; k++) {
                    outfile << data[i][j][k] << " ";
                }
            }
            outfile << endl;
        }
    } else {
        exit(1);
    }
}

// Convert image to grayscale
void ImageEditor::convertToGrayscaleImage(int image_index, float cr, float cg, float cb)
{
    Image *image = NULL;
    
    int width;
    int height;
    int ***data;
    
    switch (image_index) {
        case 1:
            image = &this->m_image1;
            break;
        case 2:
            image = &this->m_image2;
            break;
    }
    
    width = image->getWidth();
    height = image->getHeight();
    data = image->getData();
    
    if (data == NULL) {
        return;
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Calculate new pixel value with coefficients
            int f = (int) (cr * data[i][j][0] + cg * data[i][j][1] + cb * data[i][j][2]);
            
            // If calculated value is bigger than 255 than make it max value 255
            if (f > 255)
                f = 255;
            
            // Assign new image data
            data[i][j][0] = f;
            data[i][j][1] = f;
            data[i][j][2] = f;
        }
    }
}

// Print main menu
void ImageEditor::printMainMenu()
{
    cout << "MAIN MENU" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Open An Image(D)" << endl;
    cout << "2 - Save Image Data(D)" << endl;
    cout << "3 - Tools(D)" << endl;
}

// Print open a image menu
void ImageEditor::printOpenImageMenu()
{
    cout << "OPEN AN IMAGE MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter The Name Of The First Image File" << endl;
    cout << "2 - Enter The Name Of The Second Image File" << endl;
}

// Print save image data menu
void ImageEditor::printSaveImageDataMenu()
{
    cout << "SAVE IMAGE DATA MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter A File Name To Save The First Image" << endl;
    cout << "2 - Enter A File Name To Save The Second Image" << endl;
}

// Print scripts menu
void ImageEditor::printScriptsMenu()
{
    cout << "TOOLS MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Convert To Grayscale(D)" << endl;
    cout << "2 - Add Two Images And Save" << endl;
}

// Print image selection menu
void ImageEditor::printImageSelectionMenu()
{
    cout << "IMAGE SELECTION MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Image 1(D)" << endl;
    cout << "2 - Image 2(D)" << endl;
}

// Print convert to grayscale menu
void ImageEditor::printConvertGrayscaleMenu()
{
    cout << "CONVERT TO GRAYSCALE MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels" << endl;
}

// If cin failed clear error
void ImageEditor::cinFailed(int &selection)
{
    if (cin.fail()) {
        cin.clear();
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        selection = -1;
    }
}
    
// Main
int main()
{
    ImageEditor imageEditor;
    
    imageEditor.run();
    
    return 0;
}
