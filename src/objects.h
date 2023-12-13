   // objects.h

#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
using namespace std;

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

enum playerdirn{
      UP,
      LEFT,
      DOWN,
      RIGHT,
};

enum boundary{
       UPPERB,
       LOWERB,
       LEFTB,
       RIGHTB,
       NOB,
};

keypress getinput( SDL_Event e )
{
           if( e.type = SDL_KEYDOWN )
           {
                 switch(e.key.keysym.sym)
                 {
                     case(SDLK_w):
                     return KEY_W;
       
                     case(SDLK_a):
                     return KEY_A;
              
                     case(SDLK_s):
                     return KEY_S;
                     
                     case(SDLK_d):
                     return KEY_D;
       
                     case(SDLK_SPACE):
                     return KEY_SPACE;
              
                     case(SDLK_e):
                     return KEY_E;
                     
                 }

           }
           return KEY_DEFAULT;
};

class texrect {
       
       public: 

       SDL_Rect rectangle;
       SDL_Texture* text;
       SDL_Renderer* renderer;
       SDL_Window* window;
       int speed;
       playerdirn direction;
       bool collision=false;

        texrect( )//default constructer
       {
           rectangle.x=0;
           rectangle.y=0;
           rectangle.h=0;
           rectangle.w=0;    
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
                    rectangle.y-=speed;
                    direction=UP;
             break;

             case(KEY_A):
                    rectangle.x-=speed;
                    direction=LEFT;
             break;

             case(KEY_S):
                    rectangle.y+=speed;
                    direction=DOWN;
             break;

             case(KEY_D):
                    rectangle.x+=speed;
                    direction=RIGHT;
             break;

           }            
       }

       void reverse_input( keypress key )
       {
           switch(key)
           {
             case(KEY_W):
                    rectangle.y+=speed;
                    direction=UP;
             break;

             case(KEY_A):
                    rectangle.x+=speed;
                    direction=LEFT;
             break;

             case(KEY_S):
                    rectangle.y-=speed;
                    direction=DOWN;
             break;

             case(KEY_D):
                    rectangle.x-=speed;
                    direction=RIGHT;
             break;
                         
           }
       }
       
       boundary which_boundary()
       {
             if(rectangle.x<=0)return LEFTB;
             else if(rectangle.x>= WIDTH- rectangle.w/2)return RIGHTB;
             else if(rectangle.y<=0)return UPPERB;
             else if(rectangle.y >= HEIGHT - rectangle.h/2)return LOWERB;
             else return NOB;        
       }

       bool is_out_of_boundary()
       {

             if( which_boundary() == NOB )return false;
             else return true;
       }

};

bool iscolliding( texrect a , texrect b )
{          
          SDL_Rect rect_a = a.getrect();
          SDL_Rect rect_b = b.getrect();
        
          if( SDL_HasIntersection ( &rect_a , &rect_b ) ) return true ;
          else return false;
}

class projectile:public texrect
{
     public:
     int velx;
     int vely;
     
     projectile( Sigma player )
     {
       velx=0;
       vely=0;
       rectangle.w=10;
       rectangle.h=10;
       rectangle.x=player.rectangle.x;
       rectangle.y=player.rectangle.y;
       
         switch( player.direction ){
                
                case(UP):
                vely= -10;
                case(DOWN):
                vely= 10;
                case(LEFT):
                velx= -10;
                case(RIGHT):
                velx= 10;
         } 
         loadtexture("Assets/ball.png");
     }
     

     void update_projectile ()
     {
       rectangle.x+=velx;
       rectangle.y+=vely;
     }





};

class Sigma:public texrect
{
      public:
      
      
      Sigma( SDL_Renderer* rend , SDL_Window* wind)
      { 
        direction=UP;  
        set_dimension( WIDTH/2 , HEIGHT/2 , 60 , 60 , 6 , rend , wind );
        loadtexture("Assets/character.png");
      }

      playerdirn get_player_direction()
      {
            return direction;
      }

      
      
};

void spawn_bullet( keypress gkey , vector <projectile> Bullets , Sigma player )
      {    
                   if(gkey==KEY_SPACE)
                   {        
                            projectile bullet( player );
                            Bullets.push_back( bullet ) ;
                   }
      }



#endif

