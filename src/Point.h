#pragma once
#include <iostream>

using namespace std;

class Point {
public:
	double x;
	double y;
	double esp = 1e-10;

	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	bool equals(Point otherPoint) {
		return abs(x - otherPoint.x) < esp && abs(y - otherPoint.y) < esp;
	}

	bool operator<(const Point& A) const {
		if (abs(this->x - A.x) < esp && abs(this->y - A.y) < esp) {
			return false;
		}
		else
		{
			if (this->x != A.x) {
				return this->x < A.x;
			}
			else {
				return this->y < A.y;
			}
		}
	}

};

double trans(double ans) {
	return abs(ans) < 1e-10 ? 0.0 : ans;
}