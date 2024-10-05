#include <iostream> 
#include <vector>
#include <thread>
#include <cmath>
#include <mutex>
#include <algorithm>

void workerFunction(int id, int start, int end){
	std::cout << "Thread " << id << " is working. " << start << " " << end <<" \n";
}

int main(){
	
	int limit = 0;

	for(int i = 1; i > 0;i++)
	{
		std::cin >> limit;

		if( limit >= 1)
		{
			break;
		}
		else
		{
			std::cout<< "input invalid, try again\n";
		}

	}

	unsigned int numThreads = std::thread::hardware_concurrency();

	if(numThreads == 0)
	{
		numThreads = 2;
	}

	std::cout<< "Creating " << numThreads << " threads.\n";

	std::vector<std::pair<int,int>>range;
	int start = 1;
	int remaining = limit % numThreads;

	for (int i = 0; i <numThreads; i++)
	{
		int end = start + (limit/numThreads);

		if (i==numThreads - 1)
		{
			start = end + remaining;
		}

		range.push_back({start,end});
		start = end + 1;
	}




	std::vector<std::thread> threads;

	for (unsigned int i = 0; i <numThreads; ++i)
	{
	
		threads.emplace_back(workerFunction,i,range[i].first, range[i].second);
	}
	
	for(auto& t:threads)
	{
		t.join();
	}
	
	return 0;
}
