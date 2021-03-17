#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define KEY_LENGHT 15
#define MESSAGE_LENGHT 500

//Middle Square Weyl Sequence Pseudorandom Number Generators (PRNG)
unsigned long msws() {
    unsigned long long x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;
    x *= x;
    x += (w += s);
    return x = (x>>32) | (x<<32);
}

//Membuat Key
void generateKey(int i, long long ntime, char *key){
    --i;
    ntime = (((ntime * msws()) % 93) + 33);
    key[i] = ntime;
    if(i >= 0){
        generateKey(i, ntime, key);
    }
}

//Konversi Key untuk Mengenkripsi atau Mendekripsi Message
int getKey(char key[KEY_LENGHT]){
    int getkey = 0;
    for(int i = 0; i < KEY_LENGHT; ++i){
        getkey += key[i];
    }
    return getkey;
}

//Mengenkripsi Message
void encryption(int *loop, char *key, char *message, int getKey, int i) {

    for(int shift = getKey * key[i], j = 0, k = strlen(message); j < k; ++j, ++shift){
        shift = (shift % 93) + 1;
        if((message[j]) + shift > '~') {
            message[j] = '!' + (shift - ('~' - message[j])) - 1;
        } else {
            message[j] += shift;
        }
    }
    *loop -= 1;
    if(*loop > 0){
        if(++i > 14)
            i = 0;
        encryption(loop, key, message, getKey, i);
    }
}

//Mendekripsi Message
void decryption(int *loop, char key[KEY_LENGHT], char *message, int getKey, int i) {
    for(int shift = getKey * key[i], j = 0, k = strlen(message); j < k; ++j, ++shift){
        shift = (shift % 93) + 1;
        if((message[j]) - shift < ' ') {
            message[j] = '~' - (shift - (message[j] - ' '));
        } else {
            message[j] -= shift;
        }
    }
    *loop -= 1;
    if(*loop > 0){
        if(++i > 14)
            i = 0;
        decryption(loop, key, message, getKey, i);
    }
}

//Antarmuka Awal Program
void head(){
    system("cls");
    for(int i=0; i < 28; ++i){
        printf("%c", 196);
    }
    printf("%c", 180);
    printf(" ADVANCE HDAVH MESSAGE ENCRYPTION ");
    printf("%c", 195);
    for(int i=0; i < 28; ++i){
        printf("%c", 196);
    }
    printf("\n\n");
}

//Antarmuka dan Subprogram untuk Mengenkripsi
void encrypt(){
    printf("Message:\n");
    char message[MESSAGE_LENGHT];
    scanf("%[^\n]", message);
    while(getchar() != '\n');
    time_t ntime = time(NULL);
    char key[KEY_LENGHT+1];
    generateKey(KEY_LENGHT, ntime, key);
    int loop = key[KEY_LENGHT - 1];
    head();
    printf("Encrypted Message:\n");
    encryption(&loop, key, message, getKey(key), 0);
    printf("%s\n\n", message);
    printf("Key: %s", key);
    printf("\n\n\n\n");
    printf("Note:\n");
    printf("1. Save the 15-digit key in separate place for security reason.\n");
    printf("2. Use the key to decrypt the encrypted message.\n");
}

//Antarmuka dan Subprogram untuk Mendekripsi
void decrypt(){
    printf("Encrypted Message:\n");
    char message[MESSAGE_LENGHT];
    scanf("%[^\n]", message);
    while(getchar() != '\n');
    printf("\n");
    printf("Key: ");
    char key[KEY_LENGHT+1]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    scanf("%s", key);
    while(getchar() != '\n');
    int loop = key[KEY_LENGHT - 1];
    head();
    printf("Message: \n");
    decryption(&loop, key, message, getKey(key), 0);
    printf("%s\n", message);
}

//Mengatur Ukuran Jendela Terminal/Command Prompt
void changeWindowSize() {
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 700, 500, TRUE);
}

int main() {
    changeWindowSize();
    char loop = 'N';
    do{
        head();
        printf("Encryption or Decription? [E/d] : ");
        char option = getchar();
        while(option != '\n'&& getchar() != '\n');
        printf("\n");
        head();
        if(option == 'd' || option == 'D') {
            decrypt();
        } else {
            encrypt();
        }
        printf("\n\n");
        printf("Loop? (y/N): ");
        loop = getchar();
        while(loop != '\n' && getchar() != '\n');
    } while(loop == 'y' || loop == 'Y');

    return 0;
}
