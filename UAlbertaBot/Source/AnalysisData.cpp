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
	//if anything has changed over the last few frames
	int frame = BWAPI::Broodwar->getFrameCount();
	if (frame%10==0)
		AnalysisData::Instance().writeData();
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
	else UAB_ASSERT(true, "Couldn't open the file\n");
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

		data_file << "worker count: " + std::to_string(worker_count) + " time: " + std::to_string(frame) + " \n";

		int dead_worker_count = player->deadUnitCount(BWAPI::UnitTypes::Terran_SCV);
		int workers_minerals_spent = 50 * (worker_count - 4 + dead_worker_count);
		data_file << "workers minerals spent: " + std::to_string(workers_minerals_spent) + " time: " + std::to_string(frame) + " \n";

		data_file << "workers on minerals: " + std::to_string(mineral_count) + " time: " + std::to_string(frame) + " \n";

		data_file << "workers on gas: " + std::to_string(gas_count) + " time: " + std::to_string(frame) + " \n";

		//military_minerals_spent = player->spentMinerals() + player->refundedMinerals() - upgrade_minerals_spent - building_minerals_spent;
		data_file << "military minerals spent: " + std::to_string(military_minerals_spent) + " time: " + std::to_string(frame) + " \n";

		//military_gas_spent = player->spentGas() + player->refundedGas() - workers_minerals_spent - upgrade_minerals_spent - building_gas_spent; //should be less than spentGas
		data_file << "military gas spent: " + std::to_string(military_gas_spent) + " time: " + std::to_string(frame) + " \n";

		int supply_used = player->supplyUsed();
		data_file << "military unit supply used: " + std::to_string(supply_used-worker_count) + " time: " + std::to_string(frame) + " \n";

		data_file << "upgrade minerals spent: " + std::to_string(upgrade_minerals_spent) + " time: " + std::to_string(frame) + " \n";
		
		data_file << "upgrade gas spent: " + std::to_string(upgrade_gas_spent) + " time: " + std::to_string(frame) + " \n";
		
		data_file << "building minerals spent: " + std::to_string(building_minerals_spent) + " time: " + std::to_string(frame) + " \n";
		
		minerals_on_hand = player->minerals();
		data_file << "minerals on hand: " + std::to_string(minerals_on_hand) + " time: " + std::to_string(frame) + " \n";
		
		data_file << "gas on hand: " + std::to_string(gas_on_hand) + " time: " + std::to_string(frame) + " \n";
		
		data_file << "supply: " + std::to_string((player->supplyTotal())/2) + " time: " + std::to_string(frame) + " \n\n\n";

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

void AnalysisData::writeScoutData()
{
	
}