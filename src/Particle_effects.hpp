#ifndef PARTICLE_EFFECTS_HPP
#define PARTICLE_EFFECTS_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;
#include "objects.h"

//create vector with all the active particle effects
//wnv an effect is to start create an object of particle_effect and store in vector...when ends delete it
//load tileset for each animation (bullets etc) in the begining and store it in main

class Animation_Tile{
	public:

		int tilesize;
		int sx,sy;
		SDL_Texture* text;

		Animation_Tile(SDL_Texture* tex , int size, int row , int col){

			text = tex;
			tilesize = size;

			sx = col*size;
			sy = row*size;

		}
		
};

class particle_effect{
    
      public:
      
      vector <Animation_Tile> Animation_tileset;
      //vector <SDL_Texture*> animation_textures;
	  int dx , dy, destination_size, no_of_frames;
	  int fcounter = 0;


		/**
	 * @param no_of_Frames Number of frames should be integral multiple of number of animations.
	*/
	  particle_effect(vector <Animation_Tile> &tileset , int x, int y, int Animation_size, int no_of_Frames){
		dx = x;
		dy = y;
		destination_size = Animation_size;
		no_of_frames = no_of_Frames;
		Animation_tileset = tileset;
	  }

	
      void update(SDL_Renderer* ren, int& done){
		
		SDL_Rect Dest;
		Dest.x = dx-CAMX;
		Dest.y = dy-CAMY;
		Dest.h = Dest.w = destination_size;

		SDL_Rect src;
		int i = (fcounter)/(no_of_frames/Animation_tileset.size());
		src.x = Animation_tileset[i].sx;
		src.y = Animation_tileset[i].sy;
		src.h = src.w = Animation_tileset[i].tilesize;

		SDL_RenderCopy(ren , Animation_tileset[i].text, &src, &Dest);
		fcounter++;

		if(fcounter >= no_of_frames){
			done = 1;
			fcounter = 0;
		}

      }

};



vector <Animation_Tile> load_particle_textures( string path , int tile_size , int start, int end, SDL_Renderer* ren ){
             
		int tilesize;
		vector <Animation_Tile> tileset;
            SDL_Surface* tile_surface = IMG_Load( path.c_str() );
            SDL_Texture* tileset_texture = SDL_CreateTextureFromSurface( ren ,  tile_surface );

            tilesize = tile_size;
		int tileset_rows = (tile_surface->h)/tilesize;
		int tileset_columns = (tile_surface->w)/tilesize;

            SDL_FreeSurface(tile_surface);
		
            for( int index = start ; index<=end ; ++index)
            {
                      
                  Animation_Tile temp_tile( tileset_texture , tilesize, index%tileset_columns, index/tileset_columns);
                  tileset.push_back( temp_tile ); 

            }

		return tileset;

      }


   vector <Animation_Tile> enemy_dead_animation;
   vector <Animation_Tile> miniboss_teleport_animation;
  
      void load_animations( SDL_Renderer* renderer){

                enemy_dead_animation = load_particle_textures( "Assets/selectionswirl.png" , 140 , 1 , 39 , renderer);
				miniboss_teleport_animation = load_particle_textures("Assets/teleporting.png",256,2,7,renderer);

      }

      vector <particle_effect> active_particle_effects; 

      void update_animations ( SDL_Renderer * renderer ){
           
            int done = 0;

            for( int i = 0 ; i < active_particle_effects.size() ; ++i){
     
                     active_particle_effects[i].update( renderer , done );
                     if( done ){
                           active_particle_effects.erase( active_particle_effects.begin() + i);
                           done = 0;
                     }
 
                   
            }
   


      }
      
      		/**
	 * @param no_of_Frames Number of frames should be integral multiple of number of animations.
	*/

      void trigger_animation( vector <Animation_Tile> &animation , int x , int y , int display_size , int number_of_frames ){
                
              particle_effect temp( animation , x , y  , display_size , number_of_frames );
              active_particle_effects.push_back(temp);  
               
      }



#endif