
#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "CommonFunction.h"

class TextObject
{
    public:
        TextObject();
        ~TextObject();

        enum TextColor
        {
            RED_TEXT = 0,
            WHITE_TEXT = 1,
            BLACK_TEXT = 2,
        };

        bool LoadFromRenderText(TTF_Font* Font, SDL_Renderer* screen);
        void Free();

        void SetColor(Uint8 red, Uint8 green , Uint8 blue);
        void SetColor(int type);
        void SetTextRect(const int &x , const int &y){
            rect_.x = x;
            rect_.y = y;
        }

        void RenderText(SDL_Renderer* screen,
                        int xp , int yp,
                        const SDL_Rect* clip = NULL,
                        const double angle = 0.0,
                        const SDL_Point* center = NULL,
                        const SDL_RendererFlip Flip = SDL_FLIP_NONE);

        int GetWidth() const {return width_;}
        int GetHeight() const {return height_;}

        void SetText(const std::string& text) {str_val_ = text; }
        std::string GetText() const {return str_val_;}

    private:
        std::string str_val_;
        SDL_Color text_color_;
        SDL_Texture* texture_;
        int height_;
        int width_;
        SDL_Rect rect_;
};


#endif // TEXT_OBJECT_H

