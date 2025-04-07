#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <vector>
#include <utility>


class ConnectedComponent {
    private:
        int id;
        int pixelCount;
        std::vector<std::pair<int, int>> pixels;
    
    public:
        ConnectedComponent(int componentId) : id(componentId), pixelCount(0) {}
    
        void addPixel(int x, int y) {
            pixels.emplace_back(x, y);
            ++pixelCount;
        }
    
        int getSize() const { return pixelCount; }
        int getId() const { return id; }
        const std::vector<std::pair<int, int>>& getPixels() const { return pixels; }
};

#endif