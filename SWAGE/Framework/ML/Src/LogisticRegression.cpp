#include "Precompiled.h"

#include "Datasets.h"
#include "LogisticRegression.h"

using namespace SWAGE::ML;

float LogisticRegression::Fit(const Dataset & dataset)
{
	const int datasetSize = static_cast<int>(dataset.x0.size());

	float averageError = 0.0f;
	float errorForB0 = 0.0f;
	float errorForB1 = 0.0f;
	float errorForB2 = 0.0f;

	for (int i = 0; i < datasetSize; ++i)
	{
		const float x0 = dataset.x0[i];
		const float x1 = dataset.x1[i];
		const float y = dataset.y[i];
		const float predictY = Predict(x0, x1);
		const float error = predictY - y;

		const float cost = ((-1 * y) * log(predictY)) - ((1 - y) * log(1 - predictY));

		errorForB0 += error * 1.0f;
		errorForB1 += error * x0;
		errorForB2 += error * x1;

		averageError += cost;
	}

	errorForB0 /= datasetSize;
	errorForB1 /= datasetSize;
	errorForB2 /= datasetSize;

	b0 -= learningRate * errorForB0;
	b1 -= learningRate * errorForB1;
	b2 -= learningRate * errorForB2;

	averageError /= datasetSize;

	return averageError;
}

float LogisticRegression::Predict(float x0, float x1) const
{
	float z = b0 + (b1 * x0) + (b2 * x1);
	return 1 / (1 + exp(-z));
}

void LogisticRegression::Reset(const float B0, const float B1, const float B2, const float LearningRate)
{
	b0 = B0;
	b1 = B1;
	b2 = B2;
	learningRate = LearningRate;
}
