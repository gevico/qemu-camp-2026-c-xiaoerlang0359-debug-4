#include <stdio.h>
#include <limits.h>

#define CHECK_OVERFLOW(carry) \
    carry ? "Overflow" : "Not Overflow"

int check_add_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "movl %1, %%eax\n\t"   // eax = a
        "addl %2, %%eax\n\t"   // eax += b, CF set if unsigned overflow
        "setc %0\n\t"          // carry = CF
        : "=r" (carry)
        : "r" (a), "r" (b)
        : "eax"
    );
    return carry;
}

int check_sub_overflow_asm(unsigned int a, unsigned int b) {
    unsigned char carry;
    __asm__ volatile(
        "movl %1, %%eax\n\t"   // eax = a
        "subl %2, %%eax\n\t"   // eax -= b, CF set if borrow (a < b)
        "setc %0\n\t"          // carry = CF
        : "=r" (carry)
        : "r" (a), "r" (b)
        : "eax"
    );
    return carry;
}

int check_mul_overflow_asm(unsigned int a, unsigned int b) {
    unsigned int high_bits;
    unsigned char overflow;
    __asm__ volatile(
        "movl %2, %%eax\n\t"   // eax = a
        "mull %3\n\t"          // edx:eax = eax * b, CF=1 if edx != 0
        "setc %0\n\t"          // overflow = CF
        "movl %%edx, %1\n\t"   // high_bits = edx
        : "=r" (overflow), "=r" (high_bits)
        : "r" (a), "r" (b)
        : "eax", "edx"
    );
    return overflow || (high_bits != 0);
}

int check_div_overflow_asm(unsigned int a, unsigned int b) {
    (void)a;  // a 在除法溢出检测中不使用
    unsigned char is_div_zero;
    __asm__ volatile(
        "cmpl $0, %1\n\t"      // cmp b, 0 → ZF=1 if b == 0
        "sete %0\n\t"          // is_div_zero = ZF
        : "=r" (is_div_zero)
        : "r" (b)
    );
    return is_div_zero;
}

int main() {
    printf("(UINT_MAX + 1)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(UINT_MAX, 1)));   // 1
    printf("(1, 0)Add: %s\n", CHECK_OVERFLOW(check_add_overflow_asm(1, 0)));  
    printf("(0, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(0, 1)));          // 1
    printf("(2, 1)Sub: %s\n", CHECK_OVERFLOW(check_sub_overflow_asm(2, 1)));
    printf("(UINT_MAX, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(UINT_MAX, 2)));   // 1
    printf("(1, 2)Mul: %s\n", CHECK_OVERFLOW(check_mul_overflow_asm(1, 2)));
    printf("(10, 0)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(10, 0)));                         // 1
    printf("(2, 1)Div: %s\n", CHECK_OVERFLOW(check_div_overflow_asm(2, 1)));
    return 0;
}