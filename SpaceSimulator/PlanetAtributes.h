#pragma once

#define UNIVERSE_SCALE 0.002f


/**
* This file contains planet information. the unit of distance is currently miles
* TODO: put all measurements in comparison to pluto to prevent overflow errors
*/

// SUN
#define SUN_TEXTURE "Sun.bmp"
#define SUN_TEXTURE_HEIGHT 150
#define SUN_TEXTURE_WIDTH 150
#define SUN_SIZE (UNIVERSE_SCALE*696000.0)
#define SUN_MASS (UNIVERSE_SCALE*10000.0)
#define SUN_STARTING_X 0
#define SUN_STARTING_Y 0
#define SUN_STARTING_Z 0

// Mercury
#define MERCURY_TEXTURE "EarthTexture.bmp"
#define MERCURY_TEXTURE_HEIGHT 150
#define MERCURY_TEXTURE_WIDTH 300
#define MERCURY_SIZE (UNIVERSE_SCALE*2440.0)
#define MERCURY_MASS (UNIVERSE_SCALE*1000.0)
#define MERCURY_DISTANCE_FROM_SUN (UNIVERSE_SCALE*720000.0)

// Venus
#define VENUS_TEXTURE "EarthTexture.bmp"
#define VENUS_TEXTURE_HEIGHT 150
#define VENUS_TEXTURE_WIDTH 300
#define VENUS_SIZE (UNIVERSE_SCALE*6052.0)
#define VENUS_MASS (UNIVERSE_SCALE*1000.0)
#define VENUS_DISTANCE_FROM_SUN (UNIVERSE_SCALE*750000.0)

// EARTH
#define EARTH_TEXTURE "EarthTexture.bmp"
#define EARTH_TEXTURE_HEIGHT 150
#define EARTH_TEXTURE_WIDTH 300
#define EARTH_SIZE (UNIVERSE_SCALE*6378.0)
#define EARTH_MASS (UNIVERSE_SCALE*1000.0)
#define EARTH_DISTANCE_FROM_SUN (UNIVERSE_SCALE*800000.0)

// earth's moon
#define EARTH_MOON_TEXTURE "Moon.bmp"
#define EARTH_MOON_TEXTURE_HEIGHT 150
#define EARTH_MOON_TEXTURE_WIDTH 300
#define EARTH_MOON_SIZE (UNIVERSE_SCALE*1737.0)
#define EARTH_MOON_MASS (UNIVERSE_SCALE*50.0)
#define EARTH_MOON_DISTANCE_FROM_EARTH (UNIVERSE_SCALE*15000.0)

// Mars
#define MARS_TEXTURE "EarthTexture.bmp"
#define MARS_TEXTURE_HEIGHT 150
#define MARS_TEXTURE_WIDTH 300
#define MARS_SIZE (UNIVERSE_SCALE*3378.0)
#define MARS_MASS (UNIVERSE_SCALE*1000.0)
#define MARS_DISTANCE_FROM_SUN (UNIVERSE_SCALE*900000.0)

// Jupiter
#define JUPITER_TEXTURE "EarthTexture.bmp"
#define JUPITER_TEXTURE_HEIGHT 150
#define JUPITER_TEXTURE_WIDTH 300
#define JUPITER_SIZE (UNIVERSE_SCALE*71492.0)
#define JUPITER_MASS (UNIVERSE_SCALE*1000.0)
#define JUPITER_DISTANCE_FROM_SUN (UNIVERSE_SCALE*1200000.0)

// Saturn
#define SATURN_TEXTURE "EarthTexture.bmp"
#define SATURN_TEXTURE_HEIGHT 150
#define SATURN_TEXTURE_WIDTH 300
#define SATURN_SIZE (UNIVERSE_SCALE*60268.0)
#define SATURN_MASS (UNIVERSE_SCALE*1000.0)
#define SATURN_DISTANCE_FROM_SUN (UNIVERSE_SCALE*1500000.0)

// Uranus
#define URANUS_TEXTURE "EarthTexture.bmp"
#define URANUS_TEXTURE_HEIGHT 150
#define URANUS_TEXTURE_WIDTH 300
#define URANUS_SIZE (UNIVERSE_SCALE*25559.0)
#define URANUS_MASS (UNIVERSE_SCALE*1000.0)
#define URANUS_DISTANCE_FROM_SUN (UNIVERSE_SCALE*1700000.0)

// Neptune
#define NEPTUNE_TEXTURE "EarthTexture.bmp"
#define NEPTUNE_TEXTURE_HEIGHT 150
#define NEPTUNE_TEXTURE_WIDTH 300
#define NEPTUNE_SIZE (UNIVERSE_SCALE*24766.0)
#define NEPTUNE_MASS (UNIVERSE_SCALE*1000.0)
#define NEPTUNE_DISTANCE_FROM_SUN (UNIVERSE_SCALE*1850000.0)
