#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include "stdlib.h"
#include "stdio.h"

using namespace cv;
using namespace std;

class RPiCamera : VideoCapture
{
    private:    

    public:
    /**
     * @brief Construct a new RPiCamera object
     * 
     */
    RPiCamera(int index = 0, int apiPreference = CAP_V4L2) : VideoCapture(index, apiPreference) {}
};