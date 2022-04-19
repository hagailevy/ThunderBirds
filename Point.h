#pragma once

#include "utils.h"

struct Point
{
	int x, y;
	Point(int x1=0, int y1=0);
	Point& operator=(Point p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
};