#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

typedef struct {
        char *str;
        int len;
} String;

#define STRLIT(s) (String){ (char *)(s), sizeof((s)) - 1 }
#define STRFORMAT(s) (int)(s).len, (s).str
#define STRFORMAT_PTR(s) (int)(s)->len, (s)->str

#define string_cmp(x, y) string_n_cmp((x), (y), INT_MAX)

String init_string(char *line);
String substr(String former, int start, int end);
int string_n_cmp(String former, String latter, int count);

int main(int argc, char **argv) {
        String *a = &(STRLIT("hello"));
        printf("%.*s\n", STRFORMAT_PTR(a));
        return 0;
}

String substr(String former, int start, int end) {
        if (end > former.len) {
                end = former.len;
        }
        if (start > end) {
                start = end;
        }
        return (String){ (former.str + start), (end - start) };
}

// strcmp(f > l) > 0

int string_n_cmp(String former, String latter, int count) {
        int index = 0;
        for ( ; index < former.len && index < latter.len && index < count; index++) {
                if (*(former.str + index) > *(latter.str + index)) {
                        return 1;
                } else if (*(former.str + index) < *(latter.str + index)) {
                        return -1;
                }
        }

        if (index == latter.len && index != former.len) {
                return 1;
        } else if (index == former.len && index != latter.len) {
                return -1;
        }

        return 0;
}
