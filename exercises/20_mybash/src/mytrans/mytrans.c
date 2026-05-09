// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <libgen.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void trim(char *str) {
    // TODO: 在这里添加你的代码
    
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    // TODO: 在这里添加你的代码
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    if (strlen(line)==0)
      continue;
    if (line[0] != '#')
      continue;
    strcpy(current_word, line+1);
    if (!fgets(line, sizeof(line), file))
      break;
    line[strcspn(line, "\n")] = '\0';
    strcpy(current_translation, line+6);
    hash_table_insert(table,current_word, current_translation);
    (*dict_count)++;
  } 

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;

  // 基于可执行文件位置解析 dict.txt 路径
  char dict_path[512];
  char exe_path[512];
  ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
  if (len != -1) {
    exe_path[len] = '\0';
    // 可执行文件位于 .../20_mybash/bin/mybash
    // 向上两级到 exercises/20_mybash 目录
    char *exe_dir = dirname(exe_path);      // .../20_mybash/bin
    char exe_dir_copy[512];
    strncpy(exe_dir_copy, exe_dir, sizeof(exe_dir_copy) - 1);
    char *base_dir = dirname(exe_dir_copy); // .../20_mybash
    snprintf(dict_path, sizeof(dict_path), "%s/src/mytrans/dict.txt", base_dir);
  } else {
    // /proc/self/exe 不可用时回退到相对路径
    strncpy(dict_path, "src/mytrans/dict.txt", sizeof(dict_path) - 1);
  }

  if (load_dictionary(dict_path, table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}