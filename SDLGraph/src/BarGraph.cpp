
#ifndef SDL_BAR_GRAPH_CPP
   #define SDL_BAR_GRAPH_CPP
#endif


#include "SDL_Graph.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace SDL_Graph{
// Constructor for BarGraph
 BarGraph::BarGraph (SDL_Renderer* renderer , std::vector<Dataset> data, int w, int h  , TTF_Font* graph_font)
        : Graph(data, w, h) {
        if(renderer == NULL) {
            SDL_SetError("SDL_Graph::LineGraph::LineGraph() ERROR : SDL_Renderer* -> NULL pointer passed ");
            return;
        }

        if(data.empty()) {
            SDL_SetError("SDL_Graph::LineGraph::LineGraph() ERROR : Dataset array is empty ");
            return;
        }

        setDatasetArray(data); 
        setWidth(w);
        setHeight(h);
        setTextColor({0, 0, 0, 255});
        setBackgroundColor({255, 255, 255, 255});
        setFlags(0);
        setFont(graph_font);

       setGraphTexture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, w, h));
       
       //creating graph first time
       updateGraph(renderer);

} // end of constructor


void BarGraph::updateGraph(SDL_Renderer* renderer ){
   if(getGraphTexture()==NULL)
            std::cout<<"SDL_Graph::LineGraph::LineGraph() ERROR : SDL_CreateTexture() failed : "<<SDL_GetError()<<std::endl;
        
        SDL_Color b = getBackgroundColor();
        // Set the background color
        SDL_SetRenderDrawColor(renderer , b.r , b.g , b.b , b.a);
        SDL_SetRenderTarget(renderer , getGraphTexture());
        SDL_RenderClear(renderer);
        
      // now printing x and y lines
        SDL_SetRenderDrawColor(renderer , 0,0,0,100);
        SDL_RenderDrawLine(renderer ,20 , 20 , 20 , -20);// rendering Y axis line
        SDL_RenderDrawLine(renderer ,20 , getHeight()-20 ,getWidth()-20 , getHeight()-20);// rendering X axis line

        int x_max=GetGraphMaxX();
        int x_min=GetGraphMinX();

        int y_max=GetGraphMaxY();
        int y_min=GetGraphMinY();

        int x_pix=(getWidth()-40)/(x_max+1);
        int y_pix=(getHeight()-40)/y_max;

        int xv_pix=x_pix/getDatasetArray().size();

       SDL_Color c;

      SDL_Rect r;
      r.w=x_pix;
      
      Dataset* d=NULL;
      for(int j=0 ; j<getDatasetArray().size();j++){
         d=&getDatasetArray()[j];
         c=getBarColor();
        if(getBarColorsArray().empty())
            for(int i=0;i< getBarColorsArray().size() ; i++){
                SDL_SetRenderDrawColor(renderer ,c.r,c.g,c.b,c.a );
                r.w=xv_pix;
                r.h=y_pix*(d->getData()[i].second );  //i,1
                r.y=(getHeight()-20)-r.h;
                r.x=(d->getData()[i].first)*x_pix + (j*xv_pix);
                r.x+=20;
                SDL_RenderFillRect(renderer , &r);

                r.y=r.y-1;
                r.x=r.x-1;
                r.w=r.w+1;

                SDL_SetRenderDrawColor(renderer ,0,0,0,244 );
                SDL_RenderDrawRect(renderer,&r);
        }// end of i loop
          else
              for(int i=0;i<getDatasetArray().size(); i++){
                  c=getBarColorsArray()[i];
                  SDL_SetRenderDrawColor(renderer ,c.r,c.g,c.b,c.a );
                  r.w=xv_pix;
                  r.h=y_pix*(d->getData()[i].second);
                  r.y=(getHeight()-20)-r.h;
                  r.x=(d->getData()[i].first)*x_pix + (j*xv_pix);
                  r.x+=20;
                  SDL_RenderFillRect(renderer , &r);

                  r.y=r.y-1;
                  r.x=r.x-1;
                  r.w=r.w+1;

                  SDL_SetRenderDrawColor(renderer ,0,0,0,244 );
                  SDL_RenderDrawRect(renderer,&r);
     
            }//end of i loop
          }



      //rendering text using SDL_ttf




    if(getFont()==NULL)
         return;
       
      SDL_Surface* tmp_sur;
      SDL_Texture* tmp_tex;
      

      //creating x_title texture

     if( getXTitle().length() >0 ){
       //creating and rendering x title 
       tmp_sur=TTF_RenderUTF8_Blended(getFont() , getXTitle().c_str() , getTextColor() );
       if( tmp_sur==NULL){
         SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
         return;
         }

       tmp_tex=SDL_CreateTextureFromSurface(renderer , tmp_sur);

      if(tmp_tex==NULL){
        SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
       return;
      }
   
      r.x=(getWidth()-tmp_sur->w)/2;
      r.y=getHeight()-20;
      r.h=tmp_sur->h;
      r.w=tmp_sur->w;
      SDL_RenderCopy(renderer , tmp_tex , NULL,&r);
      SDL_FreeSurface(tmp_sur);
      x_title_texture=tmp_tex;
    }


    //creating y_title texture
    if( getYTitle().length()>0){
       //creating and rendering x title 
       tmp_sur =TTF_RenderUTF8_Blended(getFont() ,getYTitle().c_str(), getTextColor() );
      if(tmp_sur==NULL){
        SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
        return ;
       }
   
      tmp_tex=SDL_CreateTextureFromSurface(renderer ,tmp_sur );
   
     if(tmp_tex==NULL){
        SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
       return;
     }
   
     r.x=10;
     r.y=0;
     r.h=tmp_sur->h;
     r.w=tmp_sur->w;
     SDL_RenderCopy(renderer , tmp_tex , NULL,&r);
     SDL_FreeSurface(tmp_sur);
     y_title_texture=tmp_tex;
  }


  //setting renderer to default
  SDL_SetRenderTarget(renderer , NULL);   
}


    // Setter for Bar color
    void BarGraph::setBarColor(SDL_Color color) {
        this->Bar_color = color;
    }

    // Getter for Bar color
    SDL_Color BarGraph::getBarColor() {
        return this->Bar_color;
    }

    // Setter for Bar colors array
    void BarGraph::setBarColorsArray(std::vector<SDL_Color> colors) {
        this->bar_colors_array = colors;
    }

    // Getter for Bar colors array
    std::vector<SDL_Color> BarGraph::getBarColorsArray() {
        return this->bar_colors_array;
    }
    
     
    // Setter for X-axis title
    void BarGraph::setXTitle(std::string title) {
        this->x_title = title;
    }

    // Getter for X-axis title
    std::string BarGraph::getXTitle() {
        return this->x_title;
    }

    // Setter for Y-axis title
    void BarGraph::setYTitle(std::string title) {
        this->y_title = title;
    }

    // Getter for Y-axis title
    std::string BarGraph::getYTitle() {
        return this->y_title;
    }


}

