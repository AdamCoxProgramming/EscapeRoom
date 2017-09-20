
#include<map>;
#include<string>;
#include<iostream>;
#include"Player.cpp"
using namespace std;

struct ActionManager
{

	map<string, Action> Actions;

	map< string, std::function< Action( string Target, void * ContainingObject)> >  ActionMaker;

	ActionManager(Player ThePlayer)
	{	
		

		auto LookAround = [](Player * In) {

			cout << endl;
			cout << World::GetInstance().Rooms[In->CurrentRoom].Description;
			cout << endl;

			int ContentSize = World::GetInstance().Rooms[In->CurrentRoom].RoomsContents.size();

			if (ContentSize > 0)
			{
				cout << "In this room there is a ";

				if (ContentSize > 1)
				{

					Room tetmp = World::GetInstance().Rooms[In->CurrentRoom];

					for (size_t i = 0; i < ContentSize; i++)
					{

						cout << World::GetInstance().Rooms[In->CurrentRoom].RoomsContents[i].Name;

						if (i != ContentSize - 1 && i != ContentSize - 2)
						{
							cout << ", ";
						}

						if (i == ContentSize - 2)
						{
							cout << " and a ";
						}


					}

				}
				else {

					cout << World::GetInstance().Rooms[In->CurrentRoom].RoomsContents[0].Name;

				}

				cout << endl;


			}

			cout << "You could enter the ";	

			int ConnectionSize = World::GetInstance().Rooms[In->CurrentRoom].Connections.size();

			for (size_t i = 0; i < ConnectionSize; i++)
			{
				cout << World::GetInstance().Rooms[In->CurrentRoom].Connections[i];
				if (i != ConnectionSize - 1)
				{
					if (i == ConnectionSize - 2)
					{
						cout << " or ";
					}
					else
					{
						cout << ", ";
					}
				}

			}

			cout << endl;


		};

		vector<string> LookAroundKeyWords{ "Look" , "observe" };
		Action LookAroundAction( LookAroundKeyWords , false , "around" , LookAround , "Observe the room" );

		Actions["lookaround"] = LookAroundAction;
	
		//////////

		auto CreateEnterFunction = [ThePlayer]( string Target, void * ContainingObject ) -> Action {
					
			auto Enterfunction = [ Target ](Player * PlayerIn ) {
					
				cout << endl;
				PlayerIn->CurrentRoom = Target;
				cout << "You enter the " + Target  << endl;
			};

			vector<string> EnterWords{ "Enter", "Go" ,"walk"};
			Action EnterAction(EnterWords, false , Target,Enterfunction , "enter" );

			return EnterAction;
		};

		ActionMaker["enter"] = CreateEnterFunction;

		//////////

		auto CreatePickUpFunction = [ThePlayer](string Target , void* AttatchedTo ) -> Action {

			Object * Holder = reinterpret_cast<Object *>(AttatchedTo);

			string Description = "Pick it up";

			auto PickUpfunction = [Target, Holder , Description]( Player * PlayerIn ) {

			PlayerIn->Inventory.push_back( *Holder );

			cout << endl;

			Holder->RemoveAction(Description);
			
			cout << "You have picked up a " + Target;

			if (Target == "mat")
			{
				World::GetInstance().Rooms["porch"].AddConnection("stairs");

				cout << endl << "under the mat was some hidden stairs" << endl;
			}

			for (size_t i = 0; i < World::GetInstance().Rooms[PlayerIn->CurrentRoom].RoomsContents.size(); i++)
			{

				if (World::GetInstance().Rooms[PlayerIn->CurrentRoom].RoomsContents[i].Name == Holder->Name)
				{
					World::GetInstance().Rooms[PlayerIn->CurrentRoom].RoomsContents.erase
					(
						World::GetInstance().Rooms[PlayerIn->CurrentRoom].RoomsContents.begin() + i
					);
				}

			} 

			cout << endl;

			};

			vector<string> PickWords{ "pick" ,"take" };
			Action PickAction(PickWords, false ,Target, PickUpfunction , Description );

			return PickAction;

		};

		ActionMaker["pick"] = CreatePickUpFunction;

		//////////

		auto CreateHitFunction = [ThePlayer](string Target, void* AttatchedTo) -> Action {

			Object * Holder = reinterpret_cast<Object *>(AttatchedTo);

			auto Hitfunction = [Target, Holder](Player * PlayerIn , Object* ObjectIn ) {
								
				//PlayerIn->Inventory.push_back(*Holder);

				cout << endl;

				cout << "Smaked It " + Target;

				//int NumberOfObjectsInRoom = World::GetInstance().Rooms[PlayerIn->CurrentRoom].RoomsContents.size();

				cout << endl;

			};
			
			vector<string> HitWords{ "hit" };
			Action HitAction(HitWords, true ,Target, Hitfunction , "hit things with it");

			return HitAction;

		};

		ActionMaker["hit"] = CreateHitFunction;


		//////////////////////

		auto CreatePlugFunction = [ThePlayer](string Target, void* AttatchedTo) -> Action {

			Object * Holder = reinterpret_cast<Object *>(AttatchedTo);

			auto Plugfunction = [Target, Holder](Player * PlayerIn, Object* ObjectIn) {

				if ( ObjectIn->Name == "Charger" )
				{

				cout << endl;

				cout << "The phones screen turns on ";

				Holder->Description = "The phone shows a QR code";
				cout << endl;
				cout << "The phone has a quick charge and is now fully charged!";

				World::GetInstance().QRCodeOnScreen = true;

				}
				else
				{
					cout << endl;

					cout << " you cant plug this into a " + ObjectIn->Name + " you cray muther fucer";
				}

				//int NumberOfObjectsInRoom = World::GetInstance().Rooms[PlayerIn->CurrentRoom].RoomsContents.size();

				cout << endl;

			};

			vector<string> PlugWords{ "plug" , "charge" };
			Action PlugAction(PlugWords, true, Target, Plugfunction , "Plug it into a charger if there is a charger available" );

			return PlugAction;

		};

		ActionMaker["plug" ] = CreatePlugFunction;

		//////////////////////

		auto CreateScanFunction = [ThePlayer](string Target, void* AttatchedTo) -> Action {

			Object * Holder = reinterpret_cast<Object *>(AttatchedTo);

			auto Scanfunction = [Target, Holder](Player * PlayerIn, Object* ObjectIn) {

				bool PhoneIsInInventory = false;

				for (size_t i = 0; i < PlayerIn->Inventory.size(); i++)
				{
					if (PlayerIn->Inventory[i].Name == "Phone")	PhoneIsInInventory = true;
				}

				if (ObjectIn->Name == "Phone" && PhoneIsInInventory && World::GetInstance().QRCodeOnScreen )
				{
					cout << endl;
					cout << "The door unlocks and opens" ;
					World::GetInstance().Rooms["Office"].AddConnection("corridor");
					for (size_t i = 0; i < World::GetInstance().Rooms["Office"].RoomsContents.size() ; i++)
					{
						if (World::GetInstance().Rooms["Office"].RoomsContents[i].Name == "Door")
						{
							World::GetInstance().Rooms["Office"].RoomsContents[i].Description = "An open door";
						}
					}
				}
				else
				{		
					
					cout << endl;
					cout << "The scan had no effect";
				}

				cout << endl;

			};

			vector<string> ScanWords{ "scan" , "show" };
			Action ScanAction(ScanWords, false, Target, Scanfunction , "Scan things");

			return ScanAction;

		};

		ActionMaker["scan"] = CreateScanFunction;

		////////

		auto CreateLookAtFunction = [ThePlayer](string Target, void * AttatchedTo) -> Action {

			Object * Holder = reinterpret_cast<Object *>(AttatchedTo);

			string Description = "Look at it";

			auto LookAtfunction = [ Target , Holder , Description](Player * PlayerIn)
			{
				cout << endl;
				cout << Holder->Description << endl;

				bool onlyLookAt = false;

				if ( (Holder->GetNumberOfActions() == 1) && Holder->GetActions()[0].Description == Description)
				{
					onlyLookAt = true;
				}

				if ( Holder->GetNumberOfActions() > 0 && onlyLookAt == false)
				{
					cout << "Options with this " + Holder->Name + ": " << endl;

					vector<Action> HolderActions =  Holder->GetActions();

					for (size_t i = 0; i <HolderActions.size(); i++)
					{
						if (HolderActions[i].Description != Description)
						{
							cout << HolderActions[i].Description << endl;
						}
						
					}
				}

			};

			vector<string> LookAtKeyWords{ "Look" , "Check" };
			Action LookAtAction(LookAtKeyWords, false , Target, LookAtfunction , Description);

			return LookAtAction;

		};

		ActionMaker["lookat"] = CreateLookAtFunction;

		////////

		auto Runfunction = [](Player * PlayerIn) {

			

			int NumOfConnections = PlayerIn->GetCurrentRoom().Connections.size();
			if (NumOfConnections > 0)
			{
				int RandInRange = rand() % (NumOfConnections);

				Room Current = PlayerIn->GetCurrentRoom();

				PlayerIn->CurrentRoom = PlayerIn->GetCurrentRoom().Connections[RandInRange];
				cout << endl;
				cout<< (PlayerIn->GetCurrentRoom().Description);
				cout << endl;
			}
			else {
				cout << endl;
				cout << ("there is nowhere to run");
				cout << endl;
			}
		
		};

		vector<string> RunKeyWords{ "run" };
		Action RunAction(RunKeyWords, false , Runfunction , "Run" );
	
		Actions["run"] = RunAction;

		///////////

		auto Inventoryfunction = [](Player * PlayerIn) {

			int InventorySize = PlayerIn->Inventory.size();

			if (InventorySize > 0)
			{
				cout << endl;
				if (InventorySize > 1)
				{
					cout << ("In your Inventory is : ");
					for (size_t i = 0; i < InventorySize; i++)
					{
						cout << endl;
						cout << PlayerIn->Inventory[i].GetName();;
						cout << endl;
					}
				}
				else
				{
					cout << ("In your Inventory is a ");
					cout << endl;
					cout << PlayerIn->Inventory[0].GetName();;
					cout << endl;
				}

			}
			else
			{
				cout << endl;
				cout << ("Your Inventory is empty ");
				cout << endl;
			}

			
		

		};

		vector<string> InventoryKeyWord{ "inventory" };
		Action InventoryAction(InventoryKeyWord, false , Inventoryfunction , "Look at Inventory");

		Actions["inventory"] = InventoryAction;

	}

};