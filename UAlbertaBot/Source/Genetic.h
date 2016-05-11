#pragma once

#include "Common.h"
#include "BuildOrder.h"
#include "UnitUtil.h"
#include "UnitData.h"

#define NUMBER_ORGANISMS 10
#define NUMBER_GENES     6//different unit types 
#define MUTATION_RATE    0.001

#define MAXIMUM_FITNESS NUMBER_GENES
#define FALSE 0
#define TRUE  1 

namespace UAlbertaBot
{
	class Genetic
	{
	private:
		// global variables
		int currentGeneration[NUMBER_ORGANISMS][NUMBER_GENES + 1],
			nextGeneration[NUMBER_ORGANISMS][NUMBER_GENES + 1];
		int organismsFitnesses;
		int totalOfFitnesses;
		BWAPI::UnitType terran_units[NUMBER_GENES];

		Genetic();
	public:
		static Genetic & Instance();
		void InitializeOrganisms(int terran_heuristic, int enemy_heuristic);
		void EvaluateOrganisms(int terran_heuristic, int enemy_heuristic);
		void ProduceNextGeneration();
		int SelectOneOrganism();
	};
}