#ifndef FILELINE_H
#define FILELINE_H

#define SIZE 100
#define MAX_LENGTH 10
#define NUMBER_OF_KEYWORDS 32
#define LINE_NUM 20     

// Define the fileLine struct
typedef struct {
    int lineno;                  // Line number
    int linelen;                 // Line length
    char linetext[MAX_LENGTH];   // Line text
} fileLine;

#endif  // FILELINE_H
