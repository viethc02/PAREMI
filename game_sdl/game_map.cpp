
#include "game_map.h"

void GameMap::LoadMap(char* name)
{
    // load file map
    FILE* fp = NULL;
    fopen_s(&fp , name , "rb");
    if (fp == NULL)
    {
        return;
    }
    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;
    for (int i = 0 ; i < MAX_MAP_Y ; i++)
    {
        for (int j = 0 ; j < MAX_MAP_X ; j++)
        {
            fscanf(fp, "%d" , &game_map_.tile[i][j]); // doc tu file vao game_map
            int val = game_map_.tile[i][j];
            if (val > 0) // neu la gia tri 1 2 3...
            {
                if (j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j; // neu j lon hon o do thi gan'
                }
                if (i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i ;
                }
            }
        }
    }
    game_map_.max_x_ = (game_map_.max_x_ + 1) *TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) *TILE_SIZE;
    // toi vi tri cuoi cua map

    game_map_.start_x_ = 0 ;
    game_map_.start_y_ = 0 ;

    game_map_.file_name_ = name;
    fclose(fp);

}

void GameMap::LoadTiles(SDL_Renderer* screen)
{
    //load tile map
    char file_img[30];
    FILE* fp = NULL;

    for (int i = 0 ; i < MAX_TILES ; i++)
    {
        sprintf_s(file_img, "map/%d.png" , i);
        fopen_s(&fp, file_img, "rb");
        if (fp == NULL)
        {
            continue;
        }
        fclose(fp);
        tile_mat[i].LoadIMG(file_img, screen); // LOAD TAM' ANH 1 2 3 ..
    }

}
void GameMap::DrawMap(SDL_Renderer* screen)
{
    //DIEN` hinh anh vao cac o
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_ / TILE_SIZE;

    x1 = (game_map_.start_x_%TILE_SIZE) * -1; // nhan lui lai de fill thua hon thieu
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE); // + them de fill thua ra

    map_y = game_map_.start_y_ / TILE_SIZE;

    y1 = (game_map_.start_y_%TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1 ; i < y2 ; i+= TILE_SIZE)
    {
        map_x = game_map_.start_x_/ TILE_SIZE;
        for (int j = x1 ; j < x2 ; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x]; // gia tri cua vi tri o duoc fill
            if (val > 0)
            {
                tile_mat[val].SetRect(j,i);
                tile_mat[val].Render(screen); // fill o
            }
            map_x++;
        }
        map_y++;
    }

}



















