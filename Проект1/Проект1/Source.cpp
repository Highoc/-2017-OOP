#include <iostream> 
#include <string> 
#include <map> 

using std::string;
using std::map;
using std::pair;

using std::cin;
using std::cout;
using std::endl;

typedef char Result;
typedef int Points;
typedef int Wins;

map<string, map<string, Result>> competitionTable;
map<string, pair<Points, Wins>> winnersTable;

enum Error
{
	noErrors = 0,
	repeatedRecord = 1,
	repeatedTeamName = 2
};

enum ResultStates
{
	win = 'W',
	lose = 'L',
	draw = 'D',
	oneself = 'X',
	space = ' '
};


int addToTables(const string& nameA, const string& nameB, int gA, int gB);
void printTable();

char getResult(int gA, int gB);
int getMaxNameLength();

void printLine(int nameLength, int nTeams, int nLength, int sLength);
void printTitle(int nameLength, int nTeams, int nLength, int sLength);

int main()
{
	string nameA, nameB, delA;
	int goalsA = 0, goalsB = 0;
	char delB = 0;

	while (true)
	{
		cin >> nameA >> delA >> nameB >> delA >> goalsA >> delB >> goalsB;
		if (!cin.good())
		{
			cout << "Exit."<< endl;
			break;
		}

		addToTables(nameA, nameB, goalsA, goalsB);
		printTable();
	}

	system("pause");
	return 0;
}

int addToTables(const string &nameA, const string &nameB, int gA, int gB)
{
	if (competitionTable.count(nameA) == 0)
	{
		competitionTable[nameA][nameA] = oneself;
		winnersTable[nameA] = pair<Points, Wins>(0, 0);
	}
	if (competitionTable.count(nameB) == 0)
	{
		competitionTable[nameB][nameB] = oneself;
		winnersTable[nameB] = pair<Points, Wins>(0, 0);
	}

	if (competitionTable[nameA].count(nameB) == 0)
	{
		competitionTable[nameA][nameB] = getResult(gA, gB);
		switch (getResult(gA, gB))
		{
		case win:
			winnersTable[nameA].first += 3;
			winnersTable[nameA].second += 1;
			break;
		case draw:
			winnersTable[nameA].first += 1;
			break;
		}
	}
	else
	{
		return repeatedRecord;
	}

	if (competitionTable[nameB].count(nameA) == 0)
	{
		competitionTable[nameB][nameA] = getResult(gB, gA);
		switch (getResult(gB, gA))
		{
		case win:
			winnersTable[nameB].first += 3;
			winnersTable[nameB].second += 1;
			break;
		case draw:
			winnersTable[nameB].first += 1;
			break;
		}
	}

	return 0;
}

void printTable()
{
	int nTeams = winnersTable.size();
	int nameLength = 12, nLength = 1, sLength = 1;

	int i = 1;
	for (const auto &mapPair : competitionTable)
	{
		cout<< "|"; cout.width(nLength); cout<< std::left<< i++;
		cout<< "|"; cout.width(nameLength); cout<< std::left<< mapPair.first;

		for (const auto &winmapPair : winnersTable)
		{
			cout<< "|"; cout.width(1);
			if (mapPair.second.count(winmapPair.first) > 0)
			{
				cout<< std::left<< mapPair.second.at(winmapPair.first);
			}
			else
			{
				cout<< std::left<<(char) space;
			}
		}

		cout<< "|\n"; cout.width(1);
		printLine(nameLength, nTeams, nLength, sLength);
	}
}

char getResult(int gA, int gB)
{
	if (gA > gB)
		return win;
	if (gA < gB)
		return lose;
	if (gA == gB)
		return draw;
}

void printLine(int nameLength, int nTeams, int nLength, int sLength)
{
#define minusLine(length) for (size_t i = 0; i < length; i++) {cout<< "-";} 
#define plusLine(length) for (size_t i = 0; i < length; i++) {cout<< "+";} 

	plusLine(1);
	minusLine(nLength);
	plusLine(1);
	minusLine(nameLength);

	for (size_t i = 0; i < nTeams; i++)
	{
		plusLine(1);
		minusLine(1);
	}

	plusLine(1);
	minusLine(sLength);
	plusLine(1);
	minusLine(1);
	plusLine(1);
	cout<< endl;

#undef plusLine 
#undef minusLine 
}