#ifndef _函数及变量_H_
#define _函数及变量_H_
#include"Point.h"
#include<vector>
#include<time.h>
#include<string>
#include<conio.h>
#include<iostream>
#include<windows.h>
using namespace std;

const int N = 23;//游戏栏、信息栏的行数
const int M = 14;//游戏栏的列数
const int MM = 8;//信息栏的列数
static int ju = 0, bo = 0;

const string square = "■";
const string bomb = "**";
const string space = "  ";
const string line[] = { "┄","┆" };
const string corner[] = { "┌","┐","└","┘" };

string g[N][M], gg[N][MM];       //g为游戏栏,gg为信息栏


void SetCursor(int x, int y)      //设置光标位置
{
	COORD cd = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void SetCursor(Point &p)      //将数组中的位置映射到屏幕上
{
	SetCursor(2 * p.gety(), p.getx());
}

void HideCursor()                  //隐藏光标
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfo);
}

template<typename T>
void PrintAt(Point &p, T data, int wid = 0)           //在点p处输出data
{
	SetCursor(p);
	if (wid)
		cout.width(wid);
	cout << data;
}

void  Choose(Point &p, bool flag = false, bool info = false) //在点p处输出/擦除方块
{
	if (info || g[p.getx()][p.gety()] == space)
		PrintAt(p, flag ? square : space);
}
void  Choose1(Point &p, bool flag = false, int i = 0)       //输出称赞
{
	if (i || g[p.getx()][p.gety()] == space)
	{
		switch (i)
		{
		case 1:PrintAt(p, flag ? "G o o d！" : space); break;
		case 2:PrintAt(p, flag ? "哎哟，不错哦！" : space); break;
		case 3:PrintAt(p, flag ? "p e r f e c t！" : space); break;
		case 4:PrintAt(p, flag ? "登 峰 造 极！" : space); break;
		}
	}
}

#endif