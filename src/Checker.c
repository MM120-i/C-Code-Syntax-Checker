#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define MAX_LENGTH 10
#define NUMBER_OF_KEYWORDS 32
#define LINE_NUM 20

typedef struct
{

    int lineno;
    int linelen;
    char linetext[SIZE];

} fileLine;

int search(char arr[], int len);
// void analyzeProgram(fileLine arr[], int len);
void print(fileLine str[], int len);
void keyword(fileLine arr[], int len);
void bracket(fileLine arr[], int len);
void builtinfunction(fileLine arr[], int len);
void printScan(fileLine arr[], int size);
int printCheck(char arr[], int size);
int scanCheck(char arr[], int size);
int fprintfCheck(char arr[], int size);
int getsCheck(char arr[], int size);
int putsCheck(char arr[], int size);
void function_and_prototype_count(fileLine arr[], int len);
void varCount(fileLine arr[], int len);
int fscanfcheck(char arr[], int size);
int forCheck(char arr[], int size);
int whileCheck(char arr[], int size);
void fCheck(fileLine arr[], int len);

/**
 * The main function. Reads a C program from a specified input file, analyzes it, and prints the result.
 *
 * @param argc  Number of the command line arguments.
 * @param argv  Array of command line arguments, where argv[1] should contain the input file.
 *
 * @return      Exit status (0 for success)
 */
int main(int argc, char *argv[])
{

    FILE *input;
    fileLine str[SIZE]; // Array to store liness of the C program
    char str1[SIZE];    // Temporary buffer to read lines from the input file
    int totallen, len, found;
    size_t i = 0, j;

    // open the input file for reading
    input = fopen(argv[1], "r");

    // Read lines from the input file and store them in the fileLine array
    while (fgets(str1, SIZE, input) != NULL)
    {
        len = strlen(str1);
        found = search(str1, len);

        // Check if the line is not empty and does not contain a comment
        if (str1[0] != '\n' && found == -1)
        {
            // Store the line details in the fileLine array
            str[i].lineno = i + 1;
            str[i].linelen = len;
            strcpy(str[i].linetext, str1);
            i++;
        }
        else if (str1[0] != '\n' && found != 1) // if the line doesnt start with a comment
        {
            // Store a portion of the line without comment in the fileLine array
            str[i].lineno = i + 1;

            for (j = 0; j < found; j++)
            {
                str[i].linetext[j] = str1[j];
            }

            str[i].linetext[found] = '\n';
            str[i].linelen = strlen(str[i].linetext);
            i++;
        }
    }

    totallen = i;
    // analyzeProgram(str, totallen); // Analyze the c program and print results
    printf("******************THE C- PROGRAM***********************\n\n\n\n");
    printf("\t\tOUTPUT PRINTED ON TEXT FILE NAME OUTPUT\n\n\n");
    print(str, totallen);

    printf("-----------BRACKET ,PARANTHESIS Check-----------\n\n\n\n");
    bracket(str, totallen);

    printf("\n\n\n\t\t\tKEYWORDS with LINE NUMBER\n\n\n");
    keyword(str, totallen);
    // protocheck(str,totallen);

    printf("\n\n\n\t\t\tTOTAL NUMBER OF BUILTIN FUNCTIONS USED\n\n\n");
    builtinfunction(str, totallen);

    printf("\n\n\n\t\t\tTOTAL FUNCTIONS USED INCLUDING MAIN\n\n\n");
    function_and_prototype_count(str, totallen);
    printf("\n\n\n\t\t\tVARIABLES WITH COUNTS\n\n\n");
    varCount(str, totallen);

    printf("\n\n\n\t\t\tSYNTAX CHECK\n\n");
    // printscan(str,totallen);
    fCheck(str, totallen);
    printf("\n\n\n\t\t\tTOTAL LINES IN PROGRAM\n\n\n");
    printf("Total line in Program are: %d", totallen);
    fclose(input);

    return 0;
}

/**
 * Analyzes a C program represented by an array of fileLine structures.
 * Prints various aspects of the program such as brackets, keywords, built-in functions,
 * function counts, variables with counts, syntax check, and total lines.
 * The output is both displayed on the console and written to an output text file.
 *
 * @param arr   Array of fileLine structures representing lines of the C - program
 * @param len   Length of the array.
 */
// void analyzeProgram(fileLine arr[], int len)
// {
//     // Display intro info about the C program.
//     printf("******************THE C- PROGRAM***********************\n\n\n\n");
//     printf("\t\tOUTPUT PRINTED ON TEXT FILE NAME OUTPUT\n\n\n");
//     print(arr, len); // Write program content to an output txt file

//     // Write bracket and parenthesis check info
//     printf("-----------BRACKET, PARENTHESIS Check-----------\n\n\n\n");
//     bracket(arr, len);

//     // Display keywords with line numbers
//     printf("\n\n\n\t\t\tKEYWORDS with LINE NUMBER\n\n\n");
//     keyword(arr, len);

//     // Display total number of built-in functions used
//     printf("\n\n\n\t\t\tTOTAL NUMBER OF BUILTIN FUNCTIONS USED\n\n\n");
//     builtinfunction(arr, len);

//     // Display total functions used, including main
//     printf("\n\n\n\t\t\tTOTAL FUNCTIONS USED INCLUDING MAIN\n\n\n");
//     function_and_prototype_count(arr, len);

//     // Display variables with counts
//     printf("\n\n\n\t\t\tVARIABLES WITH COUNTS\n\n\n");
//     varCount(arr, len);

//     // Display sytanx check info
//     printf("\n\n\n\t\t\tSYNTAX CHECK\n\n");
//     fCheck(arr, len);

//     // Display the total lines in the program
//     printf("\n\n\n\t\t\tTOTAL LINES IN PROGRAM\n\n\n");
//     printf("Total line in Program are: %d", len);
// }

/**
 * Writes the content of the array of fileLine structures to an output text file.
 * Each line is formatted with line number, line length, and line text.
 *
 * @param str   Array of fileLine structures representing lines of text.
 * @param len   Length of the array.
 */
void print(fileLine str[], int len)
{
    FILE *fout = fopen("output.txt", "w");
    for (size_t i = 0; i < len; i++)
    {
        fprintf(fout, "line %d [%d]: %s", str[i].lineno, str[i].linelen, str[i].linetext);
    }
}

/**
 * Searches for the occurrence of the "//" (double slash) comment in a character array.
 *
 * @param arr   Character array representing a line of text.
 * @param len   Length of the character array.
 *
 * @returns     If found, the index of the start of the "//" comment; otherwise, returns -1
 */
int search(char arr[], int len)
{
    int found = 0;

    // Loop through each character in the character array
    for (size_t i = 0; !found && i < len; i++)
    {
        // Check if the current and next characters from the "//" comment
        if (arr[i] == '/' && arr[i + 1] == '/')
        {
            return i;  // Return the index of the start of the "//" comment
            found = 1; // setting to 1 to indicate that a comment is found
        }
    }

    // If the "//" comment is not found, then return -1
    if (!found)
    {
        return -1;
    }
}

/**
 * Identifies and prints C keywords along with their line numbers in the src code.
 *
 * @param arr   Array of fileLine structures representing the src code lines.
 * @param len   The number of lines in the src code.
 */
void keyword(fileLine arr[], int len)
{
    char str[SIZE], currentWord[SIZE];
    size_t i, j, k;

    // C keywords to be checked for
    char sync[NUMBER_OF_KEYWORDS][MAX_LENGTH] = {
        "auto",
        "double",
        "int",
        "struct",
        "break",
        "else",
        "long",
        "switch",
        "case",
        "enum",
        "register",
        "typedef",
        "char",
        "extern",
        "return",
        "union",
        "const",
        "float",
        "short",
        "unsigned",
        "continue",
        "for",
        "signed",
        "void",
        "default",
        "goto",
        "sizeof",
        "volatile",
        "do",
        "if",
        "static",
        "while"};

    // Loop through each line in the source code
    for (i = 0; i < len; i++)
    {
        int pos = 0, k;
        strcpy(str, arr[i].linetext);

        // Loop through each character in the line
        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                // Terminate the currentWord string
                currentWord[k] = '\0';

                // Check if the current word is a C keyword
                for (k = 0; k < NUMBER_OF_KEYWORDS; k++)
                {
                    if (strcmp(currentWord, sync[k]) == 0)
                    {
                        // Print the keyword and its line number
                        printf("Line %d: %s\n", arr[i].lineno, currentWord);
                    }
                }

                // Reset k and update the position
                k = 0;
                pos = j + 1;
            }
            else
            {
                // Add the character to the currentWord
                currentWord[k] = str[j];
                k++;
            }
        }
    }
}

/**
 * Checks the balance of curly braces, parentheses, and square brackets in the C code.
 *
 * @param arr   Array of file line containing C code.
 * @param len   Number of lines in the array.
 */
void bracket(fileLine arr[], int len)
{
    // 'p' is an array to keep track of the count of different brackets.
    int *p;
    size_t i, j;

    // Allocating memory for the array p to store counts for different brackets
    p = (int *)calloc(3, sizeof(int));

    // Arrays to store line numbers where different brackets are opened or closed.
    int linea1[LINE_NUM], linea2[LINE_NUM], lineb1[LINE_NUM], lineb2[LINE_NUM], linec1[LINE_NUM], linec2[LINE_NUM];
    int a = 0, a2 = 0, b = 0, b2 = 0, c = 0, c2 = 0;

    // Loop through each line in the input file (code file)
    for (i = 0; i < len; i++)
    {
        // Loop through each character in the line
        for (j = 0; j < arr[i].linelen; j++)
        {
            // Check for different types of brackets and update counts and line numbers accordingly.
            switch (arr[i].linetext[j])
            {
            case '{':
                *p = *p + 1;
                linea1[a++] = arr[i].lineno;
                break;

            case '}':
                *p = *p - 1;
                linea2[a2++] = arr[i].lineno;
                break;

            case '(':
                *(p + 1) = *(p + 1) + 1;
                lineb1[b++] = arr[i].lineno;
                break;

            case ')':
                *(p + 1) = *(p + 1) - 1;
                lineb2[b2++] = arr[i].lineno;
                break;

            case '[':
                *(p + 2) = *(p + 2) + 1;
                linec1[c++] = arr[i].lineno;
                break;

            case ']':
                *(p + 2) = *(p + 2) - 1;
                linec2[c2++] = arr[i].lineno;
                break;

            default:
                break;
            }
        }
    }

    // Print messages for any unbalanced brackets
    while (*p > 0)
    {
        printf("line %d: { is greater\n", linea1[--a]);
        *p -= 1;
    }

    while (*p < 0)
    {
        printf("line %d: } is greater\n", linea2[--a2]);
        *p += 1;
    }

    while (*(p + 1) > 0)
    {
        printf("line %d: ( is greater\n", lineb1[--b]);
        *(p + 1) -= 1;
    }

    while (*(p + 1) < 0)
    {
        printf("line %d: ) is greater\n", lineb2[--b2]);
        *(p + 1) += 1;
    }

    while (*(p + 2) > 0)
    {
        printf("line %d: [ is greater\n", linec1[--c]);
        *(p + 2) -= 1;
    }

    while (*(p + 2) < 0)
    {
        printf("line %d: ] is greater\n", linec2[--c2]);
        *(p + 2) += 1;
    }

    // Free allocated memory
    free(p);
}

/**
 * Count and print the total number of occurrences of predefined builtin function in the code.
 *
 * @param arr   Array of file lines containing code info.
 * @param len   Length of the array.
 */
void builtinfunction(fileLine arr[], int len)
{
    // Declare variables for storing the line and current word.
    char str[SIZE], currentWord[SIZE];
    char sync[30][MAX_LENGTH] = {
        "printf",
        "scanf",
        "gets",
        "puts",
        "fsanf",
        "fprintf",
        "fgets",
        "fputs",
        "fputc",
        "fgetc",
        "fopen",
        "fclose",
        "feof",
        "fflush",
        "malloc",
        "calloc",
        "rand",
        "strcmp",
        "strlen",
        "strcpy",
        "strncpy",
        "strncmp",
        "tolower",
        "toupper",
        "strrev",
        "getch",
        "strcat",
        "strncat",
        "sqrt",
        "pow"};

    size_t i, j, l;
    int total = 0;

    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext); // Copy the line text to a local variable

        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                currentWord[k] = '\0'; // Null-terminate the current word
                for (l = 0; l < 30; l++)
                {
                    if (strcmp(currentWord, sync[l]) == 0)
                    {
                        total += 1; // Increment total if the word is a built in function.
                    }
                }

                k = 0;
                pos = j + 1;
            }
            else
            {
                currentWord[k] = str[j]; // Add characters to the current word
                k++;
            }
        }
    }

    printf("Total Builtin Functions: %d\n", total); // Print the total count
}

/**
 * Print and analyze lines with print and scan functions.
 *
 * @param arr   Array of file lines containing code info.
 * @param size  Size of the array
 */
void printScan(fileLine arr[], int size)
{
    size_t i, j, k, l, x;
    char str[SIZE];

    for (i = 0; i < size; i++)
    {
        // Skip leading white spaces in the line
        for (x = 0; (arr[i].linetext[x] == ' ' || arr[i].linetext[x] == '\t'); x++)
            ;
        printf("%d", x); // Print the count of leading spaces or tabs.

        // Extract the sub-string excluding leading whitespaces
        for (size_t a = 0; arr[i].linelen - x; a++)
        {
            str[a] = arr[i].linetext[x + a];
        }

        // Check if the line contains the printf function
        if (strncmp(arr[i].linetext, "printf", 6) == 0)
        {
            printCheck(str, arr[i].linelen);
            printf("exist\n");
        }

        // Check if the line contains the scanf function
        if (strncmp(arr[i].linetext, "scanf", 5) == 0)
        {
            scanCheck(str, arr[i].linelen);
            printf("scanf exist\n");
        }
    }
}

/**
 * @brief Checks the format of a printf statement in the given array.
 *
 * This function counts the occurrences of "%", ",", and " "
 * characters in the input array and checks if the counts are valid for a printf statement.
 *
 * @param arr   The input character array representing a line of code.
 * @param size  The size of the input character array.
 * @return      1 if the format check fails, 0 otherwise.
 */
int printCheck(char arr[], int size)
{
    int pCount = 0, cCount = 0, iCount = 0, flag = 0;

    // Loop through the characters in the array
    for (size_t i = 0; i < size; i++)
    {
        switch (arr[i])
        {
        case '%':
            pCount++;
            break;

        case ',':
            cCount++;
            break;

        case '\"':
            iCount++;
            break;

        default:
            break;
        }
    }

    // Check the conditions for invalid printf format
    if (pCount != cCount || iCount % 2 != 0)
    {
        flag = 1;
    }

    return flag;
}

/**
 * @brief Checks the format of a scanf statement in the given array.
 *
 * This function counts the occurrences of '%' (percent), ',' (comma), '\"' (double quote),
 * '&' (ampersand), and '%s' (string specifier) characters in the input array.
 * It then checks if the counts are valid for a scanf statement.
 *
 * @param arr The input character array representing a line of code.
 * @param size The size of the input character array.
 * @return 1 if the format check fails, 0 otherwise.
 */
int scanCheck(char arr[], int size)
{
    int pCount = 0, cCount = 0, iCount = 0, flag = 0, aCount = 0, sCount = 0;

    // Loop through the characters in the array
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == '%')
        {
            pCount++;
        }
        else if (arr[i] == ',')
        {
            cCount++;
        }
        else if (arr[i] == '\"')
        {
            iCount++;
        }
        else if (arr[i] == '&')
        {
            aCount++;
        }
        else if (arr[i] == '%' && arr[i + 1] == 's')
        {
            sCount++;
        }
    }

    // Check the conditions for invalid scanf format.
    if ((pCount != cCount) || (iCount % 2 != 0) || ((pCount - sCount) != aCount))
    {
        flag = 1;
    }

    return flag;
}

/**
 * @brief Checks the syntax of the fprintf function call in a given string.
 *
 * @param arr The character array containing the string to be checked.
 * @param size The size of the character array.
 * @return Returns 1 if there is a syntax error, otherwise returns 0.
 */
int fprintfCheck(char arr[], int size)
{
    int pCount = 0, cCount = 0, iCount = 0, flag = 0;

    // Loop through each character in the array

    for (size_t i = 0; i < size; i++)
    {
        switch (arr[i])
        {
        case '%': // Count the occurrences of '%' character

            pCount++;
            break;

        case ',': // Count the occurrences of ',' character

            cCount++;
            break;

        case '\"': // Count the occurrences of '\"' character

            iCount++;
            break;

        default:
            break;
        }
    }

    // Check for syntax errors: unequal '%' and ',' counts, or odd number of '\"'

    if ((pCount != cCount - 1) || (iCount % 2 != 0))
    {
        flag = 1;
    }

    return flag;
}

/**
 * Checks for potential security issues in a string intended for gets function.
 *
 * @param arr   The character array to be checked.
 * @param size  The size of the character array.
 * @return      Returns 1 if potential security issues are found, otherwise 0.
 */
int getsCheck(char arr[], int size)
{
    int flag = 0;

    // Iterate through each character in the array
    for (size_t i = 0; i < size; i++)
    {
        // Check for characters that might indicate security issues
        if (arr[i] == '%' || arr[i] == ',' || arr[i] == '\"' ||
            arr[i] == '&' || arr[i] == '\'')
        {
            flag = 1;
        }
    }

    return flag; // Return the final flag value indicating the presence of potential issues
}

/**
 * Checks if the given character array contains any of the specified characters.
 *
 * @param arr   The character array to be checked.
 * @param size  The size of the character array.
 * @return      Returns 1 if any of the specified characters ('%', ',', '\"', '&', '\'') is found, 0 otherwise.
 */
int putsCheck(char arr[], int size)
{
    int flag = 0;

    // Loop through each character in the array.
    for (size_t i = 0; i < size; i++)
    {
        // Check if the current character is any of the specified characters.
        if (arr[i] == '%' || arr[i] == ',' || arr[i] == '\"' ||
            arr[i] == '&' || arr[i] == '\'')
        {
            flag = 1;
        }
    }

    return flag;
}

/**
 * Counts the total number of functions (including main function) and prototypes in the given array of lines.
 *
 * @param arr   The array of lines to be analyzed.
 * @param len   The length of the array.
 */
void function_and_prototype_count(fileLine arr[], int len)
{
    char str[SIZE], currentWord[SIZE];
    char sync[7][MAX_LENGTH] = {
        "int",
        "char",
        "void",
        "double",
        "float",
        "long",
        "short"};

    size_t i, j, l;
    int total = 0;

    for (i = 0; i < len; i++) // Count total functions (including main function) in the array.
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext);
        int strlength;
        strlength = arr[i].linelen;

        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                currentWord[k] = '\0';
                for (l = 0; l < 7; l++)
                {
                    if ((strcmp(currentWord, sync[l]) == 0) && (str[strlength - 2] == ')'))
                    {
                        total++;
                    }
                }
                k = 0;
                pos = j + 1;
            }
            else
            {
                currentWord[k] = str[j];
                k++;
            }
        }
    }

    // Print the total number of functions.
    printf("Total Functions used including main function: %d\n", total);

    int fun = 0, found = 0, m, pos = 0;

    // Search for the main function and store its position.
    for (l = 0; l < len && !found; i++)
    {
        int k = 0;
        strcpy(str, arr[i].linetext);
        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                currentWord[k] = '\0';
                k = 0;
            }
            else
            {
                currentWord[k] = str[j];
                k++;

                if (strcmp(currentWord, "main") == 0)
                {
                    found = 1;
                    pos = i;
                    break;
                }
            }
        }
    }

    fun = 0;

    // Count the prototypes before the main function.
    for (i = 0; i < pos; i++)
    {
        int k = 0;
        strcpy(str, arr[i].linetext);
        int strlength;
        strlength = arr[i].linelen;

        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                currentWord[k] = '\0';
                for (l = 0; l < 7; l++)
                {
                    if ((strcmp(currentWord, sync[l]) == 0) && str[strlength - 3] == ')' && str[strlength - 2] == ';')
                    {
                        fun++;
                    }
                }

                k = 0;
                pos = j + 1;
            }
            else
            {
                currentWord[k] = str[j];
                k++;
            }
        }
    }

    // Print the total number of prototypes.
    printf("\n\n\n\t\t\tPROTOTYPE CHECK\n\n\n");
    printf("Total prototype: %d\n", fun);

    // Check if all prototypes are defined.
    if (fun < total - 1)
    {
        printf("Some prototypes are not defined.\n");
    }
    else
    {
        printf("Prototypes are defined.\n");
    }
}

/**
 * Counts the occurrences of different variable types and calculates the memory consumed by each type.
 *
 * @param arr   Array of fileLine structures representing lines of the C program.
 * @param len   Length of the array.
 */
void varCount(fileLine arr[], int len)
{
    char str[SIZE], currnetWord[SIZE];
    char sync[6][MAX_LENGTH] = {
        "int",
        "char",
        "long",
        "double",
        "float",
        "short"};

    size_t i, j, l;
    int total[6] = {0}, memory[6] = {0};

    // Loop through each line in the array
    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext);
        int strlength;
        strlength = arr[i].linelen;

        // Copy the line text to a local string
        for (j = 0; j < arr[i].linelen; j++)
        {
            // Check for space, parenthesis, null terminator, or tab to identify the end of a word
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' | str[j] == '\t')
            {
                // Null-terminate the current word
                currnetWord[k] = '\0';

                // Check if the current word matches any of the synchronization words
                for (size_t l = 0; l < 6; l++)
                {
                    if (strcmp(currnetWord, sync[l]) == 0)
                    {
                        pos = j;

                        // Check if the line does not end with ')' to ensure it is a function declaration
                        if ((str[strlength - 3] != ')') && (str[strlength - 2] != ')'))
                        {
                            // Loop through the line to count commas and semicolons, indicating variable declarations
                            for (size_t x = 0; x < strlength; x++)
                            {
                                if (str[x] == ',' || str[x] == ';')
                                {
                                    total[l]++;
                                }
                            }
                        }
                    }
                }

                k = 0; // Reset the current word index
            }
            else
            {
                // Add the current character to the current word
                currnetWord[k] = str[j];
                k++;
            }
        }
    }

    // Print the total counts for each type
    printf("Total int: %d\nTotal Char: %d\nTotal long integer: %d\nTotal Double: %d\nTotal float: %d\nTotal short integer: %d\n", total[0], total[1], total[2], total[3], total[4], total[5], total[6]);

    // Calculate memory consumed by variables for each type
    memory[0] = total[0] * sizeof(int);
    memory[1] = total[1] * sizeof(char);
    memory[2] = total[2] * sizeof(long);
    memory[3] = total[3] * sizeof(double);
    memory[4] = total[4] * sizeof(float);
    memory[5] = total[5] * sizeof(short);

    // // Calculate memory consumption for each data type
    // for (size_t s = 0; s < 6; s++)
    // {
    //     if (strcmp(currnetWord, sync[s]) == 0)
    //     {
    //         memory[s] = total[s] * sizeof(sync[s]);
    //         break;
    //     }
    // }

    // Print the memory consumed by variables for each type
    printf("\n\n\n\t\t\tMEMORY CONSUMED BY VARIABLES\n\n\n");
    printf("Memory int: %d BYTES\nMemory Char: %d BYTES\nMemory long integer: %d BYTES\nMemory Double: %d BYTES\nMemory float: %d BYTES\nMemory short integer: %d BYTES\n", memory[0], memory[1], memory[2], memory[3], memory[4], memory[5], memory[6]);
}

/**
 * Checks the format specifier string for potential issues in the fscanf function call.
 *
 * @param arr   Format specifier string to be checked.
 * @param size  Size of the format specifier string.
 * @return      0 if the format specifier string is valid, 1 if there are potential issues.
 */
int fscanfcheck(char arr[], int size)
{
    int pCount = 0, cCount = 0, iCount = 0, flag = 0, aCount = 0, sCount = 0;

    // Loop through each character in the format specifier string
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == '%') // Count the number of '%' characters
        {
            pCount++;
        }
        if (arr[i] == ',') // Count the number of ',' characters
        {
            cCount++;
        }
        if (arr[i] == '\"') // Count the number of '\"' characters
        {
            iCount++;
        }
        if (arr[i] == '&') // Count the number of '&' characters
        {
            aCount++;
        }
        if (arr[i] == '%' && arr[i] == 's') // Count the number of '%s' occurrences
        {
            sCount++;
        }
    }

    // Check for potential issues in the format specifier string
    if ((pCount != cCount - 1) || (iCount % 2 != 0) || ((pCount - sCount) != aCount))
    {
        flag = 1;
    }

    return flag;
}

/**
 * Checks the syntax of a C for loop by analyzing the provided character array.
 *
 * @param arr   Character array representing the C for loop to be checked.
 * @param size  Size of the character array.
 * @return      0 if the for loop syntax is valid, 1 if there are potential issues.
 */
int forCheck(char arr[], int size)
{
    int pCount = 0, qCount = 0, flag = 0;

    // Loop through each character in the provided character array
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == ';') // Count the number of ';' characters
        {
            pCount++;
        }
        else if (arr[i] == '\'') // Count the number of '\'' (single quote) characters
        {
            qCount++;
        }
    }

    // Check for potential issues in the C for loop syntax
    if ((pCount != 2) || (qCount % 2 != 0))
    {
        flag = 1;
    }

    return flag;
}

/**
 * Checks the syntax of a C while loop by analyzing the provided character array.
 *
 * @param arr   Character array representing the C while loop to be checked.
 * @param size  Size of the character array.
 * @return      0 if the while loop syntax is valid, 1 if there are potential issues.
 */
int whileCheck(char arr[], int size)
{
    int qCount = 0, flag = 0, iCount = 0;

    // Loop through each character in the provided character array
    for (size_t i = 0; i < size; i++)
    {
        switch (arr[i])
        {
        case ';': // If a ';' is encountered, set the flag to indicate a potential issue
            flag = 1;
            break;

        case '\'': // Count the number of '\'' (single quote) characters
            qCount++;
            break;

        case '\"': // Count the number of '\"' (double quote) characters
            iCount++;
            break;

        default:
            break;
        }
    }

    // Check for potential issues in the C while loop syntax
    if ((qCount % 2 != 0) || (iCount % 2 != 0))
    {
        flag = 1;
    }

    return flag;
}

/**
 * Checks the syntax of various C statements in the given array of file lines.
 *
 * @param arr   Array of fileLine structures representing the lines of the C program.
 * @param len   Number of elements in the array.
 */
void fCheck(fileLine arr[], int len)
{
    char str[SIZE], currentWord[SIZE];
    char sync[8][MAX_LENGTH] = {"printf", "scanf", "gets", "puts", "fscanf", "fprintf", "for", "while"};
    size_t i, j, l, f;

    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext);

        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                currentWord[k] = '\0';

                // Iterate over the sync array and perform corresponding syntax checks
                for (l = 0; l < 8; l++)
                {
                    if (strcmp(currentWord, sync[l]) == 0)
                    {
                        // Use a function pointer to call the appropriate check function
                        int (*checkFunction)(char[], int) = NULL;

                        switch (l)
                        {
                        case 0:
                            checkFunction = printCheck;
                            break;

                        case 1:
                            checkFunction = scanCheck;
                            break;

                        case 2:
                            checkFunction = getsCheck;
                            break;

                        case 3:
                            checkFunction = putsCheck;
                            break;

                        case 4:
                            checkFunction = fscanfcheck;
                            break;

                        case 5:
                            checkFunction = fprintfCheck;
                            break;

                        case 6:
                            checkFunction = forCheck;
                            break;

                        case 7:
                            checkFunction = whileCheck;
                            break;

                        default:
                            break;
                        }

                        // Perform the syntax check using the selected function
                        f = checkFunction(str, arr[i].linelen);

                        if (f)
                            printf("Error in Statement : ---> line no: %d\n", arr[i].lineno);

                        break; // Break out of the loop once a match is found
                    }
                }

                k = 0;
            }
            else
            {
                currentWord[k] = str[j];
                k++;
            }
        }
    }
}

/** Credits to https://github.com/sanifalimomin/C-Syntax-Checker/tree/master for the base source code. Further modifications to the code is done by me.*/
