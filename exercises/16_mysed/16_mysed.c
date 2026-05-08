#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

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
    // TODO: 在这里添加你的代码
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

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
