
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
   int r[][2]={ {0,5}, {1,8} ,{2,3},{3,9} ,{4,3},{5,9},{6,13},{7,2} ,{8 ,11},{9,17} };

  SDL_Color pink={255,25,200,25};
  SDL_Color white={255,255,255};
  SDL_Color red={200,35,25,200};
  
   SDL_setGraphFontStyle("Space_Mono/SpaceMono-Regular.ttf");

  SDL_Color arr[]={pink,red,pink,red,pink,red,pink,red,pink,red};

   SDL_Dataset dataset[2];
   SDL_CreateDataset(&dataset[0] ,d, 10 , red, NULL);
   SDL_CreateDataset(&dataset[1] ,r, 10 , pink, NULL);

   SDL_Graph bar;
   SDL_CreateGraph(&bar , dataset , 2, 300, 200);
   bar.x_title="days";
   bar.y_title="rainfall";
   SDL_CreateBarGraph(renderer , &bar);
   SDL_Rect grect={50,10,bar.w,bar.h};

   SDL_Graph line;
   SDL_CreateGraph(&line , dataset , 2, 300, 200);
   line.x_title="days";
   line.y_title="rainfall";
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
                 SDL_UpdateBarGraph(renderer,&bar);
                 SDL_UpdateLineGraph(renderer,&line);
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
    SDL_CloseGraph();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
   
    
    return 0;
}
