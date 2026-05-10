#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
    unsigned int result;
    
    // 内联汇编实现欧几里得算法: while(b!=0) { t=a%b; a=b; b=t; }
    __asm__ volatile (
        "mov %1, %%eax\n\t"     // 将a存入eax
        "mov %2, %%ebx\n\t"     // 将b存入ebx
        "jmp .L_check\n\t"      // 跳转到检查条件
        
        ".L_loop:\n\t"
        "xorl %%edx, %%edx\n\t" // 清空edx（div需要edx:eax作为被除数）
        "divl %%ebx\n\t"        // edx:eax / ebx → edx = a % b
        "movl %%ebx, %%eax\n\t" // a = 原来的 b
        "movl %%edx, %%ebx\n\t" // b = a % b（余数）
        
        ".L_check:\n\t"
        "testl %%ebx, %%ebx\n\t" // 测试ebx是否为0
        "jne .L_loop\n\t"        // 如果不为0，继续循环
        
        "mov %%eax, %0"         // 将结果（eax）存入输出变量
        : "=r" (result)          // 输出操作数：结果存入result
        : "r" (a), "r" (b)       // 输入操作数：a和b
        : "eax", "ebx", "edx"    // 被修改的寄存器（通知编译器）
    );
    
    return result;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    printf("%d\n", gcd_asm(12, 8));
    printf("%d\n", gcd_asm(7, 5));
    return 0;
}