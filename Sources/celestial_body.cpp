#include <iostream>

#include "celestial_body.h"

using namespace Astro_herb;

Celestial_body::Celestial_body(const Astro_time time)
	:time(time)
{
}

/*
* Find eccentric anomaly by iteratively solving Keppler equation
*/
double Celestial_body::eccentric_anomaly()
{
	return lazy_value_or(v_eccentric_anomaly, [this] {
		const double M = mean_anomaly();
		const double e = eccentricity();

		const int max_iterations = 10;	// Process should converge quite soon
		const double eps = 0.005;		// Acceptable error

		double E0 = M+radeg*e*sind(M)*(1.0+e*cosd(M));
		double E1 = E0;

		// Iterate over, until error would be acceptable
		for (int it = 0; it<max_iterations; ++it) {
			E1 = E0-(E0-radeg*e*sind(E0)-M)/(1-e*cosd(E0));
			if (fabs(E1-E0)<eps) {
				break;
			}

			E0 = E1;
		}

		return E1;
	});
}

double Celestial_body::true_anomaly()
{
	return lazy_value_or(v_true_anomaly, [this] {
		double a = mean_distance();
		double e = eccentricity();
		double E = eccentric_anomaly();

		double xv = a*(cosd(E)-e);
		double yv = a*sqrt(1.0-e*e)*sind(E);

		return rev(atan2d(yv, xv));
	});
}

double Celestial_body::distance_to_earth()
{
	return lazy_value_or(v_distance_to_earth, [this] {
		double a = mean_distance();
		double e = eccentricity();
		double v = true_anomaly();

		return a*(1 - e*e)/(1 + e*cosd(v));
	});
}

vec3d Celestial_body::ecliptic_rectangular_coordinates()
{
	return lazy_value_or(v_ecliptic_rectangular_coordinates, [this] {
		double N = longitude_of_ascending_node();
		double i = inclination_of_ecliptic();
		double tl = true_longitude();
		double r = distance_to_earth();

		double xs = r*(cosd(N)*cosd(tl) - sind(N)*sind(tl)*cosd(i));
		double ys = r*(sind(N)*cosd(tl) + cosd(N)*sind(tl)*cosd(i));
		double zs = r*sind(tl)*sind(i);

		return vec3d {xs,ys,zs};
	});
}

Ecliptic_coordinates Celestial_body::ecliptic_spherical_coordinates()
{
	return lazy_value_or(v_ecliptic_spherical_coordinates, [this] {
		vec3d ecliptic = Celestial_body::ecliptic_rectangular_coordinates();

		// Ecliptic true longitude, latitude
		double lon_ecl = rev(atan2d(ecliptic.y, ecliptic.x));
		double lat_ecl = atan2d(ecliptic.z, sqrt(ecliptic.x*ecliptic.x+ecliptic.y*ecliptic.y));

		return Ecliptic_coordinates {lat_ecl,lon_ecl};
	});
}

Celestial_coordinates Celestial_body::celestial_coordinates()
{
	return lazy_value_or(v_celestial_coordinates, [this] {
		vec3d ecliptic = ecliptic_rectangular_coordinates();

		// Equatorial coordinates
		double xe = ecliptic.x;
		double ye = ecliptic.y*cosd(obliquity_of_ecliptic) - ecliptic.z*sind(obliquity_of_ecliptic);
		double ze = ecliptic.y*sind(obliquity_of_ecliptic) + ecliptic.z*cosd(obliquity_of_ecliptic);

		double Decl = atan2d(ze, sqrt(xe*xe+ye*ye));
		double RA = rev(atan2d(ye, xe));

		return Celestial_coordinates{ Decl, RA };
	});
}

double Celestial_body::sun_mean_anomaly()
{
	return lazy_value_or(v_sun_mean_anomaly, [this] {
		return rev(356.0470+0.9856002585*time.jd);
	});
}

double Celestial_body::sun_mean_longitude()
{
	return lazy_value_or(v_sun_mean_longitude, [this] {
		return rev(356.0470+0.9856002585*time.jd+282.9404+4.70935E-5*time.jd);
	});
}
