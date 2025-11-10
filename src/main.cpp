#include <iostream>
#include <fstream>
#include "Image.h"
using namespace std;

Image Multiply(Image& top, Image& bottom);
Image Subtract(Image& top, Image& bottom);
Image Screen(Image& top, Image& bottom);
Image Overlay(Image& top, Image& bottom);
Image addColor(Image& image, string color, int value);
Image scaleColor(Image& image, string color, int value);
Image Channel(Image& image, string color);
Image Combine(Image& blue, Image& green, Image& red);
Image Flip(Image& image);
bool isFileOpen(const string& path);

int main(int argc, char* argv[]) {
    vector<string> args;

    for (int i = 0; i < argc; i++) {
        args.push_back(argv[i]);
    }

    if (argc == 1 || args[1] == "--help") {
        cout << "Project 2: Image Processing, Summer 2025\n\n"
                "Usage:\n"
                "\t./project2.out [output] [firstImage] [method] [...]\n";
        return 0;
    }
    if (args[1].length() < 4 || args[1].substr(args[1].length() - 4, 4) != ".tga") {
        cout << "Invalid file name." << endl;
        return 0;
    }
    if (args[2].length() < 4 || args.size() < 3 || args[2].substr(args[2].length() - 4, 4) != ".tga") {
        cout << "Invalid file name." << endl;
        return 0;
    }
    if (!isFileOpen(args[2])) {
        cout << "File does not exist." << endl;
        return 0;
    }
    Image tracking_image = ReadTGA(args[2]);
    for (int i = 3; i < argc; i ++) {
        if (args[i] == "multiply" || args[i] == "subtract" ||
            args[i] == "overlay" || args[i] == "screen") {
            if (i + 2 > argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (args[i+1].length() < 4 || args[i+1].substr(args[i+1].length() - 4, 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            if (!isFileOpen(args[i+1])) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            Image second_image = ReadTGA(args[i+1]);
            if (args[i] == "multiply") {
                cout << "Attempting multiply." << endl;
                tracking_image = Multiply(tracking_image, second_image);
                cout << "Success." << endl;
            }
            if (args[i] == "subtract") {
                cout << "Attempting subtract." << endl;
                tracking_image = Subtract(tracking_image, second_image);
                cout << "Success." << endl;
            }
            if (args[i] == "overlay") {
                cout << "Attempting overlay." << endl;
                tracking_image = Overlay(tracking_image, second_image);
                cout << "Success." << endl;
            }
            if (args[i] == "screen") {
                cout << "Attempting screen." << endl;
                tracking_image = Screen(second_image, tracking_image);
                cout << "Success." << endl;
            }
            i++;
        }
        else if (args[i] == "addred" || args[i] == "addgreen" ||
                   args[i] == "addblue" || args[i] == "scalered" ||
                   args[i] == "scalegreen" || args[i] == "scaleblue") {
            if (i + 2 > argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            try {
                int value = stoi(args[i+1]);
                if (args[i] == "addred") {
                    cout << "Attempting addred." << endl;
                    tracking_image = addColor(tracking_image, "red", value);
                    cout << "Success." << endl;
                }
                if (args[i] == "addblue") {
                    cout << "Attempting addblue." << endl;
                    tracking_image = addColor(tracking_image, "blue", value);
                    cout << "Success." << endl;
                }
                if (args[i] == "addgreen") {
                    cout << "Attempting addgreen." << endl;
                    tracking_image = addColor(tracking_image, "green", value);
                    cout << "Success." << endl;
                }
                if (args[i] == "scalered") {
                    cout << "Attempting scalered." << endl;
                    tracking_image = scaleColor(tracking_image, "red", value);
                    cout << "Success." << endl;
                }
                if (args[i] == "scalegreen") {
                    cout << "Attempting scalegreen." << endl;
                    tracking_image = scaleColor(tracking_image, "green", value);
                    cout << "Success." << endl;
                }
                if (args[i] == "scaleblue") {
                    cout << "Attempting scaleblue." << endl;
                    tracking_image = scaleColor(tracking_image, "blue", value);
                    cout << "Success." << endl;
                }
                i++;
            }
            catch (invalid_argument &e) {
                cout << "Invalid argument, expected number." << endl;
                return 0;
            }
        }
        else if (args[i] == "onlyred") {
            tracking_image = Channel(tracking_image, "red");
        }
        else if (args[i] == "onlyblue") {
            tracking_image = Channel(tracking_image, "blue");
        }
        else if (args[i] == "onlygreen") {
            tracking_image = Channel(tracking_image, "green");
        }
        else if (args[i] == "combine") {
            if (i + 3 > argc) {
                cout << "Missing argument." << endl;
                return 0;
            }
            if (args[i+1].substr(args[i+1].length() - 4, 4) != ".tga" ||
                args[i+2].substr(args[i+2].length() - 4, 4) != ".tga") {
                cout << "Invalid argument, invalid file name." << endl;
                return 0;
            }
            if (!isFileOpen(args[i+1]) || !isFileOpen(args[i+2])) {
                cout << "Invalid argument, file does not exist." << endl;
                return 0;
            }
            Image second_image = ReadTGA(args[i+1]);
            Image third_image = ReadTGA(args[i+2]);
            cout << "Attempting combine." << endl;
            tracking_image = Combine(third_image, second_image, tracking_image);
            cout << "Success." << endl;
            i++;
            i++;
        }
        else if (args[i] == "flip") {
            if (i + 1 < argc && args[i+1] != "flip") {
                cout << "Missing argument." << endl;
                return 0;
            }
            cout << "Attempting flip." << endl;
            tracking_image = Flip(tracking_image);
            cout << "Success." << endl;
        }
        else {
            cout << "Invalid method name.";
            return 0;
        }
        WriteFile(tracking_image, args[1]);
    }


//    Image layer1 = ReadTGA("input/layer1.tga");
//    Image pattern1 = ReadTGA("input/pattern1.tga");
//    Image output1 = Multiply(layer1, pattern1);
//    WriteFile(output1, "output/part1.tga");
//
//
//    Image layer2 = ReadTGA("input/layer2.tga");
//    Image car = ReadTGA("input/car.tga");
//    Image output2 = Subtract(car, layer2);
//    WriteFile(output2, "output/part2.tga");
//
//    Image pattern2 = ReadTGA("input/pattern2.tga");
//    Image text = ReadTGA("input/text.tga");
//    Image mult = Multiply(layer1, pattern2);
//    Image output3 = Screen(mult, text);
//    WriteFile(output3, "output/part3.tga");
//
//    Image circles = ReadTGA("input/circles.tga");
//    Image mult2 = Multiply(layer2, circles);
//    Image output4 = Subtract(mult2, pattern2);
//    WriteFile(output4, "output/part4.tga");
//
//    Image output5 = Overlay(layer1, pattern1);
//    WriteFile(output5, "output/part5.tga");
//
//    Image new_car = addColor(car, "green", 200);
//    WriteFile(new_car, "output/part6.tga");
//
//    Image new_car_2 = scaleColor(car, "blue", 0);
//    Image new_car_3 = scaleColor(new_car_2, "red", 4);
//    WriteFile(new_car_3, "output/part7.tga");
//
//    Image redCar = Channel(car, "red");
//    Image blueCar = Channel(car, "blue");
//    Image greenCar = Channel(car, "green");
//    WriteFile(redCar, "output/part8_r.tga");
//    WriteFile(blueCar, "output/part8_b.tga");
//    WriteFile(greenCar, "output/part8_g.tga");
//
//    Image blue = ReadTGA("input/layer_blue.tga");
//    Image green = ReadTGA("input/layer_green.tga");
//    Image red = ReadTGA("input/layer_red.tga");
//    Image combined = Combine(blue, green, red);
//    WriteFile(combined, "output/part9.tga");
//
//    Image text2 = ReadTGA("input/text2.tga");
//    Flip(text2);
//    WriteFile(text2, "output/part10.tga");

    return 0;
}

Image Multiply(Image& top, Image& bottom) {
    Image final = top;
    for (int i = 0; i < top.pixels.size(); i++) {
        float norm_blue_top = static_cast<int>(top.pixels[i].blue) / 255.0f;
        float norm_green_top = static_cast<int>(top.pixels[i].green) / 255.0f;
        float norm_red_top = static_cast<int>(top.pixels[i].red) / 255.0f;
        float norm_blue_bottom = static_cast<int>(bottom.pixels[i].blue) / 255.0f;
        float norm_green_bottom = static_cast<int>(bottom.pixels[i].green) / 255.0f;
        float norm_red_bottom = static_cast<int>(bottom.pixels[i].red) / 255.0f;
        float new_blue_norm = norm_blue_top * norm_blue_bottom;
        float new_green_norm = norm_green_top * norm_green_bottom;
        float new_red_norm = norm_red_top * norm_red_bottom;
        float finalb = new_blue_norm * 255.0f + 0.5f;
        float finalg = new_green_norm * 255.0f + 0.5f;
        float finalr = new_red_norm * 255.0f + 0.5f;
        final.pixels[i].blue = static_cast<unsigned char>(finalb);
        final.pixels[i].green = static_cast<unsigned char>(finalg);
        final.pixels[i].red = static_cast<unsigned char>(finalr);
    }
    return final;
}

Image Subtract(Image& top, Image& bottom) {
    Image final = top;
    for (int i = 0; i < top.pixels.size(); i++) {
        int new_blue = static_cast<int>(top.pixels[i].blue) - static_cast<int>(bottom.pixels[i].blue);
        if (new_blue < 0) {
            new_blue = 0;
        }
        final.pixels[i].blue = static_cast<unsigned char>(new_blue);
        int new_green = static_cast<int>(top.pixels[i].green) - static_cast<int>(bottom.pixels[i].green);
        if (new_green < 0) {
            new_green = 0;
        }
        final.pixels[i].green = static_cast<unsigned char>(new_green);
        int new_red = static_cast<int>(top.pixels[i].red) - static_cast<int>(bottom.pixels[i].red);
        if (new_red < 0) {
            new_red = 0;
        }
        final.pixels[i].red = static_cast<unsigned char>(new_red);
    }
    return final;
}

Image Screen(Image& top, Image& bottom) {
    Image final = top;
    for (int i = 0; i < top.pixels.size(); i++) {
        float norm_blue_top = top.pixels[i].blue / 255.0f;
        float norm_green_top = top.pixels[i].green / 255.0f;
        float norm_red_top = top.pixels[i].red / 255.0f;
        float norm_blue_bottom = bottom.pixels[i].blue / 255.0f;
        float norm_green_bottom = bottom.pixels[i].green / 255.0f;
        float norm_red_bottom = bottom.pixels[i].red / 255.0f;
        final.pixels[i].blue = (1 - (1 - norm_blue_top) * (1 - norm_blue_bottom)) * 255.0f + 0.5f;
        final.pixels[i].green = (1 - (1 - norm_green_top) * (1 - norm_green_bottom)) * 255.0f + 0.5f;
        final.pixels[i].red = (1 - (1 - norm_red_top) * (1 - norm_red_bottom)) * 255.0f + 0.5f;
    }
    return final;
}

Image Overlay(Image& top, Image& bottom) {
    Image final = top;
    for (int i = 0; i < top.pixels.size(); i++) {
        float norm_blue_top = top.pixels[i].blue / 255.0f;
        float norm_green_top = top.pixels[i].green / 255.0f;
        float norm_red_top = top.pixels[i].red / 255.0f;
        float norm_blue_bottom = bottom.pixels[i].blue / 255.0f;
        float norm_green_bottom = bottom.pixels[i].green / 255.0f;
        float norm_red_bottom = bottom.pixels[i].red / 255.0f;
        if (norm_blue_bottom <= 0.5f) {
            final.pixels[i].blue = (2 * norm_blue_bottom * norm_blue_top) * 255.0f + 0.5f;
        }
        else {
            final.pixels[i].blue = (1 - 2 * (1 - norm_blue_top) * (1 - norm_blue_bottom)) * 255.0f + 0.5f;
        }
        if (norm_green_bottom <= 0.5f) {
            final.pixels[i].green = (2 * norm_green_bottom * norm_green_top) * 255.0f + 0.5f;
        }
        else {
            final.pixels[i].green = (1 - 2 * (1 - norm_green_top) * (1 - norm_green_bottom)) * 255.0f + 0.5f;
        }
        if (norm_red_bottom <= 0.5f) {
            final.pixels[i].red = (2 * norm_red_bottom * norm_red_top) * 255.0f + 0.5f;
        }
        else {
            final.pixels[i].red = (1 - 2 * (1 - norm_red_top) * (1 - norm_red_bottom)) * 255.0f + 0.5f;
        }
    }
    return final;
}

Image addColor(Image& image, string color, int value) {
    Image final = image;
    final.header = image.header;
    if (color == "green") {
        for (int i = 0; i < image.pixels.size(); i++) {
            int new_green = static_cast<int>(final.pixels[i].green) + value;
            if (new_green > 255) {
                new_green = 255;
            }
            final.pixels[i].green = static_cast<unsigned char>(new_green);
        }
    }
    if (color == "blue") {
        for (int i = 0; i < image.pixels.size(); i++) {
            int new_blue = static_cast<int>(final.pixels[i].blue) + value;
            if (new_blue > 255) {
                new_blue = 255;
            }
            final.pixels[i].blue = static_cast<unsigned char>(new_blue);
        }
    }
    if (color == "red") {
        for (int i = 0; i < image.pixels.size(); i++) {

            int new_red = static_cast<int>(final.pixels[i].red) + value;
            if (new_red > 255) {
                new_red = 255;
            }
            final.pixels[i].red = static_cast<unsigned char>(new_red);
        }
    }
    return final;
}

Image scaleColor(Image& image, string color, int value) {
    Image final = image;
    if (color == "green") {
        for (int i = 0; i < image.pixels.size(); i++) {
            int new_green = static_cast<int>(final.pixels[i].green) * value;
            if (new_green > 255) {
                new_green = 255;
            }
            if (new_green < 0) {
                new_green = 0;
            }
            final.pixels[i].green = static_cast<unsigned char>(new_green);
        }
    }
    if (color == "blue") {
        for (int i = 0; i < image.pixels.size(); i++) {
            int new_blue = static_cast<int>(final.pixels[i].blue) * value;
            if (new_blue > 255) {
                new_blue = 255;
            }
            if (new_blue < 0) {
                new_blue = 0;
            }
            final.pixels[i].blue = static_cast<unsigned char>(new_blue);
        }
    }
    if (color == "red") {
        for (int i = 0; i < image.pixels.size(); i++) {
            int new_red = static_cast<int>(final.pixels[i].red) * value;
            if (new_red > 255) {
                new_red = 255;
            }
            if (new_red < 0) {
                new_red = 0;
            }
            final.pixels[i].red = static_cast<unsigned char>(new_red);
        }
    }
    return final;
}

Image Channel(Image& image, string color) {
    Image newImage = image;
    if (color == "blue") {
        for (int i = 0; i < image.pixels.size(); i++) {
            unsigned char b = image.pixels[i].blue;
            newImage.pixels[i].green = b;
            newImage.pixels[i].red = b;
            newImage.pixels[i].blue = b;
        }
    }
    if (color == "green") {
        for (int i = 0; i < image.pixels.size(); i++) {
            unsigned char g = image.pixels[i].green;
            newImage.pixels[i].green = g;
            newImage.pixels[i].red = g;
            newImage.pixels[i].blue = g;
        }
    }
    if (color == "red") {
        for (int i = 0; i < image.pixels.size(); i++) {
            unsigned char r = image.pixels[i].red;
            newImage.pixels[i].green = r;
            newImage.pixels[i].red = r;
            newImage.pixels[i].blue = r;
        }
    }
    return newImage;
}

Image Combine(Image& blue, Image& green, Image& red) {
    Image newImage = blue;
    for (int i = 0; i < newImage.pixels.size(); i++) {
        newImage.pixels[i].green = green.pixels[i].green;
        newImage.pixels[i].red = red.pixels[i].red;
        newImage.pixels[i].blue = blue.pixels[i].blue;
    }
    return newImage;
}

Image Flip(Image& image) {
    Image flipped;
    flipped.header = image.header;
    flipped.pixels = image.pixels;
    for (int i = image.pixels.size() - 1; i >= 0; i--) {
        flipped.pixels[image.pixels.size()- i - 1] = image.pixels[i];
    }
    return flipped;
}

bool isFileOpen(const string& path) {
    ifstream file(path);
    if (file.is_open()) {
        return true;
    }
    else {
        return false;
    }
}