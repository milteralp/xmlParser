#pragma once

#include <iostream>
#include<opencv2/opencv.hpp>
#include <stdio.h>
#include <time.h>


using namespace std;
using namespace cv;

class Ellipse {
public:

	struct Circle{
		Point2f center;
		char entranceType;
	};
	// Constructor for Ellipse.
	Ellipse(string filename);

	// Draws ellipses on center and end regions of entrance rectangles.
	void drawCircle(Mat image, vector<Ellipse::Circle> &circles);

	Mat frame;
};
