
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

class BulletObject: public BaseObject
{
    public:
        BulletObject();
        ~BulletObject();

        enum BulletDir{
            DIR_RIGHT = 20,
            DIR_LEFT = 21,
            DIR_UP = 22,
            DIR_UP_LEFT = 23,
            DIR_UP_RIGHT = 24,
            DIR_DOWN_LEFT = 25,
            DIR_DOWN_RIGHT = 26,
        };

        void Set_x_val(const int &xVal) {x_val_ = xVal;}
        void Set_y_val(const int &yVal) {y_val_ = yVal;}

        int get_x_val() const { return x_val_; }
        int get_y_val() const { return y_val_; }

        void set_is_move (const bool &isMove) {is_move_ = isMove; }
        bool get_is_move() const { return is_move_ ;}

        void set_bullet_dir (const unsigned int &bulletDir) {bullet_dir_ = bulletDir; }
        unsigned int get_bullet_dir () const {return bullet_dir_; }

        void HandleMove(const int &x_border , const int &y_border);



    private:
        int x_val_;
        int y_val_;
        bool is_move_;
        unsigned int bullet_dir_;


};

#endif // BULLET_OBJECT_H
