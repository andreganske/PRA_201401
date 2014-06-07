/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Wesklei Migliorini
 */

#ifndef _file_manager_h
#define _file_manager_h

// Including some library
#include "../../main.h"

//Function definition

void fDataWrite(FILE* pFile, pDATA pData);
void fDataOverWrite(FILE* pFile, pDATA pData, int position);
void fDataRead(FILE* pFile, pDATA pData);
void fDataReadPosition(FILE* pFile, pDATA pData, int position);
void fDataWriteBlock(FILE* pFile, ppDATA ppData, int quanty);
void fDataReadBlock(FILE* pFile, ppDATA ppData, int quanty, int position);
void fileGenericProblemError();
void fIndexTableWriteBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty);
void fIndexTableReadBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty, int position);

#endif
