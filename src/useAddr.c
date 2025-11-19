#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 输出：eval $(useAddr <ip>) 的环境变量方式
void print_shell_exports(const char *ip) {
    printf("export BIND_ADDR=%s\n", ip);
    printf("export LD_PRELOAD=/usr/local/lib/libsourceip.so\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "用法:\n");
        fprintf(stderr, "  useAddr <源IP>             # 切换当前 Shell 会话的 IP\n");
        fprintf(stderr, "  useAddr <源IP> <命令...>    # 使用指定 IP 执行命令\n");
        return 1;
    }

    const char *ip = argv[1];

    // 模式1：只有一个参数 → 输出 shell export 语句
    if (argc == 2) {
        print_shell_exports(ip);
        return 0;
    }

    // 模式2：多参数 → 直接执行命令
    setenv("BIND_ADDR", ip, 1);
    setenv("LD_PRELOAD", "/usr/local/lib/libsourceip.so", 1);

    execvp(argv[2], &argv[2]);
    perror("execvp");
    return 1;
}
