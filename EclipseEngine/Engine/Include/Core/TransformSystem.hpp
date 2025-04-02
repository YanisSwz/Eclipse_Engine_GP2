#pragma once
#include "Transform.hpp"
#include "ProjectExports.hpp"

namespace Core 
{
	class TransformSystem
	{
	public:
		ECLIPSE_ENGINE TransformSystem();
		ECLIPSE_ENGINE ~TransformSystem();
		ECLIPSE_ENGINE void Add(Transform* _transform);
		ECLIPSE_ENGINE void Update();

	private:
		static const int MAX_SIZE = 100;
		int currentCount = 0;
		Transform data[MAX_SIZE];

	};
}