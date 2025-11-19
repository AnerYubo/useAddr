#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "用法: %s <源IP> <命令> [参数...]\n", argv[0]);
        return 1;
    }

    setenv("BIND_ADDR", argv[1], 1);
    setenv("LD_PRELOAD", "/usr/local/lib/libsourceip.so", 1);

    execvp(argv[2], &argv[2]);
    perror("execvp");
    return 1;
}
