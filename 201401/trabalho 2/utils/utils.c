/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Weskley Migliorini
 */

// Calling some librarys
#include "../main.h"

int cmpChar(char *first, char *second)
{
	if(first && second){

		return strcmp(first,second);
	}
}

int cmpInt(int *first, int *second)
{
	if(first && second){

		if( *first == *second)
		{
			return 0;
		}
		if( *first < *second )
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}

int cmpDate(pDATE first, pDATE second)
{
	if(first && second)
	{
		int day1,day2,month1,month2,year1,year2;

		year1 = first->ano;
		year2 = second->ano;

		if( year1 == year2)
		{
			month1 = first->mes;
			month2 = second->mes;

			if( month1 == month2)
			{
				day1 = first->dia;
				day2 = second->dia;

				if( day1 == day2)
				{
					return 0;
				}
				else if ( day1 < day2)
				{
					return -1;
				}
				else
				{
					return 1;
				}
			}
			else if(month1 < month2)
			{
				return -1;
			}
			else 
			{
				return 1;
			}
		}
		else if(year1 < year2)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}


