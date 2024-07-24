#pragma once
#include <iostream>
#include <string>


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
	static void printUint64(uint64_t num, int maxRows, int maxCols)
	{
		// Print the board
		for (int i = maxRows - 1; i >= 0; i--)
		{
			for (int j = 0; j < maxCols; j++)
			{
				uint64_t mask = 1;
				mask <<= (i * maxRows + j);
				if (num & mask)
				{
					Helper::printWithColor("1 ", "red");
				}
				else
				{
					Helper::printWithColor("0 ", "white");
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};

