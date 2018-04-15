
#include <avr/io.h>
//ATMEGA32
# define F_CPU 8000000UL

# define _LCD_LIB_

#include "D:\GitHub\LCD-Lib-Cplusplus\Proteus Design\LIB\CharacterLCD.h"
#include "D:\GitHub\LCD-Lib-Cplusplus\Proteus Design\LIB\CharacterLCD.cpp"

const uint8_t LCDwelcomeln2[] PROGMEM="_LCD_LIB_\0";

const uint8_t LCDwelcomeln3[] PROGMEM=" Loading ... \0";

Character_LCD LCD1;





	
	


int main(void)
{
	////////////////
		_delay_ms(100);
		// Register Summary
		// Peripheral Module Address Map
		
		LCD1.SetRSPin (ADD(PORTA),ADD(DDRA),0);
		LCD1.SetRWPin (ADD(PORTA),ADD(DDRA),1);
		LCD1.SetEPin  (ADD(PORTA),ADD(DDRA),7);
		LCD1.SetD4Pin (ADD(PORTA),ADD(DDRA),3);
		LCD1.SetD5Pin (ADD(PORTA),ADD(DDRA),4);
		LCD1.SetD6Pin (ADD(PORTA),ADD(DDRA),5);
		LCD1.SetD7Pin (ADD(PORTA),ADD(DDRA),6);
		LCD1.Init();
		
	
	
	////////////////////
	const uint8_t LCDwelcome[] PROGMEM="wefwefwef\0";
	char aa =10 ;
	uint8_t a[3] = {90,51,80} ;
	while (1)
	{
		LCD1.Clr();
		LCD1.Printf("1001100110011001",0,0,aa);
		 _delay_ms(1000);
		 LCD1.Clr();
		 //LCD1.GotoXY(1,1);LCD1.SendChar(20);
		 LCD1.SendString_V(a,3);
		 //LCD1.SendString("Hello Word !  ",1,1);
		 		 _delay_ms(1000);

	};
}