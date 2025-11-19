#define _GNU_SOURCE
#include <dlfcn.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int (*real_connect)(int, const struct sockaddr *, socklen_t) = NULL;
static char source_ip[64] = {0};

__attribute__((constructor))
static void init() {
    char *env = getenv("BIND_ADDR");
    if (env)
        strncpy(source_ip, env, sizeof(source_ip)-1);

    real_connect = dlsym(RTLD_NEXT, "connect");
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t len) {
    if (source_ip[0]) {
        struct sockaddr_in local = {0};
        local.sin_family = AF_INET;
        inet_pton(AF_INET, source_ip, &local.sin_addr);
        bind(sockfd, (struct sockaddr *)&local, sizeof(local));
    }
    return real_connect(sockfd, addr, len);
}
