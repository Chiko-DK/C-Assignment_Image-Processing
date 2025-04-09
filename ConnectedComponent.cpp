
#include <vector>
#include <utility>

#include "ConnectedComponent.h"

// Constructor
ConnectedComponent::ConnectedComponent()
    : id(-1), pixelCount(0) {}

ConnectedComponent::ConnectedComponent(int id)
    : id(id), pixelCount(0) {}

// Destructor
ConnectedComponent::~ConnectedComponent() = default;

// Copy constructor
ConnectedComponent::ConnectedComponent(const ConnectedComponent& other)
    : id(other.id), pixelCount(other.pixelCount), pixels(other.pixels) {}

// Copy assignment operator
ConnectedComponent& ConnectedComponent::operator=(const ConnectedComponent& other) {
    if (this != &other) {
        id = other.id;
        pixelCount = other.pixelCount;
        pixels = other.pixels;
    }
    return *this;
}

// Move constructor
ConnectedComponent::ConnectedComponent(ConnectedComponent&& other)
    : id(other.id), pixelCount(other.pixelCount), pixels(std::move(other.pixels)) {
    other.id = -1;
    other.pixelCount = 0;
}

// Move assignment operator
ConnectedComponent& ConnectedComponent::operator=(ConnectedComponent&& other) {
    if (this != &other) {
        id = other.id;
        pixelCount = other.pixelCount;
        pixels = std::move(other.pixels);

        other.id = -1;
        other.pixelCount = 0;
    }
    return *this;
}


// Add a pixel to the component
void ConnectedComponent::addPixel(int x, int y) {
    pixels.emplace_back(x, y);
    ++pixelCount;
}
