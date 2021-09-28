#ifndef MINILIBMX_H
#define MINILIBMX_H

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct t_point {
    int x;
    int y;
}               point;

void mx_printchar(char);
void mx_printint(int);
void mx_printstr(const char *);
int mx_strlen(const char *);
void mx_printerr(const char *s);
int mx_count_substr(const char *str, const char *sub);
char *mx_file_to_str(const char *filename);
bool mx_isdigit(int c);
bool mx_isspace(char c);
int mx_atoi(const char *str, int *err);
void mx_alhororithm(int **arr, int width, int height ,point *begin, point *end);

#endif

