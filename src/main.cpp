#include <cstdio>
#include <highgui.h>

#include "RubiksCubeLocalizator.h"

int main(int argc, char** argv)
{
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
