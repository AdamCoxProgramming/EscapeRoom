
#include"Room.cpp";
#include<map>;
struct World
{

	static World & GetInstance()
	{

		static World Instance;
		return Instance;
	}

	map<string, Room> Rooms;

	bool QRCodeOnScreen = false;

	private:

		World() {}		

};