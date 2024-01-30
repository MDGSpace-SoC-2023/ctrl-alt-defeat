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
vector < miniboss > minibosses;
vector < Boss > main_boss;

// to do list
// sounds : 
// player shooting sound 
// minibossdying effect


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

        level temp4;
        load_level_3_A(renderer , temp4);
        levels.push_back(temp4);
        temp4.destory_level();
        
        level temp5;
        load_level_3_B(renderer , temp5);
        levels.push_back(temp5);
        temp5.destory_level();
        

        colliders.push_back(main_menu_collider);
        colliders.push_back(level_1_collider);
        colliders.push_back(level_2_collider);
        colliders.push_back(level_3_A_collider);
        colliders.push_back(level_3_B_collider);
        load_enemies(enemies , renderer , window );
        load_powerups( powerups , renderer , window  );
        load_animations( renderer);
        load_minibosses( minibosses , renderer);
        load_main_boss(renderer , main_boss);
        levels[0].enemy_count = enemies[0].size();
        levels[1].enemy_count = enemies[1].size();
        levels[2].enemy_count = 0;
        levels[3].enemy_count = enemies[3].size();
        levels[4].enemy_count = enemies[4].size();
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
        
        level cur_level = levels[2];
        vector <int> cur_collider = colliders[2];
        int cur_level_index = 2;
        vector <Enemy> cur_enemies = enemies[2];
        vector <powerup> cur_powerup = powerups[2];
        Music cur_track = cur_level.level_bgm;
        machinegun machine_gun(renderer,window);
        machine_gun.spawn_machinegun(960,1084);
      //   player.rectangle.x = 100;
        player.bullet_damage = 100;

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

                                        if(bulletcounter >= guncounter )
                                      {
                                          spawn_bullet(Bullets , player, 0 , player_bullet_texture);
                                          player.gunshot_sound.Play_sound(0);
                                          bulletcounter = 0;
                                      }

                                    }

                        }
                  }
            }
            
            manage_music(cur_track);            
            if( !gameisover )
            {
            player.process_input(player);
            process_cam_input( player );
            }

            level_changing = false;

            if(check_collision_for_level(cur_level , player , cur_collider, 0, cur_level_index)){
                              player.reverse_input(gkey,player);
                              reverse_cam_input(gkey , player);
                              if( player.dashing){
                                      player.dashing = false;
                                      player.reverse_dash();
                              }
            }  

            
            level_transition(levels , colliders , enemies ,cur_level_index , cur_level , cur_collider ,cur_enemies ,  player , powerups , cur_powerup, renderer , cur_track , minibosses);
      
                 if( player.dashing)
                            {
                               if(check_collision_for_level( cur_level , player , cur_collider, 0 , cur_level_index))
                               {
                                     player.dashing = false;
                                     player.reverse_dash();
                               }
                            }

                            cout << level_changing << endl;

            clear_display(); //clear screen to black or level texture
            
            cur_level.draw_level(renderer ,cur_level_index);
          //    cur_level.draw_layer(renderer , cur_level.tiles_layer3 , cur_level_index);




          // temp code 
          if( gkey == KEY_I){
              
                   int x1 =(player.rectangle.x + CAMX)/64;
                   int y1 = (player.rectangle.y + CAMY)/64;
                   int ind = x1 + y1*cur_level.columns;

                   cout << player.rectangle.x + CAMX << " " << player.rectangle.y + CAMY << " "<< cur_collider[ind] << endl;
                    
                
          }

                      

             update_enemies( cur_enemies , player );
             update_bullets( cur_enemies , cur_collider , cur_level , player , minibosses , cur_level_index , main_boss[0]);
             update_powerup( renderer , cur_powerup , player );
             update_animations( renderer);
             if( cur_level_index == 2)update_minibosses( minibosses , renderer , player);
             if( cur_level_index == 3){
                  main_boss[0].update_boss(renderer, player);
                  if(bombcounter>300){
                        bomb temp(renderer);
                        active_bombs.push_back(temp);

                        bomb temp1(renderer);
                        active_bombs.push_back(temp1);

                        bomb temp2(renderer);
                        active_bombs.push_back(temp2);

                        bomb temp3(renderer);
                        active_bombs.push_back(temp3);

                        bomb temp4(renderer);
                        active_bombs.push_back(temp4);

                        bomb temp5(renderer);
                        active_bombs.push_back(temp5);

                        bomb temp6(renderer);
                        active_bombs.push_back(temp6);

                        bomb temp7(renderer);
                        active_bombs.push_back(temp7);

                        bomb temp8(renderer);
                        active_bombs.push_back(temp8);

                        bomb temp9(renderer);
                        active_bombs.push_back(temp9);

                        bomb temp10(renderer);
                        active_bombs.push_back(temp10);

                        bomb temp11(renderer);
                        active_bombs.push_back(temp11);

                        bomb temp12(renderer);
                        active_bombs.push_back(temp12);

                        bombcounter = 0;
                        
                  }
                  int done = 0;
                  for(int i = 0 ; i<active_bombs.size(); i++){
                        done = 0;
                        active_bombs[i].update(renderer,player,done);
                        if(done) {
                              active_bombs.erase(active_bombs.begin()+i);
                              i--;
                        }
                  }
                  bombcounter++;
             }

             else if(cur_level_index == 4) machine_gun.update(renderer,player);
             player.update_sigma(); // update sigma pos and render sigma to screen
             //limit_cam(player);
             if( cur_level.tiles_layer4.size()){
                cur_level.draw_layer(renderer , cur_level.tiles_layer4 , cur_level_index);
             }
             trigger_font(cur_level, renderer); // trigger font on level change
             check_game_over(player , cur_level_index , gkey , renderer );

             show_display();  //present renderer
             SDL_Delay(16.66);


      }
      


      return 0;

}