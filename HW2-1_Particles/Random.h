#ifndef RANDOM_H
#define RANDOM_H

#include <random>

/// <summary>
/// Simple wrapper for the standard C++ Random functions.
/// </summary>
class Random
{

private:

	/// <summary>
	/// Ensures that a variable seed is provided.
	/// </summary>
	Random()
	{
		srand((unsigned int)time(nullptr));
	}

	/// <summary>
	/// Member function for a random int range.
	/// </summary>
	int m_Range(int a, int b)
	{
		return rand() % (b - a + 1) + a;
	}

	/// <summary>
	/// Member function for a random float range.
	/// </summary>
	float m_Range(float a, float b, unsigned int n)
	{
		return (rand() % (n + 1)) * ((b - a) / n) + a;
	}

	/// <summary>
	/// Singleton accessor.
	/// </summary>
	static Random& Instance()
	{
		static Random instance;
		return instance;
	}

public:

	/// <summary>
	/// Returns a pseudorandom integer on an inclusive interval.
	/// </summary>
	static int Range(int a, int b)
	{
		// Handle equality edge case.
		if (a == b) return a;

		// Handle negative difference edge case.
		if (a > b) return Instance().m_Range(b, a);

		// Handle standard input cases.
		return Instance().m_Range(a, b);
	}

	/// <summary>
	/// Returns a pseudorandom floating-point value on an inclusive interval.
	/// </summary>
	static float Range(float a, float b, unsigned int n = 1000)
	{
		// Handle equality edge case.
		if (a == b) return a;

		// Handle negative difference edge case.
		if (a > b) return Instance().m_Range(b, a, n);

		// Handle standard input cases.
		return Instance().m_Range(a, b, n);
	}
};

#endif
