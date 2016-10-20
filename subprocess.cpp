#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd[2];
    int val = 0;
    int sum = 0;
    int avg = 0;
    int i = 0;
    int j = 0;
    int ar[argc];

    // create pipe descriptors
    pipe(fd);

    if (fork() != 0)
    {
        // parent
        close(fd[0]);

        for (i = 0; i < argc; i++)
        {

            ar[i] = atoi(argv[i]);

        }

        for (j = 0; j < argc; j++)
        {
            sum = sum + ar[j];
        }
        
        avg = sum/(argc-1);

        // send the value on the write-descriptor.
        val = avg;
        write(fd[1], &val, sizeof(val));
        printf("Parent(%d) send integer value: %d\n", getpid(), val);

        // close the write descriptor
        close(fd[1]);
    }
    else
    {   // child: reading only, so close the write-descriptor
        close(fd[1]);

        // now read the data (will block)
        read(fd[0], &val, sizeof(val));
        printf("Child(%d) received integer value: %d\n", getpid(), val);

        // close the read-descriptor
        close(fd[0]);
    }
    return 0;
}
