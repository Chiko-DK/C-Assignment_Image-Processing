
#include <vector>
#include <utility>

// ConnectedComponent.cpp
#include "ConnectedComponent.h"

// Default constructor
ConnectedComponent::ConnectedComponent()
    : id(-1), pixelCount(0) {}

// Parameterized constructor
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


// Modifiers
void ConnectedComponent::addPixel(int x, int y) {
    pixels.emplace_back(x, y);
    ++pixelCount;
}
