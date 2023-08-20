
// SDL_Graph library version
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
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



typedef struct {
  int (*data)[2];// array pointer of 2 dimensional data 
  uint32_t size;
  SDL_Color Bar_color;//the color of graph bars
  SDL_Color Text_color;
  SDL_Color background_color;//backgroung color
  uint8_t graphlines;
  const char* x_title;
  const char* y_title;
  SDL_Texture* graph_texture;
  int w,h;
} SDL_Graph;
#define SDL_GRAPH_STRUCT


int SDL_GetMaxX(SDL_Graph* b){
  int max=b->data[0][0];
  for(int i=0;i<b->size;i++){
     if(b->data[i][0]>max)
       max=b->data[i][0];
  }

  return max;
}

int SDL_GetMinX(SDL_Graph* b){
  int min=b->data[0][0];
  for(int i=0;i<b->size;i++){
     if(b->data[i][0]<min)
       min=b->data[i][0];
  }

  return min;
}

int SDL_GetMaxY(SDL_Graph* b){
  int max=0;
  for(int i=0;i<b->size;i++){
     if(b->data[i][1]>max)
       max=b->data[i][1];
  }

  return max;
}


int SDL_GetMinY(SDL_Graph* b){
  int min=b->data[0][1];
  for(int i=0;i<b->size;i++){
     if(b->data[i][1]<min)
       min=b->data[i][1];
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

#include"SDL_Pichart.c"
#ifndef SDL_PICHART_GRAPH_C_
  #error "SDL_Pichart.c file not found"
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
    SDL_SetError("SDL_DestroyGraph( SDL_BarGraph*) ERROR : SDL_BarGraph* -> NULL poninter passed ");
    return -1;
  }

    SDL_DestroyTexture(bar->graph_texture);
    bar=NULL;

    return 0;
}


void SDL_GraphQuit(){
#ifdef SDL_TTF_H_
  TTF_CloseFont(graph_font);
#endif
}