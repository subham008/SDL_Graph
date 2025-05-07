
// SDL_Graph library version
#define VERSION_MAJOR 2
#define VERSION_MINOR 0
#define VERSION_PATCH 0

//marking that SDL_Graph header file is included
#ifndef SDL_GRAPH_H_
   #define SDL_GRAPH_H_



#include<SDL2/SDL.h>
#include <iostream>
#include <vector>


namespace SDL_Graph{


    class Dataset{
       
      private:
        SDL_Color color ;
        std::vector<std::pair<int,int>> data;// array pointer of 2 dimensional data 
      public:
         
        //defining the constructor
        Dataset(std::vector<std::pair<int,int>> data , SDL_Color color);

       //define setter and getter methods for the private members
        void setData(std::vector<std::pair<int,int>> data);

        std::vector<std::pair<int,int>> getData();

        void setColor(SDL_Color color);
        SDL_Color getColor();
        
        int getMaxX() ;
        int getMinX() ;
        int getMaxY() ;
        int getMinY() ;


    };
    


    class Graph{

      private:
        SDL_Texture* graph_texture;
        std::vector<Dataset> dataset_array; //pointer to array of Dataset
        SDL_Color Text_color;//color of text
        SDL_Color background_color;//backgroung color
        uint8_t flags;
        int width , height;

      public:
         //defining the constructor
         Graph(std::vector<Dataset> data, int w, int h);


        //define setter and getter methods for the private members


        void setGraphTexture(SDL_Texture* texture);

        SDL_Texture* getGraphTexture();

        void setTextColor(SDL_Color color);

        SDL_Color getTextColor();


        void setBackgroundColor(SDL_Color color);

        SDL_Color getBackgroundColor();


        void setFlags(uint8_t flags);

        uint8_t getFlags();

        int SDL_GetGraphMaxX();
      
        int SDL_GetGraphMinX() ;
      
        int SDL_GetGraphMaxY() ;
      
        int SDL_GetGraphMinY() ;
    };  //end of Graph class
    


    class LineGraph : public Graph {
      
      public:
        // Constructor for LineGraph
        LineGraph(std::vector<Dataset> data, int w, int h)
            : Graph(data, w, h) {}
    
        // Additional methods specific to LineGraph can be added here
        void drawLineGraph(SDL_Renderer* renderer);
    };



    
    class BarGraph : public Graph {
      public:
        // Constructor for BarGraph
        BarGraph(std::vector<Dataset> data, int w, int h)
            : Graph(data, w, h) {}
    
        // Additional methods specific to BarGraph can be added here
        void drawBarGraph(SDL_Renderer* renderer);
    };


  
}




// int SDL_RenderGraph(SDL_Renderer* ren ,SDL_Graph* bar,SDL_Rect* r){

//   if(bar==NULL){
//     SDL_SetError("SDL_RenderGraph(... , SDL_BarGraph*) ERROR : SDL_BarGraph* -> NULL poninter passed ");
//     return -1;
//   }

//   if(ren==NULL){
//     SDL_SetError("SDL_RenderGraph(... , SDL_BarGraph*) ERROR : SDL_Renderer* -> NULL poninter passed ");
//     return -1;
//   }

//   if(bar->graph_texture==NULL){
//      SDL_SetError("SDL_RenderGraph(... , SDL_BarGraph*) ERROR : SDL_BarGraph* ->SDL_Texture*  NULL Texture passed ");
//     return -1;
//   }
//     SDL_RenderCopy(ren , bar->graph_texture , NULL, r);
//     return 0;
// }


// int  SDL_DestroyGraph(SDL_Graph* bar){
//     if(bar==NULL){
//     SDL_SetError("SDL_DestroyGraph( SDL_BarGraph*) ERROR : SDL_Graph* -> NULL poninter passed ");
//     return -1;
//   }

//     SDL_DestroyTexture(bar->graph_texture);
    
//     SDL_DestroyTexture(bar->x_title_texture);
//     SDL_DestroyTexture(bar->y_title_texture);

// bar=NULL;
//     return 0;
// }

#endif

