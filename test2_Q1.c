/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include<string.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define PERL_IDENTIFIER_SCALAR 2
#define PERL_IDENTIFIER_HASH 3
#define PERL_IDENTIFIER_ARRAY 4
#define JAVA_STRING_LITERAL 5
#define FUNCTION_PRAM 6
#define ARRAY_INDEX 7
#define CODE_BLOCK 50
#define Floating_Point 51
#define UNKNOWN 99



/* Token codes */

#define IDENT 8
#define ASSIGN_OP 9
#define ADD_OP 10
#define SUB_OP 11
#define MULT_OP 12
#define DIV_OP 13
#define MOD_OP 14
#define OPEN_FUNCTION_PRAM 15
#define CLOSE_FUNCTION_PRAM 16
#define OPEN_CODE_BLOCK 17
#define CLOSE_CODE_BLOCK 18
#define HASH_OP 19
#define LOGICAL_NOT_OP 20
#define LOGICAL_AND_OP 22
#define LOGICAL_OR_OP 23
#define OPEN_ARRAY_INDEX 24
#define CLOSE_ARRAY_INDEX 25
#define DOUBLE_QUOTES 26
#define FLOAT_CODE 27
#define FLOAT_TYPE 28
#define INT_TYPE 29
#define STRING_TYPE 30
#define CHARACTER_TYPE 31
#define VOID_TYPE 32
#define INT_LIT 33
#define UNDERSCORE 34
// perl identifier starts with $, @ and %
//$ is for scalar variables, @ is for arrays
//% is for hash
#define PERL_SCALAR 35
#define PERL_ARRAY 36
#define PERL_HASH 37

/******************************************************/
/* main driver */
int main(void) {
    /* Open the input data file and process its contents */
     if ((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
     else {
        getChar();
     do {
        lex();
     } while (nextToken != EOF);
     }
     return 0;
}



/******************************************************/
/* lookup - a function to look up operators and return the token */
int lookup(char ch) {
     switch (ch) { 
         case '+':
             addChar();
             nextToken = ADD_OP;
             break;
         case '-':
             addChar();
             nextToken = SUB_OP;
             break;
         case '*':
             addChar();
             nextToken = MULT_OP;
             break;
         case '/':
             addChar();
             nextToken = DIV_OP;
             break;    
         case '%':
             addChar();
             nextToken = MOD_OP;
             break; 
         case '#':
             addChar();
             nextToken = HASH_OP;
             break;                                                        
         default:
             addChar();
             nextToken = EOF;
             break;
     }
     return nextToken;
}

/******************************************************/
/* lookup - a function to look up floating point characters and return the token */
int lookupfloat(char ch) {
     switch (ch) {
         case '.':
             addChar();
             nextToken = FLOAT_CODE;
             break;
         case 'e':
             addChar();
             nextToken = FLOAT_CODE;
             break;
         case 'E':
             addChar();
             nextToken = FLOAT_CODE;
             break;          

     }
     return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    } else
    printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
     if ((nextChar = getc(in_fp)) != EOF) {
         if (isalpha(nextChar))
            charClass = LETTER;                    
         else if (isdigit(nextChar))
            charClass = DIGIT;
         else if (nextChar == '$' )
            charClass = PERL_IDENTIFIER_SCALAR;  
         else if (nextChar == '%' )
            charClass = PERL_IDENTIFIER_HASH;  
         else if (nextChar == '@' )
            charClass = PERL_IDENTIFIER_ARRAY; 
         else if(nextChar == '_')
            charClass = UNDERSCORE; 
         else if(nextChar == '\"')
            charClass = DOUBLE_QUOTES; 
         else if (nextChar == '(')
             charClass = OPEN_FUNCTION_PRAM;
         else if (nextChar == ')')
             charClass = CLOSE_FUNCTION_PRAM;    
         else if (nextChar == '{')
             charClass = OPEN_CODE_BLOCK;
         else if (nextChar == '}')
             charClass = CLOSE_CODE_BLOCK;  
         else if (nextChar == '[')
             charClass = OPEN_ARRAY_INDEX;
         else if (nextChar == ']')
             charClass = CLOSE_ARRAY_INDEX;  
         else if (isdigit(nextChar))
            charClass = DIGIT;
         else if (nextChar == '.' )
            charClass = Floating_Point; 
         else if (nextChar == 'e' )
            charClass = Floating_Point;    
         else if (nextChar == 'E' )
            charClass = Floating_Point;          			      
         else
            charClass = UNKNOWN;
     }   else
            charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
    while (isspace(nextChar))
    getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
     lexLen = 0;
     getNonBlank();
     switch (charClass) {
       /* Identifiers and Data Types */
         case LETTER:
             addChar();
             getChar();
             while (charClass == LETTER || charClass == DIGIT) {
                 addChar();
                 getChar();
             }
			 /* Here we check if the lexeme equals one of the keywords, if so we assign the correct nextToken */
              if(strcmp(lexeme, "int")==0){
                 nextToken= INT_TYPE;
             }
             else if(strcmp(lexeme, "Integer")==0){
                 nextToken= INT_TYPE;
             }   
             else if(strcmp(lexeme, "String")==0){
                 nextToken= STRING_TYPE;
             }
             else if(strcmp(lexeme, "chr")==0){
                 nextToken= CHARACTER_TYPE;
             }
             else if(strcmp(lexeme, "float")==0){
                 nextToken= FLOAT_TYPE;
             }   
             else if(strcmp(lexeme, "Character")==0){
                 nextToken= CHARACTER_TYPE;
             }
             else if(strcmp(lexeme, "void")==0){
                 nextToken= VOID_TYPE;
             }                                                                                  
             else{
             nextToken = IDENT;
             }
             break;

        /* Integer literals and Floating Points */
         case DIGIT:
             addChar();
             getChar();
			 /* Here I addedd LETTER class to accomadate for when using e or E as exponent */
             while (charClass == DIGIT || charClass == Floating_Point || charClass == LETTER) {
                 addChar();
                 getChar();     
                         
             }
			 /* Here we check if the lexeme equals one of the floating point characters, if so we assign the correct nextToken */
            if (strstr(lexeme, ".") != NULL) {
                nextToken = FLOAT_CODE;
                
            }   
            else if (strstr(lexeme, "e") != NULL) {
                nextToken = FLOAT_CODE;
                
            }   
            else if (strstr(lexeme, "E") != NULL) {
                nextToken = FLOAT_CODE;
                
            }                                    
            else {
                nextToken = INT_LIT;
                
            }
            break;

        /* case for floats, where if the case is a double then we go to the lookupfloat function to check for token value  */
         case Floating_Point:
             lookupfloat(nextChar);
             getChar();
             break;  


         /* Case for Perl Identifier for Scalar */
          case PERL_IDENTIFIER_SCALAR:   
             addChar();
             getChar();
         
             while (charClass == DIGIT || charClass == LETTER || charClass == UNDERSCORE){
               addChar();
               getChar();
             }
             nextToken = PERL_SCALAR;
               break;


         /* Case for Perl Identifier for Hashes */
          case PERL_IDENTIFIER_HASH:   
             addChar();
             getChar();
         
             while (charClass == DIGIT || charClass == LETTER || charClass == UNDERSCORE){
               addChar();
               getChar();
             }
             nextToken = PERL_HASH;
               break;



         /* Case for Perl Identifier for Arrays  */
          case PERL_IDENTIFIER_ARRAY:   
             addChar();
             getChar();
         
             while (charClass == DIGIT || charClass == LETTER || charClass == UNDERSCORE){
               addChar();
               getChar();
             }
             nextToken = PERL_ARRAY;
               break;
         /* Case for Java String Identifier  */
         case DOUBLE_QUOTES:
            do
            {
               addChar();
               getChar();
            }
            while(charClass != DOUBLE_QUOTES); 
               addChar();
               getChar();
               nextToken = JAVA_STRING_LITERAL; 
               break;   
             
       /* Case for Function parameter */
         case OPEN_FUNCTION_PRAM:
            do
            {
               addChar();
               getChar();
            }
            while(charClass != CLOSE_FUNCTION_PRAM); 
               addChar();
               getChar();
               nextToken = FUNCTION_PRAM; 
               break;             

       /* Case for Array index */
         case OPEN_CODE_BLOCK:
            do
            {
               addChar();
               getChar();
            }
            while(charClass != CLOSE_CODE_BLOCK); 
               addChar();
               getChar();
               nextToken = CODE_BLOCK; 
               break;         


       /* Case for Code Block */
         case OPEN_ARRAY_INDEX:
            do
            {
               addChar();
               getChar();
            }
            while(charClass != CLOSE_ARRAY_INDEX); 
               addChar();
               getChar();
               nextToken = ARRAY_INDEX; 
               break;         




        /* Parentheses and operators */
         case UNKNOWN:
             lookup(nextChar);
             getChar();
             break;
            /* EOF */
        case EOF:
             nextToken = EOF;
             lexeme[0] = 'E';
             lexeme[1] = 'O';
             lexeme[2] = 'F';
             lexeme[3] = '\0';
            break;
     } /* End of switch */
     printf("Next token is: %d, Next lexeme is %s\n",
     nextToken, lexeme);
     return nextToken;
} /* End of function lex */

