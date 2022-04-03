/*
Name:		Dylan Rice
Date:		5/5/2020
*/

#ifndef GAMEBITS_H_
#define GAMEBITS_H_

#define NEXT printf("\n");

//Defined structure for storing the player data
typedef struct players{
	//The name, balance, and gains of the player
	char name[12];
	int balance,change;
}people;

//Predefining methods
FILE* fileFinding(char *fileName);
int getPlayers(FILE* file,people* players);
people* personFinder(int length,people *players);
int diceRoller();
void fileUpdater(FILE* file,people *players,int length);
void balanceChanger(people *player);
char diceGame(people *player);
void top5Maker(int length,people *players,char mode);

#endif /* GAMEBITS_H_ */
