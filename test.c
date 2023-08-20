
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"SDL_Graph.h"

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[]) {
    // Initialize SDL

    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow(
        "SDL2 Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return 1;
    }

   int d[][2]={ {0,4}, {1,10} ,{2,4},{3,7} ,{4,6},{5,8},{6,12},{7,9} ,{8 ,5},{9,8} };
  SDL_Color pink={255,25,200,25};
  SDL_Color red={200,35,25,200};
    
   SDL_setGraphFontStyle("SpaceMono-Regular.ttf");
   SDL_Graph bar;
   bar.data=d;
   bar.size=10;
   bar.background_color=pink;
   bar.Bar_color=red;
   bar.x_title="days";
   bar.y_title="rainfall";
   bar.w=300;
   bar.h=200;
  
   SDL_CreateBarGraph(renderer , &bar);
  
   SDL_Rect grect={50,10,bar.w,bar.h};

   SDL_Graph line;
   line.data=d;
   line.size=10;
   line.background_color=pink;
   line.Bar_color=red;
   line.x_title="days";
   line.y_title="rainfall";
   line.w=400;
   line.h=200;
  
   SDL_CreateLineGraph(renderer , &line);
  
   SDL_Rect lrect={60,300,line.w,line.h};

    // Main loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if(event.window.event==SDL_WINDOWEVENT_RESIZED){
                 SDL_DestroyGraph(&bar);
                 SDL_DestroyGraph(&line);
                 SDL_CreateBarGraph(renderer,&bar);
                 SDL_CreateLineGraph(renderer,&line);
            }

        }
        

        // Clear the screen
        SDL_RenderClear(renderer);
        SDL_RenderGraph(renderer , &bar ,&grect);
        SDL_RenderGraph(renderer , &line , &lrect);

        SDL_SetRenderDrawColor(renderer , 200 , 25 , 25 , 255);
        SDL_RenderDrawPoint(renderer , 100 , 300);
        // Update the screen
         SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);

        SDL_Delay(15);
    }

    // Clean up and quit
    SDL_DestroyGraph(&bar);
     SDL_DestroyGraph(&line);
    SDL_GraphQuit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
   
    
    return 0;
}
