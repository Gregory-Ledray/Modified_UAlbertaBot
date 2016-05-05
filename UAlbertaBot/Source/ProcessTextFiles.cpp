#include "Common.h"
#include "ProcessTextFiles.h"

using namespace UAlbertaBot;
ProcessTextFiles & ProcessTextFiles::Instance()
{
	static ProcessTextFiles instance;
	return instance;
}

void ProcessTextFiles::post_game_analysis(char *path)
{
	estimated_game_number = 0;

	//const char *path = path;
	scouting_data.open(path, std::ifstream::in);
	if (scouting_data.is_open())
	{
		scouting_data.seekg(0, scouting_data.beg);//start at the beginning
		char input[20];
		char out[10];
		while (scouting_data.getline(input, 20))//while the thing isn't over
		{
			//worker count
			int x = 0;
			for (int i = 0; i < 20; i++)
			{
				if (!std::isspace(input[i]))
				{
					out[x] = input[i];
					x++;
				}
				else
					break;
			}
			int temp = atoi(out);
							int y = 0;
			for (int i = x; i < 20; i++)
			{
				if (!std::isspace(input[i]) && input[i] != '\n')
				{
					out[y] = input[i];
					y++;
				}
				else
					break;
			}
			frame = atoi(out);

			//check if it's a new game!
			if (last_frame > frame)
				estimated_game_number++;
			last_frame = frame;

			//if over the frame limit, stop taking in data
			if (frame / 10 > 3999 || frame / 10 < 0)
				return;

			worker_count_2d[frame / 10][estimated_game_number] = temp;
							
			//workers minerals spent
			ProcessTextFiles::workerMineralsSpent();
			ProcessTextFiles::workersOnMinerals();
			ProcessTextFiles::workersOnGas();
			ProcessTextFiles::militaryMineralsSpent();
			ProcessTextFiles::militaryGasSpent();
			ProcessTextFiles::militaryUnitSupplyUsed();
			ProcessTextFiles::upgradeMineralsSpent();
			ProcessTextFiles::upgradeGasSpent();
			ProcessTextFiles::buildingMineralsSpent();
			ProcessTextFiles::mineralsOnHand();
			ProcessTextFiles::gasOnHand();
			ProcessTextFiles::supplyTotal();
			ProcessTextFiles::supplyUsed();
		}

		//all data has now been pulled from the text file and put into those 
		//2d arrays or vectors depending on what was commented out
	}
	scouting_data.close();

	//At this point I need to go through every frame and look at every stored data value
	//and condense it into one function or something

}

void ProcessTextFiles::workerMineralsSpent()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_workers_on_minerals_aa.push_back(std::make_pair(temp, frame));

	enemy_workers_on_minerals_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::workersOnMinerals()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_workers_on_minerals_aa.push_back(std::make_pair(temp, frame));
	enemy_workers_on_minerals_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::workersOnGas()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_workers_on_gas_aa.push_back(std::make_pair(temp, frame));
	enemy_workers_on_gas_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::militaryMineralsSpent()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//military_minerals_spent_aa.push_back(std::make_pair(temp, frame));
	military_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::militaryGasSpent()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//military_gas_spent_aa.push_back(std::make_pair(temp, frame));
	military_gas_spent_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::militaryUnitSupplyUsed()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_military_supply_used_aa.push_back(std::make_pair(temp, frame));
	enemy_military_supply_used_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::upgradeMineralsSpent()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_upgrade_minerals_spent_aa.push_back(std::make_pair(temp, frame));
	enemy_upgrade_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::upgradeGasSpent()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_upgrade_gas_spent_aa.push_back(std::make_pair(temp, frame));
	enemy_upgrade_gas_spent_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::buildingMineralsSpent()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_building_minerals_spent_aa.push_back(std::make_pair(temp, frame));
	enemy_building_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::mineralsOnHand()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_minerals_on_hand_aa.push_back(std::make_pair(temp, frame));
	enemy_minerals_on_hand_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::gasOnHand()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_gas_on_hand_aa.push_back(std::make_pair(temp, frame));
	enemy_gas_on_hand_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::supplyUsed()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_supply_used_aa.push_back(std::make_pair(temp, frame));
	enemy_supply_used_2d[frame / 10][estimated_game_number] = temp;
}

void ProcessTextFiles::supplyTotal()
{
	char input[20];
	char out[10];
	scouting_data.getline(input, 20);
	int x = 0;
	for (int i = 0; i < 20; i++)
	{
		if (!std::isspace(input[i]))
		{
			out[x] = input[i];
			x++;
		}
		else
			break;
	}
	int temp = atoi(out);

	int y = 0;
	for (int i = x; i < 20; i++)
	{
		if (!std::isspace(input[i]) && input[i] != '\n')
		{
			out[y] = input[i];
			y++;
		}
		else
			break;
	}
	frame = atoi(out);

	//enemy_supply_total_aa.push_back(std::make_pair(temp, frame));
	enemy_supply_total_2d[frame / 10][estimated_game_number] = temp;
}

int ProcessTextFiles::last_frame = 0;