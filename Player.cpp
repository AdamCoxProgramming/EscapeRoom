
#include"Monster.cpp"
#include<string>
#include<vector>

struct Player 
{

	string CurrentRoom;
	vector<Object> Inventory;	
	vector<Action> Actions;

	vector<Action> GetActions()
	{
		vector<Action> Temp;

		for (size_t i = 0; i < World::GetInstance().Rooms[CurrentRoom].GetActions().size(); i++)
		{
			if (World::GetInstance().Rooms[CurrentRoom].GetActions()[i].InventoryAction == false)
			{
				Temp.push_back(World::GetInstance().Rooms[CurrentRoom].GetActions()[i]);
			}			
		}

		for (size_t i = 0; i < World::GetInstance().Rooms[CurrentRoom].Connections.size(); i++)
		{
			string RoomConnectionName = World::GetInstance().Rooms[CurrentRoom].Connections[i];
			int number = World::GetInstance().Rooms[RoomConnectionName].GetActions().size();
			for (size_t J = 0; J < World::GetInstance().Rooms[RoomConnectionName].GetActions().size(); J++)
			{
				if (World::GetInstance().Rooms[RoomConnectionName].GetActions()[J].KeyWords[0] == "Enter")
				{
					Temp.push_back(World::GetInstance().Rooms[RoomConnectionName].GetActions()[J]);
				}
				
			}
			
		}

		for (size_t i = 0; i < Inventory.size(); i++)
		{
			for (size_t k = 0; k < Inventory[i].GetActions().size(); k++)
			{
				//if ( Inventory[i].GetActions()[k].InventoryAction == true )
				//{
				
						Temp.push_back(Inventory[i].GetActions()[k]);
					
				//}
			}
		}

		for (size_t i = 0; i < Actions.size(); i++)
		{
			Temp.push_back(Actions[i]);
		}
				
		return Temp;
	}

	vector<Object*> GetAvaibleObjects()
	{
		vector<Object*> Temp;

		for (size_t i = 0; i < World::GetInstance().Rooms[CurrentRoom].RoomsContents.size(); i++)
		{

			Temp.push_back( &World::GetInstance().Rooms[CurrentRoom].RoomsContents[i] );

		}

		for (size_t i = 0; i < Inventory.size(); i++)
		{
			Temp.push_back(&Inventory[i]);
		}

		return Temp;
	}

	void GetCommands()
	{

	}
	
	void AddAction(Action In)
	{
		Actions.push_back(In);
	}
	
	Room GetCurrentRoom()
	{
		return World::GetInstance().Rooms[CurrentRoom];
	}



};