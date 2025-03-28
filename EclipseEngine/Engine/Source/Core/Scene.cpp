#include "Scene.hpp"

namespace Core
{
	void MonoBehaviourArray::Sort()
	{
		int activeCount = 0;
		int tempCount = 0;
		for (int i = 0; i < currentActiveCount; ++i)
		{
			if (data[i].IsActive())
				++activeCount;
		}
		tempCount = activeCount;

		int left = 0;
		int right = currentActiveCount - 1;
		while (left < right)
		{

			while (data[left].IsActive() && left < currentActiveCount - 1)
				++left;

			while (!data[right].IsActive() && right > 0)
				--right;

			if (left < right)
			{
				Swap(&data[left], &data[right]);
			}
		}
		currentActiveCount = activeCount;
	}

	void MonoBehaviourArray::Swap(Component* _obj1, Component* _obj2)
	{
		MonoBehaviour* obj1 = dynamic_cast<MonoBehaviour*>(_obj1);
		MonoBehaviour* obj2 = dynamic_cast<MonoBehaviour*>(_obj2);

		Component* temp = _obj1;
		_obj1 = _obj2;
		_obj2 = temp;

		_obj1->GetGameObject()->UpdateComponentLocation(obj1);
		_obj1->GetGameObject()->UpdateComponentLocation(obj2);
	}
}