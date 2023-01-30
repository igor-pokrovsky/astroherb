#include "astro_time.h"

Astro_herb::Astro_time::Astro_time(int year, int month, int day, int hours, int minutes, int seconds, int milli_seconds, int time_zone)
{
	ut = time_zone + hours + minutes/60.0 + seconds/3600.0 + milli_seconds/3600000.0;
	jd = 367*year - 7*(year+(month+9)/12)/4 - 3*((year+(month-9)/7)/100+1)/4 + 275*month/9 + day - 730515
		+ ut/24.0;
}