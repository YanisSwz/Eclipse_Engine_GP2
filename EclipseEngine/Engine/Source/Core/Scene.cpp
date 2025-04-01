#include "Scene.hpp"

namespace Core
{
	void MonoBehaviourArray::Sync()
	{
		for(int i = 0; i < currentCount; ++i)
		{
			if(data[i].IsDestroyed())
			{
				data[i].GetGameObject()->RemoveComponent(&data[i]);
				data[i].SetGameObject(nullptr);
			}
		}
	}
	
	void MonoBehaviourArray::Sort()
	{
		int activeCount = 0;
		for (int i = 0; i < currentActiveCount; ++i)
		{
			if (data[i].IsActive())
				++activeCount;
		}

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
		Component temp = *_obj1;
		*_obj1 = *_obj2;
		*_obj2 = temp;

		_obj1->GetGameObject()->UpdateComponentLocation(_obj2, _obj1);
		_obj2->GetGameObject()->UpdateComponentLocation(_obj1, _obj2);
	}

	void MonoBehaviourArray::Add(Component* _comp)
	{
		MonoBehaviour* obj1 = dynamic_cast<MonoBehaviour*>(_comp);
		if(obj1 != nullptr)
		{
			// Check if we can overwrite a destroyed component
			for (int i = 0; i < currentCount; ++i)
			{
				if (data[i].IsDestroyed())
				{
					// If component hasn't been synchronyzed
					if (data[i].GetGameObject() != nullptr)
					{
						data[i].GetGameObject()->RemoveComponent(&data[i]);
						data[i].SetGameObject(nullptr);
					}
					data[i] = *obj1;
					data[i].GetGameObject()->UpdateComponentLocation(&data[i]);
					++currentActiveCount;
					return;
				}
			}

			// Insert as last active component and update game object pointer
			data[currentCount] = *obj1;
			Swap(&data[currentCount], &data[currentActiveCount]);
			data[currentActiveCount].GetGameObject()->UpdateComponentLocation(&data[currentActiveCount]);
			++currentCount;
			++currentActiveCount;
		}
	}

	void MonoBehaviourArray::Update()
	{
		for (int i = 0; i < currentActiveCount; ++i)
			data[i].Update();
	}
}