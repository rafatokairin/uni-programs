%option noyywrap

%{
#include <stdio.h>

int lines = 1, blank = 0, comment = 0, semicolon = 0, directive = 0, is_blank = 0, cnt_line = 0, cnt_blank = 0, cnt_comment = 0, cnt_semicolon = 0, cnt_direct = 0, cnt_normal = 0;

void reset_counts() {
    lines = 1; blank = 0; comment = 0; semicolon = 0; directive = 0; is_blank = 0;
}
%}

%%
";" { semicolon++; }
"//" { comment++; }
"/*" { comment++; }
"*/" { comment++; }
"#"("include"|"define") { directive++; }

"\n" {
    if (is_blank) blank++;
    is_blank = 1;
    lines++;
}
. { is_blank = 0; }
%%

int main(int argc, char** argv) {
    printf("total lines  blank lines  lines w/ comments  nb, nc lines  semi-colons  prepoc. direct.\n");
    if (argc < 2) {
        yylex();
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (!file) {
            perror(argv[i]);
            return 1;
        }
        reset_counts();
        yyrestart(file);
        yylex();
        fclose(file);
        int normal = lines - blank - comment;
        printf("%d %d %d %d %d %d %s\n", lines, blank, comment, normal, semicolon, directive, argv[i]);
        cnt_line += lines;
        cnt_blank += blank;
        cnt_comment += comment;
        cnt_semicolon += semicolon;
        cnt_direct += directive;
        cnt_normal += normal;
    }
    if (argc > 1)
        printf("%d %d %d %d %d %d total\n", cnt_line, cnt_blank, cnt_comment, cnt_normal, cnt_semicolon, cnt_direct);
    return 0;
}
