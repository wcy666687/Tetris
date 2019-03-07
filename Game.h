#ifndef _GAME_H_
#define _GAME_H_
#include"Block.h"

class Game :public Block                 //Game��
{
private:
	static int level_up[9];             //��level��Ӧ�ķ���
	static int score_up[5];             //�������ж�ӦҪ�ӵķ���
	static int interval[10];             //��level��Ӧ��ʱ����
	int level, score;
public:
	Block runB, nextB;
	Game();
	int GetInterval() { return interval[level]; }       //�õ���ǰlevel��interval
	void ShowFrame();                   //�����Ϸ���
	void CheckBoard();                  //��������Ӧ
	bool AllSquare(int xx);             //���xx���Ƿ����
	void DropDown(int xx);              //��xx�����ϵ�ȫ������һ��
	void CheckLine();                   //���鰲�ź����Ƿ��п�����
	void PlaceOn();                     //���鰲�ź�
	void Update(int);                   //������Ϣ
	void GetNext();                     //�õ���һ������
	bool OutBoard(int, int);            //��������Ƿ����
	bool CanChange(int, int);           //����Ƿ���Է��������ĸı�
	bool ChangePos(int, int);           //��鲢�ı����䷽���λ��
	void Rotate();                      //��ת
	void ChangeBlock();                 //�ı䵱ǰ��
	void Bomb();                        //����ǰ���Ϊը��
	void BombOn();                      //ը������
	void Start();                       //��Ϸ��ӭ����
	void Over();                        //��Ϸ��������
	void Win();                         //��Ϸ��ʤ����
};
int Game::level_up[9] = { 0,20,40,60,80,100,120,140,160 };
int Game::score_up[5] = { 0,10,30,60,100 };
int Game::interval[10] = { 0,50,40,25,15,8,40,20,6 };

Game::Game() :level(1), score(0)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			g[i][j] = "  ";
		for (int j = 0; j < MM; j++)
			gg[i][j] = "  ";
	}
	for (int i = 1; i < M; i++)
		g[0][i] = g[N - 1][i] = line[0];
	for (int i = 1; i < MM; i++)
		gg[0][i] = gg[N - 1][i] = line[0];
	for (int i = 1; i < N; i++)
		g[i][0] = g[i][M - 1] = gg[i][0] = gg[i][MM - 1] = line[1];
	g[0][0] = gg[0][0] = corner[0];
	g[0][M - 1] = gg[0][MM - 1] = corner[1];
	g[N - 1][0] = gg[N - 1][0] = corner[2];
	g[N - 1][M - 1] = gg[N - 1][MM - 1] = corner[3];
}

void Game::ShowFrame()
{
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<M; j++)
			cout << g[i][j];
		for (int j = 0; j<MM; j++)
			cout << gg[i][j];
		cout << endl;
	}
	PrintAt(Point(2, 16), "Next");
	PrintAt(Point(9, 16), "Level");
	PrintAt(Point(10, 16), level, 2);
	PrintAt(Point(12, 16), "Score");
	PrintAt(Point(13, 16), score);
	PrintAt(Point(15, 15), "����p����ͣ");
	PrintAt(Point(16, 15), "����c������");
	PrintAt(Point(17, 15), "����b����ը");
	PrintAt(Point(18, 15), "��space����");
	PrintAt(Point(21, 16), "by������");
}

bool Game::AllSquare(int xx)
{
	for (int j = 1; j<M - 1; j++)
		if (g[xx][j] != square)
			return false;
	return true;
}

void Game::DropDown(int xx)
{
	for (int i = xx; i>1; i--)
		for (int j = 1; j<M - 1; j++)
			g[i][j] = g[i - 1][j];
	for (int j = 1; j<M - 1; j++)
		g[1][j] = space;
}

void Game::ChangeBlock()
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			Choose(Point(runB.p.getx() + i, runB.p.gety() + j), false); //����ԭ����
	runB = nextB;                        //�����·���
	runB.p = Point(1, 5);
	nextB = Block();
	nextB.Show(true);
	runB.Show();
}

void Game::Update(int flash_line_cnt = 0)
{
	score += score_up[flash_line_cnt];
	PrintAt(Point(13, 16), score, 2);
	if (score >= level_up[level])
		PrintAt(Point(10, 16), ++level, 2);
	if (level&&score<level_up[level - 1]) PrintAt(Point(10, 16), --level, 2);
	switch (level % 7)
	{
	case 0:system("color 81"); break;
	case 1:system("color 0F"); break;
	case 2:system("color 81"); break;
	case 3:system("color 74"); break;
	case 4:system("color 80"); break;
	case 5:system("color 0E"); break;
	case 6:system("color 82"); break;
	default:break;
	}
	if (level >= 9)
	{
		this->Win(); exit(1);
	}
}

void Game::CheckLine()
{
	vector<int> flash_line;                   //��������Ҫ��ȥ���к�
	vector<int>::iterator it;
	int k = 0;                                    //������������
	for (int i = 0; i<4; i++)
		if (AllSquare(i + runB.p.getx()))
		{
			k++; flash_line.push_back(i + runB.p.getx());
		}
	if (flash_line.empty())
		return;
	int flash_times = 5;
	while (flash_times--)                         //��
	{
		for (it = flash_line.begin(); it != flash_line.end(); it++)
		{
			for (int j = 1; j < M - 1; j++)
				Choose(Point(*it, j), flash_times & 2, true);
			Choose1(Point(10, 5), true, k);
			Choose1(Point(9, 5), true, k);
			Sleep(30);
		}
	}
	for (it = flash_line.begin(); it != flash_line.end(); it++)   //��ȥĳ�к󣬽��������Ϣ�����ƶ�
		DropDown(*it);
	it = flash_line.end() - 1;
	for (int i = 1; i <= *it; i++)
		for (int j = 1; j<M - 1; j++)
			Choose(Point(i, j), g[i][j] == square, true);
	Update(flash_line.size());             //����Ҫ��ȥ�����һ���Ϸ�����Ϣ
	flash_line.clear();
}

void Game::PlaceOn()
{
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			if (runB.state[i][j])
				g[runB.p.getx() + i][runB.p.gety() + j] = square;
}

void Game::GetNext()
{
	runB = nextB;
	runB.p = Point(1, 5);
	nextB = Block();
	nextB.Show(true);
	runB.Show();
}

bool Game::OutBoard(int x, int y)
{
	return x <= 0 || x >= N - 1 || y <= 0 || y >= M - 1;
}

void Game::CheckBoard()
{
	if (_kbhit())                                    //�������Ƿ���
	{
		switch (_getch())
		{
		case 72:Rotate(); break;              //��
		case 80:ChangePos(1, 0); break;       //��
		case 75:ChangePos(0, -1); break;      //��
		case 77:ChangePos(0, 1); break;       //��
		case 'p':_getch(); break;             //��ͣ
		case ' ':ChangePos(0, 0); break;      //����
		case 'c':ChangeBlock(); break;        //����
		case 'b':Bomb(); bo = 1; break;
		}
	}
}

bool Game::CanChange(int dx = 0, int dy = 0)
{
	const int x = runB.p.getx(), y = runB.p.gety();
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			if (runB.state[i][j] && (OutBoard(i + x + dx, j + y + dy) || g[i + x + dx][j + y + dy] == square))
				return false;
	return true;
}

void Game::Rotate()
{
	runB.Rotate();
	if (!CanChange())
		for (int i = 0; i<3; i++)
			runB.Rotate();
	runB.Show();
}

bool Game::ChangePos(int dx, int dy)
{
	if (!CanChange(dx, dy))
		return false;
	const int x = runB.p.getx(), y = runB.p.gety();
	if (dx)                             //����������е���ʾ
	{
		for (int j = 0; j<4; j++)
			Choose(Point(x, y + j));
		++runB.p;
	}
	else if (dy == 1)                        //����
	{
		for (int i = 0; i<4; i++)
			Choose(Point(x + i, y));
		runB.p++;
	}
	else if (dy == -1)                        //����
	{
		for (int i = 0; i<4; i++)
			Choose(Point(x + i, y + 3));
		runB.p--;
	}
	else if (dy == 0)                        //ֱ������
	{
		ju = 1; return true;
	}
	runB.Show();
	return true;
}

void Game::Bomb()
{
	if (score)
		score -= 5;
	PrintAt(Point(13, 16), score, 2);
	Update();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (runB.state[i][j])
			{
				int flash_times = 4;
				while (flash_times--)                         //��
				{
					PrintAt(Point(runB.p.getx() + i, runB.p.gety() + j), bomb);
					Sleep(5);
				}
			}
	bo = 1;
}

void Game::BombOn()
{
	PlaceOn();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (runB.state[i][j])
			{
				g[runB.p.getx() + i][runB.p.gety() + j] = space;
				PrintAt(Point(runB.p.getx() + i, runB.p.gety() + j), space);
				if (g[runB.p.getx() + i + 1][runB.p.gety() + j] == square)
				{
					g[runB.p.getx() + i + 1][runB.p.gety() + j] = space;
					PrintAt(Point(runB.p.getx() + i + 1, runB.p.gety() + j), bomb);
					PrintAt(Point(runB.p.getx() + i + 1, runB.p.gety() + j), space);
				}
				if (g[runB.p.getx() + i][runB.p.gety() + j - 1] == square)
				{
					g[runB.p.getx() + i][runB.p.gety() + j - 1] = space;
					PrintAt(Point(runB.p.getx() + i, runB.p.gety() + j - 1), bomb);
					PrintAt(Point(runB.p.getx() + i, runB.p.gety() + j - 1), space);
				}
				if (g[runB.p.getx() + i][runB.p.gety() + j + 1] == square)
				{
					g[runB.p.getx() + i][runB.p.gety() + j + 1] = space;
					PrintAt(Point(runB.p.getx() + i, runB.p.gety() + j + 1), bomb);
					PrintAt(Point(runB.p.getx() + i, runB.p.gety() + j + 1), space);
				}
			}
		}
}
void Game::Start()
{
	ShowFrame();
	nextB = Block();
	GetNext();
	int flash_times = 1000;
	while (!_kbhit() && flash_times--)
	{
		PrintAt(Point(8, 2), "��ӭ�������˹���飡");
		PrintAt(Point(9, 2), "�÷�����������ƶ�");
		PrintAt(Point(10, 1), flash_times & 1 ? "                      " : "  * * * * * * * * * ");
		PrintAt(Point(11, 1), flash_times & 1 ? "   Press to start    " : " * Press to start * ");
		PrintAt(Point(12, 1), flash_times & 1 ? "                      " : "  * * * * * * * * * ");
		Sleep(100);
	}
	_getch();
	PrintAt(Point(8, 2), "                    ");
	PrintAt(Point(9, 1), "                     ");
	PrintAt(Point(10, 1), "                     ");
	PrintAt(Point(11, 1), "                     ");
	PrintAt(Point(12, 1), "                     ");
}

void Game::Over()
{
	int flash_times = 12;
	while (flash_times--)
	{
		PrintAt(Point(9, 3), flash_times & 1 ? "               " : "  * * * * * *  ");
		PrintAt(Point(10, 3), flash_times & 1 ? "   Game over   " : " * Game over * ");
		PrintAt(Point(11, 3), flash_times & 1 ? "               " : "  * * * * * *  ");
		Sleep(150);
	}
	PrintAt(Point(25, 0), "");                   //�ѹ���Ƶ����
}
void Game::Win()
{
	system("color 82");
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 22; j++)
			PrintAt(Point(i, j), square);
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED);
	PrintAt(Point(5, 3), "**��ո���ս���������Tetrix**");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_BLUE);
	PrintAt(Point(7, 3), "***�Ҹ��������۵糸���ٶȣ�***");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_GREEN);
	PrintAt(Point(9, 3), "**********���������ˣ�**********");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED);
	PrintAt(Point(11, 3), "**********��ϲ���ʤ��**********");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_GREEN);
	PrintAt(Point(13, 4), "******EE��Ʒ��������Ʒ��******");
	system("pause");
}
#endif