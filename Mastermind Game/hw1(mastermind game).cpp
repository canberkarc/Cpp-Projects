#include <climits>
#include <cstring>
#include <iostream>
#include<cstdlib>

using namespace std;

// Control if all digits are unique in the number string
bool is_digit_unique(const char *numstr)
{
    int counts[10] = {0};
    
    const char *p = numstr;
    
    while (*p != '\0') {
        counts[*p - '0']++;
        p++;
    }
    
    for (size_t i = 0; i < sizeof(counts) / sizeof(counts[0]); i++) {
        if (counts[i] > 1) {
            return false;
        }
    }
    
    return true;
}

/* Control if the number given is a valid number
 * a) check if it is a number
 * b) check if there is any other characters at the end of the string
 * c) check if it is a negative number
 * d) check if there is a leading 0 at the beginning of the string
 */
bool is_valid_number(const char *numstr)
{
    long long int val;
    char *endptr;

    val = strtoll(numstr, &endptr, 10);
    
    // check if it is a number
    if ((val == LLONG_MAX || val == LLONG_MIN)) {
        return false;
    }
     
    if (numstr == endptr) {
        return false;
    }
    
    // check if there is any other characters at the end of the string
    if (*endptr != '\0') {
        return false;
    }
    
    // check if it is a negative number
    if (val < 0) {
        return false;
    }
    
    // check if there is a leading 0 at the beginning of the string
    if (numstr[0] == '0') {
        return false;
    }

    // check if any digit is used at most ones
    return is_digit_unique(numstr);
}

// check if it is a negative number
bool is_negative(const char *num){
	long long int val;
    char *endptr;

    val = strtoll(num, &endptr, 10);

    if (val < 0) {
        return false;
    }
    return true;
}

// Convert string to its integer value and also check if it is a valid integer
// return -1 if it is not valid
int convert_digit(const char *str)
{
    long long int val;
    char *endptr;
    
    val = strtoll(str, &endptr, 10);
    
    if ((val == LLONG_MAX || val == LLONG_MIN)) {
        return -1;
    }
    
    if (str == endptr) {
        return -1;
    }
    
    if (*endptr != '\0') {

        return -1;
    }
    
    return val;
}

// Generate a secret number with the length of n
void generate_secret_number(char *numstr, int n)
{
    int counts[10] = {0};
    
    // Get a random number between 1-9, first digit cannot be 0
    int r = (rand() % 9) + 1;
    
    if (counts[r] == 0) {
        counts[r] = 1;
        numstr[0] = r + '0';
    }
    
    for (int i = 1; i < n; i++) {
        while (true) {
            // Get a random number between 0-9
            r = rand() % 10;
        
            // If the digit does not exist before, continue with the next digit
            if (counts[r] == 0) {
                counts[r] = 1;
                numstr[i] = r + '0';
                break;
            }
        }
    }
    //Secret number can be printed with this cout
    // cout << numstr << endl;
    
    return;
}

// Check if the the length of the input entered is equals to the length of the secret number
bool check_input_length(char *numstr, int n)
{
    return strlen(numstr) == (unsigned int) n;
}

// Compare input which is entered with the secret number and find matches.
// exact_match_count : the count of exact matched digits with the right position
// total_match_count : the count of total matched digits
void compare_input(const char *input, const char *numstr, int& exact_match_count, int& total_match_count)
{
    int n = 0;
    
    int counts_input[10] = {0};
    int counts_numstr[10] = {0};
    
    exact_match_count = 0;
    total_match_count = 0;
    
    const char *p = input;
    
    while (*p != '\0') {
        counts_input[*p - '0']++;
        p++;
        n++;
    }
    
    p = numstr;
    
    while (*p != '\0') {
        counts_numstr[*p - '0']++;
        p++;
    }
    
    // Find the count of total matched digits
    for (size_t i = 0; i < sizeof(counts_input) / sizeof(counts_input[0]); i++) {
        if ((counts_input[i] & counts_numstr[i]) == 1) {
            total_match_count++;
        }
    }
    
    // Find the count of exact matched digits
    for (int i = 0; i < n; i++) {
        if (input[i] == numstr[i]) {
            exact_match_count++;
        }
    }
    
    return;
}

int main(int argc, char *argv[])
{
    // Hold input string entered
    char input[128];

    // Maximum length of the secret number
    const int max_number_length = 10;

    // Maximum number of iteration to predict the secret number 
    const int max_iteration = 100;
 
    // The length of the secret number string
    int number_len = 0;
    // Holds secret number string
    char number[16] = {0};
    
    // Seed random generator
    srand(time(NULL));

    // Check the number of command line arguments
    if (argc < 3) {
        cout << "E0" << endl;
        return 0;
    }
    
    if (strcmp(argv[1], "-r") == 0) {
        number_len = convert_digit(argv[2]);
        
        if (number_len <= 0) {
            cout << "E0" << endl;
            return 0;
        }
        
        // Check if number_len is bigger than max number length
        if (number_len >= max_number_length) {
            cout << "E0" << endl;
            return 0;
        }
        
        // Generate a secret number
        generate_secret_number(number, number_len);
    } else if (strcmp(argv[1], "-u") == 0) {
        snprintf(number, sizeof(number), "%s", argv[2]);
        
        // Check if the number given with -u option valid
        if (!is_valid_number(number)) {
            cout << "E0" << endl;
            return 0;
        }
        
        number_len = strlen(number);
    } else {
        cout << "E0" << endl;
        return 0;
    }
    
    int turn = 0;
    
    for (int i = 0; i < max_iteration; i++) {
        int exact_match_count = 0;
        int total_match_count = 0;
        
        cin >> input;
        
        // Check if it starts with zero
        if(input[0] == '0') {
		    cout << "E1" << endl;
		    return 0;
		}
        
		// Check if it is a negative number
		if (!is_negative(input)) {
		    cout << "E1" << endl;
		    return 0;
		}

        //Check if the number is unique
        if(!is_digit_unique(input)){
            cout << "E1" << endl;
            return 0;
        }

        // Check if the input string is a valid number
        if (!is_valid_number(input)) {
            cout << "E2" << endl;
            return 0;
        }

        // Check if the input length is correct
        if (!check_input_length(input, number_len)) {
            cout << "E1" << endl;
            return 0;
        }
        
        // Compare input number with the secret number
        compare_input(input, number, exact_match_count, total_match_count);
        
        // If exact matched count is equal to the secret number length, then it means that the secret number has been found
        if (exact_match_count == number_len) {
            cout << "FOUND " << (turn + 1) << endl;
            break;
        }
        
        // Print exact match count and unmatched digit count to the screen
        cout << exact_match_count << " " << total_match_count - exact_match_count << endl;
        
        turn++;
    }
    
    // If it has been reached to the max iteration, it means that secret number has been found
    if (turn == max_iteration) {
        cout << "FAILED" << endl;
    }
    
    return 0;
}
