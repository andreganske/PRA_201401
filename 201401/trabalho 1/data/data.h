/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Wesklei Migliorini
 */


#ifndef _data_h
#define _data_h

/** Type of DATA, can be used for genereic
 * type
 * Start in 1
 */
typedef enum DataType{
		TYPE_PARTIDA = 1
	}DataType;

/**
 * File path and name
*/
#define FILEPATH "data_base/"
#define FILENAME "generatedFile.bin"
#define FULLFILEPATH "data_base/generatedFile.bin"

/**
 * Generic use of struct, it's use a void* (pointer of void)
 * and a enum to descripe it's type of DATA
 */
// Define struct
typedef struct DATA{
	unsigned int	id;
	PARTIDA		partida;
	DataType	type;
	int		isDeleted;
}DATA;

typedef struct DATA *pDATA;
typedef struct DATA **ppDATA;

/**
 * Defining functions
 */

// generic functions
void executionTime();
void openFile(FILE** ppFile,char* param);
void closeFile(FILE** ppFile);
long currentSizeInFile(FILE** ppFile);
void printEntries(pDATA pData);

/**
 * Set in second parameter a string representative of DataType
 */
void getStringOfType(DataType type, char* typeOfData);
#endif
