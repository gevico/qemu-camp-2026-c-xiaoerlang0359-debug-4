#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];

int partition(int left, int right){
    Student pivot = students[left];
    int i = left;
    int j = right;
    while (i < j){
        while(i < j && students[j].score < pivot.score) j--;
        while(i < j && students[i].score >= pivot.score) i++;
        if (i<j){
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;
        }
    }
    students[left] = students[i];
    students[i] = pivot;
    return i;
}

void quick_sort(int left, int right) {
    // TODO: 在这里添加你的代码
    if (left>=right) return;
    int partition_pos = partition(left, right);
    quick_sort(left, partition_pos - 1);
    quick_sort(partition_pos+1,right);
}

int main(void) {
    FILE *file = fopen("03_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 03_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    quick_sort(0, n - 1);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}