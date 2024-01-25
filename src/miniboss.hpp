#ifndef MINIBOSS_HPP
#define MINIBOSS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "objects.h"
using namespace std;

bool boss_fight = false;

class miniboss{

      public:
      int miniboss_counter = 0;
      int miniboss_counter2 = 0;
      int wall_x1 , wall_x2;
      int wall_y1 , wall_y2;
      int x,y;
      SDL_Texture* miniboss_texture = NULL;
      SDL_Texture* gunshot_texture = NULL;
      SDL_Rect dest;
      int health = 50;

      miniboss( int bosscode , SDL_Renderer* renderer , int xn , int yn){

          SDL_Surface* temp = NULL;

          x = xn;
          y = yn;
          dest.w = 128;
          dest.h = 256;
        
          if(bosscode == 1){
                temp = IMG_Load( "Assets/Miniboss/blue.png");
                miniboss_texture = SDL_CreateTextureFromSurface( renderer , temp );
                temp = IMG_Load( "Assets/blue_gunshot.png");
                gunshot_texture = SDL_CreateTextureFromSurface( renderer , temp);
                wall_x1 = 2944;
                wall_x2 = 3840;
                wall_y1 = 512;
                wall_y2 = 1024;
          }
          if(bosscode == 2){
                temp = IMG_Load( "Assets/Miniboss/red.png");
                miniboss_texture = SDL_CreateTextureFromSurface( renderer , temp );
                temp = IMG_Load( "Assets/red_gunshot.png");
                gunshot_texture = SDL_CreateTextureFromSurface( renderer , temp);
          
          }
          if(bosscode == 3){
                temp = IMG_Load( "Assets/Miniboss/magenta.png");
                miniboss_texture = SDL_CreateTextureFromSurface( renderer , temp );
                temp = IMG_Load( "Assets/purple_gunshot.png");
                gunshot_texture = SDL_CreateTextureFromSurface( renderer , temp);

          }

          SDL_FreeSurface(temp);

      }

      void display_miniboss( SDL_Renderer* renderer ){

          miniboss_counter++;
          miniboss_counter %= 280;
        
          SDL_Rect src;
          src.w = 32;
          src.h = 64;
          src.x = (64*(miniboss_counter%70/5)) + 14;
          src.y =  0;

          dest.x = x -CAMX;
          dest.y = y -CAMY;
     
          SDL_RenderCopy(renderer , miniboss_texture , &src , &dest);      

      }     

      };

      void teleport_miniboss( int playerx, int playery , int wallx1 , int wallx2 , int wally1 , int wally2 , miniboss &miniboss){

                     int first = rand()%2;
                     int second = rand()%2;

                     int x1 = playerx - 64;
                     int x2 = playerx + 128;

                     int y1 = playery - 64;
                     int y2 = playery + 128;

                     if( (playerx < wallx2 && playerx > wallx1) && (playery < wally2 && playery > wally1))

                    {                     
                         if(first){ // code first == 1 means it teleports to the same y coordinate as the player
 
                         if( second && ((x1 - wallx1) > 128) ){ // code second == 1 means it teleports to segment no.1 
                              miniboss.y = playery - 64;
                              miniboss.x = wallx1 + rand()%(x1 - wallx1);


                         }
                         else if( (wallx2 - x2) > 128 ){

                              miniboss.y = playery - 64;
                              miniboss.x = x2 + rand()%(wallx2 - x2);

                         }
                         else {
                            
                              miniboss.y = playery - 64;
                              miniboss.x = wallx1 + rand()%(x1 - wallx1);                               

                         }

                     }
                     else {

                         if( second && ( y1 - wally1 > 128 ) ){ // code second == 1 means it teleports to segment no.1 
                              miniboss.x = playerx - 64;
                              miniboss.y = wally1 + rand()%(y1 - wally1);

                         }
                         else if( (wally2 - y2) > 128 ){

                              miniboss.x = playerx - 64;
                              miniboss.y = y2 + rand()%(wally2 - y2);

                         }
                         else {
                            
                              miniboss.x = playerx - 64;
                              miniboss.y = wally1 + rand()%(y1 - wally1);                               

                         }

                     }
                    }
       
                else{
              
                    boss_fight = false;

                }

       }

      void spawn_miniboss_bullets(miniboss &miniboss , SDL_Renderer* renderer , SDL_Window* window ){

              projectile bullet1( miniboss.x - 64 , miniboss.y - 32  , 1 , renderer , window , 40 , miniboss.gunshot_texture);                     
              projectile bullet2( miniboss.x - 64 , miniboss.y - 32  , 2 , renderer , window , 40 , miniboss.gunshot_texture);                     
              projectile bullet3( miniboss.x - 64 , miniboss.y - 32  , 3 , renderer , window , 40 , miniboss.gunshot_texture);                     
              projectile bullet4( miniboss.x - 64 , miniboss.y - 32  , 4 , renderer , window , 40 , miniboss.gunshot_texture);                     
              miniboss_bullets.push_back(bullet1);
              miniboss_bullets.push_back(bullet2);
              miniboss_bullets.push_back(bullet3);
              miniboss_bullets.push_back(bullet4);

      }  


      void update_minibosses( vector <miniboss> &minibosses , SDL_Renderer* renderer , Sigma &player){

            for( int i=0 ; i<1 ; ++i){

                   miniboss &cur_boss = minibosses[i];
                   if(boss_fight)cur_boss.miniboss_counter2++;

                     if( cur_boss.miniboss_counter2 == 300 && boss_fight ){
      
                        teleport_miniboss( player.rectangle.x + CAMX, player.rectangle.y + CAMY , cur_boss.wall_x1 , cur_boss.wall_x2 , cur_boss.wall_y1 , cur_boss.wall_y2 , cur_boss);
                        cur_boss.miniboss_counter2 = 0;

                     }
                     if( (cur_boss.miniboss_counter2 == 80 || cur_boss.miniboss_counter2 == 100) && boss_fight ){
                             
                             spawn_miniboss_bullets(cur_boss , player.renderer , player.window);

                     }

                   cur_boss.display_miniboss( renderer );
            }


      }



#endif