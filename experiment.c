#include <stdio.h>
#include <string.h>

// 定义图书信息的结构体
struct Book {
    char number[15]; // 书号
    char name[100];  // 书名
    float price;     // 价格
};

// 函数用于交换两本书的信息
void swap(struct Book *a, struct Book *b) {
    struct Book temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    // 初始化一个图书信息表
    struct Book book_table[100];
    int book_count = 0;
    float total_price = 0.0; // 移动到此处

    // 读入图书信息，直到遇到输入结束标志
    while (1) {
        // 读取一行输入
        char input[128];
        fgets(input, sizeof(input), stdin);

        // 检查是否为输入结束标志
        if (strcmp(input, "0 0 0\n") == 0) {
            break;
        }

        // 解析书号、书名和价格
        sscanf(input, "%s %s %f", book_table[book_count].number, book_table[book_count].name, &book_table[book_count].price);

        // 增加图书计数
        book_count++;
    }

    int choice;
    printf("请选择功能 (1: 输出图书数量, 2: 按价格降序排序, 3: 修改价格): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // 输出图书个数
            printf("图书数量: %d\n", book_count);
            for (int i = 0; i < book_count; i++) {
                printf("%s %s %.2f\n", book_table[i].number, book_table[i].name, book_table[i].price);
            }
            break;

        case 2:
            // 使用冒泡排序按价格降序排列图书信息
            for (int i = 0; i < book_count - 1; i++) {
                for (int j = 0; j < book_count - i - 1; j++) {
                    if (book_table[j].price < book_table[j + 1].price) {
                        swap(&book_table[j], &book_table[j + 1]);
                    }
                }
            }

            // 输出排序后的图书信息
            for (int i = 0; i < book_count; i++) {
                printf("%s %s %.2f\n", book_table[i].number, book_table[i].name, book_table[i].price);
            }
            break;

        case 3:
            // 计算所有图书的平均价格
            for (int i = 0; i < book_count; i++) {
                total_price += book_table[i].price;
            }
            float average_price = total_price / book_count;

            // 输出平均价格
            printf("平均价格: %.2f\n", average_price);

            // 修改图书价格并逐行输出价格修改后的图书信息
            for (int i = 0; i < book_count; i++) {
                if (book_table[i].price < average_price) {
                    book_table[i].price *= 1.2; // 价格低于平均价格，提高20%
                } else {
                    book_table[i].price *= 1.1; // 价格高于或等于平均价格，提高10%
                }
                printf("%s %s %.2f\n", book_table[i].number, book_table[i].name, book_table[i].price);
            }
            break;

        default:
            printf("无效的选择\n");
            break;
    }

    return 0;
}
