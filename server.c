#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int fd1;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    while (1)
    {
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, str1, 80);

        // Print the read string and close
        printf("Client: %s\n", str1);
        if(strcmp(str1,"exit\n")==0){
        	close(fd1);
        	break;
        }
        close(fd1);

        // Now open in write mode and write
        // string taken from user.
        fd1 = open(myfifo,O_WRONLY);
        printf("Server: ");
        fgets(str2, 80, stdin);
        
        write(fd1, str2, strlen(str2)+1);
        if(strcmp(str2,"exit\n")==0){
        	close(fd1);
        	break;
        }
        close(fd1);
    }
    return 0;
}

