#ifndef _GAME_H_
#define _GAME_H_
#include"Block.h"

class Game :public Block                 //Game类
{
private:
	static int level_up[9];             //各level对应的分数
	static int score_up[5];             //消除各行对应要加的分数
	static int interval[10];             //各level对应的时间间隔
	int level, score;
public:
	Block runB, nextB;
	Game();
	int GetInterval() { return interval[level]; }       //得到当前level的interval
	void ShowFrame();                   //输出游戏框架
	void CheckBoard();                  //检查键盘响应
	bool AllSquare(int xx);             //检查xx行是否可消
	void DropDown(int xx);              //将xx行以上的全部下移一格
	void CheckLine();                   //方块安放后检查是否有可消行
	void PlaceOn();                     //方块安放好
	void Update(int);                   //更新信息
	void GetNext();                     //得到下一个方块
	bool OutBoard(int, int);            //检查坐标是否出界
	bool CanChange(int, int);           //检查是否可以发生这样的改变
	bool ChangePos(int, int);           //检查并改变下落方块的位置
	void Rotate();                      //旋转
	void ChangeBlock();                 //改变当前块
	void Bomb();                        //将当前块变为炸弹
	void BombOn();                      //炸弹降落
	void Start();                       //游戏欢迎界面
	void Over();                        //游戏结束界面
	void Win();                         //游戏获胜界面
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
	PrintAt(Point(15, 15), "按“p”暂停");
	PrintAt(Point(16, 15), "按“c”更换");
	PrintAt(Point(17, 15), "按“b”爆炸");
	PrintAt(Point(18, 15), "按space下落");
	PrintAt(Point(21, 16), "by王春禹");
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
			Choose(Point(runB.p.getx() + i, runB.p.gety() + j), false); //擦除原方块
	runB = nextB;                        //生成新方块
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
	vector<int> flash_line;                   //用来储存要消去的行号
	vector<int>::iterator it;
	int k = 0;                                    //可消除的行数
	for (int i = 0; i<4; i++)
		if (AllSquare(i + runB.p.getx()))
		{
			k++; flash_line.push_back(i + runB.p.getx());
		}
	if (flash_line.empty())
		return;
	int flash_times = 5;
	while (flash_times--)                         //闪
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
	for (it = flash_line.begin(); it != flash_line.end(); it++)   //消去某行后，将上面的信息向下移动
		DropDown(*it);
	it = flash_line.end() - 1;
	for (int i = 1; i <= *it; i++)
		for (int j = 1; j<M - 1; j++)
			Choose(Point(i, j), g[i][j] == square, true);
	Update(flash_line.size());             //更新要消去的最后一行上方的信息
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
	if (_kbhit())                                    //检测键盘是否按下
	{
		switch (_getch())
		{
		case 72:Rotate(); break;              //上
		case 80:ChangePos(1, 0); break;       //下
		case 75:ChangePos(0, -1); break;      //左
		case 77:ChangePos(0, 1); break;       //右
		case 'p':_getch(); break;             //暂停
		case ' ':ChangePos(0, 0); break;      //下落
		case 'c':ChangeBlock(); break;        //更换
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
	if (dx)                             //处理最后那行的显示
	{
		for (int j = 0; j<4; j++)
			Choose(Point(x, y + j));
		++runB.p;
	}
	else if (dy == 1)                        //向右
	{
		for (int i = 0; i<4; i++)
			Choose(Point(x + i, y));
		runB.p++;
	}
	else if (dy == -1)                        //向左
	{
		for (int i = 0; i<4; i++)
			Choose(Point(x + i, y + 3));
		runB.p--;
	}
	else if (dy == 0)                        //直接下落
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
				while (flash_times--)                         //闪
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
		PrintAt(Point(8, 2), "欢迎进入俄罗斯方块！");
		PrintAt(Point(9, 2), "用方向键来控制移动");
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
	PrintAt(Point(25, 0), "");                   //把光标移到最后
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
	PrintAt(Point(5, 3), "**你刚刚挑战完成了最快的Tetrix**");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_BLUE);
	PrintAt(Point(7, 3), "***我跟不上你风驰电掣的速度！***");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_GREEN);
	PrintAt(Point(9, 3), "**********是在下输了！**********");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_RED);
	PrintAt(Point(11, 3), "**********恭喜你获胜！**********");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
		FOREGROUND_GREEN);
	PrintAt(Point(13, 4), "******EE出品，必属精品！******");
	system("pause");
}
#endif