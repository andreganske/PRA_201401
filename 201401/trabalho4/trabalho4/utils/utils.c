/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Wesklei Migliorini
 */

// Calling some librarys
#include "../main.h"

int cmpChar(char *first, char *second)
{
	if(first && second){

		return strcmp(first,second);
	}
}

int cmpInt(int first, int second)
{
	if(first && second){

		if( first == second)
		{
			return 0;
		}
		if( first < second )
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

/**
 * typeCmp:	0,1,4	Char
 * 		3	Int
 * 		2	Date
 **/
int cmpEncapsulate(pDATA p1, pDATA p2, int typeCmp)
{
    
	DATE date1;
	DATE date2;
	int score1;
	int score2;

        if(p1 == NULL && p2 != NULL){
            return 1;
        }
        
        if(p2 == NULL && p1 != NULL){
            return -1;
        }
            
	if(p1 && p2 && typeCmp)
	{
            
		pDATA data1 = (pDATA) p1;
		pDATA data2 = (pDATA) p2;
                
                if(data1->id == 0) return -1;
                if(data2->id == 0) return -1;
                
		int type = typeCmp;

		switch (type){
			case 0:
				return cmpChar(data1->partida.nameTimeA,data2->partida.nameTimeA);
			case 1:
				return cmpChar(data1->partida.nameTimeB,data2->partida.nameTimeB);
			case 4:
				return cmpChar(data1->partida.place,data2->partida.place);
				break;
			case 2:
				date1 = data1->partida.Date;
				date2 = data2->partida.Date;
				return cmpDate(&date1,&date2);
				break;
			case 3:
				score1 = data1->partida.score;
				score2 = data2->partida.score;
				return cmpInt(score1,score2);
				break;
			default:
				
				break;
		}
		
	}else{
            return -1;
        }
            

}

