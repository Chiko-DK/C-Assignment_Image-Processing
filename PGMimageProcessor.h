#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <queue>

#include "ConnectedComponent.h"

class PGMimageProcessor {
private:
    int width, height;
    std::vector<unsigned char> image;
    std::vector<std::unique_ptr<ConnectedComponent> > components;

public:
    // Constructor and Destructor
    PGMimageProcessor();
    PGMimageProcessor(const std::string &filename);
    ~PGMimageProcessor() = default;


    PGMimageProcessor(const PGMimageProcessor &other); // Copy constructor
    PGMimageProcessor &operator=(const PGMimageProcessor &other); // Copy assignment operator

    PGMimageProcessor(PGMimageProcessor &&other); // Move constructor
    PGMimageProcessor &operator=(PGMimageProcessor &&other); // Move assignment operator

    int extractComponents(unsigned char threshold, int minValidSize);
    int filterComponentsBySize(int minSize, int maxSize);
    bool writeComponents(const std::string &outFileName);
    int getComponentCount() const { return components.size(); }
    int getLargestSize() const;
    int getSmallestSize() const;
    void printComponentData(const ConnectedComponent &comp) const;
};


#endif