#pragma once

#include "Common.h"
#include "BWTA.h"
#include "BuildOrderQueue.h"
#include "InformationManager.h"
#include "WorkerManager.h"
#include "BuildOrder.h"
#include <string>

namespace UAlbertaBot
{
typedef std::pair<MetaType, size_t> MetaPair;
typedef std::vector<MetaPair> MetaPairVector;

struct Strategy
{
    std::string _name;
    BWAPI::Race _race;
    int         _wins;
    int         _losses;
    BuildOrder  _buildOrder;

    Strategy()
        : _name("None")
        , _race(BWAPI::Races::None)
        , _wins(0)
        , _losses(0)
    {
    
    }

    Strategy(const std::string & name, const BWAPI::Race & race, const BuildOrder & buildOrder)
        : _name(name)
        , _race(race)
        , _wins(0)
        , _losses(0)
        , _buildOrder(buildOrder)
    {
    
    }
};

class StrategyManager 
{
	StrategyManager();

	BWAPI::Race					    _selfRace;
	BWAPI::Race					    _enemyRace;
    std::map<std::string, Strategy> _strategies;
    int                             _totalGamesPlayed;
    const BuildOrder                _emptyBuildOrder;

	        void	                writeResults();
	const	int					    getScore(BWAPI::Player player) const;
	const	double				    getUCBValue(const size_t & strategy) const;
	const	bool				    shouldExpandNow() const;
    const	MetaPairVector		    getProtossBuildOrderGoal() const;
	const	MetaPairVector		    getTerranBuildOrderGoal();
	const	MetaPairVector		    getZergBuildOrderGoal() const;

public:
    
	static	StrategyManager &	    Instance();
	//my code starts
			void					update();

	static	int						enemy_heuristic;
	static	int						terran_heuristic;
			int						terran_military_count;
			int						terran_military_array[8];
			int						best_organism[8];
	static	int						previous_frame;
	static	bool					first_pass;
	//my code ends
			void				    onEnd(const bool isWinner);
            void                    addStrategy(const std::string & name, Strategy & strategy);
            void                    setLearnedStrategy();
            void	                readResults();
	const	bool				    regroup(int numInRadius);
	const	bool				    rushDetected();
	const	int				        defendWithWorkers();
	const	MetaPairVector		    getBuildOrderGoal();
	const	BuildOrder &            getOpeningBookBuildOrder() const;
};
}