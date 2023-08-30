#pragma once

#include <tgaimage.h>

#include<array>
#include<functional>
#include <algorithm>

struct Vector2 {
    Vector2(int x, int y) : x(x), y(y) {
    }
    Vector2() {}

    bool operator == (Vector2 value) {
        return (x == value.x) && (y == value.y);
    }

    int x = 0;
    int y = 0;
};  

class MoveByLine {
public:
    MoveByLine(Vector2 start, Vector2 stop) : _start(start), _stop(stop) {
        _pointOnLine =  _start;
        if (std::abs(_start.x - _stop.x) < std::abs(_start.y - _stop.y)) {
            std::swap(_start.x, _start.y);
            std::swap(_stop.x , _stop.y);
            _steep = true;
        }
        if (start.x > stop.x) {
            std::swap(_start.x, _stop.x);
            std::swap(_start.y, _stop.y);
        }

        _delta.x = _stop.x - _start.x;
        _delta.y = _stop.y - _start.y;
        
        _deltaError = std::abs(_delta.y)*2;            
    }

    Vector2 doNext() {
        Vector2 result = _pointOnLine;
        if (_steep) {
            std::swap(_pointOnLine.x, _pointOnLine.y);
        }
        _error += _deltaError;

        if (_error > _delta.x) {
            _pointOnLine.y += (_stop.y > _start.y ? 1 : -1);
            _error -= _delta.x*2;
        }        
        ++_pointOnLine.x;

        if (_steep) {
            std::swap(_pointOnLine.x, _pointOnLine.y);
        }

        return result;
    } 
private:
    Vector2 _start;
    Vector2 _stop;
    bool _steep = false;
    Vector2 _delta {};
    Vector2 _pointOnLine {};
    int _deltaError = 0;
    int _error = 0;
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

        std::array<Vector2, 3> points {t0, t1, t2};

        
        std::sort(begin(points), end(points), [](const auto& left, const auto& right){
            return left.y < right.y;
        });

        int deltaY = points[2].y - points[0].y;

        std::sort(begin(points), end(points), [](const auto& left, const auto& right){
            return left.x < right.x;
        });

        int deltaX = points[2].x - points[0].x;

        if (deltaY > deltaX) {
            std::sort(begin(points), end(points), [](const auto& left, const auto& right){
                return left.y < right.y;
            });
            MoveByLine bigLine {points[0], points[2]};
            MoveByLine lessLine {points[0], points[1]};
            for (int y = points[0].y; y <= points[2].y; y++) {
                Vector2 point1 = bigLine.doNext();
                Vector2 point2 = lessLine.doNext();
                if (point2 == points[1]) {
                    lessLine = {points[1], points[2]};
                }
                line(point1, point2, image, color);
            }
        } else {
            MoveByLine bigLine {points[0], points[2]};
            MoveByLine lessLine {points[0], points[1]};
            for (int x = points[0].x; x <= points[2].x; x++) {
                auto point1 = bigLine.doNext();
                auto point2 = lessLine.doNext();
                if (point2 == points[1]) {
                    lessLine = {points[1], points[2]};
                }
                line(point1, point2, image, color);
            }
        }



        
        

        

    }
private:
};