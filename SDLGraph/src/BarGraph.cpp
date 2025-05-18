
#ifndef SDL_BAR_GRAPH_CPP
   #define SDL_BAR_GRAPH_CPP
#endif


#include "SDL_Graph.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include<set>

namespace SDL_Graph{
// Constructor for BarGraph
 BarGraph::BarGraph (SDL_Renderer* renderer , std::vector<Dataset> data, int w, int h  , TTF_Font* graph_font)
        : Graph(data, w, h) {
        if(renderer == NULL) {
            std::cerr<< "SDL_Graph::BarGraph::BargRph() ERROR : SDL_Renderer* -> NULL pointer passed " << std::endl;
            return;
        }

        if(data.empty()) {
          std::cerr<<  "SDL_Graph::BarGraph::BargRph() ERROR : Dataset array is empty "<<std::endl;
            return;
        }

        setDatasetArray(data); 
        setWidth(w);
        setHeight(h);
        setFlags(0);
        setFont(graph_font);

       setGraphTexture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, w, h));
       
       //creating graph first time
       updateGraph(renderer);

} // end of constructor

void BarGraph::updateGraph(SDL_Renderer* renderer) {
    
    if (!getGraphTexture()) {
        std::cerr << "BarGraph::updateGraph() ERROR: Graph texture is NULL." << std::endl;
        return;
    }

    SDL_SetRenderTarget(renderer, getGraphTexture());

    // Fill background
    SDL_Color bg = getBackgroundColor();
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);

    // Draw axes
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int margin = 40;
    int w = getWidth();
    int h = getHeight();
    SDL_RenderDrawLine(renderer, margin, margin, margin, h - margin); // Y axis
    SDL_RenderDrawLine(renderer, margin, h - margin, w - margin, h - margin); // X axis

    // Get data range
    int x_min = GetGraphMinX();
    int x_max = GetGraphMaxX();
    int y_min = GetGraphMinY();
    int y_max = GetGraphMaxY();
    if (x_max == x_min) x_max++;
    if (y_max == y_min) y_max++;

    // Gather all unique X values
    auto datasets = getDatasetArray();
    std::set<int> unique_xs;
    for (const auto& dataset : datasets) {
        for (const auto& point : dataset.getData()) {
            unique_xs.insert(point.first);
        }
    }
    std::vector<int> x_positions(unique_xs.begin(), unique_xs.end());
    int num_groups = x_positions.size();
    int num_datasets = datasets.size();

    // Calculate group and bar width
    double group_width = (w - 2 * margin) / double(num_groups ? num_groups : 1);
    double bar_width = group_width / (num_datasets ? num_datasets : 1);
    if (bar_width < 2) bar_width = 2;

    // Draw bars
for (size_t group = 0; group < x_positions.size(); ++group) {
    int x_val = x_positions[group];
    for (int d = 0; d < num_datasets; ++d) {
         auto& dataset = datasets[d];
        // Find if this dataset has a point at x_val
        auto it = std::find_if(dataset.getData().begin(), dataset.getData().end(),
                               [x_val](const std::pair<int, int>& p) { return p.first == x_val; });
        if (it != dataset.getData().end()) {
            int y_val = it->second;
            SDL_Color bar_color;
            // Priority: bar_colors_array > dataset color > default bar color
            if (!getBarColorsArray().empty() && d < getBarColorsArray().size()) {
                bar_color = getBarColorsArray()[d];
            } else {
                bar_color = dataset.getColor();
            }
            SDL_SetRenderDrawColor(renderer, bar_color.r, bar_color.g, bar_color.b, bar_color.a);

            int x = margin + int(group * group_width + d * bar_width);
            int y = h - margin - int((y_val - y_min) * (double(h - 2 * margin) / (y_max - y_min)));
            SDL_Rect bar_rect = { x, y, int(bar_width) - 1, h - margin - y };
            SDL_RenderFillRect(renderer, &bar_rect);

            // Draw bar outline
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &bar_rect);
        }
    }
}

    // Draw X and Y axis labels
    if (getFont()) {
        SDL_Log("Drawing Text");

        SDL_Color textColor = getTextColor();
        SDL_Surface* xLabelSurface = TTF_RenderUTF8_Blended(getFont(), getXTitle().c_str(), textColor);
        SDL_Surface* yLabelSurface = TTF_RenderUTF8_Blended(getFont(), getYTitle().c_str(), textColor);

        if (xLabelSurface) {
            SDL_Texture* xLabelTexture = SDL_CreateTextureFromSurface(renderer, xLabelSurface);
            SDL_Rect xLabelRect = { (w - xLabelSurface->w) / 2, h - margin + 10, xLabelSurface->w, xLabelSurface->h };
            SDL_RenderCopy(renderer, xLabelTexture, NULL, &xLabelRect);
            SDL_FreeSurface(xLabelSurface);
            SDL_DestroyTexture(xLabelTexture);
        }
        if (yLabelSurface) {
            SDL_Texture* yLabelTexture = SDL_CreateTextureFromSurface(renderer, yLabelSurface);
            SDL_Rect yLabelRect = { 5, (h - yLabelSurface->h) / 2, yLabelSurface->w, yLabelSurface->h };
            SDL_RenderCopy(renderer, yLabelTexture, NULL, &yLabelRect);
            SDL_FreeSurface(yLabelSurface);
            SDL_DestroyTexture(yLabelTexture);
        }
    }

    SDL_SetRenderTarget(renderer, NULL);
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

