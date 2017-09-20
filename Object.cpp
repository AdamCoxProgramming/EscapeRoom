
#include<vector>

#include"Action.cpp"

using namespace std;

struct Object {

	Object(string name, string description) : Name(name), Description(description)
	{

	}

	Object(string name, string description, Action ActionIn) : Name(name), Description(description)
	{
		ObjectActions.push_back(ActionIn);
	}

	int GetNumberOfActions() {
		return ObjectActions.size();
	}

	vector<Action>GetActions() {
	return ObjectActions;
	}

	void  AddAction(Action ActionIn) {
		ObjectActions.push_back(ActionIn);
	}

	string GetDescription()
	{
		return Description;
	}

	string GetName()
	{
		return Name;
	}

	string Name;

	string Description;

	void RemoveAction( string Description )
	{

		for (size_t i = 0; i < ObjectActions.size(); i++)
		{
			if (ObjectActions[i].Description == Description)
			{
				ObjectActions.erase(ObjectActions.begin() + i);
			}
			
		}
	}

private :
	vector<Action> ObjectActions;



};