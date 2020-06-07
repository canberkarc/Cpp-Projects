#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

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
    void readImage(const char *);
    
    // Write to image file
    void writeImage(const char *);
    
    // Convert image to grayscale
    void convertToGrayscaleImage(float cr, float cg, float cb);
    
    // Free allocated data
    void free();
    
    // Print main menu
    void printMainMenu();

    // Print open a image menu
    void printOpenImageMenu();

    // Print save image data menu
    void printSaveImageDataMenu();

    // Print scripts menu
    void printScriptsMenu();

    // Print convert to grayscale menu
    void printConvertGrayscaleMenu();
    
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
ImageEditor::ImageEditor()
{
    // Initialize local variables
    m_width = 0;
    m_height = 0;
    m_maxval = 0;
    m_data = NULL;
    m_format = "";
}

// Destructor
ImageEditor::~ImageEditor()
{
    // Free allocated memory
    this->free();
}

// Run method which loops until user exits
void ImageEditor::run()
{
	const int MAIN_MENU_STATE = 0;
	const int OPEN_IMAGE_MENU_STATE = 10;
	const int SAVE_IMAGE_DATA_MENU_STATE = 20;
	const int SCRIPTS_MENU_STATE = 30;
	const int CONVERT_GRAYSCALE_MENU_STATE = 300;
    
    //While flag
	int flag=1;

    // Holds input filename
    char inputFilename[256] = { 0 };
    
    // Holds output filename
    char outputFilename[256] = { 0 };
    
    // Holds menu state
    int state = 0;
    
    // cr, cg, cb coefficients
    float cr = 0.0;
    float cg = 0.0;
    float cb = 0.0;
    
    while(flag) {
        // Hold which option selected
        int selection = -1;
        
        switch (state) {
            case MAIN_MENU_STATE:
                // Print main menu
                printMainMenu();
                
                // Get selected option from user
                cin >> selection;
                
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
                        flag = 0;
                        exit(1);
                }
                break;
            case OPEN_IMAGE_MENU_STATE:
                // Print open image menu
                printOpenImageMenu();
                
                // Get selected option from user
                cin >> selection;
                
                switch (selection) {
                    case 0:
                        state = MAIN_MENU_STATE;
                        break;
                    case 1:
                        state = OPEN_IMAGE_MENU_STATE;
                        
                        // Get input file name from the user
                        cin >> inputFilename;
                        
                        // Read image from the given file
                        this->readImage(inputFilename);
                        
                        break;
                    default:
                        flag = 0;
                        exit(1);
                }
                break;
            case SAVE_IMAGE_DATA_MENU_STATE:
                // Print save image data menu
                printSaveImageDataMenu();
                
                // Get selected option from user
                cin >> selection;
                
                switch (selection) {
                    case 0:
                        state = MAIN_MENU_STATE;
                        break;
                    case 1:
                        // Get output file name from the user
                        cin >> outputFilename;
                        
                        // Write image to the given file
                        this->writeImage(outputFilename);
                        
                        state = SAVE_IMAGE_DATA_MENU_STATE;
                        break;
                    default:
                        flag = 0;
                        exit(1);
                }
                break;
            case SCRIPTS_MENU_STATE:
                // Print scripts menu
                printScriptsMenu();
                
                // Get selected option from user
                cin >> selection;
                
                switch (selection) {
                    case 0:
                        state = MAIN_MENU_STATE;
                        break;
                    case 1:
                        state = CONVERT_GRAYSCALE_MENU_STATE;
                        break;
                    default:
                        flag = 0;
                        exit(1);
                }
                break;
            case CONVERT_GRAYSCALE_MENU_STATE:
                // Print convert to grayscale menu
                printConvertGrayscaleMenu();
                
                // Get selected option from user
                cin >> selection;
                
                switch (selection) {
                    case 0:
                        state = SCRIPTS_MENU_STATE;
                        break;
                    case 1:
                        state = CONVERT_GRAYSCALE_MENU_STATE;
                        
                        // Get cr, cg and cb values from the user
                        cin >> cr >> cg >> cb;
                        
                        // Check if cr value is valid
                        if (cr < 0 && cr >= 1.0) {
                            flag = 0;
                            exit(1);
                        }
                        
                        // Check if cg value is valid
                        if (cg < 0 && cg >= 1.0) {
                            flag = 0;
                            exit(1);
                        }
                        
                        // Check if cb value is valid
                        if (cb < 0 && cb >= 1.0) {
                            flag = 0;
                            exit(1);
                        }
                        
                        // Convert image to grayscale
                        this->convertToGrayscaleImage(cr, cg, cb);
                        
                        break;
                    default:
                        flag = 0;
                        exit(1);
                }
                break;
            default:
                break;
        }
    }
}

// Read from image file
void ImageEditor::readImage(const char *filename)
{
    
    // Open file to read
    ifstream infile(filename);
    
    if (infile.is_open()) {
        // Read format, width, height and maxval from file and check for errors
        infile >> m_format;
        if(m_format != "P3")
        	exit(1);

        infile >> m_width >> m_height;
        if(m_width <= 0 || m_height <= 0)
        	exit(1);

        infile >> m_maxval;
        if(m_maxval <= 0)
        	exit(1);

        // Free old image data
        this->free();
        
        // Allocate memory of height x width x 3 3D integer array
        m_data = new int**[m_height];
        
        for (int i = 0; i < m_height; i++) {
            m_data[i] = new int*[m_width];
            
            for (int j = 0; j < m_width; j++) {
                m_data[i][j] = new int[3];
            }
        }

        // Read image data to the 3D array from file
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                for (int k = 0; k < 3; k++) {
                    infile >> m_data[i][j][k];
                }
            }
        }
    } else {
    	exit(1);
    }
}

// Write to image file
void ImageEditor::writeImage(const char *filename)
{
    if (m_data == NULL) {
        return;
    }
 
    // Open file to write
    ofstream outfile(filename);
    
    if (outfile.is_open()) {
        // Write format, width, height and maxval to file
        outfile << m_format << endl;
        outfile << m_width << " " << m_height << endl;
        outfile << m_maxval << endl;
        
        // Write image data from the 3writeImageD array to file
        for (int i = 0; i < m_height; i++) {
            for (int j = 0; j < m_width; j++) {
                for (int k = 0; k < 3; k++) {
                    outfile << m_data[i][j][k] << " ";
                }
            }
            outfile << endl;
        }
    } else {
    	exit(1);
    }
}

// Convert image to grayscale
void ImageEditor::convertToGrayscaleImage(float cr, float cg, float cb)
{
    if (m_data == NULL) {
        return;
    }
    
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            // Calculate new pixel value with coefficients
            int f = (int) (cr * m_data[i][j][0] + cg * m_data[i][j][1] + cb * m_data[i][j][2]);
            
            // If calculated value is bigger than 255 than make it max value 255
            if (f > 255)
                f = 255;
            
            // Assign new image data
            m_data[i][j][0] = f;
            m_data[i][j][1] = f;
            m_data[i][j][2] = f;
        }
    }
}

// Free allocated data
void ImageEditor::free()
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


// Print main menu
void ImageEditor::printMainMenu()
{
    cout << "MAIN MENU" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Open An Image(D)" << endl;
    cout << "2 - Save Image Data(D)" << endl;
    cout << "3 - Scripts(D)" << endl;
}

// Print open a image menu
void ImageEditor::printOpenImageMenu()
{
    cout << "OPEN AN IMAGE MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter The Name Of The Image File" << endl;
}

// Print save image data menu
void ImageEditor::printSaveImageDataMenu()
{
    cout << "SAVE IMAGE DATA MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter A File Name" << endl;
}

// Print scripts menu
void ImageEditor::printScriptsMenu()
{
    cout << "SCRIPTS MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Convert To Grayscale(D)" << endl;
}

// Print convert to grayscale menu
void ImageEditor::printConvertGrayscaleMenu()
{
    cout << "CONVERT TO GRAYSCALE MENU" << endl;
    cout << "0 - UP" << endl;
    cout << "1 - Enter Coefficients For RED GREEN And BLUE Channels" << endl;
}

int main()
{
    ImageEditor imageEditor;
    
    imageEditor.run();
    
    return 0;
}
