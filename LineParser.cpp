#include<string>
#include<vector>
#include"FileReader.cpp"

using namespace std;

string MakeStringLower(string);

struct LineParser {

	static void PassLine(string StringIn, Player & player)
	{
		cout << endl;

		StringIn = MakeStringLower(StringIn);

		vector<string> bits = SplitLineIntoStrings(StringIn);

		vector<Action> Actions = player.GetActions();

		bool DidAction = false;

		for (size_t i = 0; i < Actions.size(); i++)
		{
			pair<bool, Object*> Result = CheckAction(Actions[i], bits, player);

			if (Result.first == true)
			{
				DidAction = true;

				if ( Actions[i].ThreePart == true )
				{
					Object* Second = Result.second;
					Actions[i].ActionFunctionTool( &player , Result.second );

				}
				else
				{
					Actions[i].ActionFunction(&player);
				}
			}
		}		
		
		if (!DidAction)
		{
			cout << endl;
			cout << "Your Input is invalid";
			cout << endl;
		}

		cout << endl;

	}

	static string MakeStringLower(string in)
	{
		string NewString;
		for (size_t i = 0; i < in.size(); i++)
		{
			NewString.push_back(tolower(in[i]));
		}

		return NewString;
	}

	static vector<string> SplitLineIntoStrings(string & StringIn)
	{
		vector<string> bits;
		size_t pos = 0;
		size_t newpos;
		while (pos != string::npos) {
			newpos = StringIn.find_first_of(" ", pos);
			bits.push_back(StringIn.substr(pos, newpos - pos));
			if (newpos > StringIn.length()) break;
			pos = ++newpos;
		}

		return bits;
	}

	static pair< bool , Object* > CheckAction(Action ActionIn, vector<string> Line , Player & PlayerIn) {


		/////// ONE PART CHECKS
		bool KeyWordsMatch = false;
	
		for (size_t i = 0; i < ActionIn.KeyWords.size(); i++)
		{
			for (size_t k = 0; k < Line.size(); k++)
			{
				if (MakeStringLower(ActionIn.KeyWords[i]) == Line[k])
				{
 					KeyWordsMatch = true;
					break;
				}
			}
			
			if (KeyWordsMatch == true)
			{
				break;
			}

		}

		if (KeyWordsMatch == false)
		{
			return pair< bool, Object* >(false, nullptr);
		}
		
		if ( ActionIn.OnePart == true )
		{
			return pair< bool, Object* >(true, nullptr);
		}

		/////// TWO PART CHECKS

		string ToolLower = MakeStringLower(ActionIn.Tool);

		bool IsTool = IsToolInScene( Line , ToolLower );

		if (IsTool == false)
		{
			return pair< bool, Object* >(false, nullptr);
		}

		if (ActionIn.TwoPart == true)
		{	
			return pair< bool, Object* >(true, nullptr );
		}
		
		/////// THREE PART CHECKS

		Object* Second = FindTargetObjectInScene(Line, PlayerIn , ActionIn.Tool );

		if (Second != nullptr )
		{
			return pair< bool , Object* >( true , Second );
		}

		return pair< bool, Object* >(false, nullptr);

	}

	static Object * FindObject(string ObjName, Player & PlayerIn)
	{

		vector< Object* > Objects = PlayerIn.GetAvaibleObjects();

		for (size_t i = 0; i < Objects.size(); i++)
		{
			if (MakeStringLower( Objects[i]->Name ) == MakeStringLower( ObjName ) )
			{
				return Objects[i];
			}
		}

		return nullptr;

	}

	static Object* FindTargetObjectInScene( vector<string> Line , Player & PlayerIn , string ToolName)
	{

		for (size_t i = 0; i < Line.size(); i++)
		{
			Object* Result = FindObject(Line[i], PlayerIn);
			if (Result != nullptr && Result->Name != ToolName  )
			{
				return  Result;
			}
		}

		return nullptr;

	}

	static bool IsToolInScene( vector<string> Line , string ToolName )
	{
		for (size_t i = 0; i <Line.size(); i++)
		{

			if (Line[i] == ToolName)
			{
				return true;
			}

		}

		return false;
	}

};
