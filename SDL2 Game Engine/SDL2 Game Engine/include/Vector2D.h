#pragma once
#include <iostream>

class Vector2D
{
public:
	float m_X;
	float m_Y;

	Vector2D();
	Vector2D(float p_X, float p_Y);

	Vector2D& Add(const Vector2D& p_Vector);
	Vector2D& Subtract(const Vector2D& p_Vector);
	Vector2D& Multiply(const Vector2D& p_Vector);
	Vector2D& Divide(const Vector2D& p_Vector);
	
	Vector2D& operator+=(const Vector2D& p_Vector);
	Vector2D& operator-=(const Vector2D& p_Vector);
	Vector2D& operator*=(const Vector2D & p_Vector);
	Vector2D& operator/=(const Vector2D& p_Vector);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

};

std::ostream& operator<<(std::ostream& p_Stream, const Vector2D& p_Vector);
Vector2D& operator+(Vector2D& p_V1, const Vector2D& p_V2);
Vector2D& operator-(Vector2D& p_V1, const Vector2D& p_V2);
Vector2D& operator*(Vector2D& p_V1, const Vector2D& p_V2);
Vector2D& operator/(Vector2D& p_V1, const Vector2D& p_V2);
