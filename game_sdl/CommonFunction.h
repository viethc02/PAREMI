#ifndef COMMON_FUNCTION_H_

#define COMMON_FUNCTION_H_

#include<windows.h>
#include<stdlib.h>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<vector>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Surface* g_menu = NULL;


//Screen
const int FRAME_PER_SECOND = 25; // fps
const int SCREEN_WIDTH = 1280;//1280;
const int SCREEN_HEIGHT = 640;//640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;//167
const int COLOR_KEY_G = 175;//175
const int COLOR_KEY_B = 180;//180

const int RENDER_DRAW_COLOR = 0Xff;

#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK_TILE 0

#define STATE_MONEY 4
#define THE_GATE 10

typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};



typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1 , const SDL_Rect& object2);
}



#endif // COMMON_FUNCTION_H_


