   // objects.h

#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "Music.hpp"

using namespace std;

int CAMX = 0;
int CAMY = 0;
int cam_speed = 4;

int WIDTH  =1024;
int HEIGHT =960;

int ECOUNTER = 0;
int framecount = 0;
int dashcounter = 0;

int enemy_dead_counter = 0;
int musicplayed = -1;

bool keystate[10];

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
     KEY_ENTER,
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

                     case(SDLK_RETURN):
                     return KEY_ENTER;
                     
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
       float speedx,speedy;
       playerdirn direction;
       bool collision=false;
       SDL_Rect srectangle;

        texrect( )//default constructer
       {
           rectangle.x=0;
           rectangle.y=0;
           rectangle.h=0;
           rectangle.w=0;    
           speedx=speedy=0;   
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
              speedx = speedy =sped;
       }

       void set_dimension( int x , int y , int height , int width, int sped, SDL_Renderer* rend , SDL_Window* wind)
       {
              rectangle.x=x;
              rectangle.y=y;
              rectangle.h=height;
              rectangle.w=width;
              speedx = speedy =sped;
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

       void copytexture ( SDL_Texture *texture){
                text = texture;
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

          return SDL_HasIntersection( &rect_a , &rect_b );        
}



int staminacounter = 0;
int bulletcounter = 0;
SDL_Texture* player_bullet_texture = NULL;

Sound miniboss_shooting;
class Sigma:public texrect
{
      public:
      bool dashing = false;
      int health;
      int bullet_damage = 1;
      int stamina;


      SDL_Texture* heart=NULL;
      SDL_Texture* stamina_text = NULL;
      SDL_Texture* gameover_text1 =NULL;
      SDL_Texture* gameover_text2 =NULL;

      Sound gunshot_sound;
      Sound damage_taken_sound;
      Sound Game_over_sound;
      Sound enemy_dead_sound;


      Sigma( SDL_Renderer* rend , SDL_Window* wind)
      { 
        direction=UP;  
       //  set_dimension( 512 , 400 , 64 , 64 , 1 , rend , wind );
               set_dimension( 512 , 480 , 64 , 64 , 0 , rend , wind );

        loadtexture("Assets/chibi_tileset.png");

        health = 10;
        stamina = 10;
        SDL_Surface* temp = IMG_Load( "Assets/heart.png" );
        heart = SDL_CreateTextureFromSurface(renderer , temp);

        temp = IMG_Load("Assets/power.png");
        stamina_text = SDL_CreateTextureFromSurface( renderer , temp);
        SDL_FreeSurface(temp);

            
       TTF_Font* gameover_font = TTF_OpenFont( "Assets/8bit_font.ttf" , 32);

       SDL_Surface* temp1 = TTF_RenderText_Solid( gameover_font , "Game Over!" , {255,255,51});
       gameover_text1 = SDL_CreateTextureFromSurface( renderer , temp1 );

       SDL_Surface* temp2 = TTF_RenderText_Solid( gameover_font , "Press [Enter] To Restart" , {255,255,51});
       gameover_text2 = SDL_CreateTextureFromSurface( renderer , temp2 );

       SDL_Surface* temp3 = IMG_Load( "Assets/gunshot.png");
       player_bullet_texture = SDL_CreateTextureFromSurface( renderer , temp3);

       gunshot_sound.Load_Sound("/home/jshishimaru/development/Sigma_Loop/src/Assets/Audio/Sound_Effects/player_shoot.wav" , 40);
       damage_taken_sound.Load_Sound( "/home/jshishimaru/development/Sigma_Loop/src/Assets/Audio/Sound_Effects/damage_taken.wav" , 100);
       enemy_dead_sound.Load_Sound( "/home/jshishimaru/development/Sigma_Loop/src/Assets/Audio/Sound_Effects/enemy_death.wav" , 50);
       miniboss_shooting.Load_Sound( "/home/jshishimaru/development/Sigma_Loop/src/Assets/Audio/Sound_Effects/miniboss_shooting.wav" , 50);

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

      void draw_stamina()
      {
            
             for( int i=1 ; i<=stamina ; ++i){
               SDL_Rect dest;
               dest.w = 20;
               dest.h = 20;
               dest.y = 40;
               dest.x = 10 + i*20;

               SDL_RenderCopy(renderer , stamina_text , NULL , &dest);  
               
         }


      }
      
         void update_sigma() // updating to renderer
       {      
              int frame = (framecount/6) % 3;
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

              //    rectangle.y += 2;
                 CAMY += 7;     

              //      if(CAMY>960)
              //      {
              //          int gap = CAMY-960;
              //          CAMY = 960;
              //          rectangle.y += gap;
              //      }
                 break;

                 case(RIGHT):
              //    rectangle.x += 2;
                 CAMX += 7;

              //      if(CAMX>1024)
              //      {
              //          int gap = CAMX-1024;
              //          CAMX = 1024;
              //          rectangle.x += gap;
              //      }
                 break;

                 case(LEFT):
              //    rectangle.x -= 2;
                 CAMX -= 7;

              //      if(CAMX<0)
              //      {
              //          int gap = -CAMX;
              //          CAMX = 0;
              //          rectangle.x -= gap;
              //      }
                 break;

                 case(UP):
              //    rectangle.y -= 2;
                 CAMY -= 7;

              //      if(CAMY<0)
              //      {
              //          int gap = -CAMY;
              //          CAMY = 0;
              //          rectangle.y -= gap;
              //      }
                 break;
              } 
              

              dashcounter++;
              if(dashcounter==20){
                     dashing = false;
                     dashcounter = 0;
              }

            }  

              staminacounter++;
              if( staminacounter >= 30){
   
                  if(stamina < 10)stamina++;
                  staminacounter = 0;

              }

              bulletcounter++;
              draw_hearts();
              draw_stamina();
              SDL_RenderCopy(renderer , text , &src , &rectangle );

       }
       void process_input_direction( keypress key )
       {
       //    framecount++;
           switch(key)
           {
             case(KEY_W):                                                        
                    direction=UP;
             break;

             case(KEY_A):
                    direction=LEFT;
             break;

             case(KEY_S):
                    direction=DOWN;
             break;

             case(KEY_D):
                    direction=RIGHT;
             break;

             case(KEY_E):
                    
                   if(stamina == 10)
                   { 
                    dashing = true;
                    stamina = 0;
                   }

             break;

            // case( KEY_I):
                  
          //        cout << rectangle.x << " "<< rectangle.y<<endl;

           }

       }

       void process_input( Sigma &player){
           
           int pressed = 0;
           
           switch( player.direction ){
    
           case(UP):
           if( keystate[KEY_W]){

               //     rectangle.y -=speedy;
                    pressed++;
                    
           }
           break;

           case(LEFT):
           if( keystate[KEY_A]){

                 //   rectangle.x -=speedx;
                    pressed++;
                    
           }
           break;

           case(DOWN):
           if( keystate[KEY_S]){

                   // rectangle.y +=speedy;
                    pressed++;
                    

           }
           break;

           case(RIGHT):
           if( keystate[KEY_D]){

                   // rectangle.x +=speedx;
                    pressed++;                    

           }
           break;

         }

         if(pressed){
               framecount++;
         }
           
       }

       void reverse_dash()
       {
               switch(direction)
              {
                 case(DOWN):
              //    rectangle.y -= 2;
                 CAMY -= 7;
                 break;
                 case(RIGHT):
              //    rectangle.x -= 2;
                 CAMX -= 7;
                 break;
                 case(LEFT):
              //    rectangle.x += 2;
                 CAMX += 7;
                 break;
                 case(UP):
              //    rectangle.y += 2;
                 CAMY += 7;
                 break;
              }
       }

       void reverse_input( keypress key , Sigma &player )
       {
          switch( player.direction ){
    
           case(UP):
           if( keystate[KEY_W]){

                    //rectangle.y +=speedy;
           //         keystate[KEY_W]=false;
                    
           }
           break;

           case(LEFT):
           if( keystate[KEY_A]){

                    //rectangle.x +=speedx;
          //          keystate[KEY_A]=false;
                    
                    
           }
           break;

           case(DOWN):
           if( keystate[KEY_S]){

                    //rectangle.y -=speedy;
          //          keystate[KEY_S]=false;
                    
              
           }
           break;

           case(RIGHT):
           if( keystate[KEY_D]){

                    //rectangle.x -=speedx;
           //         keystate[KEY_D]=false;
                                        

           }
           break;

         }
       }
 
};


class 
projectile:public texrect
{
       public:
       int velx;
       int vely;
     
       projectile( texrect player , int code)
       {
              velx=0;
              vely=0;
              rectangle.w = 20;
              rectangle.h = 20;
              srectangle.w=20;
              srectangle.h=20;
              rectangle.x=player.rectangle.x + player.rectangle.w/2 + CAMX;
              rectangle.y=player.rectangle.y + player.rectangle.h/2 + CAMY;
              srectangle.x = rectangle.x - CAMX  ;
              srectangle.y = rectangle.y  - CAMY ;
              copytexture(player_bullet_texture);


              if(code == 1){  // for non player entities
                       
                     rectangle.x=player.rectangle.x + player.rectangle.w/2;
                     rectangle.y=player.rectangle.y + player.rectangle.h/2;
                     srectangle.x = rectangle.x - CAMX ;
                     srectangle.y = rectangle.y - CAMY ;
                       
              }
               
              renderer = player.renderer;
              window = player.window;
       
              switch( player.direction ){
                
              case(UP):
                     vely= -7;
                     velx=0;
                     break;
              case(DOWN):
                     vely= 7;
                     velx=0;
                     break;
              case(LEFT):
                     velx= -7;
                     vely=0;
                     break;
              case(RIGHT):
                     velx= 7;
                     vely=0;
                     break;
              } 
       }
        projectile( texrect player , int code , SDL_Texture* gun_texture)
       {
              velx=0;
              vely=0;
              rectangle.w = 20;
              rectangle.h = 20;
              srectangle.w=20;
              srectangle.h=20;
              rectangle.x=player.rectangle.x + player.rectangle.w/2 + CAMX;
              rectangle.y=player.rectangle.y + player.rectangle.h/2 + CAMY;
              srectangle.x = rectangle.x - CAMX  ;
              srectangle.y = rectangle.y  - CAMY ;
              copytexture(gun_texture);


              if(code == 1){  // for non player entities
                       
                     rectangle.x=player.rectangle.x + player.rectangle.w/2;
                     rectangle.y=player.rectangle.y + player.rectangle.h/2;
                     srectangle.x = rectangle.x - CAMX ;
                     srectangle.y = rectangle.y - CAMY ;
                       
              }
               
              renderer = player.renderer;
              window = player.window;
       
              switch( player.direction ){
                
              case(UP):
                     vely= -7;
                     velx=0;
                     break;
              case(DOWN):
                     vely= 7;
                     velx=0;
                     break;
              case(LEFT):
                     velx= -7;
                     vely=0;
                     break;
              case(RIGHT):
                     velx= 7;
                     vely=0;
                     break;
              } 
       }

       projectile( int x , int y , int dirn , SDL_Renderer* renderer1 , SDL_Window* window1 , int size ,SDL_Texture *gunshot_text){

       renderer = renderer1;
       window = window1;


              rectangle.w = size;
              rectangle.h = size;
              rectangle.x = x + 64;
              rectangle.y = y + 96;

              srectangle.w=size;
              srectangle.h=size;
              srectangle.x = x - CAMX ;
              srectangle.y = y - CAMY ;

              copytexture(gunshot_text);              
              switch(dirn){

              case(1):
                     vely= -7;
                     velx=0;
                     break;
              case(2):
                     vely= 7;
                     velx=0;
                     break;
              case(3):
                     velx= -7;
                     vely=0;
                     break;
              case(4):
                     velx= 7;
                     vely=0;
                     break;

              }

       }
       

       void update_projectile ()
       {
              rectangle.x+=velx;
              rectangle.y+=vely;
              
       }
};

vector <projectile> Bullets;
vector <projectile> eBullets;
vector <projectile> miniboss_bullets; 

void spawn_bullet(vector <projectile> &Bullets , texrect enemy , int code  ,SDL_Texture* gun_texture)
{       
       projectile bullet( enemy ,code , gun_texture);
       Bullets.push_back( bullet );
}




class Enemy:public texrect{
       public:
              int x1;
              int y1;
              int x2;
              int y2;
              int ehealth=3;
              int speed;
              int mode = 1;
              int counter = 0;
              
              SDL_Texture * enemy_gunshot = NULL;
              //1-same direction
              //2-up down enmy shoots right, right left enmy shoots up
              //3-opposite

              Music enemy_damage_taken_sound;
              Music enemy_death_sound;

              
              Enemy(int height,int width,int xpt1,int ypt1, int xpt2, int ypt2,int MODE, SDL_Renderer* ren, SDL_Window* win){
                     srectangle.h = height;
                     srectangle.w = width;
                     rectangle.h = height;
                     rectangle.w = width;
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
                     loadtexture("Assets/enemy_spritesheet.png");
                     SDL_Surface* temp = IMG_Load("Assets/enemy_gunshot.png");
                     enemy_gunshot = SDL_CreateTextureFromSurface(renderer , temp);
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
                     spawn_bullet(Bullets,enmy, 1 , enmy.enemy_gunshot);
                     break;
              case(2) :
                     if(enmy.direction==UP || enmy.direction==DOWN) enmy.direction=RIGHT;
                     else enmy.direction=UP;
                     spawn_bullet(Bullets, enmy , 1 ,enmy.enemy_gunshot );
                     break;
              case(1) : 
                     spawn_bullet(Bullets, enmy , 1 , enmy.enemy_gunshot);
       }
}

void update_enemy(Sigma& player,Enemy& enmy ){
       
       
       if(ECOUNTER==110){
              spawn_enemy_bullets(eBullets,enmy);
       }
       else if(ECOUNTER>=130){
              spawn_enemy_bullets(eBullets,enmy);
              ECOUNTER = 0;
       } 
       enmy.update_enemy_position();

              enmy.counter++;
              enmy.counter%=80;
              
              SDL_Rect src;
              src.w = 286;
              src.h = 286;
              src.x = 286*(enmy.counter/8);
              src.y = 0; 
              enmy.srectangle.x = enmy.rectangle.x - CAMX;
              enmy.srectangle.y = enmy.rectangle.y - CAMY;

              SDL_RenderCopy(player.renderer , enmy.text , &src , &enmy.srectangle );

}

void process_cam_input(Sigma &player){
       
          switch( player.direction ){

           case(UP):
           if( keystate[KEY_W]){

                    CAMY -= cam_speed;
           }
           break;
           case(LEFT):
           if( keystate[KEY_A]){

                    CAMX -= cam_speed;

           }
           break;
           case(DOWN):
           if( keystate[KEY_S]){

                    CAMY +=cam_speed;

           }
           break;
           case(RIGHT):
           if( keystate[KEY_D]){

                    CAMX +=cam_speed;

           }
           break;
          }

}

void reverse_cam_input(keypress key , Sigma &player){

       switch( player.direction ){

              case(UP):
              if( keystate[KEY_W]){

                    CAMY +=cam_speed;

              }
              break;

              case(LEFT):
              if( keystate[KEY_A]){

                    CAMX +=cam_speed;

              }
              break;

              case(DOWN):
              if( keystate[KEY_S]){

                    CAMY -=cam_speed;

              }
              break;
              
              case(RIGHT):
              if( keystate[KEY_D]){

                    CAMX -=cam_speed;

              }
              break;

       
       }
}

void limit_cam(Sigma& player){
    if(CAMY>960){
       CAMY = 960;
       player.speedy = 3;
    }
    else if(CAMY<0){
       CAMY = 0;
       player.speedy = 3;
    }
    else player.speedy = 1;
    if(CAMX>1024){
       CAMX = 1024;
       player.speedx = 3;
    }
    else if(CAMX<0){
       CAMX = 0;
       player.speedx = 3;
    }
    else player.speedx = 1;
}

enum Effect{
        NO_EFFECT,
        HEALTH_INCREASE,
        SPEED_INCREASE,
        BULLET_DAMAGE_INCREASE,
        CHIPI_CHIPI_CHAPA_CHAPA,

};

int active_powerups=0;

class powerup:public texrect{

       public:
       Effect powerup_effect   ;
       int powerup_counter     ;
       bool powerup_started    ;   
       SDL_Texture* icon = NULL;

       Music chipi_chipi;
       powerup( SDL_Renderer* ren , SDL_Window* win){
               
               rectangle.x = 0;
               rectangle.y = 0;
               rectangle.w = 32;
               rectangle.h = 32;
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
              loadtexture("Assets/health_powerup.png");
               break;

               case SPEED_INCREASE:

               powerup_effect = SPEED_INCREASE;
               loadtexture("Assets/speed_powerup.png");
               loadicon( "Assets/sped.png");
               break;

               case BULLET_DAMAGE_INCREASE:

               powerup_effect = BULLET_DAMAGE_INCREASE;
               loadtexture("Assets/bullet_powerup.png");
               loadicon( "Assets/bullet_icon.png");
               break;

               case CHIPI_CHIPI_CHAPA_CHAPA:

               powerup_effect = CHIPI_CHIPI_CHAPA_CHAPA;
               chipi_chipi.Load_Music("Assets/Audio/Music/chipi_chipi.mp3" , 50);
               loadtexture("Assets/cool.png");

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

              //     player.speedx*=2;
              //     player.speedy*=2;
                     cam_speed=6;
                  
                  powerup_started = true;
                  break;

                  case ( BULLET_DAMAGE_INCREASE):

                  player.bullet_damage=3;
                  powerup_started = true;
                  break;

                  case ( CHIPI_CHIPI_CHAPA_CHAPA ):

                  chipi_chipi.playmusic(0);
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
                                   dest.y = 10;
                                   dest.x = 950 - 80*i;

                          if( cur_powerup[i].powerup_effect != HEALTH_INCREASE) SDL_RenderCopy( renderer , cur_powerup[i].icon , NULL , &dest);                         
                     }
       }

       void update_powerup( SDL_Renderer* renderer , vector <powerup> &cur_powerup  ,Sigma &player ){
                
                   

                   for( int i=0 ; i<cur_powerup.size() ; ++i){
                   
                             powerup &current_powerup = cur_powerup[i];
                            

                             if( isplayercolliding( current_powerup , player ) ){
                                        
                                        current_powerup.trigger_powerup( player );
                                        current_powerup.rectangle.w = 0;
                                        current_powerup.rectangle.h = 0;
                                        active_powerups++;
                             }

                             if( !current_powerup.powerup_started){
                                        current_powerup.update();
                             }

                             else{

                            switch(current_powerup.powerup_effect)
                            {
                                   case(SPEED_INCREASE):
                                   cam_speed = 6;
                                   break;
                                   case(BULLET_DAMAGE_INCREASE):
                                   player.bullet_damage = 3;   
                                   break;
                            }


                                         current_powerup.powerup_counter++;

                                         if( current_powerup.powerup_counter >= 360 ){
 
                                                 switch(current_powerup.powerup_effect){

                                                        case(SPEED_INCREASE):
                                                        cam_speed = 4;
                                                        break;
                                                        case(BULLET_DAMAGE_INCREASE):
                                                        player.bullet_damage = 1;   
                                                        break;
                                                        case(CHIPI_CHIPI_CHAPA_CHAPA):
                                                        musicplayed = -1;
                                                        break;

                                                 }
                                                 cur_powerup.erase( cur_powerup.begin() + i );
                                                 active_powerups--;
       

                                         }
                             }

                           update_icons( renderer , cur_powerup);

                   }   
       }

#endif
