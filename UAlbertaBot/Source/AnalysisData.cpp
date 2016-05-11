#include "Common.h"
#include "AnalysisData.h"
#include "UnitUtil.h"
#include <fstream>
#include <iostream>
#include <string>
#include "UnitData.h"
#include "WorkerManager.h"
#include "ParticleModel.h"
#include "ProcessTextFiles.h"
#include <stdio.h>
#include "StrategyManager.h"


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
		data_file << "\n";
		data_file.close();
	}
	else UAB_ASSERT(true, "Couldn't open the main file at game termination\n");

	const char *path2 = "C:/Users/Gregory/Desktop/ualbertabot_2/scouting_data_out.txt";
	std::ofstream data_file_2;
	data_file.open(path2, std::ofstream::out | std::ofstream::app);

	if (data_file_2.is_open())
	{
		data_file_2 << "\n";
		data_file_2.close();
	}
	else UAB_ASSERT(true, "Couldn't open the scouting file at game termination\n");

	ProcessTextFiles::Instance().post_game_analysis("C:/Users/Gregory/Desktop/ualbertabot/scouting_data_out.txt");
	ProcessTextFiles::Instance().post_game_analysis("C:/Users/Gregory/Desktop/ualbertabot_2/data_out.txt");
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

void AnalysisData::time(double time_in_millis)
{
	const char *path = "C:/Users/Gregory/Desktop/ualbertabot/time_out.txt";
	std::ofstream data_file;
	data_file.open(path, std::ofstream::out | std::ofstream::app);
	int frame = BWAPI::Broodwar->getFrameCount();
	data_file << time_in_millis << " " << frame << "\n";
	data_file.close();
}

void AnalysisData::writeData()
{
	int test_number = 0;

	const char *path = "C:/Users/Gregory/Desktop/ualbertabot/data_out.txt";
	std::ofstream data_file;
	data_file.open(path, std::ofstream::out | std::ofstream::app);

	int frame = BWAPI::Broodwar->getFrameCount();

	if (data_file.is_open())
	{
		BWAPI::PlayerInterface * player = BWAPI::Broodwar->self();

		int gas_on_hand = player->gas();

		data_file << std::to_string(worker_count)+ " " + std::to_string(frame) + "\n";

		int dead_worker_count = player->deadUnitCount(BWAPI::UnitTypes::Terran_SCV);
		int workers_minerals_spent = 50 * (worker_count - 4 + dead_worker_count);
		data_file << std::to_string(workers_minerals_spent) + " " + std::to_string(frame) + "\n";

		data_file << std::to_string(mineral_count) + " " + std::to_string(frame) + "\n";

		data_file << std::to_string(gas_count) + " " + std::to_string(frame) + "\n";

		//military_minerals_spent = player->spentMinerals() + player->refundedMinerals() - upgrade_minerals_spent - building_minerals_spent;
		data_file << std::to_string(military_minerals_spent) + " " + std::to_string(frame) + "\n";

		//military_gas_spent = player->spentGas() + player->refundedGas() - workers_minerals_spent - upgrade_minerals_spent - building_gas_spent; //should be less than spentGas
		data_file << std::to_string(military_gas_spent) + " " + std::to_string(frame) + "\n";

		int supply_used = player->supplyUsed();
		data_file << std::to_string(supply_used-worker_count) + " " + std::to_string(frame) + "\n";

		data_file << std::to_string(upgrade_minerals_spent) + " " + std::to_string(frame) + "\n";
		
		data_file << std::to_string(upgrade_gas_spent) + " " + std::to_string(frame) + "\n";
		
		data_file << std::to_string(building_minerals_spent) + " " + std::to_string(frame) + "\n";
		
		minerals_on_hand = player->minerals();
		data_file << std::to_string(minerals_on_hand) + " " + std::to_string(frame) + "\n";
		
		data_file << std::to_string(gas_on_hand) + " " + std::to_string(frame) + "\n";
		
		data_file << std::to_string((player->supplyTotal())/2) + " " + std::to_string(frame) + "\n";

		data_file <<  std::to_string((player->supplyUsed()) / 2) + " " + std::to_string(frame) + "\n";

		data_file.close();

		StrategyManager::Instance().terran_heuristic = military_minerals_spent + military_gas_spent + upgrade_minerals_spent +
			upgrade_gas_spent + building_minerals_spent + building_gas_spent + gas_count + mineral_count;
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
	int enemy_workers_on_gas(0);//purely local variable
	int enemy_workers_on_minerals(0);//purely local variable
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

	//clear out the old new particle list
	new_particle_model_list.clear();

	int a = 0;
	for (BWAPI::UnitInterface* unit : BWAPI::Broodwar->enemy()->getUnits())
	{
		if (unit->isVisible())
		{
			//create a new particle model for this observed unit
			ParticleModel model = ParticleModel::ParticleModel(unit);

			//check if observable units could have been a particle of the past
			//if so, need to delete it from the old particle list
			//this is all handled in previousParticleCheck
			bool duplicate = model.previousParticleCheck();//true for a duplicate

			//it's definitely being observed so it must be added to the particle list
			new_particle_model_list.push_back(model);

			a++;
		}
	}
	//data_file << "oberved particle count: " << a;
	a = 0;

	//if there are any particles not observed, they still need to be updated
	//and culled by this function
	for (std::vector<ParticleModel>::iterator i = previous_particle_model_list.begin(); i != previous_particle_model_list.end(); ++i)
	{
		i->particleUpdate();
		a++;
	}
	//data_file << " non-observed particle count: " << a;
	a = 0;

	previous_particle_model_list.clear();
	previous_particle_model_list = new_particle_model_list;

	int c(0);
	int b(0);

	for (std::vector<ParticleModel>::iterator i = previous_particle_model_list.begin(); i != previous_particle_model_list.end(); ++i)
	{
		BWAPI::UnitType zulu = i->_type;
		if (i->worker())
		{
			enemy_worker_count++;
			enemy_supply_used += i->_type.supplyRequired();

			if (i->collecting_gas)
			{
				enemy_workers_on_gas++;
			}
			else if (i->collecting_minerals)
			{
				enemy_workers_on_minerals++;
			}				

			a++;
		}
		else if (i->building())
		{
			enemy_building_minerals_spent += i->_type.mineralPrice();
			enemy_supply_total += i->_type.supplyProvided();
			enemy_upgrade_gas_spent += i->_type.armorUpgrade().gasPrice() + i->_type.airWeapon().upgradeType().gasPrice() + i->_type.groundWeapon().upgradeType().gasPrice();
			enemy_upgrade_minerals_spent += i->_type.armorUpgrade().mineralPrice() + i->_type.airWeapon().upgradeType().mineralPrice() + i->_type.groundWeapon().upgradeType().mineralPrice();
			if (i->_type == BWAPI::UnitTypes::Terran_Command_Center)//account for free Command Center
				enemy_building_minerals_spent -= 400;

			b++;
		}
		else if (!(i->milunit()))
		{
			//must be military units
			enemy_military_minerals_spent += i->_type.mineralPrice();
			enemy_military_gas_spent += i->_type.gasPrice();
			enemy_supply_used += i->_type.supplyRequired();
			enemy_upgrade_gas_spent += i->_type.armorUpgrade().gasPrice() + i->_type.airWeapon().upgradeType().gasPrice() + i->_type.groundWeapon().upgradeType().gasPrice();
			enemy_upgrade_minerals_spent += i->_type.armorUpgrade().mineralPrice() + i->_type.airWeapon().upgradeType().mineralPrice() + i->_type.groundWeapon().upgradeType().mineralPrice();
		}
		else if (i->_type == NULL){
			data_file << "type is null\n";
		}

		c++;
	}

	//for all of these: need a flag to make sure they're only activated if no
	//enemy units have been killed/destroyed in the last 10 frames of the game.
	//if that is the case, then the new value could very well be smaller than the old
	if (previous_enemy_worker_count > enemy_worker_count)
	{
		enemy_worker_count = previous_enemy_worker_count;
	}
	/*
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
		*/
	bool dont_output = false;

	
	//if there's nothing to report... report nothing
	if (enemy_worker_count + enemy_gas_count + enemy_mineral_count + enemy_military_minerals_spent
		+ enemy_military_minerals_spent + enemy_military_gas_spent + enemy_supply_used + enemy_upgrade_minerals_spent
		+ enemy_upgrade_gas_spent + enemy_building_minerals_spent + enemy_minerals_on_hand + enemy_gas_on_hand
		+ enemy_supply_total == 0)
	{
		dont_output = true;
	}

	if (data_file.is_open() && !dont_output)
	{
		BWAPI::PlayerInterface * player = BWAPI::Broodwar->enemy();

		data_file << std::to_string(enemy_worker_count) + " " << frame << "\n";

		int dead_worker_count = player->deadUnitCount(BWAPI::UnitTypes::Terran_SCV);
		int enemy_workers_minerals_spent = 50 * (enemy_worker_count - 4 + dead_worker_count);
		data_file << std::to_string(enemy_workers_minerals_spent) + " " << frame << "\n";

		data_file << std::to_string(enemy_workers_on_minerals) + " " << frame << "\n";

		data_file << std::to_string(enemy_workers_on_gas) + " " << frame << "\n";

		//military_minerals_spent = player->spentMinerals() + player->refundedMinerals() - upgrade_minerals_spent - building_minerals_spent;
		data_file << std::to_string(enemy_military_minerals_spent) + " " << frame << "\n";

		//military_gas_spent = player->spentGas() + player->refundedGas() - workers_minerals_spent - upgrade_minerals_spent - building_gas_spent; //should be less than spentGas
		data_file << std::to_string(enemy_military_gas_spent) + " " << frame << "\n";

		data_file << std::to_string(enemy_supply_used - enemy_worker_count) + " " << frame << "\n";

		data_file << std::to_string(enemy_upgrade_minerals_spent) + " " << frame << "\n";

		data_file << std::to_string(enemy_upgrade_gas_spent) + " " << frame << "\n";

		data_file << std::to_string(enemy_building_minerals_spent) + " " << frame << "\n";

		data_file << std::to_string(enemy_minerals_on_hand) + " " << frame << "\n";

		data_file << std::to_string(enemy_gas_on_hand) + " " << frame << "\n";

		data_file << std::to_string(enemy_supply_total / 2) + " " << frame << "\n";

		data_file << std::to_string(enemy_supply_used) + " " << frame << "\n";

		data_file.close();
	}

	StrategyManager::Instance().enemy_heuristic = enemy_worker_count + enemy_gas_count + enemy_mineral_count + enemy_military_minerals_spent +
		enemy_military_gas_spent + enemy_supply_used + enemy_upgrade_minerals_spent + enemy_upgrade_gas_spent +
		enemy_building_minerals_spent + enemy_minerals_on_hand + enemy_gas_on_hand + enemy_supply_total;


	previous_enemy_worker_count = enemy_worker_count;//
	previous_enemy_workers_on_gas = enemy_workers_on_gas;//
	previous_enemy_workers_on_minerals = enemy_workers_on_minerals;//
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
int AnalysisData::previous_enemy_workers_on_gas = 0;//
int AnalysisData::previous_enemy_workers_on_minerals = 0;//
int AnalysisData::previous_enemy_military_minerals_spent = 0;//
int AnalysisData::previous_enemy_military_gas_spent = 0;//
int AnalysisData::previous_enemy_supply_used = 0;//
int AnalysisData::previous_enemy_upgrade_minerals_spent = 0;//
int AnalysisData::previous_enemy_upgrade_gas_spent = 0;//
int AnalysisData::previous_enemy_building_minerals_spent = 0;//
int AnalysisData::previous_enemy_minerals_on_hand = 0;
int AnalysisData::previous_enemy_gas_on_hand = 0;
int AnalysisData::previous_enemy_supply_total = 0;//

std::vector<ParticleModel> AnalysisData::previous_particle_model_list;
std::vector<ParticleModel> AnalysisData::new_particle_model_list;