#include "sun.h"

using namespace Astro_herb;

Sun::Sun(const Astro_time time)
	: Observed_body{time}
{
}

double Sun::mean_anomaly()
{
	return lazy_value_or(v_mean_anomaly, [this] {
		return rev(356.0470+0.9856002585*time.jd);
	});
}

double Sun::longitude_of_ascending_node()
{
	return 0;
}

double Sun::inclination_of_ecliptic() const
{
	return 0;
}

double Sun::argument_of_perihelion()
{
	return lazy_value_or(v_argument_of_perihelion, [this] {
		return rev(282.9404+4.70935E-5*time.jd);
	});
}

double Sun::eccentricity()
{
	return lazy_value_or(v_eccentricity, [this] {
		return 0.016709-1.151E-9*time.jd;
	});
}

double Sun::mean_distance() const
{
	return 1;
}

double Sun::mean_longitude()
{
	return lazy_value_or(v_mean_longitude, [this] {
		return rev(356.0470+0.9856002585*time.jd+282.9404+4.70935E-5*time.jd);
	});
}

double Sun::true_longitude()
{
	return lazy_value_or(v_true_longitude, [this] {
		return rev(true_anomaly()+argument_of_perihelion());
	});
}

double Sun::parallax()
{
	return lazy_value_or(v_parallax, [this] {
		return (8.794/3600)/mean_distance();
	});
}
