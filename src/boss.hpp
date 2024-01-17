#ifndef BOSS_HPP
#define BOSS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
using namespace std;

int bosscounter = 0;
class Boss{

     pair < int , int > standing;
     pair < int , int > attack_left;
     pair < int , int > attack_right;
     pair < int , int > teleportation; 
     pair < int , int > cur_boss_animation;
     int tilesize;

     SDL_Texture* Boss_tileset = NULL;

     Boss( SDL_Renderer* renderer , string path ){

           SDL_Surface* tempsur;
           tempsur = IMG_Load( path.c_str() );
           Boss_tileset = SDL_CreateTextureFromSurface( renderer , tempsur);
           SDL_FreeSurface( tempsur);
           tilesize =  
   


     }

     void update_boss(){

            
               
               

     }


};


#endif