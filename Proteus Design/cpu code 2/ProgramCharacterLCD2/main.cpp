
#include <avr/io.h>

# define F_CPU 8000000UL

# define _AtmelStudio_com_

#include "D:\GitHub\LCD-Lib-Cplusplus\Proteus Design\LIB\CharacterLCD.h"
#include "D:\GitHub\LCD-Lib-Cplusplus\Proteus Design\LIB\CharacterLCD.cpp"

const uint8_t LCDwelcomeln2[] PROGMEM="AtmelStudio .com\0";

const uint8_t LCDwelcomeln3[] PROGMEM=" Loading ... \0";



Character_LCD LCD1;

void Welcome(void)
{
_delay_ms(100);
	// Register Summary
	// Peripheral Module Address Map
	LCD1.SetRSPin (ADD(PORTA),ADD(DDRA),0);
	LCD1.SetRWPin (ADD(PORTA),ADD(DDRA),1);
	LCD1.SetEPin  (ADD(PORTA),ADD(DDRA),2);
	LCD1.SetD4Pin (ADD(PORTA),ADD(DDRA),3);
	LCD1.SetD5Pin (ADD(PORTA),ADD(DDRA),4);
	LCD1.SetD6Pin (ADD(PORTA),ADD(DDRA),5);
	LCD1.SetD7Pin (ADD(PORTA),ADD(DDRA),6);

	LCD1.Init(ProgressBar_Mode);
	
	LCD1.Clr();
	
	LCD1.CopyString(LCDwelcomeln3, 0, 0);

	
	LCD1.GotoXY(12,1);LCD1.SendChar(6);
	LCD1.GotoXY(0,1);LCD1.SendChar(7);
	
	for (uint8_t i1 = 0 ; i1 < 31 ; i1 ++ )
	{
		LCD1.ProgressBar(i1,30,11,1,1);
		_delay_ms(100);
	}
	LCD1.Clr();
	LCD1.Init(Big_Number_Mode);
	LCD1.BigVariable( 12 , 1, 1);
	LCD1.BigVariable( 30 , 10, 1);
	LCD1.GotoXY(8,1);
	LCD1.SendChar(3);
	LCD1.SendChar(4);
	LCD1.GotoXY(8,2);
	LCD1.SendChar(3);
	LCD1.SendChar(4);
	_delay_ms(2000);
}


int main(void)
{
	uint8_t Counter = 0 ;
	uint8_t a[3] = {90,51,80} ;
	Welcome();
	
	LCD1.Clr();
	
	LCD1.SendString("Hello Word !  ",0,0);
	
	_delay_ms(1000);
	
	LCD1.SendString_V(a,3);
	
	_delay_ms(1000);
	
	LCD1.Clr();
	
	LCD1.SendString("Decimal = ",0,0); LCD1.VariableDec(11,14,0);
	
	LCD1.SendString("Hexadecimal = ",0,1);LCD1.VariableHex(11,14,1);
	
	_delay_ms(2000);
	
	while (1)
	{
		LCD1.Clr();
		
		LCD1.BigVariable( Counter , 4, 0); _delay_ms(300);
		
		Counter ++ ;
		
	};
}