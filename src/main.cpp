#include <cstdio>
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>

#include <boost/program_options.hpp>

#include "RubiksCubeLocalizator.h"
#include "RKLConfig.h"
#include "logger.h"

//using namespace boost::program_options;
namespace po = boost::program_options;
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	try {
		// process command line options
		string configFile;
		po::options_description programOptions("POBR - Rubik\'s cube recognition - Mateusz Boryn 2010");
		programOptions.add_options()("help", "print help")("image,i", po::value<string>(), "image file to load")(
				"config,c", po::value<string>(&configFile)->default_value("rkl.conf"), "config file")("log", po::value<
				bool>(&log_enabled)->default_value(false), "print more info")("log_dbg", po::value<bool>(
				&log_dbg_enabled)->default_value(false), "print even more info");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, programOptions), vm);
		po::notify(vm);
		if (vm.count("help")) {
			cout << programOptions << "\n";
			return 1;
		}

		// create RKL localizator
		RKLConfig config;
		config.readConfig(configFile);

		RubiksCubeLocalizator rkl(config);

		string imageFilename;
		if (vm.count("image")) {
			imageFilename = vm["image"].as<string> ();
			cout << "Image file: " << imageFilename << ".\n";
		} else {
			throw std::runtime_error("Image file not supplied.");
		}

		Mat original = imread(imageFilename.c_str());
		if (original.data == NULL) {
			cout << "Error loading image file.\n" << programOptions << "\n";
			return 1;
		}
		namedWindow("Original", CV_WINDOW_AUTOSIZE);
		imshow("Original", original);

		if (rkl.locateCube(original)) {
			Mat afterLocalization = original.clone();
			for (int i = 0; i < rkl.walls.size(); ++i) {
				if(rkl.walls[i].bricks.size() == 0){
					continue;
				}
				Point p1, p2;
				int lineColor = 0;
				p1 = rkl.walls[i].bricks[0].getMassCenter();
				circle(afterLocalization, p1, 5, CV_RGB(255 - lineColor, lineColor, 0), 2);
				for (int j = 1; j < rkl.walls[i].bricks.size(); ++j) {
					p2= rkl.walls[i].bricks[j].getMassCenter();
					lineColor = j * 255 / rkl.walls[i].bricks.size();
					line(afterLocalization, p1, p2, CV_RGB(255 - lineColor, lineColor, 0));
					circle(afterLocalization, p2, 5, CV_RGB(255 - lineColor, lineColor, 0), 2);
					p1 = p2;
				}
			}

			namedWindow("After localization", CV_WINDOW_AUTOSIZE);
			imshow("After localization", afterLocalization);
		}

		cvWaitKey(0);
	} catch (const exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}
