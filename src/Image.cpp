#include "Image.h"
#include <iostream>
using namespace std;


//Image::Image() {
//}

Image ReadTGA(const string& path) {
    ifstream file(path, ios::binary);
    Image image;
    Header header;
    if (!file.is_open()) {
        cout << "file not found" << endl;
        return image;
    }
    if (file.is_open()) {
        //(16) Read in each element of the .tga file
        file.read(reinterpret_cast<char*>(&header.idLength), 1);
        file.read(reinterpret_cast<char*>(&header.colorMapType), 1);
        file.read(reinterpret_cast<char*>(&header.dataTypeCode), 1);
        file.read(reinterpret_cast<char*>(&header.colorMapOrigin), 2);
        file.read(reinterpret_cast<char*>(&header.colorMapLength), 2);
        file.read(reinterpret_cast<char*>(&header.colorMapDepth), 1);
        file.read(reinterpret_cast<char*>(&header.xOrigin), 2);
        file.read(reinterpret_cast<char*>(&header.yOrigin), 2);
        file.read(reinterpret_cast<char*>(&header.width), 2);
        file.read(reinterpret_cast<char*>(&header.height), 2);
        file.read(reinterpret_cast<char*>(&header.bitsPerPixel), 1);
        file.read(reinterpret_cast<char*>(&header.imageDescriptor), 1);
        image.header = header;
        //(17) Get the image size by multiplying the image height and width
        int size = header.height * header.width;
        //(18) Create a for loop to read in all the pixels
        for (int i = 0; i < size; i++) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel.blue), 1);
            file.read(reinterpret_cast<char*>(&pixel.green), 1);
            file.read(reinterpret_cast<char*>(&pixel.red), 1);
            //(21) Push in each pixel to the pixel vector
            image.pixels.push_back(pixel);
        }
    }
    file.close();
    return image;
}

void WriteFile(Image& image, const string& outName) {
    //(22) Create a .tga file
    ofstream file(outName, ios::binary);
    //(23) Write out each .tga file header element
    file.write(reinterpret_cast<char*>(&image.header.idLength), 1);
    file.write(reinterpret_cast<char*>(&image.header.colorMapType), 1);
    file.write(reinterpret_cast<char*>(&image.header.dataTypeCode), 1);
    file.write(reinterpret_cast<char*>(&image.header.colorMapOrigin), 2);
    file.write(reinterpret_cast<char*>(&image.header.colorMapLength), 2);
    file.write(reinterpret_cast<char*>(&image.header.colorMapDepth), 1);
    file.write(reinterpret_cast<char*>(&image.header.xOrigin), 2);
    file.write(reinterpret_cast<char*>(&image.header.yOrigin), 2);
    file.write(reinterpret_cast<char*>(&image.header.width), 2);
    file.write(reinterpret_cast<char*>(&image.header.height), 2);
    file.write(reinterpret_cast<char*>(&image.header.bitsPerPixel), 1);
    file.write(reinterpret_cast<char*>(&image.header.imageDescriptor), 1);
    //(24) Create a for loop to write out each pixel
    for (int i = 0; i < image.header.width * image.header.height; i++) {
        file.write(reinterpret_cast<char*>(&(image.pixels[i]).blue), 1);
        file.write(reinterpret_cast<char*>(&(image.pixels[i]).green), 1);
        file.write(reinterpret_cast<char*>(&(image.pixels[i]).red), 1);
    }
    //(25) Write out each image pixel
    file.close();
}


