#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

//Check if the character is a Delimiter 
bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '\n' || ch == '\t') 
        return (true); 
    return (false); 
} 
  
//Check if the character is an Operator 
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=') 
        return (true); 
    return (false); 
}
  
//Check if the string is a Valid Identifier 
bool validIdentifier(char* str) 
{ 
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true) 
        return (false); 
    return (true); 
} 
  
//Check if the string is a Keyword
bool isKeyword(char* str) 
{ 
    if (!strcmp(str, "if") || !strcmp(str, "else") || 
        !strcmp(str, "while") || !strcmp(str, "do") ||  
        !strcmp(str, "break") ||  
         !strcmp(str, "continue") || !strcmp(str, "int") 
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "char") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto")) 
        return (true); 
    return (false); 
} 
  
//Check if the string is an Integer 
bool isInteger(char* str) 
{ 
    int i, len = strlen(str); 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) 
    { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
            return (false); 
    } 
    return (true); 
} 
  
//Check if the string is a Real Number 
bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str); 
    bool hasDecimal = false; 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) 
    { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 
  
//Extract the Substring 
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 
  
//Function to Parse the Input String 
void parse(char* str) 
{ 
    int left = 0, right = 0; 
    int len = strlen(str),i;
    char* s;

    if (len == 0)
    {
        return;
    }

    if (str[left] == '#')
    {
        for (i = 0; str[i] != '\n'; i++)
        {
            s[i] = str[i];
        }
        s[i] = '\0';
        printf("\n%s -> Header File",s);
        return;
    }
    
    while (right <= len && left <= right) 
    { 
        if (isDelimiter(str[right]) == false) 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) 
        { 
            if (isOperator(str[right]) == true) 
                printf("\n%c -> Operator", str[right]); 
  
            right++; 
            left = right; 
        } 
        else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right)) 
        { 
            char* subStr = subString(str, left, right - 1); 
  
            if (isKeyword(subStr) == true) 
                printf("\n%s -> Keyword", subStr);
  
            else if (isInteger(subStr) == true) 
                printf("\n%s -> Integer", subStr); 
  
            else if (isRealNumber(subStr) == true) 
                printf("\n%s -> Real Number", subStr); 
  
            else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false) 
                if (strcmp(subStr,"") != 0)
                {
                    printf("\n%s -> Valid Identifier", subStr); 
                }
                 
            else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false) 
                printf("\n%s -> Invalid Identifier", subStr); 
            left = right; 
        } 
    } 
    return; 
} 
  
void main() 
{ 
    FILE *fptr=fopen("program.txt","r");
    char str[100];
    if (fptr==NULL)
    {
        printf("Error Opening File!!");
        exit(1);
    }
    while (fgets(str,sizeof(str),fptr))
    {
        parse(str);
    }
} 
