#pragma once
#include <iostream>
#include <string>
#include <bitset>

using std::bitset;
using std::string;


class Helper
{
public:
	static void printWithColor(const string& letter, const string& color)
	{
		if (color == "red")
		{
			std::cout << "\033[1;31m" << letter << "\033[0m";
		}
		else if (color == "yellow")
		{
			std::cout << "\033[1;33m" << letter << "\033[0m";
		}
		else if (color == "green")
		{
			std::cout << "\033[1;32m" << letter << "\033[0m";
		}
		else if (color == "blue")
		{
			std::cout << "\033[1;34m" << letter << "\033[0m";
		}
		else if (color == "magenta")
		{
			std::cout << "\033[1;35m" << letter << "\033[0m";
		}
		else if (color == "cyan")
		{
			std::cout << "\033[1;36m" << letter << "\033[0m";
		}
		else if (color == "white")
		{
			std::cout << "\033[1;37m" << letter << "\033[0m";
		}
		else if (color == "black")
		{
			std::cout << "\033[1;30m" << letter << "\033[0m";
		}
		else
		{
			std::cout << letter;
		}
	}
	static void printBitset(const bitset<42>& bitset)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				std::cout << bitset[i * 7 + j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

