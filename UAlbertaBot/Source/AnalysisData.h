#pragma once

#include "Common.h"
#include "UnitUtil.h"

namespace UAlbertaBot
{

	class AnalysisData
	{
    		static int worker_count;
			static int military_minerals_spent;
			static int military_gas_spent;
			static int upgrade_minerals_spent;
			static int upgrade_gas_spent;
			static int building_minerals_spent;
			static int building_gas_spent;
			static int gas_count;//#workers on gas
			static int mineral_count;//#workers on minerals
    		int minerals_on_hand;
    		int gas_on_hand;
			int supply;
			static int mil_units_total_supply;
    		
    		std::vector<BWAPI::Unit> Unit_List;
    		std::vector<BWAPI::Unit> Building_List;
			static BWAPI::Unitset Military_Unit_List;

			static int previous_enemy_worker_count;//
			static int previous_enemy_gas_count;
			static int previous_enemy_mineral_count;
			static int previous_enemy_military_minerals_spent;//
			static int previous_enemy_military_gas_spent;//
			static int previous_enemy_supply_used;//
			static int previous_enemy_upgrade_minerals_spent;//
			static int previous_enemy_upgrade_gas_spent;//
			static int previous_enemy_building_minerals_spent;//
			static int previous_enemy_minerals_on_hand;
			static int previous_enemy_gas_on_hand;
			static int previous_enemy_supply_total;//

			AnalysisData();
    
	public:
		static AnalysisData & Instance();

		//AnalysisData();
		void Update();
		void writeData();
		void buildInfo(int minerals_used, int gas_used);//these are called in productionmanager.cpp around line 350
		void techAndUpgradeInfo(int minerals_used, int gas_used);
		void unitBuildInfo(int minerals_used, int gas_used);
		void AnalysisData::workerInfo(int count, int mineral_count, int gas_count);
		void gameOver(bool win);
		void updateMilitary_Unit_List(BWAPI::Unitset unit);

		void writeScoutData();
		void updateScoutData();
	};

}
