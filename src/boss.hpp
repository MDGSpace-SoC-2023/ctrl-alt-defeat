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

      public:

      //first is starting index and second is length
      pair < int , int > standing;
      pair < int , int > attack;
      pair < int , int > dying;
      pair < int , int > hit;
      pair < int , int > cur_boss_animation;
      int speed;
      int tilesize;
      int columns ;
      int cur_index=0;
      int x,y;
      SDL_Rect  collider , dest;
      

      SDL_Texture* Boss_tileset = NULL;

      Boss( SDL_Renderer* renderer , int xn , int yn , int size){

            SDL_Surface* tempsur;
            tempsur = IMG_Load( "Assets/boss.png" );
            Boss_tileset = SDL_CreateTextureFromSurface( renderer , tempsur);
            SDL_FreeSurface( tempsur);

            tilesize =  192;
            standing = {0,7};
            attack = {18,14};
            hit = {31, 6};
            dying = {37,15};
            cur_boss_animation = standing;
            columns = 7;
            cur_index = 0;
            speed = 10;

            // src.w = 192;
            // src.h = 192;
            dest.w = size;
            dest.h = size;
            collider.h = 96;
            collider.w = 96;
            x = xn;
            y = yn;

      }

      void update_boss(SDL_Renderer* renderer){

            SDL_Rect src;
            src.w = tilesize;
            src.h = tilesize;
            src.x = ((cur_index+1)/columns)*tilesize;
            src.y = ((cur_index+1)%columns)*tilesize;

            dest.x = x - CAMX;
            dest.y = y - CAMY;

            SDL_RenderCopy(renderer,Boss_tileset,&src,&dest);
            bosscounter++;

            if(bosscounter>speed){
                  cur_index++;
                  bosscounter=0;
            }
            if(cur_index>cur_boss_animation.first+cur_boss_animation.second-1) cur_index = cur_boss_animation.first;           

      }


};

void load_main_boss( SDL_Renderer* renderer , vector <Boss>& main_bosses){

         Boss main_boss( renderer , 1276 , 620 , 244);
         main_bosses.push_back(main_boss);
         main_boss.dest.w = 500;
         main_boss.dest.h = 500;
         main_bosses.push_back(main_boss);

}


#endif