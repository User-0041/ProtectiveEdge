#define _CRT_SECURE_NO_WARNINGS
#include "players.h"
#include "game.h"


//C PROJECT FOR THE FIRST FRIST SIMESTER THIS PROJECTS MEET ALL REQUERMTS EXPECT WIN CONDTIONS AND SCORE
//THE CUSTOM MODULES ARE CALL BACK SYSTEM FOR REAL TIME INPUT WITCH PROVIED BETTER USER EXPRICE
//GARABADGE COLLECTOR FOR MORE EFFECTIVE MEMEORY MANGMENT
//HASHED PASSWORDS SINCE ALL FILES ARE STORED LOCLY 



// MOVING IS DONE WITH   Z
//                      Q D
//                       S 
// FOR DIRECTIONS
// AND E TO PICK A PICE
// AND A TO MOVE THE PICE
// AND P TO SAVE GAME

struct GarbageCollector*  Garbage;

int main() {
     gc_startup(100);


    struct players loadedPlayers = initPlayersStruct();
    loadPlayersFromDisk(&loadedPlayers);
    if (loadedPlayers.length==0) {
        printf("OPRATION PROTECTIVE EDGE ");
        struct player user1 = readPlayerFromKeyboard();
        addPlayerToList(&loadedPlayers, &user1);
        writePlayersToDisk(&loadedPlayers);


    }


LogIn:

    struct player p = readPlayerFromKeyboard();

    


    if (!isPlayer(&loadedPlayers, p)) {
        goto LogIn;
    }


    int choice;

    while (1)
    {

    // Display menu options
    printf("\nMenu:\n");
    printf("1. Start New Game\n");
    printf("2. Continue Game\n");
    printf("3. Add Player\n");
    printf("4. Quit\n");
    printf("Enter your choice: ");
    
    int x  = scanf("%d", &choice);
    // Process user choice
    switch (choice) {
    case 1:
        StartGame(loadedPlayers);
        break;
    case 2:
        LoadGame(loadedPlayers);
        break;
    case 3:
        SavePlayer(loadedPlayers);
        break;
    case 4:
        printf("Quitting...\n");
        gc_cleanup();
        return 0;
        break;
    default:
        printf("Invalid choice. Please enter a number between 1 and 5.\n");
        break;
    }

    }








  
}
