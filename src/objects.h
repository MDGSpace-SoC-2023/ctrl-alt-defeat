   // objects.h

#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

using namespace std;

int CAMX = 0;
int CAMY = 0;

int WIDTH  =1024;
int HEIGHT =960;

int ECOUNTER = 0;
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
     KEY_I,
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

                     case(SDLK_i):
                     return KEY_I;
                     
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
       SDL_Rect srectangle;

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
              srectangle.h = height;
              srectangle.w = width;
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
           srectangle.x = rectangle.x - CAMX;
           srectangle.y = rectangle.y - CAMY;   
              SDL_RenderCopy(renderer , text , NULL , &srectangle );
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

bool iscolliding( texrect &a , texrect &b )
{          
          SDL_Rect &rect_a = a.rectangle;
          SDL_Rect &rect_b = b.rectangle;
        
          if( SDL_HasIntersection ( &rect_a , &rect_b ) ) return true ;
          else return false;
}





class Sigma:public texrect
{
      public:
      bool dashing = false;
      int health;
      int bullet_damage = 1;

      SDL_Texture* heart=NULL;

      Sigma( SDL_Renderer* rend , SDL_Window* wind)
      { 
        direction=UP;  
        set_dimension( 512 , 400 , 64 , 64 , 1 , rend , wind );
        loadtexture("Assets/chibi_tileset.png");

        health = 10;
        SDL_Surface* temp = IMG_Load( "Assets/heart.png" );
        heart = SDL_CreateTextureFromSurface(renderer , temp);
        SDL_FreeSurface(temp);

      }     

      void draw_hearts()
      {
         
         for( int i=1 ; i<=health ; ++i){
               SDL_Rect dest;
               dest.w = 16;
               dest.h = 16;
               dest.y = 10;
               dest.x = 10 + i*20;

               SDL_RenderCopy(renderer , heart , NULL , &dest);  
               
         }

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
                 rectangle.y += 5;
                 break;
                 case(RIGHT):
                 rectangle.x += 5;
                 break;
                 case(LEFT):
                 rectangle.x -= 5;
                 break;
                 case(UP):
                 rectangle.y -= 5;
                 break;
              } 

              dashcounter++;
              if(dashcounter==20){
                     dashing = false;
                     dashcounter = 0;
              }

            }  

              draw_hearts();
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
     
       projectile( texrect player , int code)
       {
              velx=0;
              vely=0;
              srectangle.w=20;
              srectangle.h=20;
              rectangle.x=player.rectangle.x + player.rectangle.w/2 + CAMX;
              rectangle.y=player.rectangle.y + player.rectangle.h/2 + CAMY;
              srectangle.x = rectangle.x - CAMX  ;
              srectangle.y = rectangle.y  - CAMY ;

              if(code == 1){
                       
                     rectangle.x=player.rectangle.x + player.rectangle.w/2;
                     rectangle.y=player.rectangle.y + player.rectangle.h/2;
                     srectangle.x = rectangle.x - CAMX ;
                     srectangle.y = rectangle.y - CAMY ;
                       
              }
               
              renderer = player.renderer;
              window = player.window;
       
              switch( player.direction ){
                
              case(UP):
                     vely= -4;
                     velx=0;
                     break;
              case(DOWN):
                     vely= 4;
                     velx=0;
                     break;
              case(LEFT):
                     velx= -4;
                     vely=0;
                     break;
              case(RIGHT):
                     velx= 4;
                     vely=0;
                     break;
              } 
              loadtexture("Assets/heart.png");
       }
     

       void update_projectile ()
       {
              rectangle.x+=velx;
              rectangle.y+=vely;
              
       }
};

vector <projectile> eBullets;
void spawn_bullet(vector <projectile> &Bullets , texrect enemy , int code )
{       
       projectile bullet( enemy ,code);
       Bullets.push_back( bullet );
}




class Enemy:public texrect{
       public:
              int x1;
              int y1;
              int x2;
              int y2;
              int ehealth=3;
              int mode = 1;
              //1-same direction
              //2-up down enmy shoots right, right left enmy shoots up
              //3-opposite
              
              Enemy(int height,int width,int xpt1,int ypt1, int xpt2, int ypt2,int MODE, SDL_Renderer* ren, SDL_Window* win){
                     srectangle.h = height;
                     srectangle.w = width;
                     x1 = xpt1;
                     x2 = xpt2;
                     y1 = ypt1;
                     y2 = ypt2;
                     mode = MODE;
                     renderer = ren;
                     window = win;
                     speed = 1;
                     rectangle.x = (x1+x2)/2;
                     rectangle.y = (y1+y2)/2;
                     srectangle.x = rectangle.x - CAMX;
                     srectangle.y = rectangle.y - CAMY;
                     loadtexture("Assets/enemy.png");
              }

              void change( int x , int y , int xi , int yi,int MODE) //this is to make it easier to set enemies on the map
              {
                     x1=x;
                     y1=y;
                     x2=xi;
                     y2=yi;
                     mode = MODE;
                     rectangle.x = (x1+x2)/2;
                     rectangle.y = (y1+y2)/2;
                     srectangle.x = rectangle.x - CAMX;
                     srectangle.y = rectangle.y - CAMY;
              }

              void update_enemy_position(){

                     
                     if((rectangle.x==x1 && rectangle.y == y1) || (rectangle.x==x2 && rectangle.y == y2)) speed = -speed;


                     if(x1==x2){
                            rectangle.y += speed;
                            srectangle.y = rectangle.y - CAMY;
                            if(speed>0) direction = DOWN;
                            else direction = UP;
                     }
                     else{
                            rectangle.x +=speed;
                            srectangle.x = rectangle.x - CAMX;
                            if(speed>0) direction = RIGHT;
                            else direction = LEFT;
                     }
                      
              }


};

void spawn_enemy_bullets(vector <projectile> &Bullets,Enemy enmy){
       switch(enmy.mode){
              case(3) : 
                     if(enmy.direction==UP || enmy.direction==DOWN) enmy.direction=LEFT;
                     else enmy.direction=DOWN;
                     spawn_bullet(Bullets,enmy, 1);
                     break;
              case(2) :
                     if(enmy.direction==UP || enmy.direction==DOWN) enmy.direction=RIGHT;
                     else enmy.direction=UP;
                     spawn_bullet(Bullets,enmy , 1);
                     break;
              case(1) : 
                     spawn_bullet(Bullets,enmy , 1);
       }
}

void update_enemy(Sigma& player,Enemy& enmy){
       
       // if(iscolliding(enmy,player)){//killing player on collision with enemy
       //        SDL_DestroyTexture(player.text);
       //        player.text = NULL;
       // }

       
       if(ECOUNTER==110){
              spawn_enemy_bullets(eBullets,enmy);
       }
       else if(ECOUNTER>=130){
              spawn_enemy_bullets(eBullets,enmy);
              ECOUNTER = 0;
       } 
       enmy.update_enemy_position();

       enmy.update();

}

void process_cam_input(keypress key, Sigma &player){
    switch(key)
    {
        case(KEY_W):
        CAMY-=2;
        break;

        case(KEY_S):
        CAMY+=2;
        break;

        case(KEY_A):
        CAMX-=2;
        break;

        case(KEY_D):
        CAMX+=2;
        break;

    }     
}

void reverse_cam_input(keypress key){
    switch(key)
    {
        case(KEY_W):
        CAMY+=2;
        break;

        case(KEY_S):
        CAMY-=2;
        break;

        case(KEY_A):
        CAMX+=2;
        break;

        case(KEY_D):
        CAMX-=2;
        break;
    }  
}

void limit_cam(){
    if(CAMY>960) CAMY = 960;
    else if(CAMY<0) CAMY = 0;
    if(CAMX>1024) CAMX = 1024;
    else if(CAMX<0) CAMX = 0;
    
}

enum Effect{
        NO_EFFECT,
        HEALTH_INCREASE,
        SPEED_INCREASE,
        BULLET_DAMAGE_INCREASE,

};

int active_powerups=0;

class powerup:public texrect{

       public:
       Effect powerup_effect;
       int powerup_counter ;
       bool powerup_started ;   
       SDL_Texture* icon;
       
     

       powerup( SDL_Renderer* ren , SDL_Window* win){
               
               rectangle.x = 0;
               rectangle.y = 0;
               srectangle.w = 32;
               srectangle.h = 32;
               renderer = ren;
               window = win;
       }   
       
       void loadicon( std::string path)
       {
              SDL_Surface* temp=IMG_Load( path.c_str() );
              icon = SDL_CreateTextureFromSurface( renderer , temp );
              SDL_FreeSurface(temp);
       }

       void spawn_powerup( int x , int y , Effect effect )
       {
              rectangle.x = x;
              rectangle.y = y;

              powerup_counter = 0;
              powerup_started = false;

              switch( effect ){
               
               case HEALTH_INCREASE:

               powerup_effect = HEALTH_INCREASE;
              loadtexture("Assets/powerup.png");
               break;

               case SPEED_INCREASE:

               powerup_effect = SPEED_INCREASE;
               loadtexture("Assets/powerup.png");
               loadicon( "Assets/speed.png");
               break;

               case BULLET_DAMAGE_INCREASE:

               powerup_effect = BULLET_DAMAGE_INCREASE;
               loadtexture("Assets/powerup.png");
               loadicon( "Assets/bullet_icon.png");
               break;

              }
       }

       void trigger_powerup( Sigma &player)

       {
              
              switch( powerup_effect ){

                  case( HEALTH_INCREASE ):

                  if(player.health <=7)player.health +=3;
                  else player.health = 10;
                  powerup_started = true;
                  break;

                  case( SPEED_INCREASE ):

                  player.speed*=2;
                  powerup_started = true;
                  break;

                  case ( BULLET_DAMAGE_INCREASE):

                  player.bullet_damage*=3;
                  powerup_started = true;
                  break;

              }

       }

     

};

        bool isplayercolliding( texrect &a , Sigma &player ){
          
           SDL_Rect playerrect = player.rectangle;
           playerrect.x+=CAMX;
           playerrect.y+=CAMY;
           SDL_Rect &rect_b = a.rectangle;

           
          if( SDL_HasIntersection ( &playerrect , &rect_b ) ) return true ;
          else return false; 
}
       
        void update_icons( SDL_Renderer* renderer , vector <powerup> &cur_powerup ){

                     for( int i=0 ; i< active_powerups ; ++i){
                     
                                   SDL_Rect dest;
                                   dest.h = 64;
                                   dest.w = 64;
                                   dest.y = 200;
                                   dest.x = 1000 - 80*i;

                                   SDL_RenderCopy( renderer , cur_powerup[i].icon , NULL , &dest);                         
                     }
       }

       void update_powerup( SDL_Renderer* renderer , vector <powerup> &cur_powerup  ,Sigma &player ){

                   

                   for( int i=0 ; i<cur_powerup.size() ; ++i){
                   
                             powerup &current_powerup = cur_powerup[i];
                            

                             if( isplayercolliding( current_powerup , player ) ){
                                        
                                        current_powerup.trigger_powerup( player );
                                        active_powerups++;
                             }

                             if( !current_powerup.powerup_started){
                                        current_powerup.update();
                             }

                             else{

                                         current_powerup.powerup_counter++;

                                         if( current_powerup.powerup_counter >= 300 ){
 
                                                 player.speed = 1;
                                                 player.bullet_damage = 1;
                                                 cur_powerup.erase( cur_powerup.begin() + i );
                                                 active_powerups--;

                                         }
                             }

                          // update_icons( renderer , cur_powerup);
                   }   
       }
   
#endif
