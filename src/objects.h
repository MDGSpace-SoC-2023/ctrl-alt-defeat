   // objects.h

#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

int WIDTH  =1280;
int HEIGHT =720 ;

enum keypress
{
     KEY_DEFAULT,
     KEY_W,
     KEY_A,
     KEY_S,
     KEY_D,
     KEY_SPACE,
     KEY_E,
};


keypress getinput( SDL_Event e )
{
           if( e.type = SDL_KEYDOWN )
           {
                 switch(e.key.keysym.sym)
                 {
                     case(SDLK_w):
                     return KEY_W;
                     break;
                     case(SDLK_a):
                     return KEY_A;
                     break;
                     case(SDLK_s):
                     return KEY_S;
                     break;
                     case(SDLK_d):
                     return KEY_D;
                     break;
                     case(SDLK_SPACE):
                     return KEY_SPACE;
                     break;
                     case(SDLK_e):
                     return KEY_E;
                     break;
                 }

           }
           return KEY_DEFAULT;
}

class texrect{
       
       public: 
       int x,y,h,w;
       int speed;
        texrect( )//default constructer
       {
           x=0;
           y=0;
           h=0;
           w=0;    
           speed=0;   
       }

       texrect( int x , int y , int height , int width ,SDL_Renderer* rend , SDL_Window* wind )//paremeterised constructor
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
         window=wind;
         renderer=rend;
       }

       void set_dimension( int x , int y , int height , int width)
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
       }

        void set_dimension( int x , int y , int height , int width , SDL_Renderer* rend , SDL_Window* wind)
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
        window=wind;
        renderer=rend;
       }
       
         void set_dimension( int x , int y , int height , int width, int sped)
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
        speed=sped;
       }

        void set_dimension( int x , int y , int height , int width, int sped, SDL_Renderer* rend , SDL_Window* wind)
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
        speed=sped;
        window=wind;
        renderer=rend;
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

       SDL_Rect getrect()
       {
        return rectangle;
       }
       
       void process_input( keypress key )
       {
           switch(key)
           {
             case(KEY_W):
                    y-=speed;
             break;

             case(KEY_A):
                    x-=speed;
             break;

             case(KEY_S):
                    y+=speed;
             break;

             case(KEY_D):
                    x+=speed;
             break;
                         
           }
       }


       private :

       SDL_Rect rectangle;
       SDL_Texture* text;
       SDL_Renderer* renderer;
       SDL_Window* window;
};


class Sigma:public texrect
{
      public:

      Sigma( SDL_Renderer* rend , SDL_Window* wind)
      { 
        set_dimension( WIDTH/2 , HEIGHT/2 , 60 , 60 , 4 , rend , wind );
        loadtexture("Assets/character.png");
      }
  
      void update_sigma()
      { 
        update();
        loadtexture("Assets/character.png");   
      }
            
      
};

#endif

