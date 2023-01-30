#pragma once

namespace Astro_herb
{
	class Astro_time {
	public:
		double jd;	// Julian day (days since 2000 Jan 0.0 UT)
		double ut;	// Universal time (UT)

		Astro_time(int year, int month, int day, int hours, int minutes, int seconds, int milli_seconds, int time_zone);
	};
}
