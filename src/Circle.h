#pragma once
#include <iostream>
#include <cmath>
#include "Line.h"
#include "Ray.h"
#include "Segment.h"

using namespace std;

class Circle {
public:
	double x;	// 圆心x坐标
	double y;	// 圆心y坐标
	double r;	// 半径

	Circle(double x, double y, double r) {
		this->x = x;
		this->y = y;
		this->r = r;
	}

	void intersect_C(Circle otherCircle) {
		if (x == otherCircle.x && y == otherCircle.y && r == otherCircle.r) {
			error_type3();
		}
		double center_d = sqrt((x - otherCircle.x) * (x - otherCircle.x)
			+ (y - otherCircle.y) * (y - otherCircle.y));
		if (center_d != 0) {
			double a = (r * r - otherCircle.r * otherCircle.r + center_d * center_d) / (2 * center_d);
			double x0 = x + a / center_d * (otherCircle.x - x);
			double y0 = y + a / center_d * (otherCircle.y - y);
			if ((center_d == r + otherCircle.r) || (center_d == abs(r - otherCircle.r))) {
				nodes.insert(Point(trans(x0), trans(y0)));
				/*cout << x0 << "," << y0 << endl;*/
			}
			else if ((center_d > abs(r - otherCircle.r)) && (center_d < r + otherCircle.r)) {
				double h = sqrt(r * r - a * a);
				double x1 = x0 - h / center_d * (otherCircle.y - y);
				double y1 = y0 + h / center_d * (otherCircle.x - x);
				double x2 = x0 + h / center_d * (otherCircle.y - y);
				double y2 = y0 - h / center_d * (otherCircle.x - x);
				nodes.insert(Point(trans(x1), trans(y1)));
				nodes.insert(Point(trans(x2), trans(y2)));
				/*cout << x1 << "," << y1 << endl;
				cout << x2 << "," << y2 << endl;*/
			}
		}
	}

	void intersect_L(Line line) {
		if (line.k == INFINITY) {
			double d = abs(line.b - x);
			if (d < r) {
				double offset = sqrt(r * r - d * d);
				double y1 = y + offset;
				double y2 = y - offset;
				nodes.insert(Point(line.b, trans(y1)));
				nodes.insert(Point(line.b, trans(y2)));
				/*cout << line.b << "," << y1 << endl;
				cout << line.b << "," << y2 << endl;*/
			}
			else if (d == r) {
				nodes.insert(Point(line.b, y));
				/*cout << line.b << "," << y << endl;*/
			}
		}
		else {
			double c = -x, d = -y, k = line.k, b = line.b;
			double delta = k * k * r * r + r * r - c * c * k * k + 2 * c * d * k +
				2 * b * c * k - d * d - 2 * b * d - b * b;
			if (delta > 0) {
				delta = sqrt(delta);
				double x1 = -((delta + k * d + k * b + c) / (k * k + 1));
				double y1 = -((k * delta + k * c + d * k * k - b) / (k * k + 1));
				double x2 = (delta - k * d - k * b - c) / (k * k + 1);
				double y2 = -((-k * delta + k * c + d * k * k - b) / (k * k + 1));
				nodes.insert(Point(trans(x1), trans(y1)));
				nodes.insert(Point(trans(x2), trans(y2)));
				//cout << x1 << "," << y1 << endl;
				//cout << x2 << "," << y2 << endl;
			}
			else if (delta == 0) {
				double x1 = (-k * d - k * b - c) / (k * k + 1);
				double y1 = (b - d * k * k - k * c) / (k * k + 1);
				nodes.insert(Point(trans(x1), trans(y1)));
				/*cout << x1 << "," << y1 << endl;*/
			}
		}
	}

	void intersect_R(Ray ray) {
		if (ray.k == INFINITY) {
			double d = abs(ray.b - x);
			if (d < r) {
				double offset = sqrt(r * r - d * d);
				double y1 = y + offset;
				double y2 = y - offset;
				Point p1 = Point(ray.b, trans(y1));
				Point p2 = Point(ray.b, trans(y2));
				if (ray.onRay(p1)) {
					nodes.insert(p1);
				}
				if (ray.onRay(p2)) {
					nodes.insert(p2);
				}
				/*cout << line.b << "," << y1 << endl;
				cout << line.b << "," << y2 << endl;*/
			}
			else if (d == r) {
				Point p = Point(ray.b, trans(y));
				if (ray.onRay(p)) {
					nodes.insert(p);
				}
				/*cout << line.b << "," << y << endl;*/
			}
		}
		else {
			double c = -x, d = -y, k = ray.k, b = ray.b;
			double delta = k * k * r * r + r * r - c * c * k * k + 2 * c * d * k +
				2 * b * c * k - d * d - 2 * b * d - b * b;
			if (delta > 0) {
				delta = sqrt(delta);
				double x1 = -((delta + k * d + k * b + c) / (k * k + 1));
				double y1 = -((k * delta + k * c + d * k * k - b) / (k * k + 1));
				double x2 = (delta - k * d - k * b - c) / (k * k + 1);
				double y2 = -((-k * delta + k * c + d * k * k - b) / (k * k + 1));
				Point p1 = Point(x1, trans(y1));
				Point p2 = Point(x2, trans(y2));
				if (ray.onRay(p1)) {
					nodes.insert(p1);
				}
				if (ray.onRay(p2)) {
					nodes.insert(p2);
				}
				//cout << x1 << "," << y1 << endl;
				//cout << x2 << "," << y2 << endl;
			}
			else if (delta == 0) {
				double x1 = (-k * d - k * b - c) / (k * k + 1);
				double y1 = (b - d * k * k - k * c) / (k * k + 1);
				Point p = Point(trans(x1), trans(y1));
				if (ray.onRay(p)) {
					nodes.insert(p);
				}
				/*cout << x1 << "," << y1 << endl;*/
			}
		}
	}

	void intersect_S(Segment segment) {
		if (segment.k == INFINITY) {
			double d = abs(segment.b - x);
			if (d < r) {
				double offset = sqrt(r * r - d * d);
				double y1 = y + offset;
				double y2 = y - offset;
				Point p1 = Point(segment.b, trans(y1));
				Point p2 = Point(segment.b, trans(y2));
				if (segment.onSegment(p1)) {
					nodes.insert(p1);
				}
				if (segment.onSegment(p2)) {
					nodes.insert(p2);
				}
				/*cout << line.b << "," << y1 << endl;
				cout << line.b << "," << y2 << endl;*/
			}
			else if (d == r) {
				Point p = Point(segment.b, trans(y));
				if (segment.onSegment(p)) {
					nodes.insert(p);
				}
				/*cout << line.b << "," << y << endl;*/
			}
		}
		else {
			double c = -x, d = -y, k = segment.k, b = segment.b;
			double delta = k * k * r * r + r * r - c * c * k * k + 2 * c * d * k +
				2 * b * c * k - d * d - 2 * b * d - b * b;
			if (delta > 0) {
				delta = sqrt(delta);
				double x1 = -((delta + k * d + k * b + c) / (k * k + 1));
				double y1 = -((k * delta + k * c + d * k * k - b) / (k * k + 1));
				double x2 = (delta - k * d - k * b - c) / (k * k + 1);
				double y2 = -((-k * delta + k * c + d * k * k - b) / (k * k + 1));
				Point p1 = Point(x1, trans(y1));
				Point p2 = Point(x2, trans(y2));
				if (segment.onSegment(p1)) {
					nodes.insert(p1);
				}
				if (segment.onSegment(p2)) {
					nodes.insert(p2);
				}
				//cout << x1 << "," << y1 << endl;
				//cout << x2 << "," << y2 << endl;
			}
			else if (delta == 0) {
				double x1 = (-k * d - k * b - c) / (k * k + 1);
				double y1 = (b - d * k * k - k * c) / (k * k + 1);
				Point p = Point(trans(x1), trans(y1));
				if (segment.onSegment(p)) {
					nodes.insert(p);
				}
				/*cout << x1 << "," << y1 << endl;*/
			}
		}
	}
};