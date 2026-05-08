#include <stdio.h>
#include <stdbool.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码
    int ptr = 0;
    bool space = true;
    while (str[ptr]!=NULL){
        if (space && str[ptr]!=' '){
            wordCount++;
            space = false;
        }
        else if (!space && str[ptr]==' '){
            space = true;
        }
        ptr++;
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}