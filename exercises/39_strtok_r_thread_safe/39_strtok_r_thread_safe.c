#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 19 字符串分割器（类似 strtok_r）
 * 目标：实现线程安全的字符串分割函数，不依赖静态全局状态
 * 原型：char* strtok_r(char *str, const char *delim, char **saveptr)
 * 示例：输入 "hello,world test"，分隔符 ", " → 依次得到 hello、world、test
 */

/* 判断字符 c 是否在分隔符集合 delim 中 */
static int is_delim(char c, const char *delim) {
    // TODO: 在这里添加你的代码
    char * p =delim;
    while (*p!=NULL){
        if (*p==c) return 1;
        p++;
    }
    return 0;
}

/* 线程安全版本：通过 saveptr 维护调用状态，不使用静态变量 */
char *strtok_r(char *str, const char *delim, char **saveptr) {
    // TODO: 在这里添加你的代码
    char * pos;
    char * tail;
    if (*saveptr) pos = *saveptr;
    else pos = str;
    if (pos==NULL) return NULL;
    while (*pos && is_delim(*pos, delim)) pos++;
    if (*pos=='\0') return NULL;
    tail = pos;
    while (*tail && !is_delim(*tail, delim)) tail++; 
    if (*tail=='\0') *saveptr = tail;
    else {
        *tail = '\0';
        *saveptr = tail+1;
    }
    return pos;
}

int main(void) {
    char buf[] = "hello,world test";
    const char *delim = ", ";
    char *save = NULL;
    char *tok = strtok_r(buf, delim, &save);
    while (tok) {
        printf("%s\n", tok);
        tok = strtok_r(NULL, delim, &save);
    }
    return 0;
}
