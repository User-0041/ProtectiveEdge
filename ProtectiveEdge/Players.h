#pragma onces
#define _CRT_SECURE_NO_WARNINGS

#define MAX_LENGTH 10

struct players {
    char** usernames;
    char** passwords;
    int length;
};

struct player {
    char* username;
    char* password;
};

void addPlayerToList(struct players* playersArray, struct player* newPlayer);
void writePlayersToDisk(struct players* playersArray);
struct players initPlayersStruct();
void hashFunction(char* str);
struct player readPlayerFromKeyboard();
int isPlayer(struct players * players , struct player player);

