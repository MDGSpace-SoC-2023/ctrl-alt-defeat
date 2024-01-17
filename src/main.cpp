#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include "objects.h"
#include "level.hpp"
#include "Music.hpp"
#include "Keyboard_handler.hpp"


SDL_Window* window = NULL;
SDL_Renderer* renderer= NULL;
SDL_Renderer* present = SDL_CreateRenderer( window , -1 , 0);

//resources
vector <level> levels;
vector < vector <int> > colliders;
vector < vector <Enemy>> enemies; 
vector < vector <powerup> > powerups;


void init()
{       
      //initialize all subsystems
      SDL_Init(SDL_INIT_EVERYTHING);
      IMG_Init(IMG_INIT_PNG);
      TTF_Init();
      Mix_Init(MIX_INIT_MP3);
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

void load_levels( vector <level> &levels , vector < vector <int> > &colliders , vector <vector <Enemy> > &enemies , vector <vector <powerup> > &powerups )
{

        level temp;
        load_main_menu ( renderer , temp );
        levels.push_back(temp);
        temp.destory_level();

        level temp2;
        load_level_1 (renderer , temp2);
        levels.push_back(temp2);
        temp2.destory_level();

        level temp3;
        load_level_2( renderer , temp3);
        levels.push_back(temp3);
        temp3.destory_level();

        colliders.push_back(main_menu_collider);
        colliders.push_back(level_1_collider);
        colliders.push_back(level_2_collider);
        
        load_enemies(enemies , renderer , window );
        load_powerups( powerups , renderer , window  );
        load_animations( renderer);
}


int main ( int argc , char* argv[] )
{
      
        init();
        
        bool quit=false;
        SDL_Event e;
        keypress gkey;

        Sigma player( renderer , window );
        
        load_levels( levels , colliders , enemies , powerups );
        load_animations( renderer);
        
        level cur_level = levels[0];
        vector <int> cur_collider = colliders[0];
        int cur_level_index = 0;
        vector <Enemy> cur_enemies = enemies[0];
        vector <powerup> cur_powerup = powerups[0];
        Music cur_track = cur_level.level_bgm;

      while(!quit) //gameloop
      {      

            while( SDL_PollEvent(&e) )
            {
                  if( e.type == SDL_QUIT ) quit = true;   

                  else{

                        handle_input(e);
                        

                        if( e.type == SDL_KEYDOWN){
                                gkey = getinput(e);
                                player.process_input_direction( gkey );

                                    if(gkey == KEY_SPACE){

                                        if(bulletcounter >= 25 )
                                      {
                                          spawn_bullet(Bullets , player, 0);
                                          player.gunshot_sound.Play_sound(0);
                                          bulletcounter = 0;
                                      }
                                    }

                        }
                  }
            }
            
            if( !cur_track.isplaying() ){
                    cur_track.fadein_music(-1 , 2000);
            }
            
            if( !gameisover )
            {
            player.process_input(player);
            process_cam_input( player );
            }

            if(check_collision_for_level(cur_level , player , cur_collider, 0)){
                              player.reverse_input(gkey,player);
                              reverse_cam_input(gkey , player);
                              if( player.dashing){
                                      player.dashing = false;
                                      player.reverse_dash();
                              }
            }  

            
            level_transition(levels , colliders , enemies ,cur_level_index , cur_level , cur_collider ,cur_enemies ,  player , powerups , cur_powerup, renderer , cur_track);
      
                 if( player.dashing)
                            {
                               if(check_collision_for_level( cur_level , player , cur_collider, 0))
                               {
                                     player.dashing = false;
                                     player.reverse_dash();
                               }
                            }

            clear_display(); //clear screen to black or level texture
            
            cur_level.draw_level(renderer);
              //     cur_level.draw_layer(renderer , cur_level.tiles_layer2);
                      

             update_enemies( cur_enemies , player );
             update_bullets( cur_enemies , cur_collider , cur_level , player );
             update_powerup( renderer , cur_powerup , player );
             update_animations( renderer);

             player.update_sigma(); // update sigma pos and render sigma to screen
             //limit_cam(player);
             trigger_font(cur_level, renderer); // trigger font on level change
             check_game_over(player , cur_level_index , gkey , renderer );

             show_display();  //present renderer
             SDL_Delay(16.66);


      }
      


      return 0;

}