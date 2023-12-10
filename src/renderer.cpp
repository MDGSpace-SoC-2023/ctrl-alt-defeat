#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
using namespace std;

int WIDTH =640;
int HEIGHT = 480;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* texture=NULL;
SDL_Surface* surface=NULL;

class texrect{
       
       public: 

       SDL_Rect rectangle;
       int x,y,h,w;
       SDL_Texture* text;
       
       texrect();
       texrect( int x , int y , int height , int width )
       {
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;
       }

       void updatepos()
       {
        rectangle.x=x;
        rectangle.y=y;
       }
       
       void loadtexture(string path)
       {
        SDL_Surface* temp=IMG_Load( path.c_str() );
        text = SDL_CreateTextureFromSurface( renderer , temp );
        SDL_FreeSurface(temp);
        SDL_RenderCopy(renderer , text , NULL , &rectangle );
       }
       
       void update()
       {      
              updatepos();
              SDL_RenderCopy(renderer , text , NULL , &rectangle );
       }
       
       void colorKeyimage(int x, int y, int z, string path )
       {         
                SDL_Surface* temp=IMG_Load( path.c_str() );
                SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(surface->format,x,y,z));
                text = SDL_CreateTextureFromSurface( renderer , temp );
                SDL_FreeSurface(temp);
               SDL_RenderCopy(renderer , text , NULL , &rectangle );
       }

};

class ball : texrect {
        public:
        int velx;
        int vely;

        ball( int x , int y , int height ,int width , string path)
        { 
        rectangle.x=x;
        rectangle.y=y;
        rectangle.h=height;
        rectangle.w=width;   
        colorKeyimage(0,255,255,path);
        }



};


void init()
{    
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init( IMG_INIT_PNG);
    if(!TTF_Init())cout<<"failed to load ttf"<<endl;
    window=SDL_CreateWindow( "rendering" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH ,HEIGHT , SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer( window , -1 , SDL_RENDERER_ACCELERATED );
}

int main(){ 

    init();

    bool quit=false;  
    SDL_Event e;
    ball blueball(200,200,50,50,"Assets/ball.png");
    
    
    while(!quit)
    {
        while( SDL_PollEvent( &e )!=0 )
        {
         if(e.type == SDL_QUIT )quit=true;
         else if( e.type == SDL_KEYDOWN )//this event happens when any key on keyboard is pressed
                  {
                     switch(e.key.keysym.sym)
                     {       
                           case SDLK_UP:
                           if(rectangle.y>0)rectangle.y-=5; 
                           break;
                           case SDLK_DOWN:
                           if(rectangle.y<HEIGHT-50) rectangle.y+=5;
                           break;
                           case SDLK_LEFT:
                           if(rectangle.x>0)rectangle.x-=5;
                           break;
                           case SDLK_RIGHT:
                           if(rectangle.x<WIDTH-50)rectangle.x+=5;
                           break;
                     }
                  }
        }
            SDL_SetRenderDrawColor(renderer , 0 ,0 ,0 ,255);
            SDL_RenderClear(renderer);
            rectangle.loadtexture("Assets/ball.png");
            rectangle.update();
            SDL_RenderPresent( renderer );
    }
   

return 0;
}