
#include <HeaderLibraryCharacterLCD.h>

# ifdef _AtmelStudio_com_

const uint8_t LcdCustomChar[] PROGMEM=//define 8 custom LCD chars
{
	0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, // 0. 0/5 full progress block
	0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, // 1. 1/5 full progress block
	0x00, 0x1F, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x00, // 2. 2/5 full progress block
	0x00, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x1F, 0x00, // 3. 3/5 full progress block
	0x00, 0x1F, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x00, // 4. 4/5 full progress block
	0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00, // 5. 5/5 full progress block
	0x03, 0x07, 0x0F, 0x1F, 0x0F, 0x07, 0x03, 0x00, // 6. rewind arrow
	0x18, 0x1C, 0xFE, 0x7F, 0xFE, 0x1C, 0x18, 0x00  // 7. fast-forward arrow
};

const uint8_t LCD_Big_Number[] PROGMEM=//define 8 custom LCD chars
{
	0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, // 0. upper line char
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, // 1. lower line char
	0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, // 2. both line char
	0x00, 0x00, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, // 3. large colon left char
	0x00, 0x00, 0x10, 0x18, 0x18, 0x10, 0x00, 0x00, // 4. large colon right char
	0x1F, 0x00, 0x1F, 0x00, 0x10, 0x00, 0x1F, 0x00, // 5. up char
	0x10, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x1F, 0x00, // 6. rewind arrow
	0x1F, 0x00, 0x10, 0x00, 0x1F, 0x00, 0x1F, 0x00  // 7. fast-forward arrow
};

#define UpPerLineAddr 0
#define ULC UpPerLineAddr
#define LowerLineAddr 1
#define LLC LowerLineAddr
#define BothLineAddr 2
#define BLC BothLineAddr
#define LargeColonLeftAddr 3
#define LargeColonRightAddr 4
#define XXC 0xFF
#define SSC 0x20
#define UpCharAddr 5
#define DownCharAddr 6

const uint8_t numchar[10][6] PROGMEM =
{
	{
		XXC, ULC, XXC,
		XXC, LLC, XXC,
	},
	{
		ULC, XXC, SSC,
		LLC, XXC, LLC,
	},
	{
		ULC, BLC, XXC,
		XXC, LLC, LLC,
	},
	{
		ULC, BLC, XXC,
		LLC, LLC, XXC,
	},
	{
		XXC, LLC, XXC,
		SSC, SSC, XXC,
	},
	{
		XXC, BLC, ULC,
		LLC, LLC, XXC,
	},
	{
		XXC, BLC, ULC,
		XXC, LLC, XXC,
	},
	{
		ULC, ULC, XXC,
		SSC, SSC, XXC,
	},
	{
		XXC, BLC, XXC,
		XXC, LLC, XXC,
	},
	{
		XXC, BLC, XXC,
		LLC, LLC, XXC,
	}
};

const uint8_t _AtmelStudio_com__[] PROGMEM="AtmelStudio.com\0";

Character_LCD :: Character_LCD ()
{
		RS_PORT = 0x18 ; RS_DDR = 0x17 ; RS_Bit = 1 ;
		RW_PORT = 0x18 ; RW_DDR = 0x17 ; RW_Bit = 2 ;
		E_PORT = 0x18 ; E_DDR = 0x17 ; E_Bit  = 3 ;

		D4_PORT = 0x18 ; D4_DDR = 0x17 ; D4_Bit = 4 ;
		D5_PORT = 0x18 ; D5_DDR = 0x17 ; D5_Bit = 5 ;
		D6_PORT = 0x18 ; D6_DDR = 0x17 ; D6_Bit = 6 ;
		D7_PORT = 0x18 ; D7_DDR = 0x17 ; D7_Bit = 7 ;
}
void Character_LCD :: Clr(void)				//Clears LCD
{
	SendCommand(1<<LCD_CLR);
	_delay_ms(1);
}
void Character_LCD :: Home(void)			//LCD cursor home
{
	SendCommand(1<<LCD_HOME);
	_delay_ms(1);
}
void Character_LCD :: SendString_V(uint8_t* data, uint8_t nBytes)	//Outputs string to LCD
{
	register uint8_t i;
	if (!data) return;
	for(i=0; i<nBytes; i++)
	{
		SendChar(data[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: SendString(char *_String , uint8_t PositionX , uint8_t PositionY)
{
	GotoXY(PositionX,PositionY);
	while(*_String)
	{
		SendChar(*_String++ );	
	}
}
void Character_LCD :: GotoXY(uint8_t x, uint8_t y)	//Cursor to X Y position
{
	register uint8_t DDRAMAddr;
	switch(y)
	{
		case 0: DDRAMAddr = LCD_LINE0_DDRAMADDR+x; break;
		case 1: DDRAMAddr = LCD_LINE1_DDRAMADDR+x; break;
		case 2: DDRAMAddr = LCD_LINE2_DDRAMADDR+x; break;
		case 3: DDRAMAddr = LCD_LINE3_DDRAMADDR+x; break;
		default: DDRAMAddr = LCD_LINE0_DDRAMADDR+x;
	}
	SendCommand(1<<LCD_DDRAM | DDRAMAddr);
	_delay_ms(1);
	
}
void Character_LCD :: VariableDec(uint32_t Number, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[15];
	GotoXY(x,y);
	do
	{
		b=Number%10;
		k[i] = 48 +b;
		Number /= 10;
		i++;
	}
	while (Number != 0);
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableBin(uint32_t Number, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[30];
	GotoXY(x,y);
	
	do
	{
		b=Number%2;
		k[i] = 48 +b;
		Number /= 2;
		i++;
	}
	while (Number != 0);
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableOct(uint32_t Number, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[30];
	GotoXY(x,y);
	do
	{
		b=Number%8;
		k[i] = 48 + b;
		Number /= 8;
		i++;
	}
	while (Number != 0);
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableHex(uint32_t Number, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[30];
	GotoXY(x,y);
	do
	{
		b=Number%16;
		if (b<10)k[i] = 48 + b;
		else k[i] = 87 + b;
		Number /= 16;
		i++;
	}
	while (Number != 0);
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableDec_Length(uint32_t Number, uint8_t length, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[16];
	while(i<16){k[i]=48;i++;}
	i=0;
	GotoXY(x,y);
	do
	{
		b=Number%10;
		k[i] = 48 +b;
		Number /= 10;
		i++;
	}
	while (Number != 0);
	i=length;
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableBin_Length(uint32_t Number, uint8_t length, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[30];
	while(i<16){k[i]=48;i++;}
	i=0;
	GotoXY(x,y);
	
	do
	{
		b=Number%2;
		k[i] = 48 +b;
		Number /= 2;
		i++;
	}
	while (Number != 0);
	i=length;
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableOct_Length(uint32_t Number, uint8_t length, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[30];
	while(i<16){k[i]=48;i++;}
	i=0;
	GotoXY(x,y);
	do
	{
		b=Number%8;
		k[i] = 48 + b;
		Number /= 8;
		i++;
	}
	while (Number != 0);
	i=length;
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: VariableHex_Length(uint32_t Number, uint8_t length, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b;
	int8_t k[30];
	while(i<16){k[i]=48;i++;}
	i=0;
	GotoXY(x,y);
	do
	{
		b=Number%16;
		if (b<10)k[i] = 48 + b;
		else k[i] = 87 + b;
		Number /= 16;
		i++;
	}
	while (Number != 0);
	i=length;
	while (i != 0 )
	{
		i--;
		SendChar(k[i]);
	}
	_delay_ms(1);
}
void Character_LCD :: ShiftLeft(uint8_t n)	//Scrol n of characters Right
{
	for (uint8_t i=0;i<n;i++)
	{
		SendCommand(0x1E);
	}
	_delay_ms(1);
}
void Character_LCD :: ShiftRight(uint8_t n)	//Scrol n of characters Left
{
	for (uint8_t i=0;i<n;i++)
	{
		SendCommand(0x18);
	}
	_delay_ms(1);
}
void Character_LCD :: CursorOn(void) //displays LCD cursor
{
	SendCommand(0x0E);
	_delay_ms(1);
}
void Character_LCD :: CursorOnBlink(void)	//displays LCD blinking cursor
{
	SendCommand(0x0F);
	_delay_ms(1);
}
void Character_LCD :: CursorOFF(void)	//turns OFF cursor
{
	SendCommand(0x0C);
	_delay_ms(1);
}
void Character_LCD :: Blank(void)		//blanks LCD
{
	SendCommand(0x08);
	_delay_ms(1);
}
void Character_LCD :: Visible(void)		//Shows LCD
{
	SendCommand(0x0C);
	_delay_ms(1);
}
void Character_LCD :: CursorLeft(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i=0;i<n;i++)
	{
		SendCommand(0x10);
	}
	_delay_ms(1);
}
void Character_LCD :: CursorRight(uint8_t n)	//Moves cursor by n poisitions left
{
	for (uint8_t i=0;i<n;i++)
	{
		SendCommand(0x14);
	}
	_delay_ms(1);
}
void Character_LCD :: SendChar(uint8_t ch)		//Sends Char to LCD
{
	if ((ch&0b00010000)==0)
	_SFR_IO8(D4_PORT) &= ~(1<<D4_Bit) ;
	else
	_SFR_IO8(D4_PORT) |= 1<<D4_Bit ;
	if ((ch&0b00100000)==0)
	_SFR_IO8(D5_PORT) &= ~(1<<D5_Bit) ;
	else
	_SFR_IO8(D5_PORT) |= 1<<D5_Bit ;
	if ((ch&0b01000000)==0)
	_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;
	else
	_SFR_IO8(D6_PORT) |= 1<<D6_Bit ;
	if ((ch&0b10000000)==0)
	_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	else
	_SFR_IO8(D7_PORT) |= 1<<D7_Bit ;
	
	_SFR_IO8(RS_PORT)|=1<<RS_Bit;
	_SFR_IO8(E_PORT) |= 1<<E_Bit;
	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	_SFR_IO8(RS_PORT)&=~(1<<RS_Bit);
	_delay_ms(1);
	
	if ((ch&0b00000001)==0)
	_SFR_IO8(D4_PORT) &= ~(1<<D4_Bit) ;
	else
	_SFR_IO8(D4_PORT) |= 1<<D4_Bit ;
	if ((ch&0b00000010)==0)
	_SFR_IO8(D5_PORT) &= ~(1<<D5_Bit) ;
	else
	_SFR_IO8(D5_PORT) |= 1<<D5_Bit ;
	if ((ch&0b00000100)==0)
	_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;
	else
	_SFR_IO8(D6_PORT) |= 1<<D6_Bit ;
	if ((ch&0b00001000)==0)
	_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	else
	_SFR_IO8(D7_PORT) |= 1<<D7_Bit ;
	
	_SFR_IO8(RS_PORT)|=1<<RS_Bit;
	_SFR_IO8(E_PORT)|=1<<E_Bit;
	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	_SFR_IO8(RS_PORT)&=~(1<<RS_Bit);
	_delay_ms(1);
}
void Character_LCD :: SendCommand(uint8_t cmd)	//Sends Command to LCD
{
	if ((cmd&0b00010000)==0)_SFR_IO8(D4_PORT) &= ~(1<<D4_Bit) ;
	else _SFR_IO8(D4_PORT) |= 1<<D4_Bit ;
	if ((cmd&0b00100000)==0)_SFR_IO8(D5_PORT) &= ~(1<<D5_Bit) ;
	else _SFR_IO8(D5_PORT) |= 1<<D5_Bit ;
	if ((cmd&0b01000000)==0)_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;
	else _SFR_IO8(D6_PORT) |= 1<<D6_Bit ;
	if ((cmd&0b10000000)==0)_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	else _SFR_IO8(D7_PORT) |= 1<<D7_Bit ;
	
	_SFR_IO8(E_PORT)|=1<<E_Bit;
	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	_delay_ms(1);

	if ((cmd&0b00000001)==0)_SFR_IO8(D4_PORT) &= ~(1<<D4_Bit) ;
	else _SFR_IO8(D4_PORT) |= 1<<D4_Bit ;
	if ((cmd&0b00000010)==0)_SFR_IO8(D5_PORT) &= ~(1<<D5_Bit) ;
	else _SFR_IO8(D5_PORT) |= 1<<D5_Bit ;
	if ((cmd&0b00000100)==0)_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;
	else _SFR_IO8(D6_PORT) |= 1<<D6_Bit ;
	if ((cmd&0b00001000)==0)_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	else _SFR_IO8(D7_PORT) |= 1<<D7_Bit ;
	
	_SFR_IO8(E_PORT)|=1<<E_Bit;
	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	_delay_ms(1);
}
void Character_LCD :: Definechar(const uint8_t *pc,uint8_t char_code){
	uint8_t a = 0 , pcc = 0 ;
	uint16_t i;
	//a=(char_code<<3)|0x40;
	a=64+(char_code*8);
	for (i=0; i<9; i++){
		pcc=pgm_read_byte(&pc[i]);
		
		SendCommand(a);a++;
		SendChar(pcc);
	}
	_delay_ms(1);
}
void Character_LCD :: Init(uint8_t Mode)//Initializes LCD
{
	uint8_t chn ;
	_delay_ms(15);

	_SFR_IO8(D4_PORT) &= ~(1<<D4_Bit) ;_SFR_IO8(D5_PORT) &= ~(1<<D5_Bit) ;_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	_SFR_IO8(E_PORT) &= ~(1<<E_Bit);
	_SFR_IO8(D4_DDR) |= 1<<D4_Bit ;_SFR_IO8(D5_DDR) |= 1<<D5_Bit ;_SFR_IO8(D6_DDR) |= 1<<D6_Bit ;_SFR_IO8(D7_DDR) |= 1<<D7_Bit ;
	_SFR_IO8(E_DDR)|=(1<<E_Bit);
	_SFR_IO8(RS_DDR)|=(1<<RS_Bit);_SFR_IO8(RW_DDR)|=(1<<RW_Bit);
	_SFR_IO8(D4_PORT) |= 1<<D4_Bit ;_SFR_IO8(D5_PORT) |= 1<<D5_Bit ;_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	_SFR_IO8(E_PORT)|=(1<<E_Bit);
	_SFR_IO8(RS_PORT) &= ~(1<<RS_Bit);_SFR_IO8(RW_PORT) &= ~(1<<RW_Bit);
	
	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	
	_delay_ms(1);
	_SFR_IO8(D4_PORT) |= 1<<D4_Bit ;_SFR_IO8(D5_PORT) |= 1<<D5_Bit ;_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	_SFR_IO8(E_PORT)|=(1<<E_Bit);
	_SFR_IO8(RS_PORT) &= ~(1<<RS_Bit);_SFR_IO8(RW_PORT) &= ~(1<<RW_Bit);
	
	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	
	_delay_ms(1);
	_SFR_IO8(D4_PORT) &= ~(1<<D4_Bit) ;_SFR_IO8(D5_PORT) |= 1<<D5_Bit ;_SFR_IO8(D6_PORT) &= ~(1<<D6_Bit) ;_SFR_IO8(D7_PORT) &= ~(1<<D7_Bit) ;
	
	_SFR_IO8(E_PORT)|=(1<<E_Bit);
	_SFR_IO8(RS_PORT) &= ~(1<<RS_Bit);_SFR_IO8(RW_PORT) &= ~(1<<RW_Bit);


	_delay_ms(1);
	_SFR_IO8(E_PORT)&=~(1<<E_Bit);
	_delay_ms(1);
	SendCommand(40);
	SendCommand(12);
	if (Mode == Big_Number_Mode )
	{
		chn=0;
		while(chn<8)
		{
			
			Definechar((LCD_Big_Number+(chn*8)),chn);
			chn++;
		}
	}
	else if (Mode == ProgressBar_Mode )
	{
		chn=0;
		while(chn<8)
		{
		
			Definechar((LcdCustomChar+(chn*8)),chn);
			chn++;
		}
	}
	CopyString(_AtmelStudio_com__, 0, 0);
	_delay_ms(1000);
}
void Character_LCD :: CopyString(const uint8_t *FlashLoc, uint8_t x, uint8_t y)
{
	uint8_t i;
	GotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		SendChar((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
	_delay_ms(1);
}

void Character_LCD :: ProgressBar(uint8_t progress, uint8_t maxprogress, uint8_t length,uint8_t x, uint8_t y)
{
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t c;
	GotoXY(x,y);
	pixelprogress = ((progress*(length*PROGRESSPIXELS_PER_CHAR))/maxprogress);
	for(i=0; i<length; i++)
	{
		if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)+5) > pixelprogress )
		if( ((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)) > pixelprogress )
		c = 0;
		else
		c = pixelprogress % PROGRESSPIXELS_PER_CHAR;
		else
		c = 5;
		
		
		SendChar(c);
	}
	_delay_ms(1);
}

void Character_LCD :: BigNumber(uint8_t Number, uint8_t x , uint8_t y)
{

	GotoXY(x,y);
	if (Number == 0 )
	{
		SendChar (XXC);
		SendChar (ULC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (XXC);
		SendChar (LLC);
		SendChar (XXC);
	}
	else if (Number == 1 )
	{
		SendChar (ULC);
		SendChar (XXC);
		SendChar (SSC);
		GotoXY(x,y+1);
		SendChar (LLC);
		SendChar (XXC);
		SendChar (LLC);
	}
	
	else if (Number == 2 )
	{
		SendChar (ULC);
		SendChar (BLC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (XXC);
		SendChar (LLC);
		SendChar (LLC);
	}
	else if (Number == 3 )
	{
		SendChar (ULC);
		SendChar (BLC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (LLC);
		SendChar (LLC);
		SendChar (XXC);
	}
	else if (Number == 4 )
	{
		SendChar (XXC);
		SendChar (LLC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (SSC);
		SendChar (SSC);
		SendChar (XXC);
	}
	else if (Number == 5 )
	{
		SendChar (XXC);
		SendChar (BLC);
		SendChar (ULC);
		GotoXY(x,y+1);
		SendChar (LLC);
		SendChar (LLC);
		SendChar (XXC);
	}
	else if (Number == 6 )
	{
		SendChar (XXC);
		SendChar (BLC);
		SendChar (ULC);
		GotoXY(x,y+1);
		SendChar (XXC);
		SendChar (LLC);
		SendChar (XXC);
	}
	else if (Number == 7 )
	{
		SendChar (ULC);
		SendChar (ULC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (SSC);
		SendChar (SSC);
		SendChar (XXC);
	}

	else if (Number == 8 )
	{
		SendChar (XXC);
		SendChar (BLC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (XXC);
		SendChar (LLC);
		SendChar (XXC);
	}

	else if (Number == 9 )
	{
		SendChar (XXC);
		SendChar (BLC);
		SendChar (XXC);
		GotoXY(x,y+1);
		SendChar (LLC);
		SendChar (LLC);
		SendChar (XXC);
	}

}

void Character_LCD :: BigVariable(uint32_t Number, uint8_t x, uint8_t y)
{
	uint8_t i=0;
	uint8_t b,x1;
	uint8_t k[15];
	x1 = x ;
	do
	{
		b=Number%10;
		k[i] = b;
		Number /= 10;
		i++;
	}
	while (Number != 0);
	while (i != 0 )
	{
		i--;
		BigNumber(k[i],x1,y);
		x1 = x1 + 4 ;
	}
	_delay_ms(1);
}


# endif