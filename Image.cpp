//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"




bool Image::loadRaw(string filename)
{
    return false;
}



void Image::filterRed()
{
    double average = 0.0;
    for (int i = 0; i < w * h; ++i)
    {
        average = (pixels[i].r+pixels[i].g+pixels[i].b)/3;
        pixels[i].r=average;
        pixels[i].b= 0;
        pixels[i].g = 0;

    }
}
void Image::filterGreen()
{
    double average = 0.0;
    for (int i = 0; i < w * h; ++i)
    {
        average = (pixels[i].r+pixels[i].g+pixels[i].b)/3;
        pixels[i].r=0;
        pixels[i].b= 0;
        pixels[i].g = average;

    }
}
void Image::filterBlue()
{
    double average = 0.0;
    for (int i = 0; i < w * h; ++i)
    {
        average = (pixels[i].r+pixels[i].g+pixels[i].b)/3;
        pixels[i].r=0;
        pixels[i].b= average;
        pixels[i].g = 0;

    }
}
void Image::greyScale()
{
      double average = 0.0;
    for (int i = 0; i < w * h; ++i)
{
    average = (pixels[i].r+pixels[i].g+pixels[i].b)/3;
      pixels[i].r=average;
      pixels[i].b= average;
      pixels[i].g = average;

    }
}


void Image::flipHorizontal()
{
    // Rgb hold this is here to hold 1 of the pixels values
    Rgb hold;
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w/2; x++){
            // Here will var hold saves first half of the width
            hold = pixels[y*w+x];
            // this here then takes second half put it where first half is replacing it
            pixels[y*w+x] = pixels[y*w+(w+1-x)];
            // Here then we take the where the second half was and place hold
            //Which hold the first half
            pixels[y*w+(w+1-x)] = hold;
        }
    }
}
void Image::flipVertically()
{
    // This is the same logic as flip Horizontal but changing
    // x to y axis --- y to x in the for loops
    //this time its w on the first loop while divide h in second loop

    Rgb hold;
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h/2; y++){
            // we hold the same pixels here
            hold = pixels[y*w+x];
            // we just change swaping pixels formula here
            pixels[y*w+x] = pixels[x+(h-1-y)*w];
            // same in here but with new formula
            pixels[x+(h-1-y)*w] = hold;
        }
    }
}
void Image::rotate90cw()
{

}
void Image::AdditionalFunction2()
{
    int nW = 1000, nH = 200;
    Rgb **newSize = new Rgb*[nH];
    for(int x = 0; x < nH; x++){
        newSize[x] = new Rgb[nW];
        for(int y = 0;y < nW; y++){
            newSize[x][y].r = 256;
            newSize[x][y].g = 256;
            newSize[x][y].b = 256;
        }
    }

    for(int x = 0; x < nH; x++)
        for(int y = 0;y < nW; y++)
            newSize[x][y] = newSize[x*this->h/nH][y*this->w/nW];

    pixels = *newSize;
    this->h = nH;
    this->w = nW;
}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

    for(int i = 0; i < h; i++){
        for(int x = 0; x < w/2; x++){
            pixels[i*w+x] = 0;
        }
    }
}


bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary|std::ios::in); // need to spec. binary & input mode for Windows users
    try {
        if (ifs.fail()) { throw("Can't open input file"); }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h];  // this will throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines if necessary until we get to the binary data

        unsigned char pixel_buffer[3]; // buffer to store one pixel, with three channels red,green and blue

        // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < (w * h); ++i) {
            ifs.read(reinterpret_cast<char *>(pixel_buffer), 3);
            this->pixels[i].r = pixel_buffer[0]; // / 255.f;
            this->pixels[i].g = pixel_buffer[1]; // / 255.f;
            this->pixels[i].b = pixel_buffer[2]; // / 255.f;
        }
        ifs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
    }
    return true;

}

bool Image::savePPM(string filename)
{
    if (this->w == 0 || this->h == 0) { fprintf(stderr, "Can't save an empty image\n"); return true; }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary|std::ios::out); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << this->w << " " <<  this->h << "\n255\n";

        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i <  this->w *  this->h; ++i) {
//            r = static_cast<unsigned char>(std::min(1.f,  this->pixels[i].r) * 255);
//            g = static_cast<unsigned char>(std::min(1.f,  this->pixels[i].g) * 255);
//            b = static_cast<unsigned char>(std::min(1.f,  this->pixels[i].b) * 255);
//            ofs << r << g << b;

            ofs.write(reinterpret_cast<char *>(&this->pixels[i].r),1);    // write 1 byte;
            ofs.write(reinterpret_cast<char *>(&this->pixels[i].g),1);    // write 1 byte;
            ofs.write(reinterpret_cast<char *>(&this->pixels[i].b),1);    // write 1 byte;
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return true;
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}