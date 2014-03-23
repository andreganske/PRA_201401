/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */
#include "main.h"

// main menu
int main() {
	printf("\nWelcome!");
	printf("\nWhat you want to do?");
	
	menu();
}

void menu() {
	//to use random values
	srand(time(NULL));

	int menu, status = 0, position, quantity;

	do {

		printf("\n[0] Generate randon entries");
		printf("\n[1] Create and insert one entry");
		printf("\n[2] Create and insert multiple entries");
		printf("\n[3] Find and print one entry");
		printf("\n[4] Find and print multiple entries");

		printf("\n");
		scanf("%d", &menu);

		switch (menu) {
			case 0:
				status = 0;
			break;

			case 1:
				/* status = 0; */
				/* position = getInsertPosition(); */
				/* saveOneEntry(position); */
			break;

			case 2:
				/* status = 0; */
				/* position = getInsertPosition(); */
				/* quantity = getInsertQuantity(); */
				/* saveMultipleEntries(position, quantity); */
			break;

			case 3:
				/* status = 0; */
				/* position = getInsertPosition(); */
				/* printEntries(getOneEntry(position), 1); */
			break;
			
			case 4:
				/* status = 0; */
				/* position = getInsertPosition(); */
				/* quantity = getInsertQuantity(); */
				/* printEntries(getMultipleEntries(position, quantity), quantity); */
			break;

			default: 
				status = 1;
				printf("\nPlease, select a valid option!!!");
			break;
		}

	} while (status == 1);
}
