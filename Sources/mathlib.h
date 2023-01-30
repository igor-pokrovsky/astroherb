/*
* Igor Pokrovsky
* 26.01.2023
* Math library for astrolib project
*/

#pragma once
#ifndef _MATHLIB_
#define _MATHLIB_

#include <cmath>

namespace Astro_herb 
{
	struct vec3d {
		double x;
		double y;
		double z;
	};

	static constexpr double pi = 3.14159265358979323846;
	static constexpr double epsilon = 0.000001;
	static constexpr double radeg = 180.0/pi;
	static constexpr double degrad = pi/180.0;
	static constexpr double earth_radii_to_au = 1/23450;

	/**
	* Angle normalization for trigonometric functions
	*/
	inline double rev(const double angle)
	{
		return angle - floor(angle/360.0)*360.0;
	}

	/*
	* Check if values are equal up to epsilon
	*/
	inline bool eps_equal(const double a, const double b)
	{
		return fabs(a-b) < epsilon;
	}

	/*
	* Degrees version of sin
	*/
	inline double sind(const double x)
	{
		return sin(x*degrad);
	}

	/*
	* Degrees version of cos
	*/
	inline double cosd(const double x)
	{
		return cos(x*degrad);
	}

	/*
	* Degrees version of tan
	*/
	inline double tand(const double x)
	{
		return tan(x*degrad);
	}

	/*
	* Result of asin turned into degrees
	*/
	inline double asind(const double x)
	{
		return radeg*asin(x);
	}

	/*
	* Result of acos turned into degrees
	*/
	inline double acosd(const double x)
	{
		return radeg*acos(x);
	}

	/*
	* Result of atan turned into degrees
	*/
	inline double atand(const double x)
	{
		return radeg*atan(x);
	}

	/*
	* Result of atan2 turned into degrees
	*/
	inline double atan2d(const double y, const double x)
	{
		return radeg*atan2(y,x);
	}
}

#endif


