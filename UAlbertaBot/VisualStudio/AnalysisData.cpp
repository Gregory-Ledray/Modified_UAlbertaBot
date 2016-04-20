#include "Common.h"
#include "AnalysisData.h"
#include "UnitUtil.h"

using namespace UAlbertaBot;

AnalysisData::AnalysisData()
	: _selfRace(BWAPI::Broodwar->self()->getRace())
	, _enemyRace(BWAPI::Broodwar->enemy()->getRace())
	, worker_count(5)
	, military_minerals_spent(0)
	, military_gas_spent(0)
	, upgrade_minerals_spent(0)
	, upgrade_gas_spent(0)
	, building_minerals_spent(0)
	, building_gas_spent(0)
	, minerals_on_hand(50)
	, gas_on_hand(0)
	, oberved_enemy_supply(0)
{
}

void AnalysisData::Update()
{
  //the goal here is to update this player's current figures.
  
  //updating unit counts
  worker_count = 0;
  for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++)
  {
  //http://pages.cs.wisc.edu/~starr/bwapi-read-only/html/classBWAPI_1_1Unit.html#adffa706cce7eb05c50573642cc80a5e2
  //http://pages.cs.wisc.edu/~starr/bwapi-read-only/html/classBWAPI_1_1Unit.html
    for (int j = 0; j < Unit_List.length(); j++)
    {
      
    }
  }
  
  bool AnalysisData::AlreadyNoted(BWAPI::Unit toCheck)
  {
    if ( (*i)->getType().isWorker() == true)
    {
      for (int j = 0; j < Unit_List.length(); j++)
      {
        if (BWAPI::i::getID == toCheck)
        //means this unit has already been noted so I need to skip it
        {
          return true;
        }
      }
      return false;
    }
    if ( (*i)->getType().isBuilding() == true)//pretty sure this line is wrong but I'll get to fixing it later
    {
    
    }
  }
}
