#include<iostream>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geometric.h"
#include "BossObject.h"
#include "ThreatsObject2.h"
#include "FlyThreatObject.h"

using namespace std;

#define INIT_BULLET_X 1000
#define INIT_BULLET_Y 20
BaseObject g_background;
BaseObject g_gamewon;
TTF_Font* font_time = NULL;
SDL_Texture* gTexture = NULL;
TTF_Font* gFont = NULL;
bool isRunning = true;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("PAREMI",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
            success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if ( !(IMG_Init(imgFlags)) && imgFlags )
                success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }
        font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
        if (font_time == NULL)
        {
            success = false;
        }
    }


    return success;
}

SDL_Texture* LoadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface(g_screen, loadedSurface);
        if (newTexture == NULL) cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
bool loadMedia()
{
    bool succes = true;
    gTexture = LoadTexture("img/menu_background1.jpg");
    if (gTexture == NULL)
    {
        cout << "Error image" << endl;
        succes = false;
    }
    return succes;
}

bool createImage( SDL_Texture* texture )
{
    if( texture == NULL ) return false;
    SDL_RenderCopy( g_screen, texture, NULL, NULL );
    return true;
}

int showMenu()
{
    if (TTF_Init() < 0)
    {
        cout << TTF_GetError();
        return 0;
    }
    gFont = TTF_OpenFont("font/Ash.ttf", 50);

    int x, y;

    const int numMenu = 2;
    SDL_Color colorMenu[numMenu] = {{243, 156, 18}, {255, 0, 0}};
    string text[numMenu] = {"Play", "Exit"};
    bool selected[numMenu] = {0,0};

    SDL_Surface* surface[numMenu];
    for (int i=0; i<numMenu; i++) surface[i] = TTF_RenderText_Solid(gFont, text[i].c_str(), colorMenu[0]);

    SDL_Texture* texture[numMenu];
    for (int i=0; i<numMenu; i++) texture[i] = SDL_CreateTextureFromSurface(g_screen, surface[i]);
    for (int i=0; i<numMenu; i++) SDL_FreeSurface(surface[i]);

    SDL_Rect scrRest[numMenu];
    SDL_Rect desRest[numMenu];
    for (int i=0; i<numMenu; i++) TTF_SizeText(gFont, text[i].c_str(), &scrRest[i].w, &scrRest[i].h);

    scrRest[0].x = 0;
    scrRest[0].y = 0;

    desRest[0].x = 150;
    desRest[0].y = 250;

    desRest[0].w = scrRest[0].w;
    desRest[0].h = scrRest[0].h;

    scrRest[1].x = 0;
    scrRest[1].y = 0;

    desRest[1].x = 150;
    desRest[1].y = 330;

    desRest[1].w = scrRest[1].w;
    desRest[1].h = scrRest[1].h;
    while (isRunning)
    {
        while (SDL_PollEvent(&g_event))
		{
			switch (g_event.type)
			{
				case SDL_QUIT:
				{
					isRunning = false;
					return 1;
				}
				case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    for (int i=0; i<numMenu; i++)
                    {
                        if (x>=desRest[i].x && x<=desRest[i].x+desRest[i].w && y>=desRest[i].y && y<=desRest[i].y+desRest[i].h)
                        {
                            if (!selected[i])
                            {
                                selected[i] = 1;
                                surface[i] = TTF_RenderText_Solid(gFont, text[i].c_str(), colorMenu[1]);
                                texture[i] = SDL_CreateTextureFromSurface(g_screen, surface[i]);
                            }
                        }
                        else
                        {
                            if (selected[i])
                            {
                                selected[i] = 0;
                                surface[i] = TTF_RenderText_Solid(gFont, text[i].c_str(), colorMenu[0]);
                                texture[i] = SDL_CreateTextureFromSurface(g_screen, surface[i]);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.button.x;
                    y = g_event.button.y;
                    for (int i=0; i<numMenu; i++)
                    {
                        if (x>=desRest[i].x && x<=desRest[i].x+desRest[i].w && y>=desRest[i].y && y<=desRest[i].y+desRest[i].h)
                        {
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 1;
                    }
				default:
				{
					break;
				}
			}
		}
        for (int i=0; i<numMenu; i++)
        {
            SDL_RenderCopy(g_screen, texture[i],&scrRest[i], &desRest[i]);
            SDL_RenderPresent(g_screen);
        }
    }
    return 1;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_QUIT || e.type == SDL_KEYDOWN)) return;
        SDL_Delay(100);
    }
}

bool LoadBackground()
{
    bool ret = g_background.LoadIMG("img/background1.jpg",g_screen);
    if (ret == false)
        return false;

    return true;
}

void ClearThreats(std::vector<ThreatsObject*> threats_list)
{
    for (int i = 0 ; i < threats_list.size() ; i++)
    {
        ThreatsObject* p_threat = threats_list[i];
        if (p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
        threats_list.clear();
    }
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_CloseFont(gFont);
    gFont = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void DrawGeometric()
{
    Geometricformat rectangle_size(0,0, SCREEN_WIDTH, 40);
    ColorData color_data(54,33,49);
    Geometric::RenderRectangle(rectangle_size,color_data,g_screen);

    Geometricformat outLineSize(1,1, SCREEN_WIDTH - 1, 38);
    ColorData color_data2(255, 255, 255);

    Geometric::RenderOutline(outLineSize,color_data2, g_screen);
}

std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[15];
    for (int i = 0 ; i < 15; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats +i);
        if (p_threat != NULL)
        {
            p_threat->LoadIMG("img//jiren_left.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i * 1500);
            p_threat->set_y_pos(50);

            p_threat->set_input_left(1);


            int pos1 = p_threat->get_x_pos() - 200;
            int pos2 = p_threat->get_x_pos() + 200;
            p_threat->SetAnimationPos(pos1, pos2);

            list_threats.push_back(p_threat);

        }
    }

    ThreatsObject* threat_objs = new ThreatsObject[16];

    for (int i = 0 ; i < 16 ; i++)
    {
        ThreatsObject* p_threat = (threat_objs + i);
        if (p_threat != NULL && i != 4 && i != 6)
        {
            p_threat->LoadIMG("img//toppo.png", g_screen);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_clips();
            p_threat->set_x_pos(float(1000 + i * 1500));
            p_threat->set_y_pos(float(250));
            p_threat->set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

std::vector<ThreatsObject2*> Make_Threats2_List()
{
    std::vector<ThreatsObject2*> list_threats2;
    ThreatsObject2* threat_objs2 = new ThreatsObject2[10];

    for (int i = 0 ; i < 10 ; i++)
    {
        ThreatsObject2* p_threat2 = (threat_objs2 + i);
        if (p_threat2 != NULL && i != 8)
        {
            p_threat2->LoadIMG("img//gokurosehit.png", g_screen);
            p_threat2->set_clips();
            p_threat2->set_x_pos(float(1500 + i * 2800));
            p_threat2->set_y_pos(float(250));
            list_threats2.push_back(p_threat2);
        }
    }
    return list_threats2;
}

std::vector<FlyThreatsObject*> Make_Fly_Threats_List()
{
    std::vector<FlyThreatsObject*> list_fly_threats;

    FlyThreatsObject* dynamic_threats = new FlyThreatsObject[15];
    for (int i = 0 ; i < 15; i++)
    {
        FlyThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL && i != 4)
        {
            p_threat->LoadIMG("img//kefla_right.png",g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(FlyThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(850 + i * 1600);
            p_threat->set_y_pos(0);

            p_threat->set_input_left(1);


            int pos1 = p_threat->get_x_pos() - 400;
            int pos2 = p_threat->get_x_pos() + 400;
            p_threat->SetAnimationPos(pos1, pos2);

            list_fly_threats.push_back(p_threat);

        }
    }
    return list_fly_threats;
}



void CheckMain(std::vector<ThreatsObject*> &threats_list, Map map_data,
               MainObject &p_player, ExplosionObject &exp_main,int &num_die, PlayerPower &player_power)
{
    for (int i = 0 ; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list[i];
        if (p_threat != NULL)
        {
            p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
            p_threat->ImpMoveType(g_screen);
            p_threat->DoPlayer(map_data);
            p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
            p_threat->Show(g_screen);


            SDL_Rect rect_player = p_player.GetRectFrame();
            bool bCol1 = false;
            std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
            for (int jj = 0 ; jj < tBullet_list.size(); jj++)
            {
                BulletObject* pt_bullet = tBullet_list[jj];
                if (pt_bullet)
                {
                    SDL_Rect bullet_rect = pt_bullet->GetRect();
                    bCol1 = SDLCommonFunc::CheckCollision(rect_player,pt_bullet->GetRect());
                    if (bCol1 == true)
                    {
                        p_threat->RemoveBullet(jj);
                        break;
                    }
                }

            }

            SDL_Rect rect_threat = p_threat->GetRectFrame();
            bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
            if (bCol1 || bCol2)
            {
                int width_exp_frame = exp_main.get_frame_width();
                int height_exp_frame = exp_main.get_frame_height();
                for (int ex = 0 ; ex < 4 ; ex++)
                {
                    int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
                    int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - height_exp_frame * 0.5;

                    exp_main.set_frame(ex);
                    exp_main.SetRect(x_pos, y_pos);
                    exp_main.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }

                num_die++;

                if (num_die <= 3)
                {
                    p_player.SetRect(0,0);
                    p_player.set_comeback_time(50);
                    SDL_Delay(1000);
                    player_power.Decrease();
                    player_power.Render(g_screen);

                    if (bCol1 == true)
                    {
                        BulletObject* threat_bullet = new BulletObject();
                        p_threat->InitBullet(threat_bullet, g_screen);

                    }

                    continue;
                }
                else

                {
                    g_gamewon.RenderGameOver(g_screen);
                    SDL_Delay(1000);

                    ClearThreats(threats_list);
                    close();
                    SDL_Quit();
                    exit(0) ;

                }

            }

        }
    }
}


void CheckMainShotThreats(std::vector<ThreatsObject*> &threats_list, ExplosionObject &exp_threat, MainObject &p_player, UINT &mark_val)
{
    int frame_exp_width = exp_threat.get_frame_width();
    int frame_exp_height = exp_threat.get_frame_height();


    std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
    for (int r = 0 ; r < bullet_arr.size(); r++)
    {
        BulletObject* p_bullet = bullet_arr[r];
        if (p_bullet != NULL)
        {
            for (int t = 0 ; t < threats_list.size(); t++)
            {
                ThreatsObject* obj_threat = threats_list[t];
                if (obj_threat != NULL)
                {
                    SDL_Rect tRect;
                    tRect.x = obj_threat->GetRect().x;
                    tRect.y = obj_threat->GetRect().y;
                    tRect.w = obj_threat->get_width_frame();
                    tRect.h = obj_threat->get_height_frame();

                    SDL_Rect bRect = p_bullet->GetRect();

                    bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                    if (bCol == true)
                    {
                        mark_val++;
                        for (int ex = 0 ; ex < NUM_FRAME_EXP; ex++)
                        {
                            int x_pos = p_bullet->GetRect().x ;
                            int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                            exp_threat.set_frame(ex);
                            exp_threat.SetRect(x_pos,y_pos);
                            exp_threat.Show(g_screen);
                        }


                        p_player.RemoveBullet(r);
                        obj_threat->Free();
                        threats_list.erase(threats_list.begin() + t);
                    }
                }
            }

        }
    }
}

void CheckMain2(MainObject &p_player, std::vector<ThreatsObject2*> &threats_list2, Map &map_data,
                ExplosionObject &exp_threat2, ExplosionObject &exp_main,
                int &num_die,PlayerPower &player_power, UINT &mark_val)
{


    SDL_Rect rect_player = p_player.GetRectFrame();
    bool bCol1 = false;
    for (int i = 0 ; i < threats_list2.size() ; i++)
    {
        ThreatsObject2* p_threat2 = threats_list2[i];

        p_threat2->SetMapXY(map_data.start_x_, map_data.start_y_);
        p_threat2->DoPlayer(map_data);
        p_threat2->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        p_threat2->Show(g_screen);

        std::vector<BulletObject*> tBullet_list = p_threat2->get_bullet_list();
        for (int jj = 0 ; jj < tBullet_list.size(); jj++)
        {
            BulletObject* pt_bullet = tBullet_list[jj];
            if (pt_bullet)
            {
                SDL_Rect bullet_rect = pt_bullet->GetRect();
                bCol1 = SDLCommonFunc::CheckCollision(rect_player,pt_bullet->GetRect() );
                if (bCol1 == true)
                {
                    p_threat2->RemoveBullet(jj);
                    break;
                }
            }

        }

        SDL_Rect rect_threat = p_threat2->GetRectFrame();
        bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
        if (bCol1 || bCol2)
        {
            int width_exp_frame = exp_main.get_frame_width();
            int height_exp_frame = exp_main.get_frame_height();
            for (int ex = 0 ; ex < 4 ; ex++)
            {
                int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
                int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - height_exp_frame * 0.5;

                exp_main.set_frame(ex);
                exp_main.SetRect(x_pos, y_pos);
                exp_main.Show(g_screen);
                SDL_RenderPresent(g_screen);
            }

            num_die++;

            if (num_die <= 3)
            {
                p_player.SetRect(0,0);
                p_player.set_comeback_time(50);
                SDL_Delay(1000);
                player_power.Decrease();
                player_power.Render(g_screen);

            }
            else
            {
                g_gamewon.RenderGameOver(g_screen);
                SDL_Delay(1000);
                //ClearThreats(threats_list2);
                close();
                SDL_Quit();
                exit(0) ;
            }
        }

        int frame_exp_width = exp_threat2.get_frame_width();
        int frame_exp_height = exp_threat2.get_frame_height();

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int r = 0 ; r < bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr[r];
            if (p_bullet != NULL)
            {
                SDL_Rect tRect;
                tRect.x = p_threat2->GetRect().x;
                tRect.y = p_threat2->GetRect().y;
                tRect.w = p_threat2->get_width_frame();
                tRect.h = p_threat2->get_height_frame();

                SDL_Rect bRect = p_bullet->GetRect();

                bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                if (bCol == true)
                {
                    for (int ex = 0 ; ex < NUM_FRAME_EXP; ex++)
                    {
                        int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                        int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                        exp_threat2.set_frame(ex);
                        exp_threat2.SetRect(x_pos,y_pos);
                        exp_threat2.Show(g_screen);
                    }
                    exp_threat2.Free();
                    p_player.RemoveBullet(r);
                    mark_val++;
                    threats_list2.erase(threats_list2.begin() +i);
                    p_threat2->Free();
                    std::vector<BulletObject*> tBullet_list = p_threat2->get_bullet_list();
                    for (int jj = 0 ; jj < tBullet_list.size(); jj++)
                        p_threat2->RemoveBullet(jj);
                }

            }
        }
    }
}

void CheckMainVsFlyThreat(std::vector<FlyThreatsObject*> &threats_fly_list, Map map_data,
                          MainObject &p_player, ExplosionObject &exp_main, int &num_die, PlayerPower &player_power,
                          ExplosionObject &exp_flythreat, UINT& mark_val)
{
    for (int i = 0 ; i < threats_fly_list.size(); i++)
    {
        FlyThreatsObject* fly_threat = threats_fly_list[i];
        if (fly_threat != NULL)
        {
            fly_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
            fly_threat->ImpMoveType(g_screen);
            fly_threat->DoPlayer(map_data);
            fly_threat->Show(g_screen);


            SDL_Rect rect_player = p_player.GetRectFrame();

            SDL_Rect rect_threat = fly_threat->GetRectFrame();
            bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
            if (bCol2)
            {
                int width_exp_frame = exp_main.get_frame_width();
                int height_exp_frame = exp_main.get_frame_height();
                for (int ex = 0 ; ex < 4 ; ex++)
                {
                    int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
                    int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - height_exp_frame * 0.5;

                    exp_main.set_frame(ex);
                    exp_main.SetRect(x_pos, y_pos);
                    exp_main.Show(g_screen);
                    SDL_RenderPresent(g_screen);
                }

                num_die++;

                if (num_die <= 3)
                {
                    p_player.SetRect(0,0);
                    p_player.set_comeback_time(50);
                    SDL_Delay(1000);
                    player_power.Decrease();
                    player_power.Render(g_screen);

                    continue;
                }
                else

                {
                    g_gamewon.RenderGameOver(g_screen);

                    SDL_Delay(1000);
                    //ClearThreats(threats_list);
                    close();
                    SDL_Quit();
                    exit(0) ;
                }
            }

        }
    }
    int frame_exp_width = exp_flythreat.get_frame_width();
    int frame_exp_height = exp_flythreat.get_frame_height();


    std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
    for (int r = 0 ; r < bullet_arr.size(); r++)
    {
        BulletObject* p_bullet = bullet_arr[r];
        if (p_bullet != NULL)
        {
            for (int t = 0 ; t < threats_fly_list.size(); t++)
            {
                FlyThreatsObject* obj_threat = threats_fly_list[t];
                if (obj_threat != NULL)
                {
                    SDL_Rect tRect;
                    tRect.x = obj_threat->GetRect().x;
                    tRect.y = obj_threat->GetRect().y;
                    tRect.w = obj_threat->get_width_frame();
                    tRect.h = obj_threat->get_height_frame();

                    SDL_Rect bRect = p_bullet->GetRect();

                    bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

                    if (bCol == true)
                    {
                        mark_val++;
                        for (int ex = 0 ; ex < NUM_FRAME_EXP; ex++)
                        {
                            int x_pos = p_bullet->GetRect().x ;
                            int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                            exp_flythreat.set_frame(ex);
                            exp_flythreat.SetRect(x_pos,y_pos);
                            exp_flythreat.Show(g_screen);
                        }


                        p_player.RemoveBullet(r);
                        obj_threat->Free();
                        threats_fly_list.erase(threats_fly_list.begin() + t);
                    }
                }
            }

        }
    }

}

void ShowTimeGame(bool &is_quit, TextObject &time_game, UINT &mark_val, TextObject &mark_game, MainObject &p_player, TextObject &money_game)
{
    std::string str_time = "Time: ";
    Uint32 time_val = SDL_GetTicks() / 1000;
    Uint32 val_time = 300 - time_val;
    if (val_time <= 0)
    {
        if (MessageBox(NULL, ("Game Over"), ("Info"), MB_OK | MB_ICONSTOP) == IDOK)
        {
            is_quit = true;
            g_gamewon.RenderGameOver(g_screen);
            SDL_Delay(1000);
            close();
            SDL_Quit();
            exit(0) ;
        }
    }
    else
    {
        std::string str_val = std::to_string(val_time);
        str_time += str_val;

        time_game.SetText(str_time);
        time_game.LoadFromRenderText(font_time,g_screen);
        time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
    }

    std::string val_string_mark = std::to_string(mark_val);
    std::string strMark = "SCORE: ";
    strMark += val_string_mark;
    mark_game.SetText(strMark);
    mark_game.LoadFromRenderText(font_time, g_screen);
    mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

    int money_count = p_player.Get_Money_Count();
    std::string string_money = std::to_string(money_count);

    money_game.SetText(string_money);
    money_game.LoadFromRenderText(font_time, g_screen);
    money_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);
}


void HandleBoss(BossObject &boss_object,
                ExplosionObject &exp_boss,
                ExplosionObject &exp_main, MainObject &p_player,
                UINT &mark_val, Map &map_data,
                int &num_die, PlayerPower &player_power, int &Boss_blood, bool &boss,
                std::vector<ThreatsObject*> threats_list)
{
    boss_object.SetMapXY(map_data.start_x_, map_data.start_y_);
    boss_object.DoPlayer(map_data,Boss_blood);
    boss_object.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
    boss_object.Show(g_screen,Boss_blood);


    //CHECK BOSS AND BULLET

    SDL_Rect rect_player = p_player.GetRectFrame();
    bool bCol1 = false;
    std::vector<BulletObject*> tBullet_list = boss_object.get_bullet_list();
    for (int jj = 0 ; jj < tBullet_list.size(); jj++)
    {
        BulletObject* pt_bullet = tBullet_list[jj];
        if (pt_bullet)
        {
            SDL_Rect bullet_rect = pt_bullet->GetRect();
            bCol1 = SDLCommonFunc::CheckCollision(rect_player,pt_bullet->GetRect() );
            if (bCol1 == true)
            {
                boss_object.RemoveBullet(jj);
                break;
            }
        }

    }

    SDL_Rect rect_boss = boss_object.GetRectFrame();
    bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_boss);
    if (bCol1 || bCol2)
    {
        int width_exp_frame = exp_main.get_frame_width();
        int height_exp_frame = exp_main.get_frame_height();
        for (int ex = 0 ; ex < 4 ; ex++)
        {
            int x_pos = (p_player.GetRect().x + p_player.get_frame_width() * 0.5) - width_exp_frame * 0.5;
            int y_pos = (p_player.GetRect().y + p_player.get_frame_height() * 0.5) - height_exp_frame * 0.5;

            exp_main.set_frame(ex);
            exp_main.SetRect(x_pos, y_pos);
            exp_main.Show(g_screen);
            SDL_RenderPresent(g_screen);
        }

        num_die++;

        if (num_die <= 3)
        {
            p_player.SetRect(0,0);
            p_player.set_comeback_time(50);
            SDL_Delay(1000);
            player_power.Decrease();
            player_power.Render(g_screen);

        }
        else
        {
            g_gamewon.RenderGameOver(g_screen);
            SDL_Delay(1000);
            boss_object.Free();
            ClearThreats(threats_list);
            close();
            SDL_Quit();
            exit(0) ;
        }
    }

    int frame_exp_width = exp_boss.get_frame_width();
    int frame_exp_height = exp_boss.get_frame_height();

    std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
    for (int r = 0 ; r < bullet_arr.size(); r++)
    {
        BulletObject* p_bullet = bullet_arr[r];
        if (p_bullet != NULL)
        {
            SDL_Rect tRect;
            tRect.x = boss_object.GetRect().x;
            tRect.y = boss_object.GetRect().y;
            tRect.w = boss_object.get_width_frame();
            tRect.h = boss_object.get_height_frame();

            SDL_Rect bRect = p_bullet->GetRect();

            bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

            if (bCol == true)
            {


                for (int ex = 0 ; ex < NUM_FRAME_EXP; ex++)
                {
                    int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                    int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                    exp_boss.set_frame(ex);
                    exp_boss.SetRect(x_pos,y_pos);
                    exp_boss.Show(g_screen);
                }

                Boss_blood -= 2;
                exp_boss.Free();
                p_player.RemoveBullet(r);
                if (Boss_blood == 0)
                {
                    mark_val += 10;
                    boss_object.Free();
                    boss = false;
                    std::vector<BulletObject*> tBullet_list = boss_object.get_bullet_list();
                    for (int jj = 0 ; jj < tBullet_list.size(); jj++)
                        boss_object.RemoveBullet(jj);
                }

            }

        }
    }
}

void FPS(ImpTimer &fps_timer)
{
    int real_imp_time = fps_timer.get_ticks();
    int time_one_frame = 1000/FRAME_PER_SECOND;

    if (real_imp_time < time_one_frame)
    {
        int delay_time = time_one_frame - real_imp_time;
        if (delay_time >= 0 )
            SDL_Delay(delay_time);
    }
}

int main(int argc, char *argv[])
{

    ImpTimer fps_timer;


    if (InitData() == false)
        return -1;

    if (loadMedia() == true)
    {
        createImage(gTexture);
        SDL_RenderPresent(g_screen);
    }

    int tmp = showMenu();
    if (tmp == 1)
    {
        isRunning = true;
        return 0;
    }
    while(!isRunning)
    {
        while (SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                default:
                    break;
            }
        }
    }

    if (LoadBackground() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("map/map01.dat");
    game_map.LoadTiles(g_screen);




    MainObject p_player;
    p_player.LoadIMG("img//goku_jump_right.png",g_screen);
    p_player.set_clips();


    PlayerPower player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.5 - 290, 8);

    std::vector<ThreatsObject*> threats_list = MakeThreadList();

    std::vector<ThreatsObject2*> threats_list2 = Make_Threats2_List();

    std::vector<FlyThreatsObject*> threats_fly_list = Make_Fly_Threats_List();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadIMG("img//exp3.png",g_screen);
    if (tRet == false)
    {
        return -1;
    }
    exp_threat.set_clip();

    ExplosionObject exp_threat2;
    bool tRet3 = exp_threat2.LoadIMG("img//exp3.png",g_screen);
    if (tRet3 == false)
    {
        return -1;
    }
    exp_threat2.set_clip();

    ExplosionObject exp_flythreat;
    bool tRet4 = exp_flythreat.LoadIMG("img//exp3.png",g_screen);
    exp_flythreat.set_clip();


    ExplosionObject exp_main;
    bool tRet1 = exp_main.LoadIMG("img//exp3.png",g_screen);
    if (tRet1 == false)
    {
        return -1;
    }
    exp_main.set_clip();



    int num_die = 0;

    //BOSS
    BossObject boss_object;
    boss_object.LoadIMG("img//boss_object.png", g_screen);
    boss_object.set_clips();
    int xPos = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH* 0.6;
    boss_object.set_x_pos(xPos);
    boss_object.set_y_pos(10);
    int Boss_blood = 80;

    ExplosionObject exp_boss;
    bool tRet2 = exp_boss.LoadIMG("img//exp3.png",g_screen);
    if (tRet2 == false)
    {
        return -1;
    }
    exp_boss.set_clip();


    //TIME TEXT
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    UINT mark_val = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);

    bool is_quit = false;
    bool boss = true;


    int check = 0;

    while (!is_quit)
    {
        fps_timer.start();

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.HandleInputAction(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR );
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getmap();



        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data,g_screen);
        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);
        int come_back_time = p_player.get_come_back_time();
        if (come_back_time == 59)
        {
            player_power.Decrease();
            num_die++;
        }
        if (num_die > 3)
        {
            g_gamewon.RenderGameOver(g_screen);
            is_quit = true;
            SDL_Delay(1000);
        }
        p_player.HandleBullet(g_screen);
        p_player.Show(g_screen);

        //DRAW GEOMETRIC
        DrawGeometric();

        player_power.Show(g_screen);
        player_money.Show(g_screen);


        //CheckMainvsthreat1
        CheckMain(threats_list, map_data, p_player, exp_main, num_die, player_power);

        //CheckMainvsthreat2
        CheckMain2(p_player, threats_list2, map_data, exp_threat2, exp_main, num_die, player_power, mark_val);

        CheckMainVsFlyThreat(threats_fly_list, map_data, p_player, exp_main, num_die, player_power, exp_flythreat, mark_val);

        //CheckMainBullet
        CheckMainShotThreats(threats_list, exp_threat, p_player, mark_val);

        //SHOW_GAME_TIME
        ShowTimeGame(is_quit, time_game, mark_val, mark_game, p_player, money_game);


        //SHOW BOSS
        int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x) - 200;
        if (val <= SCREEN_WIDTH && boss == true)
        {
            HandleBoss(boss_object, exp_boss, exp_main, p_player, mark_val, map_data, num_die, player_power, Boss_blood, boss, threats_list);
        }

        SDL_RenderPresent(g_screen);
        FPS(fps_timer);

    }
    close();
    return 0;
}

