#ifndef SDL_GRAPH_CPP
  #define SDL_GRAPH_CPP

#include <SDL_Graph.hpp>
#include <stdexcept>

// Source defination for Dataset class

namespace SDL_Graph{

Dataset::Dataset(std::vector<std::pair<int,int>> data , SDL_Color color):data(data),color(color){}

void  Dataset::setData(std::vector<std::pair<int,int>> data) {
    this->data=data;
}

std::vector<std::pair<int,int>> Dataset::getData()  {
    return this->data;
 }

 void Dataset::setColor(SDL_Color color){
    this->color=color;
 }

 // Setter for width
void Graph::setWidth(int w) {
    this->width = w;
}

// Getter for width
int Graph::getWidth() {
    return this->width;
}

// Setter for height
void Graph::setHeight(int h) {
    this->height = h;
}

// Getter for height
int Graph::getHeight() {
    return this->height;
}

 SDL_Color Dataset::getColor(){
     return this->color;
 }


 int Dataset::getMaxX() {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty. Cannot determine maximum X value.");
    }

    int max = data[0].first; // Access the first element's X value
    for (const auto& point : data) {
        if (point.first > max) {
            max = point.first;
        }
    }
    return max;
}

int Dataset::getMinX() {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty. Cannot determine minimum X value.");
    }

    int min = data[0].first; // Access the first element's X value
    for (const auto& point : data) {
        if (point.first < min) {
            min = point.first;
        }
    }
    return min;
}


int Dataset::getMaxY() {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty. Cannot determine maximum Y value.");
    }

    int max = data[0].second; // Access the first element's Y value
    for (const auto& point : data) {
        if (point.second > max) {
            max = point.second;
        }
    }
    return max;
}


int Dataset::getMinY() {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty. Cannot determine minimum Y value.");
    }

    int min = data[0].second; // Access the first element's Y value
    for (const auto& point : data) {
        if (point.second < min) {
            min = point.second;
        }
    }
    return min;
}



// Source defination for Graph class



// Constructor for Graph class
Graph::Graph(std::vector<Dataset> data, int w, int h) 
    : dataset_array(data), graph_texture(nullptr), Text_color({0, 0, 0, 255}), background_color({255, 255, 255, 255}), flags(0) {
    this->width = w;
    this->height= h;
}

// Setter for graph texture
void Graph::setGraphTexture(SDL_Texture* texture) {
    if(this->graph_texture != nullptr) {
        SDL_DestroyTexture(this->graph_texture);
    }
    this->graph_texture = texture;
}

// Getter for graph texture
SDL_Texture* Graph::getGraphTexture() {
    return this->graph_texture;
}

// Setter for text color
void Graph::setTextColor(SDL_Color color) {
    this->Text_color = color;
}

// Getter for text color
SDL_Color Graph::getTextColor() {
    return this->Text_color;
}

// Setter for background color
void  Graph::setBackgroundColor(SDL_Color color) {
    this->background_color = color;
}

// Getter for background color
SDL_Color Graph::getBackgroundColor() {
    return this->background_color;
}

// Setter for flags
void Graph::setFlags(uint8_t flags) {
    this->flags = flags;
}

// Getter for flags
uint8_t Graph::getFlags() {
    return this->flags;
}


// Get the maximum X value from the dataset array
int Graph::GetGraphMaxX() {
    if (dataset_array.empty()) {
        throw std::runtime_error("Graph dataset array is empty. Cannot determine maximum X value.");
    }

    int max = dataset_array[0].getMaxX();
    for ( auto& dataset : dataset_array) {
        int currentMax = dataset.getMaxX();
        if (currentMax > max) {
            max = currentMax;
        }
    }
    return max;
}

// Get the minimum X value from the dataset array
int Graph::GetGraphMinX() {
    if (dataset_array.empty()) {
        throw std::runtime_error("Graph dataset array is empty. Cannot determine minimum X value.");
    }

    int min = dataset_array[0].getMinX();
    for ( auto& dataset : dataset_array) {
        int currentMin = dataset.getMinX();
        if (currentMin < min) {
            min = currentMin;
        }
    }
    return min;
}

// Get the maximum Y value from the dataset array
int Graph::GetGraphMaxY() {
    if (dataset_array.empty()) {
        throw std::runtime_error("Graph dataset array is empty. Cannot determine maximum Y value.");
    }

    int max = dataset_array[0].getMaxY();
    for ( auto& dataset : dataset_array) {
        int currentMax = dataset.getMaxY();
        if (currentMax > max) {
            max = currentMax;
        }
    }
    return max;
}

// Get the minimum Y value from the dataset array
int Graph::GetGraphMinY() {
    if (dataset_array.empty()) {
        throw std::runtime_error("Graph dataset array is empty. Cannot determine minimum Y value.");
    }

    int min = dataset_array[0].getMinY();
    for ( auto& dataset : dataset_array) {
        int currentMin = dataset.getMinY();
        if (currentMin < min) {
            min = currentMin;
        }
    }
    return min;
}


}



#endif