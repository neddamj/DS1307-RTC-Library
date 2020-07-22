/*
 * lcd.h
 *
 * Created: 11/26/2014 11:27:53 AM
 *  Author: Lindon
 */ 

#ifndef LCD_H_
#define LCD_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define	LCD_PRT	PORTA				//LCD DATA PORT
#define	LCD_DDR	DDRA				//LCD DATA DDR
#define	LCD_PIN	PINA				//LCD DATA PIN
#define	LCD_RS	PA1					//LCD RS
#define	LCD_RW	PA2					//LCD RW
#define LCD_EN	PA3					//LCD EN

void lcdCommand(unsigned char);
void lcdData(unsigned char);
void lcd_init();
void lcd_gotoxy(unsigned char, unsigned char );
void lcd_print(char *);
void clear_lcd();
unsigned char GetKey(void);
void CopyStringtoLCD(const char*);

#endif /* LCD_H_ */
