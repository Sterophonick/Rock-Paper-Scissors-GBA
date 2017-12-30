#include <agb_lib.h>
#include "hands.h"

int score, cpu, boi,stf;
int sram, handrand, loop, hand,blah,x,y,i,feel_brave,yo,yt;
u16 offset = 0;
u16 srmdata;
char* buf[256];

int main()
{
	vsync
	fillscreen3(0xFFFF);
	SetMode(MODE_3|BG2_ENABLE|OBJ_MAP_1D|OBJ_ENABLE);
	handrand=LoadInt(offset);
	if(handrand==0)
	{
		SaveInt(offset, 25);
		hardreset();
	}
	scanlines3(0x0000, 0.5);
	fillscreen3(0x0000);
	FadeIn(0);
	loop=1;
	loadSpriteGraphics((void*)handsData, 6144);
	loadSpritePal((void*)handsPalette);
	initSprite(2, SIZE_64, 128);
	sprites[1].attribute0 = COLOR_256 | SQUARE | x;
	sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | y;
	sprites[1].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
	MoveSprite(&sprites[1], 32, 88);
	MoveSprite(&sprites[2], 96, 88);
	CopyOAM();
	SaveInt(0x00000005, cpu + stf);
	cpu=0;
	while(loop==1)
	{
		fillscreen3(0x0000);
		Print(-1, 0, "PREPARING...", RED, BLACK);
		for(i=0;i<handrand;i++)
		{
			cpu = rand()%3+1;
		}
		fillscreen3(0x0000);
		WaitForVblank();
		Sleep(3);
		Print(-1, 0, "ROCK PAPER SCISSORS", RED, BLACK);
		Print(-1, 8, "LEFT FOR ROCK", RED, BLACK);
		Print(-1, 16, "UP FOR PAPER", RED, BLACK);
		Print(-1, 24, "RIGHT FOR SCISSORS", RED, BLACK);
		WaitForVblank();
		Sleep(3);
		while(NOT((keyDown(KEY_UP))OR(keyDown(KEY_LEFT))OR(keyDown(KEY_RIGHT))))
		{
			cpu = rand() % 3 + 1;
		}
		if(keyDown(KEY_LEFT))
		{
			hand=1;
		}
		if(keyDown(KEY_UP))
		{
			hand=2;
		}
		if(keyDown(KEY_RIGHT))
		{
			hand=3;
		}
	sprites[1].attribute0 = COLOR_256 | SQUARE | 32;
	sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | 88;
	sprites[1].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
	sprites[2].attribute0 = COLOR_256 | SQUARE | 96;
	sprites[2].attribute1 = SIZE_64 | 88;
	sprites[2].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd

		for(boi=0;boi<3;boi++)
		{
			MoveSprite(&sprites[1], 32, 98);
			MoveSprite(&sprites[2], 96, 98);
			CopyOAM();
			Sleep(48);
			MoveSprite(&sprites[1], 32, 88);
			MoveSprite(&sprites[2], 96, 88);
			CopyOAM();
			Sleep(48);
		}
		if(cpu==1)
		{
			sprites[2].attribute0 = COLOR_256 | SQUARE | 96;
			sprites[2].attribute1 = SIZE_64 | 88;
			sprites[2].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
		}
		if(cpu==2)
		{
			sprites[2].attribute0 = COLOR_256 | SQUARE | 96;
			sprites[2].attribute1 = SIZE_64 | 88;
			sprites[2].attribute2 = 512 + 0; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
		}
		if(cpu==3)
		{
			sprites[2].attribute0 = COLOR_256 | SQUARE | 96;
			sprites[2].attribute1 = SIZE_64 | 88;
			sprites[2].attribute2 = 512 + 256; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
		}
		if(hand==1)
		{
			sprites[1].attribute0 = COLOR_256 | SQUARE | 32;
			sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | 88;
			sprites[1].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
		}
		if(hand==2)
		{
			sprites[1].attribute0 = COLOR_256 | SQUARE | 32;
			sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | 88;
			sprites[1].attribute2 = 512 + 0; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
		}
		if(hand==3)
		{
			sprites[1].attribute0 = COLOR_256 | SQUARE | 32;
			sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | 88;
			sprites[1].attribute2 = 512 + 256; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
		}
		MoveSprite(&sprites[1], 32, 88);
		MoveSprite(&sprites[2], 96, 88);
		CopyOAM();
		if(((hand==1)AND(cpu==2))OR((hand==3)AND(cpu==1))OR((hand==2)AND(cpu==3)))
		{
			Sleep(255);
			MoveSprite(&sprites[1], 240, 160);
			MoveSprite(&sprites[2], 240, 160);
			CopyOAM();
			SetMode(MODE_3|BG2_ENABLE|OBJ_ENABLE|OBJ_MAP_1D);
			fillscreen3(0x0000);	
			WaitForVblank();
			Sleep(25);
			Print(0, 0, "*CUE THE EXPECTED SONG*", RED, BLACK);
			WaitForVblank();
			Sleep(3);
			sprintf(buf, "GAME OVER! YOU SCORED: %d.", score);
			Print(0, 9, (char*)buf, RED, BLACK);
			WaitForVblank();
			Sleep(3);
			Print(0, 18, "PRESS ANY BUTTON TO RESET.", RED, BLACK);
			Print(0, 152, "GET REKT M80.", 0x0C63, BLACK);
			Sleep(127.5);
			vsync
			while(1)
			{
				CopyOAM();
				if(KEY_ANY_PRESSED)
				{
					asm("swi 0x26");
				}
			}
		} else {
			if(hand==cpu)
			{
				fillscreen3(0x0000);
				WaitForVblank();
				Sleep(8);
				Print(-1, 0, "TIE!", RED, BLACK);	
				while(NOT(keyDown(KEY_A)));
				sprites[2].attribute0 = COLOR_256 | SQUARE | 96;
				sprites[2].attribute1 = SIZE_64 | 88;
				sprites[2].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
				sprites[1].attribute0 = COLOR_256 | SQUARE | 32;
				sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | 88;
				sprites[1].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd

			}else{
				fillscreen3(0x0000);
				WaitForVblank();
				Sleep(8);
				Print(-1, 0, "WOOT!", RED, BLACK);
				score++;	
				while(NOT(keyDown(KEY_A)));
				sprites[2].attribute0 = COLOR_256 | SQUARE | 96;
				sprites[2].attribute1 = SIZE_64 | 88;
				sprites[2].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
				sprites[1].attribute0 = COLOR_256 | SQUARE | 32;
				sprites[1].attribute1 = SIZE_64 | HORIZONTAL_FLIP | 88;
				sprites[1].attribute2 = 512 + 128; // NOTE: mode4 doesn't support the first tiles, so offset of 512 is requirerd
			}	
		}
	}
	
	return 0;
}
