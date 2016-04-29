#include "Common.h"
#include "ParticleModel.h"
#include "AnalysisData.h"

using namespace UAlbertaBot;

ParticleModel::ParticleModel(BWAPI::Unit unit)
	: weight(1.0)
	, _unit(unit)
	, _enemy(BWAPI::Broodwar->enemy())
{
	BWAPI::Point<int, 1> Position(0, 0);
	BWAPI::UnitType _type = _unit -> getType();
	double trajectory[2] = { 0.0, 0.0 };
	if (!(_type.isBuilding() || _type.isAddon()))
	{
		movementspeed = _type.topSpeed();
	}
	else
	{
		movementspeed = 0;//building have some movementspeed cause terran :/
		//the plus side of this is these building particles never decay!
	}
	
	weightdecay = .005*movementspeed;//SCVs speed 5 so last 1/.025=40 frames
	
	if (_unit->isCarryingGas())
	{
		collecting_gas = true;
		collecting_minerals = false;
	}
	else if (_unit->isCarryingMinerals())
	{
		collecting_minerals = true;
		collecting_gas = false;
	}
	else
	{
		collecting_gas = false;
		collecting_minerals = true;
	}

	int xpos = _unit->getPosition().x;
	int ypos = _unit->getPosition().y;

	//update trajectory - 
	trajectory[0] = _unit->getVelocityX();
	trajectory[1] = _unit->getVelocityY();
	//normalize vectors to unit vectors
	double to_divide = trajectory[0] + trajectory[1];
	double normalized_trajectory[2] = { trajectory[0] / to_divide, trajectory[1] / to_divide };
	//multiply vectors by class-specific weights
	double weighted_normalized_trajectory[2] = { normalized_trajectory[0] * movementspeed, normalized_trajectory[1] * movementspeed };
	//sum resulting vectors - n/a b/c not taking terrain into account for simplicity
	trajectory[0] = weighted_normalized_trajectory[0];
	trajectory[1] = weighted_normalized_trajectory[1];
}

void ParticleModel::particleUpdate()//this updates a single particle of type ParticleModel
{
	//update weight - could find this over many generations if i wanted to
	weight -= weightdecay;

	//update estimated position
	xpos += trajectory[0];
	ypos += trajectory[1];

	//remove particles with less than 0 weight by not adding them to the 'new' list
	if (weight >= 0)
	{
		new_enemy_list.push_back(_unit);
		AnalysisData::new_particle_model_list.push_back(*this);
	}

	//update gas/mineral status
	if (_unit->isCarryingGas())
	{
		collecting_gas = true;
		collecting_minerals = false;
	}
	else if (_unit->isCarryingMinerals())
	{
		collecting_minerals = true;
		collecting_gas = false;
	}
}

//checks if observable units could have been a particle of the past
bool ParticleModel::previousParticleCheck()
{
	//iterate through all of the previous enemy list
	for (std::vector<BWAPI::Unit>::iterator i = previous_enemy_list.begin(); i != previous_enemy_list.end(); i++)
	{
		BWAPI::Unit j = *i;
		//if the unit is where a particle is predicted to be
		if (_unit->exists() && _unit->getPlayer() == _enemy &&
			(j->getPosition().x + (trajectory[0]/weight*.9)) < (_unit->getPosition().x) < (j->getPosition().x + (trajectory[0]/weight*1.1))
			&& (j->getPosition().y - (trajectory[1]/weight*.9)) < (_unit->getPosition().y) < (j->getPosition().y + (trajectory[1]/weight*1.1)))
		{
			new_enemy_list.push_back(j);//add this to the list of known units!
			previous_enemy_list.erase(i);//remove the unit from the previous enemy list for reasons
			for (std::vector<ParticleModel>::iterator k = AnalysisData::previous_particle_model_list.begin(); k != AnalysisData::previous_particle_model_list.end(); k++)
			{
				ParticleModel l = *k;
				if (l.xpos==xpos && l.ypos==ypos) {//in this case the particle being examined is this particle
					AnalysisData::previous_particle_model_list.erase(k);
					break;
				}
			}
			
			return true;
		}


	}
	return false;
}

std::vector<BWAPI::Unit> ParticleModel::previous_enemy_list;
std::vector<BWAPI::Unit> ParticleModel::new_enemy_list;