#include "Common.h"
#include "AnalysisData.h"
#include "UnitUtil.h"
#include <fstream>
#include <iostream>
#include <string>
#include "UnitData.h"
#include "WorkerManager.h"
#include <ctime>


using namespace UAlbertaBot;
AnalysisData::AnalysisData()
	: minerals_on_hand(50)
	, gas_on_hand(0)
	, supply(0)
{
}

AnalysisData & AnalysisData::Instance()
{
	static AnalysisData instance;
	return instance;
}

void AnalysisData::Update()
{
	int frame = BWAPI::Broodwar->getFrameCount();
	if (frame % 10 == 0)
	{
		AnalysisData::Instance().writeData();
		AnalysisData::Instance().writeScoutData();
	}
}

void AnalysisData::buildInfo(int minerals_used, int gas_used)
{
	building_minerals_spent += minerals_used;
	building_gas_spent += gas_used;
}

void AnalysisData::techAndUpgradeInfo(int minerals_used, int gas_used)
{
	upgrade_gas_spent += gas_used;
	upgrade_minerals_spent += minerals_used;
}

void AnalysisData::unitBuildInfo(int minerals_used, int gas_used)
{
	military_minerals_spent += minerals_used;
	military_gas_spent += gas_used;
}

void AnalysisData::workerInfo(int count, int mineral_count_in, int gas_count_in)//gets called in ProductionManager.cpp at ~360
{
	worker_count = count;
	mineral_count = mineral_count_in;
	gas_count = gas_count_in;
}

void AnalysisData::gameOver(bool win)
{
	int w(0);
	if (win) w = 1;
	const char *path = "C:/Users/Gregory/Desktop/ualbertabot_2/data_out.txt";
	std::ofstream data_file;
	data_file.open(path, std::ofstream::out | std::ofstream::app);

	if (data_file.is_open())
	{
		data_file << "Game Over\n" << w << "\n\n";
	}
	else UAB_ASSERT(true, "Couldn't open the main file at game termination\n");

	const char *path2 = "C:/Users/Gregory/Desktop/ualbertabot_2/scouting_data_out.txt";
	std::ofstream data_file_2;
	data_file.open(path2, std::ofstream::out | std::ofstream::app);

	if (data_file_2.is_open())
	{
		data_file_2 << "Game Over\n" << w << "\n\n";
	}
	else UAB_ASSERT(true, "Couldn't open the scouting file at game termination\n");
}

//aupdating the list of military units
//called in line 62 of combatcommander
void AnalysisData::updateMilitary_Unit_List(BWAPI::Unitset unit)
{
	Military_Unit_List = unit;
	/*
	instead of messing around with this I just used supplyUsed-num_workers to get supply remaining
	mil_units_total_supply = 0;
	for (BWAPI::Unit i = *Military_Unit_List.begin(); i = *Military_Unit_List.end(); i++)
	{
		mil_units_total_supply += &i;
	}*/
}

void AnalysisData::writeData()
{
	int test_number = 0;

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	const char *path = "C:/Users/Gregory/Desktop/ualbertabot/data_out.txt";
	std::ofstream data_file;
	data_file.open(path, std::ofstream::out | std::ofstream::app);

	int frame = BWAPI::Broodwar->getFrameCount();

	if (data_file.is_open())
	{
		BWAPI::PlayerInterface * player = BWAPI::Broodwar->self();

		int gas_on_hand = player->gas();

		data_file << "worker count: " + std::to_string(worker_count) + " frame: " + std::to_string(frame) + " \n";

		int dead_worker_count = player->deadUnitCount(BWAPI::UnitTypes::Terran_SCV);
		int workers_minerals_spent = 50 * (worker_count - 4 + dead_worker_count);
		data_file << "workers minerals spent: " + std::to_string(workers_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

		data_file << "workers on minerals: " + std::to_string(mineral_count) + " frame: " + std::to_string(frame) + " \n";

		data_file << "workers on gas: " + std::to_string(gas_count) + " frame: " + std::to_string(frame) + " \n";

		//military_minerals_spent = player->spentMinerals() + player->refundedMinerals() - upgrade_minerals_spent - building_minerals_spent;
		data_file << "military minerals spent: " + std::to_string(military_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

		//military_gas_spent = player->spentGas() + player->refundedGas() - workers_minerals_spent - upgrade_minerals_spent - building_gas_spent; //should be less than spentGas
		data_file << "military gas spent: " + std::to_string(military_gas_spent) + " frame: " + std::to_string(frame) + " \n";

		int supply_used = player->supplyUsed();
		data_file << "military unit supply used: " + std::to_string(supply_used-worker_count) + " frame: " + std::to_string(frame) + " \n";

		data_file << "upgrade minerals spent: " + std::to_string(upgrade_minerals_spent) + " frame: " + std::to_string(frame) + " \n";
		
		data_file << "upgrade gas spent: " + std::to_string(upgrade_gas_spent) + " frame: " + std::to_string(frame) + " \n";
		
		data_file << "building minerals spent: " + std::to_string(building_minerals_spent) + " frame: " + std::to_string(frame) + " \n";
		
		minerals_on_hand = player->minerals();
		data_file << "minerals on hand: " + std::to_string(minerals_on_hand) + " frame: " + std::to_string(frame) + " \n";
		
		data_file << "gas on hand: " + std::to_string(gas_on_hand) + " frame: " + std::to_string(frame) + " \n";
		
		data_file << "supply: " + std::to_string((player->supplyTotal())/2) + " frame: " + std::to_string(frame) + " \n\n\n";

		data_file.close();
	}
	else UAB_ASSERT(true, "Couldn't open the file\n");
}

int AnalysisData::military_minerals_spent = 0;
int AnalysisData::military_gas_spent = 0;
int AnalysisData::upgrade_minerals_spent = 0;
int AnalysisData::upgrade_gas_spent = 0;
int AnalysisData::building_minerals_spent = 0;
int AnalysisData::building_gas_spent = 0;
int AnalysisData::worker_count = 5;
int AnalysisData::gas_count = 0;
int AnalysisData::mineral_count = 0;
int AnalysisData::mil_units_total_supply = 0;
BWAPI::Unitset AnalysisData::Military_Unit_List;

void AnalysisData::updateScoutData()
{
	int frame = BWAPI::Broodwar->getFrameCount();
	if (frame % 10 == 0)
		AnalysisData::Instance().writeScoutData();
}

void AnalysisData::writeScoutData()
{
	const char *path = "C:/Users/Gregory/Desktop/ualbertabot/scouting_data_out.txt";
	std::ofstream data_file;
	data_file.open(path, std::ofstream::out | std::ofstream::app);

	int frame = BWAPI::Broodwar->getFrameCount();

	int enemy_worker_count = 0;//
	int enemy_gas_count = 0;
	int enemy_mineral_count = 0;
	int enemy_military_minerals_spent = 0;//
	int enemy_military_gas_spent = 0;//
	int enemy_supply_used = 0;//
	int enemy_upgrade_minerals_spent = 0;//
	int enemy_upgrade_gas_spent = 0;//
	int enemy_building_minerals_spent = 0;//
	int enemy_minerals_on_hand = 0;
	int enemy_gas_on_hand = 0;
	int enemy_supply_total = 0;//

	for (auto & unit : BWAPI::Broodwar->enemy()->getUnits())
	{
		BWAPI::UnitType _unittype = unit->getType();
		if (_unittype.isWorker())
		{
			enemy_worker_count++;
			enemy_supply_used += _unittype.supplyRequired();
		}
		else if (_unittype.isBuilding() || _unittype.isAddon())
		{
			enemy_building_minerals_spent += _unittype.mineralPrice();
			enemy_supply_total += _unittype.supplyProvided();
			enemy_upgrade_gas_spent += _unittype.armorUpgrade().gasPrice() + _unittype.airWeapon().upgradeType().gasPrice() + _unittype.groundWeapon().upgradeType().gasPrice();
			enemy_upgrade_minerals_spent += _unittype.armorUpgrade().mineralPrice() + _unittype.airWeapon().upgradeType().mineralPrice() + _unittype.groundWeapon().upgradeType().mineralPrice();
			if (_unittype == BWAPI::UnitTypes::Terran_Command_Center)//account for free Command Center
				enemy_building_minerals_spent -= 400;
		}
		else if (!_unittype.isFlagBeacon())
		{
			//must be military units
			enemy_military_minerals_spent += _unittype.mineralPrice();
			enemy_military_gas_spent += _unittype.gasPrice();
			enemy_supply_used += _unittype.supplyRequired();
			enemy_upgrade_gas_spent += _unittype.armorUpgrade().gasPrice() + _unittype.airWeapon().upgradeType().gasPrice() + _unittype.groundWeapon().upgradeType().gasPrice();
			enemy_upgrade_minerals_spent += _unittype.armorUpgrade().mineralPrice() + _unittype.airWeapon().upgradeType().mineralPrice() + _unittype.groundWeapon().upgradeType().mineralPrice();

		}
	}

	//for all of these: need a flag to make sure they're only activated if no
	//enemy units have been killed/destroyed in the last 10 frames of the game.
	//if that is the case, then the new value could very well be smaller than the old
	if (previous_enemy_worker_count > enemy_worker_count)
	{
		enemy_worker_count = previous_enemy_worker_count;
	}
	if (previous_enemy_building_minerals_spent > enemy_building_minerals_spent)
	{
		enemy_building_minerals_spent = previous_enemy_building_minerals_spent;
	}
	if (previous_enemy_supply_used > enemy_supply_used)
	{
		enemy_supply_used = previous_enemy_supply_used;
	}
	if (previous_enemy_military_gas_spent > enemy_military_gas_spent)
		enemy_military_gas_spent = previous_enemy_military_gas_spent;
	if (previous_enemy_military_minerals_spent > enemy_military_minerals_spent)
		enemy_military_minerals_spent = previous_enemy_military_minerals_spent;
	if (previous_enemy_supply_total > enemy_supply_total)
	{
		enemy_supply_total = previous_enemy_supply_total;
	}

	bool dont_output = false;

	//if there's nothing to report... report nothing
	if (enemy_worker_count + enemy_gas_count + enemy_mineral_count + enemy_military_minerals_spent
		+ enemy_military_minerals_spent + enemy_military_gas_spent + enemy_supply_used + enemy_upgrade_minerals_spent
		+ enemy_upgrade_gas_spent + enemy_building_minerals_spent + enemy_minerals_on_hand + enemy_gas_on_hand 
		+ enemy_supply_total == 0)
		dont_output = true;

	if (data_file.is_open() && !dont_output)
	{
		BWAPI::PlayerInterface * player = BWAPI::Broodwar->enemy();

		data_file << "worker count: " + std::to_string(enemy_worker_count) + " frame: " + std::to_string(frame) + " \n";

		int dead_worker_count = player->deadUnitCount(BWAPI::UnitTypes::Terran_SCV);
		int enemy_workers_minerals_spent = 50 * (enemy_worker_count - 4 + dead_worker_count);
		data_file << "workers minerals spent: " + std::to_string(enemy_workers_minerals_spent) + " frame: " + std::to_string(frame) + " \n";

		data_file << "workers on minerals: " + std::to_string(enemy_mineral_count) + " frame: " + std::to_string(frame) + " \n";

		data_file << "workers on gas: " + std::to_string(enemy_gas_count) + " frame: " + std::to_string(frame) + " \n";

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

		data_file.close();
	}
	previous_enemy_worker_count = enemy_worker_count;//
	previous_enemy_gas_count = enemy_gas_count;
	previous_enemy_mineral_count = enemy_mineral_count;
	previous_enemy_military_minerals_spent = enemy_military_minerals_spent;//
	previous_enemy_military_gas_spent = enemy_military_gas_spent;//
	previous_enemy_supply_used = enemy_supply_used;//
	previous_enemy_upgrade_minerals_spent = enemy_upgrade_minerals_spent;//
	previous_enemy_upgrade_gas_spent = enemy_upgrade_gas_spent;//
	previous_enemy_building_minerals_spent = enemy_building_minerals_spent;//
	previous_enemy_minerals_on_hand = enemy_minerals_on_hand;
	previous_enemy_gas_on_hand = enemy_gas_on_hand;
	previous_enemy_supply_total = enemy_supply_total;//
}
int AnalysisData::previous_enemy_worker_count = 0;//
int AnalysisData::previous_enemy_gas_count = 0;
int AnalysisData::previous_enemy_mineral_count = 0;
int AnalysisData::previous_enemy_military_minerals_spent = 0;//
int AnalysisData::previous_enemy_military_gas_spent = 0;//
int AnalysisData::previous_enemy_supply_used = 0;//
int AnalysisData::previous_enemy_upgrade_minerals_spent = 0;//
int AnalysisData::previous_enemy_upgrade_gas_spent = 0;//
int AnalysisData::previous_enemy_building_minerals_spent = 0;//
int AnalysisData::previous_enemy_minerals_on_hand = 0;
int AnalysisData::previous_enemy_gas_on_hand = 0;
int AnalysisData::previous_enemy_supply_total = 0;//