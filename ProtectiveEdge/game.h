#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>


// Structure to represent the game field
struct Filed {
    int players;
    int player;
    int x;
    int y;
    int** grid;
    int** outputbuffer;
    int* playersid;
    int cx;
    int cy;
    char name[10];
    int SelectionMode;
    int sx;
    int sy;
    
};

// Function declarations
void writeFieldToFile(const char* filename, struct Filed* f);
void readFieldFromFile(const char* filename, struct Filed* field);
void BuildBuffer(struct Filed f);
void printField(struct Filed f);
struct Filed initFiled(int x, int y, int players);
void fillPattern(struct Filed f);
void CurrsorUp(struct Filed* f);
void CurrsorDown(struct Filed* f);
void CurrsorLeft(struct Filed* f);
void CurrsorRight(struct Filed* f);
void Select(struct Filed* f);
void UnSelect(struct Filed* f);
void Move(struct Filed* f);
void gameLoopFromSave(char* name);
void gameLoop(int players, char* name);
