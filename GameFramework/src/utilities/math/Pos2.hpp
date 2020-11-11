#ifndef Pos2_H_
#define Pos2_H_


#include <assert.h> 




template<class T>
struct Pos2 
{
	union
	{
		struct { T x, y; };
		struct { T w, h; };
		struct { T u, v; };
	};



	Pos2(const Pos2<T> & other)
	{
		x = other.x;
		y = other.y;
	}



	/// <summary>
	/// Calculates the dot product of this position and the given position
	/// </summary>
	/// <param name="other">The other position</param>
	/// <returns></returns>
	T dot(const Pos2<T>& other)
	{
		return (x * other.x) + (y * other.y);
	}



	Pos2<T>& operator=(const Pos2<T>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
		return *this;
	}



	bool operator==(const Pos2<T>& other) const
	{
		return x == other.x && y == other.y;
	}



	bool operator==(T scalar) const
	{
		return x == scalar && y == scalar;
	}



	bool operator!=(const Pos2<T>& other) const
	{
		return x != other.x && y != other.y;
	}



	bool operator>(const Pos2<T>& other) const
	{
		return x > other.x && y > other.y;
	}



	bool operator>(T scalar) const
	{
		return x > scalar && y > scalar;
	}



	bool operator>=(const Pos2<T>& other) const
	{
		return x >= other.x && y >= other.y;
	}



	bool operator>=(T scalar) const
	{
		return x >= scalar && y >= scalar;
	}



	bool operator<(const Pos2<T>& other) const
	{
		return x < other.x&& y < other.y;
	}



	bool operator<(T scalar) const
	{
		return x < scalar&& y < scalar;
	}



	bool operator<=(const Pos2<T>& other) const
	{
		return x <= other.x && y <= other.y;
	}



	bool operator<=(T scalar) const
	{
		return x <= scalar && y <= scalar;
	}



	Pos2<T> operator+(const Pos2<T>& other) const
	{
		return Pos2<T>(x + other.x, y + other.y);
	}



	Pos2<T> operator+(T scalar) const
	{
		return Pos2<T>(x + scalar, y + scalar);
	}



	Pos2<T>& operator+=(const Pos2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}



	Pos2<T>& operator+=(T scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}



	Pos2<T> operator-(const Pos2<T>& other) const
	{
		return Pos2<T>(x - other.x, y - other.y);
	}



	Pos2<T> operator-(T scalar) const
	{
		return Pos2<T>(x - scalar, y - scalar);
	}



	Pos2<T>& operator-=(const Pos2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}



	Pos2<T>& operator-=(T scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}



	Pos2<T> operator*(T scalar) const
	{
		return Pos2<T>(x * scalar, y * scalar);
	}



	Pos2<T>& operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}



	Pos2<T> operator/(T scalar) const
	{
		assert(scalar != 0);
		return Pos2<T>(x / scalar, y / scalar);
	}



	Pos2<T>& operator/=(T scalar)
	{
		assert(scalar != 0);
		x /= scalar;
		y /= scalar;
		return *this;
	}



	protected:

		Pos2()
			: x(0), y(0)
		{}



		Pos2(T xIn, T yIn)
			: x(xIn), y(yIn)
		{}
};



struct Pos2D : public Pos2<double>
{
	Pos2D()
		: Pos2<double>(0.0, 0.0)
	{}



	Pos2D(double xIn, double yIn)
		: Pos2<double>(xIn, yIn)
	{}



	Pos2D(const Pos2<double>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
	}
};



struct Pos2F : public Pos2<float>
{
	Pos2F()
		: Pos2<float>(0.0f, 0.0f)
	{}



	Pos2F(float xIn, float yIn)
		: Pos2<float>(xIn, yIn)
	{}



	Pos2F(const Pos2<float>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
	}
};



struct Pos2N : public Pos2<int>
{
	Pos2N()
		: Pos2<int>(0, 0)
	{}



	Pos2N(int xIn, int yIn)
		: Pos2<int>(xIn, yIn)
	{}



	Pos2N(const Pos2<int>& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
	}
};


#endif



