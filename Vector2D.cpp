#include "Vector2D.h"

Vector2D::Vector2D() {
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float newX, float newY) {
    x = newX;
    y = newY;
}

Vector2D &Vector2D::operator+(const Vector2D &vector){
    x += vector.x;
    y += vector.y;
    return *this;
}

Vector2D &Vector2D::operator-(const Vector2D &vector) {
    x -= vector.x;
    y -= vector.y;

    return *this;
}

Vector2D &Vector2D::operator*(const Vector2D &vector) {
    x *= vector.x;
    y *= vector.y;

    return *this;
}

Vector2D &Vector2D::operator/(const Vector2D &vector) {
    x /= vector.x;
    y /= vector.y;

    return *this;
}

Vector2D &Vector2D::operator+=(const Vector2D &vector) {
    return *this + vector;
}

Vector2D &Vector2D::operator-=(const Vector2D &vector) {
    return *this - vector;
}

Vector2D &Vector2D::operator*=(const Vector2D &vector) {
    return *this * vector;
}

Vector2D &Vector2D::operator/=(const Vector2D &vector) {
    return *this / vector;
}

Vector2D &Vector2D::operator*(const int &i){
    x *= i;
    y *= i;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D &vector){
    stream<<"Vector2D "<<"("<<vector.x<<", "<<vector.y<<")"<<std::endl;
    return stream;
}