/*
Name:		Dylan Rice
Date:		5/5/2020
*/

#include <stdio.h>
#include "gameBits.h"

//Main method of the program
int main(){
	//Variable to store the file
	FILE* file = fileFinding("Players.txt");

	//Stores the player data
	people players[10],*player;

	//Stores choices the user makes and other data
	char choice;
	int length = getPlayers(file,players);

	//Loop to print menu and get choices
	while(1){
		//Prints out each menu item
		printf("0) Top up balance\n");
		printf("1) Play the game\n");
		printf("2) Top 5 players by score\n");
		printf("3) Top 5 winners by earnings\n");
		printf("4) Quit\n");
		printf("Please choose desired option: ");

		//Gets selection from the user
		scanf("%c",&choice);getchar();
		NEXT

		//Checks to see what the user input
		//If the input is 0 or 1
		if(choice == '0' || choice == '1'){
			//Keeps looping until the player goes back or is found
			while(1){
				//Gets the player to find
				player = personFinder(length,players);

				//If the player was not found, loops back to ask again
				if(player == NULL)
					printf("Name not found, please try again\n\n");

				//if the name is found or the player says to go back
				else if(player->balance == -255)
					break;

				//if the player didn't ask to go back to the menu
				else{
					//If the input is 0
					if(choice == '0'){
						//Prints out the player's current balance
						printf("The current balance of %s is %d\n",player->name,player->balance);

						//Calls method to change player balance
						balanceChanger(player);
					}
					//If the input is 1
					else if(choice == '1'){
						do{
							//Calls the dice game method
							choice = diceGame(player);

						//Loops if the user chooses to
						}while(choice == 'y');
					}
					//Exits back to menu
					break;
				}
			}
		}
		//If the player chooses option 2
		else if(choice == '2'){
			//Calls method for making top 5 list from balance
			top5Maker(length,players,'b');
		}
		//If the input is 3
		else if(choice == '3'){
			//Calls method for making top 5 list from gains
			top5Maker(length,players,'g');
		}
		//Happens if the user wishes to go back
		else if(choice == '4'){
			fileUpdater(file,players,length);
			//Closes the file and exits the program
			fclose(file);
			return 1;
		}
		//Happens if the user input an invalid choice
		else
			printf("Please chose one of the options above\n\n");
	}
}
