#include "moon.h"

using namespace Astro_herb;

Moon::Moon(const Astro_time time)
	: Observed_body{time}
{
}

double Moon::mean_anomaly()
{
	return lazy_value_or(v_mean_anomaly, [this] {
		return rev(115.3654+13.0649929509*time.jd);
	});
}

double Moon::longitude_of_ascending_node()
{
	return lazy_value_or(v_longitude_of_ascending_node, [this] {
		return rev(125.1228-0.0529538083*time.jd);
	});
}

double Moon::inclination_of_ecliptic() const
{
	return 5.1454;
}

double Moon::argument_of_perihelion()
{
	return lazy_value_or(v_argument_of_perihelion, [this] {
		return rev(318.0634+0.1643573223*time.jd);
	});
}

double Moon::eccentricity()
{
	return 0.054900;
}

double Moon::mean_distance() const
{
	return 60.2666;
}

double Moon::mean_longitude()
{
	return lazy_value_or(v_mean_longitude, [this] {
		return rev(115.3654+13.0649929509*time.jd+318.0634+0.1643573223*time.jd);
	});
}

double Moon::true_longitude()
{
	return lazy_value_or(v_true_longitude, [this] {
		return rev(true_anomaly()+argument_of_perihelion());
	});
}

double Moon::parallax()
{
	return lazy_value_or(v_parallax, [this] {
		return asind(1/distance_to_earth());
	});
}

vec3d Moon::ecliptic_rectangular_coordinates()
{
	return lazy_value_or(v_ecliptic_rectangular_coordinates, [this] {
		Ecliptic_coordinates ec = ecliptic_spherical_coordinates();

		// Calculate new ecliptic coordinates
		double r = distance_to_earth();
		vec3d ecliptic = {
			r*cosd(ec.longitude)*cosd(ec.latitude),
			r*sind(ec.longitude)*cosd(ec.latitude),
			r*sind(ec.latitude)
		};

		return ecliptic;
	});
}

Ecliptic_coordinates Moon::ecliptic_spherical_coordinates()
{
	double Mm = mean_anomaly();
	double Nm = longitude_of_ascending_node();
	double wm = argument_of_perihelion();

	double Ms = sun_mean_anomaly();
	double Ls = sun_mean_longitude();

	double Lm = rev(Nm+wm+Mm);		// Mean longitude
	double D = rev(Lm-Ls);			// Mean elongation
	double F = rev(Lm-Nm);			// Agrument of latitude

	Ecliptic_coordinates ec = Celestial_body::ecliptic_spherical_coordinates();

	// Apply perturbations

	ec.longitude +=
		-1.274*sind(Mm-2*D)
		+0.658*sind(2*D)
		-0.186*sind(Ms)
		-0.059*sind(2*Mm-2*D)
		-0.057*sind(Mm-2*D+Ms)
		+0.053*sind(Mm+2*D)
		+0.046*sind(2*D-Ms)
		+0.041*sind(Mm-Ms)
		-0.035*sind(D)
		-0.031*sind(Mm+Ms)
		-0.015*sind(2*F-2*D)
		+0.011*sind(Mm-4*D);

	ec.latitude +=
		-0.173*sind(F-2*D)
		-0.055*sind(Mm-F-2*D)
		-0.046*sind(Mm+F-2*D)
		+0.033*sind(F+2*D)
		+0.017*sind(2*Mm+F);

	return ec;
}

double Moon::distance_to_earth()
{
	return lazy_value_or(v_distance_to_earth, [this] {
		double Mm = mean_anomaly();
		double Nm = longitude_of_ascending_node();
		double wm = argument_of_perihelion();

		double Ls = sun_mean_longitude();
		double Lm = rev(Nm+wm+Mm);
		double D = rev(Lm-Ls);

		double r = Celestial_body::distance_to_earth();

		r += -0.58*cosd(Mm-2*D) - 0.46*cosd(2*D);

		return r;
	});
}

double Moon::phase(double sun_true_longitude)
{
	double Lm = ecliptic_spherical_coordinates().longitude;
	double Ls = sun_true_longitude;

	return 0.5*(1-cosd(Lm-Ls));
}