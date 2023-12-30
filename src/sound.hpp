#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <string>
using namespace std;


class sound_interface{

   virtual void playsound();
   virtual void stopsound();


};

class sound : public sound_interface{
   
       public:

       SDL_AudioDeviceID device;
       SDL_AudioSpec audiospec;
       Uint8* wavestart;
       Uint32 wavelength;
       
       sound( string path){
              
               SDL_LoadWAV( path.c_str() , &audiospec ,  &wavestart , &wavelength);  
             
       }

       void playsound(){
           
             SDL_QueueAudio( device , wavestart , wavelength );
             SDL_PauseAudioDevice( device , 0);
              
       }

       void stopsound(){
             SDL_PauseAudioDevice(device , 1);
       }

       void setupdevice(){

                  device = SDL_OpenAudioDevice(nullptr, 0, &audiospec, nullptr, 0);

       }


};








#endif