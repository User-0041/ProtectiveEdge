#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include"Players.h"
#include "game.h"

void StartGame(struct players loadedPlayers) {
	int x;
	printf("Enter Number Of Ops\n");
	scanf("%d", &x);
	while (x>4)
	{
		printf("Too Many Opratavies");
		scanf("%d", &x);
	}


	printf("Enter Host Credinations");
	struct player op = readPlayerFromKeyboard();
	printf("Enter Game Name (This will be needed to load the save game later)\n");

	char name[10];
	scanf("%s", &name);

	gameLoop(x,name);
}


void SavePlayer(struct players loadedPlayers) {
	struct player user1 = readPlayerFromKeyboard();
	addPlayerToList(&loadedPlayers, &user1);
	writePlayersToDisk(&loadedPlayers);
}

void LoadGame(struct players loadedPlayers) {
	printf("Enter Game Name You want to load\n");
	char name[10];
	scanf("%s", &name);
	gameLoopFromSave(name);
}