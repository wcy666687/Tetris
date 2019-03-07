#ifndef _BLOCK_H_
#define _BLOCK_H_
#include"Point.h"
#include"����������.h"
#include<string>
using namespace std;

class Block :public Point               //Block��
{

private:
	static string allstate[7][4];      //7�ַ�����У����ࣩ4��״̬
	int kind, dir;                     //kind��ʾ����,dir��ʾ����
public:
	Block();
	Point p;                        //4*4��������Ͻ�����
	bool state[4][4];               //��4*4���������Լ���״̬
	static void StateInit();       //��ʼ�����з����״̬
	void StateCpy();                //���Լ���״̬��kind��dir��Ӧ
	void Rotate();                  //��ת
	void Show(bool info=false);                //����������Ļ�����
};
string Block::allstate[7][4];       //��ʼ����̬����
void Block::StateInit()
{
	//������
	allstate[0][0] = allstate[0][2] = "0100 0100 0100 0100";
	allstate[0][1] = allstate[0][3] = "0000 1111 0000 0000";
	//������
	allstate[1][0] = allstate[1][1] = allstate[1][2] = allstate[1][3] = "0000 0110 0110 0000";
	//��"Z"��
	allstate[2][0] = allstate[2][2] = "0000 0110 1100 0000";
	allstate[2][1] = allstate[2][3] = "0100 0110 0010 0000";
	//"Z"��
	allstate[3][0] = allstate[3][2] = "0000 1100 0110 0000";
	allstate[3][1] = allstate[3][3] = "0100 1100 1000 0000";
	//"T"��
	allstate[4][0] = "0000 1110 0100 0000";
	allstate[4][1] = "0100 1100 0100 0000";
	allstate[4][2] = "0100 1110 0000 0000";
	allstate[4][3] = "0100 0110 0100 0000";
	//��"L"��
	allstate[5][0] = "0100 0100 1100 0000";
	allstate[5][1] = "1000 1110 0000 0000";
	allstate[5][2] = "1100 1000 1000 0000";
	allstate[5][3] = "0000 1110 0010 0000";
	//"L"��
	allstate[6][0] = "0100 0100 0110 0000";
	allstate[6][1] = "0000 1110 1000 0000";
	allstate[6][2] = "1100 0100 0100 0000";
	allstate[6][3] = "0010 1110 0000 0000";
}

Block::Block()
{
	kind = rand() % 7;                     //������ɿ������
	dir = rand() % 4;                      //������ɿ�ķ���
	p = Point(4, 15);                      //��ʼ����p��λ��
	StateCpy();
}

void Block::StateCpy()
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			state[i][j] = allstate[kind][dir][i * 5 + j] == '1';   //��ÿ�������״̬��ֵ
}

void Block::Rotate()
{
	dir = (dir + 1) % 4;
	StateCpy();
}

void Block::Show(bool info)      //info��ʾ�Ƿ�����Ϣ��,��ͬ
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			Choose(Point(p.getx() + i, p.gety() + j), state[i][j], info);
}
#endif