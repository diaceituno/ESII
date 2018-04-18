#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <stdbool.h>

#include "lcd.h"

#include "../i2c/i2cmaster.h"

void lcd_init(){
	i2c_init();
	_delay_ms(20);
	i2c_start(LCD_ADRESS << 1);	// 8-Bit Adresse ist anzugeben, Write -> RW = 0
	i2c_write(0x00);
	i2c_stop();
	_delay_ms(16);  //-  Wait for more than 15ms after VDD rises to 4.5V

	  lcd_write_command(LCD_8BIT);  //-  Set interface to 8-bit
	  lcd_write_command(LCD_4BIT);
	  lcd_write_command(LCD_4BIT_SET);  //Set für 4Bit-Mode: 2 lines, 5*8 Punktmatrix
	  lcd_write_command(LCD_ON);  		//Display on, cursor and cursor blink off
	  lcd_write_command(LCD_ENTRY);  	//Increment cursor (shift cursor to right)
	  lcd_write_command(LCD_CLEAR); 	//Display löschen
	  _delay_ms(20);
}
void lcd_write_command(unsigned char command)
{

	uint8_t port = (command & 0xf0)+EN;
	  i2c_start(LCD_ADRESS << 1);
	  i2c_write(port);
	  port &= ~EN;
	  i2c_write(port);

	  port = (command << 4)+EN;
	  i2c_write(port);
	  port &= ~EN;
	  i2c_write(port);
	  i2c_stop();
}
void lcd_putchar (unsigned char character)
{

	uint8_t port = (character & 0xf0)+RS+EN;
	  i2c_start(LCD_ADRESS << 1);
	  i2c_write(port);
	  port &= ~EN;
	  i2c_write(port);

	  port = (character << 4)+RS+EN;
	  i2c_write(port);
	  port &= ~EN;
	  i2c_write(port);
	  i2c_stop();
}
void lcd_putstring(char *string)
{
	unsigned char i = 0;
	while(string[i] != 0x00)
	{
		if(i==16) lcd_nextline();
		lcd_putchar(string[i]);
		i++;
	}
}
bool lcd_goto_position(unsigned int line, unsigned int row)
{
	if(line>LCD_LINES) return false;
	if(row>16) return false;
	if((row==0)||(line == 0)) return false;
	if(line==1)
	{
		lcd_write_command(LCD_LINE1+row-1);
	}
	else if(line==2)
	{
		lcd_write_command(LCD_LINE2+row-1);
	}
	return true;
}
void lcd_nextline()
{
	lcd_write_command(LCD_LINE2);
}
