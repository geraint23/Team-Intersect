#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "..\src\Circle.h"

using namespace std;

vector<Line> lines;
vector<Circle> circles;
vector<Ray> rays;
vector<Segment> segments;

#define random(a, b) (rand() % (b - a + 1)) + a

int random_para() {
	return random(-10, 10);
}

void add_graph() {
	srand((int)time(NULL));
	int N;
	int type;
	cin >> N;
	int l = 0, c = 0, r = 0, s = 0;
	while (N--) {
		type = random(0, 3);
		if (type == 0) {
			lines.push_back(Line(random_para(), random_para(), random_para(), random_para()));
			l++;
		}
		else if (type == 1) {
			circles.push_back(Circle(random_para(), random_para(), random_para()));
			c++;
		}
		else if (type == 2) {
			rays.push_back(Ray(random_para(), random_para(), random_para(), random_para()));
			r++;
		}
		else if (type == 3) {
			segments.push_back(Segment(random_para(), random_para(), random_para(), random_para()));
			s++;
		}
	}
	cout << l << " lines" << endl;
	cout << c << " circles" << endl;
	cout << r << " rays" << endl;
	cout << s << " segments" << endl;
}

void intersect() {
	int lineSize = (int)lines.size();
	int circleSize = (int)circles.size();
	int raySize = (int)rays.size();
	int segmentSize = (int)segments.size();
	int N;
	for (N = 0; N <= lineSize - 2; N++) {	// 直线-直线
		for (int i = N + 1; i <= lineSize - 1; i++) {
			lines[N].intersect_L(lines[i]);
		}
	}
	for (N = 0; N <= circleSize - 2; N++) {	// 圆-圆
		for (int i = N + 1; i <= circleSize - 1; i++) {
			circles[N].intersect_C(circles[i]);
		}
	}
	for (N = 0; N <= circleSize - 1; N++) {	// 直线-圆
		for (int i = 0; i <= lineSize - 1; i++) {
			circles[N].intersect_L(lines[i]);
		}
	}
	for (N = 0; N <= circleSize - 1; N++) {	// 圆-射线
		for (int i = 0; i <= raySize - 1; i++) {
			circles[N].intersect_R(rays[i]);
		}
	}
	for (N = 0; N <= circleSize - 1; N++) {	// 圆-线段
		for (int i = 0; i <= segmentSize - 1; i++) {
			circles[N].intersect_S(segments[i]);
		}
	}
	for (N = 0; N <= raySize - 2; N++) {	// 射线-射线
		for (int i = N + 1; i <= raySize - 1; i++) {
			rays[N].intersect_R(rays[i]);
		}
	}
	for (N = 0; N <= raySize - 1; N++) {	// 直线-射线
		for (int i = 0; i <= lineSize - 1; i++) {
			rays[N].intersect_L(lines[i]);
		}
	}
	for (N = 0; N <= segmentSize - 1; N++) {	// 直线-线段
		for (int i = 0; i <= lineSize - 1; i++) {
			segments[N].intersect_L(lines[i]);
		}
	}
	for (N = 0; N <= segmentSize - 2; N++) {	// 线段-线段
		for (int i = N + 1; i <= segmentSize - 1; i++) {
			segments[N].intersect_S(segments[i]);
		}
	}
	for (N = 0; N <= segmentSize - 1; N++) {	// 线段-射线
		for (int i = 0; i <= raySize - 1; i++) {
			segments[N].intersect_R(rays[i]);
		}
	}
}

int main() {
	add_graph();
	intersect();
	/*cout << "All nodes:" << endl;
	for (auto it : nodes) {
		cout << it.x << "," << it.y << endl;
	}*/
	cout << nodes.size() << endl;
	return 0;
}