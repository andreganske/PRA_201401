/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

// Calling some librarys
#include "dao.h"

#define WRITE 	"w"
#define READ 	"r"

/**************************************************************************************/
/**
 * defining some constants
 */
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

unsigned int id; 

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

// generic functions
void executionTime();
void openFile();
void removeFile();
void createEntry();
int getInsertPosition();
int getInsertQuantity();
void countFileLines();
void printEntries();

/**************************************************************************************/
/**
 * Generic functions
 */
void executionTime() {
	double duration;

	// calc time elapsed
	duration = (double) (time_end - time_start) / CLOCKS_PER_SEC;

	// print elapsed time
	printf("\n[dao.executionTime] - This function was running for %.2lf seconds", duration);
	return 0;
}

FILE openFile() {
	if (fp = fopen(filename, WRITE) == NULL) {
		printf("\n[dao.openFile] Error while creating file!");		
	}

	return fp;
}

void removeFile() {
	if (remove(fp) == 0) {
		printf("\n[dao.removeFile] File deleted!");
	} else {
		printf("\n[dao.removeFile] Error while deleting file!");
	}
}

void createEntry() {
	dao.id() = id;
	dao.data() = (rand() % 10);
}

int getInsertPosition() {

	int position, status = 0, line;

	do {
		printf("\n[dao.getInsertPosition] Where it will be included? (1) start, (2) middle, and I'll selecte it, (3) end of file");
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
					case 0:
						printf("\n[dao.getInsertPosition] File is empty. You dont need to worry about it.");
						status = 1;
						line = -1;
						break;
					default: 
						printf("\n[dao.getInsertPosition] This file have %d lines. Select where it will be included." qtd_total_lines);
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
				printf("\n[dao.getInsertPosition] Please, select one of given options.", );
				status = 0;
			break;
		}
	} while (status != 1);

	return line;
}

int getInsertQuantity() {

	int quantity, status = 0;

	do {
		printf("\n[dao.getInsertQuantity] How much entries do you want to include at file?");
		scanf("%d", &quantity);

		if (quantity <= 0) {
			status = 1;
		} else {
			status = 0;
		}

	} while (status != 1);
}

void countFileLines() {
	printf("\n[dao.countFileLines] Reading file to count lines, please wait...");

	long temp = 0;

    if ((fp = fopen(filename, READ)) == NULL) {
        printf("[dao.countFileLines] File not found!");
        return 0;

    } else {
        while (1) {
            fread(&dao, sizeof(DAO),1,fp);

            if (feof(fp)) break;
            temp++;
        }
        fclose(fp);
    }

    qtd_file_lines = temp;
}

void printEntries(DAO* block, int quantity) {

	do {

	} while ()

}

/**************************************************************************************/
void saveOneEntry(int position) {
	saveMultipleEntries(position, 1);
}

void saveMultipleEntries(int position, int quantity) {

	DAO* block;

	time_start = time();

	fp = openFile();

	switch (position) {
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
			fseek(fp, dao, line);
		break;
	}

	for (int i = 1; i == quantity; i ++) {
		createEntry();
		block = malloc (DAO dao);
	}

	// write in the file
	if (!fwrite(block, sizeof(dao), quantity, fp)) {
		printf("\n[dao.saveOneEntry] - Error while saving data!");
		exit(0);
	}

	free(block);
	free(dao);
	fclose(fp);

	time_end = time();
	executionTime();

	printf("\n[dao.saveOneEntry] - File updated with success with %s new entry(ies)!" quantity);
}

/**************************************************************************************/
DAO* getOneEntry(int start) {
	getMultipleEntries(start, 1);
}

DAO* getMultipleEntries(int start, int quantity) {
	
	DAO* block;

	time_start = time();

	fp = openFile();

	fseek(fp, dao, start);

	for (int i = 0; i <= quantity; i++) {
		dao = (fread(dao, quantity, sizeof(DAO), fp));
		block = malloc(DAO dao);
	}

	fclose(fp);

	time_end = time();
	executionTime();

	printf("\n[dao.getMultipleEntries] Success! %d entry(ies) successfully retrieved!" quantity);

	return block;
}

/**************************************************************************************/