#include "come_on.h"

#define ST_COMMAND	0
#define ST_DATA		1

static int i, j;

void draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x1);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x2);
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, y1);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, y2);

	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 160; i++){
		for(j = 0; j < 128; j++){
			st7586_write(ST_DATA, 0xFF);
		}
	}
}

void draw_walk_a(uint8_t x, uint8_t y) {
static const uint8_t walk_a[] = {
0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 
0x00, 0x00, 0xff, 0xe0, 0xff, 0x00, 
0x00, 0x1f, 0xe0, 0x00, 0x03, 0xe0, 
0x00, 0xfc, 0x00, 0x00, 0x00, 0xe0, 
0x03, 0xe0, 0x00, 0x00, 0x00, 0xfc, 
0x1f, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 
0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0x1f, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0x03, 0xe0, 0x00, 0x00, 0x00, 0xfc, 
0x00, 0xfc, 0x00, 0x00, 0x03, 0xe0, 
0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x1f, 
0x00, 0x00, 0x03, 0xe0, 0x00, 0xff, 
0x00, 0x00, 0x03, 0x00, 0x00, 0xff, 
0x00, 0x00, 0x03, 0x00, 0x00, 0x1c, 
0x00, 0x00, 0x03, 0xe0, 0x00, 0xfc, 
0x00, 0x00, 0xff, 0xfc, 0x00, 0xe0, 
0x00, 0xff, 0x03, 0x1f, 0xff, 0xe0, 
0x03, 0xe0, 0x03, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x1f, 0x00, 0x03, 0x00, 0x00, 0x00, 
0x1c, 0x00, 0x03, 0x00, 0x00, 0x00, 
0xff, 0x00, 0x03, 0xe0, 0x00, 0x00, 
0xff, 0x00, 0x03, 0xe0, 0x00, 0x00, 
0xfc, 0x00, 0x1f, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0x03, 0xe0, 0x00, 
0x00, 0x03, 0xe0, 0x00, 0xe0, 0x00, 
0xff, 0xff, 0x00, 0x00, 0x1c, 0x00, 
0xff, 0x00, 0x00, 0x00, 0x1c, 0x00, 
0x1f, 0x00, 0x00, 0x00, 0x1c, 0x00, 
0x03, 0xe0, 0x00, 0x00, 0x1f, 0x00, 
0x00, 0xfc, 0x00, 0x00, 0x1f, 0xff};

	// (x, y) 좌표에 걷기a 그리기
	x /= 3;
	
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x+5);		// 0~5(18px / 3)
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x9f - y);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x9f - y + 40);		// 0~39(40px)
	
	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 6 * 40; i++){
		st7586_write(ST_DATA, walk_a[i]);
	}
}

void draw_walk_b(uint8_t x, uint8_t y) {
static const uint8_t walk_b[] = {
0x00, 0x00, 0x03, 0xff, 0xe0, 0x00, 
0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 
0x00, 0x1f, 0xe0, 0x00, 0x03, 0xe0, 
0x00, 0xfc, 0x00, 0x00, 0x00, 0xe0, 
0x03, 0xe0, 0x00, 0x00, 0x00, 0xfc, 
0x1f, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 
0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0x1c, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0x1f, 0x00, 0x00, 0x00, 0x00, 0x1c, 
0x03, 0xe0, 0x00, 0x00, 0x00, 0xfc, 
0x00, 0xfc, 0x00, 0x00, 0x03, 0xe0, 
0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0xe3, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0xe3, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0xe3, 0x1f, 0xe0, 0x00, 
0x00, 0x03, 0xff, 0x1f, 0xe0, 0x00, 
0x00, 0x03, 0xff, 0x1f, 0xe0, 0x00, 
0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x1c, 0xe0, 0x00, 0x00, 
0x00, 0x00, 0x1c, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0x1c, 0x00, 0x00, 
0x00, 0x00, 0xe0, 0x1c, 0x00, 0x00, 
0x00, 0x03, 0xe0, 0x1c, 0x00, 0x00, 
0x00, 0x03, 0x00, 0x1c, 0x00, 0x00, 
0x00, 0x03, 0x00, 0x1c, 0x00, 0x00, 
0x00, 0x03, 0x00, 0x1c, 0x00, 0x00, 
0x00, 0x1f, 0xfc, 0x1f, 0xfc, 0x00};
	
	// (x, y) 좌표에 걷기b 그리기
	x /= 3;
	
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x+5);		// 0~5(18px / 3)
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x9f - y);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x9f - y + 40);		// 0~39(40px)
	
	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 6 * 40; i++){
		st7586_write(ST_DATA, walk_b[i]);
	}
}

void draw_jump(uint8_t x, uint8_t y) {
	// (x, y) 좌표에 점프 그리기
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x+9);		// 0~9(30px / 3)
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x77);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x1d);		// 0~29(30px)

static const uint8_t jump[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x1c, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x1c, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xff, 0x00, 0x00, 0x1c, 0x03, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x03, 0xff, 0xff, 0xfc, 0x1f, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x1c, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x1f, 0xe0, 0x1c, 0x00, 0x03, 0x00, 0x00, 0x00, 0xfc, 
0x00, 0xfc, 0xff, 0xfc, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1c, 
0x03, 0xe0, 0x00, 0xff, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x1f, 
0x1f, 0x00, 0x00, 0xe0, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 
0x1c, 0x03, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
0x1c, 0x03, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 
0x1f, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0xe0, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1c, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 30*10; i++){
		st7586_write(ST_DATA, jump[i]);
	}
}

//플레이어 1: (0,6)~(47,13), 플레이어 2: (80, 6)~(127, 13)
void draw_hp(uint8_t pl, uint8_t hp)
{
	int i1, j1;
	if (pl == 1) {
		//체력바 범위 설정
		st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 0);
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 15);
		st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 6);
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 13);

		st7586_write(ST_COMMAND, 0x2C);
		for (i1 = 6; i1 < 14; i1++)	//행 색칠
		{
			//흰색 색칠
			for (j1 = 0; j1 < 15 - hp / 3; j1++)
			{
				st7586_write(ST_DATA, 0x00);
			}
			//j==15-hp/3
			if (hp % 3 == 1) {
				st7586_write(ST_DATA, 0x03);
				j1++;
			}
			else if (hp % 3 == 2) {
				st7586_write(ST_DATA, 0x1F);
				j1++;
			}
			//검은색 색칠
			for (; j1 < 16; j1++)
			{
				st7586_write(ST_DATA, 0xFF);
			}

		}
		
	}
	else if (pl == 2) {
		//체력바 범위 설정
		st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
		st7586_write(ST_DATA, 0x00);	
		st7586_write(ST_DATA, 26);			//26
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 42);			//42
		st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 6);
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 13);

		st7586_write(ST_COMMAND, 0x2C);
		for (i1 = 6; i1 < 14; i1++)	//행 색칠
		{
			if (hp > 0)
			{
				st7586_write(ST_DATA, 0x03);
				//hp--;
				//검은색 색칠
				for (j1 = 1; j1 < hp / 3+1 ; j1++)
				{
					st7586_write(ST_DATA, 0xFF);
				}
				//j==hp/3 16
				/*if (hp % 3 == 0) {
					st7586_write(ST_DATA, 0xFF);
					j1++;
				}*/
				if (hp % 3 == 2) {
					st7586_write(ST_DATA, 0xE0);
					j1++;
				}
				else if (hp % 3 == 1) {
					st7586_write(ST_DATA, 0x00);
					j1++;
				}
				//흰색 색칠
				for (; j1 < 17; j1++)
				{
					st7586_write(ST_DATA, 0x00);
				}
			}
			else
			{
				for (j1 = 0; j1 < 127 / 3; j1++)
				{
					st7586_write(ST_DATA, 0x00);
				}
			}
		}
		
	}
}

void draw_circle(uint8_t x1, uint8_t wl)
{
	static const uint8_t empty_circle[] = {
		0x00, 0x00, 0x00,
		0x00, 0x1F, 0x00,
		0x03, 0xE0, 0xFC,
		0x03, 0x00, 0x1C,
		0x1C, 0x00, 0x03,
		0x1C, 0x00, 0x03,
		0x03, 0x00, 0x1C,
		0x03, 0xE0, 0xFC,
		0x00, 0x1F, 0x00,
		0x00, 0x00, 0x00
	};
	static const uint8_t filled_circle[] = {
		0x00, 0x00, 0x00,
		0x00, 0x1F, 0x00,
		0x03, 0xFF, 0xFC,
		0x03, 0xFF, 0xFC,
		0x1F, 0xFF, 0xFF,
		0x1F, 0xFF, 0xFF,
		0x03, 0xFF, 0xFC,
		0x03, 0xFF, 0xFC,
		0x00, 0x1F, 0x00,
		0x00, 0x00, 0x00
	};
	if (x1 == 0)
	{
		st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 0);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 2);			//여기까지 (둘 다 포함)
		st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 20);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 29);			//여기까지 (둘 다 포함)
	}
	else if (x1 == 1)
	{
		st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 3);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 5);			//여기까지 (둘 다 포함)
		st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 20);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 29);			//여기까지 (둘 다 포함)
	}
	else if (x1 == 2)
	{
		st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 36);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 38);			//여기까지 (둘 다 포함)
		st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 20);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 29);			//여기까지 (둘 다 포함)
	}
	else if (x1 == 3)
	{
		st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 39);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 41);			//여기까지 (둘 다 포함)
		st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 20);			//여기서
		st7586_write(ST_DATA, 0x00);
		st7586_write(ST_DATA, 29);			//여기까지 (둘 다 포함)
	}
	if (wl == 0) {
		st7586_write(ST_COMMAND, 0x2C);
		for (i = 0; i < 10 * 3; i++) {
			st7586_write(ST_DATA, empty_circle[i]);
		}
	}
	else if (wl == 1) {
		st7586_write(ST_COMMAND, 0x2C);
		for (i = 0; i < 10 * 3; i++) {
			st7586_write(ST_DATA, filled_circle[i]);
		}
	}
}

void draw_ready()
{
	static const uint8_t draw_READY[] = {
		0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xff, 0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x03, 0xe0, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x03, 0xe0, 0x00, 0x03, 0xe0, 0x03, 0xe0, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x03, 0xe0, 0x03, 0xe0, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x03, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x1f, 0x00, 0x00,
		0xfc, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x03, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x1f, 0x00, 0x00,
		0xff, 0xff, 0xff, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00,
		0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00,
		0xfc, 0x00, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x03, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x03, 0xe0, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xfc, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00
	};

	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 9);			//여기서
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 33);			//여기까지 (둘 다 포함)
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 40);			//여기서
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 59);			//여기까지 (둘 다 포함)

	st7586_write(ST_COMMAND, 0x2C);
	for (i = 0; i < 20 * 25; i++) {
		st7586_write(ST_DATA, draw_READY[i]);
	}
}

void draw_go()
{
	static const uint8_t draw_GO[]={
		0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xfc, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
		0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00
	};

	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 16);			//여기서
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 26);			//여기까지 (둘 다 포함)
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 40);			//여기서
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 59);			//여기까지 (둘 다 포함)

	st7586_write(ST_COMMAND, 0x2C);
	for (i = 0; i < 20 * 11; i++) {
		st7586_write(ST_DATA, draw_GO[i]);
	}
}

void draw_splash() {
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x2A);		// 0~42(128px / 3)
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 0x9F);		// 0~159(160px)

	// Clear whole DDRAM by "0"
	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 160; i++){
		for(j = 0; j < 43; j++){
			st7586_write(ST_DATA, 0xff);
		}
	}
}

void draw_clear(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	// 왼쪽 하단이 (0, 0)인 좌표계로 (x1, y1) (x2, y2) 사각형을 clear함
	x1 /= 3; x2 /= 3;
	
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x1);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, x2);
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 159 - y1);
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 159 - y2);

	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < x2 - x1 + 1; i++){
		for(j = 0; j < y1 - y2 + 1; j++){
			st7586_write(ST_DATA, 0x00);
		}
	}
}

void draw_time(uint8_t time) {
if(time < 0) { time = 0; }

// 9px 16px
static const uint8_t num[][48] = {
// 0
{0x00, 0xff, 0xe0, 
0x03, 0xff, 0xfc, 
0x1f, 0xe0, 0xff, 
0x1f, 0x00, 0x1f, 
0xff, 0x00, 0x03, 
0xff, 0x00, 0x03, 
0xfc, 0x00, 0x03, 
0xfc, 0x00, 0x03, 
0xfc, 0x00, 0x03, 
0xff, 0x00, 0x03, 
0xff, 0x00, 0x03, 
0x1f, 0x00, 0x1f, 
0x1f, 0xe0, 0xff, 
0x03, 0xff, 0xff, 
0x00, 0xff, 0xe0, 
0x00, 0x00, 0x00},

// 1
{0x00, 0xff, 0x00, 
0x03, 0xff, 0x00, 
0x1f, 0xff, 0x00, 
0xff, 0xff, 0x00, 
0xff, 0xff, 0x00, 
0xfc, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0xff, 0xff, 0xff, 
0xff, 0xff, 0xff },

// 2
{0x1f, 0xff, 0xe0, 
0xff, 0xff, 0xff, 
0xfc, 0x1f, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x03, 0xff, 
0x00, 0x1f, 0xfc, 
0x00, 0x1f, 0xe0, 
0x00, 0x1f, 0xe0, 
0x00, 0xff, 0x00, 
0x03, 0xff, 0x00, 
0x1f, 0xe0, 0x00, 
0xff, 0xe0, 0x00, 
0xff, 0xff, 0xff, 
0xff, 0xff, 0xff},

// 3
{0x00, 0x00, 0x00, 
0xff, 0xff, 0xe0, 
0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x03, 0xff, 
0x03, 0xff, 0xfc, 
0x03, 0xff, 0xfc, 
0x03, 0xff, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x03, 0xff, 
0xff, 0xff, 0xff, 
0xff, 0xff, 0xfc, 
0xff, 0xff, 0xe0, 
0x00, 0x00, 0x00},

// 4
{0x00, 0x03, 0xe0, 
0x00, 0x1f, 0xe0, 
0x00, 0xff, 0xe0, 
0x00, 0xff, 0xe0, 
0x03, 0xff, 0xe0, 
0x03, 0xe3, 0xe0, 
0x1f, 0x03, 0xe0, 
0xff, 0x03, 0xe0, 
0xfc, 0x03, 0xe0, 
0xe0, 0x03, 0xe0, 
0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 
0x00, 0x03, 0xe0, 
0x00, 0x03, 0xe0, 
0x00, 0x03, 0xe0, 
0x00, 0x00, 0x00},

// 5
{0xff, 0xff, 0xfc, 
0xff, 0xff, 0xfc, 
0xfc, 0x00, 0x00, 
0xfc, 0x00, 0x00, 
0xfc, 0x00, 0x00, 
0xfc, 0x00, 0x00, 
0xff, 0xff, 0x00, 
0xff, 0xff, 0xfc, 
0x00, 0x00, 0xfc, 
0x00, 0x00, 0xff, 
0x00, 0x00, 0x1f, 
0x00, 0x00, 0xff, 
0xe0, 0x03, 0xfc, 
0xff, 0xff, 0xfc, 
0xff, 0xff, 0x00, 
0x00, 0x00, 0x00},

// 6
{0x00, 0xff, 0xfc, 
0x03, 0xff, 0xff, 
0x1f, 0xe0, 0x00, 
0xff, 0x00, 0x00, 
0xfc, 0x00, 0x00, 
0xfc, 0xff, 0xe0, 
0xff, 0xff, 0xfc, 
0xff, 0x00, 0xff, 
0xfc, 0x00, 0x1f, 
0xfc, 0x00, 0x1f, 
0xfc, 0x00, 0x1f, 
0xfc, 0x00, 0x1f, 
0xff, 0x00, 0xfc, 
0x1f, 0xff, 0xfc, 
0x03, 0xff, 0x00, 
0x00, 0x00, 0x00},

// 7
{0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 
0x00, 0x00, 0x1f, 
0x00, 0x00, 0xff, 
0x00, 0x00, 0xfc, 
0x00, 0x00, 0xfc, 
0x00, 0x03, 0xfc, 
0x00, 0x03, 0xe0, 
0x00, 0x1f, 0xe0, 
0x00, 0x1f, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xff, 0x00, 
0x00, 0xfc, 0x00, 
0x03, 0xfc, 0x00, 
0x03, 0xe0, 0x00, 
0x00, 0x00, 0x00},

// 8
{0x03, 0xff, 0xe0, 
0xff, 0xff, 0xfc, 
0xff, 0x00, 0xff, 
0xfc, 0x00, 0xff, 
0xfc, 0x00, 0xff, 
0xff, 0x03, 0xfc, 
0x1f, 0xff, 0xe0, 
0x1f, 0xff, 0xe0, 
0xff, 0x03, 0xfc, 
0xfc, 0x00, 0xff, 
0xe0, 0x00, 0x1f, 
0xfc, 0x00, 0x1f, 
0xfc, 0x00, 0xff, 
0xff, 0xff, 0xfc, 
0x03, 0xff, 0xe0, 
0x00, 0x00, 0x00 },

// 9
{ 0x03, 0xff, 0x00, 
0xff, 0xff, 0xfc, 
0xfc, 0x03, 0xfc, 
0xfc, 0x00, 0xff, 
0xe0, 0x00, 0x1f, 
0xe0, 0x00, 0x1f, 
0xfc, 0x00, 0xff, 
0xfc, 0x00, 0xff, 
0xff, 0xff, 0xff, 
0x03, 0xff, 0xff, 
0x00, 0x00, 0xff, 
0x00, 0x00, 0xfc, 
0x00, 0x1f, 0xfc, 
0xff, 0xff, 0xe0, 
0xff, 0xfc, 0x00, 
0x00, 0x00, 0x00}};

	// 10의 자리 숫자 그리기
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 18);			// 18~20 (54px ~ 62px)
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 20);
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 2);			// 2px ~ 17px(16px)
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 17);
	
	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 3 * 16; i++){	// 9px 16px
		st7586_write(ST_DATA, num[time / 10][i]);	// 10의 자리
	}
	
	// 1의 자리 숫자 그리기
	st7586_write(ST_COMMAND, 0x2A);		// Column Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 22);			// 22~24 (66px ~ 74px)
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 24);
	st7586_write(ST_COMMAND, 0x2B);		// Row Address Setting
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 2);			// 2px ~ 17px(16px)
	st7586_write(ST_DATA, 0x00);
	st7586_write(ST_DATA, 17);
	
	st7586_write(ST_COMMAND, 0x2C);
	for(i = 0; i < 3 * 16; i++){	// 9px 16px
		st7586_write(ST_DATA, num[time % 10][i]);	// 1의 자리
	}
}
