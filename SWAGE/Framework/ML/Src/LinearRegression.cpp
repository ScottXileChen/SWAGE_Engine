#include "Precompiled.h"

#include "Datasets.h"
#include "LinearRegression.h"

using namespace SWAGE::ML;

float LinearRegression::Fit(const Dataset & dataset)
{
	const int datasetSize = static_cast<int>(dataset.x0.size());

	float totalErrorForb0 = 0.0f;
	float totalErrorForb1 = 0.0f;
	float MSE = 0.0f;

	for (int i = 0; i < datasetSize; ++i)
	{
		float predictY = Predict(dataset.x0[i]);
		float trueY = dataset.y[i];
		float error = predictY - trueY;
		totalErrorForb0 += error;
		totalErrorForb1 += error * dataset.x0[i];
		MSE += Math::Sqr(error);
	}

	totalErrorForb0 /= datasetSize;
	totalErrorForb1 /= datasetSize;
	MSE /= datasetSize;

	b0 -= learningRate * totalErrorForb0;
	b1 -= learningRate * totalErrorForb1;

	return MSE;
}

float LinearRegression::Predict(float X) const
{
	return b0 + (b1 * X);
}

void LinearRegression::Reset(const float B0, const float B1, const float LearningRate)
{
	b0 = B0;
	b1 = B1;
	learningRate = LearningRate;
}
