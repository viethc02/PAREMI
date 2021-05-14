#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "CommonFunction.h"

typedef struct Geometricformat
{
    public:
        Geometricformat(int left , int top , int width , int height) {left_ = left; top_= top; width_ = width; height_ = height;}

        int left_;
        int top_;
        int width_;
        int height_;
};

typedef struct ColorData
{
    ColorData(Uint8 red , Uint8 green , Uint8 blue) {red_ = red; green_ = green; blue_ = blue;}
    public:
        Uint8 red_;
        Uint8 green_;
        Uint8 blue_;
};
class Geometric
{
    public:
        static void RenderRectangle(const Geometricformat& geo_size, const ColorData& color_data, SDL_Renderer* screen);
        static void RenderOutline(const Geometricformat& geo_size, const ColorData& color_data, SDL_Renderer* screen);
};

#endif // GEOMETRIC_H
