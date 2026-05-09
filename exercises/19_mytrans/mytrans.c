// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    *dict_count++;
  } 

  fclose(file);
  return 0;
}
