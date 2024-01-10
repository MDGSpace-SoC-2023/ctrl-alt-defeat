#ifndef PARTICLE_EFFECTS_HPP
#define PARTICLE_EFFECTS_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
using namespace std;

class particle_effect{
    
      public:
      int tilesize;
      int framecount;
      vector <SDL_Texture*> animation_textures;

      void load_particle_textures( string path , int tile_size , int frame_count ){




      } 


      void show_particle_effect(  ){





      }






  



}









#endif


