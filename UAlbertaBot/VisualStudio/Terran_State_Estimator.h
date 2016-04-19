#pragma once

#include "Common.h"
#include "BWTA.h"

namespace UAlbertaBot
{
	int worker_count = 0;
	double estimated_enemy_worker_count; //calculated via enemyWorkerCalculation();
	
	double military_resource_estimation;
	double military_resource_estimation_error;//calculated via enemyMilitaryCalculation();
	
	double observed_building_resources;
	double estimated_enemy_building_resources;//calculated via enemyBuildingCalcuation();
	
	double observed_upgrade_resources;
	double estimated_upgrade_resources;//calculated via enemyUpgradeResourcesCalcuation();
	
	double estimated_enemy_minerals_on_hand;
	double estimated_enemy_gas_on_hand;
	double estimated_total_enemy_minerals_mined;
	double estimated_total_enemy_gas_mined;//calculated via enemyResourceCalcuation();
	
	double observed_enemy_supply;
	double estimated_enemy_supply;//calculated via enemySupplyCalcuation();

	class Terran_State_Estimator
	{
		BWAPI::Race					    _selfRace;
		BWAPI::Race					    _enemyRace;

	public:
		bool enemyWorkerCalculation();
		bool enemyMilitaryCalculation();
		bool enemyBuildingCalcuation();
		bool enemyUpgradeResourcesCalcuation();
		bool enemyResourceCalcuation(); //includes resources on hand calculation
		bool enemySupplyCalcuation();
	};

}
