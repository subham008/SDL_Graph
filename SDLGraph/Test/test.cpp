#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_Graph.hpp"

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[]) {
    // Initialize SDL and SDL_ttf
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF initialization failed: %s", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a window
    window = SDL_CreateWindow(
        "SDL2 Bar Graph Example",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load a font
    TTF_Font* font = TTF_OpenFont("assets/SpaceMono-Regular.ttf", 24);
    if (!font) {
        SDL_Log("Font loading failed: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Define datasets
    std::vector<std::pair<int, int>> data1 = {{50, 200}, {150, 300}, {250, 100}, {350, 400}, {450, 250}};
    std::vector<std::pair<int, int>> data2 = {{50, 150}, {150, 250}, {250, 50}, {350, 350}, {450, 200}};
    SDL_Color color1 = {255, 0, 0, 255}; // Red
    SDL_Color color2 = {0, 0, 255, 255}; // Blue

    SDL_Graph::Dataset dataset1(data1, color1);
    SDL_Graph::Dataset dataset2(data2, color2);

    std::vector<SDL_Graph::Dataset> datasets = {dataset1, dataset2};

    // Create a BarGraph object
    SDL_Graph::BarGraph barGraph(renderer, datasets, 600, 400, font);
    barGraph.setXTitle("X-Axis");
    barGraph.setYTitle("Y-Axis");
    barGraph.setBarColor({0, 255, 0, 255}); // Default bar color (green)

    // Main loop
    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
               // Handle window resizing
                // int newWidth, newHeight;
                // SDL_GetWindowSize(window, &newWidth, &newHeight);
                // barGraph.setWidth(newWidth);
                // barGraph.setHeight(newHeight);
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Draw the bar graph
        barGraph.renderGraph(renderer , 10,10);

        // Update the screen
        SDL_RenderPresent(renderer);

        SDL_Delay(15);
    }

    // Cleanup
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}