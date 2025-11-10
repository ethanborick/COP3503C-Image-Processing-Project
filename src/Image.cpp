#include "Image.h"
#include <iostream>
using namespace std;

Image ReadTGA(const string& path) {
    ifstream file(path, ios::binary);
    Image image;
    Header header;
    if (!file.is_open()) {
        cout << "file not found" << endl;
        return image;
    }
    if (file.is_open()) {
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
        int size = header.height * header.width;
        for (int i = 0; i < size; i++) {
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel.blue), 1);
            file.read(reinterpret_cast<char*>(&pixel.green), 1);
            file.read(reinterpret_cast<char*>(&pixel.red), 1);
            image.pixels.push_back(pixel);
        }
    }
    file.close();
    return image;
}

void WriteFile(Image& image, const string& outName) {
    ofstream file(outName, ios::binary);
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
    for (int i = 0; i < image.header.width * image.header.height; i++) {
        file.write(reinterpret_cast<char*>(&(image.pixels[i]).blue), 1);
        file.write(reinterpret_cast<char*>(&(image.pixels[i]).green), 1);
        file.write(reinterpret_cast<char*>(&(image.pixels[i]).red), 1);
    }
    file.close();
}


