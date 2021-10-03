#pragma once

namespace SWAGE::ML
{
	class Neuron;
	using Layer = std::vector<Neuron>;

	struct Connection
	{
		float weight;
	};

	class Neuron
	{
	public:
		Neuron(size_t numOutputs, size_t myIndex, bool isBias);

		void SetOutputValue(float value) { mOutputValue = value; }
		float GetOutputValue() const { return mOutputValue; }

		void FeedForward(const Layer& previousLayer);
		void CalculateOutputGradients(float targetValue);
		void CalculateHiddenGradients(const Layer& nextLayer);
		void UpdateInputWeights(Layer& previousLayer);

	private:
		std::vector<Connection> mOutputWeights;
		size_t mMyIndex = 0;
		float mOutputValue = 0.0f;
		float mGradient = 0.0f;
	};

	class NeuralNetwork
	{
	public:
		NeuralNetwork(const std::vector<size_t>& topology);

		void FeedFoward(const std::vector<float>& inputValues);
		void BackPropagate(const std::vector<float>& targetValues);
		std::vector<float> GetResults() const;

	private:
		std::vector<Layer> mLayers;
	};
}