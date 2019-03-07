#ifndef _BLOCK_H_
#define _BLOCK_H_
#include"Point.h"
#include"函数及变量.h"
#include<string>
using namespace std;

class Block :public Point               //Block类
{

private:
	static string allstate[7][4];      //7种方块各有（至多）4种状态
	int kind, dir;                     //kind表示种类,dir表示方向
public:
	Block();
	Point p;                        //4*4数组的左上角坐标
	bool state[4][4];               //用4*4的数组标记自己的状态
	static void StateInit();       //初始化所有方块的状态
	void StateCpy();                //将自己的状态与kind和dir对应
	void Rotate();                  //旋转
	void Show(bool info=false);                //将方块在屏幕上输出
};
string Block::allstate[7][4];       //初始化静态变量
void Block::StateInit()
{
	//长条形
	allstate[0][0] = allstate[0][2] = "0100 0100 0100 0100";
	allstate[0][1] = allstate[0][3] = "0000 1111 0000 0000";
	//正方形
	allstate[1][0] = allstate[1][1] = allstate[1][2] = allstate[1][3] = "0000 0110 0110 0000";
	//反"Z"形
	allstate[2][0] = allstate[2][2] = "0000 0110 1100 0000";
	allstate[2][1] = allstate[2][3] = "0100 0110 0010 0000";
	//"Z"形
	allstate[3][0] = allstate[3][2] = "0000 1100 0110 0000";
	allstate[3][1] = allstate[3][3] = "0100 1100 1000 0000";
	//"T"形
	allstate[4][0] = "0000 1110 0100 0000";
	allstate[4][1] = "0100 1100 0100 0000";
	allstate[4][2] = "0100 1110 0000 0000";
	allstate[4][3] = "0100 0110 0100 0000";
	//反"L"形
	allstate[5][0] = "0100 0100 1100 0000";
	allstate[5][1] = "1000 1110 0000 0000";
	allstate[5][2] = "1100 1000 1000 0000";
	allstate[5][3] = "0000 1110 0010 0000";
	//"L"形
	allstate[6][0] = "0100 0100 0110 0000";
	allstate[6][1] = "0000 1110 1000 0000";
	allstate[6][2] = "1100 0100 0100 0000";
	allstate[6][3] = "0010 1110 0000 0000";
}

Block::Block()
{
	kind = rand() % 7;                     //随机生成块的种类
	dir = rand() % 4;                      //随机生成块的方向
	p = Point(4, 15);                      //初始化点p的位置
	StateCpy();
}

void Block::StateCpy()
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			state[i][j] = allstate[kind][dir][i * 5 + j] == '1';   //给每个方块的状态赋值
}

void Block::Rotate()
{
	dir = (dir + 1) % 4;
	StateCpy();
}

void Block::Show(bool info)      //info表示是否是信息栏,下同
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			Choose(Point(p.getx() + i, p.gety() + j), state[i][j], info);
}
#endif