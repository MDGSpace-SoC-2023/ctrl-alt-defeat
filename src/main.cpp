#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "objects.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer= NULL;


void init()
{       
        //initialize all subsystems
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        window= SDL_CreateWindow( "Sigma_Loop" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED );
}


void update_display()
{
            SDL_SetRenderDrawColor(renderer, 25 , 25 , 25 , SDL_ALPHA_OPAQUE );
            SDL_RenderClear(renderer);
}

void show_display()
{
        SDL_RenderPresent( renderer );
}

bool iscolliding( SDL_Rect a , SDL_Rect b )
{
          if(SDL_HasIntersection( &a , &b ))return true;
          else return false;
}



int main ( int argc , char* argv[] )
{
        
        init();
        
        bool quit=false;
        SDL_Event e;
        keypress gkey;

        Sigma player( renderer , window );
        texrect obstacle1( 50 , 50 , 150 , 50 , renderer , window ); 
        
         
        while(!quit) //gameloop
        {
        
             while(SDL_PollEvent(&e) )
                   {
                     if( e.type == SDL_QUIT ) quit = true;

                     else if ( e.type == SDL_KEYDOWN )
                   {     
                         gkey= getinput(e);  //convert SDL_input to keypress type input
                         player.process_input(gkey);


                          update_display(); //clear screen to black or level texture
                          player.update_sigma(); // update sigma pos and render sigma to screen
                          show_display();  //present renderer

                   }   
                   }

             update_display(); //clear screen to black or level texture
             player.update_sigma(); // update sigma pos and render sigma to screen
             show_display();  //present renderer

        } 


        return 0;

}