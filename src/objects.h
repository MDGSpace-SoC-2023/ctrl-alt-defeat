   // objects.h

#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
using namespace std;

int WIDTH  =1024;
int HEIGHT =960;

int COUNTER = 0;
int framecount = 0;
int dashcounter = 0;


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
       
       void update() // updating to renderer
       {      
              SDL_RenderCopy(renderer , text , NULL , &rectangle );
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
             else 
             {
              return true;
             } 
       }
       
       
       

};

bool iscolliding( texrect a , texrect b )
{          
          SDL_Rect rect_a = a.rectangle;
          SDL_Rect rect_b = b.rectangle;
        
          if( SDL_HasIntersection ( &rect_a , &rect_b ) ) return true ;
          else return false;
}



class Sigma:public texrect
{
      public:
      bool dashing = false;

      Sigma( SDL_Renderer* rend , SDL_Window* wind)
      { 
        direction=UP;  
        set_dimension( 512 , 300 , 32 , 32 , 1 , rend , wind );
        loadtexture("Assets/chibi_tileset.png");
      }      
      
         void update_sigma() // updating to renderer
       {      
              int frame = (framecount/3) % 3;
              SDL_Rect src;
              src.w = 32;
              src.h = 32;

              switch(direction)
              {
                 case(DOWN):
                 src.x = frame * 32;
                 src.y = 0;
                 break;
                 case(RIGHT):
                 src.x = frame * 32;
                 src.y = 32;
                 break;
                 case(LEFT):
                 src.x = frame * 32;
                 src.y = 64;
                 break;
                 case(UP):
                 src.x = frame * 32;
                 src.y = 96;
                 break;
              }

            if(dashing)
            {
              switch(direction)
              {
                 case(DOWN):
                 rectangle.y += 1;
                 break;
                 case(RIGHT):
                 rectangle.x += 1;
                 break;
                 case(LEFT):
                 rectangle.x -= 1;
                 break;
                 case(UP):
                 rectangle.y -= 1;
                 break;
              } 

              dashcounter++;
              if(dashcounter==7){
                     dashing = false;
                     dashcounter = 0;
              }

            }  
              SDL_RenderCopy(renderer , text , &src , &rectangle );
       }
       void process_input( keypress key )
       {
           framecount++;
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
             case(KEY_E):
                    dashing = true;
                    break;

           }            
       }

       void reverse_dash()
       {
               switch(direction)
              {
                 case(DOWN):
                 rectangle.y -= 1;
                 break;
                 case(RIGHT):
                 rectangle.x -= 1;
                 break;
                 case(LEFT):
                 rectangle.x += 1;
                 break;
                 case(UP):
                 rectangle.y += 1;
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
};

class projectile:public texrect
{
       public:
       int velx;
       int vely;
     
       projectile( texrect player )
       {
              velx=0;
              vely=0;
              rectangle.w=20;
              rectangle.h=20;
              rectangle.x=player.rectangle.x;
              rectangle.y=player.rectangle.y;
              renderer = player.renderer;
              window = player.window;
       
              switch( player.direction ){
                
              case(UP):
                     vely= -5;
                     velx=0;
                     break;
              case(DOWN):
                     vely= 5;
                     velx=0;
                     break;
              case(LEFT):
                     velx= -5;
                     vely=0;
                     break;
              case(RIGHT):
                     velx= 5;
                     vely=0;
                     break;
              } 
              loadtexture("Assets/ball.png");
       }
     

       void update_projectile ()
       {
              rectangle.x+=velx;
              rectangle.y+=vely;
       }
};

void spawn_bullet( keypress gkey , vector <projectile> &Bullets , Sigma player )
      {    
              if(gkey==KEY_SPACE)
              {        
                     projectile bullet( player );
                     Bullets.push_back( bullet );
              }
      }
      

vector <projectile> eBullets;
void spawn_bullet(vector <projectile> &Bullets , texrect player )
{       
       projectile bullet( player );
       Bullets.push_back( bullet );
}


class Enemy:public texrect{
       public:
              int x1;
              int y1;
              int x2;
              int y2;
              Enemy(int height,int width,int xpt1,int ypt1, int xpt2, int ypt2, SDL_Renderer* ren, SDL_Window* win){
                     rectangle.h = height;
                     rectangle.w = width;
                     x1 = xpt1;
                     x2 = xpt2;
                     y1 = ypt1;
                     y2 = ypt2;
                     renderer = ren;
                     window = win;
                     speed = 2;
                     rectangle.x = (x1+x2)/2;
                     rectangle.y = (y1+y2)/2;
                     loadtexture("Assets/enemy.png");
              }

              void update_enemy_position(){
                     if((rectangle.x==x1 && rectangle.y == y1) || (rectangle.x==x2 && rectangle.y == y2)) speed = -speed;
                     if(x1==x2){
                            rectangle.y += speed;
                            if(speed>0) direction = DOWN;
                            else direction = UP;
                     }
                     else{
                            rectangle.x +=speed;
                            if(speed>0) direction = RIGHT;
                            else direction = LEFT;
                     }
                      
                     COUNTER++;
              }


};

void update_enemy(Sigma& player,Enemy& enmy){
       
       if(iscolliding(enmy,player)){//killing player on collision with enemy
              SDL_DestroyTexture(player.text);
              player.text = NULL;
       }

       for(int i=0 ; i<eBullets.size() ; ++i){
              eBullets[i].update_projectile();
              eBullets[i].update();
              
              if(iscolliding(player,eBullets[i])){
                     eBullets.erase(eBullets.begin()+i);
                     SDL_DestroyTexture(player.text);
                     player.text = NULL;
              }
              //else if( iscolliding(obstacle1 , eBullets[i]) || eBullets[i].is_out_of_boundary() ) eBullets.erase( eBullets.begin()+i);
       }

       enmy.update_enemy_position();
       if(COUNTER==110) spawn_bullet(eBullets,enmy);
       else if(COUNTER==130){
              spawn_bullet(eBullets,enmy);
              COUNTER = 0;
       } 

       enmy.update();

}

#endif
