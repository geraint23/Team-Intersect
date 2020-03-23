#pragma once

class Ray {
public:
	double k;
	double b;
	double x1;
	double y1;	// ���(x1,y1)
	double x2;
	double y2;	// ������һ��(x2,y2)

	Ray(double x1, double y1, double x2, double y2) {	// б�ʴ���ʱb�ǽؾ࣬������ʱb��x����
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

	bool onRay(Point p) {
		double xjudge = this->x2 - this->x1;
		double yjudge = this->y2 - this->y1;
		if (xjudge >= 0 && yjudge >= 0) {
			return(p.x >= this->x1 && p.y >= this->y1);
		}
		if (xjudge >= 0 && yjudge <= 0) {
			return (p.x >= this->x1 && p.y <= this->y1);
		}
		if (xjudge <= 0 && yjudge >= 0) {
			return(p.x <= this->x1 && p.y >= this->y1);
		}
		if (xjudge <= 0 && yjudge <= 0) {
			return(p.x <= this->x1 && p.y <= this->y1);
		}
		return false;
	}

	bool preprocess(Ray otherRay) { // �����������һ��������ͬ
		if (x1 == otherRay.x1 && y1 == otherRay.y1) {
			if ((x2 - x1) * (otherRay.x2 - x1) <= 0) {
				if ((x2 - x1) * (otherRay.x2 - x1) < 0) {
					return true;
				}
				else {	// �������ߴ���һ���������ֱx��Ĺ�ϵ
					if ((x2 == x1) && (otherRay.x2 == x1)) {
						if ((y2 - y1) * (otherRay.y2 - y1)) {
							return true;
						}
						else {
							return false;
						}
					}
					else {	// һ�����ߴ�ֱx һ������ֱ
						return true;
					}
				}
			}
			return false;
		}
		return false;
	}

	void intersect_R(Ray otherRay) {
		if (preprocess(otherRay)) {
			nodes.insert(Point(x1, y1));
			return;
		}
		double x, y;
		if (k != otherRay.k) {
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
			if (this->onRay(p) && otherRay.onRay(p)) {
				nodes.insert(p);
			}
			/*cout << x << "," << y << endl;*/
		}
	}

	void intersect_L(Line otherline) {
		double x, y;
		if (k != otherline.k) {
			if (k == INFINITY) {
				x = b;
				y = otherline.k * x + otherline.b;
			}
			else if (otherline.k == INFINITY) {
				x = otherline.b;
				y = k * x + b;
			}
			else {
				x = (otherline.b - b) / (k - otherline.k);
				y = k * x + b;
			}
			Point p = Point(trans(x), trans(y));
			if (this->onRay(p)) {
				nodes.insert(p);
			}
			/*cout << x << "," << y << endl;*/
		}
	}
};