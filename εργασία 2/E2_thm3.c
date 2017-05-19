#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//structure prototypes.
typedef struct  {
    char name[18];
    unsigned short int score;
    char id;
}PLAYER;

typedef struct {
    char color;
    char shape;
    unsigned short int number;
    char texture;
    unsigned short int flag;
}CARD;

//function prototypes
int createRandomNumber();// creates Random Numbers
int createPlayers();// Collects the users data and creates Players
void createCards();//
void createTableOfCards();//
void displayTableOfCards();//
int compareData();//
int collectAndCompareData();//
void printScore();//

// variable declaration
CARD cards[81];
CARD playedCards[3][4];
PLAYER *player;// for the dynamic array of the players


/* the function below creates the players in a dynamic array structure*/
int createPlayers () {
    int numberOfPlayers;
    int a;
    char tmpName[18];
    char tmpID;
    int k;//for the loop

    do {
        printf("\nHow many players are playing ? >> ");
        scanf("%d", &numberOfPlayers);
        if (numberOfPlayers> 5)
            printf("\nThere can't be more than 5 players....\nPlease try again!\n");
        else if (numberOfPlayers<1) {
            printf("Please for Gods shake enter a valid number....");
        }
    }while (numberOfPlayers > 5 || numberOfPlayers<1);

    player = (PLAYER *)malloc(sizeof(PLAYER)* numberOfPlayers);

    for (a=0;a<numberOfPlayers;a++) {
        printf("Please enter Player's No %d Name: ", a+1);
        scanf("%s",tmpName);
        strcpy(player[a].name, tmpName);
        tmpID = tmpName[0];
        player[a].id = tmpID;
        player[a].score = 0;
        printf("Players No. %d Character ID is: %c\n",a+1,player[a].id);
    }
    printf("\nPlayers are: \n");
    for (k=0;k < numberOfPlayers; k++) {
         printf("%d: %s\n",k+1, player[k].name);
    }
    printf("\n");
    return numberOfPlayers;
}

/*The function below creates the 81 cards */
void createCards () {
    int a,b,c,d;//for the loop
    char tmpcolor[] = {'r','g','b'};//temporary for the loop
    char tmpshape[] = {'c','t','r'};// same
    unsigned short int tmpNumber[] = {1,2,3};//same
    char tmpTexture[] = {'b','h','e'}; // same
    // to fill the cards I am going to use 3x3x3x3 loop...
    printf("\nCreating cards... \n\n");
    int j=0;
    for (a=0;a<3;a++) {
        for (b=0;b<3;b++) {
            for (c=0;c<3;c++) {
                for (d=0;d<3;d++) {
                    cards[j].color = tmpcolor[a];
                    cards[j].shape = tmpshape[b];
                    cards[j].number = tmpNumber[c];
                    cards[j].texture = tmpTexture[d];
                    cards[j].flag = 0;
                    j++;
                }
            }
        }
    }
    printf("Cards Created!\n\n");

}
//this function creates the random number...
int createRandomNumber(int Min, int Max) {

    double rnd= (double)rand()/((double)RAND_MAX+1);
    return   (int)(rnd*(Max-Min+1))+Min;
}

/*The function below creates the 12 cards */
void createTableOfCards () {
    int num;// for the random number
    int a=0;
    int b;
    char tmpColor;
    char tmpShape;
    unsigned short int tmpNumber;
    char tmpTexture;
    while (a < 3) {
        b=0;
        while (b < 4){
            num = createRandomNumber(0,80);
            if (cards[num].flag == 0) {
                cards[num].flag = 1;
                tmpColor = cards[num].color;
                playedCards[a][b].color = tmpColor;
                tmpShape = cards[num].shape;
                playedCards[a][b].shape = tmpShape;
                tmpNumber = cards[num].number;
                playedCards[a][b].number = tmpNumber;
                tmpTexture = cards[num].texture;
                playedCards[a][b].texture = tmpTexture;
                b++;
            }
        }
        a++;
    }
}

/*The function below displays the 12 cards in a 3x4 table */
void displayTableOfCards (){
    int j,k;
    for (j=0;j<3;j++) {
        for (k=0;k<4;k++) {
            printf("[%c%c%hu%c]\t", playedCards[j][k].color, playedCards[j][k].shape, playedCards[j][k].number, playedCards[j][k].texture);
        }
        printf("\n\n");
    }
}

/*This function is used by the one below to check if the users input is correct.
If yes then calculates the score and manipulates the value integer accordingly */
int compareData (int a, int b, int c, int d, int e, int f, int forPlayer) {
    int value;//will be returned after evaluation.
    int tmpscore=0;//is used for calculating the ....
    int tmpscore2=0;
    /*To compare the data all I have to do is see if 3 out of the 4 parts of each card are the same
    OR if 1 out of the four parts of each card is the same but at the same time there must not be
    a same part twice in the two cards */
    if (playedCards[a][b].color == playedCards[c][d].color) {
        if (playedCards[a][b].color == playedCards[e][f].color)
            tmpscore++;
    }
    if(playedCards[a][b].shape == playedCards[c][d].shape) {
        if (playedCards[a][b].shape == playedCards[e][f].shape)
            tmpscore++;
    }
    if (playedCards[a][b].number == playedCards[c][d].number) {
        if (playedCards[a][b].number== playedCards[e][f].number)
            tmpscore++;
    }
    if (playedCards[a][b].texture == playedCards[c][d].texture) {
        if (playedCards[a][b].texture == playedCards[e][f].texture)
            tmpscore++;
    }
    // the tmpscore2 is used to check if in a set has two of a kind. It is important in case we have 1 of the same
    //and all the others are different
    if (((playedCards[a][b].color == playedCards[c][d].color) && (playedCards[a][b].color != playedCards[e][f].color)) || ((playedCards[a][b].color != playedCards[c][d].color) && (playedCards[a][b].color == playedCards[e][f].color))) {
        tmpscore2++;

    }
    if (((playedCards[a][b].shape == playedCards[c][d].shape) && (playedCards[a][b].shape != playedCards[e][f].shape)) || ((playedCards[a][b].shape != playedCards[c][d].shape) && (playedCards[a][b].shape == playedCards[e][f].shape))) {
        tmpscore2++;

    }
    if (((playedCards[a][b].number == playedCards[c][d].number) && (playedCards[a][b].number != playedCards[e][f].number)) || ((playedCards[a][b].number != playedCards[c][d].number) && (playedCards[a][b].number == playedCards[e][f].number))) {
        tmpscore2++;

    }
    if (((playedCards[a][b].texture == playedCards[c][d].texture) && (playedCards[a][b].texture != playedCards[e][f].texture)) || ((playedCards[a][b].texture != playedCards[c][d].texture) && (playedCards[a][b].texture == playedCards[e][f].texture))) {
        tmpscore2++;

    }

    // to have a set, the tmpscore must be either 1 (if all are different), or 3
    if ((tmpscore == 3) || (tmpscore == 1) && (tmpscore2==0)) {
        printf("Correct!!! You have found a SET.");
        printf("%s collects 2 points.\n\n",player[forPlayer].name);
        player[forPlayer].score = player[forPlayer].score + 2;
        value = 1; // draw cards again
    } else if ((tmpscore == 0) || (tmpscore ==  2) || (tmpscore == 4) || (tmpscore2>0)) {
        printf("Wrong.... Player %s looses 1 point...\n", player[forPlayer].name);
        player[forPlayer].score = player[forPlayer].score - 1;
        if (player[forPlayer].score > 1000)// because we have an unsigned int...
            player[forPlayer].score = 0;
        value = 2;// don't draw cards again...
    }
    return value;
}

/*The function below collects the users data and compares them by using the function above.
Additionally  checks if we have a winner*/
int collectAndCompareData (int numOfPlayers) {
    int value;//If 0 to Exit the program, If 2 to recycle the function, If 1 proceed to next game...
    char ID = 'a';
    int a=0;// for the array struct
    int b,c;//for the first card
    int d,e;// for the second card
    int f,g;// for the third card
    int k;// for the evaluation of the score loop

    printf("\n\nIf you want to exit the program Please enter 0.\nIf you want to draw cards again enter something irrelevant Or Else \n");
    printf("If a player has found a SET, please enter ID:");
    scanf(" %c",&ID);

    //the choice is 0  so exiting
    if (ID == '0') {
        printf("\nThank you for playing...\n\nExiting Program...\n\n");
        value = 0;
        a = numOfPlayers + 1;
    }
    //trying to locate the player, then collect his choice and then calculate his score...
    while (a<numOfPlayers) {
        if (player[a].id == ID) {
            printf("\n%s believes has found a SET...\nPlease enter below the 3 choices for evaluation.\n",player[a].name);
            printf("Please enter Line and Row with a space between: ");
            scanf("%d %d",&b,&c);
            if (1<b<3 && 1<c<4) {
                printf("\nPlease enter Line and Row with a space between: ");
                scanf("%d %d",&d,&e);
                if (1<d<3 && 1<e<4) {
                    printf("\nPlease enter Line and Row with a space between: ");
                    scanf("%d %d",&f,&g);
                    if (1<f<3 && 1<g<4) {
                        value = compareData(b,c,d,e,f,g,a);
                    } else {
                        printf("Invalid Input. Try again...\n\n");
                        value = 2;
                    }
                } else {
                    printf("Invalid Input. Try again...\n\n");
                    value = 2;
                }
            } else {
                printf("Invalid Input. Try again...\n\n");
                value = 2;
            }
            //below we check for a winner
            for (k=0;k<numOfPlayers;k++){
                if (player[k].score>=10) {
                    printf("%s is the Winner!!!",player[k].name);
                    value =0;
                }
            }
            a=numOfPlayers+1;
        } else {//player not found, going for an other loop again
            a++;
        }
    }
    //if the user has entered a wrong choice or an irrelevant number
    if (a==numOfPlayers) {
        printf("Irrelevant character was entered. Drawing cards again.\n\n");
        value = 1;
    }
    return value;
}

/* prints the score.*/
void printScore (int players) {
    int value;
    int j;//loop
    printf("Score is: \n");
    for (j=0;j<players;j++){
        printf("%s: %hu\n",player[j].name,player[j].score);
    }
    printf("\n\n");
}

int main()
{
    int players;
    int answer = 1;//if this value is 2 the createTableOfCards function will be omitted
    players = createPlayers();
    createCards();
    while (answer!=0) {
        srand(time(NULL));
        if (answer!=2)// draw cards again if not 2
            createTableOfCards();//draw cards
        displayTableOfCards();//display cards
        answer = collectAndCompareData(players);//collect and compare the selection
        printScore(players);//display the score
    }

    return 0;
}
