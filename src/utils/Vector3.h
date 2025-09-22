#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
public:
    float x, y, z;
    
    // Constructors
    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& other);
    
    // Assignment operator
    Vector3& operator=(const Vector3& other);
    
    // Arithmetic operators with issues
    Vector3 operator+(const Vector3& other);  // Missing const
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar);  // Missing const
    Vector3 operator/(float scalar) const;
    
    // Compound assignment operators
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);
    
    // Comparison operators
    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other);  // Missing const
    
    // Vector operations with wrong signatures
    float length();  // Missing const
    float lengthSquared() const;
    void normalize();
    Vector3 normalized();  // Missing const
    
    // Dot and cross products
    float dot(const Vector3& other) const;
    Vector3 cross(Vector3& other);  // Wrong parameter type
    
    // Distance calculations
    float distance(const Vector3& other) const;
    float distanceSquared(Vector3 other);  // Wrong parameter type, missing const
    
    // Utility methods
    void set(float x, float y, float z);
    void zero();
    bool isZero();  // Missing const
    
    // Static methods
    static Vector3 zero();
    static Vector3 one();
    static Vector3 up();
    static Vector3 forward();
    
    // Interpolation
    static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
    static Vector3 slerp(Vector3 a, Vector3 b, float t);  // Wrong parameter types
    
    // String representation
    std::string toString();  // Missing const, missing include
};

// Global operators with issues
Vector3 operator*(float scalar, Vector3& vector);  // Wrong parameter type
Vector3 operator-(Vector3& vector);  // Unary minus, wrong parameter type

#endif