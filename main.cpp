// main.cpp
#include <iostream>
#include <string>
#include <memory>
#include "PGMimageProcessor.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: findcomp [options] <inputPGMfile>\n";
        return 1;
    } else {
        
    }

    std::string inputFile;  // default = "" (no input file)
    int minValidSize = 1;   // default = 1
    int minSizeFilter = -1; // default = -1 (no filter)
    int maxSizeFilter = -1; // default = -1 (no filter)
    int threshold = 128; // default = 128 (midpoint of 0-255)
    bool printData = false;   // default = false (no print)
    std::string outputFile = "output.pgm";   // default = "" (no output file)

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-m" && i + 1 < argc) {
            minValidSize = std::stoi(argv[++i]);
        } else if (arg == "-f" && i + 2 < argc) {
            minSizeFilter = std::stoi(argv[++i]);
            maxSizeFilter = std::stoi(argv[++i]);
        } else if (arg == "-t" && i + 1 < argc) {
            threshold = std::stoi(argv[++i]);
        } else if (arg == "-p") {
            printData = true;
        } else if (arg == "-w" && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (arg[0] != '-') {
            inputFile = arg;
        }
    }

    if (inputFile.empty()) {
        std::cerr << "No input file provided.\n";
        return 1;
    }

    // Create processor and load image
    PGMimageProcessor processor(inputFile);
    

    // Extract connected components
    int count = processor.extractComponents(threshold, minValidSize);
    std::cout << "Extracted " << count << " components.\n";

    // Filter components by size if requested
    if (minSizeFilter != -1 && maxSizeFilter != -1) {
        int remaining = processor.filterComponentsBySize(minSizeFilter, maxSizeFilter);
        std::cout << "Filtered components. Remaining: " << remaining << "\n";
    }

    // Print component data if requested
    if (printData) {
        for (const auto& comp : processor.getComponents()) {
            processor.printComponentData(*comp);
        }
    }

    // Write components to output file if specified
    if (!outputFile.empty()) {
        if (processor.writeComponents(outputFile)) {
            std::cout << "Components written to " << outputFile << "\n";
        } else {
            std::cerr << "Failed to write to " << outputFile << "\n";
        }
    }

    return 0;
}
