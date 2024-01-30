#ifndef BOSS_HPP
#define BOSS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include "objects.h"
using namespace std;


int bosscounter = 0;
int bosscounter2 = 0;

int changeboss = 0;
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
      int health = 620;
      SDL_Rect src, collider , dest;
      SDL_Texture* bullet_up = NULL;
      SDL_Texture* bullet_down = NULL;
      SDL_Texture* bullet_right = NULL;
      SDL_Texture* bullet_left = NULL;
      SDL_Texture* empty_health = NULL;
      SDL_Texture* health_segment = NULL;
      

      SDL_Texture* Boss_tileset = NULL;

      Boss( SDL_Renderer* renderer , int xn , int yn , int size){

            SDL_Surface* temp;
            temp = IMG_Load( "Assets/boss.png" );
            Boss_tileset = SDL_CreateTextureFromSurface( renderer , temp);
            temp = IMG_Load( "Assets/boss_bullets/bullet_up.png");;
            bullet_up = SDL_CreateTextureFromSurface( renderer , temp);
            temp = IMG_Load( "Assets/boss_bullets/bullet_down.png");;
            bullet_down = SDL_CreateTextureFromSurface( renderer , temp);
            temp = IMG_Load( "Assets/boss_bullets/bullet_right.png");;
            bullet_right = SDL_CreateTextureFromSurface( renderer , temp);
            temp = IMG_Load( "Assets/boss_bullets/bullet_left.png");;
            bullet_left = SDL_CreateTextureFromSurface( renderer , temp);
            temp = IMG_Load("Assets/empty_health.png");
            empty_health = SDL_CreateTextureFromSurface(renderer , temp);
            temp = IMG_Load("Assets/health_segment.png");
            health_segment = SDL_CreateTextureFromSurface(renderer , temp);            
            SDL_FreeSurface( temp);

            tilesize =  192;
            standing = {0,6};
            attack = {18,10};
            hit = {31, 5};
            dying = {37,14};
            cur_boss_animation = standing;
            columns = 7;
            cur_index = cur_boss_animation.first;
            speed = 8;

            src.w = 192;
            src.h = 192;
            dest.w = size;
            dest.h = size;
            collider.h = 250;
            collider.w = 250;
            x = xn;
            y = yn;

      }
      void teleport_miniboss( int xn , int yn , int wallx ){
          
               y = yn - 500;
               x = xn + rand()%(wallx - x);     
                  
      }

      void update_boss(SDL_Renderer* renderer , Sigma&player){

            src.x = ((cur_index)%columns)*tilesize;
            src.y = ((cur_index)/columns)*tilesize;
            collider.x = x + 500 - CAMX;
            collider.y = y + 500 - CAMY;

            dest.x = x - CAMX;
            dest.y = y - CAMY;

            SDL_RenderCopy(renderer,Boss_tileset,&src,&dest);
            bosscounter++;
            bosscounter2++;

            if(bosscounter>speed){
                  cur_index++;
                  bosscounter=0;
            }
            if( bosscounter2 > 420 ){
                  //   teleport_miniboss( player.rectangle.x + CAMX , player.rectangle.y + CAMY , 1540);
                    bosscounter2 = 0;
            }
            if( bosscounter2 == 20 || bosscounter2 == 80 || bosscounter2 == 160 || bosscounter2 == 220 ){
              projectile bullet1( collider.x + CAMX - 80 , collider.y  + CAMY   , 2 , renderer , player.window , 78 , 132, bullet_down);                     
              projectile bullet6( collider.x + CAMX + 80 , collider.y  + CAMY  , 2 , renderer , player.window , 78 , 132, bullet_down);                     
              projectile bullet2( collider.x + CAMX - 80 , collider.y + CAMY     , 1 , renderer , player.window , 78 , 132 , bullet_up);                     
              projectile bullet7( collider.x + CAMX + 80 , collider.y + CAMY     , 1 , renderer , player.window , 78 , 132 , bullet_up);                     
              projectile bullet3( collider.x + CAMX  , collider.y + CAMY - 80    , 4 , renderer , player.window , 78 , 132 , bullet_right);                     
              projectile bullet8( collider.x + CAMX  , collider.y + CAMY + 80    , 4 , renderer , player.window , 78 , 132 , bullet_right);                     
              projectile bullet4( collider.x + CAMX  , collider.y + CAMY - 80   , 3 , renderer , player.window , 78 , 132 , bullet_left);                     
              projectile bullet5( collider.x + CAMX  , collider.y + CAMY + 80  , 3 , renderer , player.window  , 78 , 132 , bullet_left);                     
              mainboss_bullets.push_back(bullet1);
              mainboss_bullets.push_back(bullet2);
              mainboss_bullets.push_back(bullet3);
              mainboss_bullets.push_back(bullet4);
              mainboss_bullets.push_back(bullet5);
              mainboss_bullets.push_back(bullet6);
              mainboss_bullets.push_back(bullet7);
              mainboss_bullets.push_back(bullet8);
            }

            if(cur_index>cur_boss_animation.first+cur_boss_animation.second-1) cur_index = cur_boss_animation.first;   

                        SDL_Rect dest2;
                        dest2.w = 800;
                        dest2.h = 50;
                        dest2.x = 112;
                        dest2.y = 40;
                        SDL_RenderCopy(renderer , empty_health , NULL , &dest2);

                        dest2.w = 1*health;
                        dest2.x += 90;
                        dest2.h = 35;
                        dest2.y += 10;
                        SDL_RenderCopy(renderer , health_segment , NULL , &dest2);  
            if(player.rectangle.x+CAMX>=x && player.rectangle.x+CAMX<= (x+800) && player.rectangle.y+CAMY>=(y+400) && player.rectangle.y+CAMY<= (y+800)){
                  cur_boss_animation = attack;
                  if(cur_index >= cur_boss_animation.first+cur_boss_animation.second-1 && bosscounter == speed -1){
                        player.health -= 2;
                        cur_boss_animation = standing;
                        cout<<player.health<<" ";
                  }
   
            }
            else cur_boss_animation = standing;
            if(cur_index>cur_boss_animation.first+cur_boss_animation.second-1) cur_index = cur_boss_animation.first;           

                        SDL_RenderCopy(renderer , health_segment , NULL , &dest2); 
                        
                                 if(health == 400){
                                       changeboss++;
                                 }
 
      }



};




void load_main_boss( SDL_Renderer* renderer , vector <Boss>& main_bosses){

         Boss main_boss( renderer , 600 , 150 + 256 , 800);
         main_bosses.push_back(main_boss);
}


#endif