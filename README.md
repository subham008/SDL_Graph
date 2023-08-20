# SDL_Graph 1.0.0
SDL_Graph is a extension to SDL library , it is able to render bar and line graphs ,its easy to use , no need to think about architecture , as it is not compiled you just have to  add this files to your desired directory and include this files from there 

HOW TO INSTALL
this is a source file so just need to download the files
SDL_Graph.h the SDL_Graph header file
SDL_BarGraph.c the source to SDL_CreateBarGraph(...) function
SDL_LineGraph.c the source to SDL_CreateLineGraph(...) function

This above files are source so you should place this file in the same directory as your working directory

HOW TO COMPILE 
There is no special linker or anything to compile this , normally use SDL2 and SDL_ttf compile commands 

command is : gcc tect.c -o test -lSDL2 -lSDL2_ttf

*********WARNING**************
 Always include SDL_Graph.h after including SDL.h and SDL_ttf.h
 
For detailed information have a look at test.c file 
