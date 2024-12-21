#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} DynamicArray;

void initArray(DynamicArray* arr) {
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void resizeArray(DynamicArray* arr, int newCapacity) {
    int* newData = (int*)realloc(arr->data, newCapacity * sizeof(int));
    if (newData == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Or handle the error in a more sophisticated way
    }
    arr->data = newData;
    arr->capacity = newCapacity;
}

void insertArray(DynamicArray* arr, int value, int index) {
    assert(index >= 0 && index <= arr->size);  //Basic assertion

    if (arr->size == arr->capacity) {
        int newCapacity = arr->capacity == 0 ? 1 : arr->capacity * 2;
        resizeArray(arr, newCapacity);
    }

    //Shift elements to make space
    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = value;
    arr->size++;
}

void deleteArray(DynamicArray* arr, int index) {
    assert(isValidIndex(arr,index));

    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
}

int getArray(const DynamicArray* arr, int index) {
    assert(isValidIndex(arr, index));
    return arr->data[index];
}

int sizeArray(const DynamicArray* arr) {
    return arr->size;
}

void freeArray(DynamicArray* arr) {
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}


void printArray(const DynamicArray* arr) {
    printf("[");
    for (int i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i < arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


bool isValidIndex(const DynamicArray* arr, int index) {
    return index >= 0 && index < arr->size;
}


int main() {
    DynamicArray arr;

    initArray(&arr);
    printf("Initialized array: size = %d, capacity = %d, data = %p\n", arr.size, arr.capacity, arr.data);

    insertArray(&arr, 10, 0);
    printf("Array after inserting 10: ");
    printArray(&arr);

    DynamicArray arr2;
    initArray(&arr2);
    insertArray(&arr2, 10, 0);
    insertArray(&arr2, 20, 1);
    deleteArray(&arr2, 0);
    printf("Array after deleting element at index 0: ");
    printArray(&arr2);

    DynamicArray arr3;
    initArray(&arr3);
    insertArray(&arr3, 5, 0);
    int value = getArray(&arr3, 0);
    printf("Value at index 0: %d\n", value);

    DynamicArray arr4;
    initArray(&arr4);
    insertArray(&arr4, 1, 0);
    insertArray(&arr4, 2, 1);
    int size = sizeArray(&arr4);
    printf("Size of the array: %d\n", size);

    freeArray(&arr);
    freeArray(&arr2);
    freeArray(&arr3);
    freeArray(&arr4);
    printf("Memory freed.\n");

    return 0;
}



