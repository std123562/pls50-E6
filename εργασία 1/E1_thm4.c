#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variables
FILE *myFile;//declare the myFile
int seats; // this integer will be used for the number of total seats
int freeSeats; // this integer will be used for the number of free seats
int busSeats[53]; // a global array variable for the bus seats, defined to 53 ---values 0 and 1
char busNumber[7]; // the number of the bus eg. AMM5131

//function prototypes
int fileHandler(); // handles the bus.txt file
void signChecker(); // checks the validity of the sign of the bus
int options(); // the options menu function
void displayFreeSeats(); // displays the free seats
void seatReserve (); // function to reserve seat
void reserveSeatInWindow();// reserves the first seat available next to the window
void cancelReservation ();// cancels a reservation
void checkReservedSeat (); // to check if a seat is taken...
void displayReservedSeats ();// to display the reserved seats
void displayBusDiagram ();// display the bus diagram
void saveFile (); // saves the bus diagram in a text file

/* the function below opens the file, reads it, checks it,
and THEN puts the data to the appropriate  variables for further use*/
int fileHandler () {
    int num;// this integer will be used to check if the input is valid, and if yes, to be returned as the number of the seats
    myFile = fopen("bus.txt", "r");//openS the text file. the file is supposed to be placed inside the folder of the program... For read only!
    if (myFile==NULL) {
        printf("Empty File... closing program...\n\n"); // if the file is empty returns a warning and closes the program...
        exit(0);
    } else {
        fscanf(myFile, "%s %d", busNumber, &num);// scan the file and put the number of the bus in global variable string -- char[7] busNumber -- and the number of the seats in num integer for further use
        /* The if statement below checks if the number of the bus seats is greater than 53
           and if the input number is correct -- (num - 5) % 4 !=0) -- and closes the program*/
        signChecker(); // checks the sign of the inserted bus.
        if (num>53 || ((num - 5) % 4 !=0) || num <0){
            printf("The number of the bus seats in the .txt file is incorrect. Please check and try again later\n\n");
            exit(0);
        } else {
            printf("The number of the bus is: %s \n", busNumber); //display the results from the .txt file
            printf("The number of the bus seats are: %d \n\n", num); //display the results from the .txt file
        }

    }
    fclose(myFile);
    return num;
}

// The function below checks if the sign is correct... The sign must be 3 Letters and 4 Number all in Raw
void signChecker() {
    int i; // for the loop
    if (strlen(busNumber) > 7) { // checks if the sign has MORE THAN 7 digits
        printf("Wrong Sign!!! Please enter a correct one in the bus.txt File\n");
        exit(0);
    }
    for (i=0; i<3; i++) {
        if ((busNumber[i]>=0 && busNumber[i]<=9)) {
            printf("Wrong Sign!! Please enter a correct one in the bus.txt File\n");
            exit(0);
        }
    }
    for (i=0; i<4; i++) {
        if ((busNumber[i]<=0 && busNumber[i]>=9)) {
            printf("Wrong Sign! Please enter a correct one in the bus.txt File\n");
            exit(0);
        }
    }
}

/* The function below is used for the display of the menu of options,
   handling the users choice*/
int options () {
    int x;// the users choice
    do {
        printf("Enter 1 to display Free seats\n");
        printf("Enter 2 for new seat reservation\n");
        printf("Enter 3 for new seat reservation in a window seat\n");
        printf("Enter 4 to cancel a reservation\n");
        printf("Enter 5 to check if a specific seat is free for reservation\n");
        printf("Enter 6 to display reserved seats\n");
        printf("Enter 7 to display bus seat diagram\n");
        printf("Enter 8 to save bus data to text file\n");
        printf("Enter 0 to close the program\n>>");
        scanf("%d",&x); // collect choice and handle it
        if (x<0 || x>8) {
            printf("Please enter a valid choice\n");
        }
    } while (x<0 || x>8);
    return x;
}

/*  the function below displays the free seats.
    uses the three inputs for use (number of total seats n ,
    number of free seats m)*/
void displayFreeSeats (int n, int m) {
    int i;
    printf("The number of total free seats is: %d\n", m);
    for (i=0; i<n; i++) { // a loop for checking all the bus seats
        if (busSeats[i] == 0) { // check if free
            printf("\tSeat %d is Free\n", (i+1));
        }
    }
    printf("\n");
}

/* The function below asks the user what seat to reserve and reserves the seat */
void seatReserve () {
    int a; // for the selection of the seat
    printf("Please enter the seat to Reserve\n>>");
    scanf("%d", &a); // users choice
    if (a >= seats || a <=0) { // check if the user input is within the bus seats limits
        printf("Wrong input. Please enter a valid option From 1 to %d \n\n", seats); // error message
    } else if (busSeats[a-1]==1) { //check if the seat is taken
        printf("Wrong input. Seat no.%d is already taken\n\n", a); // error message
    } else {
        busSeats[a-1] = 1; // reserve seat
        printf("seat %d Reserved...\n\n", a);
        freeSeats = freeSeats -1; // the no of free seats is decreased by 1
    }
}

/* the function below when  called automatically reserves the first available seat next to the window
 For more info please read the info.docx
 The int for insert is the total seats the bus has...*/
void reserveSeatInWindow (int totalseats) {
    printf("The first seat available, next to the window will be reserved...\n\n");
    int a; // this integer will be used for the total number of the window seats
    a = ((totalseats - 5)/2) + 2; // the number of window seats is calculated
    int i=0; // for the loop
    int x=0; // for the loop
    do {
        if (i % 2 ==0 ){
            if (busSeats[i*2]==0) {
                if (i*2 >= seats) {
                    printf("All seats in windows are reserved...\n\n");
                    x++;
                } else {
                    busSeats[i*2]=1;
                    printf("Seat No. %d Reserved\n\n",(i*2+1));
                    freeSeats = freeSeats -1;
                    x++;
                }

            }
        } else if (i % 2 !=0) {
            if (i*2+1 >= seats) {
                    printf("All seats in windows are reserved...\n\n");
                    x++;
            }
            else if (i == a - 1) {
                if (busSeats[totalseats - 1]==0) {
                    busSeats[totalseats - 1]=1;
                    printf("Seat No. %d Reserved\n\n", totalseats);
                    freeSeats = freeSeats -1;
                    x++;
                }
            } else {
                if (busSeats[i*2+1]==0) {
                    busSeats[i*2+1]=1;
                    printf("Seat No. %d Reserved\n\n", i*2+2);
                    freeSeats = freeSeats -1;
                    x++;
                }
            }
        }
        i++;
    } while (x==0);
}

/* The function below when called cancels a reservation  already in place.
   If the users choice is incorrect it displays error messages and asks again.
   If the user chooses to exit to main he has to press the 0 number.*/
void cancelReservation () {
    int a;
    int x=0;

    do {
        printf("Please enter the Reserved seat you want to cancel Or press 0 to go to main menu\n>>");
        scanf("%d", &a); // user choice
        if (a == 0) { // if the users choice is 0 then the program goes  to main menu by adding 1 to int x
             x++;
             printf("Exiting to main menu...\n\n");
        }
        else if (a>seats || a <1) { //check for valid input data
            printf("The seat position you have entered is incorrect...\n\n");
        } else if (busSeats[a-1] == 0) { // check if the seat is not taken
            printf("This seat is not Reserved. \nPlease enter a reserved seat\n\n");
        } else { // here the function cancels the reservation.
            busSeats[a-1] = 0;
            printf("Seat No. %d is no longer Reserved...\n\n", a);
            x++;
        }
    } while (x==0);// if the x is 0 the menu is displayed again...

}

/* the function below checks if a specific seat is reserved*/
void checkReservedSeat () {
    printf("Please enter the No. of the seat you want to check\n>>");
    int a;
    scanf("%d", &a); // user input
    if (a > seats || a < 1) // check if the input is valid
        printf("Wrong seat selection please try again later...\n\n");
    // the check for the seat is done in the line below...
    (busSeats[a-1] == 0)? printf("Seat No. %d is Free for reservation...\n\n", a): printf("Seat No. %d is already reserved...\n\n",a);
}

/* The function below displays the reserved seats just like the function displayFreeSeats() does */
void displayReservedSeats () {
    int i;
    printf("The number of total Reserved seats is: %d\n", (seats - freeSeats));//the number of reserved seats is calculated by the abstraction of total seats - free seats...
    for (i=0; i<seats; i++) {
        if (busSeats[i] == 1) {
            printf("\tSeat %d is Reserved\n", (i+1));
        }
    }
    printf("\n");
}

/* The function below displays the bus diagram as asked.. for more info please read the info.docx file*/
void displayBusDiagram () {
    printf("\n    %s \n\n",busNumber);
    int rows = (seats - 5) / 4; // finds the number of the bus seats rows except from the last one...
    int a;
    int i;
    int b;
    int x=0;
    for (a=0; a < rows; a++) {
        for (i=0;i < 2; i++) {
            for ( b=0; b < 2; b++) {
                if (busSeats[x] == 0) {
                    printf(" _ ");
                    x++;
                }else if (busSeats[x] == 1){
                    printf(" * ");
                    x++;
                }
            }
            printf("\t "); // prints the space between the two seats on the left and the 2 seats on the right
        }
        printf("\n");
    }
    for (a=0;a<5;a++) { // prints the seats in the last row -- 5 seats
        if (busSeats[x] == 0) {
            printf(" _ ");
            x++;
        }else if (busSeats[x] == 1){
            printf(" * ");
            x++;
        }
    }
    printf("\n\n");
}

/* The function below does exactly as the function above but doesn't display the data. It saves them to a text file*/
void saveFile () {
    myFile = fopen("layout.txt", "w"); // open or create the layout.txt file
    fprintf(myFile,"   %s \n",busNumber);
    int rows = (seats - 5) / 4; // finds the number of the bus seats rows except from the last one...
    int a;
    int i;
    int b;
    int x=0;
    for (a=0; a < rows; a++) {
        for (i=0;i < 2; i++) {
            for ( b=0; b < 2; b++) {
                if (busSeats[x] == 0) {
                    fprintf(myFile," _ ");
                    x++;
                }else if (busSeats[x] == 1){
                    fprintf(myFile," * ");
                    x++;
                }
            }
            fprintf(myFile,"    "); // prints the space between the two seats on the left and the 2 seats on the right
        }
        fprintf(myFile,"\n");
    }
    for (a=0;a<5;a++) { // prints the seats in the last row -- 5 seats
        if (busSeats[x] == 0) {
            fprintf(myFile," _ ");
            x++;
        }else if (busSeats[x] == 1){
            fprintf(myFile," * ");
            x++;
        }
    }
    fprintf(myFile,"\n");
    fclose(myFile);// close the layout.txt file
    printf("\nbus Diagram Data saved to layout.txt File\n\n");// message to the operator
}

/* The main function of the program opens the file, fills the seats variable,calculates the free seats and then
opens the main menu... Then according to the users choice in the option function opens the appropriate function above...
The program exits only if the user wants to...
*/
int main() {
    int i,k;//
    seats = fileHandler();// the seats var is calling the fileHandler function to get filled...
    // the loop below fills the bus seats with 0s
    for (i=0; i<seats; i++) {
        busSeats[i] = 0;
    }
    freeSeats = seats; // the number of free seats are set equal to the total seats...
    do {
        k = options();
        if (k == 1) {
            displayFreeSeats(seats, freeSeats);
        } else if (k==2) {
            seatReserve ();
        } else if (k==3) {
            reserveSeatInWindow (seats);
        } else if (k==4) {
            cancelReservation ();
        } else if (k==5) {
            checkReservedSeat ();
        } else if (k==6) {
            displayReservedSeats ();
        } else if (k==7) {
            displayBusDiagram ();
        } else if (k==8) {
            saveFile ();
        } else if (k==0) {
            printf("Exiting program.\n\n");
        }
    } while (k!=0);

    return k;
}
