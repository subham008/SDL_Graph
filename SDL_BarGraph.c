
#ifndef SDL_BAR_GRAPH_C_
   #define SDL_BAR_GRAPH_C_
#endif

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


//now allocating texture
bar->graph_texture=SDL_CreateTexture(ren , SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET,bar->w , bar->h );

if(bar->graph_texture==NULL)
  return -1;

SDL_Color b=bar->background_color;


SDL_SetRenderDrawColor(ren , b.r , b.g , b.b , b.a);
SDL_SetRenderTarget(ren , bar->graph_texture);
SDL_RenderClear(ren);


// now printing x and y lines
SDL_SetRenderDrawColor(ren , 0,0,0,255);
SDL_RenderDrawLine(ren ,20 , 20 , 20 , bar->h-20);// rendering Y axis line
SDL_RenderDrawLine(ren ,20 , bar->h-20 ,bar->w-20 , bar->h-20);// rendering X axis line

int x_max=SDL_GetMaxX(bar);
int x_min=SDL_GetMinX(bar);

int y_max=SDL_GetMaxY(bar);
int y_min=SDL_GetMinY(bar);

int x_pix=(bar->w-40)/(x_max+1);
int y_pix=(bar->h-40)/y_max;

SDL_Color c=bar->Bar_color;

SDL_Rect r;
r.w=x_pix;


for(int i=0;i<bar->size; i++){
  SDL_SetRenderDrawColor(ren ,c.r,c.g,c.b,c.a );
  r.w=x_pix;
  r.h=y_pix*(bar->data[i][1]);
  r.y=(bar->h-20)-r.h;
  r.x=(bar->data[i][0])*x_pix;
  r.x+=20;
  SDL_RenderFillRect(ren , &r);

  r.y=r.y-1;
  r.x=r.x-1;
  r.w=r.w+1;

  SDL_SetRenderDrawColor(ren ,0,0,0,244 );
  SDL_RenderDrawRect(ren,&r);
 
}


#ifdef SDL_TTF_H_
SDL_Color black={0,0,0,255};
 // code for renderig font
 if(graph_font!=NULL){
   SDL_Surface* sur;
   SDL_Texture* tex;
  
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
   SDL_DestroyTexture(tex);
   
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
   SDL_DestroyTexture(tex);

 }


   
#endif

SDL_SetRenderTarget(ren , NULL);
    return 0;
}

