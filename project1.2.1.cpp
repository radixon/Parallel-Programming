/***************************************************************
	Project I Chapter Two - Managing threads
	
	Demonstrate capabilities to execute concepts presented
	in Chapter Fifteen.
	
	File Name:   project1.2.1.cpp
***************************************************************/

	#include <iostream>
	#include <vector>
	#include <thread>
		
	void title()
	{
		std::cout << "\nFind the sum of all the multiples of 3 or 5 below 1000.\n\n";
	}
	
	bool mult_3(int num)
	{
		bool answer = true;
		int const measure = 3;
		answer = num % measure;
				
		return answer;		 
	}
	
	
	bool mult_5(int num)
	{
		bool answer = true;
		int const measure = 5;
		answer = num % measure;
				
		return answer;		 
	}
	
	int main( )
	{
		std::vector<int> stor;
		int value = 1000;
		int count = 0;
		
		std::thread t(title);
		t.join();
		
		while(value > 1)
		{
			if(mult_5(value) != true)
			{
				stor.push_back(value);
				count++;
				value--;
			}
			else if(mult_3(value) != true)
			{
				stor.push_back(value);
				count++;
				value--;
			}
			else
			{
				value--;
			}			
		}
		
		while(count > 0)
		{
			std::cout << stor[count] << '\t';
			value++;
			count--;
		}
		
		while(value > 1)
		{
			count += stor[value];
			value--;
		}
		
		std::cout << '\n' << "The sum of multiples of 3 or 5 less than 1000 is:\t" << count;
		
		return 0;		
	}
