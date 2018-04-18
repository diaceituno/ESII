/*
 Created by none other than Serhii Volovyk, Sebastian Werner ...

 LCD-Bibliothek für die Ansteuerung des LCD-Displayes 162A über den I2C BUs mit dem PCF8574 I/O Expander.
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include <stdbool.h>
//--------------------------------------------------------------------
/*
 Default Adresse von PCF8574 I/O Expander
 */
#define LCD_ADRESS 0x27
//--------------------------------------------------------------------


//--------------------------------------------------------------------
/*
 Verdrahtung:
_______________________________________
 I/O Expander |P7|P6|P5|P4|P3|P2|P1|P0 |
---------------------------------------|
LCD Steuerung |D7|D6|D5|D4|bl|E |RW|RS |
_______________________________________|
bl : nicht verdratheter Pin
RS-Register Select:  Isrtruction Register(IR), Data Register(DR) 0/1
RW-Read/Write  1/0
E-Enable
 */
#define RS  (1 << 0)
#define EN  (1 << 2)
#define BL  (1 << 3)
//--------------------------------------------------------------------


//--------------------------------------------------------------------
/*
 LCD-Befehle für die 4BIT Ansteuerung:
 */
#define LCD_CLEAR  		0x01	//Display löschen
#define LCD_HOME  		0x02	//Auf erste Zeile und Spalte zurückkehren
#define LCD_8BIT 		0x33	//Doppelte Initialisierung von 8Bit:  0x03 beim high nibble bits und 0x03 beim low nibble bits
#define LCD_4BIT 		0x32	//Zusammen mit LCD_8BIT(0x33) wird hier zum dritten mal 8Bit Initialisierung gemacht: 0x03 beim high nibble bits. Und ein mal 4Bit Initzialisierung: 0x02 beim low nibble bits
#define LCD_4BIT_SET 	0x28	//Set für 4Bit-Mode: 2 lines, 5*8 Punktmatrix
#define LCD_ON			0x0C	//Display on cursor and cursor blink off
#define LCD_ENTRY		0x06	//Increment cursor (shift cursor to right)
#define LCD_LINE1       0x80	//Erste Zeile, erste Spalte
#define LCD_LINE2		0xC0	//Zweite Zeile, erste Spalte
#define LCD_LINES		2		//Anzahl von Zeilen des LCD-Displays
//--------------------------------------------------------------------


//--------------------------------------------------------------------
void lcd_init();
void lcd_write_command(unsigned char command);
void lcd_write_data(unsigned char character);
void lcd_putstring(char *string);
bool lcd_goto_position(unsigned int line,unsigned int row);
void lcd_nextline();

//--------------------------------------------------------------------
#endif /* LCD_LCD_H_ */
