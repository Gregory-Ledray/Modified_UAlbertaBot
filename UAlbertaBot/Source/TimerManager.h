#pragma once

#include "Config.h"
#include "Common.h"
#include "../../BOSS/source/Timer.hpp"

namespace UAlbertaBot
{

class TimerManager
{
	std::vector<BOSS::Timer> _timers;
	std::vector<std::string> _timerNames;

	int _barWidth;

public:

	enum Type { All, Worker, Production, Building, Combat, Scout, InformationManager, MapGrid, MapTools, Search, NumTypes, Analyze };

	TimerManager();

	void startTimer(const TimerManager::Type t);

	void stopTimer(const TimerManager::Type t);

	double getTotalElapsed(const TimerManager::Type t);

	void displayTimers(int x, int y);
};

}