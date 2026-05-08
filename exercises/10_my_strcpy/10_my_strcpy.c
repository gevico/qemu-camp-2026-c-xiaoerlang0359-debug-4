#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	// TODO: 在这里添加你的代码
    int ptr = 0;
    while (source[ptr]!=NULL){
        destination[ptr] = source[ptr];
        ptr++;
    }
    destination[ptr] = NULL;
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}