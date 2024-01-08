#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
using namespace std;

class Music{
   
    public:

    Mix_Music* music = NULL;
    int volume;

    Music(){
         volume = 0;
    }

    Music( string path , int vol){ // vol ranges from 0 to 128
             
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
            {
                        cout << "Error loading audio"<<endl;
            }
             
            music = Mix_LoadMUS( path.c_str() );
            volume = vol; 
            Mix_VolumeMusic(volume);      

    }   

    void Load_Music( string path , int vol ){
     
         if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
            {
                        cout << "Error loading audio"<<endl;
            }
             
            music = Mix_LoadMUS( path.c_str() );
            volume = vol; 
            Mix_VolumeMusic(volume);  
        
    }
 
    ~Music(){
        Mix_FreeMusic( music );
    }   

    void playmusic( int loopcount ){  //set loopcount to -1 to play music forever
  
            Mix_PlayMusic( music , loopcount );

    }

    void pausemusic(){

        Mix_PauseMusic();

    }
    
    void stopmusic(){



    }



};



#endif