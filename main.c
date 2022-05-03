#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct Club {
	    char clubName[20];
        int budget;
        char transferList[5][2][20];
        // Player plyerTrnsfrDone()
	} clubs[5]; 


struct Player {
    char positionName[20];
    int transferCost;

};

struct Agent {
    
    char agentName[20];
    struct Player* managementList;


    // ScoutCostUpdate()  ScoutAddNewPlayer
    

} Agent1;


// there is no need for scout struct
struct Scout {

};


// Let us create a global variable to change it in threads
int g = 0;
int budgetLimit[] = {10000000, 2000000, 3000000, 4000000, 5000000};

struct Club budgetGenerator();
struct Club transferListGenerator();
struct Player * resizeArray();
void incrementInt();
struct Player* initializePlayers();


int main()
{
    srand(time(NULL));

    Agent1.managementList = (struct Player*) malloc(7 *sizeof(struct Player));
   
    Agent1.managementList = initializePlayers(Agent1.managementList);

    for(int i = 0; i < sizeof(Agent1.managementList) - 1; i++){
        printf("Position: %s   TransferCost %d\n", Agent1.managementList[i].positionName, Agent1.managementList[i].transferCost);
    }

    printf(" The size of: %d\n", sizeof(Agent1.managementList));
    
    resizeArray(Agent1.managementList);
    
    printf(" The size of: %d\n", sizeof(Agent1.managementList));

    
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

    free(Agent1.managementList);
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

struct Player * resizeArray(struct Player * a){
    a = malloc(10 * sizeof(struct Player));

    if(a == NULL) {}     // malloc() was unable to allocate the memory, handle the
                     // error and DO NOT use this pointer anymore

    

    // suppose 10 ints aren't no more enough:
    a = realloc(a, 20 * sizeof(struct Player));

    if(a == NULL) {}     // same thing as before

    // here you have 20 ints, the previous 10 are still there
    //a[18] = a[4]

    // don't forget to free the memory when you have finished:
    //free(a);
    return a;
    
    
   
}

struct Player scoutCostUpdate(struct Player * mngList){
    
    int costChange[] = {-500000, 0, 1000000};
    int length = sizeof(costChange)/sizeof(int);

    int mngListLen = sizeof(mngList)/sizeof(struct Player);


    for(int i = 0; i < sizeof(mngList) - 1; i++ ){
        if(mngList[i].transferCost != 0 ) {
            int r = rand()%(length);
            mngList[i].transferCost += costChange[r];
            if(mngList[i].transferCost <= 3000000)
                mngList[i].transferCost += 500000;
            else if( mngList[i].transferCost >= 22000000)
                mngList[i].transferCost -= 1000000;
           
        }   
    }
    return *mngList;   

}

struct Player* initializePlayers(struct Player * mngList){
    
    int baseCost = 1000000;
    char positions [4][20] = {"Forward", "Midfielder", "Defender","Goalkeeper"};

    int length = 4;


    int mngListLen = sizeof(mngList)/sizeof(struct Player);


    for(int i = 0; i < sizeof(mngList) - 1; i++ ){
        
            int transferCost = baseCost * ((rand()%16) + 4);
            mngList[i].transferCost = transferCost;
            
            int randPositions = rand()%(length);
            strcpy(mngList[i].positionName, positions[randPositions]);
                
        }
    return mngList;   

}
