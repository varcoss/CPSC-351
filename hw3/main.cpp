#include <iostream> 
#include <vector>
#include <thread>
#include <cmath>
#include <mutex>
#include <algorithm>
#include <unistd.h>
#include <sys/wait.h>

bool checkingIfPrime(int number);

void workerFunction(int id, int start, int end, std::vector<int>& local){
	std::cout << "Thread " << id << " is working. " << start << " " << end <<" \n";

	// checking for primes and adding to vector
	while(start <= end )
	{
		if(checkingIfPrime(start))
		{
			local.push_back(start);
		}

		start++;
	}	
}

// checking for primes
bool checkingIfPrime (int number)
	{
		//excluding non prime numbers and divisable numbers
		if(number<=1)
		{
			return false;
		}
		else if(number<=3)
		{
			return true;
		}
		else if(number%2==0 || number%3==0)
		{
			return false;
		}

		// identifying non primes 
		for (int i=5; i <= std::sqrt(number); i = (i + 6))
		{
			if (number%i == 0 || number % (i + 2) == 0)
			{
				return false;
			}
		}

		// yay we did it
		return true;
	}


int main(int argc, char* argv[]){

	//getting input from user
	int limit = std::atoi(argv[1]);	

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

	std::vector<std::vector<int>> vectorOfVector(numThreads);

	// starting threads
	for (unsigned int i = 0; i <numThreads; ++i)
	{
		threads.emplace_back(workerFunction,i,range[i].first, range[i].second, std::ref(vectorOfVector[i]));
	}
	
	//waiting for threads
	for(auto& t:threads)
	{
		t.join();
	}

	//combining all vectors
	std::vector<int> finalVector;

	for (unsigned int i = 0; i < numThreads;i++)
	{
		finalVector.insert(finalVector.end(), vectorOfVector[i].begin(), vectorOfVector[i].end());
	}

	//sorting
	sort(finalVector.begin(), finalVector.end());

	//displaying sorted prime nums
	for(int i = 0; i< finalVector.size();i++)
	{
		std::cout<<finalVector[i] << " ";
	}

	std::cout<<"\n";
	
	return 0;
}
