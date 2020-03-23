#pragma once
#include <iostream>
using namespace std;

void error_type1() {
	cerr << "WRONG FORMAT" << endl;
	exit(-1);
}

bool type2_check(double x1, double y1, double x2, double y2) {
	return (x1 == x2) && (y1 == y2);
}

void error_type2() {
	cerr << "CANNOT SOLVE THE SAME POINTS" << endl;
	exit(-1);
}

void error_type3() {
	cout << "INFINITE INTERSECTANT POINTS" << endl;
	exit(0);
}

void error_type4() {
	cerr << "RADIUS CANNOT BE LESS THAN ZERO" << endl;
	exit(-1);
}

void error_type5() {
	cerr << "COMMAND ERROR" << endl;
	exit(-1);
}

void command_check(int argc, char* argv[]) {
	if (argc != 5 || strcmp(argv[1], "-i") != 0 || strcmp(argv[3], "-o") != 0) {
		error_type5();
	}
}
