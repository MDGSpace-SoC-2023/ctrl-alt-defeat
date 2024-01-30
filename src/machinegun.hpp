#ifndef MACHINEGUN_HPP
#define MACHINEGUN_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "objects.h"

int guncounter = 20;
bool machinegun_started;
class machinegun{

       public:
       SDL_Rect rectangle , srectangle;
 
       SDL_Renderer* renderer;
       SDL_Window* window; 
       SDL_Texture* text; 
       machinegun( SDL_Renderer* ren , SDL_Window* win){
               rectangle.x = 0;
               rectangle.y = 0;
               rectangle.w = 128;
               rectangle.h = 128;
               srectangle.w = 128;
               srectangle.h = 128;
               renderer = ren;
               window = win;
       }  

       void loadtexture( std::string path)//loading texture from a path
       {
              SDL_Surface* temp=IMG_Load( path.c_str() );
              text = SDL_CreateTextureFromSurface( renderer , temp );
              SDL_FreeSurface(temp);
              SDL_RenderCopy(renderer , text , NULL , &rectangle );

       } 
    

       void spawn_machinegun( int x , int y  )
       {
              rectangle.x = x;
              rectangle.y = y;

              machinegun_started = false;
              loadtexture("Assets/machinegun.png");

              
       }

       void trigger_machinegun(Sigma& player)
       {
                  player.bullet_damage=3;
                  guncounter = 5;
                  machinegun_started = true;

       }

       void update(SDL_Renderer* ren , Sigma& player){
            int isplayercolliding = 0;
            SDL_Rect playerrect = player.rectangle;
            playerrect.x+=CAMX;
            playerrect.y+=CAMY;
            SDL_Rect &rect_b = rectangle;
           
           if( SDL_HasIntersection ( &playerrect , &rect_b ) ) isplayercolliding = 1 ;
           else isplayercolliding = 0;



            if( isplayercolliding){
                                        
                trigger_machinegun( player );
                rectangle.w = 0;
                rectangle.h = 0;

            }

            if(!machinegun_started){
                srectangle.x = rectangle.x - CAMX;
                srectangle.y = rectangle.y - CAMY;   
                SDL_RenderCopy(renderer , text , NULL , &srectangle );
            }

       }

     

};




       

#endif
