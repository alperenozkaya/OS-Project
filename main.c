#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>



pthread_mutex_t lock;
sem_t sem;



struct Club
{
    char clubName[20];
    int budget;
    char transferList[5][2][20];
    // Player plyerTrnsfrDone()
} clubs[5];

struct Player
{
    char positionName[20];
    int transferCost;
};

struct Agent
{

    char agentName[20];
    struct Player *managementList;
    int playerNumber;

    // ScoutCostUpdate()  ScoutAddNewPlayer

} Agents[4];

// Let us create a global variable to change it in threads
int g = 0;
int budgetLimit[] = {10000000, 2000000, 3000000, 4000000, 5000000};

struct Club budgetGenerator();
struct Club transferListGenerator();
struct Player *resizeArray();
void incrementInt();
struct Player *initializePlayers();
struct Player * scoutCostUpdate();
struct Agent addNewPlayers();
struct Club completeTransfer();
int printSomething();


void* clubThreadLoop1(void* arg){
   
while (1)
{
    sleep(1);
    int counter1 = 0;
    
    
    //printf("I am in");
    clubs[0] = completeTransfer(clubs[0], Agents);   

    for(int i = 0; i < 5; i++) {
        if (strcmp(clubs[3].transferList[i][0], "") == 0)
            counter1++;
    }
    if (counter1 == 5)
        pthread_exit(NULL);    
}
    return NULL;

}

void* clubThreadLoop2(void* arg){
   
while (1)
{
    sleep(1);
    int counter2 = 0;
    
    clubs[1] = completeTransfer(clubs[1], Agents); 

    for(int i = 0; i < 5; i++) {
        if (strcmp(clubs[3].transferList[i][0], "") == 0)
            counter2++;
    }
    if (counter2 == 5)
        pthread_exit(NULL);    
    else if(clubs[3].budget < 3000000){
        printf("Budget of Club-%s is too low to transfer a player", clubs[3].clubName);
        pthread_exit(NULL); 
    }
}
    return NULL;

}

void* clubThreadLoop3(void* arg){
   
while (1)
{
    sleep(1);
    int counter3 = 0;
    
    clubs[2] = completeTransfer(clubs[2], Agents);    

    for(int i = 0; i < 5; i++) {
        if (strcmp(clubs[3].transferList[i][0], "") == 0)
            counter3++;
    }
    if (counter3 == 5)
        pthread_exit(NULL);  
}
    return NULL;

}

void* clubThreadLoop4(void* arg){
   
while (1)
{
    sleep(1);
    int counter4 = 0;
    
    clubs[3] = completeTransfer(clubs[3], Agents);  

     for(int i = 0; i < 5; i++) {
        if (strcmp(clubs[3].transferList[i][0], "") == 0)
            counter4++;
    }
    if (counter4 == 5)
        pthread_exit(NULL);   
}
    return NULL;

}

void* clubThreadLoop5(void* arg){
    int counter5 = 0;
   
while (1)
{
    sleep(1);
    clubs[4] = completeTransfer(clubs[4], Agents);
     

    for(int i = 0; i < 5; i++) {
        if (strcmp(clubs[4].transferList[i][0], "") == 0)
            counter5++;
    }
    if (counter5 == 5)
        pthread_exit(NULL); 


    
      
}
    return NULL;

}

void * scoutThreadLoop(void* arg){

    while (1)
    {
        sleep(1);
        sleep(rand()%5 + 3);
        for(int i = 0; i < 4; i++){
            Agents[i].managementList = scoutCostUpdate(Agents[i].managementList);
        }
        sleep(rand()%2);



        for(int i = 0; i < 4; i++){
            Agents[i]= addNewPlayers(Agents[i]);
        }  

        


        for (int j = 0; j < 5; j++)
        {
            printf("Transfer list of club %s with budget €%d:\n", clubs[j].clubName, clubs[j].budget);
            for (int i = 0; i < 5; i++)
            {

                printf("%s: %s\n", clubs[j].transferList[i][0], clubs[j].transferList[i][1]);
            }
        }


        for (int i = 0; i < Agents[i].playerNumber; i++)
        {
            for (int j = 0; j < Agents[i].playerNumber; j++)
                printf("%d-Position: %s   TransferCost %d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
        }
        printf("\n");  
    }
     
return NULL;
    }
     


int main()
{

    srand(time(NULL));

    // initialize player numbers

    strcpy(Agents[0].agentName, "Agent1");
    Agents[0].playerNumber = 7;
    strcpy(Agents[1].agentName, "Agent2");
    Agents[1].playerNumber = 6;
    strcpy(Agents[2].agentName, "Agent3");
    Agents[2].playerNumber = 6;
    strcpy(Agents[3].agentName, "Agent4");
    Agents[3].playerNumber = 4;

    

    // randomly assign players to agents
    for (int i = 0; i < 4; i++)
    {
        Agents[i].managementList = (struct Player *)malloc(Agents[i].playerNumber * sizeof(struct Player));
        Agents[i].managementList = initializePlayers(Agents[i].managementList);
    }
/*
    for (int i = 0; i < Agents[i].playerNumber; i++)
    {
        for (int j = 0; j < Agents[i].playerNumber; j++)
            printf("%d-Position: %s   TransferCost %d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
    }
    printf("\n");

    // update costs (Scout)
    for (int i = 0; i < Agents[i].playerNumber; i++)
    {
        Agents[i].managementList = scoutCostUpdate(Agents[i].managementList);
    }
    printf("\n");

    for (int i = 0; i < Agents[i].playerNumber; i++)
    {
        for (int j = 0; j < Agents[i].playerNumber; j++)
            printf("%d-Position: %s   TransferCost %d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
    }
    printf("\n");

    */



    // name initialization
    strcpy(clubs[0].clubName, "ClubA");
    strcpy(clubs[1].clubName, "ClubB");
    strcpy(clubs[2].clubName, "ClubC");
    strcpy(clubs[3].clubName, "ClubD");
    strcpy(clubs[4].clubName, "ClubE");

    // nested methods to generate and assign random budgets and transfer lists
    for (int i = 0; i < 5; i++)
    {
        clubs[i] = budgetGenerator(transferListGenerator(clubs[i]));
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", clubs[i].budget);
    }

    for (int j = 0; j < 5; j++)
    {
        printf("Transfer list of club %s with budget €%d:\n", clubs[j].clubName, clubs[j].budget);
        for (int i = 0; i < 5; i++)
        {

            printf("%s: %s\n", clubs[j].transferList[i][0], clubs[j].transferList[i][1]);
        }
    }

    
    for (int i = 0; i < Agents[i].playerNumber; i++)
    {
        for (int j = 0; j < Agents[i].playerNumber; j++)
            printf("%d-Position: %s   TransferCost %d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
    }
    printf("\n");
      


    

   /*
    completeTransfer(clubs[0], Agents);

    */

    // Create threads (5 clubs)  end if the transfer list is completed or the club is out of budget
    // if out of budget - wait for a period and negotiate second time

    // scout thread
    sem_init(&sem, 0, 2); // Semaphore to prevent more than 2 negotiation


   
    pthread_t newthread_1;
    pthread_t newthread_2;
    pthread_t newthread_3;
    pthread_t newthread_4;
    pthread_t newthread_5;

    
    
    
    pthread_t scoutThread;


    pthread_create(&newthread_1, NULL,clubThreadLoop1, NULL);
    pthread_create(&newthread_2, NULL,clubThreadLoop2, NULL);
    pthread_create(&newthread_3, NULL,clubThreadLoop3, NULL);
    pthread_create(&newthread_4, NULL,clubThreadLoop4, NULL);
    pthread_create(&newthread_5, NULL,clubThreadLoop5, NULL);

    pthread_create(&scoutThread, NULL, scoutThreadLoop, NULL);


    pthread_join(newthread_1, NULL);
    pthread_join(newthread_2, NULL);
    pthread_join(newthread_3, NULL);
    pthread_join(newthread_4, NULL);
    pthread_join(newthread_5, NULL);
    
    pthread_join(scoutThread, NULL);




  
    return 0;
}

struct Club budgetGenerator(struct Club s)
{

    int budgetLimit[] = {10000000, 20000000, 30000000, 40000000, 50000000};
    int length = sizeof(budgetLimit) / sizeof(int);

    int r = rand() % (length);
    s.budget = budgetLimit[r];
    return s;
}

struct Club transferListGenerator(struct Club s)
{

    char agents[4][20] = {"Agent1", "Agent2", "Agent3", "Agent4"};
    char positions[4][20] = {"Forward", "Midfielder", "Defender", "Goalkeeper"};

    int length = 4;
    /*
        printf("%s", agents[0]);
        printf("%s", agents[1]);
        printf("%s", agents[2]);
        printf("%s", agents[3]);
        */

    for (int i = 0; i < 5; i++)
    {
        int randAgents = rand() % (length);
        int randPositions = rand() % (length);
        printf("%d  %d", randAgents, randPositions);

        strcpy(s.transferList[i][0], agents[randAgents]);
        strcpy(s.transferList[i][1], positions[randPositions]);
    }
    return s;
}

struct Player * scoutCostUpdate(struct Player * mngList)
{

    int costChange[] = {-500000, 0, 1000000};
    int length = sizeof(costChange) / sizeof(int);

    int mngListLen = sizeof(mngList) / sizeof(struct Player);

    for (int i = 0; i < sizeof(mngList) - 1; i++)
    {
        if (mngList[i].transferCost != 0)
        {
            int r = rand() % (length);
            mngList[i].transferCost += costChange[r];
            if (mngList[i].transferCost <= 3000000)
                mngList[i].transferCost += 500000;
            else if (mngList[i].transferCost >= 22000000)
                mngList[i].transferCost -= 1000000;
        }
    }
    return mngList;
}

struct Player *initializePlayers(struct Player *mngList)
{

    int baseCost = 1000000;
    char positions[4][20] = {"Forward", "Midfielder", "Defender", "Goalkeeper"};

    int length = 4;
    int mngListLen = sizeof(mngList) / sizeof(struct Player);

    for (int i = 0; i < sizeof(mngList) - 1; i++)
    {

        int transferCost = baseCost * ((rand() % 16) + 4);
        mngList[i].transferCost = transferCost;

        int randPositions = rand() % (length);
        strcpy(mngList[i].positionName, positions[randPositions]);
    }
    return mngList;
}

struct Agent addNewPlayers(struct Agent agent)
{

    int baseCost = 1000000;
    char positions[4][20] = {"Forward", "Midfielder", "Defender", "Goalkeeper"};

    int length = 4;
    int isEnough = 0;

    int numPlayers = 0;

    int mngListLen = sizeof(agent.managementList) / sizeof(struct Player);

    for (int i = 0; i < agent.playerNumber; i++)
    {

        if (agent.managementList[i].transferCost == 0 || agent.managementList[i].positionName == "")
        {
        label:
            printf("\n");

            int transferCost = baseCost * ((rand() % 16) + 4);
            agent.managementList[i].transferCost = transferCost;

            int randPositions = rand() % (length);
            strcpy(agent.managementList[i].positionName, positions[randPositions]);
            isEnough = 1;
            break;
        }

        if (isEnough == 0)
        { // list is full
            i = agent.playerNumber;
            agent.playerNumber++;
            agent.managementList = (struct Player *)realloc(agent.managementList, agent.playerNumber * sizeof(struct Player));
            goto label;
        }
    }
    // printf("%d", agent.playerNumber);
    return agent;
}



struct Club completeTransfer(struct Club c, struct Agent agents[]) {

    //printf("***************\n");

   
     
    char wantedAgentName[20];
    char wantedPlayerPosition[20];
    int minTransferCost = 100000000;
    int agentPlayerIndex;
    int agentIndex;
    
    int clubTransferListIndex;

    int count = 0;



    
    for(int i = 0; i < 5; i++ ){
        if(strcmp(c.transferList[i][0], "") != 0){
            clubTransferListIndex = i;
            strcpy(wantedAgentName, c.transferList[i][0]);
            strcpy(wantedPlayerPosition, c.transferList[i][1]);
            //printf("clubTransferListINdex: %d and agentname %s\n", clubTransferListIndex, c.transferList[clubTransferListIndex][0]);
            count++;
            break;
        }
    }  

    //printf("count: %d\n", count);
    

   // printf("clubTransferListINdex: %d and agentname %s\n", clubTransferListIndex, c.transferList[clubTransferListIndex][0]);

  
    pthread_mutex_lock(&lock);
    int transferDone;
    for(int x = 0; x < 4; x++){
        //printf("\n1\n");
        if(strcmp(wantedAgentName, Agents[x].agentName) == 0) {
            sem_wait(&sem);
           // printf("2\n");
            for(int y = 0; y < Agents[x].playerNumber; y++){
               // printf("3\n");
                
                
                if(strcmp(Agents[x].managementList[y].positionName, wantedPlayerPosition) == 0 && Agents[x].managementList[y].transferCost < minTransferCost && c.budget > Agents[x].managementList[y].transferCost) {
                   // printf("4\n");
                    minTransferCost = Agents[x].managementList[y].transferCost;
                    agentPlayerIndex = y;
                    agentIndex = x;
                  //  printf("The player index: %d cost: %d  position: %s  agent index: %d\n", agentPlayerIndex, Agents[agentIndex].managementList[agentPlayerIndex].transferCost, Agents[agentIndex].managementList[agentPlayerIndex].positionName, agentIndex);
                    transferDone = 1; 
                    }
                }                          
            }
        } 
        //printf("%d\n", transferDone);
        if(transferDone) {
            c.budget -= Agents[agentIndex].managementList[agentPlayerIndex].transferCost; // update the budget
            strcpy(Agents[agentIndex].managementList[agentPlayerIndex].positionName, "");
            Agents[agentIndex].managementList[agentPlayerIndex].transferCost = 0;
            printf("Transfer is done");
            transferDone = 0;

           
            strcpy(c.transferList[clubTransferListIndex][0], ""); // set the agent name to ""
            strcpy(c.transferList[clubTransferListIndex][1], ""); // set the position of wanted player to ""
           
        }

        pthread_mutex_unlock(&lock);
        sem_post(&sem);
        

        return c;
    }



