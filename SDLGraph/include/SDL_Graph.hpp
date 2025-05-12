
// SDL_Graph library version
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0

//marking that SDL_Graph header file is included
#ifndef SDL_GRAPH_H_
   #define SDL_GRAPH_H_



#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
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
        bool showTextLabels;
        TTF_Font* font;
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
        
        void setDatasetArray(std::vector<Dataset> data);
        std::vector<Dataset> getDatasetArray();
        
        void addDataset(Dataset data);
        void removeDataset(int index);
        void clearDatasetArray();

        int getWidth();
        int getHeight();  
        
        void setHeight(int h);
        void setWidth(int w);

        void setFont(TTF_Font* font);
        TTF_Font* getFont();

        void setFlags(uint8_t flags);

        uint8_t getFlags();

        int GetGraphMaxX();
      
        int GetGraphMinX() ;
      
        int GetGraphMaxY() ;
      
        int GetGraphMinY() ;
        
        int renderGraph(SDL_Renderer* renderer){
            if(graph_texture==NULL){
                SDL_SetError("SDL_Graph::Graph::renderGraph() ERROR : SDL_Texture* -> NULL pointer passed ");
                return -1;
            }
            SDL_SetRenderTarget(renderer , graph_texture);
            SDL_RenderCopy(renderer , graph_texture , NULL, NULL);

            SDL_SetRenderTarget(renderer , NULL);
            return 0;
        }

        ~Graph(){
            SDL_DestroyTexture(graph_texture);
        }
    };  //end of Graph class
    


    class LineGraph : public Graph {
      
      public:
        // Constructor for LineGraph
        LineGraph(SDL_Renderer* renderer  , std::vector<Dataset> data, int w, int h)
            : Graph(data, w, h) {}
    
        // Additional methods specific to LineGraph can be added here
        void drawLineGraph(SDL_Renderer* renderer);
    };



    
    class BarGraph : public Graph {
      private:
        SDL_Color Bar_color;
        std::vector<SDL_Color> bar_colors_array;

        //x and y axis title
        std::string x_title;
        std::string y_title;

        // x and y axis title textures
        SDL_Texture* x_title_texture;
        SDL_Texture* y_title_texture;

       

      public:

       void updateGraph(SDL_Renderer* renderer);
        // Constructor for BarGraph
        BarGraph(SDL_Renderer* renderer  ,std::vector<Dataset> data, int w, int h  , TTF_Font* graph_font )
            : Graph(data, w, h) {}
    
        void setBarColor(SDL_Color color);
        SDL_Color getBarColor();
        void setBarColorsArray(std::vector<SDL_Color> colors);
        std::vector<SDL_Color> getBarColorsArray();
       
        void setXTitle(std::string title);
        std::string getXTitle();
        void setYTitle(std::string title);
        std::string getYTitle();

       ~BarGraph(){
            SDL_DestroyTexture(x_title_texture);
            SDL_DestroyTexture(y_title_texture);
        }
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

