#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>

int main() {
pid_t pid;

//Fork a child process
pid = fork();

if (pid < 0) { // Error occurred
std::cerr << "Fork Failed" << std::endl;
return 1;
}
else if (pid == 0) { // Child process
execlp("/bin/ls", "ls", NULL);
std::cout << "Hello World";
}
else { // Parent process
//sleep(100);
// Parent will wait for the child to complete
wait(NULL);
std::cout << "Child Complete" << std::endl;
}

return 0;
}		
