#include "mysed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    // 检查输入参数有效性
    if (!cmd || !old_str || !new_str) {
        return -1;
    }
    
    // 初始化输出参数
    *old_str = NULL;
    *new_str = NULL;
    
    // TODO: 在这里添加你的代码
    int len = strlen(cmd);
    *old_str = (char*)malloc(len);
    *new_str = (char*)malloc(len);
    int i = 2;
    int old_i = 0;
    int new_i = 0;
    while (cmd[i] && cmd[i]!='/'){
        (*old_str)[old_i] = cmd[i];
        i++;
        old_i++;
    }
    (*old_str)[old_i] = '\0';
    if (cmd[i] != '/'){
        return -1;
    }
    i++;
    while (cmd[i] && cmd[i]!='/'){
        (*new_str)[new_i] = cmd[i];
        i++;
        new_i++;
    }
    (*new_str)[new_i] = '\0';
    if (cmd[i] != '/'){
        return -1;
    }

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // 检查输入参数有效性
    if (!str || !old || !new) {
        return;
    }
    char * pos = strstr(str, old);
    if (pos == NULL){
        printf("found none!!!");
        return;
    }
    int str_len = strlen(str);
    int old_len = strlen(old);
    for (char* p = pos; p<=(pos + str_len-old_len); p++){
        *p = *(p+old_len);
    }
    int new_len = strlen(new);
    for (char* p = (str+str_len); p >= pos; p--){
        *(p+new_len) = *(p);
    }
    int i=0;
    for (char* p=pos; p<(pos+new_len);p++){
        *p = new[i];
        i++; 
    }
    
}

int __cmd_mysed(const char* rules, const char* str) {
    // 检查输入参数有效性
    if (!rules || !str) {
        fprintf(stderr, "Error: NULL rules or str parameter\n");
        return 1;
    }

    printf("rules: %s\n", rules);
    printf("str: %s\n", str);

    char* old_str = NULL;
    char* new_str = NULL;

    // 解析规则，例如 "s/old/new/"
    if (parse_replace_command(rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    if (!old_str || !new_str) {
        fprintf(stderr, "Error: Failed to parse old/new strings from rules\n");
        free(old_str);
        free(new_str);
        return 1;
    }

    // 复制原始字符串，因为我们可能会修改它（避免修改输入参数）
    char line[1024];
    strncpy(line, str, sizeof(line) - 1);
    line[sizeof(line) - 1] = '\0';  // 确保终止

    // 执行替换：在 line 中把 old_str 替换为 new_str（第一次出现）
    replace_first_occurrence(line, old_str, new_str);

    // 输出结果（建议加上换行，除非 str 本身带了）
    printf("%s\n", line);

    // 释放动态分配的内存
    free(old_str);
    free(new_str);

    return 0;
}