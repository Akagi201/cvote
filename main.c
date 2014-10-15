/*
 * @file main.c
 * @author Akagi201
 * @date 2014/10/15
 * A Voting program in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "log.h"

#define WINNER_NUM (3)
#define LINE_MAX (1024)

int count_lines(char *filename) {
    FILE *fp = NULL;
    int lines = 0;
    char ch = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        LOG("Open file %s failed, error: %s", filename, strerror(errno));
        return 0;
    }

    while (!feof(fp)) {
        if ((ch = fgetc(fp)) == '\n') {
            ++lines;
        }
    }

    fclose(fp);                     //关闭文件
    return lines;
}

void print_line(const char *filename, int line) {

    FILE *fp = NULL;
    char buf[LINE_MAX] = {0};
    int linecount = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        LOG("Open file %s failed, error: %s", filename, strerror(errno));
        return;
    }

    while (NULL != fgets(buf, LINE_MAX, fp)) {
        ++linecount;

        if (linecount == line) {
            fputs(buf, stdout);
            break;
        }
    }

    return;
}

int main(int argc, char *argv[]) {

    int cur_win = 0;
    int lines = 0;
    int i = 0;
    int *candicate = NULL;

    const char *filename = NULL;

    if (argc <= 1) {
        printf("usage: %s candicate.txt\n", argv[0]);
        return 0;
    }

    srand((unsigned) time(NULL));

    filename = argv[1];

    lines = count_lines(filename);

    LOG("lines: %d", lines);

    candicate = (int *)calloc(lines, sizeof(int));



    for (i = 0; i < WINNER_NUM;) {
        cur_win = rand() % lines;

        if (candicate[cur_win] != 1) {
            candicate[cur_win] = 1;
            ++i;
            printf("The winner is %d line.\n", cur_win + 1);
            print_line(filename, cur_win + 1);
        }
    }

    free(candicate);

    return 0;
}
