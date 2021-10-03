#include "Precompiled.h"
#include "FontManager.h"

using namespace SWAGE;
using namespace SWAGE::Graphics;

namespace
{
	FontManager* sFontManager = nullptr;
}

void FontManager::StaticInitialize()
{
	ASSERT(sFontManager == nullptr, "[FontManager] Manager already initialized!");
	sFontManager = new FontManager();
	sFontManager->Initialize();
}

void FontManager::StaticTerminate()
{
	if (sFontManager != nullptr)
	{
		sFontManager->Terminate();
		SafeDelete(sFontManager);
	}
}

FontManager* FontManager::Get()
{
	ASSERT(sFontManager != nullptr, "[FontManager] No instance registered.");
	return sFontManager;
}

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	ASSERT(mTextCommands.empty(), "[sFontManager] Clear() must be called to clean up.");
}

void FontManager::Initialize()
{
	mFont.Initialize();
}

void FontManager::Terminate()
{
	mTextCommands.clear();
	mFont.Terminate();
}

void FontManager::AddText(const char * str, float size, float x, float y, const Color & color)
{
	int len = (int)strlen(str);
	int sizeNeeded = MultiByteToWideChar(CP_UTF8, 0, str, len, NULL, 0);
	std::wstring wstr(sizeNeeded, 0);
	MultiByteToWideChar(CP_UTF8, 0, str, len, &wstr[0], sizeNeeded);
	mTextCommands.emplace_back(std::move(wstr), size, x, y, color);
}

void FontManager::Draw()
{
	for (const auto& command : mTextCommands)
		mFont.Draw(command.str.c_str(), command.x, command.y, command.size, command.color);

	mTextCommands.clear();
}
