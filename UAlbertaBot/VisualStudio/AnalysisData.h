#pragma once

#include "Common.h"
#include "UnitUtil.h"

namespace UAlbertaBot
{

	class AnalysisData
	{
		BWAPI::Race					    _selfRace;
		BWAPI::Race					    _enemyRace;
    		int worker_count;
    		double military_minerals_spent;
    		double military_gas_spent;
    		double upgrade_minerals_spent;
    		double upgrade_gas_spent;
    		double building_minerals_spent;
    		double building_gas_spent;
    		double minerals_on_hand;
    		double gas_on_hand;
    
    		double supply;
    		
    		std::vector<BWAPI::Unit> Unit_List;
    		std::vector<BWAPI::Unit> Building_List;
    		std::vector<BWAPI::Unit> Unit_List;
    
	public:
		void Update();
		void WriteData();
		bool AlreadyNoted(BWAPI::Unit);
	};

}
