#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义图书信息的结构体
struct Book {
    char number[15]; // 书号
    char name[100];  // 书名
    float price;     // 价格
    struct Book *next; // 指向下一本书的指针
};

// 函数用于交换两本书的信息
void swap(struct Book *a, struct Book *b) {
    struct Book temp = *a;
    temp.next = a->next; // 保持原有的next指针不变
    *a = *b;
    a->next = temp.next; // 恢复a的next指针
    *b = temp;
    b->next = a->next; // 设置b的next指针指向a的下一本书
}

// 释放链表内存
void freeList(struct Book *head) {
    struct Book *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    // 初始化一个图书链表
    struct Book *head = NULL, *tail = NULL, *new_book = NULL;
    int book_count = 0;
    float total_price = 0.0;

    // 读入图书信息，直到遇到输入结束标志
    while (1) {
        // 读取一行输入
        char input[128];
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // 检查是否为输入结束标志
        if (strcmp(input, "0 0 0\n") == 0) {
            break;
        }

        // 创建新的图书节点
        new_book = (struct Book *)malloc(sizeof(struct Book));
        if (new_book == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            freeList(head);
            return 1;
        }

        // 解析书号、书名和价格
        sscanf(input, "%s %s %f", new_book->number, new_book->name, &new_book->price);
        new_book->next = NULL;

        // 将新节点添加到链表末尾
        if (tail) {
            tail->next = new_book;
        } else {
            head = new_book;
        }
        tail = new_book;

        // 增加图书计数
        book_count++;
    }

    int choice;
    printf("请选择功能 (1: 输出图书数量, 2: 按价格降序排序, 3: 修改价格): ");
    scanf("%d", &choice);
    getchar(); // 消耗掉输入流中的换行符

    struct Book *current, *index;
    switch (choice) {
        case 1:
        {
            // 输出图书个数
            printf("图书数量: %d\n", book_count);
            for (current = head; current != NULL; current = current->next) {
                printf("%s %s %.2f\n", current->number, current->name, current->price);
            }
            break;
        }

        case 2:
        {
            // 使用冒泡排序按价格降序排列图书信息
            for (current = head; current != NULL; current = current->next) {
                for (index = current->next; index != NULL; index = index->next) {
                    if (current->price < index->price) {
                        swap(current, index);
                    }
                }
            }

            // 输出排序后的图书信息
            for (current = head; current != NULL; current = current->next) {
                printf("%s %s %.2f\n", current->number, current->name, current->price);
            }
            break;
        }

        case 3:
        {
            // 计算所有图书的平均价格
            for (current = head; current != NULL; current = current->next) {
                total_price += current->price;
            }
            float average_price = total_price / book_count;

            // 输出平均价格
            printf("平均价格: %.2f\n", average_price);

            // 修改图书价格并逐行输出价格修改后的图书信息
            for (current = head; current != NULL; current = current->next) {
                if (current->price < average_price) {
                    current->price *= 1.2; // 价格低于平均价格，提高20%
                } else {
                    current->price *= 1.1; // 价格高于或等于平均价格，提高10%
                }
                printf("%s %s %.2f\n", current->number, current->name, current->price);
            }
            break;
        }

        default:
        {
            printf("无效的选择\n");
            break;
        }
    }

    // 释放链表内存
    freeList(head);

    return 0;
}
