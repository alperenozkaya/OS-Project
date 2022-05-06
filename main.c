#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>


pthread_mutex_t lock; // mutex used in completeTransfer function
sem_t sem; // semaphore used in completeTransfer

// seperate semaphores which stop club threads to negotiate
sem_t scoutUpdate1;
sem_t scoutUpdate2;
sem_t scoutUpdate3;
sem_t scoutUpdate4;
sem_t scoutUpdate5;


// structs 
struct Club
{
    char clubName[20];
    int budget;
    char transferList[5][2][20];  // [players][0=agentName 1=position][str length]
    
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

} Agents[4];

// Let us create a global variable to change it in threads
int g = 0;
int budgetLimit[] = {10000000, 2000000, 3000000, 4000000, 5000000};

// function prototypes
struct Club budgetGenerator();
struct Club transferListGenerator();
struct Player *resizeArray();
void incrementInt();
struct Player *initializePlayers();
struct Player * scoutCostUpdate();
struct Agent addNewPlayers();
struct Club completeTransfer();

void* clubThreadLoop1(void* arg){
   
    while (1)
    {
        sleep(1);
        int counter1 = 0; // counter to check if the transfer list is completed

        sem_wait(&scoutUpdate1);
        clubs[0] = completeTransfer(clubs[0], Agents);
        sem_post(&scoutUpdate1);

        for(int i = 0; i < 5; i++) {
            if (strcmp(clubs[0].transferList[i][0], "") == 0)
                counter1++;
        }
        if (counter1 == 5) {
            printf("Transfer list of Club%s is completed\n", clubs[0].clubName);
            pthread_exit(NULL);   

        }
        else if(clubs[0].budget < 3000000){
            printf("Budget of Club-%s is too low to transfer a player\n", clubs[0].clubName);
            pthread_exit(NULL); 
        }
    }
        return NULL;

}

void* clubThreadLoop2(void* arg){
   
    while (1)
    {
        sleep(1);
        int counter2 = 0; // counter to check if the transfer list is completed
        sem_wait(&scoutUpdate2);
        
        clubs[1] = completeTransfer(clubs[1], Agents); 
        sem_post(&scoutUpdate2);

        for(int i = 0; i < 5; i++) {
            if (strcmp(clubs[3].transferList[i][0], "") == 0)
                counter2++;
        }
        if (counter2 == 5) {
            printf("Transfer list of Club%s is completed\n", clubs[1].clubName);
            pthread_exit(NULL);   
        }  
        else if(clubs[1].budget < 3000000){
            printf("Budget of Club-%s is too low to transfer a player\n", clubs[1].clubName);
            pthread_exit(NULL); 
        }
    }
        return NULL;

}

void* clubThreadLoop3(void* arg){
   
    while (1)
    {
        sleep(1);
        int counter3 = 0; // counter to check if the transfer list is completed
        
        sem_wait(&scoutUpdate3);
        clubs[2] = completeTransfer(clubs[2], Agents); 
        sem_post(&scoutUpdate3);

        for(int i = 0; i < 5; i++) {
            if (strcmp(clubs[2].transferList[i][0], "") == 0)
                counter3++;
        }
        if (counter3 == 5) {
            printf("Transfer list of Club%s is completed\n", clubs[2].clubName);
            pthread_exit(NULL);   

        }
        else if(clubs[2].budget < 3000000){
            printf("Budget of Club-%s is too low to transfer a player\n", clubs[2].clubName);
            pthread_exit(NULL); 
        }
    }
        return NULL;

}

void* clubThreadLoop4(void* arg){
   
    while (1)
    {
        sleep(1);
        int counter4 = 0; // counter to check if the transfer list is completed
        
        sem_wait(&scoutUpdate4);
        clubs[3] = completeTransfer(clubs[3], Agents); 
        sem_post(&scoutUpdate4);

        for(int i = 0; i < 5; i++) {
            if (strcmp(clubs[3].transferList[i][0], "") == 0)
                counter4++;
        }
        if (counter4 == 5) {
            printf("Transfer list of Club%s is completed\n", clubs[3].clubName);
            pthread_exit(NULL);   

        }
        else if(clubs[3].budget < 3000000){
            printf("Budget of Club-%s is too low to transfer a player\n", clubs[3].clubName);
            pthread_exit(NULL); 
        }
            
    }
        return NULL;

}

void* clubThreadLoop5(void* arg){
    
    while (1)
    {
        int counter5 = 0; // counter to check if the transfer list is completed
        sleep(1);
    
        sem_wait(&scoutUpdate5);
        clubs[4] = completeTransfer(clubs[4], Agents); 
        sem_post(&scoutUpdate5);
        
        for(int i = 0; i < 5; i++) {
            if (strcmp(clubs[4].transferList[i][0], "") == 0)
                counter5++;
        }
        if (counter5 == 5) {
            printf("Transfer list of Club%s is completed\n", clubs[4].clubName);
            pthread_exit(NULL);  
        }
        else if(clubs[4].budget < 3000000){
            printf("Budget of Club-%s is too low to transfer a player\n", clubs[4].clubName);
            pthread_exit(NULL); 
        }
            
    }
        return NULL;

}

void * scoutThreadLoop(void* arg){
    while (1)
    { 
        int randNumUpdateOrAdd = rand()%100; // let scout randomly choose to update the costs or add new players
        // update case
        if(randNumUpdateOrAdd < 70) {
            // semaphore for club threads to prevent transfer neg.
            sem_wait(&scoutUpdate1);
            sem_wait(&scoutUpdate2);
            sem_wait(&scoutUpdate3);
            sem_wait(&scoutUpdate4);
            sem_wait(&scoutUpdate5);
            
            for(int i = 0; i < 4; i++){
                Agents[i].managementList = scoutCostUpdate(Agents[i].managementList);
            }
            printf("The cost of all players are updated\nUpdated List is:\n");

            for (int i = 0; i < Agents[i].playerNumber; i++){
                for (int j = 0; j < Agents[i].playerNumber; j++)
                    printf("%d-Position: %s TransferCost: $%d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
            }
            // signal for club threads 
            sem_post(&scoutUpdate1);
            sem_post(&scoutUpdate2);
            sem_post(&scoutUpdate3);
            sem_post(&scoutUpdate4);
            sem_post(&scoutUpdate5);
            sleep(rand()%4 + 2); // sleep for a while
        }
        // add players case
        else {
            // semaphore for club threads to prevent transfer neg.
            sem_wait(&scoutUpdate1);
            sem_wait(&scoutUpdate2);
            sem_wait(&scoutUpdate3);
            sem_wait(&scoutUpdate4);
            sem_wait(&scoutUpdate5);
            

        for(int i = 0; i < 4; i++){
            Agents[i]= addNewPlayers(Agents[i]);
        }  
        printf("New players are added!\nUpdated List is:\n");
        
        for (int i = 0; i < Agents[i].playerNumber; i++)
        {
            for (int j = 0; j < Agents[i].playerNumber; j++)
                printf("%d-Position: %s  TransferCost: $%d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
        }
         // signal for club threads 
            sem_post(&scoutUpdate1);
            sem_post(&scoutUpdate2);
            sem_post(&scoutUpdate3);
            sem_post(&scoutUpdate4);
            sem_post(&scoutUpdate5);
            sleep(rand()%4 + 2); // sleep for a while
        }
        // print the transfer lists in a random interval
        int randTransferLists = rand()%100;
        // print the current transfer lists
        if(randTransferLists < 100) {
            sleep(1); 
            printf("\nCurrent transfer lists:\n");
            for (int j = 0; j < 5; j++) {
            printf("Transfer list of club %s with budget €%d:\n", clubs[j].clubName, clubs[j].budget);
            for (int i = 0; i < 5; i++)
                printf("%s: %s\n", clubs[j].transferList[i][0], clubs[j].transferList[i][1]);    
        }
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

    // name initialization
    strcpy(clubs[0].clubName, "ClubA");
    strcpy(clubs[1].clubName, "ClubB");
    strcpy(clubs[2].clubName, "ClubC");
    strcpy(clubs[3].clubName, "ClubD");
    strcpy(clubs[4].clubName, "ClubE");

    // nested functions to generate and assign random budgets and transfer lists
    for (int i = 0; i < 5; i++)
    {
        clubs[i] = budgetGenerator(transferListGenerator(clubs[i]));
    }
    
    //print inital values
    printf("****Initial transfer lists and players****\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", clubs[i].budget);
    }

    for (int j = 0; j < 5; j++)
    {
        printf("Transfer list of club %s with budget $%d:\n", clubs[j].clubName, clubs[j].budget);
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
    // semaphore value is initialized as 2  
    sem_init(&sem, 0, 2); // Semaphore to prevent more than 2 negotiation
    
    // semaphore for clubs to prevent from transfer negotiation
    sem_init(&scoutUpdate1, 0, 1);
    sem_init(&scoutUpdate2, 0, 1);
    sem_init(&scoutUpdate3, 0, 1);
    sem_init(&scoutUpdate4, 0, 1);
    sem_init(&scoutUpdate5, 0, 1);
    // threads for each seperate clubs
    pthread_t newthread_1;
    pthread_t newthread_2;
    pthread_t newthread_3;
    pthread_t newthread_4;
    pthread_t newthread_5;
    // thread for scout
    pthread_t scoutThread;

    // threads are created
    pthread_create(&newthread_1, NULL,clubThreadLoop1, NULL);
    pthread_create(&newthread_2, NULL,clubThreadLoop2, NULL);
    pthread_create(&newthread_3, NULL,clubThreadLoop3, NULL);
    pthread_create(&newthread_4, NULL,clubThreadLoop4, NULL);
    pthread_create(&newthread_5, NULL,clubThreadLoop5, NULL);

    pthread_create(&scoutThread, NULL, scoutThreadLoop, NULL);

    // waiting threads to return
    pthread_join(newthread_1, NULL);
    pthread_join(newthread_2, NULL);
    pthread_join(newthread_3, NULL);
    pthread_join(newthread_4, NULL);
    pthread_join(newthread_5, NULL);

    printf("All the clubs completed their transfer lists!");
    
    pthread_join(scoutThread, NULL);

    return 0;
}

// a function to create random budget for each clubs
struct Club budgetGenerator(struct Club s)
{

    int budgetLimit[] = {10000000, 20000000, 30000000, 40000000, 50000000};
    int length = sizeof(budgetLimit) / sizeof(int);

    int r = rand() % (length);
    s.budget = budgetLimit[r];
    return s;
}

// a function to create random transfer lists for each clubs
struct Club transferListGenerator(struct Club s)
{

    char agents[4][20] = {"Agent1", "Agent2", "Agent3", "Agent4"};
    char positions[4][20] = {"Forward", "Midfielder", "Defender", "Goalkeeper"};

    int length = 4;

    for (int i = 0; i < 5; i++)
    {
        int randAgents = rand() % (length);
        int randPositions = rand() % (length);

        strcpy(s.transferList[i][0], agents[randAgents]);
        strcpy(s.transferList[i][1], positions[randPositions]);
    }
    return s;
}
// a function for scout to update the costs of player in a management list
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
// a function to create players in the management list of an agent
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
// a function that add new players to agents
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
        // do not point a new address to add a player if an empty index exists
        if (agent.managementList[i].transferCost == 0 || strcmp(agent.managementList[i].positionName, ""))
        {
        label:
            printf("\n");

            int transferCost = baseCost * ((rand() % 17) + 4); // random cost between 4M-20M euros
            agent.managementList[i].transferCost = transferCost;

            int randPositions = rand() % (length);
            strcpy(agent.managementList[i].positionName, positions[randPositions]);
            isEnough = 1;
            break;
        }
        // list is full
        // add new player to the new allocated index
        if (isEnough == 0)
        { 
            i = agent.playerNumber;
            agent.playerNumber++;
            agent.managementList = (struct Player *)realloc(agent.managementList, agent.playerNumber * sizeof(struct Player));
            goto label;
        }
    }
    return agent;
}

// a function that represent the transfer negotiation between clubs and agents
// a mutex is used to prevent 2 clubs to transfer the same player at the same time (2)
// a semaphore is used to prevent more than 2 negotiation (3)
struct Club completeTransfer(struct Club c, struct Agent agents[]) {

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
            count++;
            break;
        }
    }  

    pthread_mutex_lock(&lock); // mutex (2)
    int transferDone;
    for(int x = 0; x < 4; x++){
        //printf("\n1\n");
        if(strcmp(wantedAgentName, Agents[x].agentName) == 0) {
            sem_wait(&sem); // semaphore (3)
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
        if(transferDone) {
            c.budget -= Agents[agentIndex].managementList[agentPlayerIndex].transferCost; // update the budget
            strcpy(Agents[agentIndex].managementList[agentPlayerIndex].positionName, "");
            Agents[agentIndex].managementList[agentPlayerIndex].transferCost = 0;
            printf("Transfer is done by Club%s\n", c.clubName);
            transferDone = 0;

            strcpy(c.transferList[clubTransferListIndex][0], ""); // set the agent name to ""
            strcpy(c.transferList[clubTransferListIndex][1], ""); // set the position of wanted player to ""
           
        }

        pthread_mutex_unlock(&lock); // (2)
        sem_post(&sem); // (3)
        
        return c;
    }



