#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;
    const char *p;

    // 找到 '?'，参数从它后面开始
    p = strchr(url, '?');
    if (p == NULL) {
        err = -1;
        goto exit;
    }
    p++; // 跳过 '?' 本身

    // 逐段解析 key=value
    while (*p) {
        // 输出 key
        printf("key = ");
        while (*p && *p != '=') {
            putchar(*p);
            p++;
        }

        // 必须有 '='，否则格式错误
        if (*p != '=') {
            err = -1;
            goto exit;
        }
        printf(", value = ");
        p++; // 跳过 '='

        // 输出 value，将 '+' 替换为空格
        while (*p && *p != '&') {
            putchar(*p);
            p++;
        }

        putchar('\n');

        // 跳过 '&'，继续下一个参数
        if (*p == '&') {
            p++;
        }
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}