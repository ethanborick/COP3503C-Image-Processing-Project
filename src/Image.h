#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//(1) Declare a Header struct
struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
};

struct Image {

    public:
        Header header;
        vector<Pixel> pixels;
        //Image();

};

Image ReadTGA(const string& path);
void WriteFile(Image& image, const string& outName);