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
	FILE *fp;

	if (fp = fopen(filename, "wb") == NULL) {
		printf("\nError while creating file!");
		return 0;
	} else {
		return fp;
	}
}

void removeFile(FILE *fp) {
	if (remove(fp) == 0) {
		printf("\nFile %c deleted!", filename);
	} else {
		printf("\nError while deleting file!");
	}
}

/**************************************************************************************/
void saveOneEntry() {

	// get file pointer
	FILE *fp = createFile();

	// identify where will insert that entry
	printf("\nWhere it will be include? (1) start, (2) middle, and I'll selecte it, (3) end of file");

	// generate entry

	// insert entry

	// save entry

	// close file

}


