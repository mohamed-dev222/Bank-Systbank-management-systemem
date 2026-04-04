#pragma once
#include <vector>
#include <cctype>
using namespace std;

/*
	The clsString class provides various functionalities for handling strings, including methods for manipulating and analyzing string content.
*/
class clsString
{
private:
	string _Text;
public:
	clsString() { _Text = ""; }
	clsString(string Text) { _Text = Text; }
	void SetText(string Text)
	{
		_Text = Text;
	}
	string GetText()
	{
		return _Text;
	}
	static int Length(string Text)
	{
		int Count = 0;
		for (int i = 0; ; i++)
		{
			if (Text[i] == '\0') break;
			Count++;
		}
		return Count;
	}
	int Length()
	{
		return Length(_Text);
	}
	static int CounterWords(const string& S1)
	{
		if (S1.empty()) return 0;
		int Counter = 0;
		bool inWord = false;
		for (char c : S1)
		{
			if (c == ' ') inWord = false;
			else if (!inWord)
			{
				inWord = true;
				Counter++;
			}
		}
		return Counter;

	}
	int CounterWords()const
	{
		return CounterWords(_Text);
	}
	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool isFirstLetter = true;
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter) S1[i] = toupper(S1[i]);
			isFirstLetter = (S1[i] == ' ');
		}
		return move(S1);
	}
	void UpperFirstLetterOfEachWord()
	{
		_Text = move(UpperFirstLetterOfEachWord(_Text));
	}
	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool isFirstLetter = true;
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter) S1[i] = tolower(S1[i]);
			isFirstLetter = (S1[i] == ' ');
		}
		return move(S1);
	}
	void LowerFirstLetterOfEachWord()
	{
		_Text = LowerFirstLetterOfEachWord(_Text);
	}
	static string UpperAllString(string S1)
	{
		for (char &c : S1)  c = toupper(static_cast<unsigned char>(c));
		return S1;
	}
	void UpperAllString()
	{
		_Text = UpperAllString(_Text);
	}
	static std::string  LowerAllString(std::string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}
	void  LowerAllString()
	{
		_Text = LowerAllString(_Text);
	}
	static char InvertLetterCase(char c)
	{
		return isupper(c)  ? tolower(c) : toupper(c);
	}
	static string InvertAllLettersCase(string S1)
	{
		for (char& c : S1) c = InvertLetterCase(c);
		return S1;
	}
	void InvertAllLettersCase()
	{
		_Text = InvertAllLettersCase(_Text);
	}
	enum enWhatToCount { CapitalLetters = 1, SmallLetters  = 2, AllLetters = 3};
	static int CountCapitalLetters(string S1)
	{
		int Count = 0;
		for (char& c : S1) if (isupper(c)) Count++;
		return Count;
	}
	int CountCapitalLetters()
	{
		return CountCapitalLetters(_Text);
	}
	static int CountSmallLetters(string S1)
	{
		int Count = 0;
		for (char& c : S1) if (islower(c)) Count++;
		return Count;
	}
	int CountSmallLetters()
	{
		return CountSmallLetters(_Text);
	}
	static int CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::AllLetters)
	{
		switch (WhatToCount)
		{
		case enWhatToCount::CapitalLetters:
			return CountCapitalLetters(S1);
		case enWhatToCount::SmallLetters:
			return CountSmallLetters(S1);
		default:
			return S1.length();
		}
	}
	int CountAllLetters()
	{
		return CountLetters(_Text);
	}
	static int CountSpecificLetter(string S1, char SpecificalLetter, bool MatchCase = true)
	{
		int Count = 0;
		for (char& c : S1)
		{
			if (MatchCase)
			{
				if (c == SpecificalLetter) Count++;
			}
			else
			{
				if (toupper(c) == toupper(SpecificalLetter)) Count++;
			}
		}
		return Count;
	}
	int CountSpecificLetter(char SpecificalLetter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Text, SpecificalLetter, MatchCase);
	}
	static bool IsVowel(char c)
	{
		return string("AEIOUaeiou").find(c) != string::npos;
	}
	static int CountVowels(string S1)
	{
		int Count = 0;
		for (char& c : S1)
			if (IsVowel(c)) Count++;
		return Count;

	}
	int CountVowels()
	{
		return CountVowels(_Text);

	}
	static vector <string> Split(string S1, string Delimiter =  " ")
	{
		vector <string> vString;
		string sWord;
		int Pos;
		while((Pos = S1.find(Delimiter)) != string::npos)
		{
			sWord = S1.substr(0, Pos);
			if (sWord != "") vString.push_back(sWord);
			S1.erase(0, Pos + Delimiter.length());
		}
		if (S1 != "") vString.push_back(S1);
		return vString;
	}
	vector <string> Split(string Delimiter)
	{
		return Split(_Text, Delimiter);
	}
	static string TrimLeft(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
			if (S1[i] != ' ')
				return S1.substr(i);  
		return "";
	}
	void TrimLeft()
	{
		_Text = TrimLeft(_Text);
	}
	static string TrimRight(string S1)
	{
		for (int i = S1.length() -1; i >= 0; i--) if (S1[i] != ' ') return S1.substr(0, i+1);
		return "";
	}
	void TrimRight()
	{
		_Text = TrimRight(_Text);
	}
	static string Trim(string S1)
	{
		return TrimLeft(TrimRight(S1));
	}
	void Trim()
	{
		_Text = Trim(_Text);
	}
	static string JoinString(vector<string> vString, string Delimiter)
	{
		string sWord = "";
		for (string& s : vString)
		{
			sWord += s;
			if (vString.back() != s)
				sWord += Delimiter;
		}
		return sWord;
	}
	static string JoinString(string arrString[], short length, string Delimiter)
	{
		string sWord = "";
		for (int i = 0; i < length; i++)
		{
			sWord += arrString[i];
			if (i < length - 1)
				sWord += Delimiter;
		}
		return sWord;
	}
	static string ReverseWordsInString(string S1, string Delimiter = " ")
	{
		vector<string> vString = Split(S1, Delimiter);
		S1 = "";
		for (int i = vString.size() - 1; i >= 0; i--)
		{
			S1 += vString.at(i);
			if (i > 0)
				S1 += Delimiter;
		}
		return S1;
	}
	void ReverseWordsInString(string Delimiter = " ")
	{
		_Text = ReverseWordsInString(_Text, Delimiter);
	}
	static string ReplaceWord1(string S1, string Delimiter, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		vector<string> vString = Split(S1, Delimiter);
		for (string &s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace) s = sReplaceTo;
			}
			else
			{
				if (UpperAllString(s) == UpperAllString(StringToReplace)) s = sReplaceTo;
			}
		}
		return JoinString(vString, Delimiter);
	}
	string ReplaceWord1(string Delimiter, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		return ReplaceWord1(_Text, Delimiter, StringToReplace, sReplaceTo, MatchCase);
	}
	static string ReplaceWord2(string S1, string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		return ReplaceWord1(S1," ", StringToReplace, sReplaceTo, MatchCase);
	}
	string ReplaceWord2(string StringToReplace, string sReplaceTo, bool MatchCase = true)
	{
		return ReplaceWord2(_Text, StringToReplace, sReplaceTo,MatchCase );
	}
	static string RemovePunctuations(string S1)
	{
		string S2 = "";
		for (char c : S1)
		{
			if (!ispunct(c)) S2 += c;
		}
		return S2;
	}
	void RemovePunctuations()
	{
		_Text = RemovePunctuations(_Text);
	}
};

