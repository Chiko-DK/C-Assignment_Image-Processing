# Image Processing with Connected Components

## Overview

This program processes grayscale PGM (Portable GrayMap) images to detect 4-connected foreground components based on a specified intensity threshold. It can filter these components by size, print their information, and write them into an output image. The program is modular, testable, and includes unit tests using the Catch2 framework.

## File Descriptions

### **1. `PGMimageProcessor.h`**
- Header file for the PGMimageProcessor class.
- Handles image loading, component extraction, filtering, and writing.

### **2. `PGMimageProcessor.cpp`**
Implementation of PGMimageProcessor methods.

### **3. `ConnectedComponent.h`**
- Header file for the ConnectedComponent class.
- Stores data about each connected component.

### **4. `ConnectedComponent.cpp`**
Implementation of ConnectedComponent methods.

### **5. `main.cpp`**
- Driver file that interacts with the user.
- Processes command-line arguments, and uses the processor.

### **6. `test.cpp`**
- Contains unit tests for `PGMimageProcessor` methods.
- Use the Catch2 framework.

### **7. `Makefile`**
- Defines the build process for compiling the program.
- Ensures all source files are compiled correctly.
- Automates building of the main program and the unit test.

### **8. `README.md`**
- Provides an overview of the program.
- Explains the purpose of each file.
- Guides users on running the program.


## Usage Instructions

### **Compilation**
If using a `Makefile`, compile the program with:
```bash
make
```
and preset `test` function, to compile unit test cases, by writing:
```bash
make test
```
Use `clean` to delete files produced by the function above:
```bash
make clean
```
Otherwise, manually compile using:
```bash
g++ -o main main.cpp PGMimageProcessor.cpp ConnectedComponent.cpp
```
For the main file. And for the test case use:
```bash
g++ -o test test.cpp PGMimageProcessor.cpp ConnectedComponent.cpp
```

### **Running the Program**
Execute the program with the required arguments:
```bash
./main [options] <input_file>
```

#### **Arguments:**
- `<input_file>` : a valid PGM image
#### **Options:**
- `-m <int>` : the minimum size for valid components when creating connected components.
- `-f <int> <int>` : the minimum and maximum components sizes respectively to keep after filtering.
- `-t <int>` : the threshold for component detection.
- `-p <bool>` : True value will print all the data component detection, total number and the sizes of the smallest and largest components.
- `-w <string>` : define the name of the new PGM file where all retained component are written.

#### **Examples**
```bash
./main -m 2 -f 5 10000 -t 35 -p true -w output.pgm Birds.pgm
```
This will:
1. Read `Birds.pgm` which is the input file.
2. Extract all the components based on the given threshold of `35`.
3. Exclude any components less than the minimum valid size of `2`.
4. Filter out all the components which is not between the minimum `5` and maximum `10000` size.
5. `true` will print on the console all the component data as well as the total number and the sizes of the smallest and largest components.
6. Write all the available components to a valid PGM file `output.pgm`.

## Troubleshooting
- Ensure the input file exists and is in **PGM (P5) format**.
- Avoid having a threshold less than `10`, it might take longer to run.
- Ensure the output directory has write permissions.

---
**Author:** Chiko Kasongo
**Date:** 09/04/2025
