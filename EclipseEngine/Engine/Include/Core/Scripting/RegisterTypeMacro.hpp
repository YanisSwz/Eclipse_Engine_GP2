#pragma once
#include "Scripting/ScriptComponent.hpp"

#define REGISTER_TYPE(TYPE)										\
namespace														\
{																\
	static const bool _registered_##TYPE = []()					\
	{															\
		Core::ScriptComponent::GetScriptRegister()[#TYPE] = []()\
		{														\
			return new TYPE;									\
		};														\
		return true;											\
	}();														\
}