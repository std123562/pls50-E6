#include <stdio.h>

int main()
{
    printf("Please insert Number Operator Number (eg. 5 + 2)\n");

    float number1,number2,result; //float number to run with the requirements
    char c;

    scanf("%f %c %f", &number1, &c, &number2); //collect the data

    //In the statements below we check the operator and do the maths
    if (c== '+') {
        result = number1 + number2;// calculate
        printf("\nThe result is: %.2f ",result);
    } else if (c=='-') {
        result = number1 - number2;// calculate -
        printf("\nThe result is: %.2f ",result); //display result
    } else if (c=='*') {
        result = number1 * number2; // calculate *
        printf("\nThe result is: %.2f ",result); //display result
    } else if (c== '/') {
        if (number2 == 0) { // the statement  checks -if number2 = 0
        printf("Please enter a non-Zero second number\n");
        } else {
        result = number1 / number2;// calculate /
        printf("\nThe result is: %.2f ",result); //display result
        }
    } else {
        printf("\nPlease enter valid options... Valid number and valid operator (eg. + - * /)\n"); // warning for incorrect insert
    }
    return 0;
}
