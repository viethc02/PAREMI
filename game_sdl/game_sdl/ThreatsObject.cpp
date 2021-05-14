
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground = 0;
    come_back_time_ = 0;
    frame_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadIMG(path,screen);
    if (ret == true)
    {
        width_frame_ = rect_.w/THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = rect_.w/THREAT_FRAME_NUM;
    rect.h = height_frame_;
    return rect;
}

void ThreatsObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].h = height_frame_;
        frame_clip_[0].w = width_frame_;

        for (int i = 1; i <= 7 ; i++)
        {
            frame_clip_[i].x = i * width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].h = height_frame_;
            frame_clip_[i].w = width_frame_;
        }
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if (come_back_time_ == 0 )
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= 8)
        {
            frame_ = 0;
        }

        SDL_Rect* currentclip = &frame_clip_[frame_];
        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame_, height_frame_};
        SDL_RenderCopy(des, p_object_, currentclip, &renderquad);

    }
}

void ThreatsObject::DoPlayer(Map& gMap)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;
        if (y_val_ >= THREAT_MAX_FALL_SPEED)
        {
            y_val_ = THREAT_MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }

        CheckToMap(gMap);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_ --;
        if (come_back_time_ == 0)
        {
            InitThreats();
        }
    }
}

void ThreatsObject::InitThreats()
{
    x_val_ = 0;
    y_val_ = 0;
    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else
    {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time_ = 0;
}

void ThreatsObject::CheckToMap(Map &map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check_horizontal
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_)/ TILE_SIZE;
    y2 = (y_pos_ + height_min)/ TILE_SIZE;

    /*
        x1,x1..........x2,y1
        .
        .
        .
        .
        x1,y2..........x2,y2
    */

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // mainobject is moving to right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];


            if (( val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                input_type_.left_ = 2;
                input_type_.right_ = 0;
                x_val_ = 0;
            }

        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];


            if (( val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                input_type_.left_ = 0;
                input_type_.right_ = 2;
                x_val_ = 0;
            }
        }
    }


    //Check vertical

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min)/ TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/ TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if (( val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];


            if (( val1 != BLANK_TILE && val1 != STATE_MONEY)|| (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos_ = (y1 + 1) *TILE_SIZE;
                y_val_ = 0;
            }

        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    if (y_pos_ > map_data.max_y_ )
    {
        come_back_time_ = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if (type_move == STATIC_THREAT)
    {
        ;//
    }
    else
    {
        if (on_ground == true)
        {
            if (x_pos_ > animation_b_ || input_type_.left_ == 2)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadIMG("img//jiren_left.png", screen);
            }
            else if (x_pos_ < animation_a_ || input_type_.right_ == 2)
            {
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                LoadIMG("img//jiren_right.png", screen);
            }
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                LoadIMG("img//jiren_left.png", screen);
            }
        }
    }
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL )
    {
        p_bullet->LoadIMG("img//toppo_bullet.png", screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect_.x + 5, rect_.y + 10);//510
        p_bullet->Set_x_val(20);
        bullet_list.push_back(p_bullet);
    }
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int &x_limit , const int &y_limit)
{
    for (int i = 0 ; i < bullet_list.size() ; i++)
    {
        BulletObject* p_bullet = bullet_list[i];
        if (p_bullet != NULL)
        {

            if (p_bullet->get_is_move() == true)
            {
                int bullet_distance = rect_.x + width_frame_ - p_bullet->GetRect().x;
                if (bullet_distance < 200 && bullet_distance > 0)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x + 5, rect_.y + 10);
            }
        }
    }
}

void ThreatsObject::RemoveBullet(const int &idx)
{
    int sizex = bullet_list.size();
    if (sizex > 0 && idx < sizex)
    {
        BulletObject* p_bullet = bullet_list[idx];
        bullet_list.erase(bullet_list.begin() + idx);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }

}















