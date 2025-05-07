
// SDL_Graph library version
#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define VERSION_PATCH 0

//marking that SDL_Graph header file is included
#ifndef SDL_GRAPH_H_
   #define SDL_GRAPH_H_
#endif


#include<SDL2/SDL.h>
#include <iostream>
#include <vector>


namespace SDL_Graph{


  #ifndef SDL_DATASET_STRUCT
    #define SDL_DATASET_STRUCT

    class Dataset{
       
      private:
        std::vector<std::pair<int,int>>;// array pointer of 2 dimensional data 
      public:
        
        //defining the constructor
        Dataset(std::vector<std::pair<int,int>> data){
          this->data=data;
        }

       //define setter and getter methods for the private members
        void setData(std::vector<std::pair<int,int>> data){
          this->data=data;
        }

        std::vector<std::pair<int,int>> getData(){
          return this->data;
        }

        int getMaxX() {
          if (data.empty()) {
              throw std::runtime_error("Dataset is empty. Cannot determine maximum X value.");
          }
      
          int max = data[0].first; // Access the first element's X value
          for (const auto& point : data) {
              if (point.first > max) {
                  max = point.first;
              }
          }
          return max;
      }


      int getMinX() {
        if (data.empty()) {
            throw std::runtime_error("Dataset is empty. Cannot determine minimum X value.");
        }
    
        int min = data[0].first; // Access the first element's X value
        for (const auto& point : data) {
            if (point.first < min) {
                min = point.first;
            }
        }
        return min;
    }


    int getMaxY() {
      if (data.empty()) {
          throw std::runtime_error("Dataset is empty. Cannot determine maximum Y value.");
      }
  
      int max = data[0].second; // Access the first element's Y value
      for (const auto& point : data) {
          if (point.second > max) {
              max = point.second;
          }
      }
      return max;
  }
  
  int getMinY() {
      if (data.empty()) {
          throw std::runtime_error("Dataset is empty. Cannot determine minimum Y value.");
      }
  
      int min = data[0].second; // Access the first element's Y value
      for (const auto& point : data) {
          if (point.second < min) {
              min = point.second;
          }
      }
      return min;
  }


    };
    
    #endif

  #ifndef SDL_GRAPH_STRUCT
    #define SDL_GRAPH_STRUCT
    class Graph{

      private:
        SDL_Texture* graph_texture;
        std::vector<Dataset> dataset_array; //pointer to array of Dataset
        SDL_Color Text_color;//color of text
        SDL_Color background_color;//backgroung color
        uint8_t flags;


      public:
         //defining the constructor
         Graph(std::vector<Dataset> data, int w, int h){
           this->dataset_array=data;
           this->size=size;
           this->w=w;
           this->h=h;
         }


        //define setter and getter methods for the private members


        void setGraphTexture(SDL_Texture* texture){
          this->graph_texture=texture;
        }

        SDL_Texture* getGraphTexture(){
          return this->graph_texture;
        }



        void setTextColor(SDL_Color color){
          this->Text_color=color;
        }

        SDL_Color getTextColor(){
          return this->Text_color;
        }


        void setBackgroundColor(SDL_Color color){
          this->background_color=color;
        }

        SDL_Color getBackgroundColor(){
          return this->background_color;
        }


        void setFlags(uint8_t flags){
          this->flags=flags;
        }

        uint8_t getFlags(){
          return this->flags;
        }




        int SDL_GetGraphMaxX(SDL_Graph* b) {
          if (b->dataset_array.empty()) {
              throw std::runtime_error("Graph dataset array is empty. Cannot determine maximum X value.");
          }
      
          int max = b->dataset_array[0].getMaxX();
          for (const auto& dataset : b->dataset_array) {
              int currentMax = dataset.getMaxX();
              if (currentMax > max) {
                  max = currentMax;
              }
          }
          return max;
      }
      
      int SDL_GetGraphMinX(SDL_Graph* b) {
          if (b->dataset_array.empty()) {
              throw std::runtime_error("Graph dataset array is empty. Cannot determine minimum X value.");
          }
      
          int min = b->dataset_array[0].getMinX();
          for (const auto& dataset : b->dataset_array) {
              int currentMin = dataset.getMinX();
              if (currentMin < min) {
                  min = currentMin;
              }
          }
          return min;
      }
      
      int SDL_GetGraphMaxY(SDL_Graph* b) {
          if (b->dataset_array.empty()) {
              throw std::runtime_error("Graph dataset array is empty. Cannot determine maximum Y value.");
          }
      
          int max = b->dataset_array[0].getMaxY();
          for (const auto& dataset : b->dataset_array) {
              int currentMax = dataset.getMaxY();
              if (currentMax > max) {
                  max = currentMax;
              }
          }
          return max;
      }
      
      int SDL_GetGraphMinY(SDL_Graph* b) {
          if (b->dataset_array.empty()) {
              throw std::runtime_error("Graph dataset array is empty. Cannot determine minimum Y value.");
          }
      
          int min = b->dataset_array[0].getMinY();
          for (const auto& dataset : b->dataset_array) {
              int currentMin = dataset.getMinY();
              if (currentMin < min) {
                  min = currentMin;
              }
          }
          return min;
      }
    };

  #endif
  
}


#include"SDL_LineGraph.c"
#ifndef SDL_LINE_GRAPH_C_
  #error "SDL_LineGraph.c file not found"
#endif


#include"SDL_BarGraph.c"
#ifndef SDL_BAR_GRAPH_C_
  #error "SDL_BarGraph.c file not found"
#endif




int SDL_RenderGraph(SDL_Renderer* ren ,SDL_Graph* bar,SDL_Rect* r){

  if(bar==NULL){
    SDL_SetError("SDL_RenderGraph(... , SDL_BarGraph*) ERROR : SDL_BarGraph* -> NULL poninter passed ");
    return -1;
  }

  if(ren==NULL){
    SDL_SetError("SDL_RenderGraph(... , SDL_BarGraph*) ERROR : SDL_Renderer* -> NULL poninter passed ");
    return -1;
  }

  if(bar->graph_texture==NULL){
     SDL_SetError("SDL_RenderGraph(... , SDL_BarGraph*) ERROR : SDL_BarGraph* ->SDL_Texture*  NULL Texture passed ");
    return -1;
  }
    SDL_RenderCopy(ren , bar->graph_texture , NULL, r);
    return 0;
}


int  SDL_DestroyGraph(SDL_Graph* bar){
    if(bar==NULL){
    SDL_SetError("SDL_DestroyGraph( SDL_BarGraph*) ERROR : SDL_Graph* -> NULL poninter passed ");
    return -1;
  }

    SDL_DestroyTexture(bar->graph_texture);
    
    SDL_DestroyTexture(bar->x_title_texture);
    SDL_DestroyTexture(bar->y_title_texture);

bar=NULL;
    return 0;
}




void  SDL_CloseGraph(){
  #ifdef SDL_TTF_H_
    TTF_CloseFont(graph_font);
  #endif
}
