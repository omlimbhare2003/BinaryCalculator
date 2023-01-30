//Project bc
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "bcfun.c"


int main() {
    int i, j;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 80; j++) {
            if(i == 0 || i == 4 || j == 0 || j == 79)
                printf("*");
            else if(i == 2 && j == 25) {
                printf("WELCOME TO BINARY CALCULATOR");     //Printing Introductory Message
                j += 27;
            }
            else printf(" ");
        }
        printf("\n");
    }
    printf("Go on entering the infix expressions\nPress x or X to exit\n");
    char E[1000];  //declare large string
    while(1) {
        istack s; //number stack
        oprstack ab; //operator stack
        init_oprstack(&ab, 500);
        initstack(&s,500);
        char opr;
        j = 0;
        char c;
        i = 0;
        node *n1;
        gets(E);  //take input string
        init(&n1);
        //init(&opnd1);
        //init(&opnd2);
        init_oprstack(&ab, 500);
        initstack(&s,500);
        if(E[i] == 'x' || E[i] == 'X') {  //exit control of program
                printf("\nThank You!!!\n");
                exit(1);
            }
        while(E[i]!= '\0') {
            //if(!isdigit(E[i]) && E[i] != '+' && E[i] != '-' && E[i] != '*' && E[i] != '/' && E[i] != '%' && E[i] != '^' && E[i] != ' ' && E[i] != '(' && E[i] != ')') {
            //    printf("Please Enter Valid Expression\n");
             //   break;
            //}

            c = E[i];
            if(isdigit(c)) {
                append(&n1, c - '0');
                if(!isdigit(E[i+1])) {
                    push(&s, n1);
                    init(&n1);
                }
            }
            else if( c == '(')
                    push_oprstack(&ab,'(');
                else if(c == ')') {
                        while(!isEmpty_oprstack(ab) && peek_oprstack(ab)!= '(') {
                              process(&ab, &s);   /*Process function pops two values from operand stack, pops one value from operator stack , calculates the result and pushes back into operand stack*/
                        }
                        if(peek_oprstack(ab) == '(')
                            pop_oprstack(&ab);
                }
                else {
                        if( c == '+' || c =='-' || c == '*'|| c == '/' || c == '%' || c == '^') {
                            if(isEmpty_oprstack(ab))
                                push_oprstack(&ab, c);
                            else {
                                while(!isEmpty_oprstack(ab) && precedence(peek_oprstack(ab)) >= precedence(c)){
                                      process(&ab, &s);
                                }
                                push_oprstack(&ab, c);
                            }
                        }
                }
            i++;
        }

        while(!isEmpty_oprstack(ab)){  //final check of operator stack
            process(&ab, &s);
        }
        node *res = pop(&s);
        traverse(res);   //Printing result of the expression
        printf("\n");
    }
    return 0;

}
