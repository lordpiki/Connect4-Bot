#pragma once
#include <map>
#include <cstdint>


class ScoreCache
{
public:
	ScoreCache() = default;
	inline static std::map<std::pair<uint64_t, uint64_t>, uint8_t> cache;

};

