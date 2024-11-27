#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

class dfa {
private:
	int countStates; // êîëè÷åñòâî ñîñòîÿíèé àâòîìàòà
	vector<char> alphabet; // âõîäíîé àëôàâèò
	vector<int> finalStates; // ìíîæåñòâî äîïóñêàþùèõ ñîñòîÿíèé
	vector<vector<int>> transitFunction; // ôóíêöèÿ ïåðåõîäîâ 
	// transitFunction[i][j] = k îçíà÷àåò, ÷òî èç i-ãî ñîñòîÿíèÿ ïî j-ìó ñèìâîëó âõîäíîãî àëôàâèòà àâòîìàò ïåðåõîäèò â ñîñòîÿíèå k
	int getState(int state, char c);
	set<int> inverse(int state, int k);
public:
	dfa(int countStates, vector<char> alphabet, vector<int> finalStates, vector<vector<int>> transitFunction);
	bool isAccept(string s);
	dfa minimize();
	vector<vector<int>> quotientSet();
};

