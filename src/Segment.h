#pragma once
#include <iostream>
#include <Windows.h>
#include "error.h"

class Segment {
public:
	double k;
	double b;
	double x1;
	double y1;	// 端点A(x1,y1)
	double x2;
	double y2;	// 端点B(x2,y2)

	Segment(double x1, double y1, double x2, double y2) {	// 斜率存在时b是截距，不存在时b是x坐标
		if (x1 == x2) {
			k = INFINITY;
			b = x1;
		}
		else {
			k = (y2 - y1) / (x2 - x1);
			b = y1 - k * x1;
		}
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

	bool onSegment(Point p) {
		double X = max(x1, x2);
		double x = min(x1, x2);
		double Y = max(y1, y2);
		double y = min(y1, y2);
		if (p.x >= x && p.x <= X && p.y >= y && p.y <= Y) {
			return true;
		}
		return false;
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
			Point p = Point(trans(x), trans(y));
			if (onSegment(p)) {
				nodes.insert(p);
			}
			/*cout << x << "," << y << endl;*/
		}
		else if (b == otherLine.b) {
				error_type3();
		}
	}

	void preprocess(Segment otherSegment) {	// AB是this，CD是otherSegment
		Point A = Point(x1, y1);
		Point B = Point(x2, y2);
		Point C = Point(otherSegment.x1, otherSegment.y1);
		Point D = Point(otherSegment.x2, otherSegment.y2);
		int cnt = 0;
		if (otherSegment.onSegment(A)) {
			cnt++;
		}
		if (otherSegment.onSegment(B)) {
			cnt++;
		}
		if (onSegment(C)) {
			cnt++;
		}
		if (onSegment(D)) {
			cnt++;
		}
		// cnt == 0时没用
		if (cnt == 2) {
			if (A.equals(C)) {
				nodes.insert(A);
			}
			else if (A.equals(D)) {
				nodes.insert(A);
			}
			else if (B.equals(C)) {
				nodes.insert(B);
			}
			else if (B.equals(D)) {
				nodes.insert(B);
			}
			else {
				error_type3();
			}
		}
		else if (cnt == 3 || cnt == 4) {
			error_type3();
		}
	}

	void preprocess(Ray otherRay) {
		Point rayStart = Point(otherRay.x1, otherRay.y1);
		Point A = Point(x1, y1);
		Point B = Point(x2, y2);
		if (onSegment(rayStart)) {
			if (rayStart.equals(A)) {
				if (otherRay.onRay(B)) {
					error_type3();
				}
				else {
					nodes.insert(rayStart);
				}
			}
			else if (rayStart.equals(B)) {
				if (otherRay.onRay(A)) {
					error_type3();
				}
				else {
					nodes.insert(rayStart);
				}
			}
			else {
				error_type3();
			}
		}
		else {
			if (otherRay.onRay(A)) {
				error_type3();
			}
		}
	}

	void intersect_S(Segment otherSegment) {
		double x, y;
		if (k == otherSegment.k && b == otherSegment.b) {
			preprocess(otherSegment);
		}
		else if (k != otherSegment.k) {
			if (k == INFINITY) {
				x = b;
				y = otherSegment.k * x + otherSegment.b;
			}
			else if (otherSegment.k == INFINITY) {
				x = otherSegment.b;
				y = k * x + b;
			}
			else {
				x = (otherSegment.b - b) / (k - otherSegment.k);
				y = k * x + b;
			}
			Point p = Point(trans(x), trans(y));
			if (onSegment(p) && otherSegment.onSegment(p)) {
				nodes.insert(p);
			}
		}
	}

	void intersect_R(Ray otherRay) {
		double x, y;
		if (k == otherRay.k && b == otherRay.b) {
			preprocess(otherRay);
		}
		else if (k != otherRay.k) {
			if (k == INFINITY) {
				x = b;
				y = otherRay.k * x + otherRay.b;
			}
			else if (otherRay.k == INFINITY) {
				x = otherRay.b;
				y = k * x + b;
			}
			else {
				x = (otherRay.b - b) / (k - otherRay.k);
				y = k * x + b;
			}
			Point p = Point(trans(x), trans(y));
			if (onSegment(p) && otherRay.onRay(p)) {
				nodes.insert(p);
			}
		}
	}
};