#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义哈夫曼树节点
typedef struct Node {
    char data;
    int freq;
    struct Node *left, *right;
} Node;

// 定义哈夫曼编码表
typedef struct Code {
    char character;
    char code[256];
} Code;

// 统计字符频率
void countFrequency(char *input, int *freq) {
    while (*input) {
        freq[(unsigned char)(*input)]++;
        input++;
    }
}

// 构建哈夫曼树
Node* buildHuffmanTree(int *freq) {
    // 创建叶子节点
    Node *leaves[256];
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            leaves[i] = malloc(sizeof(Node));
            leaves[i]->data = (char)i;
            leaves[i]->freq = freq[i];
            leaves[i]->left = leaves[i]->right = NULL;
        } else {
            leaves[i] = NULL;
        }
    }

    // 构建哈夫曼树
    while (1) {
        int min1 = -1, min2 = -1;
        for (int i = 0; i < 256; i++) {
            if (leaves[i] != NULL) {
                if (min1 == -1 || leaves[i]->freq < leaves[min1]->freq) {
                    min2 = min1;
                    min1 = i;
                } else if (min2 == -1 || leaves[i]->freq < leaves[min2]->freq) {
                    min2 = i;
                }
            }
        }

        if (min2 == -1) {
            // 只剩下一个根节点，哈夫曼树构建完成
            return leaves[min1];
        }

        // 创建新的节点，作为两个最小频率节点的父节点
        Node *newNode = malloc(sizeof(Node));
        newNode->data = 0;  // 非叶子节点没有数据域
        newNode->freq = leaves[min1]->freq + leaves[min2]->freq;
        newNode->left = leaves[min1];
        newNode->right = leaves[min2];

        leaves[min1] = newNode;
        leaves[min2] = NULL;
    }
}

// 生成哈夫曼编码表
void generateHuffmanCodeTable(Node *root, Code *codeTable, char *currentCode, int depth) {
    if (root->left == NULL && root->right == NULL) {
        // 叶子节点，保存编码
        codeTable[(unsigned char)root->data].character = root->data;
        strcpy(codeTable[(unsigned char)root->data].code, currentCode);
        return;
    }

    // 遍历左子树
    currentCode[depth] = '0';
    currentCode[depth + 1] = '\0';  // 更新编码
    generateHuffmanCodeTable(root->left, codeTable, currentCode, depth + 1);

    // 遍历右子树
    currentCode[depth] = '1';
    currentCode[depth + 1] = '\0';  // 更新编码
    generateHuffmanCodeTable(root->right, codeTable, currentCode, depth + 1);
}

// 编码
void encode(char *input, Code *codeTable, char *output) {
    while (*input) {
        strcat(output, codeTable[(unsigned char)(*input)].code);
        input++;
    }
}

// 译码
void decode(char *input, Node *root, char *output) {
    Node *currentNode = root;
    while (*input) {
        if (*input == '0') {
            currentNode = currentNode->left;
        } else if (*input == '1') {
            currentNode = currentNode->right;
        }

        if (currentNode->left == NULL && currentNode->right == NULL) {
            // 叶子节点，找到一个字符
            *output = currentNode->data;
            output++;
            currentNode = root;  // 重置为根节点
        }

        input++;
    }
    *output = '\0';  // 结尾
}

int main() {
    char input[1000];
    printf("请输入文本：\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // 移除换行符

    int freq[256] = {0};
    countFrequency(input, freq);

    Node *root = buildHuffmanTree(freq);

    Code codeTable[256];
    char currentCode[256] = "";  // 初始编码为空

    generateHuffmanCodeTable(root, codeTable, currentCode, 0);

    printf("字符\t频率\t编码\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("%c\t%d\t%s\n", (char)i, freq[i], codeTable[i].code);
        }
    }

    char encoded[1000] = "";
    encode(input, codeTable, encoded);
    printf("\n编码结果：%s\n", encoded);

    char decoded[1000] = "";
    decode(encoded, root, decoded);
    printf("译码结果：%s\n", decoded);

    return 0;
}
