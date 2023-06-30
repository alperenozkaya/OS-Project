# OS-Project
OS Term Project

*1.Introduction*

During the transfer window, every football club in the world is keen to sign exceptional
players. Four well-known football agents are in charge of managing contracts on behalf of
players throughout the world. Each agent is in charge of four distinct types of players:
forwards, midfielders, defenders, and goalkeepers. For each agent, the current number of
players and their positions are listed below.

In order to fulfill these targeted tasks and perform the operations correctly, appropriate
solutions were tried to be found by using POSIX thread, mutex lock, semaphores and OS
principles.

*2. Methodology*

In order to figure out this problem, a variety of functions are used. Some of the
functions provide initializations, the other functions make some calculations
for the threads that represent clubs and scouts. To make the operations
simpler, “Club”, “Player”, and “Agent structs'' have been created.
Structs:
- Clubs: It holds the information about names of clubs, their budgets and
transfer lists.
- Player: It holds the information about the positions of players and its transfer
cost.
- Agent: It holds the information about names of agencies, a number of players
in agency, and a struct Player type pointer which handles the management of
the list between clubs and agencies.
Functions:
- struct Club budgetGenerator(): It assigns the budgets of clubs ranging from
10 million euros to 50 million euros. In order to complete this task,
randomizing methods rand() are used.
- struct Club transferListGenerator(): It generates randomized transfer lists
for each of the clubs.
- struct Player *initializePlayers(): It assigns the positions and transfer costs
of each player via the management list pointer which was mentioned in the
Structs/Agent section.
1
- struct Player * scoutCostUpdate(): It updates the transfer cost of players by
either increasing by 1 million euros or decreasing by 500 thousand euros
randomly in a random matter of time.
- struct Agent addNewPlayers(): It searches agency lists for possible addition
of new players to transfer markets. However, the function can work in two
different ways.
First, it fills the empty slots in the agencies, which were caused by completing
a transfer, by creating and adding a new player to the list randomly in a
random matter of time and a random number of players.
Second, if there was no transfer till the function operated, it adds new players
to the lists randomly in a random matter of time and a random number of
players.
- struct Club completeTransfer(): It maintains the transfer negotiation process
between clubs and agents.
Threads:
A total of 6 threads are used in the project. 5 of them represent the 5 football
clubs that contact agents for their transfer lists . And the other thread
represents the scout. All of the threads have their related functions that have
endless while loops.
- Club threads try to complete transfers in a while loop using “struct
Club completeTransfer()”.
- Scout thread updates the costs of players in management lists of
agents or add new players in random time intervals using the functions
“struct Player * scoutCostUpdate()”, and struct Club
completeTransfer().

## Authors

- [@alperenozkaya](https://www.github.com/alperenozkaya)
- [@cemtzn](https://www.github.com/cemtzn)


