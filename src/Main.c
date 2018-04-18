/*
 * Main.c
 *
 *  Created on: 16 Apr 2018
 *      Author: Diego
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD/lcd.h"

void readData(){

	char data[5] = {0,0,0,0,0};
	char dsum = 0;
	char data1[8],data2[8],data3[8],data4[8],data5[8],sum[8];
	int i;

	//Setting pin 7 as output
	DDRB = (1<<7);

	//pulling voltage down for at least 18ms
	PORTB = (0<<7);
	_delay_us(18000);

	//setting pin 7 as input. pull up resistor to set voltage high
	DDRB = (0<<7);

	//waiting for DHT answer
	while(PINB & (1<<7));

	//waiting while DHT answer LOW
	while(!(PINB & (1<<7)));

	//waiting begin data
	while(PINB & (1<<7));

	//begin receiving 40 bits
	for(i=0;i<40;i++){

		//wait DHT signal high
		while(!(PINB & (1<<7)));

		//wait 30us
		_delay_us(30);

		//If signal high after 30us -> shift left and add 0x01;
		//if signal low after 30us -> shift left
		if(PINB & (1<<7)){
			data[i/8] = (data[i/8]<<1)| (1<<0);
		}else{
			data[i/8] = (data[i/8]<<1);
		}
		while(PINB & (1<<7));
	}

	itoa(data[0],data1,10);
	itoa(data[1],data2,10);
	itoa(data[2],data3,10);
	itoa(data[3],data4,10);
	itoa(data[4],data5,10);
	dsum = data[0] + data[1] + data[2] + data[3];
	itoa(dsum, sum,10);
	if(dsum == data[4]){

	lcd_init();
	lcd_putstring("Humidity:");
	lcd_putstring(data1);
	lcd_putstring(".");
	lcd_putstring(data2);
	lcd_putstring("%");

	lcd_goto_position(2,1);
	lcd_putstring("Temp:");
	lcd_putstring(data3);
	lcd_putstring(".");
	lcd_putstring(data4);
	lcd_putstring("C");
	}else{
		lcd_init();
		lcd_putstring("sum: ");
		lcd_putstring(sum);
		lcd_goto_position(2,1);
		lcd_putstring("sent: ");
		lcd_putstring(data5);
	}
}

int main(){
	while(1){
		DDRD |= (1<<6);
		PORTD |= (1<<6);
		DDRB |= (1<<0);
		PORTB |= (1<<0);
		_delay_ms(1200);
		PORTB &= 0xFE;
		readData();
	}
	return 0;
}
