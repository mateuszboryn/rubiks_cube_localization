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
		// process command line options
		string configFile;
		po::options_description programOptions("POBR - Rubik\'s cube recognition - Mateusz Boryn 2010");
		programOptions.add_options()("help", "print help");
		programOptions.add_options()("image,i", po::value<string>(), "image file to load");
		programOptions.add_options()("config,c", po::value<string>(&configFile)->default_value("rkl.conf"),
				"config file");
		programOptions.add_options()("log", po::value<bool>(&log_enabled)->default_value(false), "print more info");
		programOptions.add_options()("log_dbg", po::value<bool>(&log_dbg_enabled)->default_value(false),
				"print even more info");
		programOptions.add_options()("camera-number", po::value<int>(), "number of camera device");

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

		shared_ptr<ImageSource> source;

		string imageFilename;
		if (vm.count("image")) {
			imageFilename = vm["image"].as<string> ();
			cout << "Image file: " << imageFilename << ".\n";
			source = shared_ptr<ImageSource> (new FileSource(imageFilename));
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
				for (int i = 0; i < rkl.walls.size(); ++i) {
					rkl.walls[i].draw(image);
				}
			}

			imshow("Kostka rubika", image);

			if (waitKey(50) == 27) {
				break;
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

