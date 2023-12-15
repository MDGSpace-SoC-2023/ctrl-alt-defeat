
#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "objects.h"
#include <map>

using namespace std;
typedef int gid;

class tile 
{
    public:

    SDL_Texture* tiletext = NULL;

    int width;
    int height;

    int x; //x and y coords on the map
    int y;
     
    int sx; // x and y coords on the sprite sheet
    int sy;
    
    int index;
    tile ( SDL_Texture* text)
    {
         tiletext = text;
         x=0;
         y=0;
         width=0;
         height=0;
         sx=0;
         sy=0;
    }

    tile ( SDL_Texture* text, int sxn , int syn , int w , int h , int ind)
    {
          sx=sxn;
          sy=syn;
          tiletext = text;
          width=w;
          height=h;
          index=ind;
    }

    void rendertile ( SDL_Renderer* renderer )
    {
         
         SDL_Rect src;
         src.x=sx;
         src.y=sy;
         src.w=width;
         src.h=height;
         
         SDL_Rect dest;
         dest.x=x;
         dest.y=y;
         dest.w=src.w;
         dest.h=src.h;
        
         SDL_RenderCopy( renderer , tiletext , &src , &dest );

     }

};


class level
{
     public:
     string name;
     int rows;
     int columns;
     int tile_width;
     int tile_height;

     vector <tile> tiles ;
     //creating a map from int to textures to store the tileset
     map < gid , SDL_Texture* > tilesets; 
      
     level ( string nam , int r , int c , int tw , int th)
     {
          name=nam;
          rows=r;
          columns=c;
          tile_width=tw;
          tile_height=th;
     }

     void set_tileset( string path , SDL_Renderer* ren )
     { 
          SDL_Surface* tile_surface = IMG_Load( path.c_str() );
          SDL_Texture* tileset_texture = SDL_CreateTextureFromSurface( ren ,  tile_surface );
      
          for( int i=0 ; i<rows ; ++i){
              for( int j=0 ; j<columns ; ++j){
                      
                     int index = j + i*columns;
                     tile temp_tile( tileset_texture , j*tile_width , i*tile_height , tile_width , tile_height , index);
                     tiles.push_back( temp_tile );
              }     
          }
     }

    void draw( SDL_Renderer* ren )
    {
    for ( auto& tile : tiles ) 
    {
        tile.rendertile(ren);
    }
    }

};









#endif