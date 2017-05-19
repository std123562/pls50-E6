#include <stdio.h>
#include <math.h> // for the sqrt function need...

#define pi 3.14 // I defined as pi = 3.14 just for training...

/* this function below is the basic menu. the user inserts his choice and then the program returns his choice as an integer
for the main program to decide what to do next... */
int menu () {
    int i;
    printf("Please choose one of the below Perimeter Calculate options:\n"); //line 10 to 15 is the menu display
    printf("1: for Square\n");
    printf("2: for Parallelogram\n");
    printf("3: for Orthogonal triangle \n");
    printf("4: for Circle\n");
    printf("0: to Exit the program\nYour choice is>>");
    scanf("%d", &i);//collect choice and put it in an integer
    if (i > 4 || i < 0) {
            printf("Please choose one of the correct options.\n"); // in this if the program checks the validity of the users insert... if wrong it displays the message.
    }
    return i; // the i integer is returned
}

// the function below calculates the perimeter of the triangle
float triangle (float a, float b) {
    float c,per;
    c = sqrt((a*a) + (b*b)); //calculate c side according to the Pythagorean theorem
    per = a+b+c; // calculate the perimeter
    return per; //return perimeter
}

// the function below calculates the perimeter of the parallelogram
float parallelogram (float a, float b) {
    float per;
    per = (a*2) + (b*2);//calculate perimeter
    return per;//return perimeter
}

// this  function calculates the perimeter of the square
float square (float a) {
    float per;
    per = a*4; //calculate perimeter
    return per; //return perimeter
}

//this function below calculates the perimeter of the circle
float circle (float a) {
    float per;
    per = 2* pi * a * a; //calculate perimeter
    return per; //return perimeter
}

//the main function ... it performs  o do-while loop to call the functions above and for menu and calculations
//until the users choses to quit
int main() {
    int l;// an integer to call for choice
    do {
        l = menu();//the l integer is filed with the result of the menu function...
        if (l==1) { // if l is equal to 1 the user inserts the required data and the appropriate function is called
            float a1;
            printf("Please enter the length of side of the Square\nside a: ");
            scanf("%f", &a1); // collects the side of the square
            printf("The perimeter of the Square is: %.2f \n\n", square(a1));//calculate and display result
        } else if (l==2) { // if l is equal to 2 the user inserts the required data and the appropriate function is called
            float a2,b2;
            printf("Please enter the length of the two sides of the Parallelogram\nside a: ");
            scanf("%f", &a2); //collect a side
            printf("\nside b: ");
            scanf("%f", &b2); // collect b side
            printf("The perimeter of the Parallelogram is: %.2f \n\n", parallelogram (a2,b2));//calculate and display result
        } else if (l==3) { // if l is equal to 3 the user inserts the required data and the appropriate function is called
            float a3, b3;
            printf("Please enter the length of the two vertical sides of the triangle\nside a: ");
            scanf("%f", &a3); // collect a side
            printf("\nside b: ");
            scanf("%f", &b3); // collect b side
            printf("The perimeter of the triangle is: %.2f\n\n", triangle(a3,b3));//calculate and display result
        } else if (l==4) { // if l is equal to 4 the user inserts the required data and the appropriate function is called
            float a4;
            printf("Please enter the length of the Radius of the circle\nRadius: ");
            scanf("%f", &a4);//collect radius
            printf("The perimeter of the circle is: %.2f \n\n", circle(a4));//calculate and display result
        } else if (l==0) {
            printf("Thank you for your time! see you...\n");
        }
    } while (l!= 0); //while l is not 0 the loop is performed as many times as the user wants...

    return 0;
}
