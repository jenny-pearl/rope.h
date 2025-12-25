#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

typedef struct {
        char *str;
        int len;
} String;

#define STR_LITERAL(s) (String){ (s), sizeof((s)) - 1 }
#define STRFMT(s) (s).len, (s).str

#define str_cmp(x, y) str_n_cmp((x), (y), INT_MAX)

String str_tok(String *orig, char *term);
String sub_str(String former, int start, int end);
int str_n_cmp(String former, String latter, int count);
void *str_first_x(String *str, char x);
void *str_last_x(String *str, char x);
void *mem_set(void *dst, int c, size_t len);
void *mem_cpy(void *src, void *dst, size_t count);

int main(int argc, char **argv) {
        String a = STR_LITERAL("hello");
        printf("%.*s\n", STRFMT(a));
        return 0;
}

String sub_str(String former, int start, int end) {
        if (end > former.len) {
                end = former.len;
        }
        if (start > end) {
                start = end;
        }
        return (String){ (former.str + start), (end - start) };
}

int str_n_cmp(String former, String latter, int count) {
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

void *mem_cpy(void *src, void *dst, size_t count) {
        if (!src || !dst) {
                return NULL;
        }

        for (size_t i = 0; i < count; i++) {
                *(char *)(dst + i) = *(char *)(src + i); 
        }

        return dst;
}

String str_tok(String *orig, char *delim) {
        size_t i = 0;
        while (i < orig->len && orig->str[i] != *delim) {
                i++;
        }

        String res = (String){ (orig->str), (i) };

        if (i < orig->len) {
                orig->str += i + 1;
                orig->len -= i + 1;
        } else {
                orig->str += i;
                orig->len -= i;
        }

        return res;
}

void *mem_set(void *dst, int c, size_t len)
{
        if (!dst) {
                return NULL;
        }

        for (size_t i = 0; i < len; i++) {
                *(char *)(dst + i) = c;
        }

        return dst;
}

void *str_first_x(String *str, char x)
{
        int index = 0;

        while (str->str[index++] != x && index < str->len)
                ;

        if (index == str->len) {
                return NULL;
        }

        return (str->str + index);
}

void *str_last_x(String *str, char x)
{
        int index = 0;
        void *last = NULL;

        while (x < str->len) {
                if (str->str[index] == x) {
                        last = (str + index);
                }
        }

        return last;
}
