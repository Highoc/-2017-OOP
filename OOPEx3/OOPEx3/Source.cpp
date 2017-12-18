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
typedef int  Points;
typedef int  Wins;

map<string, map<string, Result>> competitionTable;
map<string, pair<Points, Wins>>  winnersTable;

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

void findWinPlace(pair<Points, Wins>& firstPlace, pair<Points, Wins>& secondPlace, pair<Points, Wins>& thirdPlaice);

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
			cout << "Exit." << endl;
			break;
		}

		int err = addToTables(nameA, nameB, goalsA, goalsB);
		if (err == repeatedRecord)
		{
			cout << "It's repeated record." << endl;
		}
		else if (err == repeatedTeamName)
		{
			cout << "Teamname is repeated in record." << endl;
		}
		else
		{
			printTable();
		}
		//cout << nameA << " - " << nameB << " - " << goalsA << delB << goalsB << endl;
	}

	system("pause");
	return 0;
}

int addToTables(const string &nameA, const string &nameB, int gA, int gB)
{
	if (nameA == nameB)
	{
		return repeatedTeamName;
	}

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
	else
	{
		return repeatedRecord;
	}

	return noErrors;
}

void printTable()
{
	int nTeams = winnersTable.size();
	int nameLength = getMaxNameLength(), nLength = 1, sLength = 1;
	
	pair<Points, Wins> firstPlace, secondPlace, thirdPlace;
	findWinPlace(firstPlace, secondPlace, thirdPlace);

	printLine(nameLength, nTeams, nLength, sLength);
	printTitle(nameLength, nTeams, nLength, sLength);
	printLine(nameLength, nTeams, nLength, sLength);

	int i = 1;
	for (const auto &mapPair : competitionTable) 
	{
		cout << "|"; cout.width(nLength); cout << std::left << i++;
		cout << "|"; cout.width(nameLength); cout << std::left << mapPair.first;

		for (const auto &winmapPair : winnersTable)
		{
			cout << "|"; cout.width(1);
			if (mapPair.second.count(winmapPair.first) > 0)
			{
				 cout << std::left << mapPair.second.at(winmapPair.first);
			}
			else
			{
				cout << std::left << (char) space;
			}
		}

		cout << "|"; cout.width(sLength); cout << std::left << winnersTable[mapPair.first].first;
		cout << "|"; cout.width(1); 
		
		if (winnersTable[mapPair.first] == firstPlace)
		{
			cout << "1";
		}
		else if (winnersTable[mapPair.first] == secondPlace)
		{
			cout << "2";
		} 
		else if (winnersTable[mapPair.first] == thirdPlace)
		{
			cout << "3";
		}
		else
		{
			cout << " ";
		}
		
		cout << "|" << endl;

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

int getMaxNameLength()
{
	int result = 0;
	
	for (const auto &mapPair : winnersTable) 
	{
		result = (mapPair.first.length() > result) ? mapPair.first.length() : result;
	}

	return result + 1;
}

void printLine(int nameLength, int nTeams, int nLength, int sLength)
{
#define minusLine(length) for (size_t i = 0; i < length; i++) {cout << "-";}
#define plusLine(length)  for (size_t i = 0; i < length; i++) {cout << "+";}
	
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
	cout << endl;

#undef plusLine
#undef minusLine
}

void printTitle(int nameLength, int nTeams, int nLength, int sLength)
{
	cout << "|"; cout.width(nLength); cout << std::left << "N";
	cout << "|"; cout.width(nameLength); cout << std::left << "Name";

	for (size_t i = 0; i < nTeams; i++)
	{
		cout << "|"; cout << std::left << i + 1;
	}

	cout << "|"; cout.width(sLength); cout << std::left << "S";
	cout << "|"; cout.width(1); cout << "P";
	cout << "|" << endl;
}

void findWinPlace(pair<Points, Wins>& firstPlace, pair<Points, Wins>& secondPlace, pair<Points, Wins>& thirdPlace)
{
	firstPlace  = { 0, 0 };
	secondPlace = { 0, 0 };
	thirdPlace  = { 0, 0 };

	for (const auto &mapPair : winnersTable)
	{
		//cout << "now: " << mapPair.second.first << " " << mapPair.second.second << " " << endl;
		if((mapPair.second.first > firstPlace.first) || (mapPair.second.first == firstPlace.first) && (mapPair.second.second >= firstPlace.second))
		{
			if ((mapPair.second.first == firstPlace.first) && (mapPair.second.second >= firstPlace.second))
			{
				continue;
			}

			thirdPlace = secondPlace;
			secondPlace = firstPlace;
			firstPlace = mapPair.second;
		}
		else if((mapPair.second.first > secondPlace.first) || (mapPair.second.first == secondPlace.first) && (mapPair.second.second >= secondPlace.second))
		{
			if ((mapPair.second.first == secondPlace.first) && (mapPair.second.second >= secondPlace.second))
			{
				continue;
			}

			thirdPlace = secondPlace;
			secondPlace = mapPair.second;
		}
		else if ((mapPair.second.first > thirdPlace.first) || (mapPair.second.first == thirdPlace.first) && (mapPair.second.second >= thirdPlace.second))
		{
			if ((mapPair.second.first == thirdPlace.first) && (mapPair.second.second >= thirdPlace.second))
			{
				continue;
			}

			thirdPlace = mapPair.second;
		}

		//cout << firstPlace.first << " " << firstPlace.second << " " << endl;
		//cout << secondPlace.first << " " << secondPlace.second << " " << endl;
		//cout << thirdPlace.first << " " << thirdPlace.second << " " << endl << endl;
	}
}