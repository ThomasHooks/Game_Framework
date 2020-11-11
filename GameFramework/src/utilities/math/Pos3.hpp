#ifndef Pos3_HPP_
#define Pos3_HPP_


#include <assert.h>




template<class T>
struct Pos3 
{
	union
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T s, t, p; };
	};



	Pos3(const Pos3<T>& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}



	/// <summary>
	/// Calculates the dot product of this position and the given position
	/// </summary>
	/// <param name="other">The other position</param>
	/// <returns></returns>
	T dot(const Pos3<T>& other)
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}



	Pos3<T>& operator=(const Pos3<T>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}



	bool operator==(const Pos3<T>& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}



	bool operator==(T scalar) const
	{
		return x == scalar && y == scalar && z == scalar;
	}



	bool operator!=(const Pos3<T>& other) const
	{
		return x != other.x && y != other.y && z != other.z;
	}



	bool operator>(const Pos3<T>& other) const
	{
		return x > other.x && y > other.y && z > other.z;
	}



	bool operator>(T scalar) const
	{
		return x > scalar && y > scalar && z > scalar;
	}



	bool operator>=(const Pos3<T>& other) const
	{
		return x >= other.x && y >= other.y && z >= other.z;
	}



	bool operator>=(T scalar) const
	{
		return x >= scalar && y >= scalar && z >= scalar;
	}



	bool operator<(const Pos3<T>& other) const
	{
		return x < other.x&& y < other.y && z < other.z;
	}



	bool operator<(T scalar) const
	{
		return x < scalar&& y < scalar && z < scalar;
	}



	bool operator<=(const Pos3<T>& other) const
	{
		return x <= other.x && y <= other.y && z <= other.z;
	}



	bool operator<=(T scalar) const
	{
		return x <= scalar && y <= scalar && z <= scalar;
	}



	Pos3<T> operator+(const Pos3<T>& other) const
	{
		return Pos3<T>(x + other.x, y + other.y, z + other.z);
	}



	Pos3<T> operator+(T scalar) const
	{
		return Pos3<T>(x + scalar, y + scalar, z + scalar);
	}



	Pos3<T>& operator+=(const Pos3<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}



	Pos3<T>& operator+=(T scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}



	Pos3<T> operator-(const Pos3<T>& other) const
	{
		return Pos3<T>(x - other.x, y - other.y, z - other.z);
	}



	Pos3<T> operator-(T scalar) const
	{
		return Pos3<T>(x - scalar, y - scalar, z - scalar);
	}



	Pos3<T>& operator-=(const Pos3<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z *= other.z;
		return *this;
	}



	Pos3<T>& operator-=(T scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}



	Pos3<T> operator*(const Pos3<T>& other) const
	{
		return Pos3<T>(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}



	Pos3<T> operator*(T scalar) const
	{
		return Pos3<T>(x * scalar, y * scalar, z * scalar);
	}



	Pos3<T>& operator*=(const Pos3<T>& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}



	Pos3<T>& operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}



	Pos3<T> operator/(T scalar) const
	{
		assert(scalar != 0);
		return Pos3<T>(x / scalar, y / scalar, z / scalar);
	}



	Pos3<T>& operator/=(T scalar)
	{
		assert(scalar != 0);
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}



protected:

	Pos3()
		: x(0), y(0), z(0)
	{}



	Pos3(T xIn, T yIn, T zIn)
		: x(xIn), y(yIn), z(zIn)
	{}
}; 



struct Pos3D : public Pos3<double>
{
	Pos3D()
		: Pos3<double>(0.0, 0.0, 0.0)
	{}



	Pos3D(double xIn, double yIn, double zIn)
		: Pos3<double>(xIn, yIn, zIn)
	{}



	Pos3D(const Pos3<double> & other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
	}
};



struct Pos3F : public Pos3<float>
{
	Pos3F()
		: Pos3<float>(0.0f, 0.0f, 0.0f)
	{}



	Pos3F(float xIn, float yIn, float zIn)
		: Pos3<float>(xIn, yIn, zIn)
	{}



	Pos3F(const Pos3<float>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
	}
};



struct Pos3N : public Pos3<int>
{
	Pos3N()
		: Pos3<int>(0, 0, 0)
	{}



	Pos3N(int xIn, int yIn, int zIn)
		: Pos3<int>(xIn, yIn, zIn)
	{}



	Pos3N(const Pos3<int>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
	}
};


#endif



