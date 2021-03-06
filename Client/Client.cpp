#include <opencv2\core\core.hpp>
#include "stdafx.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <time.h> 
#include <stdio.h>

using namespace cv;
using namespace std;
int main()

{
	string input_flag;
	cout << "If you want to\ntrain face input 1\nto detecte face input 2\n";
	cin >> input_flag;
	string name, namecmd;
	if (input_flag == "1") {
	cout << "Please enter your name:   ";
	cin >> name;
	namecmd = "md train_dir_" + name;
	system(namecmd.c_str());
	}
	VideoCapture capture(0);
	if (!capture.isOpened())
		return 1;
	Mat frame;
	int count = 1;
	char file_name[30];
	while (1)
	{
		capture >> frame;
		imshow("video", frame);
		if ((count % 4) == 0) {
			sprintf_s(file_name, ".\\train_dir_%s\\%d.jpg", name.c_str(), count);
			printf(file_name);
			imwrite(file_name, frame);
		}
		if ((input_flag == "2") & (count == 20)) {
			imwrite(".\\test.jpg", frame);
			system("python client_for_dete.py test.jpg 10.10.2.220 22338");
			break;
		}
		count++;
		if (cvWaitKey(32) > 0) {
			break;
		}
	}
	char train_cmd[200];
	if (input_flag == "1") {
		sprintf_s(train_cmd, "python client_for_train.py .\\train_dir_%s 10.10.2.220 22338 %s", name.c_str(), name.c_str());
		system(train_cmd);
	}
	return 0;
}