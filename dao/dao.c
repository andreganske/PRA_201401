/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

// Calling some librarys
#include "dao.h"

/**************************************************************************************/
/**
 * defining some constants
 */
const char one[][] = {};

// database file
const char filename[] = "arquivoGerado.bin";

/**************************************************************************************/
/**
 * defining some control variables
 */
// total lines
unsigned int qtd_total_lines;

// execution time control
clock_t time_start, time_end;

FILE *fp;

/**************************************************************************************/
/**
 * Defining functions
 */

// persiste entries
void saveOneEntry();
void saveMultipleEntries();

// findind entries
void getOneEntry();
void getMultipleEntries();

// removing entries
void removeOneEntry();
void removeMultipleEntries();

void executionTime();
FILE createFile();
void removeFile(FILE *fp);

/**************************************************************************************/
/**
 * Generic functions
 */
void executionTime() {
	double duration;

	// calc time elapsed
	duration = (double) (time_end - time_start) / CLOCKS_PER_SEC;

	// print elapsed time
	printf("\n[dao.executionTime] - This function was runned for %.2lf seconds", duration);
	return 0;
}

FILE createFile() {
	if (fp = fopen(filename, "wb") == NULL) {
		printf("\nError while creating file!");		
	}

	fclose(fp);
}

void removeFile() {
	if (remove(fp) == 0) {
		printf("\nFile deleted!");
	} else {
		printf("\nError while deleting file!");
	}
}

void createEntry() {

}

int getInsertPosition() {
	int position, status = 0, line;

	do {
		printf("\nWhere it will be included? (1) start, (2) middle, and I'll selecte it, (3) end of file");
		scanf("%d", &position);

		switch (position) {
			case 1:
				// include in the begging
				line = 0;
				status = 1;
			break;

			case 2:
				// set line destination
				switch (qtd_total_lines) {
					case 0: printf("\nFile is empty. You dont need to worry about it."); status = 1; line = -1; break;
					default: 
						printf("\nThis file have %d lines. Select where it will be included." qtd_total_lines);
						scanf("%d", &line);
						status = 1;
						break;
				}
			break;

			case 3;
				// include at the end
				line = -1;
				status = 1;
			break;

			default:
				printf("\nPlease, select one of given options.", );
				status = 0;
			break;
		}
	} while (status != 1);

	return line;
}

void countFileLines(){
	printf("\nReading file to count lines, please wait");

	long temp = 0;

    if ((fp = fopen(filename,"rb")) == NULL) {
        printf("File not found!");
        return 0;

    } else {
        while (1) {
            fread(&DAO, sizeof(DAO),1,fp);

            if (feof(fp)) break;
            temp++;
        }
        fclose(fp);
    }

    qtd_file_lines = temp;
}

/**************************************************************************************/
void saveOneEntry() {

	// Create file
	createFile();

	// get line quantity
	countFileLines();

	// identify where will insert that entry
	int line = getInsertPosition();

	// generate entry
	createEntry();

	// save entry
	switch (line) {
		case -1:
			// insert in the end of file
			fseek(fp, 0, SEEK_END);
		break;

		case 0:
			// insert in the begging of file
			fseek(fp, 0, SEEK_SET);
		break;

		default:
			// insert where user wants
			fseek(fp, 0, line);
		break;
	}

	// write in the file
	if (!fwrite(NULL, sizeof(null), 1, fp)) {
		printf("\n[dao.saveOneEntry] - Error on saving data!");
		exit(0);
	}

	printf("\n[dao.saveOneEntry] - File updated with success!");
}


