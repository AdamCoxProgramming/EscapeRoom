#include"LineParser.cpp" 
#include<vector>
#include<conio.h>
#include<algorithm>
using namespace std;

string ScreenText;

int main() {
	
	//Monster Creature;
	Player MainCharecter;
	
	ActionManager ActionMan( MainCharecter );
	
	XmlParser Reader;
	Reader.LoadWorldFromFille("Rooms.txt", ActionMan);

	MainCharecter.CurrentRoom = "Office";

	MainCharecter.AddAction(ActionMan.Actions["lookaround"]);
	MainCharecter.AddAction(ActionMan.Actions["inventory"]);
	MainCharecter.AddAction(ActionMan.Actions["run"]);

	std::cout << endl;

	std::cout << "Debt" << endl << endl;

	std::cout << "I awoke with a banging headache wearing only a t-shirt and my boxers, I had nothing on my person and no memory of how I'd got here, but I had a familiar burning desire to impress the world and become rich. There was a door but it was locked it seemed to be controlled by the scanner on the wall next to it. All I had to rely on was my quick thinking and ingenuity!" << endl << endl;

	std::cout << "I had better LOOK AROUND and LOOK AT objects that could help me I thought to myself!" << endl << endl;

	for (;;)
	{			
		while (_kbhit())
		{
			char CharEnterd = _getch();
			string Temp;
			int OldLineLength = ScreenText.size();

			switch (CharEnterd)
			{
				case  '\b' :
					
					if (ScreenText.size() > 0)
					{
						ScreenText.pop_back();
					}
				
					break;

				case  '\r' :
		
					LineParser::PassLine(ScreenText, MainCharecter);					

					ScreenText.clear();

					break;

				default:
					ScreenText.push_back(CharEnterd);
				break;
			}

			string WhiteSpaces = " ";

			for (size_t i = 0; i < ScreenText.size() ; i++)
			{
				WhiteSpaces.push_back( ' ' );
			}

			WhiteSpaces.push_back('\r');
			cout << ScreenText;
			cout<< (WhiteSpaces);

		}

	}
		
	return 1;

}

