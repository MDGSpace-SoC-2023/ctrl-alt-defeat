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
     KEY_E,
};


void init()
{       
        //initialize all subsystems
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        window= SDL_CreateWindow( "Sigma_Loop" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED );
}

class texrect{
       
       public: 
       int x,y,h,w;
       int speed;
       
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

       void get_dimension( int x , int y , int height , int width)
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
       }
       
         void get_dimension( int x , int y , int height , int width, int sped)
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
        speed=sped;
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
       
};

class Sigma:public texrect
{
      public:

      Sigma()
      {
        get_dimension( WIDTH/2 , HEIGHT/2 , 60 , 60 , 4 );
        loadtexture("Assets/character.png");
      }
  
      void update_sigma()
      { 
        update();
        loadtexture("Assets/character.png");   
      }
            
      
};

void update_display()
{
            SDL_SetRenderDrawColor(renderer, 0 , 0 ,0,SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
}

void show_display()
{
        SDL_RenderPresent( renderer );
}

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
                 }

           }
           return KEY_DEFAULT;
}


int main ( int argc , char* argv[] )
{
        
        init();
        
        bool quit=false;
        SDL_Event e;
        keypress gkey;

        Sigma player;
        
         
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