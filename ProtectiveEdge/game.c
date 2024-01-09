#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "GarbageCollector.h"
#include "input.h"
#include "game.h"
#include"menu.h"


void writeFieldToFile(struct Filed* f) {
	FILE* file = fopen("test.bin", "wb");

	if (file == NULL) {
		perror("Error opening file for writing");
		return;
	}

	// Write metadata
	if (fwrite(&(f->player), sizeof(int), 1, file)!=1 ||
		fwrite(&(f->x), sizeof(int), 1, file) != 1 ||
		fwrite(&(f->y), sizeof(int), 1, file) != 1 ||
		fwrite(&(f->players), sizeof(int), 1, file) != 1) {
		perror("Error writing metadata to file");
		fclose(file);
		return;
	}

	// Write grid data
	if (fwrite(f->grid[0], sizeof(int), f->x * f->y, file) != f->x * f->y) {
		perror("Error writing grid data to file");
		fclose(file);
		return;
	}
	fclose(file);


}
void readFieldFromFile(const char* filename, struct Filed* field) {

	char binFilename[255];  // Adjust the size as needed

	// Concatenate "bin" to the original filename
	strcpy(binFilename, filename);
	strcat(binFilename, ".bin");


	FILE* file = fopen("test.bin", "rb");

	if (file == NULL) {
		fprintf(stderr, "Error opening file for reading.\n");
		return;
	}

	// Read metadata
	fread(&(field->player), sizeof(int), 1, file);
	fread(&(field->x), sizeof(int), 1, file);
	fread(&(field->y), sizeof(int), 1, file);
	fread(&(field->players), sizeof(int), 1, file);

	// Allocate memory for grid and playersids
	field->grid = (int**)malloc(field->x * sizeof(int*));
	field->grid[0] = (int*)malloc(field->x * field->y * sizeof(int));

	gc_add(field->grid[0]);

	gc_add(field->grid);

	//field->playersid = (int*)malloc(sizeof(int) * field->players);

	// Link the row pointers to the appropriate locations in the data block


	// Read grid data
	fread(field->grid[0], sizeof(int), field->x * field->y, file);


	for (int i = 1; i < field->x; i++) {
		field->grid[i] = field->grid[0] + i * field->y;
	}



	// Read playersids data
	//fread(field->playersid, sizeof(int), field->players, file);

	fclose(file);
}


int inbound(int x , int max , int min ) {
	if (x > max) { return FALSE; };
	if (x < min) { return FALSE; };
	return TRUE;
}

void BuildBuffer(struct Filed f) {
	memcpy(f.outputbuffer[0], f.grid[0], f.x * f.y * sizeof(int));
	for (int i = 0; i < f.x; i++) {
		for (int j = 0; j < f.y; j++) {
			if (i == f.cx && j == f.cy) {
				f.outputbuffer[i][j] = "@";
			};
		}
	}

	f.outputbuffer[f.cx][f.cy] = 8;

	if (f.grid[f.cx][f.cy] != 0) {

		int startX = f.cx - 1 < 0 ? 0 : f.cx - 1;
		int startY = f.cy - 1 < 0 ? 0 : f.cy - 1;
		int endX = f.cx + 1 >= f.x ? f.x - 1 : f.cx + 1;
		int endY = f.cy + 1 >= f.y ? f.y - 1 : f.cy + 1;

		for (int i = startX; i <= endX; i++) {
			for (int j = startY; j <= endY; j++) {
				int tempi = i + i;
				int tempj = j + j;

				if (f.grid[i][j] == 0 && !(i == f.cx && j == f.cy)) {

					f.outputbuffer[i][j] = 9;

				}
				else if (f.grid[i][j] != 0 ) {

					int tempi = (i - f.cx) + i;
					int tempj = (j - f.cy) + j;
					if ((inbound(tempi, f.x-1, 0) && inbound(tempj, f.y-1, 0))) {
						if (f.grid[tempi][tempj] == 0 ) {
							f.outputbuffer[tempi][tempj] = 9;
						}
					}
					}
				



			}
		}
	}


	f.outputbuffer[f.sx][f.sy] = 7;



}
void printField(struct Filed f) {
	BuildBuffer(f);
	system("cls");
	for (int i = 0; i < f.x; i++) {
		for (int j = 0; j < f.y; j++) {
			printf("%d", f.outputbuffer[i][j]);
		}
		printf("\n");
	}
}





struct Filed initFiled(int x, int y, int players) {
	srand((int)0x78642+players );
	struct Filed f;
	f.x = x;
	f.y = y;
	f.players = players;
	//f.player = rand() % players;
	f.player = 1;
	f.cx = 0;
	f.cy = 0;
	f.sx = 0;
	f.sy = 0;	// Allocate memory for the 2D array (rows and data in a single allocation)
	f.grid = (int**)malloc(x * sizeof(int*));
	f.grid[0] = (int*)malloc(x * y * sizeof(int));
	f.outputbuffer = (int**)malloc(x * sizeof(int*));
	f.outputbuffer[0] = (int*)malloc(x * y * sizeof(int));
	gc_add(f.grid[0]);
	gc_add(f.outputbuffer[0]);
	gc_add(f.outputbuffer);
	gc_add(f.grid);

	// Link the row pointers to the appropriate locations in the data block
	for (int i = 1; i < x; i++) {
		f.grid[i] = f.grid[0] + i * y;
		f.outputbuffer[i] = f.outputbuffer[0] + i * y;

	}
	f.SelectionMode = FALSE;

	// Initialize the 2D array (optional)
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			f.grid[i][j] = 0; // You can initialize with any default value
		}
	}
	return f;
}



void fillPattern(struct Filed f) {
	
	for (int num = 1; num < f.players+1; num++)
	{
		int x = num % 2;
		int y = num / 2;
		//This is Curesed It shoud  not be this complicated to fill the gird but my heart wont let me make 4 for loops so too bad
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4 - i; j++) {
				int indexx = i;
				int indexy = j;
				if (x == 1) {
					indexx = f.y - i-1;
				};
				if (y == 1) {
					indexy = f.y - j - 1;
				};
				f.grid[indexx][indexy]=num;
			}
		}
	}


}

void CurrsorUp(struct Filed* f) {
	if ((f->cx == 0) || (f->sx == 0)) { return; }
	if (f->SelectionMode) {
		if (f->sx < f->cx) { return; }
		f->sx--;
		if (f->grid[f->sx][f->sy] != 0) {
			int tempi = (f->sx - f->cx) + f->sx;
			int tempj = (f->sy - f->cy) + f->sy;
			if (f->grid[tempi][tempj] != 0) {
				f->sx++;
				return;
			}
			f->sx = tempi;
			f->sy = tempj;

		}
	}
	else {
		f->cx--;
		f->sx--;
	}


}
void CurrsorDown(struct Filed* f) {
	if ((f->cx == f->x - 1) || (f->sx == f->x - 1)) { return; }
	if (f->SelectionMode) {
		if (f->sx > f->cx) { return; }

		f->sx++;
		if (f->grid[f->sx][f->sy] != 0) {
			int tempi = (f->sx - f->cx) + f->sx;
			int tempj = (f->sy - f->cy) + f->sy;
			if (f->grid[tempi][tempj] != 0) {
				f->sx--;
				return;
			}
			f->sx = tempi;
			f->sy = tempj;

		}
	}
	else {
		f->cx++;
		f->sx++;

	}

}
void CurrsorLeft(struct Filed* f) {
	if ((f->cy == 0) || f->sy == 0) { return; }
	if (f->SelectionMode) {
		if (f->sy < f->cy) { return; }
		f->sy--;
		if (f->grid[f->sx][f->sy] != 0) {
			int tempi = (f->sx - f->cx) + f->sx;
			int tempj = (f->sy - f->cy) + f->sy;
			if (f->grid[tempi][tempj] != 0) {
				f->sy++;
				return;
			}
			f->sx = tempi;
			f->sy = tempj;

		}

	}
	else {
		f->cy--;
		f->sy--;

	}
}
void CurrsorRight(struct Filed* f) {


	if ((f->cy == f->y - 1) || (f->sy == f->y - 1)) { return; }

	if (f->SelectionMode) {
		if (f->sy > f->cy) { return; }

		f->sy++;
		if (f->grid[f->sx][f->sy] != 0) {
			int tempi = (f->sx - f->cx) + f->sx;
			int tempj = (f->sy - f->cy) + f->sy;
			if (f->grid[tempi][tempj] != 0) {
				f->sy--;
				return;
			}
			f->sx = tempi;
			f->sy = tempj;

		}
	}
	else {
		f->cy++;
		f->sy++;

	}
}



void Select(struct Filed* f) {

	if (f->grid[f->cx][f->cy] == f->player) {
		f->SelectionMode = TRUE;
		f->sx = f->cx;
		f->sy = f->cy;
	}
}

void UnSelect(struct Filed* f) {
	if (f->SelectionMode) {
		f->SelectionMode = FALSE;
		f->sx = f->cx;
		f->sy = f->cy;
	}
}


void Move(struct Filed* f) {
	int temp = f->grid[f->cx][f->cy];
	f->grid[f->cx][f->cy] = 0;
	f->grid[f->sx][f->sy] = temp;
	Select(f);
	UnSelect(f);

	
	f->player++;
	f->player = f->player % 3;
	if (0 == f->player) { f->player++; }




}



void Save(struct Filed* f) {

	writeFieldToFile(f);
	Sleep(6000);
}



void gameLoop(int players, char * name) {
	KeyState keyState;
	initializeKeySymbols(&keyState);
	int x = 16;
	int y = 16;
	

	struct Filed myField = initFiled(x, y, players);
	strcpy(myField.name,name);
	myField.grid[10][10] = 1;
	myField.grid[10][11] = 2;



	fillPattern(myField);

	bindFunction(&keyState, 'Z', CurrsorUp);
	bindFunction(&keyState, 'S', CurrsorDown);
	bindFunction(&keyState, 'Q', CurrsorLeft);
	bindFunction(&keyState, 'D', CurrsorRight);
	bindFunction(&keyState, 'A', Move);
	bindFunction(&keyState, 'E', Select);
	bindFunction(&keyState, 'R', UnSelect);
	bindFunction(&keyState, 'P', Save);




	while (1)
	{
		getPressedKeys(&keyState);
		executeKeyFunctions(&keyState, &myField);
		printField(myField);
		Sleep(20);
	}





	free(myField.grid[0]);  // Free the data block
	free(myField.grid);     // Free the row pointers
}



void gameLoopFromSave(char* name) {
	KeyState keyState;
	initializeKeySymbols(&keyState);
	int x = 16;
	int y = 16;

	struct Filed myField = initFiled(x, y, 0);
	readFieldFromFile(name, &myField);

	
	bindFunction(&keyState, 'Z', CurrsorUp);
	bindFunction(&keyState, 'S', CurrsorDown);
	bindFunction(&keyState, 'Q', CurrsorLeft);
	bindFunction(&keyState, 'D', CurrsorRight);
	bindFunction(&keyState, 'A', Move);
	bindFunction(&keyState, 'E', Select);
	bindFunction(&keyState, 'R', UnSelect);
	bindFunction(&keyState, 'P', Save);

	



	while (1)
	{
		getPressedKeys(&keyState);
		executeKeyFunctions(&keyState, &myField);
		printField(myField);
		Sleep(20);
	}





	free(myField.grid[0]);  // Free the data block
	free(myField.grid);     // Free the row pointers
}
