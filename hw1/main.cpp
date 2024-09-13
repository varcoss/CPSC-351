#include "header.h"

int main()
{
	pidManager parent;
	std::cout<<"Parent Object:\n";
	parent.allocate_map();
	parent.allocate_pid();
	parent.allocate_pid();
	parent.allocate_pid();
	parent.release_pid(100);
	parent.release_pid(101);
	parent.release_pid(102);
	
	pid_t pid = fork();


	if(pid < 0)
	{
		std::cout<<"\nFailed to create fork..\n";
	}
	else if(pid == 0)
	{
		std::cout<<"\nChild Fork Intitiated..\n";
		pidManager child;
		std::cout<<"Child Object:\n";
		child.allocate_map();
		child.allocate_pid();
		child.allocate_pid();
		child.release_pid(100);
		child.release_pid(101);
		std::cout<<"Child Process finished..\n";
	}
	else
	{
		wait(NULL);
		std::cout<<"\nParent Fork Intiated..\n";
		parent.allocate_pid();
		parent.allocate_pid();
		parent.release_pid(101);
		parent.release_pid(100);
		std::cout<<"Parent Process finished..\n";
	}
	
	return 0;
}
