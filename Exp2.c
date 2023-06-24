#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        printf("Failed to fork a child process.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        char *args[] = {"ls", "-l", NULL};  // Command and its arguments

        if (execv("/bin/ls", args) == -1) {
            printf("Failed to execute the command.\n");
            return 1;
        }
    } else {
        // Parent process
        wait(NULL);  // Wait for the child process to finish
        printf("Child process finished.\n");
    }

    return 0;
}
