#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "PGMimageProcessor.h"
#include "ConnectedComponent.h"

#include <fstream>
#include <iostream>

TEST_CASE("PGMimageProcessor::extractComponents - basic and edge cases", "[extractComponents]") {
    PGMimageProcessor processor("Birds.pgm");

    SECTION("Threshold = 0 should extract all non-zero components") {
        int count = processor.extractComponents(0, 1);
        REQUIRE(count > 0);
    }

    SECTION("Threshold = 255 should likely extract very few or no components") {
        int count = processor.extractComponents(255, 1);
        REQUIRE(count >= 0);
    }

    SECTION("Minimum valid size filtering") {
        int count = processor.extractComponents(128, 10000); // overly high
        REQUIRE(count == 0);
    }

    SECTION("Negative threshold (invalid) - should be clamped or produce 0") {
        int count = processor.extractComponents(-1, 1);
        REQUIRE(count >= 0);
    }

    SECTION("Valid mid-range threshold") {
        int count = processor.extractComponents(128, 1);
        REQUIRE(count > 0);
        REQUIRE(processor.getComponentCount() == count);
    }
}

TEST_CASE("PGMimageProcessor::filterComponentsBySize - edge and invalid ranges", "[filterComponentsBySize]") {
    PGMimageProcessor processor("Birds.pgm");
    processor.extractComponents(128, 1);

    SECTION("Valid filtering range") {
        int remaining = processor.filterComponentsBySize(5, 500);
        REQUIRE(remaining <= processor.getComponentCount());
    }

    SECTION("Zero-size range - should remove all") {
        int remaining = processor.filterComponentsBySize(10000, 10000);
        REQUIRE(remaining == 0);
    }

    SECTION("Negative range - should be ignored or remove all") {
        int remaining = processor.filterComponentsBySize(-100, -1);
        REQUIRE(remaining == 0);
    }
}

TEST_CASE("PGMimageProcessor::writeComponents - output test", "[writeComponents]") {
    PGMimageProcessor processor("Birds.pgm");
    processor.extractComponents(128, 1);
    processor.filterComponentsBySize(5, 500);
    bool result = processor.writeComponents("output.pgm");
    REQUIRE(result == true);

    std::ifstream outfile("output.pgm");
    REQUIRE(outfile.good());
    std::string header;
    std::getline(outfile, header);
    REQUIRE(header == "P5"); // Ensure valid PGM header
    outfile.close();
}

TEST_CASE("PGMimageProcessor::getLargestSize and getSmallestSize - edge behavior", "[sizes]") {
    PGMimageProcessor processor("Birds.pgm");
    processor.extractComponents(128, 1);

    int largest = processor.getLargestSize();
    int smallest = processor.getSmallestSize();

    REQUIRE(largest >= smallest);
    REQUIRE(largest > 0);
    REQUIRE(smallest > 0);
}

TEST_CASE("PGMimageProcessor::printComponentData - does not crash or throw", "[printComponentData]") {
    PGMimageProcessor processor("Birds.pgm");
    processor.extractComponents(128, 1);
    REQUIRE(processor.getComponentCount() > 0);

    const auto& components = processor.getComponents();
    for (size_t i = 0; i < std::min(components.size(), size_t(3)); ++i) {
        REQUIRE_NOTHROW(processor.printComponentData(*components[i]));
    }
}
