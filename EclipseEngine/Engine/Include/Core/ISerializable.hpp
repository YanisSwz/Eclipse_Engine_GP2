#pragma once
#include "meta/factory.hpp"
#include <string_view>
#include <nlohmann/json.hpp>

namespace Core
{
	using json = nlohmann::ordered_json;

	class ISerializable
	{
	public:
		inline static std::hash<std::string_view> hash{};

		virtual void Serialize(json& _j) = 0;
		virtual void Deserialize(const json& _j) = 0;
	};
}