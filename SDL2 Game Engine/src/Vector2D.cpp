#include "../include/Vector2D.h"

Vector2D::Vector2D()
{
	m_X = 0;
	m_Y = 0;
}

Vector2D::Vector2D(float p_X, float p_Y)
{
	this->m_X = p_X;
	this->m_Y = p_Y;
}

Vector2D& Vector2D::Add(const Vector2D& p_Vector)
{
	this->m_X += p_Vector.m_X;
	this->m_X += p_Vector.m_Y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& p_Vector)
{
	this->m_X -= p_Vector.m_X;
	this->m_X -= p_Vector.m_Y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& p_Vector)
{
	this->m_X *= p_Vector.m_X;
	this->m_X *= p_Vector.m_Y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& p_Vector)
{
	this->m_X /= p_Vector.m_X;
	this->m_X /= p_Vector.m_Y;

	return *this;
}

Vector2D& operator+(Vector2D& p_V1, const Vector2D& p_V2)
{
	return p_V1.Add(p_V2);
}

Vector2D& operator-(Vector2D& p_V1, const Vector2D& p_V2)
{
	return p_V1.Subtract(p_V2);
}

Vector2D& operator*(Vector2D& p_V1, const Vector2D& p_V2)
{
	return p_V1.Multiply(p_V2);
}

Vector2D& operator/(Vector2D& p_V1, const Vector2D& p_V2)
{
	return p_V1.Divide(p_V2);
}

Vector2D& Vector2D::operator+=(const Vector2D& p_Vector)
{
	return this->Add(p_Vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& p_Vector)
{
	return this->Subtract(p_Vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& p_Vector)
{
	return this->Multiply(p_Vector);
}

Vector2D& Vector2D::operator/=(const Vector2D& p_Vector)
{
	return this->Divide(p_Vector);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->m_X *= i;
	this->m_Y *= i;

	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->m_X = 0;
	this->m_Y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& p_Stream, const Vector2D& p_Vector)
{
	p_Stream << "(" << p_Vector.m_X << "," << p_Vector.m_Y << ")";
	return p_Stream;
}