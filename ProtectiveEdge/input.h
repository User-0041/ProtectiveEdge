#pragma once
#pragma once

#include <stdio.h>
#include <windows.h>

#define NUM_KEYS 256

typedef struct {
    BOOL keys[NUM_KEYS];
    char symbols[NUM_KEYS];
    void (*keyFunctions[NUM_KEYS])();
} KeyState;

void initializeKeySymbols(KeyState* keyState);

void getPressedKeys(KeyState* keyState);

BOOL getKeyStateByKeySymbol(KeyState* keyState, char symbol);

void getPressedKeys(KeyState* keyState);

void bindFunction(KeyState* keyState, char symbol, void (*func)());

void executeKeyFunctions(KeyState* keyState);