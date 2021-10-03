#include "Precompiled.h"
#include "TransformComponent.h"

using namespace SWAGE;

MEMPOOL_DEFINE(TransformComponent, 1000)

void TransformComponent::DebugUI()
{
	Graphics::SimpleDraw::AddLine(mPosition, mPosition + Math::Vector3::XAxis, Graphics::Colors::Red);
	Graphics::SimpleDraw::AddLine(mPosition, mPosition + Math::Vector3::YAxis, Graphics::Colors::Green);
	Graphics::SimpleDraw::AddLine(mPosition, mPosition + Math::Vector3::ZAxis, Graphics::Colors::Blue);
}
