#pragma once

namespace SWAGE::ML
{
	struct Dataset;

	class KMeans
	{
	public:
		float Fit(const Dataset& dataset);
		size_t Predict(float x0, float x1) const;

		std::vector<std::array<float, 2>> centroids0;
		std::vector<size_t> assignments;
	};
}