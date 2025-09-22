#include "Vector3.h"
#include <sstream>

// Default constructor
Vector3::Vector3() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(const Vector3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

Vector3& Vector3::operator=(const Vector3& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

// Missing const qualifier
Vector3 Vector3::operator+(const Vector3& other) {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

// Missing const qualifier
Vector3 Vector3::operator*(float scalar) {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(float scalar) const {
    if (scalar == 0.0f) {
        // Division by zero - undefined behavior
        return Vector3(0, 0, 0);
    }
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(float scalar) {
    if (scalar != 0.0f) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }
    // No else case - undefined behavior for division by zero
    return *this;
}

bool Vector3::operator==(const Vector3& other) const {
    // Floating point comparison without epsilon
    return x == other.x && y == other.y && z == other.z;
}

// Missing const qualifier
bool Vector3::operator!=(const Vector3& other) {
    return !(*this == other);
}

// Missing const qualifier
float Vector3::length() {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

void Vector3::normalize() {
    float len = length();
    if (len > 0.0f) {
        x /= len;
        y /= len;
        z /= len;
    }
    // No else case - zero vector remains zero
}

// Missing const qualifier
Vector3 Vector3::normalized() {
    Vector3 result = *this;
    result.normalize();
    return result;
}

float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Wrong parameter type
Vector3 Vector3::cross(Vector3& other) {
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vector3::distance(const Vector3& other) const {
    Vector3 diff = *this - other;
    return diff.length();
}

// Wrong parameter type and missing const
float Vector3::distanceSquared(Vector3 other) {
    Vector3 diff = *this - other;
    return diff.lengthSquared();
}

void Vector3::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::zero() {
    x = y = z = 0.0f;
}

// Missing const qualifier
bool Vector3::isZero() {
    // Exact comparison with floating point
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

// Static methods
Vector3 Vector3::zero() {
    return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::one() {
    return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::up() {
    return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::forward() {
    return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float t) {
    // No clamping of t parameter
    return a + (b - a) * t;
}

// Wrong parameter types
Vector3 Vector3::slerp(Vector3 a, Vector3 b, float t) {
    // Spherical interpolation not implemented correctly
    // Just doing linear interpolation instead
    return lerp(a, b, t);
}

// Missing const qualifier and include
std::string Vector3::toString() {
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ", " << z << ")";
    return oss.str();
}

// Global operators with wrong parameter types
Vector3 operator*(float scalar, Vector3& vector) {
    return vector * scalar;
}

Vector3 operator-(Vector3& vector) {
    return Vector3(-vector.x, -vector.y, -vector.z);
}