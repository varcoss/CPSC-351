#include <iostream> 
#include <vector>
#include <thread>
#include <cmath>
#include <mutex>
#include <algorithm>

std::vector<int> workerFunction(int id, int start, int end){
	std::cout << "Thread " << id << " is working. " << start << " " << end <<" \n";
	
	// local vector that will store prime numbers
	std::vector<int> local;

	return local;
}

int main(){
	std::vector<int> primeNums;	
	int limit = 0;
	
	// getting input from user
	for(int i = 1; i > 0;i++)
	{
		std::cin >> limit;

		if( limit >= 1)
		{
			break;
		}
		else //if input invalid, then loop
		{
			std::cout<< "input invalid, try again\n";
		}

	}

	// getting threads of csystem
	unsigned int numThreads = std::thread::hardware_concurrency();

	//checking for errors
	if(numThreads == 0)
	{
		numThreads = 2;
	}

	std::cout<< "Creating " << numThreads << " threads.\n";

	//creating vector to store the start and end of nums to be used later
	std::vector<std::pair<int,int>>range;
	int start = 1;
	int end = 0;
	int remaining = limit % numThreads;
	
	//loop that determines start and end range of digits 
	// & stores them in a vector 
	for (int i = 0; i <numThreads; i++)
	{
		end = start + (limit/numThreads) -1;

		if (i==numThreads - 1)
		{
			end = end + remaining;
		}

		range.push_back({start,end});
		start = end + 1;
	}

	// vector for threads
	std::vector<std::thread> threads;

	// starting threads
	for (unsigned int i = 0; i <numThreads; ++i)
	{
		primeNums = threads.emplace_back(workerFunction,i,range[i].first, range[i].second);
	}
	
	//waiting for threads
	for(auto& t:threads)
	{
		t.join();
	}
	
	return 0;
}
