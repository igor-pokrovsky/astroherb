#pragma once
#include "observed_body.h"

namespace Astro_herb
{
	class Moon : public Observed_body {
	public:
		Moon(const Astro_time time);

		double mean_anomaly() override;
		double longitude_of_ascending_node() override;
		double inclination_of_ecliptic() const override;
		double argument_of_perihelion() override;
		double eccentricity() override;
		double mean_distance() const override;
		double mean_longitude() override;
		double true_longitude() override;
		double parallax() override;
		vec3d ecliptic_rectangular_coordinates() override;
		Ecliptic_coordinates ecliptic_spherical_coordinates() override;
		double distance_to_earth() override;

		// Moon phase, 0 - not visible, 1 - fully visible
		double phase(double sun_true_longitude);

	private:
		std::optional<double> v_mean_anomaly;
		std::optional<double> v_longitude_of_ascending_node;
		std::optional<double> v_argument_of_perihelion;
		std::optional<double> v_mean_longitude;
		std::optional<double> v_true_longitude;
		std::optional<double> v_parallax;
		std::optional<double> v_sun_mean_anomaly;
		std::optional<double> v_sun_mean_longitude;
		std::optional<vec3d> v_ecliptic_rectangular_coordinates;
		std::optional<Ecliptic_coordinates> v_ecliptic_spherical_coordinates;
		std::optional<double> v_distance_to_earth;
	};
}
