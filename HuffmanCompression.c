#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{
    int data;
    int power;              //huffman value of all child nodes summed up
    struct NODE* left;
    struct NODE* right;
}NODE;
typedef struct RESULT{
    char* compressedBin;    //when setting this value remember to use malloc
    NODE* tree;
}RESULT;

void createHeap(NODE* arr[] , int n);
void heapify(NODE* arr[], int i, int n);
NODE* popHeap(NODE* arr[], int* n);
NODE* buildHTree(NODE* arr[], int *n);
char* hEncode(char* str, NODE* root);
void findEncoding(NODE* root, char target,char* path,  int depth, char* result, int* found);
char* decode(RESULT* res);
char* decode(RESULT* result);



RESULT* compress(char* str){
        int ascii;
        NODE* charCount[128] = {NULL};
        
        for (int i = 0; str[i] != '\0'; i++){
        ascii = (int)str[i];
        if (charCount[ascii] == NULL && ascii<128){
            NODE* temp = (NODE*)malloc(sizeof(NODE));
            temp->data = ascii;
            temp->power = 1;
            temp->left = temp->right = NULL;
            charCount[ascii] = temp;
        }
        else if(charCount[ascii] != NULL){
            (charCount[ascii]->power)++;
        }
        else{
            printf("Unsupported Character Detected.\n");
        }
        }
        NODE* heapArr[128] = {NULL};
        int index = 0;
        for(int i = 0; i < 128; i++){
            if(charCount[i]!= NULL )
            {
                heapArr[index] =charCount[i];
                index++;
            }
    }
    createHeap(heapArr, index);
    NODE* root = buildHTree(heapArr, &index);
    RESULT* result = (RESULT*)malloc(sizeof(RESULT));
    result->tree = root;
    result->compressedBin = hEncode(str, root);
    return result;
}

void createHeap(NODE* arr[] , int n){
for (int i = n/2 - 1; i >= 0; i--){
    heapify(arr, i, n);
}
}

void heapify(NODE* arr[], int i, int n){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
if(arr[smallest] != NULL){

    if (left < n && arr[left] != NULL && arr[smallest]->power > arr[left]->power ){
        smallest = left;
    }
    if (right < n && arr[right] != NULL && arr[smallest]->power > arr[right]->power ){
        smallest = right;
    }
    
    if(smallest != i){
        NODE* temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        
        heapify(arr, smallest, n);
    }
}

}


NODE* popHeap(NODE* arr[], int* n){
    if(*n == 0 || arr[0] == NULL){
        printf("Empty heap passed to popHeap()");
        return arr[0];
    }

    
    NODE* temp = arr[0];
    arr[0] = arr[*n - 1];
    arr[*n - 1] = NULL;
    (*n)--;
    heapify(arr, 0, *n);
    return temp;


}

NODE* buildHTree(NODE* arr[], int *n){
    while(*n > 1){
        NODE* min1;
        NODE* min2;
        min1 = popHeap(arr, n);
        min2 = popHeap(arr, n);
        NODE* root = (NODE*)malloc(sizeof(NODE));
        root->left = min1;
        root->right = min2;
        root->data = -1;
        root->power = min1->power + min2->power;
        arr[*n] = root;
        (*n)++;
        heapify(arr, 0, *n);

    }
    return arr[0];
}

char* hEncode(char* str, NODE* root){
    char path[128];
    char* encoding = (char*)malloc(2048);
    encoding[0] = '\0';
    for(int i = 0; str[i] != '\0'; i++){
         int found = 0;
        char result[128];
        findEncoding(root, str[i], path, 0, result,&found );
        strcat(encoding, result);


    }
    
    return encoding;
}

void findEncoding(NODE* root, char target,char* path,  int depth, char* result, int* found){
    if(root == NULL || *found){
        return;
    }

    if(root->left == NULL && root->right == NULL && root->data == (int)target){
        path[depth] = '\0';
        strcpy(result, path);
        *found = 1;
        printf("%c: %s\n", target, result);
        return;
    }

    path[depth] = '0';
    findEncoding(root->left, target, path, depth + 1, result, found);

    path[depth] = '1';
findEncoding(root->right, target, path, depth + 1, result, found);
}


char* decode(RESULT* result){
    NODE* root = result->tree;
    NODE* curr = root;
    char* encoding = result->compressedBin;
    int len = strlen(encoding);     //can't use sizeof bc that gives pointer size not string. also sizeof includes \0
    char* finalStr = malloc(1024);
    int fIndex = 0;
    for(int i = 0; i < len; i++){
        if(encoding[i] == '0' && curr->left != NULL){
            curr = curr->left;
        }
        else if(encoding[i] == '1' && curr->right != NULL){
            curr = curr->right;
        }

        else{
           printf("Decode Error");
           return NULL; 
        }
            if(curr->left == NULL && curr->right == NULL){
            char ch = (char)(curr->data);
            finalStr[fIndex++] = ch;
            curr = root;
        }
    }
    finalStr[fIndex] = '\0';
    return finalStr;
}


int main(){
    printf("Enter Text to Compress: ");
    char str[100];
    fgets(str, sizeof(str), stdin); //scanf stops at space
    str[strcspn(str, "\n")] = '\0'; //fgets includes newline char thus strip it. Also strcspn second param is a char* type so use "  " not ' '
    RESULT* compressedResult = compress(str); 
    char* bin = compressedResult->compressedBin;
    printf("Final Compressed: %s\n", bin);
    printf("Decoded Message: %s\n", decode(compressedResult));
    return 0;
}