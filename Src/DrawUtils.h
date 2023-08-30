#pragma once

#include <tgaimage.h>

struct Vector2 {
    Vector2(int x, int y) : x(x), y(y) {
    }
    int x;
    int y;
};

class Utils {
public:
    static void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
        bool steep = false;
        if (std::abs(x0-x1)<std::abs(y0-y1)) {
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }
        if (x0>x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        int dx = x1-x0;
        int dy = y1-y0;
        int derror2 = std::abs(dy)*2;
        int error2 = 0;
        int y = y0;
        for (int x=x0; x<=x1; x++) {
            if (steep) {
                image.set(y, x, color);
            } else {
                image.set(x, y, color);
            }
            error2 += derror2;

            if (error2 > dx) {
                y += (y1>y0?1:-1);
                error2 -= dx*2;
            }
        }
    }

    static void line(Vector2 t0, Vector2 t1, TGAImage &image, TGAColor color) {
        line(t0.x, t0.y, t1.x, t1.y, image, color);
    }

    static void triangle(Vector2 t0, Vector2 t1, Vector2 t2, TGAImage &image, TGAColor color) {
        line(t0, t1, image, color);
        line(t1, t2, image, color);
        line(t2, t0, image, color);
    }
private:
};