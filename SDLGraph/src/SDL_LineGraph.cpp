#ifndef SDL_LINE_GRAPH_C_
   #define SDL_LINE_GRAPH_C_
#endif


#include "SDL_Graph.cpp"
/**
 * creates a line graph into a SDL_Texture
 * 
 * This function takes input a SDL_Renderer* and SDL_Graph* as 
 * as arguments , then this will create the whole texture into
 * and stores its address into SDL_Graph->t variable 
 * The created texture is SDL_TEXTUREACCESS_STATIC 
 * 
 * when done with SDL_Graph* , use SDL_DestroyGraph() to dispose it
 * 
 * \param ren pointer to the SDL_Renderer* 
 * \param bar pointer to SDL_Graph , filled with Line graph in the form of SDL_Texture
 * \returns returns 0 if succesfull , or -1 on error
 * 
 * \since This function is available since SDL_Graph 1.0.0
*/

int SDL_CreateLineGraph(SDL_Renderer* ren , SDL_Graph* bar){
     if(bar==NULL){
    SDL_SetError("SDL_CreateLineGraph(... , SDL_BarGraph*) ERROR : SDL_BarGraph* -> NULL poninter passed ");
    return -1;
  }

  if(ren==NULL){
    SDL_SetError("SDL_CreateLineGraph(... , SDL_BarGraph*) ERROR : SDL_Renderer* -> NULL poninter passed ");
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

int x_pix=(bar->w-40)/x_max;
int y_pix=(bar->h-40)/y_max;

SDL_Color c=bar->dataset_array->Bar_color;

SDL_Dataset* d=NULL;
for(int j=0; j<bar->size; j++){
  d=&bar->dataset_array[j];
 c=d->Bar_color;
 SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
 int tmpx,tmpy , tmx,tmy;

for(int i=0;i<d->size-1;i++){
   tmpx=20+(d->data[i][0]*x_pix);
   tmpy=(d->data[i][1]*y_pix);
   tmpy=(bar->h-20)-tmpy;

   tmx=20+(d->data[i+1][0]*x_pix);
   tmy=(d->data[i+1][1]*y_pix);
   tmy=(bar->h-20)-tmy;
  SDL_RenderDrawLine(ren,tmpx , tmpy , tmx , tmy);
}

}
#ifdef SDL_TTF_H_
SDL_Rect r;
SDL_Color black={0,0,0,255};
 // code for renderig font
 if(graph_font!=NULL){
   SDL_Surface* sur;
   SDL_Texture* tex;
  
  if( bar->x_title!=NULL && strlen(bar->x_title)>0){
  //creating and rendering x title 
   sur=TTF_RenderUTF8_Blended(graph_font ,bar->x_title,black);
   if(sur==NULL){
    SDL_Log("SDL_CreateLineGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
    return -1;
   }
   tex=SDL_CreateTextureFromSurface(ren , sur);

   if(tex==NULL){
    SDL_Log("SDL_CreateLineGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
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

  if(bar->y_title!=NULL &&  strlen(bar->y_title)>0){
   //creating and rendering x title 
   sur=TTF_RenderUTF8_Blended(graph_font ,bar->y_title,black);
   if(sur==NULL){
    SDL_Log("SDL_CreateLineGraph(..) : FATAL ERROR : FAILED TO LOAD SURFACE FROM FONT : %s",SDL_GetError());
    return -1;
   }
   
   tex=SDL_CreateTextureFromSurface(ren , sur);
   
   if(tex==NULL){
    SDL_Log("SDL_CreateLineGraph(..) : FATAL ERROR : FAILED TO LOAD TEXTURE FROM SURFACE : %s", SDL_GetError());
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
//setting renderer to default 
SDL_SetRenderTarget(ren , NULL);
    return 0;

}


/**
 * updates a line graph into a SDL_Texture
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

int SDL_UpdateLineGraph(SDL_Renderer* ren , SDL_Graph* bar){

    if(bar==NULL){
    SDL_Log("SDL_CreateLineGraph(... , SDL_Graph*) ERROR : SDL_BarGraph* -> NULL poninter passed ");
    return -1;
  }

  if(ren==NULL){
    SDL_Log("SDL_CreateLineGraph(... , SDL_Graph*) ERROR : SDL_Renderer* -> NULL poninter passed ");
    return -1;
  }

   
   if(bar->graph_texture==NULL){
    SDL_Log("\n SDL_UpdateLineGraph(....) : ERROR : SDL_Graph* doesnt contain graph_texture : SDL_Graph* -> graph_texture is NULL ");
    return -1;
   }
   

   if(bar->x_title_texture==NULL || bar->y_title_texture==NULL){
     SDL_Log("\n SDL_UpdateLineGraph(....) : ERROR : SDL_Graph* doesnt contain title texture : SDL_Graph* -> x_title_texture is NULL or y_title_texture is NULL  ");
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

int x_pix=(bar->w-40)/x_max;
int y_pix=(bar->h-40)/y_max;

SDL_Color c=bar->dataset_array->Bar_color;

SDL_Dataset* d=NULL;
for(int j=0; j<bar->size; j++){
  d=&bar->dataset_array[j];
 c=d->Bar_color;
 SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
 int tmpx,tmpy , tmx,tmy;

for(int i=0;i<d->size-1;i++){
   tmpx=20+(d->data[i][0]*x_pix);
   tmpy=(d->data[i][1]*y_pix);
   tmpy=(bar->h-20)-tmpy;

   tmx=20+(d->data[i+1][0]*x_pix);
   tmy=(d->data[i+1][1]*y_pix);
   tmy=(bar->h-20)-tmy;
  SDL_RenderDrawLine(ren,tmpx , tmpy , tmx , tmy);
}

}

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
}





