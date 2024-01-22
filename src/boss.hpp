#ifndef BOSS_HPP
#define BOSS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "objects.h"
using namespace std;

int bosscounter = 0;
class Boss{

      //first is starting index and second is length
      pair < int , int > standing;
      pair < int , int > attack_left;
      pair < int , int > attack_right;
      pair < int , int > teleportation; 
      pair < int , int > cur_boss_animation;
      int speed;
      int tilesize;
      int rows , columns ;
      int cur_index;
      SDL_Rect rectangle , srectangle;

      SDL_Texture* Boss_tileset = NULL;

      Boss( SDL_Renderer* renderer , string path ){

            SDL_Surface* tempsur;
            tempsur = IMG_Load( path.c_str() );
            Boss_tileset = SDL_CreateTextureFromSurface( renderer , tempsur);
            SDL_FreeSurface( tempsur);
            tilesize =  64;
            standing = {0,0};
            attack_left = {0,0};
            attack_right = {0,0};
            teleportation = {0,0};
            cur_boss_animation = standing;
            rows = 0;
            columns = 0;
            rectangle.x = 0;
            rectangle.y = 0;
            srectangle.h = srectangle.w = tilesize;

      


      }

      void update_boss(SDL_Renderer* renderer){
            
            SDL_Rect src;
            src.x = (cur_index/columns)*tilesize;
            src.y = (cur_index%columns)*tilesize;
            src.h = src.w = tilesize;

            srectangle.x = rectangle.x-CAMX;
            srectangle.y = rectangle.y-CAMY;

            SDL_RenderCopy(renderer,Boss_tileset,&src,&srectangle);

            if(bosscounter>speed){
                  cur_index++;
                  bosscounter=0;
            }
            if(cur_index>cur_boss_animation.first+cur_boss_animation.second-1) cur_index = cur_boss_animation.first;
                     

      }


};


#endif