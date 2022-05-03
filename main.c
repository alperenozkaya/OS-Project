#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

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
struct Player *scoutCostUpdate();
struct Agent addNewPlayers();
void completeTransfer();

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

    completeTransfer(clubs[0], Agents);


    // check management lists
    for (int i = 0; i < Agents[i].playerNumber; i++)
    {
        for (int j = 0; j < Agents[i].playerNumber; j++)
            printf("%d-Position: %s   TransferCost %d\n", j + 1, Agents[i].managementList[j].positionName, Agents[i].managementList[j].transferCost);
    }
    printf("\n");

    // free(Agent1.managementList);
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

struct Player *scoutCostUpdate(struct Player *mngList)
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

void completeTransfer(struct Club c, struct Agent agents[]) {
     
    char wantedAgentName[6];
    char wantedPlayerPosition[20];
    int minTransferCost = 100000000;
    int playerIndex;
    int agentIndex;



    for(int i = 0; i < 5; i++ ){
        if(c.transferList[i][0] != ""){
            strcpy(wantedAgentName, c.transferList[i][0]);
            strcpy(wantedPlayerPosition, c.transferList[i][1]);
            break;
        }
    }

    for(int x = 0; x < 4; x++){
        printf("1");
        if(strcmp(wantedAgentName, Agents[x].agentName) == 0) {
            printf("2");
            for(int y = 0; y < Agents[x].playerNumber; y++){
                printf("3");
                if(strcmp(Agents[x].managementList[y].positionName, wantedPlayerPosition) == 0 && Agents[x].managementList[y].transferCost < minTransferCost) {
                    printf("4");
                    minTransferCost = Agents[x].managementList[y].transferCost;
                    playerIndex = y;
                    agentIndex = x;
                    printf("The player index: %d cost: %d  position: %s  agent index: %d\n", playerIndex, Agents[agentIndex].managementList[playerIndex].transferCost, Agents[agentIndex].managementList[playerIndex].positionName, agentIndex);
                    }

                }    
                                      
            }
        } 
    }


