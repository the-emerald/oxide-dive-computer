#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <new>

/// A default, placeholder ascent rate (measured in m min^-1). This is the maximum rate recommended by major instruction agencies.
static const intptr_t DEFAULT_ASCENT_RATE = -18;

/// A default, placeholder descent rate (measured in m min^-1).
static const intptr_t DEFAULT_DESCENT_RATE = 30;

/// Density of fresh water (measured in kg m^-3).
static const double DENSITY_FRESHWATER = 997.0;

/// Average density of salt water (measured in kg m^-3).
static const double DENSITY_SALTWATER = 1023.6;

/// Number of tissues in a typical decompression algorithm.
static const uintptr_t TISSUE_COUNT = 16;

/// Pressure of water vapour. (measured in bar)
static const double WATER_VAPOUR_PRESSURE = 0.06257;

/// A gas mix used in a dive.
struct Gas {
  /// Percentage fraction of oxygen in the mix.
  uintptr_t o2;
  /// Percentage fraction of helium in the mix.
  uintptr_t he;
  /// Percentage fraction of nitrogen in the mix.
  uintptr_t n2;
};

extern "C" {

Gas initialise();

} // extern "C"
