#include "Common.h"
#include "StrategyManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "Genetic.h"
#include "UnitUtil.h"
#include "UnitData.h"

using namespace UAlbertaBot;
//heavily modified:
// file: geneticAlgorithm1.c
// by: John LeFlohic
// use: simulates a species' convergence to a model
// made: February 24, 1999

Genetic::Genetic()
{
}

Genetic & Genetic::Instance()
{
	static Genetic instance;
	return instance;
}

void Genetic::InitializeOrganisms(int terran_heuristic, int enemy_heuristic){
	int organism;
	int gene;
	int max_unit_quantities[6] = {
		3,//marine
		3,//medic
		3,//wraith
		3,//vulture
		3,//goliath
		3//tank
	};
	//terran_units[6] = {BWAPI::UnitTypes::Terran_Marine, BWAPI::UnitTypes::Terran_Medic,
	//	BWAPI::UnitTypes::Terran_Wraith, BWAPI::UnitTypes::Terran_Vulture,
	//	BWAPI::UnitTypes::Terran_Goliath, BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode };

	// initialize the normal organisms
	for (organism = 0; organism < NUMBER_ORGANISMS; ++organism){
		for (gene = 0; gene < NUMBER_GENES; ++gene){
			currentGeneration[organism][gene] = (abs(rand()) % max_unit_quantities[gene]);
		}
		for (organism = 0; organism < NUMBER_ORGANISMS; ++organism){
			currentGeneration[organism][gene + 1] = (enemy_heuristic - terran_heuristic);
		}
	}
}
void Genetic::EvaluateOrganisms(int terran_heuristic, int enemy_heuristic){
	int organism;
	int gene;


	for (organism = 0; organism<NUMBER_ORGANISMS; ++organism){
		for (gene = 0; gene<NUMBER_GENES; ++gene){
			currentGeneration[organism][NUMBER_GENES + 1] -= currentGeneration[organism][gene] * (
				currentGeneration[organism][gene]);// +terran_units[gene].supplyRequired();// +
				//terran_units[gene].defaultOreCost() + terran_units[gene].defaultGasCost());
		}
	}
}

void Genetic::ProduceNextGeneration(){
	int organism;
	int gene;
	int parentOne;
	int parentTwo;
	int crossoverPoint;
	int mutateThisGene;
	int max_unit_quantities[6] = {
		3,//marine
		3,//medic
		3,//wraith
		3,//vulture
		3,//goliath
		3//tank
	};


	for (organism = 0; organism < NUMBER_ORGANISMS; ++organism){
		parentOne = SelectOneOrganism();
		parentTwo = SelectOneOrganism();
		crossoverPoint = rand() % NUMBER_GENES;

		for (gene = 0; gene < NUMBER_GENES; ++gene){

			// copy over a single gene
			mutateThisGene = rand() % (int)(1.0 / MUTATION_RATE);
			if (mutateThisGene == 0){

				// mutate
				nextGeneration[organism][gene] = (abs(rand()) % max_unit_quantities[gene]);
			}
			else {
				// or copy this gene from a parent
				if (gene < crossoverPoint){
					nextGeneration[organism][gene] =
						currentGeneration[parentOne][gene];
				}
				else {
					nextGeneration[organism][gene] =
						currentGeneration[parentTwo][gene];
				}
			}
		}
	}
	//tell strategy manager things
	int best_heuristic = 0;
	int best_organism = 0;
	for (organism = 0; organism < NUMBER_ORGANISMS; ++organism){
		if (currentGeneration[organism][NUMBER_GENES + 1] > best_heuristic)
		{
			best_heuristic = currentGeneration[organism][NUMBER_GENES + 1];
			best_organism = organism;
		}
	}
	for (gene = 0; gene < NUMBER_GENES; ++gene){
		StrategyManager::Instance().best_organism[gene] = currentGeneration[best_organism][gene];

		// generation swap
		for (organism = 0; organism < NUMBER_ORGANISMS; ++organism){
			for (gene = 0; gene < NUMBER_GENES; ++gene){
				currentGeneration[organism][gene] =
					nextGeneration[organism][gene];
			}
		}
	}

}

	int Genetic::SelectOneOrganism(){
		int organism;
		int randomSelectPoint;

		randomSelectPoint = currentGeneration[rand() % NUMBER_ORGANISMS][NUMBER_GENES + 1];

		for (organism = 0; organism<NUMBER_ORGANISMS; ++organism){
			if (currentGeneration[organism][NUMBER_GENES + 1] >= randomSelectPoint) return organism;
		}//returns first organism better than a random organism.
	}
	//End of LeFlohic's code