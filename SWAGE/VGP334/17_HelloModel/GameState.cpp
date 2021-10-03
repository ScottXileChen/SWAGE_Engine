#include "GameState.h"

using namespace SWAGE::Graphics;
using namespace SWAGE::Input;
using namespace SWAGE::Math;

namespace
{
	bool SpecularMapOn = false;
	bool NormalMapOn = false;
	float displacementWeight = 0.0f;
	int specularMapColor = 0;
	bool skeleton = true;
	float animationSpeed = 1;
	int animIndex = 0;

}

void GameState::Initialize()
{
	mCamera.SetNearPlane(0.1f);
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->SetClearColor(SWAGE::Graphics::Colors::Gray);

	mModel[0].Initialize(L"../../Assets/Models/Maria/maria_b.model", true);
	mModel[1].Initialize(L"../../Assets/Models/Vanguard/vanguard_b.model", true);
	mModel[2].Initialize(L"../../Assets/Models/Archer/archer_b.model", true);
	mAnimator[0].Initialize(&mModel[0]);
	mAnimator[1].Initialize(&mModel[1]);
	mAnimator[2].Initialize(&mModel[2]);

	ModelLoader::LoadAnimation(L"../../Assets/Models/Vanguard/dance.anim", mModel[1], true);
	mAnimator[0].Play();
	mAnimator[1].Play();
	mAnimator[2].Play();

	mAnimator[0].SetLooping(true);
	mAnimator[1].SetLooping(true);
	mAnimator[2].SetLooping(true);

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
	mTransformBuffer2.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingBuffer.Initialize();
	mBoneTransformBuffer.Initialize();

	mPosition.z = 5.0f;

	mDirectionalLight.direction = { 0.577f, -0.577f, 0.577f };
	mDirectionalLight.ambient = { 0.2f,0.2f,0.2f,1.0f };
	mDirectionalLight.diffuse = { 0.9f,0.9f,0.9f,1.0f };
	mDirectionalLight.specular = { 0.2f,0.2f,0.2f,1.0f };

	mMaterial.ambient = mModel[2].materialData[2].material.ambient;
	mMaterial.diffuse = mModel[2].materialData[2].material.diffuse;
	mMaterial.specular = mModel[2].materialData[2].material.specular;
	mMaterial.power = mModel[2].materialData[2].material.power;
}

void GameState::Terminate()
{
	mBlendState.Terminate();
	mTextureVertexShader.Terminate();
	mCloudVertexShader.Terminate();
	mTexturePixelShader.Terminate();
	mCloudPixelShader.Terminate();
	mModel[0].Terminate();
	mModel[1].Terminate();
	mModel[2].Terminate();
	mTransformBuffer.Terminate();
	mTransformBuffer2.Terminate();
	mLightBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mSettingBuffer.Terminate();
	mBoneTransformBuffer.Terminate();
	for (size_t i = 0; i < std::size(mSamplers); i++)
		mSamplers[i].Terminate();
}

void GameState::Update(float deltaTime)
{
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::LEFT))
		mRotation.y += deltaTime;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::RIGHT))
		mRotation.y -= deltaTime;

	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::UP))
		mRotation.x += deltaTime;
	if (SWAGE::Input::InputSystem::Get()->IsKeyDown(SWAGE::Input::KeyCode::DOWN))
		mRotation.x -= deltaTime;

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

	mCloudRotation -= deltaTime * 0.1f;
	mAnimationTime += deltaTime;
	mFPS = 1.0f / deltaTime;

	mAnimator[0].Update(deltaTime);
	mAnimator[1].Update(deltaTime);
	mAnimator[2].Update(deltaTime);

	mAnimator[1].PlayAnimation(animIndex);

}

void GameState::Render()
{
	SWAGE::Math::Matrix4 matView = mCamera.GetViewMatrix();
	SWAGE::Math::Matrix4 matProj = mCamera.GetProjectionMatrix();

	TransformData transformData;
	TransformData2 skyBoxtransformData2;

	mSamplers[1].BindVS(0);

	mTextureVertexShader.Bind();
	mTexturePixelShader.Bind();

	SWAGE::Math::Matrix4 matWorld = Matrix4::RotationX(20) * Matrix4::Translation(mCamera.GetPosition());
	skyBoxtransformData2.wvp = SWAGE::Math::Transpose(matWorld * matView * matProj);
	mTransformBuffer2.Update(skyBoxtransformData2);

	mTransformBuffer2.BindVS(0);

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

	mPosition.x = 0;
	for (int i = 0; i < std::size(mModel); ++i)
	{
		mPosition.x = i * 2.0f;
		matWorld = SWAGE::Math::Matrix4::RotationX(mRotation.x) * Matrix4::RotationY(mRotation.y) * Matrix4::Translation(mPosition);
		transformData.world = SWAGE::Math::Transpose(matWorld);
		transformData.wvp[0] = SWAGE::Math::Transpose(matWorld * matView * matProj);
		mTransformBuffer.Update(transformData);

		if (!skeleton)
		{
			//auto& animationClip = mModel[i].animSet[0];
			//std::vector<Matrix4> toLocalTransform = SWAGE::Graphics::CalculateSkinningMatrices(*(mModel[i].skeleton), *animationClip, mAnimationTime * animationSpeed);
			////toLocalTransform = SWAGE::Graphics::CalculateBoneMatrices(*(mModel[2].skeleton), Matrix4::Identity);
			////toLocalTransform = SWAGE::Graphics::CalculateSkinningMatrices(*(mModel[2].skeleton));

			//// Apply offset transform to align the model to bone space
			BoneTransformData boneData;

			auto& bones = mModel[i].skeleton.get()->bones;
			auto tolocal = mAnimator[i].GetToLocalTransform();
			for (auto& bone : bones)
				boneData.boneTransforms[bone->index] = SWAGE::Math::Transpose(tolocal[bone->index]);

			mBoneTransformBuffer.Update(boneData);
			mBoneTransformBuffer.BindVS(4);
			//mBoneTransformBuffer.BindPS(4);

			for (const auto& meshdata : mModel[i].meshData)
			{
				auto& material = mModel[i].materialData[meshdata->materialIndex];
				material.diffuseMap->BindPS(0);
				material.normalMap->BindPS(3);
				meshdata->meshBuffer.Render();
			}
		}
		else
		{
			auto& animationClip = mModel[i].animSet[0];
			//SWAGE::Graphics::DrawSkeleton(
			//	*(mModel[i].skeleton),
			//	SWAGE::Graphics::CalculateBoneMatrices(*(mModel[i].skeleton), matWorld, *animationClip, mAnimationTime * animationSpeed),
			//	SWAGE::Graphics::Skeleton::DrawType::line);
			auto skeleton = mAnimator[i].GetSkeletonTransform();
			SWAGE::Graphics::DrawSkeleton(
				*(mModel[i].skeleton),
				skeleton,
				SWAGE::Graphics::Skeleton::DrawType::line);
		}
	}

	if (skeleton)
		SimpleDraw::Render(mCamera);
	// Set cloud texture
	// Set texturing shader
	// Set transform + scaling transfrom + auto rotation
	// turn on alpha blending
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("FPS: %f", mFPS);
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

	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Rotation", (float*)&mRotation, 0.01f);
	}

	ImGui::Checkbox("Show Skeleton", &skeleton);
	ImGui::DragFloat("Animation Speed", &animationSpeed, 0.01f, 0.0f, 5.0f);

	ImGui::DragInt("Anim index", &animIndex);

	ImGui::End();
}

// Device interface - used for VRAM allocation/resource creation
// Context interface - used to issue draw commands