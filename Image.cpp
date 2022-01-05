#include "Image.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;
using namespace std;

void Image::darken() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s -= 0.1;
            if (pixel.s < 0) {
                pixel.s = 0; 
            }
        }
    }       
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s -= amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::illinify() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            if (pixel.h <= 293.5 && pixel.h > 113.5) {
                pixel.h = 216;
            }
            else {
                pixel.h = 11;
            }
        }
    }
}

void Image::lighten() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }        
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }        
}

void Image::rotateColor(double degrees) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.h += degrees;
            if (pixel.h > 360) {
                pixel.h -= 360;
            }  
            if (pixel.h < 0) {
                pixel.h += 360;
            } 
        }
    }
}

void Image::saturate() {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s += 0.1;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }       
    }
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < this->width(); x++) {
        for (unsigned y = 0; y < this->height(); y++) {
            HSLAPixel & pixel = this->getPixel(x, y);
            pixel.s += amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }       
        }
    }
}  

void Image::scale(double factor) {
    Image oldImage = Image(*this); // copy and store this image
    unsigned newWidth = width() * factor;
    unsigned newHeight = height() * factor;
    resize(newWidth, newHeight); // resize this image

    for (unsigned x = 0; x < newWidth; x ++) {
        for (unsigned y = 0; y < newHeight; y ++) {
            HSLAPixel & newPixel = this->getPixel(x,y);
            HSLAPixel & oldPixel = oldImage.getPixel(x/factor, y/factor);
            newPixel = oldPixel;
        }
    }
}

void Image::scale(unsigned w, unsigned h) {
    double factor = (double)(std::max(w, h)/std::max(this->width(), this->height()));
    scale(factor);
}