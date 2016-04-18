#pragma once

#include "Common.h"
#include "BWTA.h"

namespace UAlbertaBot
{
	int worker_count;
	double worker_error;
	double military_resource_estimation;
	double military_resource_estimation_error;
	WA
	double PotentialEnemyData[18];//contains doubles indicating different potential enemy values.
	//values are in pairs: [0] is a lower bound; [1] is an upper bound
	//data stored: 0/1 contain potential maximum resource totals gathered over lifetime
	//2/3 contain resources spent on workers
	//4/5 contain resources spent on military
	//6/7 contain resources spent on buildings
	//8/9 contains resources spent on upgrades
	//10/11 contains a more reasonable guess about enemy's current resource totals based on scouting
	//12/13 contains a guess of enemy resources on hand (not spent yet) based on 10/11 totals
	//14/15 contains estimated gas on hand
	//16/17 contains potential supply

	class PotentialEnemy
	{
		BWAPI::Race					    _selfRace;
		BWAPI::Race					    _enemyRace;

	public:
		PotentialEnemy();
		double							*calculatePotentialEnemy();
		double							*protossPotentialEnemy();
		double							*terranPotentialEnemy();
		double							*zergPotentialEnemy();
	};

}