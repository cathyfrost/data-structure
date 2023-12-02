#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义堆栈结构
typedef struct {
    char *array;
    int capacity;
    int top;
} Stack;

// 初始化堆栈
void initStack(Stack *s, int capacity) {
    s->array = (char *)malloc(capacity * sizeof(char));
    if (s->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->capacity = capacity;
    s->top = -1;
}

// 入栈操作
void push(Stack *s, char c) {
    if (s->top < s->capacity - 1) {
        s->array[++(s->top)] = c;
    } else {
        fprintf(stderr, "Stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

// 出栈操作
char pop(Stack *s) {
    if (s->top >= 0) {
        return s->array[(s->top)--];
    } else {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
}

// 判定括号是否匹配的函数
int areParenthesesBalanced(char expr[]) {
    Stack stack;
    int i;

    initStack(&stack, 100);

    // 遍历表达式中的每个字符
    for (i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            // 如果是开括号，入栈
            push(&stack, expr[i]);
        } else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
            // 如果是闭括号，检查栈顶的开括号是否匹配
            if (stack.top == -1 ||
                (expr[i] == ')' && pop(&stack) != '(') ||
                (expr[i] == ']' && pop(&stack) != '[') ||
                (expr[i] == '}' && pop(&stack) != '{')) {
                printf("括号不匹配位置：%d\n", i + 1);
                return 0; // 括号不匹配
            }
        }
    }

    // 最终检查栈是否为空，以确保所有开括号都有闭括号匹配
    if (stack.top != -1) {
        printf("括号不匹配位置：%d\n", i + 1);
        return 0;
    }

    return 1;
}

// 判断是否包含括号的函数
bool containsParentheses(char expr[]) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == ')' || expr[i] == '[' || expr[i] == ']' || expr[i] == '{' || expr[i] == '}') {
            return true;
        }
    }
    return false;
}

int main() {
    char expression[100];

    while (1) {
        // 从用户输入获取表达式
        printf("请输入表达式 (输入 q 退出): ");
        fgets(expression, sizeof(expression), stdin);

        // 如果用户输入 'q'，退出循环
        if (expression[0] == 'q' && (expression[1] == '\n' || expression[1] == '\0')) {
            break;
        }

        // 判断是否包含括号
        if (!containsParentheses(expression)) {
            printf("输入非法：表达式必须包含括号\n");
            continue;
        }

        // 调用函数检查括号是否匹配
        if (areParenthesesBalanced(expression)) {
            printf("括号配对正确\n");
        } else {
            printf("括号配对不正确\n");
        }
    }

    return 0;
}
