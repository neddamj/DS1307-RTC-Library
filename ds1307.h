/*
 * ds1307.c
 *
 * Created: 7/6/2020 5:36:23 PM
 * Author: Jordan Madden
 *
 * This library is intended to simplify the process of interfacing with the DS1307
 * RTC module.
 */ 


#ifndef DS1307_H_
#define DS1307_H_

#include <avr/io.h>
#include "i2c_master.h"
#include "lcd.h"

#define Device_Write_address  	0xD0	  // Define RTC DS1307 slave write address 
#define Device_Read_address		0xD1	// Make LSB bit high of slave address for read 

//=========================Function Prototypes==============
void ds1307_init();
void ds1307_clock_write(char, char, char);
void ds1307_calendar_write(char, char, char, char);
void ds1307_read_clock(char);
void ds1307_read_calendar(char);
void ds1307_display_time(char, char);
void ds1307_display_date(char, char);

#endif /* DS1307_H_ */
