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
vector <projectile> Bullets;




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
        SDL_RenderPresent( renderer );
}



int main ( int argc , char* argv[] )
{
        init();
        
        bool quit=false;
        SDL_Event e;
        keypress gkey;

        Sigma player( renderer , window );
        

        level main_menu;
        load_main_menu( renderer , main_menu );

        
         
        while(!quit) //gameloop
        {
        
             while(SDL_PollEvent(&e) )
                   {
                     if( e.type == SDL_QUIT ) quit = true;             
                                                                                  
                     else if ( e.type == SDL_KEYDOWN )
                   {     
                         
                         gkey= getinput(e);  //convert SDL_input to keypress type input
                         player.process_input(gkey);
                         spawn_bullet(gkey , Bullets , player);
                  
                          
                           if(check_collision_for_level(main_menu , player , main_menu_collider))
                                {
                                player.reverse_input(gkey);
                                }    
                           else if( player.is_out_of_boundary() )
                           {
                                player.reverse_input(gkey);
                           }     
                   }
                   }
              
             clear_display(); //clear screen to black or level texture

                main_menu.draw_level(renderer);

           

             for( int i=0 ; i<Bullets.size() ; ++i ){ //bullets loop
                   
                   
                   Bullets[i].update_projectile();
                   Bullets[i].update();
                  //  if( iscolliding(obstacle1 , Bullets[i]) || Bullets[i].is_out_of_boundary() ) Bullets.erase( Bullets.begin()+i);
             
             }

             player.update(); // update sigma pos and render sigma to screen
             show_display();  //present renderer
             SDL_Delay(16.66);
        } 


        return 0;

}