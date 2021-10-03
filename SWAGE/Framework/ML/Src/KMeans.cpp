#include "Precompiled.h"

#include "Datasets.h"
#include "KMeans.h"

using namespace SWAGE::ML;

float KMeans::Fit(const Dataset & dataset)
{
	return Math::RandomFloat(0, 1);
}

size_t KMeans::Predict(float x0, float x1) const
{
	return 0;
}
