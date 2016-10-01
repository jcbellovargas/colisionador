#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
{
	SetX(0);
	SetY(0);
}


Vector2::~Vector2()
{
}

Vector2::Vector2(float x, float y)
{
	SetX(x);
	SetY(y);
}

float Vector2::GetX()
{
	return _x;
}
float Vector2::GetY()
{
	return _y;
}
void Vector2::SetX(float x)
{
	_x = x;
}
void Vector2::SetY(float y)
{
	_y = y;
}
float Vector2::Magnitud()
{
	return sqrtf(MagnitudCuadrada());
}
float Vector2::MagnitudCuadrada()
{
	return _x*_x + _y*_y;
}
void Vector2::Normalizar()
{
	float a = Magnitud();
	_x / a;
	_y / a;
}
Vector2 Vector2::operator/(const float a) const
{
	return Vector2(_x / a, _y / a);
}

Vector2& Vector2::operator/=(const float a)
{
	this->_x / a;
	this->_y / a;
	return *this;
}

Vector2& Vector2::operator*=(const float a)
{
	this->_x * a;
	this->_y * a;
	return *this;
}

Vector2 Vector2::operator*(const float a) const
{
	return Vector2(_x * a, _y * a);
}

Vector2 Vector2::operator+(const Vector2& vector) const
{
	return Vector2(_x + vector._x, _y + vector._y);
}


Vector2& Vector2::operator+=(const Vector2& vector)
{
	this->_x += vector._x;
	this->_y += vector._y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& vector) const
{
	return Vector2(_x - vector._x, _y - vector._y);
}


Vector2& Vector2::operator-=(const Vector2& vector)
{
	this->_x -= vector._x;
	this->_y -= vector._y;
	return *this;
}

bool Vector2::operator==(const Vector2& vector)
{
	if (this->_x == vector._x && this->_y == vector._y)
		return true;
	return false;
}
bool Vector2::operator!=(const Vector2& vector)
{
	if (this->_x == vector._x && this->_y == vector._y)
		return false;
	return true;
}



