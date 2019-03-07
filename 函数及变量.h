#ifndef _����������_H_
#define _����������_H_
#include"Point.h"
#include<vector>
#include<time.h>
#include<string>
#include<conio.h>
#include<iostream>
#include<windows.h>
using namespace std;

const int N = 23;//��Ϸ������Ϣ��������
const int M = 14;//��Ϸ��������
const int MM = 8;//��Ϣ��������
static int ju = 0, bo = 0;

const string square = "��";
const string bomb = "**";
const string space = "  ";
const string line[] = { "��","��" };
const string corner[] = { "��","��","��","��" };

string g[N][M], gg[N][MM];       //gΪ��Ϸ��,ggΪ��Ϣ��


void SetCursor(int x, int y)      //���ù��λ��
{
	COORD cd = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void SetCursor(Point &p)      //�������е�λ��ӳ�䵽��Ļ��
{
	SetCursor(2 * p.gety(), p.getx());
}

void HideCursor()                  //���ع��
{
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfo);
}

template<typename T>
void PrintAt(Point &p, T data, int wid = 0)           //�ڵ�p�����data
{
	SetCursor(p);
	if (wid)
		cout.width(wid);
	cout << data;
}

void  Choose(Point &p, bool flag = false, bool info = false) //�ڵ�p�����/��������
{
	if (info || g[p.getx()][p.gety()] == space)
		PrintAt(p, flag ? square : space);
}
void  Choose1(Point &p, bool flag = false, int i = 0)       //�������
{
	if (i || g[p.getx()][p.gety()] == space)
	{
		switch (i)
		{
		case 1:PrintAt(p, flag ? "G o o d��" : space); break;
		case 2:PrintAt(p, flag ? "��Ӵ������Ŷ��" : space); break;
		case 3:PrintAt(p, flag ? "p e r f e c t��" : space); break;
		case 4:PrintAt(p, flag ? "�� �� �� ����" : space); break;
		}
	}
}

#endif