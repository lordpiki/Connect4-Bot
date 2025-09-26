#pragma once
#include <cstdint>

// Static class for bitmap manipulations
class BitmapHelper
{
public:
	static inline constexpr bool is_bit_set(uint64_t mask, uint8_t pos) { return (mask & (1ULL << pos)) != 0; }
	static inline constexpr uint64_t set_bit(uint64_t mask, uint8_t pos) { return mask | (1ULL << pos); }
	static inline constexpr uint64_t clear_bit(uint64_t mask, uint8_t pos) { return mask & ~(1ULL << pos); }
	static inline constexpr uint64_t combine_masks(uint64_t mask1, uint64_t mask2) { return mask1 | mask2; }

};

