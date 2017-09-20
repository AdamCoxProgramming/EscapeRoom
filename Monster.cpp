
#include<string>
#include<vector>
#include<iostream>
#include"World.cpp"
struct Monster {

	string CurrentRoom;

	void Move()
	{
		int NumOfConnections = World::GetInstance().Rooms[CurrentRoom].Connections.size();
		if (NumOfConnections > 0)
		{

			int RandInRange = rand() % (NumOfConnections);
			//CurrentRoom = World::GetInstance().Rooms[CurrentRoom].Connections[RandInRange];
		
		}

	}

	void Update(float deltaTime)
	{
		TimeSinceMove += deltaTime;
		//cout << deltaTime << endl;
		if (TimeSinceMove > TimeToMove)
		{
			Move();
			TimeSinceMove = 0;
			//cout << CurrentRoom->Name << endl;

		}

	}

	private:

	float TimeSinceMove = 0;

	int TimeToMove = 7;

};