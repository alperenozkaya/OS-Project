#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct Club {
	    char clubName[20];
        int budget;
        char playerNames[5][20];
	} clubA, clubB, clubC, clubD, ClubE; 

// Let us create a global variable to change it in threads
int g = 0;
int budgetLimit[] = {10000000, 2000000, 3000000, 4000000, 5000000};

int main()
{
    
    strcpy(club1.clubName, "clubA");
    club1.budget = 10000000;
    //club1.playerNames = {"Player1", "Player2", "Player3", "Player4", "Player5"};
    
    clubA.playerNames[0] = "Player";
    
    strcpy(club1.playerNames[0], "Player1");
    strcpy(club1.playerNames[1], "Player2");
    strcpy(club1.playerNames[2], "Player3");
    strcpy(club1.playerNames[3], "Player4");
    strcpy(club1.playerNames[4], "Player5");

    strcpy(club2.clubName, "clubB");
    club2.budget = 10000000;
    //club2.playerNames = {"Player1", "Player2", "Player3", "Player4", "Player5"};
    strcpy(club2.playerNames[0], "Player1");
    strcpy(club2.playerNames[1], "Player2");
    strcpy(club2.playerNames[2], "Player3");
    strcpy(club2.playerNames[3], "Player4");
    strcpy(club2.playerNames[4], "Player5");
    
    strcpy(club3.clubName, "clubC");
    club3.budget = 10000000;
    //club3.playerNames = {"Player1", "Player2", "Player3", "Player4", "Player5"};
    strcpy(club3.playerNames[0], "Player1");
    strcpy(club3.playerNames[1], "Player2");
    strcpy(club3.playerNames[2], "Player3");
    strcpy(club3.playerNames[3], "Player4");
    strcpy(club3.playerNames[4], "Player5");

    printf("name of club1 is: %s\n", club1.clubName);
    printf("name of club2 is: %s\n", club2.clubName);
    printf("name of club3 is: %s\n", club3.clubName);

    return 0;
}