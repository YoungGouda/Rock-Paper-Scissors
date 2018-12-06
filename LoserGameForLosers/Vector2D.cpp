#include "stdafx.h"
#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(const float x, const float y)
{
	this->x = x;
	this->y = y;

}
Vector2D& Vector2D::add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->divide(vec);
}


bool operator>=(const Vector2D & v1, const Vector2D & v2)
{
	return v1.x >= v2.x && v1.y >= v2.y;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;

}

