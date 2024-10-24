#pragma once
#include "Token.h"
#include "HashTable.h"
#include "TrunsFunctions.h"
#include "dfa.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

class Lexer {
private:
    HashTable hashTable;

    void getNextToken(vector<char>& alphabet, string& s, bool flag) {
		if (s != "") {
			if (flag)
				if (dfa(countStatesStringExpr, alphabet, finalStatesStringExpr, transitFunctionStringExpr).isAccept(s)) {
				hashTable.insert(Token(TokenType::STRING_EXPR, s));
				flag = 0;
				s.clear();
				return;
				}
			if (dfa(countStatesKeyWord, alphabet, finalStatesKeyWord, transitFunctionKeyWord).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesInt, alphabet, finalStatesInt, transitFunctionInt).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesChar, alphabet, finalStatesChar, transitFunctionChar).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesString, alphabet, finalStatesString, transitFunctionString).isAccept(s)) {
				hashTable.insert(Token(TokenType::KEYWORD, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesMain, alphabet, finalStatesMain, transitFunctionMain).isAccept(s)) {
				hashTable.insert(Token(TokenType::FUNCTION, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesVar, alphabet, finalStatesVar, transitFunctionVar).isAccept(s)) {
				hashTable.insert(Token(TokenType::ID, s));
				s.clear();
				return;
			}
			else if (dfa(countStatesConst, alphabet, finalStatesConst, transitFunctionConst).isAccept(s))
			{
				hashTable.insert(Token(TokenType::CONST, s));
				s.clear();
				return;
			}
			hashTable.insert(Token(TokenType::ERROR, s));
			s.clear();
		}
    }

public:
	void Alphabet(vector<char> &alphabet, string &alp) {
		for (char c = 'a'; c <= 'z'; c++) {
			alphabet.push_back(c);
		}
		for (char c = 'A'; c <= 'Z'; c++) {
			alphabet.push_back(c);
		}
		for (char c = '0'; c <= '9'; c++) {
			alphabet.push_back(c);
		}
		alphabet.push_back('.');
		alphabet.push_back('+');
		alphabet.push_back('-');
		alphabet.push_back(',');
		alphabet.push_back(';');
		alphabet.push_back('?');
		alphabet.push_back('!');
		alphabet.push_back('"');
		alphabet.push_back('(');
		alphabet.push_back(')');
		alphabet.push_back('{');
		alphabet.push_back('}');
		alphabet.push_back('=');
	alp = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?";
	}

	bool IsValidChar(char c, const std::string& alphabet) {
		for (char validChar : alphabet) {
			if (c == validChar) {
				return true;
			}
		}
		return false;
	}

	Lexer(ifstream& cin) {
		vector<char> alphabet;
		string alp;
		Alphabet(alphabet, alp);

		string str; char temp; 
		while (!cin.eof()) {
			bool f = 0;
			cin.get(temp);
			if (temp == '"') {
				f = 1;
				getNextToken(alphabet, str, f);
			}
			else if (temp == ',' || temp == '.') {
				getNextToken(alphabet, str, f);
				string u = "";
				u += temp;
				hashTable.insert(Token(TokenType::SEPARATORS, u));
			}
			else if (temp == ';') {
				getNextToken(alphabet, str, f);
				hashTable.insert(Token(TokenType::SEPARATORS, ";"));
			}
			else if (temp == '{') {
				getNextToken(alphabet, str, f);
				hashTable.insert(Token(TokenType::SEPARATORS, "{"));
			}
			else if (temp == '}') {
				getNextToken(alphabet, str, f);
				hashTable.insert(Token(TokenType::SEPARATORS, "}"));
			}
			else if (temp == '(') {
				getNextToken(alphabet, str, f);
				hashTable.insert(Token(TokenType::SEPARATORS, "("));
			}
			else if (temp == ')') {
				getNextToken(alphabet, str, f);
				hashTable.insert(Token(TokenType::SEPARATORS, ")"));
			}
			else if (temp == ' ') {
				getNextToken(alphabet, str, f);
			}
			else if (temp == '\n') {
				getNextToken(alphabet, str, f);
			}
			else if (temp == '+' || temp == '-' || temp == '=') {
				getNextToken(alphabet, str, f);
				string o = "";
				o += temp;
				hashTable.insert(Token(TokenType::OPERATOR, o));
			}
			else if (!IsValidChar(temp, alp)) {
				getNextToken(alphabet, str, f);
				string e = "";
				e += temp;
				hashTable.insert(Token(TokenType::ERROR, e));
			}
			else {
				str += temp;
			}
		}

	}
	HashTable getHashTable()
	{
		return this->hashTable;
	}
};
