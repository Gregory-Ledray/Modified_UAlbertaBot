#pragma once

#include "Common.h"

namespace UAlbertaBot
{
	class ProcessTextFiles
	{
	private:
		std::ifstream scouting_data;
		int frame;

		std::vector<std::pair<int, int>> worker_count_aa;
		std::vector<std::pair<int, int>> enemy_workers_on_minerals_aa;
		std::vector<std::pair<int, int>> enemy_workers_on_gas_aa;
		std::vector<std::pair<int, int>> military_minerals_spent_aa;
		std::vector<std::pair<int, int>> military_gas_spent_aa;
		std::vector<std::pair<int, int>> enemy_military_supply_used_aa;
		std::vector<std::pair<int, int>> enemy_upgrade_minerals_spent_aa;
		std::vector<std::pair<int, int>> enemy_upgrade_gas_spent_aa;
		std::vector<std::pair<int, int>> enemy_building_minerals_spent_aa;
		std::vector<std::pair<int, int>> enemy_minerals_on_hand_aa;
		std::vector<std::pair<int, int>> enemy_gas_on_hand_aa;
		std::vector<std::pair<int, int>> enemy_supply_total_aa;

	public:
		void post_game_analysis();

		static ProcessTextFiles & Instance();

		void workerMineralsSpent();
		void workerCount();
		void workersOnMinerals();
		void workersOnGas();
		void militaryMineralsSpent();
		void militaryGasSpent();
		void militaryUnitSupplyUsed();
		void upgradeMineralsSpent();
		void upgradeGasSpent();
		void buildingMineralsSpent();
		void mineralsOnHand();
		void gasOnHand();
		void supplyTotal();
		void supplyUsed();
	};
}