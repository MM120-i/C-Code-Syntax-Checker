# C-Code-Syntax-Checker
Syntax Checker

This repository contains a simple C code syntax checker implemented in C language. The program analyzes C source code files and performs various syntax checks for common C statements, such as printf, scanf, gets, puts, fscanf, fprintf, for, and while loops. The syntax checker helps identify potential errors in the code related to these statements and outputs error messages indicating the line numbers where issues are detected.

Key Features:
- Checks for syntax errors in C code related to common statements.
- Provides detailed error messages with line numbers for easy debugging.
- Modular design with separate functions for checking different types of statements.

How to Use:
- Clone the repository to your local machine.
- Compile the C code syntax checker using a C compiler.
- Run the compiled executable, providing the path to the C source code file as input.
- View the console output for syntax error messages and their corresponding line numbers.

Example Usage:

gcc Checker.c -o Checker

./Checker input.txt

OR

make (To compile)

make clean (To clean compiled files after compilation)

Contributing:
Contributions are welcome! If you find issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

License:
This project is licensed under the MIT License.
