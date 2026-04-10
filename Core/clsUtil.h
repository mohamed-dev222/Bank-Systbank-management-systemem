#pragma once
#include <ctime>
#include "clsDate.h"
using namespace std;
/*
	The clsUtil class provides various utility functions for common operations, such as generating random numbers and characters, swapping values, and encrypting/decrypting text.
*/
	class clsUtil
	{
	public:
		enum  enCharType { SamallLetter = 1, CapitalLetter = 2, Digit = 3, MixChars = 4, SpecialCharacter = 5 };
		static void Srand()
		{
			srand((unsigned)time(NULL));
		}
		static int RandomNumber(const int& From, const int& To)
		{
			return rand() % (To - From + 1) + From;
		}
		static char GetRandomCharacter(enCharType CharType)
		{
			if (CharType == enCharType::MixChars)
			{
				CharType = (enCharType)RandomNumber(1, 3);
			}
			switch (CharType)
			{
			case enCharType::SamallLetter:
				return (char)RandomNumber(97, 122);
			case enCharType::CapitalLetter:
				return (char)RandomNumber(65, 90);
			case enCharType::Digit:
				return (char)RandomNumber(48, 57);
			case enCharType::SpecialCharacter:
				return (char)RandomNumber(33, 47);
			}
		}
		static string GenerateWord(int WordLength = 4, enCharType CharType = enCharType::CapitalLetter)
		{
			string Word = "";
			for (int i = 0; i < WordLength; i++)
			{
				Word += GetRandomCharacter(CharType);
			}
			return Word;
		}
		static  string GenerateKey(int KayLength = 4, int WordLength = 4, enCharType CharType = enCharType::CapitalLetter)
		{
			string Kay = "";
			for (int i = 0; i < KayLength; i++)
			{
				Kay += GenerateWord(WordLength, CharType);
				if (i < KayLength - 1) Kay += "-";
			}
			return Kay;
		}
		static void GenerateKeys(int NumOfKay, int KayLength = 4, int WordLength = 4, enCharType CharType = enCharType::CapitalLetter)
		{
			for (int i = 0; i < NumOfKay; i++)
			{
				cout << "Kay[" << i + 1 << "] : " <<
					GenerateKey(KayLength, WordLength, CharType) << endl;
			}
		}
		static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
		{
			for (int i = 0; i < arrLength; i++)
				arr[i] = RandomNumber(From, To);
		}
		static void FillArrayWithRandomWords(string arr[100], int arrLength, int WordLength = 4, enCharType CharType = enCharType::CapitalLetter)
		{
			for (int i = 0; i < arrLength; i++)
				arr[i] = GenerateWord(WordLength, CharType);

		}
		static void FillArrayWithRandomKeys(string arr[100], int arrLength, int KayLength = 4, int WordLength = 4, enCharType CharType = enCharType::CapitalLetter)
		{
			for (int i = 0; i < arrLength; i++)
				arr[i] = GenerateKey(KayLength, WordLength, CharType);
		}
		static void Swap(int& A, int& B)
		{
			int s = A;
			A = B;
			B = s;
		}
		static void Swap(double& A, double& B)
		{
			double s = A;
			A = B;
			B = s;
		}
		static void Swap(bool& A, bool& B)
		{
			bool s = A;
			A = B;
			B = s;
		}
		static void Swap(char& A, char& B)
		{
			char s = A;
			A = B;
			B = s;
		}
		static void Swap(string& A, string& B)
		{
			string s = A;
			A = B;
			B = s;
		}
		static void Swap(clsDate& A, clsDate& B)
		{
			clsDate s = A;
			A = B;
			B = s;
		}
		static void ShuffleArray(int arr[100], int length)
		{
			for (int i = 0; i < length; i++)
			{
				Swap(arr[RandomNumber(0, length - 1)], arr[RandomNumber(0, length - 1)]);
			}
		}
		static void ShuffleArray(string arr[100], int length)
		{
			for (int i = 0; i < length; i++)
			{
				Swap(arr[RandomNumber(0, length - 1)], arr[RandomNumber(0, length - 1)]);
			}
		}
		static string Tabs(short NumberOfTabs)
		{
			string t = "";
			for (int i = 0; i < NumberOfTabs; i++)
			{
				t = t + "\t";
			}
			return t;
		}
		
		static string EncryptText(string Text, short EncryptionKey= 2)
		{
			for (int i = 0; i < Text.length(); i++)
			{
				Text[i] = char((int)Text[i] + EncryptionKey);
			}
			return Text;
		}
		static string DecryptText(string Text, short EncryptionKey = 2)
		{
			for (int i = 0; i < Text.length(); i++)
			{
				Text[i] = char((int)Text[i] - EncryptionKey);
			}
			return Text;
		}
	};


