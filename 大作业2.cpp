#include<vector>
#include<time.h>
#include<string>
#include<conio.h>
#include<iostream>
#include<windows.h>
#include"Block.h"
#include"Game.h"
#include"Point.h"
#include"函数及变量.h"
using namespace std;

int main()
{
	HideCursor();
	srand(time(NULL));
	Block::StateInit();
	Game* pG = new Game();
	pG->Start();
	while (1)
	{
		int tick_times = 0;
		while (++tick_times < pG->GetInterval())    //控制下落时间间隔以及控制输出
		{
            pG->CheckBoard();
			if (bo || ju)  Sleep(0.1);
			else Sleep(7);
			
		}
		if (!pG->ChangePos(1, 0))
		{
			if (pG->runB.p == Point(1, 5))       //如果一开始就下不去,game over
			{
				pG->Over();
				break;
			}
			if (!bo)
			{		
				pG->PlaceOn(); pG->CheckLine();
		     }
			else  pG->BombOn(); 
			pG->GetNext();
			ju = 0; bo = 0;
		}
	}
	delete pG;
	return 0;
}