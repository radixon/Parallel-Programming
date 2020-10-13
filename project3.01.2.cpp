/***************************************************************

	Project IV Substantially Multi-Threaded Program
	
***************************************************************/
	#include <iostream>
	#include <algorithm>
	#include <array>
	#include <thread>
	#include <mutex>
	
	std::mutex mutually;
	class thread_guard
	{
		private:
			std::thread& t;
		public:
			explicit thread_guard(std::thread& t_) : t(t_) { }
			~thread_guard()
			{
				if(t.joinable())
				{
					t.join();
				}
			}
			thread_guard(thread_guard const&)=delete;
			thread_guard& operator=(thread_guard const&)=delete;
	};
	
	
	
	
	void input_num(int i,std::array<int,10> &arr,int var)
	{
		std::lock_guard<std::mutex> guard(mutually);
		arr[var] = i;
	}
		
	void num_input(int num, std::array<int,10> &arr,int var)
	{
		std::thread v(input_num,num,std::ref(arr),var);
		thread_guard gv(v);
	}
	
	void sortArray(std::array<int,10> &soar)
	{
		std::lock_guard<std::mutex> fight(mutually);
		std::sort(soar.begin(),soar.end());
	}
	
	void callSort(std::array<int,10> &soar)
	{
		std::thread w(sortArray,std::ref(soar));
		thread_guard gw(w);
	}
	
	void printOutput(std::array<int,20> arr)
	{
		std::lock_guard<std::mutex> guard(mutually);
		for(int i = 0; i < 20; i++)
		{
			std::cout << arr[i] << "\t";
		}
	}
	
	int main() 
	{
		int num[20];
		int entry;
		int x(0);
		int y(0);
	
		std::array<int,10> x_array;
		std::array<int,10> y_array;		
		std::array<int,20> z_array;
		
		std::cout << "Please enter twenty numbers of your choosing:" << '\n';
		for(int i=0;i<20;i++)
		{
			std::cin >> entry;
			if(i%2 == 0)
			{
				x = i/2;
				num_input(entry,x_array,x);
			}
			else
			{
				y = i/2;
				num_input(entry,y_array,y);
			}
		}
		
		callSort(x_array);
		callSort(y_array); 
				
		std::merge(x_array.begin(),x_array.end(),y_array.begin(),y_array.end(),z_array.begin());
		
		std::cout << "The merged and sorted container results:\n";		
		printOutput(z_array);
				
		return 0; 
	}

