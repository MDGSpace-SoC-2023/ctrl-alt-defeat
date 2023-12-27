#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "objects.h"
#include "level.hpp"

SDL_Window* window = NULL;
SDL_Renderer* renderer= NULL;
SDL_Renderer* present = SDL_CreateRenderer( window , -1 , 0);

//resources
vector <projectile> Bullets;
vector <level> levels;
vector < vector <int> > colliders;
vector < vector <Enemy>> enemies; 


void init()
{       
      //initialize all subsystems
      SDL_Init(SDL_INIT_EVERYTHING);
      IMG_Init(IMG_INIT_PNG);
      TTF_Init();
      window= SDL_CreateWindow( "Sigma_Loop" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , SDL_WINDOW_SHOWN);
      renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED );
}


void clear_display()
{
      SDL_SetRenderDrawColor(renderer, 25 , 25 , 25 , SDL_ALPHA_OPAQUE );
      SDL_RenderClear(renderer);
}

void show_display()
{
      SDL_RenderPresent(renderer);

}

void load_levels_and_colliders( vector <level> &levels , vector < vector <int> > &colliders , vector <vector <Enemy> > &enemies )
{

        level temp;
        load_main_menu ( renderer , temp );
        levels.push_back(temp);
        temp.destory_level();
        load_level_1 (renderer , temp);
        levels.push_back(temp);

        colliders.push_back(main_menu_collider);
        colliders.push_back(level_1_collider);
        
        load_enemies(enemies , renderer , window );
}


int main ( int argc , char* argv[] )
{
      init();
        
        bool quit=false;
        SDL_Event e;
        keypress gkey;

        Sigma player( renderer , window );
        
        load_levels_and_colliders( levels , colliders , enemies);

        
        level &cur_level = levels[0];
        vector <int> &cur_collider = colliders[0];
        int cur_level_index = 0;
        vector <Enemy> &cur_enemies = enemies[0];
         
      while(!quit) //gameloop
      {
        
            while(SDL_PollEvent(&e) )
            {
                  if( e.type == SDL_QUIT ) quit = true;             
                                                                                  
                  else if ( e.type == SDL_KEYDOWN )
                  {     
                         
                         gkey= getinput(e);  //convert SDL_input to keypress type input
                         player.process_input(gkey);
                         if(gkey == KEY_SPACE)
                              spawn_bullet(Bullets , player);
                        
                        process_cam_input(gkey, player);
                         level_transition(levels , colliders , enemies ,cur_level_index , cur_level , cur_collider ,cur_enemies ,  player);
                          
                           if(check_collision_for_level(cur_level , player , cur_collider)){
                              player.reverse_input(gkey);
                              reverse_cam_input(gkey);
                           }  
                            else if( player.dashing)
                            {
                               if(check_collision_for_level( cur_level , player , cur_collider))
                               {
                                     player.dashing = false;
                                     player.reverse_dash();
                               }
                            }
                        
    
                   }
            }
                   
                 if( player.dashing)
                            {
                               if(check_collision_for_level( cur_level , player , cur_collider))
                               {
                                     player.dashing = false;
                                     player.reverse_dash();
                               }
                            }
            clear_display(); //clear screen to black or level texture
            limit_cam();
            cur_level.draw_level(renderer);
              //     cur_level.draw_layer(renderer , cur_level.tiles_layer2);
           

              for( int i=0 ; i<Bullets.size() ; ++i ){ //bullets loop
                   
                   if(check_collision_for_level(cur_level , Bullets[i] , cur_collider))Bullets.erase(Bullets.begin() + i);
                   Bullets[i].update_projectile();
                   Bullets[i].update();
                  //  if( iscolliding(obstacle1 , Bullets[i]) || Bullets[i].is_out_of_boundary() ) Bullets.erase( Bullets.begin()+i);
             
             }

             update_enemies( cur_enemies , player );
           update_enemy_bullets( cur_level , cur_collider);

             player.update_sigma(); // update sigma pos and render sigma to screen
             show_display();  //present renderer
             SDL_Delay(16.66);
      } 
      


      return 0;

}