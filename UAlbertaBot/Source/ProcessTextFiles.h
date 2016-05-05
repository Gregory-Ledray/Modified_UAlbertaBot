#pragma once

#include "Common.h"

namespace UAlbertaBot
{
	class ProcessTextFiles
	{
	private:
		std::ifstream scouting_data;
		int frame;
		int estimated_game_number;

		std::vector<std::pair<int, int>> worker_count_aa;
		int worker_count_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_workers_on_minerals_aa;
		int enemy_workers_on_minerals_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_workers_on_gas_aa;
		int enemy_workers_on_gas_2d[4000][30];
		std::vector<std::pair<int, int>> military_minerals_spent_aa;
		int military_minerals_spent_2d[4000][30];
		std::vector<std::pair<int, int>> military_gas_spent_aa;
		int military_gas_spent_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_military_supply_used_aa;
		int enemy_military_supply_used_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_upgrade_minerals_spent_aa;
		int enemy_upgrade_minerals_spent_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_upgrade_gas_spent_aa;
		int enemy_upgrade_gas_spent_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_building_minerals_spent_aa;
		int enemy_building_minerals_spent_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_minerals_on_hand_aa;
		int enemy_minerals_on_hand_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_gas_on_hand_aa;
		int enemy_gas_on_hand_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_supply_total_aa;
		int enemy_supply_total_2d[4000][30];
		std::vector<std::pair<int, int>> enemy_supply_used_aa;
		int enemy_supply_used_2d[4000][30];

	public:
		void post_game_analysis(char *path);
		static int last_frame;

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