/*
 * ds1307.c
 *
 * Created: 7/6/2020 5:36:23 PM
 * Author: Jordan Madden
 *
 * This library is intended to simplify the process of interfacing with the DS1307
 * RTC module.
 */ 

#include "ds1307.h"

//Variables to store the date and time from the module
int second, minute, hour, day, date, month, year;

//Variables to display the time on the LCD
char hour_str[3];
char min_str[3];
char sec_str[3];
char day_str[3];
char date_str[3];
char month_str[3];
char year_str[3];

void ds1307_init()
{
	lcd_init();		//Initialize the LCD
	i2c_init();		//Initialize the i2c communication that the device uses
}

void ds1307_clock_write(char _hour, char _minute, char _second)
{
	i2c_start(Device_Write_address);	// Start i2c communication with RTC 
	i2c_write(0);					          	// Write 0 address for second 
	i2c_write(_second);					      // Write second on 00 location
	i2c_write(_minute);				      	// Write minute on 01 location
	i2c_write(_hour);				        	// Write hour on 02 location 
	i2c_stop();					          		// Stop i2c communication 
}

void ds1307_calendar_write(char _day, char _date, char _month, char _year)
{
	i2c_start(Device_Write_address);	// Start i2c communication with RTC 
	i2c_write(3);						          // Write 3 address for day 
	i2c_write(_day);				        	// Write day on 03 location
	i2c_write(_date);				        	// Write date on 04 location 
	i2c_write(_month);      					// Write month on 05 location 
	i2c_write(_year);		        			// Write year on 06 location 
	i2c_stop();				          			// Stop i2c communication 
}

void ds1307_read_clock(char read_clock_address)
{
	i2c_start(Device_Write_address);	// Start i2c communication with RTC 
	i2c_write(read_clock_address);		// Write address to read from
	i2c_start(Device_Read_address);		// Repeated start with device read address 

	second = i2c_read_ack();			// Read second 
	minute = i2c_read_ack();			// Read minute  
	hour = i2c_read_nack();				// Read hour and stop reading  
	i2c_stop();						      	// Stop i2c communication  
}

void ds1307_read_calendar(char read_calendar_address)
{
	i2c_start(Device_Write_address);	//Start i2c communication with RTC
	i2c_write(read_calendar_address);	//Write address to read from
	i2c_start(Device_Read_address);		//Repeated start with devices read address

	day = i2c_read_ack();		  // Read day 
	date = i2c_read_ack();		// Read date 
	month = i2c_read_ack();		// Read month 
	year = i2c_read_nack();		// Read the year and stop reading  
	i2c_stop();					      // Stop i2c communication  
}

//The variables x and y represent the coordinates of the 1st digit to be displayed
void ds1307_display_time(char x, char y)
{
	// Read clock from read location 0
	ds1307_read_clock(0);	

	//Print hours to LCD
	if(hour<10)
	{
		lcd_gotoxy(x,y);
		lcd_print("0");
		lcd_gotoxy((x+1),1);
		itoa(hour, hour_str, 16);
		lcd_print(hour_str);
	}
	if(hour>=0x10)
	{
		lcd_gotoxy(x,y);
		itoa(hour, hour_str, 16);
		lcd_print(hour_str);
	}
	
	lcd_gotoxy((x+2),y);
	lcd_print(":");
	
	//Print minutes to LCD
	if(minute<10)
	{
		lcd_gotoxy((x+3),y);
		lcd_print("0");
		lcd_gotoxy((x+4),y);
		itoa(minute, min_str, 16);
		lcd_print(min_str);
	}
	if(minute>=10)
	{
		lcd_gotoxy((x+3),y);
		itoa(minute, min_str, 16);
		lcd_print(min_str);
	}
	
	lcd_gotoxy((x+5),y);
	lcd_print(":");
	
	//Print seconds to LCD
	if(second<10)
	{
		lcd_gotoxy((x+6),y);
		lcd_print("0");
		lcd_gotoxy((x+7),y);
		itoa(second, sec_str, 16);
		lcd_print(sec_str);
	}
	if(second>=10)
	{
		lcd_gotoxy((x+6),y);
		itoa(second, sec_str, 16);
		lcd_print(sec_str);
	}
}

//The variables x and y represent the coordinates of the 1st digit to be displayed
void ds1307_display_date(char x, char y)
{
	//Read calendar from location 3
	ds1307_read_calendar(3);
	
	//Print date to LCD
	if(date < 10)
	{
		lcd_gotoxy(x,y);
		lcd_print("0");
		lcd_gotoxy((x+1),1);
		itoa(date, date_str, 16);
		lcd_print(date_str);
	}
	if(date >= 10)
	{
		lcd_gotoxy(x,y);
		itoa(date, date_str, 16);
		lcd_print(date_str);
	}
	
	lcd_gotoxy((x+2),y);
	lcd_print("/");
	
	//Print month to LCD
	if(month < 10)
	{
		lcd_gotoxy((x+3),y);
		lcd_print("0");
		lcd_gotoxy((x+4),y);
		itoa(month, month_str, 16);
		lcd_print(month_str);
	}
	if(month>=10)
	{
		lcd_gotoxy((x+3),y);
		itoa(month, month_str, 16);
		lcd_print(month_str);
	}
	
	lcd_gotoxy((x+5),y);
	lcd_print("/");
	
	//Print year to LCD
	if(year < 10)
	{
		lcd_gotoxy((x+6),y);
		lcd_print("0");
		lcd_gotoxy((x+7),y);
		itoa(year, year_str, 16);
		lcd_print(year_str);
	}
	if(year >= 10)
	{
		lcd_gotoxy((x+6),y);
		itoa(year, year_str, 16);
		lcd_print(year_str);
	}
}
