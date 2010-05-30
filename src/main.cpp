#include <cstdio>
#include <iostream>
#include <highgui.h>

#include <boost/program_options.hpp>

#include "RubiksCubeLocalizator.h"

//using namespace boost::program_options;
namespace po = boost::program_options;
using namespace std;
int main(int argc, char** argv)
{
	po::options_description desc("Allowed optionsssssssss");
	desc.add_options()("help", "produce help message")("compression",
			po::value<int>(), "set compression level");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	if (vm.count("help"))
	{
		cout << desc << "\n";
		return 1;
	}
	if (vm.count("compression"))
	{
		cout << "Compression level was set to " << vm["compression"].as<int> ()
				<< ".\n";
	}
	else
	{
		cout << "Compression level was not set.\n";
	}
	return 0;

	if (argc != 2)
	{
		printf("Uzycie: %s <plik z obrazkiem>\n", argv[0]);
		return 1;
	}

	char *imageFilename = argv[1];

	printf("Wczytywanie pliku \"%s\"\n", imageFilename);
	IplImage* original = cvLoadImage(imageFilename);
	if (original == NULL)
	{
		printf("Nie udalo sie wczytac pliku.\n");
		return 1;
	}
	IplImage* afterLocalization = cvCloneImage(original);
	cvNamedWindow("Oryginalny", CV_WINDOW_AUTOSIZE );

	cvShowImage("Oryginalny", original);

	RubiksCubeLocalizator rkl;
	if (rkl.locateCube(afterLocalization))
	{
		printf("Zlokalizowano kostke.\n");
		cvNamedWindow("Po lokalizacji");
		cvShowImage("Po lokalizacji", afterLocalization);
	}

	cvWaitKey(0);

	cvReleaseImage(&original);
	cvReleaseImage(&afterLocalization);
	cvDestroyWindow("Po lokalizacji");
	cvDestroyWindow("Oryginalny");
}
