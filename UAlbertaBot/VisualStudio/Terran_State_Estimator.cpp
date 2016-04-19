#include "Common.h"
#include "PotentialEnemy.h"
#include "UnitUtil.h"

using namespace UAlbertaBot;

Terran_State_Estimator::Terran_State_Estimator()
	: _selfRace(BWAPI::Broodwar->self()->getRace())
	, _enemyRace(BWAPI::Broodwar->enemy()->getRace())
{
  try
  {
    if (_enemyRace != BWAPI::Races::Terran)
      throw 1;
  }
  catch(int a)
  {
    if (a==1)
      cout << "Enemy Race is not Terran";
    else
      cout << "Our race is not terran
  }
}

bool enemyWorkerCalculation()
{
  int enemy_expansions = 0;
  
  int frame = BWAPI::Broodwar->getFrameCount();
	int seconds = frame / 24;
	int minutes = seconds / 60;
	
	int estimated_enemy_worker_count = 5 + (seconds / 20) + enemy_expansions * (seconds / 20); //if they don't rush and none have been killed this should be a good figure
	
	//figuring out the worker count requires two things:
	//1. seeing the workers and noting where they are
	//2a. travelling to the enemy's main base and watching how many workers swing by to drop off resources over a period of time
	//2b. OR finding enemy worker's paths to the main base and excluding workers travelling along already noted paths
	//2c. Going to the mineral patch and noting the number of enemy workers over a period of time; doing the same at the gas geyser
	worker_count = estimated_enemy_worker_count;//totally wrong line of code
	
  return false;//returning false means the calculation could not be completed
}

bool enemyMilitaryCalculation()
{
  //oberve enemy military units and note the resource cost of those units as a baseline.
  //remember that killed units should reduce this number
  //military_resource_estimation_error is based on actual gathered data; use stats to compare estimated enemy military and this error.
  //should also change opponent's strategy occasionally to make sure this bot doesn't just get good at playing itself
  return false;//returning false means the calculation could not be completed
}

bool enemyBuildingCalcuation()
{
  //observed_building_resources is the sum of resources necessary to construct observed buildings
  //estimated_enemy_buildg_resources is based on an estimation of enemy supply, and how fast they're producing units, and 
  //what type of units are being produces, and whether there is more than one command center
  return false;//returning false means the calculation could not be completed
}

bool enemyUpgradeResourcesCalcuation()
{
  //look through enemy units and check for upgrades. This counts as observed_upgrade_resources
  //estimated_upgrade_resources == observed_upgrade resources unless there is a pattern
  return false;//returning false means the calculation could not be completed
}

bool enemyResourceCalcuation()
{
  int frame = BWAPI::Broodwar->getFrameCount();
	int seconds = frame / 24;
	int minutes = seconds / 60;
	
	//this will have to be dynamic in that as worker count increases, the rate of income increases.
	
  return false;//returning false means the calculation could not be completed
}

bool enemySupplyCalcuation()
{
  //look through known enemy buildings and count the number of supply depots (+8) and Command Centers (+10 supply)
  //only consider this to be an exhaustive list if the entire area has been scounted AND expansions have been checked for
  return false;//returning false means the calculation could not be completed
}
