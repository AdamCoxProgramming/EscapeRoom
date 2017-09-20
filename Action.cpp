
#include<string>
#include<vector>
#include<functional>

using namespace std;

class Player;
class Object;

struct Action  {

	Action()
	{

	}

	// One Part
	Action(vector<string> keyWords , bool InventoryOnly , std::function<void(Player*)> In , string DescriptionIn) : KeyWords(keyWords),
		ActionFunction(In), OnePart(true), TwoPart(false), ThreePart(false) , InventoryAction(InventoryOnly) , Description(DescriptionIn)
	{
		
	}

	// Two Part
	Action(vector<string> keyWords, bool InventoryOnly, string Target, std::function<void(Player*)> In, string DescriptionIn) : KeyWords(keyWords),
		ActionFunction(In), Tool(Target), OnePart(false), TwoPart(true), ThreePart(false) , InventoryAction(InventoryOnly) , Description(DescriptionIn)
	{

	}

	// Three Part
	Action(vector<string> keyWords, bool InventoryOnly, string tool, std::function<void( Player*, Object* ObjectIn )> In, string DescriptionIn) : KeyWords(keyWords),
		ActionFunctionTool(In), Tool(tool), TwoPart(false), ThreePart(true) , InventoryAction(InventoryOnly), Description(DescriptionIn)
	{
	}

	vector<string> KeyWords;

	bool OnePart , TwoPart , ThreePart ;

	string Tool;

	string ObjectUsingName;

	bool InventoryAction;

	string Description;

	std::function<void(Player*)> ActionFunction;

	std::function<void(Player*, Object* ObjectIn)> ActionFunctionTool;



};