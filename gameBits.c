/*
Name:		Dylan Rice
Date:		5/5/2020
*/

//Includes time for the random number generation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameBits.h"

//Method for making top 5 lists and printing them
void top5Maker(int length,people *players,char mode){
	//Variables to store what the program creates the list with
	int temp,used[4],pass,value;
	char highName[15];

	//If b is given, do the balance list
	if(mode == 'b')
		printf("The top 5 players based off balance are:\n");
	//If g is given, do the gain list
	else if(mode == 'g')
		printf("The top 5 players based off gain are:\n");
	//If neither, exit out
	else{
		printf("Please chose a valid list type\n");
		return;
	}

	//Loops 5 times, one for each name
	for(int x = 0;x < 5;x++){

		//Sets the variable as low as possible to allow for a range of scores to be checked
		temp = -(int)sizeof(int);

		//Loops the length of the array to compare all the names
		for(int y = 0; y < length;y++){
			//resets pass
			pass = 0;

			//Gets the balance if b
			if(mode == 'b')
				value = players[y].balance;
			//Gets the gain if g
			else if(mode == 'g')
				value = players[y].change;

			//If their balance is greater than the smallest number
			if(value > temp){
				//Loops for the length of the used numbers to avoid repeats
				for(int z = 0;z < sizeof(used)/4;z++){
					//If the player is already listed, skip them
					if(value == used[z]){
						pass = 1;
						break;
					}
				}
				//If not told to skip
				if(pass != 1){
					//Sets the variables to the person to print
					temp = value;
					strcpy(highName,players[y].name);
				}
			}
		}
		//Print statement for the person
		printf("%d. %s with %d\n",x+1,highName,temp);
		used[x] = temp;
	}
	NEXT
}

//Method to run the dice game
char diceGame(people *player){
	//Stores point value to get, dice rolls, and if to loop
	int pointValue,sum;
	char winValue,choice = 'n';

	if(player->balance <= 0){
		//Prints message and goes back to menu
		printf("Insufficient funds, please add more to play\n\n");
		return 'n';
	}

	//Asks the user to press enter
	printf("Press enter to roll the dice\n");
	getchar();

	//Gets the dice roll sum
	sum = diceRoller();

	//If the sum is 7 or 11, the player wins
	if(sum == 7 || sum == 11){
		//Marks the player as winning
		winValue = 'W';
	}
	//If the sum is 2, 3, or 12, then then user loses
	else if(sum == 2 || sum == 3 || sum == 12){
		//Marks the player as losing
		winValue = 'L';
	}
	//If the player hasn't won or lost yet
	else{
		//Sets point value to be the dice roll sum
		pointValue = sum;
		while(1){
			//Asks the user to roll again
			printf("Press enter to roll the dice\n");
			getchar();

			//Gets the new dice roll sum
			sum = diceRoller();

			//If the sum is 7 then the player loses
			if(sum == 7){
				//Marks the player as losing
				winValue = 'L';
				break;
			}
			//If the sum is the same as the first one, then the player wins
			else if(sum == pointValue){
				//Marks the player as winning
				winValue = 'W';
				break;
			}
		}
	}
	//If the player won, prints the message and adds 10 to their balance and gain
	if(winValue == 'W'){
		printf("Player Wins. ");
		player->balance += 10;
		player->change += 10;
	}
	//If the player lost, prints the message and subtracts 1 from their balance and gain
	else{
		printf("Player Loses. ");
		player->balance -= 1;
		player->change -= 1;
	}
	//Prints out the new balance
	printf("New balance is %d.\n\n",player->balance);

	//If the player balance is greater than 0
	if(player->balance > 0){
		//Asks the user if they want to continue
		printf("Do you wish to continue? (y/n) ");
		scanf("%c",&choice);getchar();
		NEXT
	}
	//Returns choice to loop
	return(choice);
}

//Method that changes player balance
void balanceChanger(people *player){
	//Stores how much to add or subtract
	int change;

	//Asks the user how much to add to balance
	printf("How much would you like to add to the balance? ");\
	scanf("%d",&change);getchar();

	//Adds that value to the player balance
	player->balance += change;
	NEXT
}

//Updates the file with the changed data
void fileUpdater(FILE* file,people *players,int length){
	//Variable to store the output to be put in the folder
	//If exit value == -1, increase this
	char output[20];

	//Brings the file pointer to the start
	rewind(file);

	//Loops for how many items are in the array
	for(int x = 0;x < length;x++){
		//If the value is at the end, don't add the \n
		if(x == length-1)
			//Print statement that prints the given string to the buffer(output) instead of the console
			sprintf(output,"%s\t%d\t%d",(players+x)->name,(players+x)->balance,(players+x)->change);
		//If the value isn't the last one, then add \n
		else
			//Print statement that prints the given string to the buffer(output) instead of the console
			sprintf(output,"%s\t%d\t%d\n",(players+x)->name,(players+x)->balance,(players+x)->change);

		//Puts the output string to the file
		fputs(output,file);
	}
}

//Method for rolling the dice
int diceRoller(){
	//Sets a seed for random number generation using the current time
	srand(time(0));

	//Variables to store dice values and the sum
	int dice[2],sum = 0;

	//Rolls each dice and gets a value for both
	for(;sum < 2;sum++){
		//Randomly generates a value between 1 and 6
		dice[sum] = (1 + rand() / ((RAND_MAX / 6) + 1));
	}
	//Adds the dice together for the sum
	sum = dice[0]+dice[1];

	//Prints the values and the sum
	printf("The values rolled are %d and %d, which summed equal %d\n\n",dice[0],dice[1],sum);
	//Returns the sum
	return sum;
}

//Finds the player given from the array of players
people* personFinder(int length,people *players){
	//Stores the given name
	char name[12];

	//Variables to help go through the menu
	people *temp = malloc(sizeof(people));

	//Asks the user for the name or to go back
	printf("Please enter the player's name or 'b' to go back: ");
	scanf("%s",name);getchar();NEXT

	//If the user said to go back
	if(strcmp(name,"b") == 0){
		//Set the balance to negative value
		temp->balance = -255;

		//Return the variable to be processed
		return temp;
	}
	//Loops for the length of the array
	for(int x = 0;x < length;x++){
		//If the name has been found
		if(strcmp(((players+x)->name),name) == 0){
			//return the pointer of the person in the array
			return(players+x);
		}
	}
	//If no name is found, return NULL
	return NULL;
}

//Method that gets the players from a file and puts then into an array
int getPlayers(FILE* file,people* players){
	//Variable to count the length
	int spot = 0;

	//Loops until told to quit
	while(1){
		//If the end of the file hasn't been reached yet
		if(feof(file) != 1){
			//Gets the user's information from the file
			fscanf(file,"%s\t%d\t%d",(players+spot)->name,&(players+spot)->balance,&(players+spot)->change);

			//Moves to the next spot in the array of players
			spot++;
		}
		//Breaks out of the loop once every user has been added
		else
			break;
	}
	//Returns spot for the length
	return spot;
}

//Method that opens the file and returns it
FILE* fileFinding(char *fileName){
	//Opens the file with the given name and sets it to read
	FILE *file = fopen(fileName,"r+");;

	//Checks if the file exists
	if(file == NULL){
		printf("Cannot find the file called %s\n",fileName);

		//Closes the file and exits the program
		fclose(file);
		exit(EXIT_FAILURE);
	}
	//If the file exists, it returns the variable
	else
		return file;
}
