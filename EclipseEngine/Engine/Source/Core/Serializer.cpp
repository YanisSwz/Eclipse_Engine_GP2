#include "Serializer.hpp"
#include "Scene.hpp"
#include "Transform.hpp"
#include "Model.hpp"
#include "Lighting/DirectionalLight.hpp"
#include "Lighting/PointLight.hpp"
#include "Lighting/SpotLight.hpp"
#include "Physics/BoxCollider.hpp"
#include "Physics/CapsuleCollider.hpp"
#include "Physics/MeshCollider.hpp"

namespace Core
{
	json Serializer::SerializeScene(Scene* _scene)
	{
		json scene;

		for (int i = 0; i < _scene->GetCount(); ++i)
		{
			GameObject* gameObject = _scene->GetGameObject(i);
			scene[gameObject->name] = SerializeGameObject(gameObject);
		}

		return scene;
	}

	json Serializer::SerializeGameObject(GameObject* _gameObject)
	{
		return SerializeTransform(_gameObject->transform);
	}

	json Serializer::SerializeComponent(Component* _component)
	{
		if (Model* dynamicModel_ptr = dynamic_cast<Model*>(_component))
		{
			return SerializeModel(dynamicModel_ptr);
		}
		else if (DirectionalLight* dynamicDirectionalLight_ptr = dynamic_cast<DirectionalLight*>(_component))
		{
			return SerializeDirectionalLight(dynamicDirectionalLight_ptr);
		}
		else if (PointLight* dynamicPointLight_ptr = dynamic_cast<PointLight*>(_component))
		{
			return SerializePointLight(dynamicPointLight_ptr);
		}
		else if (SpotLight* dynamicSpotLight_ptr = dynamic_cast<SpotLight*>(_component))
		{
			return SerializeSpotLight(dynamicSpotLight_ptr);
		}
		else if (BoxCollider* dynamicBoxCollider_ptr = dynamic_cast<BoxCollider*>(_component))
		{
			return SerializeBoxCollider(dynamicBoxCollider_ptr);
		}
		else if (CapsuleCollider* dynamicCapsuleCollider_ptr = dynamic_cast<CapsuleCollider*>(_component))
		{
			return SerializeCapsuleCollider(dynamicCapsuleCollider_ptr);
		}
		else if (MeshCollider* dynamicMeshCollider_ptr = dynamic_cast<MeshCollider*>(_component))
		{
			return SerializeMeshCollider(dynamicMeshCollider_ptr);
		}

		return json();
	}

	json Serializer::SerializeTransform(Transform* _transform)
	{
		json j = *_transform;
		return j;
	}

	json Serializer::SerializeModel(Model* _model)
	{
		return json();
	}

	json Serializer::SerializeDirectionalLight(DirectionalLight* _dirLight)
	{
		return json();
	}

	json Serializer::SerializePointLight(PointLight* _pointLight)
	{
		return json();
	}

	json Serializer::SerializeSpotLight(SpotLight* _spotLight)
	{
		return json();
	}

	json Serializer::SerializeBoxCollider(BoxCollider* _boxCollider)
	{
		return json();
	}

	json Serializer::SerializeCapsuleCollider(CapsuleCollider* _capsuleCollider)
	{
		return json();
	}

	json Serializer::SerializeMeshCollider(MeshCollider* _meshCollider)
	{
		return json();
	}
}