PROJECT(rubiks_cube_localization)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(Boost REQUIRED program_options)
FIND_PACKAGE(OpenCV REQUIRED)

SET(rubiks_cube_localization_LIBRARIES 
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	${OpenCV_LIBS}
)

ADD_DEFINITIONS(-Wall -pedantic -Wno-sign-compare -p  -O3)

SET(rubiks_cube_localization_SOURCES 
	main.cpp
	RubiksCubeLocalizator.cpp
	RKLConfig.cpp
	logger.cpp
	ColorDefinition.cpp
	Segment.cpp
	Segmentation.cpp
	ColorClassifier.cpp
	SegmentFilter.cpp
	ShapeFilter.cpp
	SizeFilter.cpp
	RKPattern.cpp
	RKWall.cpp
	ImageSource.cpp
	OpenCvVideoCaptureSource.cpp
	FileSource.cpp
)

ADD_EXECUTABLE(rkl ${rubiks_cube_localization_SOURCES})

SET_TARGET_PROPERTIES(rkl PROPERTIES LINK_FLAGS -p)

TARGET_LINK_LIBRARIES(rkl ${rubiks_cube_localization_LIBRARIES})
