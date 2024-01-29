#ifndef BOMB_HPP
#define BOMB_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "objects.h"
using namespace std;



class bomb{
    public:
        int x,y;
        int framecounter = 0 , index = 0;
        SDL_Texture* text = NULL;

        bomb(SDL_Renderer* ren){
            SDL_Surface* tmp = IMG_Load("Assets/bomb.png");
            text = SDL_CreateTextureFromSurface(ren,tmp);
            SDL_FreeSurface(tmp);
            x = 64*(4 + rand()%24);
            y = 64*(4 + rand()%24);
        }

        void update(SDL_Renderer* ren , Sigma& player , int& done){
            if(index<40){
                SDL_Rect src;
                src.w = src.h = 80;
                src.x = index * 80;
                src.y = 0;

                SDL_Rect dest;
                dest.w = dest.h = 64;
                dest.x = x-CAMX;
                dest.y = y-CAMY; 

                SDL_RenderCopy(ren,text,&src,&dest);

                if(framecounter>=4){
                    index++;
                    framecounter = 0;    
                }
                framecounter++;
                if(index==39 && framecounter==2 && (player.rectangle.x>=(dest.x - 64) && player.rectangle.x<=(dest.x + 128) && player.rectangle.y>=(dest.y - 64) && player.rectangle.y<=(dest.x + 128))){
                    player.health -= 3;
                }
            }
            else done = 1;

        }

};

#endif