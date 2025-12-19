// Ride Sharing Project
// Usman Joined

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "user.h"
//#include <ctring>

using namespace std;


User* CreateUser(User* root, int userId, const char *name, int isDriver) {
    if (!root) {
        User* newUser = new User;
        newUser->userId = userId;
        newUser->name = new char[strlen(name)+1];
        strcpy(newUser->name, name);
        newUser->isDriver = isDriver;
        newUser->rating = 5; // default rating
        newUser->completedRides = 0;
        newUser->history = nullptr;
        newUser->left = newUser->right = nullptr;
        return newUser;
    }

    if (userId < root->userId) {
        root->left = CreateUser(root->left, userId, name, isDriver);
    } else {
        root->right = CreateUser(root->right, userId, name, isDriver);
    }

    return root;
}

// Search user by ID
User* SearchUser(User* root, int userId) {
    if (!root)
	 return nullptr;
    if (root->userId == userId)
	 return root;
    if (userId < root->userId)
	 return SearchUser(root->left, userId);
    else
	 return SearchUser(root->right, userId);
}

void PrintUser(User* u) {
    if (!u) return;
    cout << "ID: " << u->userId
         << " | Name: " << u->name
         << " | ";
    if (u->isDriver == 1)
        cout << "Driver";
    else
        cout << "Passenger";
    cout << " | Rating: " << u->rating;
    if (u->isDriver == 1)
        cout << " | CompletedRides: " << u->completedRides;
    cout << endl;
}

// Inorder print all users
void PrintAllUsers(User* root) {
    if (!root) return;
    PrintAllUsers(root->left);
    PrintUser(root);
    PrintAllUsers(root->right);
}

HistoryNode* InsertHistoryBST(HistoryNode* root, int rideId,
                              const char* from, const char* to, int time)
{
    if (root == nullptr) {
        // Create a new node
        HistoryNode* newNode = new HistoryNode;
        newNode->rideId = rideId;

        newNode->from = new char[strlen(from)+1];
        strcpy(newNode->from, from);

        newNode->to = new char[strlen(to)+1];
        strcpy(newNode->to, to);

        newNode->time = time;
        newNode->left = newNode->right = nullptr;

        return newNode;
    }

    // Compare by time
    if (time < root->time) {
        root->left = InsertHistoryBST(root->left, rideId, from, to, time);
    } else {
        root->right = InsertHistoryBST(root->right, rideId, from, to, time);
    }

    return root;
}

void AddHistory(int userId, int rideId,
                const char* from, const char* to, int time)
{
    User* u = SearchUser(userRoot, userId);
    if (!u) {
        cout << "User not found!" << endl;
        return;
    }

    u->history = InsertHistoryBST(u->history, rideId, from, to, time);
}

void PrintHistoryBST(HistoryNode* root)
{
    if (!root) return;

    PrintHistoryBST(root->left);

    cout << "  Ride ID: " << root->rideId
         << " | From: " << root->from
         << " | To: " << root->to
         << " | Time: " << root->time << endl;

    PrintHistoryBST(root->right);
}

void PrintUserHistory(int userId)
{
    User* u = SearchUser(userRoot, userId);
    if (!u) {
        cout << "User not found!" << endl;
        return;
    }

    cout << "Ride History of " << u->name
         << " (ID " << u->userId << "):" << endl;

    if (!u->history) {
        cout << "  No ride history available." << endl;
        return;
    }

    PrintHistoryBST(u->history);
}

bool PassengerExists(int passengerId)
{
    User* u = SearchUser(userRoot, passengerId);

    if (u == nullptr)
        return false;

    // passenger = isDriver == 0
    return (u->isDriver == 0);
}

bool DriverExists(int driverId)
{
    User* u = SearchUser(userRoot, driverId);

    if (u == nullptr)
        return false;

    // driver = isDriver == 1
    return (u->isDriver == 1);
}

static void CollectDrivers(User* root, vector<User*>& out)
{
    if (!root) return;
    CollectDrivers(root->left, out);
    if (root->isDriver == 1)
        out.push_back(root);
    CollectDrivers(root->right, out);
}

void PrintTopDrivers(int k)
{
    if (k <= 0)
    {
        cout << "K must be > 0\n";
        return;
    }

    vector<User*> drivers;
    CollectDrivers(userRoot, drivers);

    if (drivers.empty())
    {
        cout << "No drivers found.\n";
        return;
    }

    sort(drivers.begin(), drivers.end(),
         [](const User* a, const User* b)
         {
             if (a->completedRides != b->completedRides)
                 return a->completedRides > b->completedRides;
             // tie-breaker: higher rating, then smaller userId
             if (a->rating != b->rating)
                 return a->rating > b->rating;
             return a->userId < b->userId;
         });

    int limit = (k < (int)drivers.size()) ? k : (int)drivers.size();
    cout << "Top " << limit << " drivers by completed rides:\n";
    for (int i = 0; i < limit; i++)
    {
        User* d = drivers[i];
        cout << (i + 1) << ") "
             << "ID: " << d->userId
             << " | Name: " << d->name
             << " | CompletedRides: " << d->completedRides
             << " | Rating: " << d->rating
             << '\n';
    }
}


