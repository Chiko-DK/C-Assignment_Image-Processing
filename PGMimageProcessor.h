#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <queue>

#include "ConnectedComponent.h"

class PGMimageProcessor {
private:
    int width, height;
    std::vector<unsigned char> image;
    std::vector<std::shared_ptr<ConnectedComponent> > components;

public:
    // Constructor and Destructor
    PGMimageProcessor();
    PGMimageProcessor(const std::string &filename);
    ~PGMimageProcessor();


    PGMimageProcessor(const PGMimageProcessor &other); // Copy constructor
    PGMimageProcessor &operator=(const PGMimageProcessor &other); // Copy assignment operator

    PGMimageProcessor(PGMimageProcessor &&other); // Move constructor
    PGMimageProcessor &operator=(PGMimageProcessor &&other); // Move assignment operator

    const std::vector<std::shared_ptr<ConnectedComponent>>& getComponents() const { return components; }

    // Core methods
    int extractComponents(unsigned char threshold, int minValidSize);
    int filterComponentsBySize(int minSize, int maxSize);
    bool writeComponents(const std::string &outFileName);
    int getComponentCount() const { return components.size(); }
    int getLargestSize() const;
    int getSmallestSize() const;
    void printComponentData(const ConnectedComponent &comp) const;

};


#endif