#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>

#define MIN_PID 100
#define MAX_PID 1000

class pidManager{

	public:
	pidManager();
	int allocate_map(void);
	int allocate_pid(void);
	void release_pid(int pid);

	private:
	std::vector<int> bitmap;
	
};
