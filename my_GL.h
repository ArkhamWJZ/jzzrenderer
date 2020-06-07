//
// Created by 万健洲 on 2020/6/7.
//

#ifndef JZZRENDERER_MY_GL_H
#define JZZRENDERER_MY_GL_H

#include "Vector.h"
#include <bits/stdc++.h>

using namespace std;

extern matrix ModelView;
extern matrix Projection;
extern matrix Viewport;
extern int height;
extern int width;

class my_GL {

};
void set_pixel(int x, int y, vec3f color, vector<vec3f>& fram_buf);
void line_slope(vec2i a, vec2i b, vector<vec3f>& fram_buf, vec3f color);
void line(vec2i a, vec2i b, vector<vec3f>& fram_buf, vec3f color);
void triangle_slope(vec2i a, vec2i b, vec2i c, vector<vec3f>& fram_buf, vec3f color);
void triangle(vec2i a, vec2i b, vec2i c, vector<vec3f>& fram_buf, vec3f color);
#endif //JZZRENDERER_MY_GL_H
