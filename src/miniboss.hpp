#ifndef MINIBOSS_HPP
#define MINIBOSS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "objects.h"
#include "Particle_effects.hpp"
#include "Music.hpp"
using namespace std;

int active_boss_fight = 0;
Music miniboss_music1;
Music miniboss_music2;
Music miniboss_music3;
int dead_boss = 0;

class miniboss{

      public:
      int miniboss_counter = 0;
      int miniboss_counter2 = 0;
      int ring_counter = 0;
      int deadcount = 0;
      int wall_x1 , wall_x2;
      int wall_y1 , wall_y2;
      int x,y;
      int bullet_damage;
      int bosscode;
      bool bossfight;
      SDL_Texture* miniboss_texture = NULL;
      SDL_Texture* gunshot_texture = NULL;
      SDL_Texture* empty_health = NULL;
      SDL_Texture* health_segment = NULL;
      SDL_Rect dest;
      SDL_Rect collision_box;
      Sound miniboss_shooting;
      int health = 62;

      miniboss( int code , SDL_Renderer* renderer , int xn , int yn){

          SDL_Surface* temp = NULL;
          x = xn;
          y = yn;
          dest.w = 128;
          dest.h = 256;
          bosscode = code;
        
          if(bosscode == 1){
                temp = IMG_Load( "Assets/Miniboss/blue.png");
                miniboss_texture = SDL_CreateTextureFromSurface( renderer , temp );
                temp = IMG_Load( "Assets/blue_gunshot.png");
                gunshot_texture = SDL_CreateTextureFromSurface( renderer , temp);
                miniboss_music1.Load_Music( "Assets/Audio/Music/bad_guy.mp3" , 50);
                wall_x1 = 2944;
                wall_x2 = 3840;
                wall_y1 = 512;
                wall_y2 = 1024;
                bullet_damage = 3;
          }
          if(bosscode == 2){
                temp = IMG_Load( "Assets/Miniboss/red.png");
                miniboss_texture = SDL_CreateTextureFromSurface( renderer , temp );
                temp = IMG_Load( "Assets/red_gunshot.png");
                gunshot_texture = SDL_CreateTextureFromSurface( renderer , temp);
                miniboss_music2.Load_Music( "Assets/Audio/Music/another_one.mp3" , 50);
                wall_x1 = 2752;
                wall_x2 = 3904;
                wall_y1 = 2752;
                wall_y2 = 3520;
                bullet_damage = 1;
          
          }
          if(bosscode == 3){
                temp = IMG_Load( "Assets/Miniboss/magenta.png");
                miniboss_texture = SDL_CreateTextureFromSurface( renderer , temp );
                temp = IMG_Load( "Assets/purple_gunshot.png");
                gunshot_texture = SDL_CreateTextureFromSurface( renderer , temp);
                miniboss_music3.Load_Music( "Assets/Audio/Music/in_the_end.mp3" , 50);
                wall_x1 = 1536;
                wall_x2 = 2560;
                wall_y1 = 1408;
                wall_y2 = 2304;
                bullet_damage = 2;

          }

               temp = IMG_Load("Assets/empty_health.png");
               empty_health = SDL_CreateTextureFromSurface(renderer , temp);
               temp = IMG_Load("Assets/health_segment.png");
               health_segment = SDL_CreateTextureFromSurface(renderer , temp);
                    
          collision_box = dest;
          collision_box.h = 170;
          SDL_FreeSurface(temp);

      }

      void display_miniboss( SDL_Renderer* renderer ){
          ring_counter++;
          if(ring_counter >= 120){
          miniboss_counter++;
          miniboss_counter %= 70;
        
          SDL_Rect src;
          src.w = 32;
          src.h = 64;
          src.x = (64*(miniboss_counter/5)) + 14;
          src.y =  0;

          dest.x = x -CAMX;
          dest.y = y -CAMY;
          collision_box.x = dest.x;
          collision_box.y = dest.y;
     
          SDL_RenderCopy(renderer , miniboss_texture , &src , &dest);   
          }  

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
              
                    miniboss.bossfight = false;

                }
                miniboss.ring_counter = 0;
                trigger_animation(miniboss_teleport_animation,miniboss.x+32,miniboss.y+96,128,120);

       }

      void spawn_miniboss_bullets(miniboss &miniboss , SDL_Renderer* renderer , SDL_Window* window , int size ){
          if(miniboss.bosscode ==1 || miniboss.bosscode == 2){
          miniboss_shooting.Play_sound(0);
              projectile bullet1( miniboss.x , miniboss.y  , 1 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet2( miniboss.x , miniboss.y  , 2 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet3( miniboss.x , miniboss.y  , 3 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet4( miniboss.x , miniboss.y  , 4 , renderer , window , size , miniboss.gunshot_texture);                     
              miniboss_bullets.push_back(bullet1);
              miniboss_bullets.push_back(bullet2);
              miniboss_bullets.push_back(bullet3);
              miniboss_bullets.push_back(bullet4);
          }
          else{
        miniboss_shooting.Play_sound(0);

              projectile bullet1( miniboss.x -32 , miniboss.y , 1 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet2( miniboss.x -32 , miniboss.y  , 2 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet3( miniboss.x  , miniboss.y -32 , 3 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet4( miniboss.x , miniboss.y-32 , 4 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet5( miniboss.x +32  , miniboss.y , 1 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet6( miniboss.x +32, miniboss.y  , 2 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet7( miniboss.x  , miniboss.y +32 , 3 , renderer , window , size , miniboss.gunshot_texture);                     
              projectile bullet8( miniboss.x , miniboss.y +32 , 4 , renderer , window , size , miniboss.gunshot_texture);  
              miniboss_bullets.push_back(bullet1);
              miniboss_bullets.push_back(bullet2);
              miniboss_bullets.push_back(bullet3);
              miniboss_bullets.push_back(bullet4);                   
              miniboss_bullets.push_back(bullet5);
              miniboss_bullets.push_back(bullet6);
              miniboss_bullets.push_back(bullet7);
              miniboss_bullets.push_back(bullet8);
          }

      }  


      void update_minibosses( vector <miniboss> &minibosses , SDL_Renderer* renderer , Sigma &player){

            for( int i=0 ; i<minibosses.size() ; ++i){

                miniboss &cur_boss = minibosses[i];
                if(cur_boss.health>0){
                    if( (player.rectangle.x + CAMX < cur_boss.wall_x2 && player.rectangle.x + CAMX > cur_boss.wall_x1) && (player.rectangle.y + CAMY < cur_boss.wall_y2 && player.rectangle.y + CAMY > cur_boss.wall_y1))
                        {
                            cur_boss.bossfight = true;
                        }
                        else
                        {
                            cur_boss.bossfight = false;
                            active_boss_fight = 0;
                        }

                    if(cur_boss.bossfight)
                    {
                        cur_boss.miniboss_counter2++;
                    }

                        if( cur_boss.miniboss_counter2 == 420 && cur_boss.bossfight ){
                            
                            teleport_miniboss( player.rectangle.x + CAMX, player.rectangle.y + CAMY , cur_boss.wall_x1 , cur_boss.wall_x2 , cur_boss.wall_y1 , cur_boss.wall_y2 , cur_boss);
                            cur_boss.miniboss_counter2 = 0;

                        }

                        if(cur_boss.bosscode == 1){
                            if( (cur_boss.miniboss_counter2 == 20+120 || cur_boss.miniboss_counter2 == 40+120 || cur_boss.miniboss_counter2 == 100+120 || cur_boss.miniboss_counter2 == 120+90) && cur_boss.bossfight ){
                                
                                spawn_miniboss_bullets(cur_boss , player.renderer , player.window,40);

                            }
                        }
                        else if(cur_boss.bosscode == 2){
                            if( (cur_boss.miniboss_counter2 == 5+120 || cur_boss.miniboss_counter2 == 10 + 120|| cur_boss.miniboss_counter2 == 15+120 || cur_boss.miniboss_counter2 == 105 +120|| cur_boss.miniboss_counter2 == 110+120 || cur_boss.miniboss_counter2 == 115+120 || cur_boss.miniboss_counter2 == 205+120 || cur_boss.miniboss_counter2 == 210+120 || cur_boss.miniboss_counter2 == 215+120) && cur_boss.bossfight ){
                                
                                spawn_miniboss_bullets(cur_boss , player.renderer , player.window,20);

                            }
                        }
                        else if(cur_boss.bosscode == 3){
                            if( (cur_boss.miniboss_counter2 == 50+120 || cur_boss.miniboss_counter2 == 150+120 || cur_boss.miniboss_counter2 == 250+120) && cur_boss.bossfight ){
                                
                                spawn_miniboss_bullets(cur_boss , player.renderer , player.window,30);

                            }

                        }

                    cur_boss.display_miniboss( renderer );
                    
                    if(cur_boss.bossfight){
                        SDL_Rect dest;
                        dest.w = 800;
                        dest.h = 50;
                        dest.x = 112;
                        dest.y = 40;
                        SDL_RenderCopy(renderer , cur_boss.empty_health , NULL , &dest);

                        dest.w = 10*cur_boss.health;
                        dest.x += 90;
                        dest.h = 35;
                        dest.y += 10;
                        SDL_RenderCopy(renderer , cur_boss.health_segment , NULL , &dest);

                    }   

                    if( (player.rectangle.x + CAMX < cur_boss.wall_x2 && player.rectangle.x + CAMX > cur_boss.wall_x1) && (player.rectangle.y + CAMY < cur_boss.wall_y2 && player.rectangle.y + CAMY > cur_boss.wall_y1)){
                        active_boss_fight = cur_boss.bosscode;
                        break;
                    }
                }
                else{
                    cur_boss.deadcount++;
                    if(cur_boss.deadcount==1){
                        trigger_animation(enemy_dead_animation,cur_boss.x,cur_boss.y,96,78);
                        dead_boss++;
                    }
                    else if(cur_boss.deadcount ==30){
                        trigger_animation(enemy_dead_animation,cur_boss.x+64,cur_boss.y+96,96,78);
                    }
                    else if(cur_boss.deadcount == 60){
                        trigger_animation(enemy_dead_animation,cur_boss.x,cur_boss.y+192,96,78);
                    }
                    
                }
            }


      }



#endif