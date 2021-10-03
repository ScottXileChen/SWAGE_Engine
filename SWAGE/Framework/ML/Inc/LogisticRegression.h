#pragma once

namespace SWAGE::ML
{
	struct Dataset;

	class LogisticRegression
	{
	public:
		float Fit(const Dataset& dataset);
		float Predict(float x0, float x1) const;

		void Reset(const float B0 = 0.0f, const float B1 = 0.0f, const float B2 = 1.0f, const float LearningRate = 0.01f);

		float b0 = 0.1f;
		float b1 = 1.0f;
		float b2 = 1.0f;
		float learningRate = 0.01f;
	};
}