#include "header.h"

pidManager::pidManager(){
	std::cout<<"\nPID Manager Created\n\n";
};

int pidManager::allocate_map(void){
	
	bitmap = std::vector<int>(MAX_PID - MIN_PID, 0);

	if(bitmap.size() != MAX_PID - MIN_PID)
	{
		std::cout << "Bitmap Failed to Intialize..\n";
		return -1;
	}
	else if(bitmap.empty())
	{
		std::cout << "Bitmap Failed to Intialize..\n";
		return -1;
	}
	else
	{
		std::cout <<"Bitmap in range..\n";
		std::cout << "Bitmap initialized..\n";
		return 0;
	}
};

int pidManager::allocate_pid(void){

	if(bitmap.size() != MAX_PID - MIN_PID && bitmap.empty() != true)
	{
		std::cout<<"Cannot allocate PID due to range..\n";
		return -1;
	}else if(bitmap.empty())
	{
		std::cout<<"Cannot allocate because bitmap not initialized..\n";
		return -1;
	}

	for(int i = MIN_PID; i < MAX_PID; i++)
	{
		if(bitmap[i] == 0)
		{
			bitmap[i] = 1;

			std::cout << "PID " << i << " allocated..\n";
			return i;
		}
	}
	std::cout << "Failed to allocated pid..\n";
	return -1;

};

void pidManager::release_pid(int pid){
	if(pid < MIN_PID || pid > MAX_PID){
		std::cout << "Error, pid not intitialized or allocated\n";
	}
	else
	{
		bitmap[pid] = 0;
		std::cout << "PID " << pid << " released..\n";
	}	
};
