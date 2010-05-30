PROJECT(rubiks_cube_localization)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FIND_PACKAGE(Boost REQUIRED program_options)
FIND_PACKAGE(OpenCV REQUIRED)

SET(rubiks_cube_localization_LIBRARIES 
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	${OpenCV_LIBS}
)

ADD_DEFINITIONS(-Wall -pedantic)

ADD_EXECUTABLE(rkl main.cpp RubiksCubeLocalizator.cpp)
TARGET_LINK_LIBRARIES(rkl ${rubiks_cube_localization_LIBRARIES})
