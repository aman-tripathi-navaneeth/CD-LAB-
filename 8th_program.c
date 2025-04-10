#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check();

int main() {
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
    puts("Enter input string: ");
    
    // Replacing unsafe gets() with fgets()
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = '\0'; // remove newline if any

    c = strlen(a);
    strcpy(act, "SHIFT->");
    puts("stack \t input \t action");

    for (k = 0, i = 0; j < c; k++, i++, j++) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, a, act);
            check();
            i++;  // Skip next slot as 'd' is added
            j++;  // Skip 'd'
        } else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act);
            check();
        }
    }

    return 0;
}

void check() {
    strcpy(ac, "REDUCE TO E");

    // id -> E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
        }
    }

    // E*E -> E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }

    // (E) -> E
    for (z = 0; z < c; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i = i - 2;
        }
    }
}


//output "
// GRAMMAR is E->E+E 
//  E->E*E 
//  E->(E) 
//  E->id
// Enter input string: 
// id+id\id+id 
// stack 	 input 	 action

// $id	  +id\id+id $	SHIFT->id
// $E	  +id\id+id $	REDUCE TO E
// $E	   id\id+id $	SHIFT->symbols
// $E	     \id+id $	SHIFT->id
// $E	     \id+id $	REDUCE TO E
// $E	      id+id $	SHIFT->symbols
// $E	        +id $	SHIFT->id
// $E	        +id $	REDUCE TO E
// $E	         id $	SHIFT->symbols
// $E	            $	SHIFT->id
// $E	            $	REDUCE TO E
// $E	            $	SHIFT->symbols

// === Code Execution Successful ===
