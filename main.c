#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct Club {
	    char clubName[20];
        int budget;
        char transferList[5][2][20];
	} clubs[]; 

<<<<<<< Updated upstream
struct Player {

};

struct Agent {
    char agentName[20];
    Player playerArray[];
    dasdasdasdas;
    // aaaaaa   try      

};
struct Scout {

};

=======
>>>>>>> Stashed changes
// Let us create a global variable to change it in threads
int g = 0;
int budgetLimit[] = {10000000, 2000000, 3000000, 4000000, 5000000};

struct Club budgetGenerator();
struct Club transferListGenerator();

int main()
{

    srand(time(NULL));

    // name initialization
    strcpy(clubs[0].clubName , "ClubA");
    strcpy(clubs[1].clubName , "ClubB");
    strcpy(clubs[2].clubName , "ClubC");
    strcpy(clubs[3].clubName , "ClubD");
    strcpy(clubs[4].clubName , "ClubE");
    

   // nested methods to generate and assign random budgets and transfer lists
   for(int i = 0; i < 5; i++){
       clubs[i]= budgetGenerator(transferListGenerator(clubs[i]));
   }

   for(int i = 0; i < 5; i++){
       printf("%d\n", clubs[i].budget);
   }

   for(int j = 0; j < 5; j++){
       printf("Transfer list of club %s with budget €%d:\n", clubs[j].clubName, clubs[j].budget);
       for(int i = 0; i < 5; i++){
           
           printf("%s: %s\n", clubs[j].transferList[i][0], clubs[j].transferList[i][1]);

       }
   }

   
    return 0;
}

struct Club budgetGenerator(struct Club s){
   
   int budgetLimit[] = {10000000, 20000000, 30000000, 40000000, 50000000};
   int length = sizeof(budgetLimit)/sizeof(int);
   
   int r = rand()%(length);
   s.budget = budgetLimit[r];
   return s;
 
}

struct Club transferListGenerator(struct Club s) {
    
    char agents [4][20] = {"Agent1", "Agent2", "Agent3", "Agent4"};
    char positions [4][20] = {"Forward", "Midfielder", "Defender","Goalkeeper"};

    int length = 4;
/*
    printf("%s", agents[0]);
    printf("%s", agents[1]);
    printf("%s", agents[2]);
    printf("%s", agents[3]);
    */
    
    for(int i = 0; i < 5; i++){
        int randAgents = rand()%(length);
        int randPositions = rand()%(length);
        printf("%d  %d", randAgents, randPositions);

        strcpy(s.transferList[i][0], agents[randAgents]);
        strcpy(s.transferList[i][1], positions[randPositions]);
    }
    return s;

}
