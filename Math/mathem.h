/*
 mathem.h
 
 Some helpful functions.
 
 Created by Aivan on 29.06.14.
 Copyright AivanF. (c) 2014-2018
 
 This code is provided 'as-is', without any express or implied warranty.
 You may not hold the author liable.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:
 
 1	The origin of this code must not be misrepresented. You must not claim
 that you wrote the original software. When use the code, you must give
 appropriate credit, provide a link to this license, and indicate if changes were made.
 
 2	Altered source versions must be plainly marked as such, and must not be misrepresented
 as being the original software.
 
 3	This notice may not be removed or altered from any source distribution.
*/


#ifndef MATHEMH
#define MATHEMH

/// Stpres color for RGB or HSV.
// - Values:
// RGB = [0, 255]
// H = [0, 359]
// SV = [0, 100]
struct Color {
    unsigned int x = 0;// x = r = h
    unsigned int y = 0;// y = g = s
    unsigned int z = 0;// z = b = v
};

Color hsv2rgb(Color &hsv) {
    Color rgb;
    if (hsv.y) {
        hsv.x %= 360;
        int i = hsv.x / 60;
        float f = ((float)hsv.x / 60.0f) - (float)i;
        unsigned char c1 = (hsv.z * (100 - hsv.y)) * 0.0255f;
        unsigned char c2 = (hsv.z * (100 - hsv.y * f)) * 0.0255f;
        unsigned char c3 = (hsv.z * (100 - hsv.y * (1.0f-f))) * 0.0255f;
        hsv.z *= 2.55f;
        switch (i) {
            case 0:
                rgb.x = hsv.z;
                rgb.y = c3;
                rgb.z = c1;
                break;
            case 1:
                rgb.x = c2;
                rgb.y = hsv.z;
                rgb.z = c1;
                break;
            case 2:
                rgb.x = c1;
                rgb.y = hsv.z;
                rgb.z = c3;
                break;
            case 3:
                rgb.x = c1;
                rgb.y = c2;
                rgb.z = hsv.z;
                break;
            case 4:
                rgb.x = c3;
                rgb.y = c1;
                rgb.z = hsv.z;
                break;
            case 5:
                rgb.x = hsv.z;
                rgb.y = c1;
                rgb.z = c2;
                break;
        }
    } else {
        rgb.x = rgb.y = rgb.z = hsv.z;
    }
    return rgb;
}

int minimal(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

float minimal(float a, float b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

int maximal(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

float maximal(float a, float b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int abso(int a) {
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}

float abso(float a) {
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}

#endif // MATHEMH
