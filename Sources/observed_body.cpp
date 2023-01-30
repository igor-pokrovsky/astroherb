#include "observed_body.h"
#include "time.h"

using namespace Astro_herb;

Observed_body::Observed_body(const Astro_time& time)
	:Celestial_body{time}
{
}

Horizontal_coordinates Observed_body::geocentric_coordinates(const Geographic_coordinates& geo_coords)
{
	return lazy_value_or(v_geocentric_coordinates, [=] {
		// Greenwich Mean Sidereal Time / Local Sidereal Time
		double GMST0 = sun_mean_longitude()+180;
		double LST = GMST0+time.ut*15+geo_coords.longitude;

		// Hour angle
		Celestial_coordinates cc = celestial_coordinates();
		double HA = rev(LST-cc.right_ascension);

		double x = cosd(HA)*cosd(cc.declination);
		double y = sind(HA)*cosd(cc.declination);
		double z = sind(cc.declination);

		double xhor = x*sind(geo_coords.latitude)-z*cosd(geo_coords.latitude);
		double yhor = y;
		double zhor = x*cosd(geo_coords.latitude)+z*sind(geo_coords.latitude);

		double azimuth = atan2d(yhor, xhor)+180;
		double altitude = asind(zhor);

		// Apply topocentric correction
		altitude -= parallax()*cosd(altitude);

		return Horizontal_coordinates{ altitude, azimuth };
	});
}
