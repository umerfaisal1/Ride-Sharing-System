#ifndef USER_H
#define USER_H

struct HistoryNode
{
    int rideId;
    char *from;
    char *to;
    int time;
    HistoryNode *left;   // BST left
    HistoryNode *right;  // BST right
};

struct User
{
	int userId;
	char *name;
	int isDriver; // 1=driver,0=passenger
	int rating;
    int completedRides; // Phase 9: count of completed rides (drivers only)
	HistoryNode* history;
	User *left; // BST
	User *right;
};

extern User* userRoot;

User* CreateUser(User* root, int userId, const char *name, int isDriver);

User* SearchUser(User* root, int userId);

void PrintAllUsers(User* root);
void PrintUser(User* u);

HistoryNode* InsertHistoryBST(HistoryNode* root, int rideId,
                              const char* from, const char* to, int time);

void AddHistory(int userId, int rideId,
                const char* from, const char* to, int time);

void PrintHistoryBST(HistoryNode* root);

void PrintUserHistory(int userId);

void PrintTopDrivers(int k);

bool PassengerExists(int passengerId);
bool DriverExists(int driverId);


#endif