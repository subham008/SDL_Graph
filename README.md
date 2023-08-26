# SDL_Graph 1.1.0
SDL_Graph is a extension to SDL library , it is able to render bar and line graphs ,its easy to use , no need to think about architecture , as it is not compiled you just have to  add this files to your desired directory and include this files from there 

HOW TO INSTALL
this is a source file so just need to download the files
SDL_Graph.h the SDL_Graph header file
SDL_BarGraph.c the source to SDL_CreateBarGraph(...) function
SDL_LineGraph.c the source to SDL_CreateLineGraph(...) function

This above files are source so you should place this file in the same directory as your working directory

HOW TO COMPILE 
There is no special linker or anything to compile this , normally use SDL2 and SDL_ttf compile commands 

command is : gcc tect.c -o test -lSDL2 -lSDL2_ttf

*********WARNING**************
 Always include SDL_Graph.h after including SDL.h and SDL_ttf.h
 
For detailed information have a look at test.c file 

**********HOW TO USE**************

The SDL_Graph have two structs ,
SDL_Dataset and SDL_Graph

To render a graph first step is to make a SDL_Dataset by using function :
          SDL_CraeteDataset( SDL_Dataset*  ,int (*)[2] , int  , SDL_Color , SDL_Color* )
 Paraments:
 
 SDL_Dataset* --> pointer to the SDL_Dataset filled with datas
 int (*)[2]   --> pointer to the 2d array pointer where x and y data is stored 
 int          --> length of the data 
 SDL_Color    --> color of the graphs in SDL_Color 
 SDL_Color*   --> poiner to the SDL_Color array , pass the SDL_Color array pointer if you want to make each graph bar or line have diffrent colors or pass NULL

 EXAMPEL CODE :
 
 SDL_Color red={200,35,25,200};
 int d[][2]={ {0,4}, {1,10} ,{2,4},{3,7} ,{4,6},{5,8},{6,12},{7,9} ,{8 ,5},{9,8} }; // 2d array filled with x y data
 
  SDL_Dataset dataset;
  SDL_CreateDataset(&dataset[0] ,d, 10 , red, NULL);


 //SDL_Dataset is now created now it is ready to create graph

 graph is creating a SDL_Texture and rendering everything in that texture 

 After creating SDL_Dataset we have to create SDL_Graph

 To make SDL_Graph we have to use function :
        void SDL_CreateGraph(SDL_Graph* bar , SDL_Dataset* data ,uint32_t size, int w , int h )

 Paraments:
 SDL_Graph* --> pointyer to the SDL_Graph filled with graph datas
 SDL_Dataset* -> pointer to SDL_Dataset , which is you want to render as graph
 uint32_     --> number of dataset 
 int w      -->  width of the graph
 int h      --> height of the graph

 now we have created SDL_Graph too , and Now we will create graph by using functions  SDL_CreateBarGraph() or  SDL_CreateLineGraph();

for exampele we are using SDL_Bargraph  :
EXMPLE CODE :

SDL_Graph bar;
   SDL_CreateGraph(&bar , dataset , 2, 300, 200); // created   SDL_Graph
   bar.x_title="days";   // giving  x title
   bar.y_title="rainfall";    // giving  y title
   SDL_CreateBarGraph(renderer , &bar);   // creating Bar graph using this function
   SDL_Rect grect={50,10,bar.w,bar.h};    //SDL_Rect , where you want to render

 ...
 // and now in the main loop 
      SDL_RenderGraph(renderer , &bar ,&grect);

 // main loop end


 thats how you can rendr a graph
