#include "CppUnitTest.h"
#include "astroherb.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Astro_herb;

namespace Astro_herb_test
{
	TEST_CLASS(Test_astro_herb) {
	public:
		TEST_METHOD(Test_moon_position)
		{
			Moon moon{time};
			Horizontal_coordinates position = moon.geocentric_coordinates(geo_coordinates);

			Horizontal_coordinates expected_position = {-16.227441, 101.786803};
			Assert::IsTrue(eps_equal(expected_position.altitude, position.altitude) && eps_equal(expected_position.azimuth, position.azimuth));
		}

		TEST_METHOD(Test_sun_position)
		{
			Sun sun{time};
			Horizontal_coordinates position = sun.geocentric_coordinates(geo_coordinates);
			
			Horizontal_coordinates expected_position = {-17.959354, 15.676805};
			Assert::IsTrue(eps_equal(expected_position.altitude, position.altitude) && eps_equal(expected_position.azimuth, position.azimuth));
		}

	private:
		const Astro_time time{1990, 4, 19, 0, 0, 0, 0, 0};
		Geographic_coordinates geo_coordinates{60, 15};
	};
}
