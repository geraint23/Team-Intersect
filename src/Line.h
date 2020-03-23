#pragma once
#include <iostream>
#include <cmath>
#include <set>
#include "Point.h"

using namespace std;

set<Point> nodes;

class Line {
public:
	double k;	// 斜率
	double b;	// 截距

	Line(double x1, double y1, double x2, double y2) {	// 斜率存在时b是截距，不存在时b是x坐标
		if (x1 == x2) {
			k = INFINITY;
			b = x1;
		}
		else {
			k = (y2 - y1) / (x2 - x1);
			b = y1 - k * x1;
		}
	}

	void intersect_L(Line otherLine) {
		double x, y;
		if (k != otherLine.k) {
			if (k == INFINITY) {
				x = b;
				y = otherLine.k * x + otherLine.b;
			}
			else if (otherLine.k == INFINITY) {
				x = otherLine.b;
				y = k * x + b;
			}
			else {
				x = (otherLine.b - b) / (k - otherLine.k);
				y = k * x + b;
			}
			nodes.insert(Point(trans(x), trans(y)));
			/*cout << x << "," << y << endl;*/
		}
	}

};