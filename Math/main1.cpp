//
//  main.cpp
//  Math
//
//  Created by IV-an on 13.11.14.
//  Copyright (c) 2014 Альфа 3. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "string.h"
#include "mem.h"
#include "islepng.h"
#include "mathem.h"

using namespace std;
using namespace mem;
using namespace isle;

int delta;

void Mbegin() {
    delta = 0;
    cout << "Begin...\n";
}

void Mdo(double d) {
    if ((int)(d*10) > delta/10){
        delta = (int)(d*100);
        cout << "Done: " << delta << "%\n";
    }
}

void Mend() {
    Mdo(1.0);
    cout << "Finished.\n";
}

void MakeImage(const char name[], int width, int height, bool HSVorRGB) {
    Picture *img = new Picture(width, height);
    type_value p, q;
    p = 1;
    q = 1;
    Value *X, *Y;
    X = new Variable("X", &p);
    Y = new Variable("Y", &q);
    Value *P, *Q;
    //P = SetLongValueVars(5, new Expression(X, Y, 0), new Expression(X, Y, 2));// cout << "P: " << P->GetString() << "\n\n";
    P = SetLongValueVars(4, X, Y);
    Q = SetLongValueVars(4, X, Y);
    if (1 == 1){/// HSV
        Value *H, *V;
        H = SetLongValueVars(4, P, Q); cout << "H: " << H->GetString() << "\n\n";
        V = SetLongValueVars(3, P, Q); cout << "V: " << V->GetString() << "\n\n";
        Mbegin();
        for (int x = 0; x < width; x += 1){
            for (int y = 0; y < height; y += 1){
                p = 16 * ((double)x / width - 0.5);
                q = 16 * ((double)y / height - 0.5);
                Color hsv, rgb;
                //hsv.x = (int)(359 * (1 + sin(H->GetValue())) / 2);
                hsv.x = (((int)abso(H->GetValue()*50))%359);
                hsv.y = 100;
                hsv.z = (int)(60 + 40 * cos(V->GetValue()));
                rgb = hsvToRgb(hsv);
                int r, g, b;
                r = rgb.x;
                g = rgb.y;
                b = rgb.z;
                img->set_pixel(x, y, r, g, b, 255);
            }
            Mdo((double)x / width);
        }
        Mend();
    }else{/// RGB
        Value *R, *G, *B;
        R = SetLongValueVars(3, P, Q);
        G = SetLongValueVars(3, P, Q);
        B = SetLongValueVars(3, P, Q);
        for (int x = 0; x < width; x += 1){
            for (int y = 0; y < height; y += 1){
                p = 10 * (double)x / width;
                q = 10 * (double)y / height;
                int r, g, b;
                r = (int)(255 * (2 + sin(R->GetValue())) / 2);
                g = (int)(255 * (2 + sin(G->GetValue())) / 2);
                b = (int)(255 * (2 + sin(B->GetValue())) / 2);
                img->set_pixel(x, y, r, g, b, 255);
                //img->set_pixel(x, y, (int)(127 * (1 + Sin(-p * Pi * 3 + 4 * q * Pi))), 0, 0, 255);
            }
        }
    }
    img->save(name);
}


string IntToStr(int Int) {
    char* Str;
    int len = 0;
    int t = Int;
    while (t > 0) {
        t /= 10;
        len++;
    }
    if (t < 1) t = 1;
    Str = new char(len);
    len = 0;
    t = Int;
    while (t > 0) {
        int p = t%10;
        t /= 10;
        Str[len] = char('0' + p);
        len++;
    }
    //sprintf(Str, "%d", Int);
    return Str;
}

int StrToInt(char Str[]) {
    int k;
    sscanf(Str, "%d", &k);
    return k;
    
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    int width = 400;
    int height = 400;
    string part = "hey";
    for (int i = 10; i < 20; i++){
        string name = part + IntToStr(i) + ".png";
        MakeImage(name.c_str(), width, height, true);
        //cout << name << endl;
    }
    return 0;
}
