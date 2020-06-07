//
// Created by 万健洲 on 2020/6/7.
//

#include "my_GL.h"

matrix ModelView;
matrix Projection;
matrix Viewport;
int height;
int width;

void set_pixel(int x, int y, vec3f color, vector<vec3f>& fram_buf){
    auto ind = x + (height-y)*width;
    fram_buf[ind] = color;
}
void line_slope(vec2i a, vec2i b, vector<vec3f>& fram_buf, vec3f color){
    bool isSwap = false;
    if(abs(a.x - b.x) < abs(a.y - b.y)){
        swap(a.x,a.y);
        swap(b.x,b.y);
        isSwap = true;
    }
    if(a.x > b.x) swap(a,b);

    float k = (b.y - a.y)/float(b.x - a.x);
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
void line(vec2i a, vec2i b, vector<vec3f>& fram_buf, vec3f color){
    bool isSwap = false;
    if(abs(a.x - b.x) < abs(a.y - b.y)){//no steep
        swap(a.x,a.y);
        swap(b.x,b.y);
        isSwap = true;
    }
    if(a.x > b.x){//left-to-right
        swap(a.x,b.x);
        swap(a.y,b.y);
    }
    float k = abs((b.y - a.y)/float(b.x - a.x));

    float error = 0;
    int y = a.y;
    if(isSwap){
        for (int i = a.x; i < b.x; ++i) {
            //cout<<y<<","<<i<<endl;
            set_pixel(y, i, color, fram_buf);
            error += k;
            if(error > 0.5){
                y += (b.y > a.y ? 1:-1);
                error -= 1.f;
            }
        }
    } else {
        for (int i = a.x; i < b.x; ++i) {
            set_pixel(i, y, color, fram_buf);
            error += k;
            if(error > 0.5){
                y += (b.y > a.y ? 1:-1);
                error -= 1.f;
            }
        }
    }
}
void triangle_slope(vec2i a, vec2i b, vec2i c, vector<vec3f>& fram_buf, vec3f color){//二分 相似 斜率
    if(a.y > b.y) swap(a,b);
    if(b.y > c.y) swap(b,c);
    if(a.y > c.y) swap(a,c);

    float total_y = c.y - a.y;
    float first_y = b.y - a.y + 1; // >= 1 避免除0
    for (int i = a.y; i < b.y; ++i) {
        float alpha = (i - a.y) / first_y;
        float beta = (i - a.y) / total_y;

        float x1 = a.x + beta*(c.x - a.x);
        float x2 = a.x + alpha*(b.x - a.x);

        if (x1 > x2) swap(x1,x2);
        for (int j = x1; j < x2; ++j) {
            set_pixel(j,i,color,fram_buf);
        }
    }

    float second_y = c.y - b.y;
    for (int k = b.y; k < c.y; ++k) {
        float alpha = (k - a.y) / second_y;
        float beta = (k - a.y) / total_y;

        float x1 = a.x + (c.x - a.x)*beta;
        float x2 = b.x + (c.x - b.x)*alpha;
        if(x1 > x2) swap(x1,x2);
        for (int i = x1; i < x2; ++i) {
            set_pixel(i,k,color,fram_buf);
        }
    }
}
vec3f barycentric(vec2i p, vec2i a, vec2i b, vec2i c){
    vec3f u = cross(vec3f(c.x-a.x, b.x-a.x, a.x-p.x), vec3f(c.y-a.y, b.y-a.y, a.y-p.y));
    return vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
}
bool isInTriangle(int x, int y, vec2i a, vec2i b, vec2i c){
    vec2i p = {x,y};
    vec3f bary = barycentric(p,a,b,c);
    if(bary.x<0 || bary.y<0 || bary.z<0) return false;
    return true;
}
void triangle(vec2i a, vec2i b, vec2i c, vector<vec3f>& fram_buf, vec3f color){
    //bounding box
    vec2i boundingBoxPoint1 = {max(0,min({a.x,b.x,c.x})),max(0,min({a.y,b.y,c.y}))};
    vec2i boundingBoxPoint2 = {min(width,max({a.x,b.x,c.x})),min(height,max({a.y,b.y,c.y}))};

    for (int i = boundingBoxPoint1.x; i < boundingBoxPoint2.x; ++i) {
        for (int j = boundingBoxPoint1.y; j < boundingBoxPoint2.y; ++j) {
            if(isInTriangle(i,j,a,b,c)){

                set_pixel(i,j,color,fram_buf);
            }
        }
    }

}