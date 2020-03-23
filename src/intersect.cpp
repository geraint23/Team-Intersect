#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Circle.h"

using namespace std;

vector<Line> lines;
vector<Circle> circles;
vector<Ray> rays;
vector<Segment> segments;

void error() {
	cerr << "Wrong format!" << endl;
	exit(1);
}

void add_graph(ifstream &in) {
	int N;
	char type;
	in >> N;
	while (N--) {
		in >> type;
		if (type == 'L') {
			double x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			if (!in) {
				error();
			}
			lines.push_back(Line(x1, y1, x2, y2));
		}
		else if (type == 'C') {
			double x, y, r;
			in >> x >> y >> r;
			if (!in) {
				error();
			}
			circles.push_back(Circle(x, y, r));
		}
		else if (type == 'R') {
			double x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			if (!in) {
				error();
			}
			rays.push_back(Ray(x1, y1, x2, y2));
		}
		else if (type == 'S') {
			double x1, y1, x2, y2;
			in >> x1 >> y1 >> x2 >> y2;
			if (!in) {
				error();
			}
			segments.push_back(Segment(x1, y1, x2, y2));
		}
		else {
			error();
		}
	}
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

int main(int argc, char* argv[]) {
	ifstream in;
	ofstream out;
	for (int i = 0; i <= argc - 1; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			in.open(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-o") == 0) {
			out.open(argv[i + 1]);
		}
	}
	add_graph(in);
	intersect();
	/*cout << "All nodes:" << endl;
	for (auto it : nodes) {
		cout << it.x << "," << it.y << endl;
	}*/
	out << nodes.size() << endl;
	return 0;
}