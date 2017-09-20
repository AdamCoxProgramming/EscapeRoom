#include<string>
#include<fstream>
#include<vector>
#include <stack>   
#include"ActionManager.cpp" 

using namespace std;

struct XmlParser
{

	struct XmlObject
	{
		string Name;

		string Info;

		vector<XmlObject> Children;

	};
		
	void LoadWorldFromFille(string FileName,ActionManager & Manager)
	{
		vector<string> ConnectionRoomNames;
		ActionMan = &Manager;
		Read(FileName);
		CreateObjects();
	}	

	private:

	ActionManager *ActionMan;

	void Read(string FileName) {

		fstream Stream(FileName);

		AddChild(Root, Stream, "");

	}

	void CreateObjects()
	{
		for (size_t i = 0; i < Root.Children.size(); i++)
		{
			if (Root.Children[i].Name == "room")
			{
				Room *Temp = CreateRoom(Root.Children[i]);
				World::GetInstance().Rooms[Temp->Name] = *Temp;
			}
			if (Root.Children[i].Name == "object")
			{
				CreateObject(Root.Children[i]);
			}
		}
	}

	bool IsNotBlank(const string & Text)
	{
		if (Text == "")
		{
			return false;
		}

		for (size_t i = 0; i < Text.size(); i++)
		{
			if (Text[i] != ' ')
			{
				return true;
			}
		}

		return false;

	}

	void AddChild(XmlObject & Object, fstream & Stream, string FirstLine)
	{
		
		bool isTag = false;
		bool isInfo = false;
		string Temp;
		bool First = true;
		bool b_FirstLine = true;

		while (Stream.eof() == false)
		{

			if (b_FirstLine == true)
			{
				b_FirstLine = false;
				Temp = FirstLine;
			}
			else 
			{
				getline(Stream, Temp);
			}

			size_t pos = 0;
			size_t newpos = 0;
			string Text;
			while (pos != string::npos) 
			{		
				newpos = Temp.find_first_of("<>/", pos);
				Text = Temp.substr(pos, newpos - pos);
		
				if (IsNotBlank(Text) == true)
				{
					if (Temp.length() >newpos &&  Temp[newpos] == '>')
					{
						isTag = true;
					}
					else
					{
						isTag = false;
					}
					if (Text != Object.Name)
					{
						if (isTag == true)
						{

							if (First == true)
							{
								First = false;
								Object.Name = Text;
							}
							else
							{		
								XmlObject NewObj;				
								AddChild(NewObj, Stream, Temp);
								Object.Children.push_back(NewObj);
								getline(Stream, Temp);
								pos = 0;
								newpos = 0;
								continue;
							}

						}
						else
						{
							Object.Info.append( Text);
						}
					}
					else {
						return;
					}
				}

				if (newpos > Temp.length()) break;
				pos = ++newpos;

			}
		}

	}

	XmlObject Root;

	Room* CreateRoom(XmlObject & RoomObj)
	{
		Room *BlankRoom = new Room("", "", vector<Object>{}, vector<string>{});

		for (size_t k = 0; k < RoomObj.Children.size(); k++)
		{
			if (RoomObj.Children[k].Name == "description")
			{
				BlankRoom->Description = RoomObj.Children[k].Info;
			}
			if (RoomObj.Children[k].Name == "name")
			{
				BlankRoom->Name = RoomObj.Children[k].Info;
			}
			if (RoomObj.Children[k].Name == "objects")
			{
				for (size_t z = 0; z < RoomObj.Children[k].Children.size(); z++)
				{
					BlankRoom->AddObject(*CreateObject(RoomObj.Children[k].Children[z]));
				}
			}
			if (RoomObj.Children[k].Name == "object")
			{
				BlankRoom->AddObject(*CreateObject(RoomObj.Children[k]));
			}
			if (RoomObj.Children[k].Name == "action")
			{
				BlankRoom->AddAction(CreateAction(RoomObj.Children[k] , &BlankRoom));
			}
			if (RoomObj.Children[k].Name == "connections")
			{
				for (size_t z = 0; z < RoomObj.Children[k].Children.size(); z++)
				{
					BlankRoom->AddConnection( RoomObj.Children[k].Children[z].Info );
				}
				
			}
			if (RoomObj.Children[k].Name == "connection")
			{				
				BlankRoom->Name = RoomObj.Children[k].Info;
			}

		}

		return BlankRoom;

	}

	Object* CreateObject(XmlObject & ObjectObj)
	{
		string Name;
		string Description;
		Object *Temp = new Object(Name, Description);

		void * Ptr = &Temp;

		for (size_t k = 0; k < ObjectObj.Children.size(); k++)
		{
			if (ObjectObj.Children[k].Name == "description")
			{
				Temp->Description = ObjectObj.Children[k].Info;
			}
			if (ObjectObj.Children[k].Name == "name")
			{
				Temp->Name = ObjectObj.Children[k].Info;
			}
			if (ObjectObj.Children[k].Name == "action")
			{
				Temp->AddAction( CreateAction(ObjectObj.Children[k], Temp));
			}
		}
		
		return Temp;

	}

	Action CreateAction(XmlObject & ActionObj , void * ActionHolder)
	{
		string Name;
		string Target;
		bool gotTarget = false;
		bool gotName = false;
		for (size_t k = 0; k < ActionObj.Children.size(); k++)
		{
			if (ActionObj.Children[k].Name == "name")
			{
				Name = ActionObj.Children[k].Info;
				gotName = true;
				//auto Test = ActionMan->ActionMaker[ActionObj.Children[k].Info]( ActionObj.Children[k].Info );
				//return Test;
			}	
			if (ActionObj.Children[k].Name == "target")
			{
				Target = ActionObj.Children[k].Info;
				gotTarget = true;
				//auto Test = ActionMan->ActionMaker[ActionObj.Children[k].Info]( ActionObj.Children[k].Info );
				//return Test;
			}
		}	

		if ( gotTarget && gotName )
		{
			return ActionMan->ActionMaker[Name](Target, ActionHolder);
		}
	}

};


