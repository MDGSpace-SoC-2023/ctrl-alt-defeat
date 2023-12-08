#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface* loadsurface ( string path );

bool init();

bool loadmedia();

void close();

bool quit = false;

SDL_Window* window=NULL;
SDL_Surface* surface=NULL;
SDL_Surface* test=NULL;


bool init(){

    bool initialized = true ;

    SDL_Init( SDL_INIT_EVERYTHING ); //initialize SDL

    window = SDL_CreateWindow( "Image loading" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 800 , 600 , SDL_WINDOW_SHOWN );

    surface = SDL_GetWindowSurface( window );//grabbing the surface contained by the window

    return initialized;
}

bool loadmedia(){
     
    bool load = true;

    test = SDL_LoadBMP( "sample.bmp" );
    
    if( test == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "sample.bmp", SDL_GetError() );
        load = false;
    }
    return load;

}

void close(){

    SDL_FreeSurface( test );
    test=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();

}

int main ( int argc , char * agrv[] ){

    
     bool quit = false;
     SDL_Event e;

     if(!init())
     {
        printf(" Window not initialized \n");
     }
     else
     {
        if(!loadmedia())
        {
            printf("media not loaded\n");
        }
        else
        {
        while(!quit)
        {
            
            if( SDL_PollEvent( &e ) != 0)
            {
                if( e.type == SDL_QUIT )quit=true;
            }

            SDL_BlitSurface( test , NULL , surface , NULL);//copy the image into the other surface
            SDL_UpdateWindowSurface( window );

        }
        }
     }
     
     close();
    
     

    return 0;

}