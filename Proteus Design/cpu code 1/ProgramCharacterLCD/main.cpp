
#include <avr/io.h>

# define _AtmelStudio_com_

#include "D:\GitHub\LCD-Lib-Cplusplus\Proteus Design\LIB\CharacterLCD.h"
#include "D:\GitHub\LCD-Lib-Cplusplus\Proteus Design\LIB\CharacterLCD.cpp"

const uint8_t LCDwelcome[] PROGMEM="AtmelStudio.com\0";

Character_LCD LCD1;






int main(void)
{
	char aa =10 ;
	_delay_ms(100);
	LCD1.Init();
	LCD1.Clr();
	LCD1.CopyString(LCDwelcome, 0, 0);
	_delay_ms(2000);
	
	LCD1.Printf("Hi %d",0,1,aa);
	while (1)
	{

		
	};
}