#pragma once
#include <optional>

#include "mathlib.h"
#include "astro_time.h"

namespace Astro_herb
{
	// Spherical ecliptic coordinates
	struct Ecliptic_coordinates {
		double latitude;
		double longitude;
	};

	// Spherical celestial coordinates
	struct Celestial_coordinates {
		double declination;			// Celestial latitude
		double right_ascension;		// Celestial longitude
	};

	class Celestial_body {
	public:
		const Astro_time time;
		const double obliquity_of_ecliptic = 23.4393-3.563E-7*time.jd;	// "Tilt" of the Earth's axis of rotation

		Celestial_body(const Astro_time time);

		virtual double mean_anomaly() = 0;
		virtual double longitude_of_ascending_node() = 0;
		virtual double inclination_of_ecliptic() const = 0;
		virtual double argument_of_perihelion() = 0;
		virtual double eccentricity() = 0;				// (0=circle, 0-1=ellipse, 1=parabola)
		virtual double mean_distance() const = 0;		// Mean distance from Sun
		virtual double mean_longitude() = 0;			// Mean anomaly + argument of perihelion
		virtual double true_longitude() = 0;			// True anomaly + argument of perihelion
		virtual double parallax() = 0;

		double eccentric_anomaly();
		double true_anomaly();

		virtual double distance_to_earth();
		virtual vec3d ecliptic_rectangular_coordinates();
		virtual Ecliptic_coordinates ecliptic_spherical_coordinates();	// True ecliptic latitude and longitude of a body
		Celestial_coordinates celestial_coordinates();

		double sun_mean_anomaly();
		double sun_mean_longitude();

	private:
		std::optional<double> v_eccentric_anomaly;
		std::optional<double> v_true_anomaly;
		std::optional<double> v_distance_to_earth;
		std::optional<vec3d> v_ecliptic_rectangular_coordinates;
		std::optional<Ecliptic_coordinates> v_ecliptic_spherical_coordinates;
		std::optional<Celestial_coordinates> v_celestial_coordinates;
		std::optional<double> v_sun_mean_anomaly;
		std::optional<double> v_sun_mean_longitude;
	};

	template<typename T, typename F>
	T lazy_value_or(std::optional<T>& opt, F fn)
	{
		if (!opt) {
			opt = fn();
		}
		return *opt;
	}
}