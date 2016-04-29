#pragma once

#include "Common.h"

namespace UAlbertaBot
{
	class ParticleModel
	{
	private:
		double* trajectory;
		double weight;
		double movementspeed;//measured in pixels per frame;
		//movement speed also represents the unit's class
		
		double weightdecay;
		BWAPI::Unit _unit;
		BWAPI::Player _enemy;

		int xpos;
		int ypos;
		BWAPI::Point<int, 1> position;

	public:
		BWAPI::UnitType _type;

		bool collecting_gas;
		bool collecting_minerals;

		ParticleModel(BWAPI::Unit _unit);

		static std::vector<BWAPI::Unit> previous_enemy_list;
		static std::vector<BWAPI::Unit> new_enemy_list;

		bool previousParticleCheck();
		void particleUpdate();
	};

}