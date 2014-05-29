/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Wesklei Migliorini
 */

#ifndef _utils_h
#define _utils_h

#define boolean int
#define true 0;
#define false 1;

boolean cmpChar(char *first, char *second);
boolean cmpInt(int first, int second);
boolean cmpDate(pDATE first, pDATE second);
int cmpEncapsulate(void *p1, void *p2, void *typeCmp);

#endif
