/***************************************************************
	Project I Chapter Three - Sharing Data Between Data
	
	File Name:   project1.3.2.cpp
***************************************************************/
	#include <iostream>
	#include <string>
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
	
	class MartialArtist
	{
		private:
			
		protected:
			double fight;
			
		public:
			virtual double Attack() = 0; 
			MartialArtist(double f) { fight = f; } 
		
			virtual ~MartialArtist() = default;
			MartialArtist() = default;
			MartialArtist& operator=(MartialArtist&& value) 
			{ 
				fight = std::move(value.fight); 
				return*this;
			} 
		
			MartialArtist& operator=(const MartialArtist&) {return*this;}
	}; 
	
	class JiuJitsu : public MartialArtist
	{ 
		public: 
				JiuJitsu(double f) : MartialArtist(f){	};	
				void title()
				{	
					//std::lock_guard<std::mutex> guard1(mutually);
					mutually.lock();	
					std::cout << "I am a Jiu Jitsu Practitioner." << '\n'; 
					std::cout << "The ground is my ocean," << '\n';   
					std::cout << "I am a shark," << '\n'; 
					std::cout << "and you don't know how to swim!!!" << '\n';
					mutually.unlock();
				}
			
			JiuJitsu& operator=(JiuJitsu&&) = default; 
			JiuJitsu& operator=(const JiuJitsu&) = default;
		
			~JiuJitsu() {}; 
			
			double Attack() override {
				return fight * 3 / 4;
			} 
	}; 
	
	
	class Boxer : public MartialArtist
	{ 
		public:
			Boxer(double f) : MartialArtist(f){	};
			void title()
			{ 
				//std::lock_guard<std::mutex> guard2(mutually);
				mutually.lock();
				std::cout <<"I am a Boxing Practitioner."<< '\n';   
				std::cout <<"Everyone has a plan,"<< '\n';   
				std::cout <<"until they get punched in the face!!!"<< '\n';
				mutually.unlock();
			}
			
			Boxer& operator=(Boxer&&) = default; 
			Boxer& operator=(const Boxer&) = default;
			
			~Boxer() { }; 
			double Attack() override { 
				return fight * 4 / 5;
			} 
	}; 
	
	void FightStyle(MartialArtist& fighter)
	{
		mutually.lock();
		std::cout << "Strength of Style: " << fighter.Attack() << '\n'; 
		std::cout << '\n'; 
		mutually.unlock();  
	}
	
	void level(MartialArtist& fighter)
	{
		fighter;
		std::thread v(FightStyle,std::ref(fighter));
		thread_guard gv(v);
	}	
	
	int main() 
	{
		JiuJitsu gracie(39.75);
		std::thread t1(&JiuJitsu::title,&gracie);
		level(gracie); 
		
		Boxer tyson(20);
		std::thread t2(&Boxer::title,&tyson);
		level(tyson);
		
		thread_guard g1(t1);
		thread_guard g2(t2);
		
		
		
		return 0; 
	}
