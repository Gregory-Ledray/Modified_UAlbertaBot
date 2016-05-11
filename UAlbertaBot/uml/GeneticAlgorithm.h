#pragma once

#include "Common.h"
#include "BuildOrder.h"
#include "UnitUtil.h"

#define NUMBER_ORGANISMS 10
#define NUMBER_GENES     20
#define ALLELES          4
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
		char **currentGeneration, **nextGeneration;
		char *modelOrganism;
		int *organismsFitnesses;
		int totalOfFitnesses;


		Genetic();
	public:
		static AnalysisData & Instance();
		void AllocateMemory(void);
		int DoOneRun(void);
		void InitializeOrganisms(void);
		int EvaluateOrganisms(void);
		void ProduceNextGeneration(void);
		int SelectOneOrganism(void);
	};
}