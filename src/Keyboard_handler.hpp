#ifndef KEYBOARD_HANDLER_HPP
#define KEYBOARD_HANDLER_HPP

#include "objects.h"


    void handle_input( SDL_Event &e){

            keypress key;

             switch( e.type){
                
                case( SDL_KEYDOWN ):

                    key = getinput(e);
                    keystate[key] = true;
                    break;

                
                case( SDL_KEYUP ):

                    key = getinput(e);
                    keystate[key] = false;
                    break;

             }

    }


#endif