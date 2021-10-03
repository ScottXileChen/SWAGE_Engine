#pragma once

#include "Config.h"

namespace SWAGE::ML::NEAT
{
	struct Genome;

	struct Neuron
	{
		enum class Type { Hidden, Input, Output, Bias };

		std::vector<std::pair<size_t, double>> inNodes; // Node index and weight pair
		Type type = Type::Hidden;
		double value = 0.0;
		bool visited = false;
	};

	class NeuralNet
	{
	public:
		void Initialize(const Genome& genome, const NeuralNetConfig& netConfig);

		std::vector<double> Evaluate(const std::vector<double>& input);

	private:
		std::vector<Neuron> mNodes;

		// Indices to the neurons
		std::vector<size_t> mInputNodes;
		std::vector<size_t> mBiasNodes;
		std::vector<size_t> mOutputNodes;
	};
}