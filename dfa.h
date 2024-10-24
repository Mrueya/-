#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

class dfa {
private:
	int countStates; // количество состояний автомата
	vector<char> alphabet; // входной алфавит
	vector<int> finalStates; // множество допускающих состояний
	vector<vector<int>> transitFunction; // функция переходов 
	// transitFunction[i][j] = k означает, что из i-го состояния по j-му символу входного алфавита автомат переходит в состояние k
	int getState(int state, char c);
	set<int> inverse(int state, int k);
public:
	dfa(int countStates, vector<char> alphabet, vector<int> finalStates, vector<vector<int>> transitFunction);
	bool isAccept(string s);
	dfa minimize();
	vector<vector<int>> quotientSet();
};

