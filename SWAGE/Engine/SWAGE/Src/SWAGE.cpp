#include "Precompiled.h"
#include "SWAGE.h"

using namespace SWAGE;

App & SWAGE::MainApp()
{
	static SWAGE::App sApp;
	return sApp;
}