
#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "objects.h"
#include "Music.hpp"

using namespace std;

int textcounter = 0;


class tile 
{
    public:

    SDL_Texture* tiletext = NULL;

    int width=64;
    int height=64;

    int x; //x and y coords on the map
    int y;
    int screen_x = x-CAMX;
    int screen_y = y-CAMY;
     
    int sx; // x and y coords on the sprite sheet
    int sy;
    
    bool isobstacle=false;
    
     tile ()
    {
         x=0;
         y=0;
         sx=0;
         sy=0;
    }


    tile ( SDL_Texture* text)
    {
         tiletext = text;
         x=0;
         y=0;
         sx=0;
         sy=0;
    }

    tile ( SDL_Texture* text, int sxn , int syn)
    {
          sx=sxn;
          sy=syn;
          tiletext = text;
    }
     
    void rendertile ( SDL_Renderer* renderer )
    {
         screen_x = x - CAMX;
         screen_y = y - CAMY;

         SDL_Rect src;
         src.x=sx;
         src.y=sy;
         src.w=32;
         src.h=32;
         
         SDL_Rect dest;
         dest.x=screen_x;
         dest.y=screen_y;
         dest.w=64;
         dest.h=64;
        
          
          SDL_RenderCopy( renderer , tiletext , &src , &dest );

     }

     void copytile ( tile tileset_tile ) // for copying the tileset data onto the map data
     {
         
         tiletext = tileset_tile.tiletext;
         sx=tileset_tile.sx;
         sy=tileset_tile.sy;
     }

};


class level
{
     public:
     string name;
     
     vector <tile> tiles_layer1;
     vector <tile> tiles_layer2;
     vector <tile> tiles_layer3;
     
     int rows;
     int columns;

     int tile_width=32;
     int tile_height=32;

     vector <tile> tileset;

     int tileset_rows;
     int tileset_columns;

     TTF_Font* levelfont=NULL;
     SDL_Texture* font = NULL;
     bool fontstart = false;

     vector <powerup> powerups;
     
     Music level_bgm;

     level()
     {
        rows=0;
        columns=0;
     }

     level ( int r , int c )
     {
          rows=r;
          columns=c;
     }

     level ( int r , int c , int tr , int tc )
     {
          rows=r;
          columns=c;
          tileset_rows = tr;
          tileset_columns = tc;
     }

     void destory_level()
     {
         tileset.clear();
         tiles_layer1.clear();
         tiles_layer2.clear();
         tiles_layer3.clear();
     }

     void set_level_dimensions( int r , int c , int tr , int tc)
     {
          rows=r;
          columns=c;
          tileset_rows = tr;
          tileset_columns = tc;
     }

     void set_tileset( string path , SDL_Renderer* ren )
     { 
          SDL_Surface* tile_surface = IMG_Load( path.c_str() );
          SDL_Texture* tileset_texture = SDL_CreateTextureFromSurface( ren ,  tile_surface );
      
          for( int i=0 ; i<tileset_rows ; ++i){
              for( int j=0 ; j<tileset_columns ; ++j){
                      
                     tile temp_tile( tileset_texture , j*tile_width , i*tile_height);
                     tileset.push_back( temp_tile );
              }     
          }
     }
     
     
    void draw_layer( SDL_Renderer* ren  , vector <tile> layer )
    {
    for ( auto& tile : layer ) 
    {
        tile.rendertile(ren);
    }
    }
    
    void draw_level( SDL_Renderer* ren)
    {
        draw_layer( ren , tiles_layer1);
        draw_layer( ren , tiles_layer2);
        draw_layer( ren , tiles_layer3);
    }
    
};


void load_main_menu( SDL_Renderer* renderer , level &main_menu )
{
     main_menu.levelfont = TTF_OpenFont( "Assets/8bit_font.ttf" , 32);
     SDL_Surface* temp = TTF_RenderText_Solid( main_menu.levelfont , "Game Started" , {255,255,51});
     main_menu.font = SDL_CreateTextureFromSurface(renderer, temp);


     main_menu.set_level_dimensions( 30 , 32 , 133 , 8 );
     
     main_menu.set_tileset("Assets/Homepage/Home_page_tileset.png" , renderer); 

     vector <int> layer_1_values;
     vector <int> layer_2_values;
     vector <int> layer_3_values(960,0);
     
     layer_1_values = {
253,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,241,261,
250,5,5,4,4,5,4,4,4,4,4,1,3,2,2,3,3,3,3,3,3,3,4,4,4,1,5,5,4,5,5,252,
250,5,5,4,4,4,4,4,4,4,4,4,3,4,4,449,450,451,4,1,1,1,3,3,1,3,4,4,5,4,5,252,
250,5,4,4,4,4,3,4,4,4,4,3,4,4,4,449,450,451,3,4,3,3,2,3,4,4,4,4,4,4,5,252,
250,4,4,4,4,4,4,4,4,4,1,3,4,4,3,449,450,451,4,1,4,4,4,4,4,4,4,4,4,4,5,252,
250,5,4,4,4,4,4,4,4,4,4,4,4,2,4,449,450,451,2,2,2,1,2,4,4,4,4,4,4,4,4,252,
250,4,4,4,4,4,117,118,119,4,4,4,3,3,3,449,450,451,3,3,3,4,4,4,4,4,4,4,4,4,4,252,
250,4,4,4,4,4,117,118,119,119,4,4,3,2,4,449,450,451,2,3,4,3,4,4,4,4,4,4,4,4,4,252,
250,3,4,4,4,4,4,117,118,119,119,4,3,3,3,449,450,451,3,1,4,3,3,4,4,4,4,1,4,4,4,252,
250,3,3,1,1,4,1,1,449,450,451,3,4,4,3,449,450,451,3,3,1,3,3,5,4,4,4,4,4,4,4,252,
250,3,3,3,3,3,3,2,449,450,451,3,1,3,3,449,450,451,1,1,3,3,2,117,118,119,119,4,4,4,4,252,
250,3,3,3,2,3,3,1,449,450,451,451,1,3,4,449,450,451,3,3,1,3,2,4,117,118,119,4,4,4,4,252,
250,1,1,4,2,2,3,2,449,449,450,451,2,3,449,450,450,450,451,1,1,2,2,4,117,118,119,119,4,4,3,252,
250,5,450,4,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,3,3,252,
250,4,4,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,451,3,252,
250,4,4,4,4,458,450,450,450,450,458,458,458,458,450,450,450,450,450,458,458,458,458,458,458,458,458,458,458,459,3,252,
250,4,4,4,4,4,457,450,450,451,1,1,1,3,457,450,450,450,459,3,3,3,2,3,2,2,3,3,3,3,3,252,
250,4,4,4,4,4,4,449,450,451,1,2,3,3,1,449,450,451,3,3,1,3,3,3,2,3,3,3,3,3,3,252,
250,3,3,4,117,118,119,457,450,450,450,450,450,450,450,450,450,451,3,1,1,3,2,3,3,3,3,2,2,3,3,252,
250,1,4,4,117,117,118,119,457,450,458,450,458,458,458,458,450,451,2,1,73,74,74,74,74,74,74,74,74,74,75,252,
250,4,4,4,117,118,119,2,3,457,458,458,1,2,3,449,450,451,1,1,81,85,85,85,85,85,85,85,85,85,83,252,
250,4,4,4,4,4,4,2,2,3,3,2,1,2,2,449,450,450,450,73,81,85,1,85,85,85,85,85,85,85,83,252,
250,4,4,4,4,3,4,4,2,3,2,1,2,3,3,449,450,450,458,89,81,85,85,85,85,85,85,85,85,85,83,252,
250,4,4,4,4,3,3,3,3,2,1,2,2,3,3,449,450,451,3,1,81,85,85,85,85,85,85,85,85,85,83,252,
250,4,4,4,1,3,2,2,2,1,2,3,3,450,450,450,450,451,1,1,81,85,85,85,85,85,85,85,85,85,83,252,
250,4,4,1,1,3,3,1,3,3,3,3,450,450,458,458,450,451,3,3,81,85,85,85,85,85,85,1,1,85,83,252,
250,2,2,1,3,3,3,1,450,450,450,450,458,450,3,1,3,3,3,3,81,85,85,85,85,85,85,85,85,85,83,252,
250,3,3,4,3,3,3,1,450,450,450,458,458,458,3,2,3,2,3,3,89,90,90,90,90,90,90,90,90,90,91,252,
250,3,1,3,4,3,3,4,458,458,458,1,3,2,2,3,3,2,2,3,3,3,1,3,1,2,2,3,1,1,1,252,
250,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,252
};


     layer_2_values = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1055,44,0,0,44,44,0,15,16,201,196,0,925,0,0,0,925,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,15,16,113,114,115,135,0,23,24,0,194,0,933,0,0,0,933,0,0,0,0,195,201,201,196,0,0,0,0,0,
0,0,23,24,129,130,131,143,0,64,1055,0,194,13,14,0,0,0,0,0,0,0,0,193,0,0,206,200,135,0,0,0,
0,0,0,44,137,138,139,151,0,72,0,195,204,21,22,0,0,0,0,0,0,0,205,204,0,0,44,0,143,44,0,0,
0,0,1030,0,145,146,147,44,205,198,199,204,0,0,0,0,0,0,0,0,0,0,0,0,1055,44,68,44,151,15,16,0,
0,0,0,44,15,16,0,0,0,0,15,16,0,0,0,0,0,0,0,0,0,0,0,0,15,16,113,114,115,23,24,0,
0,68,0,0,23,24,0,44,0,0,23,24,0,0,0,0,0,0,0,0,0,0,0,68,23,24,129,130,131,0,0,0,
0,198,199,196,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,137,138,139,1055,44,0,
0,0,0,203,198,199,200,207,0,0,0,0,0,0,0,0,0,0,0,0,0,0,196,0,0,72,145,146,147,15,16,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,206,0,0,0,0,0,0,23,24,0,
0,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,206,196,0,0,0,205,196,68,0,0,
0,21,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,194,195,0,0,201,204,13,14,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,929,930,931,0,0,0,0,0,203,204,0,0,0,0,21,22,0,
0,15,16,0,0,0,0,0,0,0,0,0,0,0,0,937,938,939,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,23,24,0,208,0,0,0,0,0,940,941,0,0,0,945,946,947,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,44,1055,0,135,15,16,0,0,0,948,949,0,909,0,0,0,0,0,909,0,0,0,0,0,0,9,10,0,0,0,0,
0,113,114,115,143,23,24,0,0,0,0,0,0,917,0,0,0,0,0,917,0,0,0,0,0,0,17,18,0,0,156,0,
0,129,130,131,151,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,229,0,0,0,0,0,0,0,0,0,164,0,
0,137,138,139,44,0,0,194,0,0,0,0,0,0,0,0,0,0,0,230,179,185,185,185,185,185,185,185,185,185,181,0,
0,145,146,147,1030,0,0,193,0,0,0,0,0,0,0,0,0,0,0,238,186,156,0,0,0,0,0,0,0,0,0,0,
0,44,0,0,0,0,195,204,0,0,0,0,0,0,0,0,0,0,0,0,0,164,0,0,0,0,881,882,319,320,0,0,
0,0,68,0,0,195,204,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,889,890,327,328,0,0,
0,0,0,0,195,204,0,0,0,0,0,0,0,0,0,0,0,0,0,868,178,0,0,0,0,0,897,898,0,887,888,0,
0,199,199,199,207,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,177,0,160,0,160,0,0,0,0,895,896,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,177,156,0,0,0,0,160,263,264,903,904,0,
0,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,17,33,34,18,177,164,0,160,0,160,0,271,272,0,0,0,
0,21,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,18,49,187,185,185,185,185,185,185,185,185,185,181,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,0,0,49,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     };


     layer_3_values = {
         0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,51,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,134,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,0,0,
0,51,0,0,142,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,51,0,0,0,0,0,0,0,0,
0,51,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,0,0,0,0,0,0,0,0,0,0,
0,0,51,51,0,0,0,0,0,0,0,0,0,0,0,49,0,0,49,0,0,0,0,0,0,0,0,134,0,51,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,142,0,0,0,0,
0,0,0,0,0,0,0,0,0,51,0,0,49,0,0,0,0,0,0,49,49,0,0,0,0,0,0,122,0,0,0,0,
0,0,0,0,0,0,0,0,51,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,51,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,455,0,0,0,455,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,51,0,0,455,455,455,0,0,0,0,455,455,0,0,924,0,0,455,455,455,0,0,0,0,51,0,0,0,0,0,
0,0,0,0,51,0,51,0,0,0,0,0,0,49,0,0,932,0,0,0,0,0,51,0,0,0,0,51,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,51,0,0,51,0,0,0,
0,0,0,0,0,0,0,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,49,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,49,0,0,0,0,49,0,0,
0,134,0,0,0,0,0,0,51,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,0,0,0,49,0,0,0,
0,142,0,0,0,0,0,0,0,0,49,0,0,49,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,122,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,228,227,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,455,49,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,51,0,0,0,0,0,0,49,0,0,49,0,0,0,49,0,0,0,49,0,0,0,0,0,0,0,0,0,0,
0,51,51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,0,0,0,0,0,49,49,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
     };


for( int i=0 ; i< layer_1_values.size() ; ++i){
   
        int index = layer_1_values[i];
         
        if(index!=0)
        {
        tile temp_tile;
        temp_tile.copytile( main_menu.tileset[index-1] );
        temp_tile.x = i%main_menu.columns * temp_tile.width;
        temp_tile.y = i/(main_menu.columns) * temp_tile.height;

        main_menu.tiles_layer1.push_back( temp_tile );
        }
}

for( int i=0 ; i< layer_2_values.size() ; ++i){
   
        int indx = layer_2_values[i];
         
        if(indx!=0)
        {
        tile temp_tile;
        temp_tile.copytile( main_menu.tileset[indx-1] );
        temp_tile.x = i%main_menu.columns * temp_tile.width ;
        temp_tile.y = i/(main_menu.columns) * temp_tile.height;
        temp_tile.isobstacle=true;

        main_menu.tiles_layer2.push_back( temp_tile );
        }
}

for( int i=0 ; i< layer_3_values.size() ; ++i){
   
        int index = layer_3_values[i];
     
        if(index!=0)
        {
        tile temp_tile;
        temp_tile.copytile( main_menu.tileset[index-1] );
        temp_tile.x = i%main_menu.columns * temp_tile.width;
        temp_tile.y = i/(main_menu.columns) * temp_tile.height;

        main_menu.tiles_layer3.push_back( temp_tile );
        }
}


}

vector <int> main_menu_collider=
 {
 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,1055,44,0,0,44,44,0,15,16,201,196,0,925,0,0,0,925,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,15,16,113,114,115,135,0,23,24,0,194,0,933,0,0,0,933,0,0,0,0,195,201,201,196,0,0,0,0,1,
1,0,23,24,129,130,131,143,0,64,1055,0,194,13,14,0,0,0,0,0,0,0,0,193,0,0,206,200,135,0,0,1,
1,0,0,44,137,138,139,151,0,72,0,195,204,21,22,0,0,0,0,0,0,0,205,204,0,0,44,0,143,44,0,1,
1,0,1030,0,145,146,147,44,205,198,199,204,0,0,0,0,0,0,0,0,0,0,0,0,1055,44,68,44,151,15,16,1,
1,0,0,44,15,16,0,0,0,0,15,16,0,0,0,0,0,0,0,0,0,0,0,0,15,16,113,114,115,23,24,1,
1,68,0,0,23,24,0,44,0,0,23,24,0,0,0,0,0,0,0,0,0,0,0,68,23,24,129,130,131,0,0,1,
1,198,199,196,0,68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,137,138,139,1055,44,1,
1,0,0,203,198,199,200,207,0,0,0,0,0,0,0,0,0,0,0,0,0,0,196,0,0,72,145,146,147,15,16,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,206,0,0,0,0,0,0,23,24,1,
1,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,206,196,0,0,0,205,196,68,0,1,
1,21,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,194,195,0,0,201,204,13,14,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,929,930,931,0,0,0,0,0,203,204,0,0,0,0,21,22,1,
1,15,16,0,0,0,0,0,0,0,0,0,0,0,0,937,938,939,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,23,24,0,208,0,0,0,0,0,940,941,0,0,0,945,946,947,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,44,1055,0,135,15,16,0,0,0,948,949,0,909,0,0,0,0,0,909,0,0,0,0,0,0,9,10,0,0,0,1,
1,113,114,115,143,23,24,0,0,0,0,0,0,917,0,0,0,0,0,917,0,0,0,0,0,0,17,18,0,0,156,1,
1,129,130,131,151,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,229,0,0,0,0,0,0,0,0,0,164,1,
1,137,138,139,44,0,0,194,0,0,0,0,0,0,0,0,0,0,0,230,179,185,185,185,185,185,185,185,185,185,181,1,
1,145,146,147,1030,0,0,193,0,0,0,0,0,0,0,0,0,0,0,238,186,156,0,0,0,0,0,0,0,0,0,1,
1,44,0,0,0,0,195,204,0,0,0,0,0,0,0,0,0,0,0,0,0,164,0,0,0,0,881,882,319,320,0,1,
1,0,68,0,0,195,204,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,889,890,327,328,0,1,
1,0,0,0,195,204,0,0,0,0,0,0,0,0,0,0,0,0,0,868,178,0,0,0,0,0,897,898,0,887,888,1,
1,199,199,199,207,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,177,0,160,0,160,0,0,0,0,895,896,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,10,9,10,177,156,0,0,0,0,160,263,264,903,904,1,
1,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,17,33,34,18,177,164,0,160,0,160,0,271,272,0,0,1,
1,21,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,18,49,187,185,185,185,185,185,185,185,185,185,181,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,49,49,49,0,0,49,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};


void load_level_1( SDL_Renderer* renderer , level &level_1 )
{
     
     level_1.levelfont = TTF_OpenFont( "Assets/8bit_font.ttf" , 32);
     SDL_Surface* temp = TTF_RenderText_Solid( level_1.levelfont , "Level 1" , {255,255,51});
     level_1.font = SDL_CreateTextureFromSurface(renderer, temp);
     level_1.set_level_dimensions( 30 , 32 , 21 , 34 );
     
     level_1.set_tileset("Assets/Level_1_Mining_Cave/Level1_tileset.png" , renderer); 

     vector <int> layer_1_values;
     vector <int> layer_2_values;
     vector <int> layer_3_values;
     
     layer_1_values = {
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,265,265,265,265,265,265,265,266,267,268,
35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,56,56,56,56,57,4,58,59,
69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,573,39,40,41,112,113,114,115,93,
103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,607,73,74,75,146,147,148,149,190,
137,138,241,242,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,641,107,108,109,180,181,182,183,224,
171,172,241,242,243,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,260,261,707,141,142,143,214,215,216,217,258,
205,206,241,242,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,294,295,581,244,207,222,219,357,358,359,394,
239,240,173,174,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,192,193,262,244,244,253,254,283,286,251,394,
273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,226,227,296,207,244,315,316,317,320,426,59,
307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,209,210,348,350,351,352,394,95,
341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,243,244,382,383,426,427,428,95,
375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,277,278,382,383,394,428,428,95,
409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,426,427,427,427,428,428,428,95,
443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,501,428,428,428,428,428,428,428,
477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,42,428,428,428,428,428,428,428,
511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,614,56,57,58,56,57,58,59,
545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,565,365,
579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,599,399,
613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,645,633,433,
647,69,581,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,668,669,670,663,656,673,669,675,711,466,467,
681,579,580,584,184,185,219,213,214,690,243,692,210,210,210,210,697,698,699,210,210,702,703,704,697,210,566,567,207,710,500,501,
62,613,614,207,275,275,209,277,243,212,213,214,244,244,244,244,390,390,390,244,244,390,390,390,391,244,600,601,282,426,427,428,
96,62,69,220,173,173,243,279,280,246,247,248,390,426,417,418,419,420,417,417,417,417,417,418,422,423,294,635,244,460,461,462,
130,96,103,186,207,275,277,313,314,244,281,282,390,399,681,681,681,681,681,681,681,681,681,681,681,293,172,363,211,212,214,496,
164,130,613,614,206,206,219,219,244,278,315,316,390,433,647,443,445,445,445,446,447,448,449,450,451,457,362,363,244,391,391,496,
198,164,62,579,616,617,618,390,278,390,390,390,391,467,681,579,580,390,391,390,390,390,391,391,390,390,294,363,390,316,391,496,
62,62,96,579,650,651,652,390,256,257,426,413,414,647,681,307,308,309,309,309,310,391,623,624,625,622,260,363,627,391,391,496,
96,62,130,613,684,685,686,390,290,291,360,647,647,647,681,613,614,342,342,343,344,391,657,658,659,656,668,669,661,177,391,496,
130,96,164,62,69,206,206,390,324,325,394,647,681,681,681,647,648,614,342,342,378,391,390,390,391,690,390,211,212,391,316,433,
164,130,198,96,409,410,411,412,420,421,428,681,681,428,428,681,682,409,410,411,412,410,410,410,411,412,414,415,416,417,418,428
};


     layer_2_values = {
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,334,334,334,334,334,335,336,337,
35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,56,56,56,56,57,4,58,59,
69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,573,39,40,41,112,113,114,115,93,
103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,607,73,74,75,146,147,148,149,190,
137,0,0,0,0,142,143,144,145,146,147,148,149,150,151,0,153,154,155,156,157,158,159,641,107,108,109,180,181,182,183,224,
171,0,0,0,0,0,0,0,179,180,181,182,183,184,185,0,0,188,189,190,191,0,0,0,0,142,143,0,0,0,0,258,
205,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,224,225,0,0,0,0,0,0,0,0,0,0,394,
239,0,0,174,0,0,0,0,0,0,0,0,0,0,0,0,0,256,257,258,259,0,193,262,0,0,0,0,283,286,0,394,
273,0,0,276,0,0,279,280,0,0,283,284,285,286,0,0,0,290,291,292,293,0,227,296,0,0,0,0,317,320,426,59,
307,308,309,310,311,312,313,314,0,0,317,318,319,320,321,0,0,0,0,326,327,0,0,0,0,0,348,350,351,352,394,95,
341,342,343,344,345,346,0,348,349,350,351,352,353,354,355,0,0,0,0,360,361,0,0,0,0,0,382,383,426,427,428,95,
375,376,377,378,379,380,0,382,383,384,385,386,387,388,389,0,0,0,0,394,395,0,0,0,0,0,382,383,394,428,428,95,
409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,0,0,426,427,428,429,0,0,0,426,427,427,427,428,428,428,95,
443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,0,0,460,461,462,463,464,0,0,501,428,428,428,428,428,428,428,
477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,0,0,494,495,496,497,498,0,0,42,428,428,428,428,428,428,428,
511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,0,0,528,529,530,531,0,0,0,614,56,57,58,56,57,58,59,
545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,0,0,562,563,564,565,0,0,0,569,570,571,572,573,574,565,365,
579,0,0,0,0,0,585,586,0,0,589,0,0,0,593,0,0,596,0,598,599,0,0,0,603,604,605,606,607,608,599,399,
613,614,0,0,0,0,0,0,0,0,0,624,0,0,0,0,0,0,0,632,633,0,0,0,637,638,639,640,641,645,633,433,
647,69,0,0,651,652,0,0,0,0,0,658,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,467,
681,579,0,0,184,185,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,501,
62,613,614,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,426,427,428,
96,62,69,0,0,0,0,279,280,0,0,0,0,426,417,418,419,420,417,417,417,417,417,418,422,423,0,0,0,460,461,462,
130,96,103,0,0,0,0,313,314,0,0,0,0,399,681,681,681,681,681,681,681,681,681,681,681,293,0,0,0,0,0,496,
164,130,613,614,0,0,0,0,0,0,0,0,0,433,647,443,445,445,445,446,447,448,449,450,451,457,0,0,0,0,0,496,
198,164,62,579,0,0,0,0,0,0,0,0,0,467,681,579,697,698,699,700,703,0,0,0,0,0,0,0,0,0,0,496,
62,62,96,579,0,651,652,0,256,257,426,413,414,647,681,307,308,309,309,309,310,0,0,624,0,0,0,0,0,0,0,496,
96,62,130,613,684,685,686,0,290,291,360,647,647,647,681,613,614,342,342,343,344,0,0,658,0,0,0,0,0,0,0,496,
130,96,164,62,69,0,0,0,0,0,394,647,681,681,681,647,648,614,342,342,378,0,0,0,0,0,0,0,0,0,0,433,
164,130,198,96,409,410,411,412,420,421,428,681,681,428,428,681,682,409,410,411,412,410,410,410,411,412,414,415,416,417,418,428
     };

for( int i=0 ; i< layer_1_values.size() ; ++i){
   
        int index = layer_1_values[i];
         
        if(index!=0)
        {
        tile temp_tile;
        temp_tile.copytile( level_1.tileset[index-1] );
        temp_tile.x = i%level_1.columns * temp_tile.width;
        temp_tile.y = i/(level_1.columns) * temp_tile.height;

        level_1.tiles_layer1.push_back( temp_tile );
        }
}

for( int i=0 ; i< layer_2_values.size() ; ++i){
   
        int indx = layer_2_values[i];
         
        if(indx!=0)
        {
        tile temp_tile;
        temp_tile.copytile( level_1.tileset[indx-1] );
        temp_tile.x = i%level_1.columns * temp_tile.width;
        temp_tile.y = i/(level_1.columns) * temp_tile.height;
        temp_tile.isobstacle=true;

        level_1.tiles_layer2.push_back( temp_tile );
        }
}
}

vector <int> level_1_collider
{
1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,334,334,334,334,334,335,336,337,
35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,56,56,56,56,57,4,58,59,
69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,573,39,40,41,112,113,114,115,93,
103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,607,73,74,75,146,147,148,149,190,
137,0,0,0,0,142,143,144,145,146,147,148,149,150,151,0,153,154,155,156,157,158,159,641,107,108,109,180,181,182,183,224,
171,0,0,0,0,0,0,0,179,180,181,182,183,184,185,0,0,188,189,190,191,0,0,0,0,142,143,0,0,0,0,258,
205,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,224,225,0,0,0,0,0,0,0,0,0,0,394,
239,0,0,174,0,0,0,0,0,0,0,0,0,0,0,0,0,256,257,258,259,0,193,262,0,0,0,0,283,286,0,394,
273,0,0,276,0,0,279,280,0,0,283,284,285,286,0,0,0,290,291,292,293,0,227,296,0,0,0,0,317,320,426,59,
307,308,309,310,311,312,313,314,0,0,317,318,319,320,321,0,0,0,0,326,327,0,0,0,0,0,348,350,351,352,394,95,
341,342,343,344,345,346,0,348,349,350,351,352,353,354,355,0,0,0,0,360,361,0,0,0,0,0,382,383,426,427,428,95,
375,376,377,378,379,380,0,382,383,384,385,386,387,388,389,0,0,0,0,394,395,0,0,0,0,0,382,383,394,428,428,95,
409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,0,0,426,427,428,429,0,0,0,426,427,427,427,428,428,428,95,
443,444,445,446,447,448,449,450,451,452,453,454,455,456,457,0,0,460,461,462,463,464,0,0,501,428,428,428,428,428,428,428,
477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,0,0,494,495,496,497,498,0,0,42,428,428,428,428,428,428,428,
511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,0,0,528,529,530,531,0,0,0,614,56,57,58,56,57,58,59,
545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,0,0,562,563,564,565,0,0,0,569,570,571,572,573,574,565,365,
579,0,0,0,0,0,585,586,0,0,589,0,0,0,593,0,0,596,0,598,599,0,0,0,603,604,605,606,607,608,599,399,
613,614,0,0,0,0,0,0,0,0,0,624,0,0,0,0,0,0,0,632,633,0,0,0,637,638,639,640,641,645,633,433,
647,69,0,0,651,652,0,0,0,0,0,658,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,467,
681,579,0,0,184,185,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,501,
62,613,614,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,426,427,428,
96,62,69,0,0,0,0,279,280,0,0,0,0,426,417,418,419,420,417,417,417,417,417,418,422,423,0,0,0,460,461,462,
130,96,103,0,0,0,0,313,314,0,0,0,0,399,681,681,681,681,681,681,681,681,681,681,681,293,0,0,0,0,0,496,
164,130,613,614,0,0,0,0,0,0,0,0,0,433,647,443,445,445,445,446,447,448,449,450,451,457,0,0,0,0,0,496,
198,164,62,579,0,0,0,0,0,0,0,0,0,467,681,579,697,698,699,700,703,0,0,0,0,0,0,0,0,0,0,496,
62,62,96,579,0,651,652,0,256,257,426,413,414,647,681,307,308,309,309,309,310,0,0,624,0,0,0,0,0,0,0,496,
96,62,130,613,684,685,686,0,290,291,360,647,647,647,681,613,614,342,342,343,344,0,0,658,0,0,0,0,0,0,0,496,
130,96,164,62,69,0,0,0,0,0,394,647,681,681,681,647,648,614,342,342,378,0,0,0,0,0,0,0,0,0,0,433,
164,130,198,96,409,410,411,412,420,421,428,681,681,428,428,681,682,409,410,411,412,410,410,410,411,412,414,415,416,417,418,428
};

 bool check_collision_for_level( level cur_level , texrect entity , vector <int> collider , int code )          
 {
        
            int ind,cx,cy;
           
            if( code == 1){ // code 1 implies entity is a projectile

                 cx = entity.rectangle.x +  (entity.rectangle.w/2);
                 cy = entity.rectangle.y +  (entity.rectangle.h/2);
    
            }
            else{

                   cx = entity.rectangle.x+(entity.rectangle.w/2)+CAMX;
                   cy = entity.rectangle.y + (entity.rectangle.h/2)+CAMY;


            }
            int column = cx/64 ;
            int rows = cy/64;
            ind = column + rows*cur_level.columns;            

            if( collider[ind] != 0 )
            {
                return true;
            } 
            else 
            {
               return false;
            }
 }    



    void level_transition( vector <level> &levels , vector < vector<int> > &colliders ,vector<vector <Enemy>> &enemies , int &index , level &cur , vector <int> &cur_col , vector <Enemy> &cur_enemy , Sigma &player , vector <vector <powerup>> &powerups , vector <powerup> &cur_powerup, SDL_Renderer* renderer)
     {
                
                if( player.health == 0)
                {     
                        levels[0].fontstart = true;
                        cur = levels[0];
                        cur_col = colliders[0];
                        cur_enemy = enemies[0];
                      
                        player.rectangle.x = 120;
                        player.rectangle.y = 230;
                        index = 0;


                }
                int player_screenx = player.rectangle.x + CAMX;
                int player_screeny = player.rectangle.y + CAMY;

                //cout << index << endl;

                switch( index )
                {
                case -1:
                CAMX = CAMY = 0;
                player.rectangle.x = 512;
                player.rectangle.y = 400;
                index = 0;
                load_level_1(renderer , levels[1]);
                cur = levels[0];
                cur_col = colliders[0];
                cur_enemy = enemies[0];
                cur_powerup = powerups[0];

                break;

                case 0:

                if( player_screenx <400 && player_screenx>377 && player_screeny == 354)
                {
                     levels[1].fontstart = true;
                     cur = levels[1];
                     cur_col = colliders[1];
                     cur_enemy = enemies[1];
                     cur_powerup = powerups[1]; 

                     player.rectangle.x = 120 - CAMX;
                     player.rectangle.y = 230 - CAMY;
                     index = 1;
                     
                }   
                break;    
              

                }
                

     }

     void load_enemies( vector <vector <Enemy>> &enemies , SDL_Renderer* renderer , SDL_Window* window)
     {       
            vector <Enemy> level0;
            enemies.push_back(level0);
                 
            vector <Enemy> level1;
              

           Enemy temp( 48 ,48 , 561 , 390 , 708 , 390  ,1,renderer ,window);
           level1.push_back( temp );

           temp.change( 953 , 460 , 1025 , 460 ,1 );
             level1.push_back(temp);

             temp.change( 941 , 1080 , 1025 , 1080 ,2);
             level1.push_back(temp);

            temp.change( 1154 , 1141 , 1082 , 1141 ,1);
            level1.push_back(temp);

            temp.change( 759 , 1412 , 759 , 1583 ,1);
            level1.push_back(temp);

            temp.change( 450 , 1777 , 450 ,1639,2);
            level1.push_back(temp);    

            temp.change( 315 , 1333 , 207 , 1333 ,1);
            level1.push_back(temp);

            temp.change( 1488 , 1330 , 1650 , 1330 ,1);
            level1.push_back(temp);
             
            temp.change( 1344 , 1779 , 1344 , 1593 ,1);
            level1.push_back(temp);

            temp.change( 1919 , 1656 , 1919 , 1790 ,1);
            level1.push_back(temp);

            temp.change( 1463 , 692 , 1463 , 554 ,1);
            level1.push_back(temp);

            temp.change( 1538 , 362 , 1538 , 437 ,1);
            level1.push_back(temp);

            temp.change( 1598 , 437 , 1598 , 359 ,1);
            level1.push_back(temp);

            temp.change( 953 , 270  ,  940 , 270 ,3);
            level1.push_back(temp);

           enemies.push_back(level1);       
            


     }

     void load_powerups( vector <vector <powerup> > &powerups , SDL_Renderer* renderer , SDL_Window* window ){
                    
                  vector <powerup> level0;
                  powerups.push_back(level0);

                  vector <powerup> level1;

                  powerup temp( renderer , window );
                  temp.spawn_powerup( 370 , 470 , SPEED_INCREASE);
                  level1.push_back( temp );

                  temp.spawn_powerup( 984 , 998 , HEALTH_INCREASE);
                  level1.push_back( temp );

                  temp.spawn_powerup( 637 , 1329 , BULLET_DAMAGE_INCREASE);
                  level1.push_back( temp );

                  temp.spawn_powerup( 250 , 1653 , HEALTH_INCREASE);
                  level1.push_back( temp );

                  temp.spawn_powerup( 1313 , 1266 , SPEED_INCREASE);
                  level1.push_back( temp );

                  temp.spawn_powerup( 1346 , 1777 , SPEED_INCREASE);
                  level1.push_back( temp );

                  temp.spawn_powerup( 1592 , 690 , BULLET_DAMAGE_INCREASE);
                  level1.push_back( temp );

                  powerups.push_back(level1); 

     }


     void update_enemies( vector <Enemy> &enemies , Sigma &player)
     {
               for( int i=0 ; i< enemies.size() ; ++i)
               {
                      if( enemies[i].ehealth <= 0){
                   
                                 enemies.erase(enemies.begin() + i);

                      }
                      update_enemy( player , enemies[i] );
               }

         for(int i=0 ; i<eBullets.size() ; ++i){
              eBullets[i].update_projectile();
              eBullets[i].update();
              
              if( isplayercolliding(eBullets[i],player) ){
                     eBullets.erase(eBullets.begin()+i);
                     player.health--;
              }
       }

       ECOUNTER++;

     }
       void update_enemy_bullets( level &cur_level , vector <int> &cur_collider )
  {
                
           for(int i=0 ; i<eBullets.size() ; ++i){
               
                     if(check_collision_for_level( cur_level , eBullets[i] , cur_collider , 1))
                     {
                                 eBullets.erase(eBullets.begin() + i); 
                     }
                    
              }
       }    

 
       void trigger_font( level &cur_level , SDL_Renderer* renderer)
       {
             
              if(cur_level.fontstart && textcounter<300){
                     
                    SDL_Rect dest;
                    dest.w = 800;
                    dest.h = 250;
                    dest.x = 112;
                    dest.y = 230;

                    SDL_RenderCopy( renderer , cur_level.font , NULL , &dest);
                    textcounter++;

              }

              else 
              {
               textcounter = 0;
               cur_level.fontstart = false;
              }

       }

          void update_bullets( vector <Enemy> &cur_enemies , vector <int> &cur_collider , level &cur_level ){

              update_enemy_bullets( cur_level , cur_collider);

              for( int i=0 ; i<Bullets.size() ; ++i ){ //bullets loop
                   
                   if(check_collision_for_level(cur_level , Bullets[i] , cur_collider, 1))
                     {
                            Bullets.erase(Bullets.begin() + i);
                     }

                     for ( int j = 0 ; j < cur_enemies.size() ; ++j){

                                 if( iscolliding( Bullets[i] , cur_enemies[j] )){

                                        cur_enemies[j].ehealth--;
                                        Bullets.erase( Bullets.begin() + i);
                                        break;
              
                                 }

                     }
                     
                     Bullets[i].update_projectile();
                     Bullets[i].update();
             
              }

      }

      bool gameisover = false;

      void check_game_over ( Sigma &player , int &cur_level_index , keypress gkey , SDL_Renderer* renderer ){

               if( player.health <= 0 ){
                    
                     gameisover = true;

                     SDL_Rect rect1;
                     rect1.h = 250;
                     rect1.w = 900;
                     rect1.x = 62;
                     rect1.y = 300;

                     SDL_Rect rect2;
                     rect2.h = 75;
                     rect2.w = 900;
                     rect2.x = 62;
                     rect2.y = 600;

                      
                    SDL_RenderCopy( renderer , player.gameover_text1 , NULL , &rect1);
                    SDL_RenderCopy( renderer , player.gameover_text2 , NULL , &rect2);

                    if( gkey == KEY_ENTER )
                    {
                         cur_level_index = -1;
                         player.health = 10;
                         player.stamina = 10;
                         gameisover = false;
                    }

               }

      }


#endif