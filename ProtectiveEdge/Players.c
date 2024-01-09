#include "players.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GarbageCollector.h"

#define USER_FILE "USER.BIN"
struct players initPlayersStruct() {
    struct players playersArray;
    playersArray.usernames = (char**)malloc(MAX_LENGTH * sizeof(char*));
    playersArray.passwords = (char**)malloc(MAX_LENGTH * sizeof(char*));
    playersArray.length = 0;

    // Allocate memory for each username and password row separately
    for (int i = 0; i < MAX_LENGTH; i++) {
        playersArray.usernames[i] = (char*)malloc(MAX_LENGTH * sizeof(char));
        playersArray.passwords[i] = (char*)malloc(MAX_LENGTH * sizeof(char));
    }
 
    gc_add(playersArray.usernames);
    gc_add(playersArray.passwords);

    return playersArray;
}

void hashFunction(char* str) {

     
        int len = strlen(str);

        for (int i = 0; i < len; i++) {
            str[i] = str[i] ^ 0xAA;
        }
    

    
}





struct player readPlayerFromKeyboard() {
    struct player newPlayer;

    // Input playerid
    
    // Input username
    printf("Enter Oprative PassWord: ");
    char usernameBuffer[MAX_LENGTH];  // Assuming a maximum length of 100 characters
    scanf("%s", usernameBuffer);
    newPlayer.username = _strdup(usernameBuffer);  // Use _strdup to allocate memory for the username

    // Input password
    printf("Enter Oprative Key: ");
    char passwordBuffer[MAX_LENGTH];  // Assuming a maximum length of 100 characters
    scanf("%s", passwordBuffer);

    // Use hashFunction for password
    hashFunction(passwordBuffer);

    newPlayer.password = _strdup(passwordBuffer);  // Use _strdup to allocate memory for the password
    return newPlayer;
}

void writePlayersToDisk( struct players* playersArray) {
    FILE* file = fopen(USER_FILE, "wb");
    if (file != NULL) {
        fwrite(&playersArray->length, sizeof(int), 1, file);
        for (int i = 0; i < playersArray->length; i++) {
            fwrite(playersArray->usernames[i], sizeof(char), MAX_LENGTH, file);
            fwrite(playersArray->passwords[i], sizeof(char), MAX_LENGTH, file);
        }
        fclose(file);
    }
    else {
        printf("Error opening file for writing.\n");
    }
}


void addPlayerToList(struct players* playersArray,  struct player* newPlayer) {
    if (playersArray->length < MAX_LENGTH) {
        strncpy(playersArray->usernames[playersArray->length], newPlayer->username, MAX_LENGTH);
        strncpy(playersArray->passwords[playersArray->length], newPlayer->password, MAX_LENGTH);
        playersArray->length++;
    }
    else {
        printf("Error: Player list is full.\n");
    }



}

void loadPlayersFromDisk(struct players* playersArray) {
    FILE* file = fopen(USER_FILE, "rb");
    if (file != NULL) {
        fread(&playersArray->length, sizeof(int), 1, file);
        for (int i = 0; i < playersArray->length; i++) {
            fread(playersArray->usernames[i], sizeof(char), MAX_LENGTH, file);
            fread(playersArray->passwords[i], sizeof(char), MAX_LENGTH, file);
        }
        fclose(file);
    }

}


int isPlayer(struct players* players , struct player player) {
  


    for (int i = 0; i < players->length; ++i) {

        
        if (strcmp(players->usernames[i], player.username) == 0) {
            // Username matched, now check the password
            if (strcmp(players->passwords[i], player.password) == 0) {
                return 1;
            }
            else {
                // Password doesn't match
                return 0;
            }
        }



    }



    // Player not found
    return 0;
}