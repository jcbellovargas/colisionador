#pragma once
class Vector2
{
public:
	Vector2();
	~Vector2();
	Vector2(float x, float y);


	float GetX();
	float GetY();
	void SetX(float x);
	void SetY(float y);
	float Magnitud();
	float MagnitudCuadrada();
	void Normalizar();

	




	bool operator==(const Vector2& vector);
	bool operator!=(const Vector2& vector);
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const float other) const;
	Vector2 operator/(const float other) const;

	Vector2& operator/=(const float a);
	Vector2& operator*=(const float a);
	Vector2& operator+=(const Vector2& vector);
	Vector2& operator-=(const Vector2& vector);


private:
	float _x, _y;
	
};