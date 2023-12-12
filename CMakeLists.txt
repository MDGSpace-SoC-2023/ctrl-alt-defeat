cmake_minimum_required(VERSION 3.0.0)
project(Sigma_Loop VERSION 0.1.0 LANGUAGES C CXX)



add_executable(Sigma_Loop src/main.cpp)

target_link_libraries( Sigma_Loop SDL2main SDL2 )
target_link_libraries( Sigma_Loop SDL2 SDL2_image)
target_link_libraries( Sigma_Loop SDL2_ttf SDL2)
