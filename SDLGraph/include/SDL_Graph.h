
// SDL_Graph library version
#define VERSION_MAJOR 1
#define VERSION_MINOR 1
#define VERSION_PATCH 0

//marking that SDL_Graph header file is included
#ifndef SDL_GRAPH_H_
   #define SDL_GRAPH_H_
#endif


#ifndef SDL_h_
  #include<SDL2/SDL.h>
#endif

#ifndef SDL_h_
  #include<SDL.h>
#endif


#ifndef STDINT_H_
  #include<stdint.h>
#endif

#ifndef _STDARG_H
  #include<stdarg.h>
#endif


#ifndef _STDBOOL_H
   #include<stdbool.h>
#endif



typedef struct{
     int (*data)[2];// array pointer of 2 dimensional data 
     uint32_t size;//number of data in the data*
     SDL_Color Bar_color;//the color of graph bars
     SDL_Color* bar_colors_array;
}SDL_Dataset;
#define SDL_DATASET_STRUCT

 void SDL_CreateDataset(SDL_Dataset* d , int (*data)[2] , uint32_t size, SDL_Color bar,SDL_Color* color_array ){
     d->Bar_color=bar;
     d->data=data;
     d->size=size;
     d->bar_colors_array=color_array;
 }


typedef struct{
  SDL_Dataset* dataset_array; //pointer to array of SDL_Dataset
  uint32_t size;//number of data in the SDL_Dataset*
  SDL_Color Text_color;//color of text
  SDL_Color background_color;//backgroung color
  bool graphlines;
  uint8_t flags;
  const char* x_title;
  const char* y_title;
  SDL_Texture* x_title_texture;
  SDL_Texture* y_title_texture;
  SDL_Texture* graph_texture;
   int w,h;
}SDL_Graph;
#define SDL_MULTIGRAPH_STRUCT


void SDL_CreateGraph(SDL_Graph* bar , SDL_Dataset* data ,uint32_t size, int w , int h ){
     bar->dataset_array=data;
     bar->size=size;
    
     SDL_Color* c;

     c=&bar->Text_color;
     c->r=0; c->g=0; c->b=0; c->a=255;
      
      c=&bar->background_color;
     c->r=255; c->g=255; c->b=255; c->a=255;

     bar->graphlines=true;
     bar->x_title=NULL;
     bar->y_title=NULL;
     bar->x_title_texture=NULL;
     bar->y_title_texture=NULL;
     bar->graph_texture=NULL;
     bar->w=w;
     bar->h=h;    
}





int SDL_GetMaxX(SDL_Dataset* d){
int max=d->data[0][0];

 for(int i=0;i<d->size;i++){
     if(d->data[i][0]>max)
       max=d->data[i][0];
  }

  return max;
}


int SDL_GetGraphMaxX(SDL_Graph* b){
  int max=SDL_GetMaxX(&b->dataset_array[0]);
  SDL_Dataset* d;
  for(int i=0;i<b->size;i++){
    d=&b->dataset_array[i];
    int m=SDL_GetMaxX(d);
   if(max<m)
     max=m;
  }//end of for loop
  return max;
}


int SDL_GetMinX(SDL_Dataset* b){
  int min=b->data[0][0];
  for(int i=0;i<b->size;i++){
     if(b->data[i][0]<min)
       min=b->data[i][0];
  }

  return min;
}


int SDL_GetGraphMinX(SDL_Graph* b){
int min=SDL_GetMinX(&b->dataset_array[0]);

 SDL_Dataset* d;
 for(int i=1;i<b->size;i++){
     d=&b->dataset_array[i];
     int m=SDL_GetMinX(d);
     if(min>m)
       min=m;
  }

  return min;
}



int SDL_GetMaxY(SDL_Dataset* b){
  int max=0;
  for(int i=0;i<b->size;i++){
     if(b->data[i][1]>max)
       max=b->data[i][1];
  }

  return max;
}

int SDL_GetGraphMaxY(SDL_Graph* b){
int max=SDL_GetMaxY(&b->dataset_array[0]);
SDL_Dataset* d;
 for(int i=1;i<b->size;i++){
     d=&b->dataset_array[i];
     int m=SDL_GetMaxY(d);
     if(max<m)
       max=m;
  }

  return max;
}



int SDL_GetMinY(SDL_Dataset* b){
  int min=b->data[0][1];
  for(int i=1;i<b->size;i++){
     if(b->data[i][1]<min)
       min=b->data[i][1];
  }

  return min;
}

int SDL_GetGraphMinY(SDL_Graph* b){
int min=SDL_GetMinY(&b->dataset_array[0]);

 SDL_Dataset* d;
 for(int i=0;i<b->size;i++){
    d=&b->dataset_array[i];
    int m=SDL_GetMinY(d);

    if(min>m)
      min=m;
  }

  return min;
}




#ifdef SDL_TTF_H_
TTF_Font* graph_font=NULL;


int SDL_setGraphFontStyle(const char* c){
  graph_font = TTF_OpenFontDPI(c,10,96,96);
  if(graph_font==NULL){
    SDL_Log("\n SDL_setGraphFontStyle(...) : ERROR : FAILED TO OPEN GIVEN FONT FILE : %s",TTF_GetError());
    return -1;
  }

 
  return 0;
}


#endif




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
