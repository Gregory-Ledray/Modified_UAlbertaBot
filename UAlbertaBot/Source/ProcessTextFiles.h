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

		int temp;

		int worker_count_2d[4000][30];
		int enemy_worker_minerals_spent_2d[4000][30];
		int enemy_workers_on_minerals_2d[4000][30];
		int enemy_workers_on_gas_2d[4000][30];
		int military_minerals_spent_2d[4000][30];
		int military_gas_spent_2d[4000][30];
		int enemy_military_supply_used_2d[4000][30];
		int enemy_upgrade_minerals_spent_2d[4000][30];
		int enemy_upgrade_gas_spent_2d[4000][30];
		int enemy_building_minerals_spent_2d[4000][30];
		int enemy_minerals_on_hand_2d[4000][30];
		int enemy_gas_on_hand_2d[4000][30];
		int enemy_supply_total_2d[4000][30];
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

		void takeInNextLine();
	};
}