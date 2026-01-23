#include<stdio.h>

void reverse(char *str){


    int length = 0;
    char *temp = str;
    while (*temp) {
        temp++;
        length++;
    }

    for(int i=0; i<length; i++){
        temp[length - 1 - i] = str[i];
    }
    str = temp;
    //str = "!dlroW olleH"
    //LENGTH = 13

    int start = 0;
    for (int i = 0; i <= length; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            int end = i - 1;
            for (int j = start, k = end; j < k; j++, k--) {
                char temp = str[j];
                str[j] = str[k];
                str[k] = temp;
                
            }
            start = i + 1;
        }
        printf("%s", temp);
        printf("\n");

    }


    printf("%s", temp);
}

int main() {

    char str[] = "Hello World!";
    reverse(str);
}