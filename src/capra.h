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

/// Represents different types of DiveSegments possible.
enum class SegmentType {
  /// Segment represents a no decompression limit.
  NoDeco,
  /// Segment represents a mandatory decompression stop.
  DecoStop,
  /// Segment represents a bottom segment.
  DiveSegment,
  /// Segment represents a change in depth.
  AscDesc,
};

struct CDiveSegment {
  /// Type of this segment. See [`SegmentType`].
  SegmentType segment_type;
  /// Depth at the beginning of segment.
  uintptr_t start_depth;
  /// Depth at the end of segment.
  uintptr_t end_depth;
  /// Duration of the segment (milliseconds)
  uint64_t time;
  /// Ascent rate (measured in m min^-1)
  intptr_t ascent_rate;
  /// Descent rate (measured in m min^-1)
  intptr_t descent_rate;
};

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

CDiveSegment get_next_stop(const Gas *gas, intptr_t ascent_rate, intptr_t descent_rate);

void initialise();

void set_gfh(uintptr_t high);

void set_gfl(uintptr_t low);

void tick_segment(const Gas *gas, uintptr_t depth, uint64_t tick);

} // extern "C"
