//
//  islepng.h
//  An abstraction for images manipultaions.
//  Uses LodePNG created by Lode Vandevenne.
//
//  Created by Aivan on 28.07.14.
//  Copyright (c) 2014 AivanF. All rights reserved.
//

#ifndef ISLEPNG
#define ISLEPNG

#include <iostream>
#include "lodepng.h"


namespace isle {
    /// Type for PNG image. All data in 1D array.
    typedef std::vector<unsigned char> picpng;
    
    /// Stores pixels data and
    class Picture {
    private:
        /// Canvas with raw data.
        picpng image;
        unsigned width, height;
        
    public:
        /// Sets vector with raw data.
        void set_image(picpng& img) {
            image = img;
        }
        
        /// Sets width and height.
        void set_size(int x, int y) {
            if (x > 0) width = x;
            if (y > 0) height = y;
        }
        /// Sets width.
        void set_width(int x) {
            if (x > 0) width = x;
        }
        /// Sets height.
        void set_height(int x) {
            if (x > 0) height = x;
        }
        
        /// Sets red component of pixel.
        void set_r(int x, int y, unsigned char r) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
                image[4 * width * y + 4 * x + 0] = r;
        }
        /// Sets green component of pixel.
        void set_g(int x, int y, unsigned char g) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
                image[4 * width * y + 4 * x + 1] = g;
        }
        /// Sets blue component of pixel.
        void set_b(int x, int y, unsigned char b) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
                image[4 * width * y + 4 * x + 2] = b;
        }
        /// Sets alpha component of pixel.
        void set_a(int x, int y, unsigned char a) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height))
                image[4 * width * y + 4 * x + 3] = a;
        }
        /// Sets all components of pixel.
        void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height)) {
                image[4 * width * y + 4 * x + 0] = r;
                image[4 * width * y + 4 * x + 1] = g;
                image[4 * width * y + 4 * x + 2] = b;
                image[4 * width * y + 4 * x + 3] = a;
            }
        }
        
        /// Returns vector with raw data.
        picpng get_image() {
            return (image);
        }
        
        /// Returns width of the canvas.
        int get_width() {
            return width;
        }
        /// Returns width of the canvas.
        int get_height() {
            return height;
        }
        
        /// Returns red component of pixel.
        int get_r(int x, int y) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height)) {
                return (int)(image[4 * width * y + 4 * x + 0]);
            } else {
                return 0;
            }
        }
        /// Returns green component of pixel.
        int get_g(int x, int y) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height)) {
                return (int)(image[4 * width * y + 4 * x + 1]);
            } else {
                return 0;
            }
        }
        /// Returns blue component of pixel.
        int get_b(int x, int y) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height)) {
                return (int)(image[4 * width * y + 4 * x + 2]);
            } else {
                return 0;
            }
        }
        /// Returns alpha component of pixel.
        int get_a(int x, int y) {
            if ((x >= 0) && (y >= 0) && (x < width) && (y < height)) {
                return (int)(image[4 * width * y + 4 * x + 3]);
            } else {
                return 0;
            }
        }
        
        // Resizes canvas and cleans it with white color.
        void clean() {
            image.resize(width * height * 4);
            for (unsigned y = 0; y < height; y++)
                for (unsigned x = 0; x < width; x++) {
                    image[4 * width * y + 4 * x + 0] = 255;
                    image[4 * width * y + 4 * x + 1] = 255;
                    image[4 * width * y + 4 * x + 2] = 255;
                    image[4 * width * y + 4 * x + 3] = 255;
                }
        }
        // Resizes canvas and cleans it with given color.
        void clean(char r, char g, char b, char a) {
            image.resize(width * height * 4);
            for (unsigned y = 0; y < height; y++)
                for (unsigned x = 0; x < width; x++) {
                    image[4 * width * y + 4 * x + 0] = r;
                    image[4 * width * y + 4 * x + 1] = g;
                    image[4 * width * y + 4 * x + 2] = b;
                    image[4 * width * y + 4 * x + 3] = a;
                }
        }
        
        /// Saves picture to a file.
        int save(const char* filename) {
            unsigned error = lodepng::encode(filename, get_image(), get_width(), get_height());
            if (error) {
                std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
                return error;
            } else {
                return 0;
            }
        }
        
        /// Loads picture from a file.
        int load(const char* filename) {
            picpng image;
            unsigned x, y;
            unsigned error = lodepng::decode(image, x, y, filename);
            set_image(image);
            set_size(x, y);
            if (error) {
                std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
                return error;
            } else {
                return 0;
            }
        }
        
        // Constructor
        Picture (int width, int height) {
            set_width(width);
            set_height(height);
            clean();
        }
    };
}

#endif // ISLEPNG


