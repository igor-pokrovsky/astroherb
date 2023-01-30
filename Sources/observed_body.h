#pragma once
#include "celestial_body.h"

namespace Astro_herb
{
	struct Horizontal_coordinates {
		double altitude;
		double azimuth;
	};

	struct Geographic_coordinates {
		double latitude;
		double longitude;
	};

	class Observed_body : public Celestial_body {
	public:
		Observed_body(const Astro_time& time);

		Horizontal_coordinates geocentric_coordinates(const Geographic_coordinates& geo_coords);

	private:
		std::optional<Horizontal_coordinates> v_geocentric_coordinates;
	};
}
