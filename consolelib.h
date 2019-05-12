#ifndef CONSOLELIB_H
#define CONSOLELIB_H
#include <iostream>
#include <windows.h>
#define ENTER 			13
#define KEY_UP          72
#define KEY_DOWN        80
using namespace std;
void Moveto(short x,short y);	//move cursor
void Clear_at(int x0, int y0, int x1, int y1); //clear screen at position desired
void Setcolor(WORD color);	//set text color
void Setbkcolor(WORD color);	//set background color
template<class _Tp>
void Print_at(int x, int y, _Tp data);	//print at desired position
void Normal(short fontColor, short backgroundColor);	//set normal view
void HighLight(short fontColor, short backgroundColor);	//set highlight view
void Moveto(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
void Clear_at(int x0, int y0, int x1, int y1)
{
	for (int i = x0; i <= x1; i+=5)
	{
		for (int j = y0; j <= y1; j+=1)
		{
			Print_at(i, j,"          ");
		}
	}
}
void Setcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Setbkcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
template<class _Tp1>
void Print_at(int x, int y, _Tp1 data1)
{
	Moveto(x, y);
	cout << data1;
}

void GetWindowSize(int &Width, int &Height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    Width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    Height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Normal(short fontColor, short backgroundColor)
{
	Setcolor(fontColor);
	Setbkcolor(backgroundColor);
}
void HighLight(short fontColor, short backgroundColor)
{
	Setcolor(fontColor);
	Setbkcolor(backgroundColor);
}
#endif
