#include "GUI/InspectorGUI.hpp"
#include "GUI/Widget/ImGuiWidget.hpp"
#include "Resource/ResourceManager.hpp"
#include "Core/Camera/Camera.hpp"
#include "Core/Physics/BoxCollider.hpp"
#include "Core/Physics/CapsuleCollider.hpp"
#include "Core/Physics/MeshCollider.hpp"
#include "Core/Lighting/DirectionalLight.hpp"
#include "Core/Lighting/PointLight.hpp"
#include "Core/Lighting/SpotLight.hpp"
#include "Core/Audio/AudioSource.hpp"
#include "GameObject.hpp"
#include "Model.hpp"

namespace GUI
{
	InspectorGUI::InspectorGUI()
	{
		m_treeNodeComponentFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed;
		m_treeNodeAddComponentFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;
		m_PopupAddComponentFlags = ImGuiPopupFlags_MouseButtonMiddle;
		m_alreadyAddComponentWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	}

	void InspectorGUI::Draw(Core::GameObject* _crtGOSelected)
	{
		ImGui::SetNextWindowSizeConstraints({ 500.f, 100.f }, ImGui::GetMainViewport()->Size);
		ImGuiWindowFlags inspectorWindowFlags = ImGuiWindowFlags_None;
		ImGui::Begin("Inspector", 0, inspectorWindowFlags);

		if (!_crtGOSelected)
		{
			ImGui::End();
			return;
		}
		if (ImGui::InputText("##Name", _crtGOSelected->name.data(), 255))
		{
			_crtGOSelected->name = _crtGOSelected->name.c_str();
			if (_crtGOSelected->name.size() == 0)
				_crtGOSelected->name = "GameObject" + std::to_string(_crtGOSelected->GetID());
		}

		bool bIsActive = _crtGOSelected->IsActive();
		if (GUI::CheckBox("Active", "##", &bIsActive))
			_crtGOSelected->SetActive(bIsActive);

		ImGui::NewLine();
		DrawTransformComponent(_crtGOSelected->transform);

		if (!_crtGOSelected->IsActive())
			ImGui::BeginDisabled();
		DrawCameraComponent(_crtGOSelected->GetComponent<Core::Camera>());
		DrawModelComponent(_crtGOSelected->GetComponent<Core::Model>());
		DrawBoxColliderComponent(_crtGOSelected->GetComponent<Core::BoxCollider>());
		DrawCapsuleColliderComponent(_crtGOSelected->GetComponent<Core::CapsuleCollider>());
		DrawMeshColliderComponent(_crtGOSelected->GetComponent<Core::MeshCollider>());
		DrawDirectionalLightComponent(_crtGOSelected->GetComponent<Core::DirectionalLight>());
		DrawPointLightComponent(_crtGOSelected->GetComponent<Core::PointLight>());
		DrawSpotLightComponent(_crtGOSelected->GetComponent<Core::SpotLight>());
		DrawAudioSourceComponent(_crtGOSelected->GetComponent<Core::AudioSource>());
		DrawAudioListenerComponent(_crtGOSelected->GetComponent<Core::AudioListener>());
		DrawParticleEmitterComponent(_crtGOSelected->GetComponent<Core::ParticleEmitter>());

		DrawAddComponent(_crtGOSelected);

		if (!_crtGOSelected->IsActive())
			ImGui::EndDisabled();
		ImGui::End();
	}

	bool InspectorGUI::DrawDeleteComponentPopup(Core::Component* _component)
	{
		bool isDelete = false;
		if (ImGui::BeginPopupContextItem("DeleteComponent"))
		{
			if (ImGui::Button("Delete"))
			{
				_component->Remove();
				isDelete = true;
			}
			ImGui::EndPopup();
		}
		return isDelete;
	}

	void InspectorGUI::DrawTransformComponent(Core::Transform* _transform)
	{
		if (!_transform)
			return;

		if (ImGui::TreeNodeEx("Transform", m_treeNodeComponentFlags))
		{
			if (GUI::DragVec3XYZ("Position", _transform->GetLocalPositionRef()))
				_transform->SetPositionChanged(true);
			if (GUI::DragVec3XYZ("Rotation", _transform->GetLocalEulerAnglesRef()))
				_transform->SetRotationChanged(true);
			if (GUI::DragUniformVec3XYZ("Scale", _transform->GetLocalScaleRef(), bIsScaleLocked, m_scaleFactor, 1.f))
				_transform->SetScaleChanged(true);

			ImGui::TreePop();
			ImGui::NewLine();
		}
	}

	void InspectorGUI::DrawCameraComponent(Core::Camera* _camera)
	{
		if (!_camera)
			return;

		if (ImGui::TreeNodeEx("Camera", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_camera))
			{
				ImGui::TreePop();
				return;
			}

			if (!_camera->IsCurrentCamera())
			{
				if (ImGui::Button("Set Current Camera"))
					_camera->SetCurrentCamera();
			}

			float fov = _camera->GetFOV();
			if (GUI::DragFloat("FOV", "CameraFOV", &fov, 0.1f, 0.001f, 179.999f))
				_camera->SetFOV(fov);

			float near = _camera->GetNear();
			float far = _camera->GetFar();
			if (GUI::DragFloat("Near", "CameraNear", &near, 0.1f, 0.1f, far))
				_camera->SetNear(near);

			if (GUI::DragFloat("Far", "CameraFar", &far, 0.1f, near, 100000.f))
				_camera->SetFar(far);

			ImGui::TreePop();
			ImGui::NewLine();
		}
	}

	void InspectorGUI::DrawModelComponent(Core::Model* _model)
	{
		if (!_model)
			return;

		if (ImGui::TreeNodeEx("Model", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_model))
			{
				ImGui::TreePop();
				return;
			}

			std::vector<std::string> meshNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Mesh>();
			std::string meshName = _model->GetMesh()->name;
			if (GUI::ComboFilter("Mesh ", &meshName, meshNames))
				_model->SetMesh(Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(meshName));
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MeshName"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					std::string payload_n;
					payload_n = *static_cast<std::string*>(payload->Data);
					_model->SetMesh(Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>(payload_n));
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::Columns(1);

			std::vector<std::string> textureNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::Texture>();
			std::string textureName = _model->GetTexture()->name;
			if (GUI::ComboFilter("Texture ", &textureName, textureNames))
				_model->SetTexture(Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(textureName));
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TextureName"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					std::string payload_n;
					payload_n = *static_cast<std::string*>(payload->Data);
					_model->SetTexture(Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>(payload_n));
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::Columns(1);
			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawBoxColliderComponent(Core::BoxCollider* _collider)
	{
		if (!_collider)
			return;

		if (ImGui::TreeNodeEx("Box Collider", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_collider))
			{
				ImGui::TreePop();
				return;
			}

			bool isDynamic = _collider->GetIsDynamic();
			if (GUI::CheckBox("Is Dynamic ", "BoxColliderIsDynamic", &isDynamic))
				_collider->SetDynamic(isDynamic);

			float mass = _collider->GetMass();
			if (GUI::DragFloat("Mass ", "BoxColliderMass", &mass, 0.1f, 0.1f, 1000.f, "%.3f Kg"))
			{
				if (mass > 0.f)
					_collider->SetMass(mass);
			}

			Math::Vec3 posOffset = _collider->GetOffsetPos();
			if (GUI::DragVec3XYZ("Offset", posOffset))
				_collider->SetOffsetPos(posOffset);

			Math::Vec3 scale = _collider->GetScale();
			if (GUI::DragVec3XYZ("Size", scale, 1.f))
				_collider->Scale(scale);

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawCapsuleColliderComponent(Core::CapsuleCollider* _collider)
	{
		if (!_collider)
			return;

		if (ImGui::TreeNodeEx("Capsule Collider", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_collider))
			{
				ImGui::TreePop();
				return;
			}

			bool isDynamic = _collider->GetIsDynamic();
			if (GUI::CheckBox("Is Dynamic ", "CapsuleColliderIsDynamic", &isDynamic))
				_collider->SetDynamic(isDynamic);

			float mass = _collider->GetMass();
			if (GUI::DragFloat("Mass ", "CapsuleColliderMass", &mass, 0.1f, 0.1f, 1000.f, "%.3f Kg"))
			{
				if (mass > 0.f)
					_collider->SetMass(mass);
			}

			Math::Vec3 posOffset = _collider->GetOffsetPos();
			if (GUI::DragVec3XYZ("Offset", posOffset))
				_collider->SetOffsetPos(posOffset);

			Math::Vec3 scale = _collider->GetScale();
			if (GUI::DragFloat("Height", "BoxColliderHeight", &scale.y, 0.1f, 0.f, 100.f, "%.3f m"))
				_collider->Scale(scale);

			if (GUI::DragFloat("Radius", "BoxColliderRadius", &scale.x, 0.1f, 0.f, 100.f, "%.3f m"))
			{
				scale.z = scale.x;
				_collider->Scale(scale);
			}

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawMeshColliderComponent(Core::MeshCollider* _collider)
	{
		if (!_collider)
			return;

		if (ImGui::TreeNodeEx("Mesh Collider", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_collider))
			{
				ImGui::TreePop();
				return;
			}

			float mass = _collider->GetMass();
			if (GUI::DragFloat("Mass ", "MeshColliderMass", &mass, 0.1f, 0.1f, 1000.f, "%.3f Kg"))
			{
				if (mass > 0.f)
					_collider->SetMass(mass);
			}

			Math::Vec3 posOffset = _collider->GetOffsetPos();
			if (GUI::DragVec3XYZ("Offset", posOffset))
				_collider->SetOffsetPos(posOffset);

			Math::Vec3 scale = _collider->GetScale();
			if (GUI::DragVec3XYZ("Size", scale, 1.f))
				_collider->Scale(scale);

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawDirectionalLightComponent(Core::DirectionalLight* _light)
	{
		if (!_light)
			return;

		if (ImGui::TreeNodeEx("Directional Light", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_light))
			{
				ImGui::TreePop();
				return;
			}

			GUI::ColorEdit4("Color", _light->GetColorRef());

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawPointLightComponent(Core::PointLight* _light)
	{
		if (!_light)
			return;

		if (ImGui::TreeNodeEx("Point Light", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_light))
			{
				ImGui::TreePop();
				return;
			}

			GUI::ColorEdit4("Color", _light->GetColorRef());
			GUI::DragFloat("Range", "##", &_light->GetDistanceRef(), 0.1f, 1.f, 200.f);

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawSpotLightComponent(Core::SpotLight* _light)
	{
		if (!_light)
			return;

		if (ImGui::TreeNodeEx("Spot Light", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_light))
			{
				ImGui::TreePop();
				return;
			}

			GUI::ColorEdit4("Color", _light->GetColorRef());
			GUI::DragFloat("Range", "##1", &_light->GetDistanceRef(), 0.1f, 1.f, 200.f);

			GUI::DragFloat("Inner Angle", "##2", &_light->GetInnerCutOffRef(), 1.f, 1.f, std::min(_light->GetOuterCutOff(), 180.f));
			GUI::DragFloat("Outer Angle", "##3", &_light->GetOuterCutOffRef(), 1.f, _light->GetInnerCutOff(), 180.f);

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAudioSourceComponent(Core::AudioSource* _source)
	{
		if (!_source)
			return;

		if (ImGui::TreeNodeEx("Audio Source", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_source))
			{
				ImGui::TreePop();
				return;
			}

			std::vector<std::string> soundNames = Resource::ResourceManager::GetInstance().GetAllResourceWithType<Resource::AudioClip>();
			std::string soundName = "No Clip";
			Resource::AudioClip* clip = _source->GetClip();
			if (clip)
			{
				soundName = clip->name;
			}
			if (GUI::ComboFilter("Audio Clip ", &soundName, soundNames))
				_source->SetClip(Resource::ResourceManager::GetInstance().GetResource<Resource::AudioClip>(soundName));
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("AudioClipName"))
				{
					IM_ASSERT(payload->DataSize == sizeof(std::string));
					std::string payload_n;
					payload_n = *static_cast<std::string*>(payload->Data);
					_source->SetClip(Resource::ResourceManager::GetInstance().GetResource<Resource::AudioClip>(payload_n));
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::Columns(1);

			if (clip == nullptr)
				ImGui::BeginDisabled();

			float* data = _source->GetData();
			if (data != nullptr)
			{
				float range = 1000.f;
				if (_source->GetVolume() >= 1.f / range)
					range = 1.f / _source->GetVolume();
				ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(1.f, 0.75f, 0.f, 1.f));
				ImGui::PlotLines("##clip", data, _source->GetSampleCount(), 0, std::to_string(_source->GetLength()).c_str(), -range, range, ImVec2(0.f, 200.f));
				ImGui::PopStyleColor();

				if (_source->IsPlaying())
				{
					float time = _source->GetTime();
					if (ImGui::SliderFloat("##Time", &time, 0.0f, _source->GetLength(), "%.3f", ImGuiSliderFlags_NoInput))
						_source->SetTime(time);
				}
				else
				{
					ImGui::BeginDisabled();
					float time = 0.0f;
					ImGui::SliderFloat("##Time", &time, 0.0f, _source->GetLength(), "%.3f", ImGuiSliderFlags_NoInput);
					ImGui::EndDisabled();
				}
			}

			bool isLooping = _source->GetLooping();
			if (GUI::CheckBox("Looping", "##1", &isLooping))
				_source->SetLooping(isLooping);

			float volume = _source->GetVolume();
			if (GUI::FloatSlider("Volume", &volume, 0.f, 1.f, "%.2f"))
				_source->SetVolume(volume);

			float sampleRate = _source->GetSampleRate();
			if (GUI::FloatSlider("Sample Rate", &sampleRate, 8000.f, 48000.f, "%.0f"))
				_source->SetSampleRate(sampleRate);

			bool is3D = _source->Get3D();
			if (is3D)
				ImGui::BeginDisabled();
			float pan = _source->GetPan();
			if (GUI::FloatSlider("Pan", &pan, -1.f, 1.f, "%.2f"))
				_source->SetPan(pan);
			if (is3D)
				ImGui::EndDisabled();

			if (GUI::CheckBox("3D", "##2", &is3D))
				_source->Set3D(is3D);

			if (!is3D)
				ImGui::BeginDisabled();
			float min = _source->GetMinDistance();
			float max = _source->GetMaxDistance();
			if (GUI::DragFloat("MinDistance", "##3", &min, 0.1f, 0.1f, max - 0.1f, "%.1f"))
				_source->SetMinDistance(min);

			if (GUI::DragFloat("MaxDistance", "##4", &max, 0.1f, min + 0.1f, 1000.f, "%.1f"))
				_source->SetMaxDistance(max);
			if (!is3D)
				ImGui::EndDisabled();


			if (ImGui::Button("Play"))
				_source->Play();

			ImGui::SameLine();
			if (!_source->GetPause())
			{
				if (ImGui::Button("Pause"))
					_source->Pause();
			}
			else
			{
				if (ImGui::Button("Unpause"))
					_source->Pause();
			}

			ImGui::SameLine();
			if (ImGui::Button("Stop"))
				_source->Stop();
			if (clip == nullptr)
				ImGui::EndDisabled();

			ImGui::Columns(1);
			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAudioListenerComponent(Core::AudioListener* _listener)
	{
		if (!_listener)
			return;

		if (ImGui::TreeNodeEx("Audio Listener", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_listener))
			{
				ImGui::TreePop();
				return;
			}

			if (!_listener->IsCurrentListener())
			{
				if (ImGui::Button("Set as current listener"))
					_listener->SetCurrentListener();
			}
			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawParticleEmitterComponent(Core::ParticleEmitter* _particleEmitter)
	{
		if (!_particleEmitter)
			return;

		if (ImGui::TreeNodeEx("Particle Emitter", m_treeNodeComponentFlags))
		{
			if (DrawDeleteComponentPopup(_particleEmitter))
			{
				ImGui::TreePop();
				return;
			}

			if (ImGui::Button("Play"))
				_particleEmitter->Play();
			ImGui::SameLine();
			if (ImGui::Button("Stop"))
				_particleEmitter->Stop();

			ImGui::SeparatorText("Emitter Properties");
			GUI::DragInt("Max Particle", "MaxParticleDragInt", &_particleEmitter->particleEmitterProps.maxNbParticles, 0.1f, 0, Core::ParticleEmitter::MAX_PARTICLE_COUNT);
			GUI::CheckBox("Is Looping", "IsLoopingCheckBox", &_particleEmitter->particleEmitterProps.bIsLoop);
			if (!_particleEmitter->particleEmitterProps.bIsLoop)
				GUI::DragFloat("Simulation \nDuration", "SimulationDurationCheckBox", &_particleEmitter->particleEmitterProps.simulationDuration, 0.1f, 0.f, FLT_MAX);
			GUI::DragFloat("Spawn Rate", "ParticleSpawnRateDragFloat", &_particleEmitter->particleEmitterProps.particleSpawnRate, 0.1f, 0.f, FLT_MAX);
			GUI::DragFloat("Spawn Rate \nVariation", "ParticleSpawnRateVariationDragFloat", &_particleEmitter->particleEmitterProps.particleSpawnRateVariation, 0.1f, 0.f, FLT_MAX);

			ImGui::SeparatorText("Particle Properties");
			GUI::DragFloat("Life Time", "LifeTimeDragFloat", &_particleEmitter->particleProps.lifeTime, 0.1f, 0.f, FLT_MAX);
			GUI::DragColorRGBA("Color Begin", _particleEmitter->particleProps.colorBegin, 255.f);
			GUI::DragColorRGBA("Color End", _particleEmitter->particleProps.colorEnd, 255.f);
			GUI::DragFloat("Size Begin", "SizeBeginDragFloat", &_particleEmitter->particleProps.sizeBegin, 1.f, 0.f, FLT_MAX, "%.3f", 125.f);
			GUI::DragFloat("Size End", "SizeEndDragFloat", &_particleEmitter->particleProps.sizeEnd, 1.f, 0.f, FLT_MAX, "%.3f", 125.f);
			GUI::DragFloat("Size Variation", "SizeVariationDragFloat", &_particleEmitter->particleProps.sizeVariation, 1.f, 0.f, FLT_MAX, "%.3f", 125.f);
			GUI::DragVec3XYZ("Velocity", _particleEmitter->particleProps.velocity, 0.f, 125.f);
			GUI::DragVec3XYZ("Velocity Variation", _particleEmitter->particleProps.velocityVariation, 0.f, 125.f);

			ImGui::NewLine();
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Add Component Popup Window");

		ImGui::SetNextWindowSize(m_alreadyAddComponentWindowSize);
		if (ImGui::BeginPopupContextWindow("Add Component Popup Window", m_PopupAddComponentFlags))
		{
			DrawAddCameraComponent(_crtGOSelected);
			DrawAddRendererComponent(_crtGOSelected);
			DrawAddColliderComponent(_crtGOSelected);
			DrawAddLightComponent(_crtGOSelected);
			DrawAddAudioComponent(_crtGOSelected);
			DrawAddParticlesComponent(_crtGOSelected);
			ImGui::EndPopup();
		}

		if (bIsComponentAlreadyAddedWindowEnable)
			ImGui::OpenPopup("ComponentAlreadyAddedWindowModal");

		if (ImGui::BeginPopupModal("ComponentAlreadyAddedWindowModal", 0, m_alreadyAddComponentWindowFlags))
		{
			ImGui::Text("This component has already been added to this object!");
			if (ImGui::Button("Close"))
			{
				bIsComponentAlreadyAddedWindowEnable = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}

	void InspectorGUI::DrawAddCameraComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Camera", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Camera", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::Camera* camera = _crtGOSelected->GetComponent<Core::Camera>();
				if (!camera)
					camera = _crtGOSelected->AddComponent<Core::Camera>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddRendererComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Renderer", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Model", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::Model* model = _crtGOSelected->GetComponent<Core::Model>();
				if (!model)
				{
					model = _crtGOSelected->AddComponent<Core::Model>();
					Resource::Mesh* mesh = Resource::ResourceManager::GetInstance().GetResource<Resource::Mesh>("Cube.obj");
					Resource::Texture* texture = Resource::ResourceManager::GetInstance().GetResource<Resource::Texture>("WhiteTexture.img");
					Resource::ShaderProgram* shader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>("DefaultDeferredRendering.shd");
					model->SetData(mesh, texture, shader);
				}
				else
				{
					bIsComponentAlreadyAddedWindowEnable = true;
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddColliderComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Collider", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Box Collider", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::BoxCollider* boxCollider = _crtGOSelected->GetComponent<Core::BoxCollider>();
				if (!boxCollider)
				{
					boxCollider = _crtGOSelected->AddComponent<Core::BoxCollider>();
					boxCollider->SetPosition(_crtGOSelected->transform->GetPosition());
					boxCollider->SetRotation(_crtGOSelected->transform->GetRotation());
					boxCollider->Scale(_crtGOSelected->transform->GetScale());
				}
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Capsule Collider", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::CapsuleCollider* capsuleCollider = _crtGOSelected->GetComponent<Core::CapsuleCollider>();
				if (!capsuleCollider)
				{
					capsuleCollider = _crtGOSelected->AddComponent<Core::CapsuleCollider>();
					capsuleCollider->SetPosition(_crtGOSelected->transform->GetPosition());
					capsuleCollider->SetRotation(_crtGOSelected->transform->GetRotation());
					capsuleCollider->Scale(_crtGOSelected->transform->GetScale());
				}
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Mesh Collider", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::MeshCollider* meshCollider = _crtGOSelected->GetComponent<Core::MeshCollider>();
				if (!meshCollider)
				{
					meshCollider = _crtGOSelected->AddComponent<Core::MeshCollider>();
					meshCollider->SetPosition(_crtGOSelected->transform->GetPosition());
					meshCollider->SetRotation(_crtGOSelected->transform->GetRotation());
					Core::Model* model = _crtGOSelected->GetComponent<Core::Model>();
					if (model != nullptr)
						meshCollider->SetMeshScale(model->GetMesh(), _crtGOSelected->transform->GetScale());
					else
						meshCollider->Scale(_crtGOSelected->transform->GetScale());
				}
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddLightComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Light", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Directional Light", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::DirectionalLight* directionalLight = _crtGOSelected->GetComponent<Core::DirectionalLight>();
				if (!directionalLight)
					_crtGOSelected->AddComponent<Core::DirectionalLight>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Point Light", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::PointLight* pointLight = _crtGOSelected->GetComponent<Core::PointLight>();
				if (!pointLight)
					_crtGOSelected->AddComponent<Core::PointLight>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Spot Light", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::SpotLight* SpotLight = _crtGOSelected->GetComponent<Core::SpotLight>();
				if (!SpotLight)
					_crtGOSelected->AddComponent<Core::SpotLight>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddAudioComponent(Core::GameObject* _crtGOSelected)
	{
		if (ImGui::TreeNodeEx("Audio", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Audio Source", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::AudioSource* audioSource = _crtGOSelected->GetComponent<Core::AudioSource>();
				if (!audioSource)
					_crtGOSelected->AddComponent<Core::AudioSource>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Audio Listener", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::AudioListener* audioListener = _crtGOSelected->GetComponent<Core::AudioListener>();
				if (!audioListener)
					_crtGOSelected->AddComponent<Core::AudioListener>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}

	void InspectorGUI::DrawAddParticlesComponent(Core::GameObject* _crtGOSelected)
	{
		_crtGOSelected;
		if (ImGui::TreeNodeEx("Particles", m_treeNodeAddComponentFlags))
		{
			if (ImGui::Button("Particle Emitter", ImVec2(ImGui::GetContentRegionAvail().x, 30.f)))
			{
				Core::ParticleEmitter* particleEmitter = _crtGOSelected->GetComponent<Core::ParticleEmitter>();
				if (!particleEmitter)
					_crtGOSelected->AddComponent<Core::ParticleEmitter>();
				else
					bIsComponentAlreadyAddedWindowEnable = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::TreePop();
		}
	}
}