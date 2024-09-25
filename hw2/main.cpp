#include "header.h"

int main()
{
	//Number Options for message
	// 0 == NA
	// 1 == allocate_pid
	// 2 == release_pid
	// 3 == Done
	char write_msg[BUFFER_SIZE];
	char read_msg[BUFFER_SIZE];


	//Creating Pipe to transfer data
	int fd1[2], fd2[2], fd3[2], fd4[2];
	pid_t pid;

	//Checking for errors
	if (pipe(fd1) == -1
	|| pipe(fd2) == -1
	|| pipe(fd3) == -1
	|| pipe(fd4) == -1)	
	{
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	
	//forking
	pid = fork();


	if(pid < 0) // checking for errors
	{
		std::cout<<"\nFailed to create fork..\n";
	}
	else if(pid == 0) // child fork
	{
		//sending request for PID
		sprintf(write_msg, "%d", 1);	
		close(fd1[READ_END]);
		write(fd1[WRITE_END],write_msg, strlen(write_msg)+1);
		close(fd1[WRITE_END]);
	
		//receiving PID from parent	
		close(fd2[WRITE_END]);
		read(fd2[READ_END],read_msg,BUFFER_SIZE);
		printf("Hello from child, received PID: %s",read_msg);
		std::cout<<std::endl;
		close(fd2[READ_END]);

		//sending request to release PID
		sprintf(write_msg, "%d", 2);
		close(fd3[READ_END]);
		write(fd3[WRITE_END],write_msg, strlen(write_msg)+1);
		close(fd3[WRITE_END]);

		//sending request to end program
		sprintf(write_msg, "%d", 3);
		close(fd4[READ_END]);
		write(fd4[WRITE_END],write_msg, strlen(write_msg)+1);
		close(fd4[WRITE_END]);

	}
	else //parent fork
	{
		//creating parent pid setup
		pidManager parent;
		parent.allocate_map();

		//reading request for PID from child
		close(fd1[WRITE_END]);
		read(fd1[READ_END],read_msg,BUFFER_SIZE);
		close(fd1[READ_END]);

		if(strcmp(read_msg, "1") == 0)
		{
			//sending PID to child
			sprintf(write_msg, "%d", parent.allocate_pid());
			close(fd2[READ_END]);
			write(fd2[WRITE_END],write_msg, strlen(write_msg)+1);
			close(fd2[WRITE_END]);
		}

		//reading command
		close(fd3[WRITE_END]);
		read(fd3[READ_END],read_msg,BUFFER_SIZE);
		close(fd3[READ_END]);
	
		if(strcmp(read_msg, "2") == 0)
		{
			// releasing pid
			printf("Parent received request to release PID 100");
			std::cout<<std::endl;
			parent.release_pid(100);
		}

		close(fd4[WRITE_END]);
		read(fd4[READ_END],read_msg,BUFFER_SIZE);
		close(fd4[READ_END]);

		if(strcmp(read_msg, "3") == 0)
		{
			std::cout<<"Ending program \n";
			return 0;
		}

	}
	
	return 0;
}
