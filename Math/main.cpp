//
//  main.cpp
//  Random abstract pictures generator.
//
//  Created by Aivan on 13.11.14.
//  Copyright (c) 2014 AivanF. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <cmath>

#include "mathem.h"
#include "islepng.h"
#include "mem.h"


using namespace std;
using namespace isle;
using namespace mem;


/// Keeps generating progress.
int delta;

/// Prints start.
void Mbegin() {
    delta = 0;
    cout << "Begin...\n";
}

/// Prints progress.
void Mdo(double d) {
    if ((int)(d * 10) > (delta / 10)) {
        delta = (int)(d * 100);
        cout << "Done: " << delta << "%\n";
    }
}

/// Prints completion.
void Mend() {
    Mdo(1.0);
    cout << "Finished.\n";
}


/// Creates deep expressions with given pointers.
void NewMany(type_value &p, type_value &q, type_value &t, Value **H, Value **V) {
    Value *X, *Y, *Z;
    X = new Variable("X", &p);
    Y = new Variable("Y", &q);
    Z = new Variable("Z", &t);
    
    Value *P, *Q;
    P = SetDeepValueVars(3, X, Y);
    Q = SetDeepValueVarsMany(6, X, Y, Z);
    *H = SetDeepValueVars(3, P, Q);
    *V = SetDeepValueVars(3, P, Q);
}


/// Calculates pixels values and saves the picture.
void MakeImageMany(const char name[], int width, int height,
                   type_value &p, type_value &q, type_value &t,
                   Value **H, Value **V) {
    Picture *img = new Picture(width, height);
    Color hsv, rgb;
    Mbegin();
    
    for (int x = 0; x < width; x += 1) {
        for (int y = 0; y < height; y += 1) {
            p = 4 * (double)x / width;
            q = 4 * (double)y / height;
//            p = 0.125 * cos(2 * Pi * p);
//            q = 0.125 * cos(2 * Pi * q);
            
//            hsv.x = (int)(359 * (1 + sin(H->GetValue())) / 2);
            hsv.x = (((int)abso((*H)->GetValue() * 50)) % 359);
            hsv.y = 100;
            hsv.z = (int)(60 + 40 * cos((*V)->GetValue()));
            
            rgb = hsv2rgb(hsv);
            int r, g, b;
            r = rgb.x;
            g = rgb.y;
            b = rgb.z;
            img->set_pixel(x, y, r, g, b, 255);
        }
        Mdo((double)x / width);
    }
    
    Mend();
    img->save(name);
    delete img;
}


/// Program entry point.
int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    type_value x = 0, y = 0, z = 1;
    Value *H = nullptr, *V = nullptr;
    bool shdo = true;
    
    cout << "Type a command index:\n* 1 - new small img\n* 2 - same but big img\n* 0 - exit\n";
    while (shdo) {
        int command = -1;
        cin >> command;
        switch (command) {
            case 0:{
                shdo = false;
            }break;
            case 1:{
                clearPool();
                NewMany(x, y, z, &H, &V);
                MakeImageMany("little.png", 256, 192, x, y, z, &H, &V);
                cout << H->GetString() << "\n";
            }break;
            case 2:{
                if (H != nullptr)
                    MakeImageMany("big.png", 640, 480, x, y, z, &H, &V);
            }break;
            case 3:{
                if (H != nullptr)
                    MakeImageMany("bigVery.png", 1440, 900, x, y, z, &H, &V);
            }break;
        }
    }
    
    clearPool();
    printCounts();
    return 0;
}
