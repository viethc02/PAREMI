

#ifndef FLY_THREAT_OBJECT_H
#define FLY_THREAT_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define THREAT_FRAME_NUM 4
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 15
#define THREAT_SPEED 15


class FlyThreatsObject : public BaseObject
{
    public:
        FlyThreatsObject();
        ~FlyThreatsObject();

        enum TypeMove
        {
            STATIC_THREAT = 0,
            MOVE_IN_SPACE_THREAT = 1,
        };

        void set_x_val(const float &xVal) {x_val_ = xVal;}
        void set_y_val(const float &yVal) {y_val_ = yVal;}

        void set_x_pos(const float &xP) {x_pos_ = xP;}
        void set_y_pos(const float &yP) {y_pos_ = yP;}

        float get_x_pos() const {return x_pos_;}
        float get_y_pos() const {return y_pos_;}

        void SetMapXY(const int &mp_x, const int &mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

        void set_clips();

        bool LoadIMG(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        int get_num_frame() const {return frame_;}
        int get_width_frame() const { return width_frame_ ;}
        int get_height_frame() const { return height_frame_ ;}

        void DoPlayer(Map& gMap);
        void CheckToMap(Map& gMap);

        void InitThreats();

        void set_type_move(const int &typemove) { type_move = typemove; }
        void SetAnimationPos(const int &pos_a, const int &pos_b) {animation_a_ = pos_a; animation_b_ = pos_b; }
        void set_input_left(const int &ipLeft) { input_type_.left_ = ipLeft; }
        void ImpMoveType(SDL_Renderer* screen);

        SDL_Rect GetRectFrame();
    private:
        int map_x_;
        int map_y_;
        float y_val_;
        float x_val_;
        float x_pos_;
        float y_pos_;

        bool on_ground;
        int come_back_time_;

        SDL_Rect frame_clip_[THREAT_FRAME_NUM];
        int width_frame_;
        int height_frame_;
        int frame_;

        int type_move;
        int animation_a_;
        int animation_b_;
        Input input_type_;
};





#endif // FLY_THREAT_OBJECT_H
