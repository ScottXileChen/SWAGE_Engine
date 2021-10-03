#include "Precompiled.h"
#include "GeneticAlgorithm.h"

using namespace SWAGE::Math;
using namespace SWAGE::ML;

namespace
{
	
}

void GeneticAlgorithm::Initialize(
	int populationSize,
	int chromoLength,
	int maxGeneValue,
	ComputeFitnessFunc computeFitness,
	CrossoverFunc crossover,
	MutateFunc mutate)
{
	mComputeFitness = std::move(computeFitness);
	mCrossover = std::move(crossover);
	mMutate = std::move(mutate);

	// Reset
	mGeneration = 0;
	mMaxGeneValue = maxGeneValue;

	//Create initial population
	mPopulation.clear();
	mPopulation.resize(populationSize);
	for (auto& genome : mPopulation)
	{
		genome.chromosome.reserve(chromoLength);
		for (int i = 0; i < chromoLength; ++i)
			genome.chromosome.push_back(Random(0, maxGeneValue));
	}
	EvaluatePopulation();
}

void GeneticAlgorithm::Initialize(
	int populationSize,
	int chromoLength,
	int maxGeneValue,
	GeneratePopulationFunc generatePopulation,
	ComputeFitnessFunc computeFitness,
	CrossoverFunc crossover,
	MutateFunc mutate)
{
	mComputeFitness = std::move(computeFitness);
	mCrossover = std::move(crossover);
	mMutate = std::move(mutate);

	// Reset
	mGeneration = 0;
	mMaxGeneValue = maxGeneValue;

	//Create initial population
	mPopulation.clear();
	generatePopulation(mPopulation);

	EvaluatePopulation();
}

void GeneticAlgorithm::Advance(float elitismPercentage)
{
	++mGeneration;

	std::vector<Genome> newPopulation;
	newPopulation.reserve(mPopulation.size());

	// Perform Elitism: keep top 10%, mate the rest using top 50%
	const int eliteCount = (int)(((int)mPopulation.size() * elitismPercentage) / 100);
	for (int i = 0; i < eliteCount; ++i)
		newPopulation.push_back(mPopulation[i]);

	const int mateCount = (int)mPopulation.size() - eliteCount;
	const int cutoff = (int)mPopulation.size() / 2;
	for (int i = 0; i < mateCount; ++i)
	{
		const auto& parent1 = mPopulation[Random(0, cutoff)];
		const auto& parent2 = mPopulation[Random(0, cutoff)];
		newPopulation.push_back(Mate(parent1, parent2));
	}

	mPopulation = std::move(newPopulation);
	EvaluatePopulation();
}

void GeneticAlgorithm::EvaluatePopulation()
{
	for (auto& genome : mPopulation)
		genome.fitness = mComputeFitness(genome);
	std::sort(mPopulation.begin(), mPopulation.end(), [](const auto& a, const auto& b) { return a.fitness > b.fitness; });
}

GeneticAlgorithm::Genome GeneticAlgorithm::Mate(const Genome& parent1, const Genome& parent2)
{
	Genome offspring;
	offspring.chromosome.reserve(parent1.chromosome.size());

	mCrossover(offspring, parent1, parent2);
	mMutate(offspring);

	//for (size_t i = 0; i < parent1.chromosome.size(); ++i)
	//{
	//	if (RandomFloat() < mMutationRate)
	//		offspring.chromosome.push_back(Random(0, mMaxGeneValue));
	//	else if (RandomFloat() < mCrossoverRate)
	//		offspring.chromosome.push_back(parent1.chromosome[i]);
	//	else
	//		offspring.chromosome.push_back(parent2.chromosome[i]);
	//}

	return offspring;
}
