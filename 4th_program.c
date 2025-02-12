#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char input[100];
int inde = 0;
int error = 0;

void E();                           
void T();             
void F();


void match(char c) {
    if (input[inde] == c) {
        inde++;
    } else {
        error = 1;
    }
}

void E() {
    T();
    if (error) return;
    if (input[inde] == '+') {
        match('+');
        E();
    }
}

void T() {
    F();
    if (error) return;
    if (input[inde] == '*') {
        match('*');
        T();
    }    
}

void F() {
    if (input[inde] == '(') {
        match('(');
        E();
        if (error) return;
        match(')');
    } else if (input[inde] == 'i') {
        match('i');
    } else {
        error = 1;
    }
} 

int main() {
    printf("Enter an arithmetic expression: ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';
    E();
    if (error == 0 && inde == strlen(input)) {
        printf("Valid expression\n");
    } else {
        printf("Invalid Expression\n");
    }
    return 0;
}
            
               
   


/*
Output:

Enter an arithmentic expression: (i+i)*i
Valid Expression
*/
