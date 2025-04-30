#pragma once
#include "meta/factory.hpp"
#include <string_view>

class ISerializable
{
public:
	inline static std::hash<std::string_view> hash{};
};
