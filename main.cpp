//
// Created by 万健洲 on 2020/6/4.
//

#include "Vector.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;

int height = 700;
int width = 700;

void set_pixel(int x, int y, vec3f color, vector<vec3f>& fram_buf){
    auto ind = x + (height-y)*width;
    fram_buf[ind] = color;
}
void line_slope(vec2f a, vec2f b, vector<vec3f>& fram_buf, vec3f color){
    bool isSwap = false;
    if(abs(a.x - b.x) < abs(a.y - b.y)){
        swap(a.x,a.y);
        swap(b.x,b.y);
        isSwap = true;
    }
    if(a.x > b.x) swap(a,b);

    float k = (b.y - a.y)/(b.x - a.x);
    if(isSwap){
        for (int i = 0; i < b.x - a.x; ++i){
            set_pixel(a.y + i*k,a.x + i,color,fram_buf);
        }
    } else {
        for (int i = 0; i < b.x - a.x; ++i){
            set_pixel(a.x + i,a.y + i*k,color,fram_buf);
        }
    }
}
void line(vec2f& a, vec2f& b, vector<vec3f>& fram_buf, vec3f color){
    bool isSwap = false;
    if(abs(a.x - b.x) < abs(a.y - b.y)){//no steep
        swap(a.x,a.y);
        swap(b.x,b.y);
        isSwap = true;
    }
    if(a.x > b.x){//left-to-right
        swap(a,b);
    }
    float k = abs((b.y - a.y)/(b.x - a.x));
    float error = 0;
    int y = a.y;
    for (int i = a.x; i < b.x; ++i) {
        if(isSwap){
            set_pixel(y, i, color, fram_buf);
        } else {
            set_pixel(i, y, color, fram_buf);
        }
        error += k;
        if(error > 0.5){
            y += (b.y-a.y > 0 ? 1:-1);
            error -= 1;
        }
    }
}
int main(){
    vector<vec3f> fram_buffer;
    fram_buffer.resize(height*width);
    vec3f red = {0,1,0};

    vec2f x1 = {0,700};
    vec2f x2 = {350,350};
    line(x1, x2, fram_buffer, red);

    cv::Mat image(width, height, CV_32FC3, fram_buffer.data());
    cv::Mat RGBImage;
    cvtColor(image, RGBImage, CV_BGR2RGB);
    cv::imshow("image", RGBImage);
    cv::waitKey();

    return 0;
}