#include "input.h"


void initializeKeySymbols(KeyState* keyState) {
    for (int i = 0; i < NUM_KEYS; i++) {
        keyState->symbols[i] = (char)i;
      
    }


    for (int i = 0; i < NUM_KEYS; i++) {
        keyState->keyFunctions[i] = NULL;
    }

}



void getPressedKeys(KeyState* keyState) {

        for (int i = 0; i < NUM_KEYS; i++) {
            keyState->keys[i] = GetAsyncKeyState(i) & 0x8001;
        }
}


void inputTrhead(KeyState* keyState) {
    while (TRUE)
    {
        for (int i = 0; i < NUM_KEYS; i++) {
            keyState->keys[i] = GetAsyncKeyState(i) & 0x8001;
        }
    }
}


BOOL getKeyStateByKeySymbol(KeyState* keyState, char symbol) {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (keyState->symbols[i] == symbol) {
            return keyState->keys[i];
        }
    }
    return FALSE; // Symbol not found, return default state
}


void bindFunction(KeyState* keyState, char symbol, void (*func)()) {
    for (int i = 0; i < NUM_KEYS; i++) {
        if (keyState->symbols[i] == symbol) {
            keyState->keyFunctions[i] = func;

            return;
        }
    }
    printf("Symbol %c not found in the key array.\n", symbol);
}

void executeKeyFunctions(KeyState* keyState, struct Filed *f) {
   

    // Check the state of each key and execute the associated function
    for (int i = 1; i < NUM_KEYS; i++) { // Skip key 0 (NULL function)
        if (getKeyStateByKeySymbol(keyState, keyState->symbols[i])) {
            if (keyState->keyFunctions[i] != NULL) {
                keyState->keyFunctions[i](f);
            }
        }
    }
}

