
#include "../../main.h"

void fDataWrite(FILE* pFile, pDATA pData) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fwrite(pData, sizeof (DATA), 1, pFile);
    }
}

void fDataOverWrite(FILE* pFile, pDATA pData, int position) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fseek(pFile, sizeof (DATA) * position, SEEK_SET);
        fDataWrite(pFile, pData);
    }
}

void fDataRead(FILE* pFile, pDATA pData) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fread(pData, sizeof (DATA), 1, pFile);
    }
}

void fDataReadPosition(FILE* pFile, pDATA pData, int position) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fseek(pFile, sizeof (DATA) * position, SEEK_SET);
        fDataRead(pFile, pData);
    }
}

/**
 * Write in block. This way always append in file
 */
void fDataWriteBlock(FILE* pFile, ppDATA ppData, int quanty) {
    int i;
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fwrite((*ppData), sizeof (DATA) * quanty, 1, pFile);
    }
}

long fsize(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0 ) {
        return st.st_size; 
    }
    return -1;
}

void fDataReadAll(FILE* pFile, ppDATA ppData) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        unsigned int i, size = (fsize(FULLFILEPATH) / sizeof (DATA));
    
        ppData = (ppDATA) malloc(sizeof (DATA) * size);
        for (i = 0; i < size; i++) {
            ppData[i] = (pDATA) malloc(sizeof (DATA));
        }
        
        // read all in one block
        fread((*ppData), size, 1, pFile);
    } 
}

void fDataReadBlock(FILE* pFile, ppDATA ppData, int quanty, int position) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fseek(pFile, position * (sizeof (DATA) * quanty), SEEK_SET);
        fread((*ppData), sizeof (DATA) * quanty, 1, pFile);
    }
}

/**
 * Write in block. This way always append in file
 */
void fIndexTableWriteBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty) {
    int i;

    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fwrite((*ppIndex_Table), sizeof (INDEX_TABLE) * quanty, 1, pFile);
    }
}

void fIndexTableReadBlock(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int quanty, int position) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fseek(pFile, position * (sizeof (INDEX_TABLE) * quanty), SEEK_SET);
        fread((*ppIndex_Table), sizeof (INDEX_TABLE) * quanty, 1, pFile);
    }
}

/**
 * Write in block. This way always append in file
 */
void fIndexTableOverWrite(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int position) {
    int i;

    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fseek(pFile, sizeof (INDEX_TABLE) * position, SEEK_SET);
        fwrite(ppIndex_Table, sizeof (INDEX_TABLE), 1, pFile);
    }
}

void fIndexTableReadPosition(FILE* pFile, ppINDEX_TABLE ppIndex_Table, int position) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fseek(pFile, position * (sizeof (INDEX_TABLE)), SEEK_SET);
        fread((*ppIndex_Table), sizeof (INDEX_TABLE), 1, pFile);

    }
}

void fileGenericProblemError() {
    perror("\nError operating file!\n");
    exit(1);
}

void fDataWriteHash(FILE* pFile, ppHASH_TABLE ppHash_table, unsigned int size) {
    if (pFile == NULL) {
        fileGenericProblemError();
    } else {
        fwrite(ppHash_table, (sizeof (HASH_TABLE) * size), 1, pFile);
    }
}