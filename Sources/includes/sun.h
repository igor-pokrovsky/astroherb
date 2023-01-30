#pragma once
#include "observed_body.h"

namespace Astro_herb
{
	class Sun : public Observed_body {
	public:
		Sun(const Astro_time time);

		double mean_anomaly() override;
		double longitude_of_ascending_node() override;
		double inclination_of_ecliptic() const override;
		double argument_of_perihelion() override;
		double eccentricity() override;
		double mean_distance() const override;
		double mean_longitude() override;
		double true_longitude() override;
		double parallax() override;

	private:
		std::optional<double> v_mean_anomaly;
		std::optional<double> v_argument_of_perihelion;
		std::optional<double> v_eccentricity;
		std::optional<double> v_mean_longitude;
		std::optional<double> v_true_longitude;
		std::optional<double> v_parallax;
	};
}
