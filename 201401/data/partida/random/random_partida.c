/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

// Including some library

#include "../../../main.h"

#ifndef const_chars
#define const_chars

/** Here I will create an array of prefixes to help generate names.
* I am banking on multiplication to ensure a large number of names
* by using 7 prefixes and 20 stems, and 16 suffixes I should be able to
* create about 7 * 20 * 16 = 2240 names out of 312 bytes of data (In my earlier
* example from the forum I used this code to generate male and female names,
* but here I combined them).
*/
const char NamesPrefix[][5] = {
	"", //who said we need to add a prefix?
	"bel", //lets say that means "the good"
	"nar", //"The not so good as Bel"
	"xan", //"The evil"
	"bell", //"the good"
	"natr", //"the neutral/natral"
	"ev", //Man am I original
};

const char NamesSuffix[][5] = {
	"", "us", "ix", "ox", "ith",
	"ath", "um", "ator", "or", "axia",
	"imus", "ais", "itur", "orex", "o",
	"y"
};


const char NamesStems[][10] = {
	"adur", "aes", "anim", "apoll", "imac",
	"educ", "equis", "extr", "guius", "hann",
	"equi", "amora", "hum", "iace", "ille",
	"inept", "iuv", "obe", "ocul", "orbis"
};


const char PlacePrefix[][10] = {
	"city ", //lets say that means "the good"
	"country ", //"The not so good as Bel"
	"stade ", //"The evil"
	"gymnasium ", //"the good"
	"gym ", //"the neutral/natral"
	"Block ", //Man am I original
};

const char PlaceSuffix[][5] = {
	"", "us", "ix", "ox", "ith",
	"ath", "um", "ator", "or", "axia",
	"imus", "ais", "itur", "orex", "o",
	"y"
};


const char PlaceStems[][10] = {
	"adur", "aes", "anim", "apoll", "imac",
	"educ", "equis", "extr", "guius", "hann",
	"equi", "amora", "hum", "iace", "ille",
	"inept", "iuv", "obe", "ocul", "orbis"
};
#endif


/**
 * Generate a random date betewen 01012000-01012014
 */
void randomDate(pDATE date)
{
	date->dia = 1 + rand() % 30;
	date->mes = 1 + rand() % 11;
	date->ano = (1999 + rand() % 14) + 1; 

}

/**
 * Generate random time name
 */
void randomTimeName(char* timeName)
{
	timeName[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(timeName, NamesPrefix[(rand() % 7)]);
	//add the stem...
	strcat(timeName, NamesStems[(rand() % 20)]);
	//add the suffix...
	strcat(timeName, NamesSuffix[(rand() % 16)]);
	//Make the first letter capital...
	timeName[0]=toupper(timeName[0]);
	
}

/**
 * Generate random score from 0 to 10
 */
void randomScore(int* score)
{
	*score = rand() % 10;
}

/**
 * Generate random payiers from 0 to 5000
 */
void randomqtdPayer(int* qtdPayer)
{
	*qtdPayer = rand() % 5000;
}

/**
 * Generate random places name
 */
void randomPlace(char* place)
{
	place[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(place, PlacePrefix[(rand() % 6)]);
	//add the stem...
	char stems[6];
        strcpy(stems,PlaceStems[(rand() % 20)]);
	stems[0] = toupper(stems[0]);
	strcat(place, stems);
	//add the suffix...
	strcat(place, PlaceSuffix[(rand() % 16)]);
	//Make the first letter capital...
	place[0]=toupper(place[0]);
}

/**
 * Generate random PARTIDA using others random metods
 */
void randomPartida(ppPARTIDA ppPartida)
{
	randomDate(&(*ppPartida)->Date);
	randomTimeName((*ppPartida)->nameTimeA);
	randomTimeName((*ppPartida)->nameTimeB);
	randomScore(&(*ppPartida)->score);
	randomqtdPayer(&(*ppPartida)->qtdPayer);
	randomPlace((*ppPartida)->place);
}
