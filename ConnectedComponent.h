#ifndef CONNECTED_COMPONENT_H
#define CONNECTED_COMPONENT_H

#include <vector>

class ConnectedComponent {
    private:
        int id;
        int pixelCount;
        std::vector<std::pair<int, int>> pixels;
    
    public:
        ConnectedComponent();
        ConnectedComponent(int componentId);
        ~ConnectedComponent();

        ConnectedComponent(const ConnectedComponent& other); // Copy constructor
        ConnectedComponent& operator=(const ConnectedComponent& other); // Copy assignment operator

        ConnectedComponent(ConnectedComponent&& other); // Move constructor
        ConnectedComponent& operator=(ConnectedComponent&& other); // Move assignment operator
    
        void addPixel(int x, int y);
    
        int getSize() const { return pixelCount; }
        int getId() const { return id; }
        const std::vector<std::pair<int, int>>& getPixels() const { return pixels; }
};

#endif