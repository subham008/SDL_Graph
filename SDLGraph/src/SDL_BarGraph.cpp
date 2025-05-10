
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

      //rendering text
       if(getFont()==NULL)
         return;
       
      SDL_Surface* sur;
      SDL_Texture* tex;
  
     if( getXTitle().length() >0 ){
       //creating and rendering x title 
       sur=TTF_RenderUTF8_Blended(graph_font , getXTitle().c_str() , getTextColor() );
       if(sur==NULL){
         SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
         return;
         }

       tex=SDL_CreateTextureFromSurface(renderer , sur);

      if(tex==NULL){
        SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
       return;
      }
   
      r.x=(getWidth()-sur->w)/2;
      r.y=getHeight()-20;
      r.h=sur->h;
      r.w=sur->w;
      SDL_RenderCopy(renderer , tex , NULL,&r);
      SDL_FreeSurface(sur);
      bar->x_title_texture=tex;
    }

    if( bar->y_title!=NULL && strlen(bar->y_title)>0){
       //creating and rendering x title 
       sur=TTF_RenderUTF8_Blended(graph_font ,bar->y_title, getTextColor() );
      if(sur==NULL){
        SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
        return ;
       }
   
      tex=SDL_CreateTextureFromSurface(renderer , sur);
   
     if(tex==NULL){
        SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
       return;
     }
   
     r.x=10;
     r.y=0;
     r.h=sur->h;
     r.w=sur->w;
     SDL_RenderCopy(renderer , tex , NULL,&r);
     SDL_FreeSurface(sur);
     bar->y_title_texture=tex;
  }


  SDL_SetRenderTarget(renderer , NULL);     


} // end of constructor


  void  BarGraph::drawBarGraph(SDL_Renderer* renderer) {
        // Implementation for drawing the bar graph
        // This function can be customized based on your requirements
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
  }



/**
 * creates a bar graph into a SDL_Texture
 * 
 * This function takes input a SDL_Renderer* and SDL_Graph* as 
 * as arguments , then this will create the whole texture into
 * and stores its address into SDL_Graph->t variable 
 * The created texture is SDL_TEXTUREACCESS_STATIC 
 * 
 * when done with SDL_Graph* , use SDL_DestroyGraph() to dispose it
 * 
 * \param ren pointer to the SDL_Renderer* 
 * \param bar pointer to SDL_Graph , filled with graph in the form of SDL_Texture
 * \returns returns 0 if succesfull , or -1 on error
 * 
 * \since This function is available since SDL_Graph 1.0.0
*/

int SDL_CreateBarGraph(SDL_Renderer* ren ,SDL_Graph* bar){

  if(bar==NULL){
    SDL_SetError("SDL_CreaterBarGraph(... , SDL_BarGraph*) ERROR : SDL_BarGraph* -> NULL poninter passed ");
    return -1;
  }

  if(ren==NULL){
    SDL_SetError("SDL_CreateBarGraph(... , SDL_BarGraph*) ERROR : SDL_Renderer* -> NULL poninter passed ");
    return -1;
  }

if(bar->graph_texture!=NULL){
  SDL_DestroyTexture(bar->graph_texture);
}

//now allocating texture
bar->graph_texture=SDL_CreateTexture(ren , SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,bar->w , bar->h );

if(bar->graph_texture==NULL)
  return -1;

SDL_Color b=bar->background_color;


SDL_SetRenderDrawColor(ren , b.r , b.g , b.b , b.a);
SDL_SetRenderTarget(ren , bar->graph_texture);
SDL_RenderClear(ren);


// now printing x and y lines
SDL_SetRenderDrawColor(ren , 0,0,0,100);
SDL_RenderDrawLine(ren ,20 , 20 , 20 , bar->h-20);// rendering Y axis line
SDL_RenderDrawLine(ren ,20 , bar->h-20 ,bar->w-20 , bar->h-20);// rendering X axis line

int x_max=SDL_GetGraphMaxX(bar);
int x_min=SDL_GetGraphMinX(bar);

int y_max=SDL_GetGraphMaxY(bar);
int y_min=SDL_GetGraphMinY(bar);

int x_pix=(bar->w-40)/(x_max+1);
int y_pix=(bar->h-40)/y_max;

int xv_pix=x_pix/bar->size;


SDL_Color c;

SDL_Rect r;
r.w=x_pix;
SDL_Dataset* d=NULL;

for(int j=0 ; j<bar->size;j++){
   d=&bar->dataset_array[j];
   c=d->Bar_color;
  if(d->bar_colors_array==NULL)
      for(int i=0;i<d->size; i++){
          SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
          r.w=xv_pix;
          r.h=y_pix*(d->data[i][1]);
          r.y=(bar->h-20)-r.h;
          r.x=(d->data[i][0])*x_pix + (j*xv_pix);
          r.x+=20;
          SDL_RenderFillRect(ren , &r);

          r.y=r.y-1;
          r.x=r.x-1;
          r.w=r.w+1;

          SDL_SetRenderDrawColor(ren ,0,0,0,244 );
          SDL_RenderDrawRect(ren,&r);
}// end of i loop
  else
      for(int i=0;i<d->size; i++){
          c=d->bar_colors_array[i];
          SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
          r.w=xv_pix;
          r.h=y_pix*(d->data[i][1]);
          r.y=(bar->h-20)-r.h;
          r.x=(d->data[i][0])*x_pix + (j*xv_pix);
          r.x+=20;
          SDL_RenderFillRect(ren , &r);

          r.y=r.y-1;
          r.x=r.x-1;
          r.w=r.w+1;

          SDL_SetRenderDrawColor(ren ,0,0,0,244 );
          SDL_RenderDrawRect(ren,&r);
 
        }//end of i loop

}//end of j loop


#ifdef SDL_TTF_H_

SDL_Color black={0,0,0,255};
 // code for renderig font
 if(graph_font!=NULL){
   SDL_Surface* sur;
   SDL_Texture* tex;
  
  if( bar->x_title!=NULL && strlen(bar->x_title)>0){
  //creating and rendering x title 
   sur=TTF_RenderUTF8_Blended(graph_font ,bar->x_title,black);
   if(sur==NULL){
    SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
    return -1;
   }

   tex=SDL_CreateTextureFromSurface(ren , sur);

   if(tex==NULL){
    SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
    return -1;
   }
   
   r.x=(bar->w-sur->w)/2;
   r.y=bar->h-20;
   r.h=sur->h;
   r.w=sur->w;
   SDL_RenderCopy(ren , tex , NULL,&r);
   SDL_FreeSurface(sur);
   bar->x_title_texture=tex;
  }

  if( bar->y_title!=NULL && strlen(bar->y_title)>0){
   //creating and rendering x title 
   sur=TTF_RenderUTF8_Blended(graph_font ,bar->y_title,black);
   if(sur==NULL){
    SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
    return -1;
   }
   
   tex=SDL_CreateTextureFromSurface(ren , sur);
   
   if(tex==NULL){
    SDL_Log("SDL_CreateBarGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
    return -1;
   }
   
   r.x=10;
   r.y=0;
   r.h=sur->h;
   r.w=sur->w;
   SDL_RenderCopy(ren , tex , NULL,&r);
   SDL_FreeSurface(sur);
   bar->y_title_texture=tex;
  }
 }


   
#endif

SDL_SetRenderTarget(ren , NULL);
    return 0;
}



/**
 * updates a Bar graph into a SDL_Texture
 * 
 * This function takes input a SDL_Renderer* and SDL_Graph* as 
 * as arguments , then this will clear the whole texture and 
 * updates it with new data
 * 
 * when done with SDL_Graph* , use SDL_DestroyGraph() to dispose it
 * 
 * \param ren pointer to the SDL_Renderer* 
 * \param bar pointer to SDL_Graph , filled with Line graph in the form of SDL_Texture
 * \returns returns 0 if succesfull , or -1 on error
 * 
 * \since This function is available since SDL_Graph 1.0.0
*/



int SDL_UpdateBarGraph(SDL_Renderer* ren , SDL_Graph* bar){

    if(bar==NULL){
    SDL_Log("SDL_UpdateBarGraph(... , SDL_Graph*) ERROR : SDL_Graph* -> NULL poninter passed ");
    return -1;
  }

  if(ren==NULL){
    SDL_Log("SDL_UpdateBarGraph(... , SDL_Graph*) ERROR : SDL_Renderer* -> NULL poninter passed ");
    return -1;
  }

   
   if(bar->graph_texture==NULL){
    SDL_Log("\n SDL_UpdateBarGraph(....) : ERROR : SDL_Graph* doesnt contain graph_texture : SDL_Graph* -> graph_texture is NULL ");
    return -1;
   }
   

   if(bar->x_title_texture==NULL || bar->y_title_texture==NULL){
     SDL_Log("\n SDL_UpdateBarGraph(....) : ERROR : SDL_Graph* doesnt contain title texture : SDL_Graph* -> x_title_texture is NULL or y_title_texture is NULL  ");
   }
  SDL_Color b=bar->background_color;
  //setting graph texture as target renderer
SDL_SetRenderDrawColor(ren , b.r , b.g , b.b , b.a);
SDL_SetRenderTarget(ren , bar->graph_texture);
SDL_RenderClear(ren);

// now printing x and y lines
SDL_SetRenderDrawColor(ren , 0,0,0,255);
SDL_RenderDrawLine(ren ,20 , 20 , 20 , bar->h-20);// rendering Y axis line
SDL_RenderDrawLine(ren ,20 , bar->h-20 ,bar->w-20 , bar->h-20);// rendering X axis line

int x_max=SDL_GetGraphMaxX(bar);
int x_min=SDL_GetGraphMinX(bar);

int y_max=SDL_GetGraphMaxY(bar);
int y_min=SDL_GetGraphMinY(bar);

int x_pix=(bar->w-40)/(x_max+1);
int y_pix=(bar->h-40)/y_max;

int xv_pix=x_pix/bar->size;

SDL_Color c;
SDL_Rect r;

SDL_Dataset* d=NULL;

//graph rendering loops
for(int j=0 ; j<bar->size;j++){
   d=&bar->dataset_array[j];
   c=d->Bar_color;
  if(d->bar_colors_array==NULL)
      for(int i=0;i<d->size; i++){
          SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
          r.w=xv_pix;
          r.h=y_pix*(d->data[i][1]);
          r.y=(bar->h-20)-r.h;
          r.x=(d->data[i][0])*x_pix + (j*xv_pix);
          r.x+=20;
          SDL_RenderFillRect(ren , &r);

          r.y=r.y-1;
          r.x=r.x-1;
          r.w=r.w+1;

          SDL_SetRenderDrawColor(ren ,0,0,0,244 );
          SDL_RenderDrawRect(ren,&r);
}// end of i loop
  else
      for(int i=0;i<d->size; i++){
          c=d->bar_colors_array[i];
          SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
          r.w=xv_pix;
          r.h=y_pix*(d->data[i][1]);
          r.y=(bar->h-20)-r.h;
          r.x=(d->data[i][0])*x_pix + (j*xv_pix);
          r.x+=20;
          SDL_RenderFillRect(ren , &r);

          r.y=r.y-1;
          r.x=r.x-1;
          r.w=r.w+1;

          SDL_SetRenderDrawColor(ren ,0,0,0,244 );
          SDL_RenderDrawRect(ren,&r);
 
        }//end of i loop

}//end of j loop


#ifdef SDL_TTF_H_
if(graph_font!=NULL){
  SDL_Rect r;
  //rendering x_title texture 

SDL_QueryTexture(bar->x_title_texture ,NULL,NULL,&r.w,&r.h  );
r.x=(bar->w-r.w)/2;
r.y=bar->h-20;
SDL_RenderCopy(ren ,bar->x_title_texture , NULL,&r);

//rendering y_title texture 
SDL_QueryTexture(bar->y_title_texture ,NULL,NULL,&r.w,&r.h  );
r.x=10;
r.y=0;
SDL_RenderCopy(ren , bar->y_title_texture , NULL,&r);
}
#endif


SDL_SetRenderTarget(ren , NULL);
  return 0;


}//end of SDL_UpdateBarGraph



