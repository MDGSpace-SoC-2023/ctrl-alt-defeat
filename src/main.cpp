#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

int WIDTH  =1280;
int HEIGHT =720 ;
SDL_Window* window = NULL;
SDL_Renderer* renderer= NULL;

enum keypress
{
     KEY_DEFAULT,
     KEY_W,
     KEY_A,
     KEY_S,
     KEY_D,
     KEY_SPACE,


}
void init()
{       
        //initialize all subsystems
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();

}

class texrect{
       
       public: 
       int x,y,h,w;
       
       texrect()//default constructer
       {
           x=0;
           y=0;
           h=0;
           w=0;       
       }

       texrect( int x , int y , int height , int width )//paremeterised constructor
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
       }

       
       void loadtexture( std::string path)//loading texture from a path
       {

        SDL_Surface* temp=IMG_Load( path.c_str() );
        text = SDL_CreateTextureFromSurface( renderer , temp );
        SDL_FreeSurface(temp);
        SDL_RenderCopy(renderer , text , NULL , &rectangle );

       }
       
       void update() // updating position of rectangle and updating to renderer
       {      
               rectangle.x=x;
               rectangle.y=y;
               SDL_RenderCopy(renderer , text , NULL , &rectangle );
       }
       
       private :

       SDL_Rect rectangle;
       SDL_Texture* text;
       
};

class Sigma:public texrect
{
      
      
}

void update_display();

void show_display()
{
        SDL_RenderPresent( renderer );
}

keypress input( SDL_Event e )
{
           if( e.type = SDL_KEYDOWN )
           {
                 switch(e.key.keysym.sym)
                 {
                     


                 }

           }
}


int main ( int argc , char* argv[] )
{
        
        init();
        
        bool quit=false;
        SDL_Event e;
         
        while(!quit) //gameloop
        {
        
        while(SDL_PollEvent(&e) )
        {
                   if( e.type == SDL_QUIT ) quit = true;

                   else if ( e.type == SDL_KEYDOWN )
                   {
                        input(e);
                   }
        }   
                  
                   update_display();
                   show_display();

        } 


        return 0;

}