#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string.h>

#define MIN_PID 100
#define MAX_PID 1000

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

class pidManager{

	public:
	pidManager();
	int allocate_map(void);
	int allocate_pid(void);
	void release_pid(int pid);

	private:
	std::vector<int> bitmap;
	
};
