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
      pair < int , int > attack;
      pair < int , int > dying;
      pair < int , int > hit;
      pair < int , int > cur_boss_animation;
      int speed;
      int tilesize;
      int columns ;
      int cur_index;
      SDL_Rect src , collider , dest;
      

      SDL_Texture* Boss_tileset = NULL;

      Boss( SDL_Renderer* renderer , string path ){

            SDL_Surface* tempsur;
            tempsur = IMG_Load( path.c_str() );
            Boss_tileset = SDL_CreateTextureFromSurface( renderer , tempsur);
            SDL_FreeSurface( tempsur);

            tilesize =  192;
            standing = {0,7};
            attack = {18,31};
            hit = {31, 36};
            dying = {37,51};
            cur_boss_animation = standing;
            columns = 7;

            src.w = 192;
            src.h = 192;
            dest.w = 192;
            dest.h = 192;
            collider.h = 96;
            collider.w = 96;

      }

      void update_boss(SDL_Renderer* renderer){
            
            SDL_Rect src;
            src.x = (cur_index/columns)*tilesize;
            src.y = (cur_index%columns)*tilesize;

            dest.x = rectangle.x-CAMX;
            dest.y = rectangle.y-CAMY;

            SDL_RenderCopy(renderer,Boss_tileset,&src,&srectangle);

            if(bosscounter>speed){
                  cur_index++;
                  bosscounter=0;
            }
            if(cur_index>cur_boss_animation.first+cur_boss_animation.second-1) cur_index = cur_boss_animation.first;
                     

      }


};


#endif