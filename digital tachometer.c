/*
 * digital_techometer.c
 *
 * Created: 20-Nov-14 11:08:20 PM
 *  Author: ashish
 */ 



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

uint16_t count=0;



void lcd_puti(int value);

int main(void)
{
    uint16_t RPM;
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	lcd_puts("    welcome");
	_delay_ms(500);
	
	 
	MCUCSR=(1<<6);
	GICR=(1<<5);
	
	
  while(1)
  {	
	sei();
    _delay_ms(1000);
	cli();
	lcd_clrscr();
	lcd_puts("ROTATION IN RPM");
	lcd_gotoxy(0,1);
	if(count==0) lcd_puts("NO ROTATION");
    else
	{
		
		RPM=count*60UL;
		lcd_puti(RPM);
	}	
	count=0;
  }

}

void lcd_puti(int value)
{
	char buff[10];
	itoa(value,buff,10);
	lcd_puts(buff);
}

ISR(INT2_vect)
{
	++count;
}