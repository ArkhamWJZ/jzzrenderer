#include <vector>
#include <cstdlib>
#include <limits>
#include <iostream>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "our_gl.h"

Model *model        = NULL;

const int width  = 800;
const int height = 800;

Vec3f       eye(1.2,-.8,3);
Vec3f    center(0,0,0);
Vec3f        up(0,1,0);

struct ZShader : public IShader {
    mat<4,3,float> varying_tri;

    virtual Vec4f vertex(int iface, int nthvert) {
        Vec4f gl_Vertex = Projection*ModelView*embed<4>(model->vert(iface, nthvert));
        varying_tri.set_col(nthvert, gl_Vertex);
        return gl_Vertex;
    }

    virtual bool fragment(Vec3f gl_FragCoord, Vec3f bar, TGAColor &color) {
        color = TGAColor(255, 0, 0);
        return false;
    }
};
//计算一个方向上的最大仰角
float max_elevation_angle(float *zbuffer, Vec2f p, Vec2f dir) {
    float maxangle = 0;
    for (float t=0.; t<1000.; t+=1.) {
        Vec2f cur = p + dir*t;
        //出界则返回0
        if (cur.x>=width || cur.y>=height || cur.x<0 || cur.y<0)
            return maxangle;
        float distance = (p-cur).norm();
        if (distance < 1.f)
            continue;
        float elevation = zbuffer[int(cur.x)+int(cur.y)*width]-zbuffer[int(p.x)+int(p.y)*width];
        maxangle = std::max(maxangle, atanf(elevation/distance));
    }
    return maxangle;
}

int main(int argc, char** argv) {
//    if (2>argc) {
//        std::cerr << "Usage: " << argv[0] << "obj/model.obj" << std::endl;
//        return 1;
//    }
    float *zbuffer = new float[width*height];
    for (int i=width*height; i--; zbuffer[i] = -std::numeric_limits<float>::max());
    model = new Model("../obj/diablo3_pose.obj");

    TGAImage frame(width, height, TGAImage::RGB);
    lookat(eye, center, up);
    viewport(width/8, height/8, width*3/4, height*3/4);
    projection(-1.f/(eye-center).norm());

    ZShader zshader;
    for (int i=0; i<model->nfaces(); i++) {
        for (int j=0; j<3; j++) {
            zshader.vertex(i, j);
        }
        triangle(zshader.varying_tri, zshader, frame, zbuffer);
    }

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            if (zbuffer[x+y*width] < -1e5)
                continue;
            float total = 0;
            //感觉上 pi/2 就是这个像素的法向，这里计算平均最大仰角和法向的夹角
            //仰角为0，平坦，与法线夹角 pi/2 处理后是1
            for (float a=0; a<M_PI*2-1e-4; a += M_PI/4) {
                total += M_PI/2 - max_elevation_angle(zbuffer, Vec2f(x, y), Vec2f(cos(a), sin(a)));
            }
            total /= (M_PI/2)*8;
            total = pow(total, 100.f);//增强对比放大差别，要不模型就是全白了，比如说0.99的一百次方是0.33
            frame.set(x, y, TGAColor(total*255, total*255, total*255));
        }
    }

    frame.flip_vertically();
    frame.write_tga_file("framebuffer.tga");
    delete [] zbuffer;
    delete model;
    return 0;
}

