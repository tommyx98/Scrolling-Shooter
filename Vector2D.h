#ifndef MAIN_CPP_VECTOR2D_H
#define MAIN_CPP_VECTOR2D_H

#include <iostream>

struct Vector2D{
    float x;
    float y;

    Vector2D();
    Vector2D(float newX, float newY);

    Vector2D& operator+(const Vector2D &vector);
    Vector2D& operator-(const Vector2D &vector);
    Vector2D& operator*(const Vector2D &vector);
    Vector2D& operator/(const Vector2D &vector);

    Vector2D& operator+=(const Vector2D &vector);
    Vector2D& operator-=(const Vector2D &vector);
    Vector2D& operator*=(const Vector2D &vector);
    Vector2D& operator/=(const Vector2D &vector);

    Vector2D& operator*(const int &i);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D &vector);
};

#endif //MAIN_CPP_VECTOR2D_H
