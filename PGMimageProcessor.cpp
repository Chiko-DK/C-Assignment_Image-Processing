#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>

//#include "ConnectedComponent.h"
#include "PGMimageProcessor.h"


// Constructor
PGMimageProcessor::PGMimageProcessor(const std::string &filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
    {
        std::cerr << "Failed top open file for read: " << filename << std::endl;
        return;
    }
    std::string line;
    ifs >> line >> std::ws;
    if (line != "P5")
    {
        std::cerr << "Malformed PGM file - magic is: " << line << std::endl;
        return;
    }
    while (getline(ifs, line))
    {
        //cout << line << endl;
        if (line[0] != '#') break;
    }
    std::istringstream iss(line);
    iss >> width >> height;
    //cout << "width, height = (" << width << "," << height << ")\n";

    if (!iss)
    {
        std::cerr << "Header not correct - unexpected image sizes found: " << line << std::endl;
        return;
    }
    int maxChan = 0;
    ifs >> maxChan >> std::ws;
    if (maxChan != 255)
    {
        std::cerr << "Max grey level incorect - found: " << maxChan << std::endl;
    }
    // start of binary block

    image.resize(width * height);
    ifs.read(reinterpret_cast<char*>(image.data()), image.size());

    if (!ifs)
    {
        std::cerr << "Failed to read binary block - read\n";
    }

    ifs.close();

}

// Destructor
PGMimageProcessor::~PGMimageProcessor() = default;

// Copy Constructor
PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &other)
    : width(other.width), height(other.height), image(other.image) {
    for (const auto &comp : other.components) {
        components.push_back(std::make_unique<ConnectedComponent>(*comp));
    }
}

// Copy Assignment Operator
PGMimageProcessor &PGMimageProcessor::operator=(const PGMimageProcessor &other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        image = other.image;
        components.clear();
        for (const auto &comp : other.components) {
            components.push_back(std::make_unique<ConnectedComponent>(*comp));
        }
    }
    return *this;
}

// Move Constructor
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&other)
    : width(other.width), height(other.height), image(std::move(other.image)), components(std::move(other.components)) {}

// Move Assignment Operator
PGMimageProcessor &PGMimageProcessor::operator=(PGMimageProcessor &&other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        image = std::move(other.image);
        components = std::move(other.components);
    }
    return *this;
}

int PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize) {
    std::vector<unsigned char> binImage = image;
    int id = 0;
    components.clear();

    auto getIndex = [this](int x, int y) { return y * width + x; };
    auto inBounds = [this](int x, int y) { return x >= 0 && x < width && y >= 0 && y < height; };

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = getIndex(x, y);
            if (binImage[index] >= threshold) {
                std::queue<std::pair<int, int>> q;
                auto component = std::make_unique<ConnectedComponent>(id);

                q.emplace(x, y);
                binImage[index] = 0;

                while (!q.empty()) {
                    auto [cx, cy] = q.front(); q.pop();
                    component->addPixel(cx, cy);

                    for (auto [dx, dy] : {std::pair{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                        int nx = cx + dx, ny = cy + dy;
                        if (inBounds(nx, ny)) {
                            int nIdx = getIndex(nx, ny);
                            if (binImage[nIdx] >= threshold) {
                                binImage[nIdx] = 0;
                                q.emplace(nx, ny);
                            }
                        }
                    }
                }

                if (component->getSize() >= minValidSize) {
                    components.push_back(std::move(component));
                    ++id;
                }
            }
        }
    }
    return components.size();
}

int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize) {
    std::vector<std::shared_ptr<ConnectedComponent>> filtered;
    for (auto &comp : components) {
        int size = comp->getSize();
        if (size >= minSize && size <= maxSize) {
            filtered.push_back(std::move(comp));
        }
    }
    components = std::move(filtered);
    return components.size();
}

bool PGMimageProcessor::writeComponents(const std::string &outFileName) {
    std::vector<unsigned char> outImage(width * height, 0);

    for (const auto &comp : components) {
        for (auto [x, y] : comp->getPixels()) {
            outImage[y * width + x] = 255;
        }
    }

    std::ofstream out(outFileName, std::ios::binary);
    if (!out.is_open()) return false;

    out << "P5\n" << width << " " << height << "\n255\n";
    out.write(reinterpret_cast<char *>(outImage.data()), outImage.size());
    return true;
}


int PGMimageProcessor::getLargestSize() const {
    int maxSize = 0;
    for (const auto &comp : components) {
        if (comp->getSize() > maxSize)
            maxSize = comp->getSize();
    }
    return maxSize;
}

int PGMimageProcessor::getSmallestSize() const {
    if (components.empty()) return 0;
    int minSize = components[0]->getSize();
    for (const auto &comp : components) {
        if (comp->getSize() < minSize)
            minSize = comp->getSize();
    }
    return minSize;
}

void PGMimageProcessor::printComponentData(const ConnectedComponent &comp) const {
    std::cout << "Component ID: " << comp.getId()
              << ", Pixel Count: " << comp.getSize() << "\n";
}


