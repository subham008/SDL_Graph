
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

        std::vector<std::pair<int,int>> getData() const;

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
        
        int renderGraph(SDL_Renderer* renderer , int x , int y){
            if(graph_texture==NULL){
                std::cerr<<"SDL_Graph::Graph::renderGraph() ERROR : SDL_Texture* -> NULL pointer passed "<<std::endl;
                return -1;
            }

            SDL_Rect graph_rect;
            graph_rect.x =x;
            graph_rect.y = y;
            graph_rect.w=width;
            graph_rect.h = height;
           // SDL_SetRenderTarget(renderer , graph_texture);
            SDL_RenderCopy(renderer , graph_texture , NULL, &graph_rect);

            SDL_SetRenderTarget(renderer , NULL);
            return 0;
        }

        ~Graph(){
            SDL_DestroyTexture(graph_texture);
        }
    };  //end of Graph class
    


    // class LineGraph : public Graph {
    //   private:
    //     SDL_Color line_color;
    //     std::vector<SDL_Color> line_colors_array;

    //     //x and y axis title
    //     std::string x_title;
    //     std::string y_title;

    //     // x and y axis title textures
    //     SDL_Texture* x_title_texture;
    //     SDL_Texture* y_title_texture;
    //   public:

    //    void updateGraph(SDL_Renderer* renderer);
      
    //     // Constructor for LineGraph
    //     LineGraph(SDL_Renderer* renderer  , std::vector<Dataset> data, int w, int h , TTF_Font* graph_font);     
        
    //     void setLineColor(SDL_Color color);
    //     SDL_Color getLineColor();
    //     void setLineColorsArray(std::vector<SDL_Color> colors);
    //     std::vector<SDL_Color> getLineColorsArray();

    //      void setXTitle(std::string title);
    //     std::string getXTitle();
    //     void setYTitle(std::string title);
    //     std::string getYTitle();
        
    //     // Destructor
    //     ~LineGraph(){
    //         SDL_DestroyTexture(x_title_texture);
    //         SDL_DestroyTexture(y_title_texture);
    //     }

    // };



    
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
        BarGraph(SDL_Renderer* renderer  ,std::vector<Dataset> data, int w, int h  , TTF_Font* graph_font );
    
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



#endif

