
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "PlayerPower.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 20


class MainObject: public BaseObject
{
    public:
        MainObject();
        ~MainObject();

        enum WalkType
        {
            WALK_NONE = 0,
            WALK_RIGHT = 1,
            WALK_LEFT = 2,
        };

        bool LoadIMG(std::string path , SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void HandleInputAction(SDL_Event events , SDL_Renderer* screen);
        void set_clips();
        void DoPlayer( Map& map_data , SDL_Renderer* screen);
        void CheckToMap( Map& map_data, SDL_Renderer* screen);
        void SetMapXY(const int map_x , const int map_y) {map_x_ = map_x; map_y_ = map_y;}
        void CenterEntityOnMap( Map &map_data);
        void UpdateImagePlayer(SDL_Renderer* des);
        SDL_Rect GetRectFrame();
        int get_frame_width() const {return width_frame_;}
        int get_frame_height() const {return height_frame_;}
        int get_x_pos() const {return x_pos_;}
        int get_y_pos() const {return y_pos_;}

        void set_bullet_list(std::vector<BulletObject*> bullet_list)
        {
            p_bullet_list_ = bullet_list;
        }
        std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
        void HandleBullet(SDL_Renderer* des);
        void RemoveBullet(const int& idx);
        void IncreaseMoney();

        void set_comeback_time(const int &cb) {come_back_time_ = cb;}

        int get_come_back_time() const {return come_back_time_;}

        int Get_Money_Count() const {return money_count;}

    private:

        int money_count;
        std::vector<BulletObject*> p_bullet_list_;
        float x_val_;
        float y_val_;

        float x_pos_;
        float y_pos_;

        int width_frame_;
        int height_frame_;

        SDL_Rect frame_clip_[8];
        Input input_type_;
        int frame_;
        int status_;
        bool on_ground;

        int map_x_;
        int map_y_;

        int come_back_time_;
};


#endif // MAIN_OBJECT_H_
