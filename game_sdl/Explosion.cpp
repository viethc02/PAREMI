
#include "Explosion.h"

ExplosionObject::ExplosionObject()
{
    frame_width_ = 0;
    frame_height_ = 0;
    frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadIMG(path,screen);
    if (ret == true)
    {
        frame_width_ = rect_.w/8;
        frame_height_ = rect_.h;
    }
    return ret;
}

void ExplosionObject::set_clip()
{
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].h = frame_height_;
        frame_clip_[0].w = frame_width_;

        for (int i = 1; i <= 7 ; i++)
        {
            frame_clip_[i].x = i * frame_width_;
            frame_clip_[i].y = 0;
            frame_clip_[i].h = frame_height_;
            frame_clip_[i].w = frame_width_;
        }
    }
}

void ExplosionObject::Show(SDL_Renderer* screen)
{

    SDL_Rect* currentclip = &frame_clip_[frame_];
    SDL_Rect renderquad = {rect_.x, rect_.y, frame_width_, frame_height_};
    if (currentclip != NULL)
    {
        renderquad.w = currentclip->w;
        renderquad.h = currentclip->h;
    }

    SDL_RenderCopy(screen, p_object_, currentclip, &renderquad);

}
