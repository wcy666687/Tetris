#ifndef _POINT_H_
#define _POINT_H_
class Point
{
public:
	Point(){}
	Point(int _x, int _y) :x(_x), y(_y) {}
	int getx() { return x; }
	int gety() { return y; }
	Point operator++(int)
	{
		y++;
		return (*this);
	}
	Point operator--(int)
	{
		y--;
		return (*this);
	}
	Point operator++()
	{
		x++;
		return (*this);
	}
	bool operator == (const Point&B)
	{
		return x == B.x && y == B.y;
	}
private:
	int x, y;
};
#pragma once
#endif