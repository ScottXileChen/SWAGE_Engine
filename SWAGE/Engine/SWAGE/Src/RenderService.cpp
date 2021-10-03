#include "Precompiled.h"
#include "RenderService.h"

#include "AnimatorComponent.h"
#include "GameObject.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

namespace
{
	bool SpecularMapOn = false;
	bool NormalMapOn = false;
	float displacementWeight = 0.0f;
	int specularMapColor = 0;
	bool skeleton = false;
	float animationSpeed = 1;
	int animIndex = 0;
}

void RenderService::Initialize()
{
	mCamera.SetNearPlane(0.1f);
	mCamera.SetPosition({ 0.0f, 5.0f, -40.0f });
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Gray);

	mBlendState.Initialize(SWAGE::Graphics::BlendState::Mode::Additive);

	mCloudVertexShader.Initialize(L"../../Assets/Shaders/Earth_Cloud.fx", VertexPNX::Format);
	mCloudPixelShader.Initialize(L"../../Assets/Shaders/Earth_Cloud.fx");

	mTextureVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VertexPX::Format);
	mTexturePixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mVertexShader.Initialize(L"../../Assets/Shaders/Skinning.fx", BoneVertex::Format);
	mPixelShader.Initialize(L"../../Assets/Shaders/Skinning.fx");

	mSamplers[0].Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mSamplers[1].Initialize(Sampler::Filter::Anisotropic, Sampler::AddressMode::Wrap);
	mSamplers[2].Initialize(Sampler::Filter::Point, Sampler::AddressMode::Wrap);

	// Create constant buffer
	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();
	mBoneTransformBuffer.Initialize();

	mDirectionalLight.direction = { 0.577f, -0.577f, 0.577f };
	mDirectionalLight.ambient = { 0.2f,0.2f,0.2f,1.0f };
	mDirectionalLight.diffuse = { 0.9f,0.9f,0.9f,1.0f };
	mDirectionalLight.specular = { 0.2f,0.2f,0.2f,1.0f };
}

void RenderService::Terminate()
{
	mBlendState.Terminate();
	mTextureVertexShader.Terminate();
	mCloudVertexShader.Terminate();
	mTexturePixelShader.Terminate();
	mCloudPixelShader.Terminate();
	mTransformBuffer.Terminate();
	mLightBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mSettingBuffer.Terminate();
	mBoneTransformBuffer.Terminate();
	for (size_t i = 0; i < std::size(mSamplers); i++)
		mSamplers[i].Terminate();
}

void RenderService::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();
	const float moveSpeed = 10.0f;
	const float turnSpeed = 10.0f * Constants::DegToRad;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::W))
		mCamera.Walk(moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::S))
		mCamera.Walk(-moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::D))
		mCamera.Strafe(moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::A))
		mCamera.Strafe(-moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::Q))
		mCamera.Rise(moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::E))
		mCamera.Rise(-moveSpeed * deltaTime);
	if (SWAGE::Input::InputSystem::Get()->IsMouseDown(SWAGE::Input::MouseButton::RBUTTON))
	{
		mCamera.Yaw(SWAGE::Input::InputSystem::Get()->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(SWAGE::Input::InputSystem::Get()->GetMouseMoveY() * turnSpeed * deltaTime);
	}

	mAnimationTime += deltaTime;
}

void RenderService::Render()
{
	for (auto& entry : mRenderEntries)
	{
		auto model = entry.modelComponent->GetModel();
		mMaterial.ambient = model->materialData[0].material.ambient;
		mMaterial.diffuse = model->materialData[0].material.diffuse;
		mMaterial.specular = model->materialData[0].material.specular;
		mMaterial.power = model->materialData[0].material.power;
	}

	SWAGE::Math::Matrix4 matWorld = Matrix4::RotationX(20) * Matrix4::Translation(mCamera.GetPosition());
	SWAGE::Math::Matrix4 matView = mCamera.GetViewMatrix();
	SWAGE::Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	TransformData transformData;

	mSamplers[1].BindVS(0);

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	transformData.viewPosition = mCamera.GetPosition();
	mTransformBuffer.BindVS(0);
	mTransformBuffer.BindPS(0);

	mLightBuffer.Update(mDirectionalLight);
	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.Update(mMaterial);
	mMaterialBuffer.BindVS(2);
	mMaterialBuffer.BindPS(2);

	Setting setting;
	setting.displacementWeight = displacementWeight;
	setting.isNormalMapOn = NormalMapOn;
	setting.isSpecularMapOn = specularMapColor;
	setting.isSkinning = 1;
	mSettingBuffer.Update(setting);
	mSettingBuffer.BindVS(3);
	mSettingBuffer.BindPS(3);

	mVertexShader.Bind();
	mPixelShader.Bind();

	for (const auto& entry : mRenderEntries)
	{
		Vector3 position = entry.transformComponent->GetPosition();
		Quaternion rotation = entry.transformComponent->GetRotation();

		const auto model = entry.modelComponent->GetModel();

		if (entry.animatorComponent)
		{
			auto toLocal = entry.animatorComponent->GetAnimator().GetToLocalTransform();

			matWorld = Matrix4::RotationQuaternion(rotation) * Matrix4::Translation(position);
			//matWorld = SWAGE::Math::Matrix4::RotationX(rotation.x) * Matrix4::RotationY(rotation.y) * Matrix4::RotationZ(rotation.z) * Matrix4::Translation(position);
			transformData.world = SWAGE::Math::Transpose(matWorld);
			transformData.wvp[0] = SWAGE::Math::Transpose(matWorld * matView * matProj);
			mTransformBuffer.Update(transformData);

			if (!skeleton)
			{
				//// Apply offset transform to align the model to bone space
				BoneTransformData boneData;

				const auto& bones = model->skeleton.get()->bones;
				for (auto& bone : bones)
					boneData.boneTransforms[bone->index] = SWAGE::Math::Transpose(toLocal[bone->index]);

				mBoneTransformBuffer.Update(boneData);
				mBoneTransformBuffer.BindVS(4);

				for (const auto& meshdata : model->meshData)
				{
					auto& material = model->materialData[meshdata->materialIndex];
					material.diffuseMap->BindPS(0);
					material.normalMap->BindPS(3);
					meshdata->meshBuffer.Render();
				}
			}
			else
			{
				auto& animationClip = model->animSet[0];
				auto skeleton = entry.animatorComponent->GetAnimator().GetSkeletonTransform();
				for (auto& matrix : skeleton)
					matrix = matrix * matWorld;
				SWAGE::Graphics::DrawSkeleton(
					*(model->skeleton),
					skeleton,
					SWAGE::Graphics::Skeleton::DrawType::line);
			}
		}
	}
	SimpleDraw::Render(mCamera);
}

void RenderService::DebugUI()
{
	ImGui::Begin("Render Service", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	
	ImGui::Text("Animation Time: %f", mAnimationTime);

	const char* themeItems[] = { "Classic", "Dark","Light" };
	static int themeItemIndex = 0;
	if (ImGui::Combo("UI Theme", &themeItemIndex, themeItems, IM_ARRAYSIZE(themeItems)))
	{
		if (themeItemIndex == 0)
		{
			DebugUI::SetTheme(DebugUI::Theme::Classic);
		}
		else if (themeItemIndex == 1)
		{
			DebugUI::SetTheme(DebugUI::Theme::Dark);
		}
		else
		{
			DebugUI::SetTheme(DebugUI::Theme::Light);
		}
	}

	if (ImGui::CollapsingHeader("Light"))
	{
		if (ImGui::DragFloat3("Light Direction", &mDirectionalLight.direction.x, 0.01f))
			mDirectionalLight.direction = SWAGE::Math::Normalize(mDirectionalLight.direction);
		ImGui::ColorEdit3("Light Ambient", &mDirectionalLight.ambient.x);
		ImGui::ColorEdit3("Light Diffuse", &mDirectionalLight.diffuse.x);
		ImGui::ColorEdit3("Light Specular", &mDirectionalLight.specular.x);
	}

	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::ColorEdit3("Material Ambient", &mMaterial.ambient.x);
		ImGui::ColorEdit3("Material Diffuse", &mMaterial.diffuse.x);
		ImGui::ColorEdit3("Material Specular", &mMaterial.specular.x);
		ImGui::DragFloat("Material Power", &mMaterial.power);
	}

	if (ImGui::CollapsingHeader("Settings"))
	{
		ImGui::DragFloat("Displacement Weight", &displacementWeight, 0.1f);

		if (ImGui::Checkbox("Specular Map", &SpecularMapOn))
		{
			specularMapColor = SpecularMapOn ? 1 : 0;
		}
		ImGui::Checkbox("Normal Map", &NormalMapOn);
	}

	ImGui::Checkbox("Show Skeleton", &skeleton);
	ImGui::DragFloat("Animation Speed", &animationSpeed, 0.01f, 0.0f, 5.0f);

	ImGui::DragInt("Anim index", &animIndex);

	ImGui::End();
}

void SWAGE::RenderService::Register(const ModelComponent * modelComponent)
{
	auto& gameObject = modelComponent->GetOwner();
	Entry& entry = mRenderEntries.emplace_back();
	entry.animatorComponent = gameObject.GetComponent<AnimatorComponent>();
	entry.modelComponent = modelComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
}

void SWAGE::RenderService::Unregister(const ModelComponent * modelComponent)
{
	auto iter = std::find_if(mRenderEntries.begin(), mRenderEntries.end(), [&](const auto& entry)
		{
			return (entry.modelComponent == modelComponent);
		});
	if (iter != mRenderEntries.end())
	{
		mRenderEntries.erase(iter);
	}
}
