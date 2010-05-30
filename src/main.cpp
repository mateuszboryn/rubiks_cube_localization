#include <cstdio>
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>

#include <boost/program_options.hpp>

#include "RubiksCubeLocalizator.h"

//using namespace boost::program_options;
namespace po = boost::program_options;
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	string configFile;
	po::options_description programOptions("POBR - Rubik\'s cube recognition - Mateusz Boryn 2010");
	programOptions.add_options()("help", "print help")("image,i", po::value<string>(), "image file to load")("config,c", po::value<string>(&configFile)->default_value("rkl.conf"), "image file to load");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, programOptions), vm);
	po::notify(vm);
	if (vm.count("help")) {
		cout << programOptions << "\n";
		return 1;
	}

	string imageFilename;
	if (vm.count("image")) {
		imageFilename = vm["image"].as<string> ();
		cout << "Image file: " << imageFilename << ".\n";
	} else {
		cout << "No image file supplied.\n" << programOptions << "\n";
		return 1;
	}

	Mat original = imread(imageFilename.c_str());
	if (original.data == NULL) {
		cout << "Error loading image file.\n" << programOptions << "\n";
		return 1;
	}
	Mat afterLocalization = original.clone();
	namedWindow("Original", CV_WINDOW_AUTOSIZE);

	imshow("Original", original);

	RubiksCubeLocalizator rkl;
	if (rkl.locateCube(afterLocalization)) {
		namedWindow("After localization", CV_WINDOW_AUTOSIZE);
		imshow("After localization", afterLocalization);
	}

	cvWaitKey(0);
}
