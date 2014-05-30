#include "../Header/Ellipse.h"
// Draws circle on center of entrance and exit regions.

	// Constructor
	Ellipse::Ellipse(string filename){
		frame = imread(filename);
		if(!frame.data)
			cout << "Location of the image is expect!" << endl << "i.e /home/visus/Desktop/enteranceMap.bmp" << endl << "No data in the frame!" << endl;
		else {
			// Draw rectangles on corners
			rectangle(frame, Point(0,0), Point(5, 5), Scalar(0,0,0), -1);
			rectangle(frame, Point(frame.size().width-5, 0), Point(frame.size().width, 5), Scalar(0,0,0), -1);
			rectangle(frame, Point(0, frame.size().height-5), Point(5, frame.size().height), Scalar(0,0,0), -1);
			rectangle(frame, Point(frame.size().width-5, frame.size().height-5), Point(frame.size().width ,frame.size().height), Scalar(0,0,0), -1);
		}
	}

	// Draws circle on center of entrance/exit regions and returns center points in a vector.
	void Ellipse::drawCircle(Mat image, vector<Ellipse::Circle> &circles){

		Mat cimage(image);
		Mat threshold_output;
		cvtColor(cimage, cimage, CV_RGB2GRAY); // image.convertTo(cimage, CV_8UC1);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		namedWindow("Contours", WINDOW_AUTOSIZE);
		imshow("Contours", cimage);

		threshold( cimage, threshold_output, 15, 255, THRESH_BINARY);
		findContours(threshold_output, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		vector<RotatedRect> minRect( contours.size() );
		//vector<RotatedRect> minEllipse( contours.size() );
		circles.resize( contours.size() );


		for(unsigned int i=0; i<contours.size(); i++){
			minRect[i] = minAreaRect( Mat( contours[i] ));
			circles[i].center = minRect[i].center; // PROBLEM

			//if(contours[i].size() > 5)
				//minEllipse[i] = fitEllipse( Mat( contours[i]));
		}

		Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
		for(unsigned int i=0; i<contours.size(); i++){
			circle(drawing, minRect[i].center, 10, Scalar(0,255,255), 1, CV_AA);
			cout << "PointX "<< circles[i].center.x << endl << " PointY " << circles[i].center.y << endl << " Point whole " << circles[i].center << endl;
		}
		namedWindow("Ellipses", CV_WINDOW_AUTOSIZE );
		imshow("Ellipses", drawing);
	}
/*
	int main(int argc, char** argv){
		//String filename;
		if(argc != 2){
			cerr << "Image could not be found!" << endl;
			return -1;
		}
		Ellipse ell(argv[1]);

		Mat cur_frame = ell.frame;

		cout << ell.getImagePath() << endl;


		ell.drawCircle(cur_frame);
		waitKey(0);

		return 0;
	}
*/
