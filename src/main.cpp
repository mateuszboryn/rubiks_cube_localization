#include <cstdio>
#include <iostream>
#include <string>
#include <cv.h>
#include <highgui.h>

#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>

#include "RubiksCubeLocalizator.h"
#include "RKLConfig.h"
#include "logger.h"
#include "OpenCvVideoCaptureSource.h"
#include "FileSource.h"

namespace po = boost::program_options;
using namespace std;
using namespace cv;
using boost::shared_ptr;

void showImage(const char* label, const Mat& image);

int main(int argc, char** argv)
{
	try {
		RubiksCubeLocalizator rkl;

		// process command line options
		string configFile;
		po::options_description programOptions("POBR - Rubik\'s cube recognition - Mateusz Boryn 2010");
		programOptions.add_options()("help", "print help");
		programOptions.add_options()("image,i", po::value<string>(), "image file to load");
		programOptions.add_options()("config,c", po::value<string>(&configFile)->default_value("rkl.conf"), "config file");
		programOptions.add_options()("log", po::value<bool>(&log_enabled)->default_value(false), "print more info");
		programOptions.add_options()("log_dbg", po::value<bool>(&log_dbg_enabled)->default_value(false), "print even more info");
		programOptions.add_options()("camera-number", po::value<int>(), "number of camera device");
		programOptions.add_options()("show-filtered", po::value<bool>(&rkl.showFilteredImage)->default_value(false), "show image after filtering");
		programOptions.add_options()("show-channels", po::value<bool>(&rkl.getColorClassifier().showColorChannels)->default_value(false), "show color channels");
		programOptions.add_options()("show-colors", po::value<bool>(&rkl.showColorsClassifiedImage)->default_value(false), "show image after color classification");
		programOptions.add_options()("show-segments", po::value<bool>(&rkl.showSegments)->default_value(false), "show segments after segments filtering");
		programOptions.add_options()("hue-shift", po::value<int>(&rkl.getColorClassifier().shift)->default_value(0), "");
		programOptions.add_options()("min-gray", po::value<int>(&rkl.getColorClassifier().minGray)->default_value(0), "min gray");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, programOptions), vm);
		po::notify(vm);
		if (vm.count("help")) {
			cout << programOptions << "\n";
			return 1;
		}

		// create RKL localizator
//		RKLConfig config;
//		config.readConfig(configFile);
//		rkl.setConfig(config);

		shared_ptr<ImageSource> source;
		bool processOnlyOneFrame = false;
		string imageFilename;
		if (vm.count("image")) {
			imageFilename = vm["image"].as<string> ();
			cout << "Image file: " << imageFilename << ".\n";
			source = shared_ptr<ImageSource> (new FileSource(imageFilename));
			processOnlyOneFrame = true;
		} else if (vm.count("camera-number")) {
			int cam_no = vm["camera-number"].as<int> ();
			cout << "cam_no: " << cam_no << ".\n";
			source = shared_ptr<ImageSource> (new OpenCvVideoCaptureSource(cam_no));
		} else {
			throw std::runtime_error("No source supplied.");
		}

		Mat image;

		namedWindow("Kostka rubika", CV_WINDOW_AUTOSIZE);
		while (1) {
			source->waitForFrame();
			source->getFrame(image);
			if (rkl.locateCube(image)) {
				for (list<RKWall>::const_iterator it = rkl.walls.begin(); it != rkl.walls.end(); ++it) {
					it->draw(image);
				}
			}

			imshow("Kostka rubika", image);

			if (processOnlyOneFrame) {
				while (waitKey(0) != 27)
					;
				break;
			} else {
				if (waitKey(30) == 27) {
					break;
				}
			}
		}
	} catch (const exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

void showImage(const char* label, const Mat& image)
{
	namedWindow(label, CV_WINDOW_AUTOSIZE);
	imshow(label, image);
}

