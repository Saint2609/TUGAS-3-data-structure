#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TABLE_SIZE 10

struct Node {
    char key[100];
    struct Node* next;
};

struct HashTable {
    char key[100];
    struct Node* chain;
} ht[TABLE_SIZE];

void initializationHT() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        strcpy(ht[i].key, "");
        ht[i].chain = NULL;
    }
}

int StoI(char key[]) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum;
}

int midSquareHash(char key[]) {
    int intKey = StoI(key);
    int square = intKey * intKey;
    int mid = (square / 100) % TABLE_SIZE;
    return mid;
}

int foldingHash(char key[]) {
    int intKey = StoI(key);
    int sum = 0;
    while (intKey > 0) {
        sum += intKey % 100;
        intKey /= 100;
    }
    return sum % TABLE_SIZE;
}

int digitExtractionHash(char key[]) {
    int intKey = StoI(key);
    return (intKey / 10) % TABLE_SIZE;
}

int rotatingHash(char key[]) {
    int intKey = StoI(key);
    return ((intKey << 4) | (intKey >> 4)) % TABLE_SIZE;
}

void linearProbing(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    int i = 0;
    while (strcmp(ht[(index + i) % TABLE_SIZE].key, "") != 0 && i < TABLE_SIZE) {
        i++;
    }
    if (i < TABLE_SIZE) {
        strcpy(ht[(index + i) % TABLE_SIZE].key, key);
        printf("Key %s inserted at index %d.\n", key, (index + i) % TABLE_SIZE);
    } else {
        printf("Table is full! Cannot insert key %s.\n", key);
    }
}

void chaining(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->next = ht[index].chain;
    ht[index].chain = newNode;
    printf("Key %s inserted at index %d using chaining.\n", key, index);
}

void displayHT() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: %s", i, strcmp(ht[i].key, "") == 0 ? "Kosong" : ht[i].key);
        struct Node* temp = ht[i].chain;
        while (temp) {
            printf(" -> %s", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    initializationHT();
    int choice, hashChoice;
    char key[100];
    int (*hashFunction)(char[]) = NULL;
    
    printf("Pilih metode hashing:\n");
    printf("1. Mid-Square\n2. Folding\n3. Digit Extraction\n4. Rotating Hash\n");
    scanf("%d", &hashChoice);
    switch (hashChoice) {
        case 1: hashFunction = midSquareHash; break;
        case 2: hashFunction = foldingHash; break;
        case 3: hashFunction = digitExtractionHash; break;
        case 4: hashFunction = rotatingHash; break;
        default: printf("Pilihan tidak valid!\n"); return 0;
    }
    
    printf("Pilih metode collision handling:\n");
    printf("1. Linear Probing\n2. Chaining\n");
    scanf("%d", &choice);
    
    while (1) {
        printf("Masukkan key (string) atau 'exit' untuk berhenti: ");
        scanf("%s", key);
        if (strcmp(key, "exit") == 0) break;
        
        if (choice == 1) {
            linearProbing(key, hashFunction);
        } else if (choice == 2) {
            chaining(key, hashFunction);
        } else {
            printf("Pilihan tidak valid!\n");
            break;
        }
    }
    
    displayHT();
    return 0;
}
