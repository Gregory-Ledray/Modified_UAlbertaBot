#include "Common.h"
#include "ProcessTextFiles.h"

using namespace UAlbertaBot;
ProcessTextFiles & ProcessTextFiles::Instance()
{
	static ProcessTextFiles instance;
	return instance;
}

void ProcessTextFiles::post_game_analysis()
{
	const char *path = "C:/Users/Gregory/Desktop/ualbertabot_2/scouting_data_out.txt";
	scouting_data.open(path, std::ifstream::in);
	if (scouting_data.is_open())
	{
		scouting_data.seekg(0, scouting_data.beg);//start at the beginning
		char input[42];
		char out[10];
		while (scouting_data.getline(input, 42) && input[0] != 'G')//while the game isn't over
		{
			//worker count
			int x = 0;
			for (int i = 14; i < 16; i++)
			{
				if (!std::isspace(input[i]))
				{
					out[x] = input[i];
					x++;
				}
			}
			int temp = atoi(out);

			x = 0;
			for (int i = 22; i < 35; i++)
			{
				if (!std::isspace(input[i]) && input[i] != NULL)
				{
					out[x] = input[i];
					x++;
				}
			}
			frame = atoi(out);
			worker_count_aa.push_back(std::make_pair(temp, frame));

			//workers minerals spent
			ProcessTextFiles::workerMineralsSpent();
		}



	}
	scouting_data.close();
	/*

	int dead_worker_count = player->deadUnitCount(BWAPI::UnitTypes::Terran_SCV);
	int enemy_workers_minerals_spent = 50 * (enemy_worker_count - 4 + dead_worker_count);
	data_file << "workers minerals spent: " + std::to_string(enemy_workers_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

	data_file << "workers on minerals: " + std::to_string(enemy_workers_on_minerals) + " frame: " + std::to_string(frame) + " \n";

	data_file << "workers on gas: " + std::to_string(enemy_workers_on_gas) + " frame: " + std::to_string(frame) + " \n";

	//military_minerals_spent = player->spentMinerals() + player->refundedMinerals() - upgrade_minerals_spent - building_minerals_spent;
	data_file << "military minerals spent: " + std::to_string(enemy_military_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

	//military_gas_spent = player->spentGas() + player->refundedGas() - workers_minerals_spent - upgrade_minerals_spent - building_gas_spent; //should be less than spentGas
	data_file << "military gas spent: " + std::to_string(enemy_military_gas_spent) + " frame: " + std::to_string(frame) + " \n";

	data_file << "military unit supply used: " + std::to_string(enemy_supply_used - enemy_worker_count) + " frame: " + std::to_string(frame) + " \n";

	data_file << "upgrade minerals spent: " + std::to_string(enemy_upgrade_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

	data_file << "upgrade gas spent: " + std::to_string(enemy_upgrade_gas_spent) + " frame: " + std::to_string(frame) + " \n";

	data_file << "building minerals spent: " + std::to_string(enemy_building_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

	data_file << "minerals on hand: " + std::to_string(enemy_minerals_on_hand) + " frame: " + std::to_string(frame) + " \n";

	data_file << "gas on hand: " + std::to_string(enemy_gas_on_hand) + " frame: " + std::to_string(frame) + " \n";

	data_file << "supply: " + std::to_string(enemy_supply_total / 2) + " frame: " + std::to_string(frame) + " \n\n\n";

	*/
}

void ProcessTextFiles::workerMineralsSpent()
{
	char input[42];
	char out[10];
	scouting_data.getline(input, 42);

	int x = 0;
	for (int i = 14; i < 16; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
	}
	int temp = atoi(out);

	worker_count_aa.push_back(std::make_pair(temp, frame));
}

void ProcessTextFiles::workersOnMinerals()
{

}

void ProcessTextFiles::workersOnGas()
{

}

void ProcessTextFiles::militaryMineralsSpent()
{

}

void ProcessTextFiles::militaryGasSpent()
{

}

void ProcessTextFiles::militaryUnitSupplyUsed()
{

}

void ProcessTextFiles::upgradeMineralsSpent()
{

}

void ProcessTextFiles::upgradeGasSpent()
{

}

void ProcessTextFiles::buildingMineralsSpent()
{

}

void ProcessTextFiles::mineralsOnHand()
{

}

void ProcessTextFiles::gasOnHand()
{

}

void ProcessTextFiles::supplyUsed()
{

}

void ProcessTextFiles::supplyTotal()
{

}