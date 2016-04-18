#include "Common.h"
#include "PotentialEnemy.h"
#include "UnitUtil.h"

using namespace UAlbertaBot;

PotentialEnemy::PotentialEnemy()
	: _selfRace(BWAPI::Broodwar->self()->getRace())
	, _enemyRace(BWAPI::Broodwar->enemy()->getRace())
{
	
}

//typedef std::vector<double> PotentialEnemyData;//contains doubles indicating different potential enemy values.
//values are in pairs: [0] is a lower bound; [1] is an upper bound
//data stored: 0/1 contain potential mineral resources gathered over lifetime
//2/3 contains a guess of enemy gas gathered over the lifetime of the game
//4/5 contain resources spent on workers
//6/7 contain resources spent on military
//8/9 contain resources spent on buildings
//10/11 contains resources spent on upgrades
//12/13 contains estimated minerals on hand
//14/15 contains estimated gas on hand
//16/17 contains potential supply

double* PotentialEnemy::protossPotentialEnemy()
{
	//this code will be written on the assumption that it is executed every frame.
	int frame = BWAPI::Broodwar->getFrameCount();
	int seconds = frame / 24;
	int minutes = seconds / 60;

	//calculate theoretical min_resources and max_resources for minerals
	//also min_gas and max_gas
	int total_num_workers = 5 + (seconds / 20); //if they don't rush and none have been killed this should be a good figure
	int num_worker_on_gas = (total_num_workers - 4) / 4;
	if (num_worker_on_gas > 6)//correcting for errors...
		num_worker_on_gas = 6;

	//this set of if statements only functions for a single base!
	int num_workers_on_mineral = total_num_workers - num_worker_on_gas;
	double min_resources, max_resources, min_gas, max_gas;
	if (num_workers_on_mineral <= 16)
	{
		min_resources = minutes*num_workers_on_mineral * 39;
		max_resources = minutes*num_workers_on_mineral * 45;
		min_gas = 33 * num_worker_on_gas;
		max_gas = 42 * num_worker_on_gas;
	}
	else if (num_workers_on_mineral <= 24)
	{
		min_resources = minutes * 16 * 39 + (num_workers_on_mineral - 16) * 22;
		max_resources = minutes * 16 * 45 + (num_workers_on_mineral - 16) * 12;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42;
	}
	else if (num_workers_on_mineral <= 32)
	{
		min_resources = minutes * 16 * 39 + 8 * 22 + (num_workers_on_mineral - 24) * 12;
		max_resources = minutes * 16 * 45 + 8 * 12 + (num_workers_on_mineral - 24) * 12;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42;
	}
	else
	{
		//at this point, enemyPlayer must have expanded to be gathering more resources & calc breaks down.
		min_resources = minutes * 16 * 39 + 8 * 22 + 8 * 12 + 0;
		max_resources = minutes * 16 * 45 + 8 * 12 + 8 * 12 + 0;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33 + 0;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42 + 0;
	}
	PotentialEnemyData[0] = min_resources*1.18;
	PotentialEnemyData[1] = max_resources*1.18;
	PotentialEnemyData[2] = min_gas*1.18;
	PotentialEnemyData[3] = max_gas*1.18;//multiplication b/c protoss gather 18% faster
	PotentialEnemyData[4] = total_num_workers * 50;
	PotentialEnemyData[5] = total_num_workers * 50;
	PotentialEnemyData[6] = 0;//plus observed military
	PotentialEnemyData[7] = 0;//plus observed military
	PotentialEnemyData[16] = total_num_workers;
	PotentialEnemyData[17] = total_num_workers + (seconds-60)/5;
	if (PotentialEnemyData[16] - 10 > 0)
		PotentialEnemyData[8] = (PotentialEnemyData[16] - 10)*100;
	PotentialEnemyData[8] = PotentialEnemyData[8];//+cost of all found buildings+increase for military's supply
	PotentialEnemyData[9] = PotentialEnemyData[8];//+cost of all found buildings+increase for military's supply
	PotentialEnemyData[10] = 0;//plus observed upgrades
	PotentialEnemyData[11] = 0;//plus observed upgrades
	PotentialEnemyData[12] = PotentialEnemyData[0] - PotentialEnemyData[4] + PotentialEnemyData[6] + PotentialEnemyData[8] + PotentialEnemyData[10];
	PotentialEnemyData[13] = PotentialEnemyData[1] - PotentialEnemyData[5] + PotentialEnemyData[7] + PotentialEnemyData[9] + PotentialEnemyData[11];
	PotentialEnemyData[14] = PotentialEnemyData[2];
	PotentialEnemyData[15] = PotentialEnemyData[3];
	return PotentialEnemyData;
}

double* PotentialEnemy::terranPotentialEnemy()
{
	/* Mineral gathering calculations:
	from http://www.teamliquid.net/forum/sc2-strategy/140055-scientifically-measuring-mining-speed
	"23.8 frames per second for fastest" but code is written assuming 24 frames/sec in StrategyManager.cpp
	- One SCV on one mineral patch harvests 39-45 minerals per game minute, depending on
	distance.
	- Two SCVs on one mineral patch harvest 78-90 minerals per game minute, depending on
	distance.
	- Three SCVs on one mineral patch harvest ~102 minerals per game minute. This is fully
	saturated and does not depend on distance.
	- One SCV on gas harvests 33-42 gas per game minute, depending on distance.
	- Two SCVs on gas harvest 67-84 gas per game minute, depending on distance.
	- Three SCVs on gas harvest 101-114 gas per game minute, depending on distance. In the
	case of far-diagonal gas placement you will need 4 SCVs for full saturation.
	- Four SCVs on gas harvest ~114 gas per game minute. This is fully saturated and does
	not depend on distance.
	- A fully saturated base with 8 minerals and 2 gas will harvest ~816 minerals and ~228
	gas per game minute.
	
	according to http://www.ign.com/faqs/2004/starcraft-battle-chest-unit-faq-565922
	time to produce an scv is 20; so I guess that's 20 seconds?
	*/

	//this code will be written on the assumption that it is executed every frame.
	int frame = BWAPI::Broodwar->getFrameCount();
	int seconds = frame / 24;
	int minutes = seconds / 60;

	//calculate theoretical min_resources and max_resources for minerals
	//also min_gas and max_gas
	int total_num_workers = 5+ (seconds / 20); //if they don't rush and none have been killed this should be a good figure
	int num_worker_on_gas = (total_num_workers - 4) / 4;
	if ( num_worker_on_gas > 6)//correcting for errors...
		num_worker_on_gas = 6;

	//this set of if statements only functions for a single base!
	int num_workers_on_mineral = total_num_workers - num_worker_on_gas;
	double min_resources, max_resources, min_gas, max_gas;
	if (num_workers_on_mineral <= 16)
	{
		min_resources = minutes*num_workers_on_mineral * 39;
		max_resources = minutes*num_workers_on_mineral * 45;
		min_gas = 33 * num_worker_on_gas;
		max_gas = 42 * num_worker_on_gas;
	}
	else if (num_workers_on_mineral <= 24)
	{
		min_resources = minutes * 16 * 39 + (num_workers_on_mineral - 16) * 22;
		max_resources = minutes * 16 * 45 + (num_workers_on_mineral - 16) * 12;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42;
	}
	else if (num_workers_on_mineral <= 32)
	{
		min_resources = minutes * 16 * 39 + 8 * 22 + (num_workers_on_mineral - 24) * 12;
		max_resources = minutes * 16 * 45 + 8 * 12 + (num_workers_on_mineral - 24) * 12;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42;
	}
	else
	{
		//at this point, enemyPlayer must have expanded to be gathering more resources & calc breaks down.
		min_resources = minutes * 16 * 39 + 8 * 22 + 8 * 12 + 0;
		max_resources = minutes * 16 * 45 + 8 * 12 + 8 * 12 + 0;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33 + 0;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42 + 0;
	}
	PotentialEnemyData[0] = min_resources;
	PotentialEnemyData[1] = max_resources;
	PotentialEnemyData[2] = min_gas;
	PotentialEnemyData[3] = max_gas;
	PotentialEnemyData[4] = total_num_workers * 50;
	PotentialEnemyData[5] = total_num_workers * 50;
	PotentialEnemyData[6] = 0;//plus observed military
	PotentialEnemyData[7] = 0;//plus observed military
	PotentialEnemyData[16] = total_num_workers;
	PotentialEnemyData[17] = total_num_workers + (seconds - 60) / 5;
	if (PotentialEnemyData[16] - 10 > 0)
		PotentialEnemyData[8] = (PotentialEnemyData[16] - 10) * 100;
	PotentialEnemyData[8] = PotentialEnemyData[8];//+cost of all found buildings+increase for military's supply
	PotentialEnemyData[9] = PotentialEnemyData[8];//+cost of all found buildings+increase for military's supply
	PotentialEnemyData[10] = 0;//plus observed upgrades
	PotentialEnemyData[11] = 0;//plus observed upgrades
	PotentialEnemyData[12] = PotentialEnemyData[0] - PotentialEnemyData[4] + PotentialEnemyData[6] + PotentialEnemyData[8] + PotentialEnemyData[10];
	PotentialEnemyData[13] = PotentialEnemyData[1] - PotentialEnemyData[5] + PotentialEnemyData[7] + PotentialEnemyData[9] + PotentialEnemyData[11];
	PotentialEnemyData[14] = PotentialEnemyData[2];
	PotentialEnemyData[15] = PotentialEnemyData[3];
	return PotentialEnemyData;
}

double* PotentialEnemy::zergPotentialEnemy()
{
	//this code will be written on the assumption that it is executed every frame.
	int frame = BWAPI::Broodwar->getFrameCount();
	int seconds = frame / 24;
	int minutes = seconds / 60;

	//calculate theoretical min_resources and max_resources for minerals
	//also min_gas and max_gas
	int total_num_workers = 5 + (seconds / 20); //if they don't rush and none have been killed this should be a good figure
	int num_worker_on_gas = (total_num_workers - 4) / 4;
	if (num_worker_on_gas > 6)//correcting for errors...
		num_worker_on_gas = 6;

	//this set of if statements only functions for a single base!
	int num_workers_on_mineral = total_num_workers - num_worker_on_gas;
	double min_resources, max_resources, min_gas, max_gas;
	if (num_workers_on_mineral <= 16)
	{
		min_resources = minutes*num_workers_on_mineral * 39;
		max_resources = minutes*num_workers_on_mineral * 45;
		min_gas = 33 * num_worker_on_gas;
		max_gas = 42 * num_worker_on_gas;
	}
	else if (num_workers_on_mineral <= 24)
	{
		min_resources = minutes * 16 * 39 + (num_workers_on_mineral - 16) * 22;
		max_resources = minutes * 16 * 45 + (num_workers_on_mineral - 16) * 12;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42;
	}
	else if (num_workers_on_mineral <= 32)
	{
		min_resources = minutes * 16 * 39 + 8 * 22 + (num_workers_on_mineral - 24) * 12;
		max_resources = minutes * 16 * 45 + 8 * 12 + (num_workers_on_mineral - 24) * 12;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42;
	}
	else
	{
		//at this point, enemyPlayer must have expanded to be gathering more resources & calc breaks down.
		min_resources = minutes * 16 * 39 + 8 * 22 + 8 * 12 + 0;
		max_resources = minutes * 16 * 45 + 8 * 12 + 8 * 12 + 0;
		min_gas = 102 * 3 + (num_worker_on_gas - 3) * 33 + 0;
		max_gas = 102 * 3 + (num_worker_on_gas - 3) * 42 + 0;
	}
	PotentialEnemyData[0] = min_resources*1.05;
	PotentialEnemyData[1] = max_resources*1.05;
	PotentialEnemyData[2] = min_gas*1.05;
	PotentialEnemyData[3] = max_gas*1.05;
	PotentialEnemyData[4] = total_num_workers * 50;
	PotentialEnemyData[5] = total_num_workers * 50;
	PotentialEnemyData[6] = 0;//plus observed military
	PotentialEnemyData[7] = 0;//plus observed military
	PotentialEnemyData[16] = total_num_workers;
	PotentialEnemyData[17] = total_num_workers + (seconds - 60) / 5;
	if (PotentialEnemyData[16] - 10 > 0)
		PotentialEnemyData[8] = (PotentialEnemyData[16] - 10) * 100;
	PotentialEnemyData[8] = PotentialEnemyData[8];//+cost of all found buildings+increase for military's supply
	PotentialEnemyData[9] = PotentialEnemyData[8];//+cost of all found buildings+increase for military's supply
	PotentialEnemyData[10] = 0;//plus observed upgrades
	PotentialEnemyData[11] = 0;//plus observed upgrades
	PotentialEnemyData[12] = PotentialEnemyData[0] - PotentialEnemyData[4] + PotentialEnemyData[6] + PotentialEnemyData[8] + PotentialEnemyData[10];
	PotentialEnemyData[13] = PotentialEnemyData[1] - PotentialEnemyData[5] + PotentialEnemyData[7] + PotentialEnemyData[9] + PotentialEnemyData[11];
	PotentialEnemyData[14] = PotentialEnemyData[2];
	PotentialEnemyData[15] = PotentialEnemyData[3];
	return PotentialEnemyData;
}

double* PotentialEnemy::calculatePotentialEnemy()
{
	if (_enemyRace == BWAPI::Races::Protoss)
	{
		return protossPotentialEnemy();
	}
	else if (_enemyRace == BWAPI::Races::Terran)
	{
		return terranPotentialEnemy();
	}
	else if (_enemyRace == BWAPI::Races::Zerg)
	{
		return zergPotentialEnemy();
	}
}