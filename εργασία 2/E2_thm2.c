#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// we declare the structure as a type.
typedef struct {
    char fullName[42]; // Name
    unsigned short int tel[10]; // Telephone
    unsigned int seatNumber; // Seat Number
} BUSSEATS;

// the struct below is for the linked list
typedef struct linkSeats {
    char fullName[42]; // Name
    unsigned short int tel[10]; // Telephone
    unsigned int seatNumber; // Seat Number
    struct linkSeats *next;
} RESERVEDSEATS;

// below we declare the necessary global variables
FILE *myFile;
char busNumber[8]; // the number of the bus eg. AMM5131
int seats; // this integer will be used for the number of total seats
int freeSeats; // this integer will be used for the number of free seats
BUSSEATS *busSeats;// This is a pointer which is going to be used as a dynamic array.
//


// function prototypes
int fileHandler(); // improved version of the previous file handler...
void signChecker(); // checks the validity of the bus sign...
int options(); // an updated version of the options menu
void seatReserve ();// check if a seat is reserved
void reservationCheck(); // this function checks if a specific seat is reserved.. it's implemented ether by asking Name or tel number.
void cancelReservation();// this function cancels an already reserved seat
void swapSeats(BUSSEATS *firstSeat, BUSSEATS *secondSeat);//used by the 2 functions below
void displayReservedSeats();//displayes the reserved seats
void saveData();//saves the data to the txt file.


// this function is opening the file, reads the data, checks them, creates the dynamic array and fills it...
int fileHandler () {
    char firstName[21];
    char lastName[21];
    char tempTelephone[11];// they will be used for reading the tel digits
    int k,m;
    unsigned int seatnumber;
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
            printf("The number of the bus seats in the bus.txt file is incorrect. Please check and try again later\n\n");
            exit(0);
        } else {
            printf("The number of the bus is: %s \n", busNumber); //display the results from the .txt file
            printf("The number of the bus seats are: %d \n\n", num); //display the results from the .txt file
        }
    }
    // the statement below creates the dynamic array and gets its space in memory
    busSeats = (BUSSEATS *)malloc(num * sizeof(BUSSEATS));
    // the statements below add the names from the bus.txt file to the dynamic array structure busSeats.
    //first  a loop fills all the array structure with "\0" and 0s data
    //the fscanf reads a line, puts the data to the temporary functions variables.
    //then the program copies these variable values to the appropriate structure array place.
    // the getc(myFile) in the while loop gets the next available character. If is's \n then the program goes on
    // if it is the end of file...  the program terminates the loop
    for (k=0;k<num;k++) {
        strcpy(busSeats[k].fullName, "\0");
        busSeats[k].seatNumber = k+1;
        for (m=0;m<10;m++)
            busSeats[k].tel[m] = 0 ;
    }
    while (getc(myFile)!=EOF) {
        fscanf(myFile, "%s %s %u %s", lastName, firstName, &seatnumber, tempTelephone);
        busSeats[seatnumber-1].seatNumber = seatnumber;
        strcpy(busSeats[seatnumber-1].fullName, lastName);
        strcat(busSeats[seatnumber-1].fullName, " ");
        strcat(busSeats[seatnumber-1].fullName, firstName);
        unsigned short int x; //below we convert the letters of the telephone string into integers
        for (m=0;m<10;m++) {
            x = tempTelephone[m] - '0';
            busSeats[seatnumber-1].tel[m] = x;
        }
    }
    printf("\n");
    fclose(myFile);
    return num;
}

/* like the previous version, this function checks if the sign data are correct.*/
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

int options () {
    int x;// the users choice
    do {
        printf("Enter 1 to display Free seats\n");
        printf("Enter 2 for new seat reservation\n");
        printf("Enter 3 to check if a seat is reserved\n");
        printf("Enter 4 to cancel a seat reservation\n");
        printf("Enter 5 to display the list of all the reserved seats\n");
        printf("Enter 0 to exit Program and Save Data\n>>");
        scanf("%d",&x); // collect choice and handle it
        if (x<0 || x>5) {
            printf("Please enter a valid choice\n");
        }
    } while (x<0 || x>5);
    return x;
}

/* This function gets an integer as the total bus seats. Then it checks if in the struct array the string name is NULL
and increases an integer by one. This integer in the end is used to display the total free seats of the bus.
 Then by using the same principles the program displays each free seat*/
int displayFreeSeats (int n) {
    int t,m,i,j=0; // the j will be used to calculate the free seats, all the others are for the loops...
    t=0;
    m=0;
    //calculation of the number of free seats by checking if the name is \0 and incrementing th j by 1
    for (t=0;t < n;t++) {
        if (strlen(busSeats[t].fullName) < 1 ) {
            j++;
        }
    }
    printf("The number of total free seats is: %d\n", j);
    for (i=0; i<n; i++) { // a loop for checking all the bus seats
        if (strlen(busSeats[i].fullName) < 1) {
            printf("\tSeat %d is Free\n", (i+1));
        }
    }
    printf("\n");
    return j;
}

/* This function is used to reserve a free seat for a new person. */
void seatReserve () {
    unsigned int x; // for the selection of the seat
    char fName[21]; // temp
    char lName[21]; // temp
    char newtempTel[11];// will be used to read the telephone number, then converted to short array
    printf("Please enter the seat to Reserve\n>>");
    scanf("%u", &x); // users choice
    if (x > seats || x <=0) { // check if the user input is within the bus seats limits
        printf("Wrong input. Please enter a valid option From 1 to %d \n\n", seats); // error message
    } else if (strlen(busSeats[x-1].fullName) > 1 ) { //check if the seat is taken
        printf("Wrong input. Seat no.%d is already taken\n\n", x); // error message
    } else {
        printf("Please enter the First Name: "); // lines 170 - 178 get the data and put into the struct array
        scanf("%s", fName);
        printf("please enter the Last Name: ");
        scanf("%s", lName);
        printf("Please enter the telephone number: ");
        scanf("%s", newtempTel);
        strcpy(busSeats[x-1].fullName, lName);
        strcat(busSeats[x-1].fullName, " ");
        strcat(busSeats[x-1].fullName, fName);
        unsigned short int q,m; //below we convert the letters of the telephone string into integers
        for (m=0;m<10;m++) {
            q = newtempTel[m] - '0';
            busSeats[x-1].tel[m] = q;
        }
        printf("seat %d Reserved for %s with phone number: %s\n\n", x,busSeats[x-1].fullName, newtempTel); // message display
    }
}

/* This function is used to check if a seat is reserved by name or by phone... The function doesn't calculate
if a name or a telephone is duplicated... */
void reservationCheck () {
    int x;
    int i; // for the strcmp()
    int k=0;
    int r=0;
    char name[42]; // temp
    char fName[21]; // temp
    char lName[21]; // temp
    char tmpTel[11]; //temp
    unsigned short int tmptel2[10];
    unsigned short int a;
    printf("Please enter 1 to check reserved seat by Name\n\tOR 2 to check reserved seat by phone\n>>");
    scanf("%d",&x);
    if (x<1 || x>2) {
        printf("Wrong input. Please try again later...\n\n");
    } else {
        //below compare by name.....
        if (x==1) {
            printf("Please enter the Name: ");//read the data and put them in the temp var
            scanf("%s %s", lName,fName);
            strcpy(name, lName);
            strcat(name, " ");
            strcat(name, fName);
            while (k < seats) {// this loop checks the seats
                i = strcmp(name, busSeats[k].fullName); // compare the temp var with the array
                if (i == 0){
                  printf("\nSeat No. %d is Reserved by %s\n\n", k+1, busSeats[k].fullName);
                  k=seats;//to stop the loop...
                } else if (i!=0){
                    k++;
                    if (k==seats)
                        printf("\n%s has not reserved any seat yet...\n\n", name);
                }
            }
            //below compare by tel. number......
        } else if (x==2) {
            printf("Please enter the Telephone number: ");
            scanf("%s", tmpTel);
            //the statements below convert the char array to an unsigned short array
            int m;
            for (m=0;m<10;m++) { // convert string to integer
            a = tmpTel[m] - '0';
            tmptel2[m] = a;
            }
            do {
                while (tmptel2[r] == busSeats[k].tel[r]){
                    r++;
                }
                if (r == 10) {
                    printf("\nseat No. %d is reserved by %s with phone number: ", k+1, busSeats[k].fullName);
                    for (m=0;m<10;m++)
                        printf("%hu", tmptel2[m]);
                    printf("\n\n");
                    k=seats + 1;// to stop the loop
                } else  if (k==seats-1){
                    printf("\nThe person with phone number %s hasn't made any reservation yet.\n\n", tmpTel);
                    k++;
                } else {
                    k++;
                    r=0;
                }
            } while (k < seats);
        }
    }
}

/*The function below cancels a reservation. to achieve that asks the user to put a seat number, checks if correct, checks if this
seat number is reserved or not, and if yes it sets this seat free. */
void cancelReservation () {
    int a,b;
    printf("Please enter the reserved seat you want to free: ");
    scanf("%d", &a);
    if (a > seats || a <1) {
        printf("Wrong input... Please try again later!\n\n");// error message
    } else  {
        if (strlen(busSeats[a-1].fullName)> 1) {
            printf("\nSeat No. %d is reserved for %s\n", a, busSeats[a-1].fullName);//display to whome the seat is reserved
            strcpy(busSeats[a-1].fullName, "\0");//set name to null
            for (b=0;b<10;b++)
                busSeats[a-1].tel[b] = 0; // set tel number to 000000000
            printf("\n Reservation Canceled...\n\n");
        } else if (strlen(busSeats[a-1].fullName) < 1){ // this seat isn't reserved
            printf("\nThis seat is not reserved...\n\n");
        }
    }
}

/*This function is used by the two below to change the positions of the struct array by using a temp struct of the same type... */
void swapSeats (BUSSEATS *firstSeat, BUSSEATS *secondSeat) {
    BUSSEATS *temp = (BUSSEATS *)malloc(sizeof(BUSSEATS));
    *temp = *firstSeat;
    *firstSeat = *secondSeat;
    *secondSeat = *temp;
    free(temp);
}

/*This function displays the reserved seats by 2 ways.
1. by Name and
2. by seat number according to the users choice.
In the first case the array is first converted according to the name, displayed, and then put back in place */
void displayReservedSeats () {
    int input, a;
    int tmpsts = seats;
    int at_least_one_swap = 1;
    printf("Enter 1 to display list by Name OR\n2 to display list by SeatNumber\n");
    scanf("%d", &input);
    if (input<1 || input>2){
        printf("Wrong input. Please try again later...\n\n");
        return;
    }
    if (input==1) {
        printf("\n");
        // part 1 swap the seats
        while (at_least_one_swap) {
            at_least_one_swap =0;

            for (a=0; a < tmpsts-1; a++) {
                if (strcmp(busSeats[a].fullName,busSeats[a+1].fullName)> 0) {
                    swapSeats(&busSeats[a], &busSeats[a+1]);
                    at_least_one_swap =1;
                }
            }
        tmpsts--;
        }
        //part 2 display the reserved seats
        for (a=0; a<seats; a++) {
            if (strcmp(busSeats[a].fullName, "\0") != 0 )
                printf("%s has reserved seat No. %d \n", busSeats[a].fullName, busSeats[a].seatNumber);
        }
        printf("\n\n");
        // part 3 return to previous status
        at_least_one_swap =1;
        tmpsts = seats;
        while (at_least_one_swap) {
            at_least_one_swap =0;

            for (a=0; a < tmpsts-1; a++) {
                if (busSeats[a].seatNumber > busSeats[a+1].seatNumber) {
                    swapSeats(&busSeats[a], &busSeats[a+1]);
                    at_least_one_swap =1;
                }
            }
        tmpsts--;
        }
    }
    // the choice to display by phone number...
    if (input==2) {
            int j,k;
            char tmptel[11];
            printf("\n\n");
            for (j=0;j<seats;j++) {// check all the bus seats in this loop
                if (strlen(busSeats[j].fullName) > 2) {

                    for (k=0;k<10;k++) {// this loop is for tel number
                        tmptel[k] = busSeats[j].tel[k] + '0';
                    }
                    printf("Seat no. %d has been reserved by %s\n",busSeats[j].seatNumber,busSeats[j].fullName);
                }
            }
            printf("\n");
        }
}

/*This function is called when the user decides to close the program.
It convert the array just as the above, creates the linked list,fills it from the last
element to the first, opens the .txt file and puts the linked list data from the first to the last in it...*/
void saveData () {
    int a,b,j,k,l;
    int tmpsts = seats;
    int at_least_one_swap = 1;

    //part 1 redirect the seats according the name just as before.....
    while (at_least_one_swap) {
        at_least_one_swap =0;
        for (a=0; a < tmpsts-1; a++) {
            if (strcmp(busSeats[a].fullName,busSeats[a+1].fullName)> 0) {
                swapSeats(&busSeats[a], &busSeats[a+1]);
                at_least_one_swap =1;
            }
        }
        tmpsts--;
    }

    //part 2 create the linked list and fill it
    RESERVEDSEATS *record, *tmp, *start=NULL;
    //below we calculate the free seats from the beginning
    //this will be used for then loop, to fill the linked list
    freeSeats=0;
    for (k=0;k<seats;k++) {
        if (strlen(busSeats[k].fullName)> 2)
            freeSeats++;
    }
    //we create the linked list below by adding from the last name of the array to the first all in the linked list
    //and we pass the head/start from the last item to the first one...
    l = seats - freeSeats;//for the loop below
    for (j=seats;j>l;j--){
        record = (RESERVEDSEATS *) malloc(sizeof(RESERVEDSEATS));
        record->next = NULL;
        strcpy(record->fullName, busSeats[j-1].fullName);
        record->seatNumber = busSeats[j-1].seatNumber;
        for (b=0;b<10;b++)
            record->tel[b] = busSeats[j-1].tel[b];
        if (start == NULL) {
            start = record;
        }
        else {
            record->next = start;
            start = record;
        }
    }

    //part 3 - save the data to the bus.txt file
    FILE *myFile = fopen("bus.txt", "w");// open the file for writing
    printf("\nSaving Data to bus.txt File\n");
    fprintf(myFile, "%s %d\n",busNumber, seats);
    tmp = start;//set to the HEAD
    //while there is no finish line, write any record to the txt file.
    while (tmp!=NULL) {
        fprintf(myFile, "%s %d %hu%hu%hu%hu%hu%hu%hu%hu%hu%hu\n", tmp->fullName, tmp->seatNumber, tmp->tel[0],tmp->tel[1],tmp->tel[2],tmp->tel[3],tmp->tel[4],tmp->tel[5],tmp->tel[6],tmp->tel[7],tmp->tel[8],tmp->tel[9]);
        tmp = tmp->next;// go to the next linked list item...
    }
    fclose(myFile);
}


int main(){
    int k;
    seats = fileHandler();// open, collect data and calculate the seats
    do {
        k = options();//call for the options menu
        if (k == 1) {
            freeSeats = displayFreeSeats(seats);
        } else if (k==2) {
            seatReserve();
        } else if (k==3) {
            reservationCheck();
        } else if (k==4) {
            cancelReservation();
        } else if (k==5) {
            displayReservedSeats();
        } else if (k==0) {
            saveData();
            printf("\n\nExiting program.\n\n");
        }
    } while (k!=0);

    return 0;
}


