
#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "objects.h"

using namespace std;

class tile 
{
    public:

    SDL_Texture* tiletext = NULL;

    int width=32;
    int height=32;

    int x; //x and y coords on the map
    int y;
     
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

     void copytile ( tile tileset_tile ) // for copying the tileset data onto the map data
     {
         
         tiletext = tileset_tile.tiletext;
         sx=tileset_tile.sx;
         sy=tileset_tile.sy;
         width = tileset_tile.width;
         height = tileset_tile.height;

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

     vector <tile> tileset ;
     int tileset_rows;
     int tileset_columns;

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


void load_main_menu( SDL_Renderer* renderer , level main_menu )
{

     main_menu.set_level_dimensions( 30 , 32 , 133 , 8 );
     
     main_menu.set_tileset("Assets/test_tileset.png" , renderer); 

     vector <int> layer_1_values;
     
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
250,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,249,252};

for( int i=0 ; i< layer_1_values.size() ; ++i){
   
        int index = layer_1_values[i];
         
        tile temp_tile;
        temp_tile.copytile( main_menu.tileset[index] );
        temp_tile.x = i%main_menu.columns;
        temp_tile.y = i/(main_menu.rows);

        main_menu.tiles_layer1.push_back( temp_tile );
        
}



}



       







#endif