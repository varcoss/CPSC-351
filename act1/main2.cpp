#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
pid_t pid = fork();

if (pid ==0){
	
std::cout << "Child's Parent Process ID (PPID):" << getppid() << std::endl;
sleep(15); //Sleep for 15 seconds
std::cout << "Child's Parent process ID (PPID):" << getppid() <<std::endl;
}

else if (pid>0){
sleep(5); // Sleep for 5 seconds
std::cout <<"Parent process Id:" << getpid() <<std::endl;
}

return 0;
}		
