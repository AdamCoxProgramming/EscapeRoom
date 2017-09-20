
#include<string>
#include<vector>
#include"Object.cpp"

using namespace std;
class Action;

struct Room {	

	string Name;

	string Description;
	vector<Object> RoomsContents;
	vector<string> Connections; 
	vector<Action> RoomActions;

	Room(string Desc, string name, vector<Object> Objs, vector<string> Connection) :Description(Desc), Name(name),
	RoomsContents(Objs), Connections(Connection)
	{

	}

	Room() {};

	void AddAction(Action In)
	{
		RoomActions.push_back(In);
	}

	void AddObject(Object In)
	{
		RoomsContents.push_back(In);
	}

	vector<Action> GetActions() {

		vector<Action> returnVec;

		for (size_t i = 0; i < RoomsContents.size(); i++)
		{
			for (size_t k = 0; k < RoomsContents[i].GetActions().size(); k++)
			{
				returnVec.push_back(RoomsContents[i].GetActions()[k]);
			}
		}

		for (size_t k = 0; k < RoomActions.size(); k++)
		{
			returnVec.push_back(RoomActions[k]);
		}

		return returnVec;
	}

	void AddConnection(string ConnectionName)
	{
		Connections.push_back(ConnectionName);
	}

};