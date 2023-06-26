#include <stdio.h>
#include <unistd.h>

int main() {
    char* args[] = { "/bin/ls", "-l", NULL };
    execv("/bin/ls", args);

    printf("This line will not be executed if execv is successful.\n");
    return 0;
}
