// Ride Sharing Project
// Usman Joined

#include <iostream>
#include <fstream>
#include <sstream>
#include "roads.h"
using namespace std;


Place *placeHead = nullptr;
struct User
{
	int userId;
	char *name;
	int isDriver; // 1=driver,0=passenger
	int rating;
	User *left; // BST
	User *right;
};
struct RideOffer
{
	int offerId;
	int driverId;
	Place *startPlace;
	Place *endPlace;
	int departTime;
	int capacity;
	int seatsLeft;
	RideOffer *next;
};
struct RideRequest
{
	int requestId;
	int passengerId;
	Place *fromPlace;
	Place *toPlace;
	int earliest;
	int latest;
	RideRequest *next;
};



User *userRoot = nullptr;
RideOffer *offerHead = nullptr;
RideRequest *requestHead = nullptr;

User *CreateUser(int userId,
				 const char *name,
				 int isDriver);
RideOffer *CreateRideOffer(int offerId, int driverId,
						   const char *start, const char *end,
						   int departTime, int capacity);
RideRequest *CreateRideRequest(int requestId, int passengerId,
							   const char *from, const char *to,
							   int earliest, int latest);
int MatchNextRequest();
void PrintUserHistory(int userId);
void PrintTopDrivers(int k);

int main()
{
	cout << "Hello world" << endl;

	fstream roadLinksFile;
	roadLinksFile.open("roads.txt");
	loadRoadNetworkFromFile(roadLinksFile);

	printGraph();

	return 0;
}
