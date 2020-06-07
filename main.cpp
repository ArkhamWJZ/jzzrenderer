//
// Created by 万健洲 on 2020/6/4.
//

#include "Vector.h"
#include "my_GL.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;

int main(){
    vector<vec3f> fram_buffer;
    height = 700; width = 700;
    fram_buffer.resize(height*width);

    vec2i t0[3] = {vec2i(10, 70),   vec2i(50, 160),  vec2i(70, 80)};
    triangle(t0[0], t0[1], t0[2], fram_buffer, {1,0,0});

    cv::Mat image(width, height, CV_32FC3, fram_buffer.data());
    cv::Mat RGBImage;
    cvtColor(image, RGBImage, CV_BGR2RGB);
    cv::imshow("image", RGBImage);
    cv::waitKey();

    return 0;
}