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
			//if there was a nulltype error
			if (input[0] == 't')
			{
				//go to the next line and proceed as normal
				scouting_data.getline(input, 20);
			}

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
			ProcessTextFiles::takeInNextLine();
			enemy_workers_on_minerals_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_worker_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_workers_on_minerals_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_workers_on_gas_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			military_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			military_gas_spent_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_military_supply_used_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_upgrade_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_upgrade_gas_spent_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_building_minerals_spent_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_minerals_on_hand_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_gas_on_hand_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_supply_total_2d[frame / 10][estimated_game_number] = temp;
			ProcessTextFiles::takeInNextLine();
			enemy_supply_used_2d[frame / 10][estimated_game_number] = temp;
		}

		//all data has now been pulled from the text file and put into those 
		//2d arrays or vectors depending on what was commented out
	}
	scouting_data.close();

	//At this point I need to go through every frame and look at every stored data value
	//and condense it into one function or something

}

int ProcessTextFiles::last_frame = 0;

void ProcessTextFiles::takeInNextLine()
{
	char input[20];
	//if there was a nulltype error
	if (input[0] == 't')
	{
		//go to the next line and proceed as normal
		scouting_data.getline(input, 20);
	}

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
	temp = atoi(out);

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
}