#pragma once

namespace SWAGE::ML
{
	class GeneticAlgorithm
	{
	public:
		// Genome -> chromosomes -> genes
		struct Genome
		{
			std::vector<int> chromosome; // [gene][gene][gene][gene]...
			float fitness = 0.0f;
		};

		using ComputeFitnessFunc = std::function<float(const Genome&)>;
		using CrossoverFunc = std::function<void(Genome&, const Genome&, const Genome&)>;
		using MutateFunc = std::function<void(Genome&)>;
		using SelectionFunc = std::function<int(const std::vector<Genome>&)>;
		using GeneratePopulationFunc = std::function<void(std::vector<Genome>&)>;

		void Initialize(
			int populationSize,
			int chromoLength,
			int maxGeneValue,
			ComputeFitnessFunc computeFitness,
			CrossoverFunc crossover,
			MutateFunc mutate);
		void Initialize(
			int populationSize,
			int chromoLength,
			int maxGeneValue,
			GeneratePopulationFunc generatePopulation,
			ComputeFitnessFunc computeFitness,
			CrossoverFunc crossover,
			MutateFunc mutate);
		void Advance(float elitismPercentage = 10);

		const Genome& GetBestGenome() const { return mPopulation.front(); }
		int GetGeneration() const { return mGeneration; }

	private:
		void EvaluatePopulation();
		Genome Mate(const Genome& parent1, const Genome& parent2);

		ComputeFitnessFunc mComputeFitness;
		CrossoverFunc mCrossover;
		MutateFunc mMutate;

		std::vector<Genome> mPopulation;
		int mGeneration = 0;
		int mMaxGeneValue = 0;
	};
}