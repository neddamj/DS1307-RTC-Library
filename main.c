/*
 * ds1307.c
 *
 * Created: 7/6/2020 5:08:24 PM
 * Author : Jordan Madden
 */ 

#include <avr/io.h>
#include "ds1307.h"

int main(void)
{
	DDRC = 0x00;
	ds1307_init();					

	while(1)
	{
		ds1307_display_time(1,1);		//Display the time starting at the 1st row, 1st column
		ds1307_display_date(1,2);		//Display the date starting at the 2nd row, 1st column
	}
}



