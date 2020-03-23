#pragma once
#include <iostream>
using namespace std;

#define MAX_COOR 1e5

bool coor_overlim(double x1, double y1, double x2, double y2 = 0) {
	return x1 > MAX_COOR || x1 < -MAX_COOR ||
		y1 > MAX_COOR || y1 < -MAX_COOR ||
		x2 > MAX_COOR || x2 < -MAX_COOR ||
		y2 > MAX_COOR || y2 < -MAX_COOR;
}

void error_type1(int error_type) {
	cerr << "WRONG FORMAT" << endl;
	switch (error_type)
	{
	case 1:cout << "Please tell me how many figures do you want first" << endl;
		cout << "And please ensure your input is a right number..." << endl;
		break;
	case 2:cout << "If you want a line,plase input as: L x1 y1 x2 y2" << endl;
		cout << "If you want a circle,plase input as: C x y r" << endl;
		cout << "And please ensure your input is a number..." << endl;
		break;
	case 3:cout << "Sorry,we do not support this type yet..." << endl;
		break;
	case 4:cout << "Sorry,your input N is wrong..." << endl;
		break;
	default:
		break;
	}
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
	cout << "Please use the right arguments as: -i <path to input file> -o <path to output file>..." << endl;
	exit(-1);
}

void command_check(int argc, char* argv[]) {
	if (argc != 5 || strcmp(argv[1], "-i") != 0 || strcmp(argv[3], "-o") != 0) {
		error_type5();
	}
}

void error_type6() {
	cerr << "COORDINATE EXCEEDS LIMIT" << endl;
	cout << "Coordinate should be within -100000 and 100000" << endl;
	exit(-1);
}
