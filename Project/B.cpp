#include <bits/stdc++.h>

struct fun {
    int first_line, last_line, tot_line;
    std::string name;
};

char str[100000];

// Find ") {", if stack is empty, then it's the start line.
std::string get_fun_name(int p) {
    std::string name = "";
    // find last (
    int i = p;
    while (str[i] != '(')
        i--;

    // the function name is before (
    while (--i >= 0) {
        if (str[i] == ' ') {
            if (!name.empty())
                break;
            else continue;
        }
        name += str[i];
    }
    std::reverse(name.begin(), name.end());
    return name;
}

bool is_code = false, is_comment = false, is_empty = true;
int code_line = 0, comment_line = 0, empty_line = 0;
char ch, last_ch;

// maintain a stack for {}
int top = 0;
// current line
int line = 1;

std::vector<fun> funs;
int first_line = -1, last_line = -1, pre_line = -1, pre_pos = -1;
bool end_with_enter = false;
std::string Name, fun_name;
int cur = 0;

char judge_code() {
    int a = code_line;
    a /= funs.size();
    if (10 <= a && a <= 15)
        return 'A';
    if (8 <= a && a <= 20)
        return 'B';
    if (5 <= a && a <= 24)
        return 'C';
    return 'D';
}

char judge_percent(int a) {
    if (15 <= a && a <= 25)
        return 'A';
    if (10 <= a && a <= 30)
        return 'B';
    if (5 <= a && a <= 35)
        return 'C';
    return 'D';
}

char judge_comment() {
    int a = comment_line * 100 / line;
    return judge_percent(a);
}

char judge_empty() {
    int a = empty_line * 100 / line;
    return judge_percent(a);
}

void print() {
    for (int i = 0; i < int(funs.size()); i++) {
        fun it = funs[i];
        printf("Function \"%s\" starts with line %d, ends with line %d, which has %d lines.\n",
               it.name.c_str(), it.first_line, it.last_line, it.tot_line);
    }
    printf("There are %d code lines in total.\n", code_line);
    printf("There are %d comment lines in total.\n", comment_line);
    printf("There are %d empty lines in total.\n", empty_line);
    printf("There are %d lines in total.\n", line);

    printf("Code Lines Grade: %c\n", judge_code());
    printf("Comment Lines Grade: %c\n", judge_comment());
    printf("Empty Lines Grade: %c\n", judge_empty());
}

signed main() {
    // freopen("code.c", "r", stdin);
    // freopen("ans_code.txt", "w", stdout);
    freopen("B.cpp", "r", stdin);
    freopen("ans_B.txt", "w", stdout);

    while ((ch = getchar()) != EOF) {
        if (is_comment && ch != '\n')
            continue;
        str[cur++] = ch;
        if (last_ch == ')' && ch == '{'/*}*/ && top == 0) {
            fun_name = get_fun_name(pre_pos);
            first_line = pre_line;
        }
        if (ch == '{')
            top++;
        if (ch == '}')
            top--;

        // if {} are all matched, add them into vector
        if (top == 0 && first_line != -1) {
            last_line = line;
            funs.push_back({first_line, last_line, last_line - first_line + 1, fun_name});
            first_line = last_line = -1;
        }

        if (ch == '\n') {
            // add info of this line
            code_line += is_code;
            comment_line += is_comment;
            empty_line += is_empty;
            end_with_enter = true;

            // init next line
            line++;
            is_code = false;
            is_comment = false;
            is_empty = true;
        } else {
            end_with_enter = false;
            if (ch == '/' && !is_code) {
                is_comment = true;
                is_empty = false;
            }
            if (ch != ' ' && !is_comment) {
                is_code = true;
                is_empty = false;
            }
        }
        if (ch != ' ' && ch != '\n') {
            last_ch = ch;
            pre_pos = cur - 1;
            pre_line = line;
        }
    }
    // corner case about last line
    if (!end_with_enter) {
        code_line += is_code;
        comment_line += is_comment;
        empty_line += is_empty;
    } else
        line--;
    print();
    return 0;
}
