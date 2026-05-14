// main.c
#include <stdio.h>
#include <string.h>

#define FILE_NAME "passwords.dat"
#define KEY 123

typedef struct {
    char site[50];
    char username[50];
    char password[50];
} Entry;

void encryptDecrypt(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] ^= KEY;
    }
}

void addPassword() {
    FILE *f = fopen(FILE_NAME, "ab");
    Entry e;

    printf("Website: ");
    scanf("%49s", e.site);

    printf("Username: ");
    scanf("%49s", e.username);

    printf("Password: ");
    scanf("%49s", e.password);

    encryptDecrypt(e.password);

    fwrite(&e, sizeof(Entry), 1, f);
    fclose(f);

    printf("Saved.\n");
}

void listPasswords() {
    FILE *f = fopen(FILE_NAME, "rb");

    if (!f) {
        printf("No passwords stored.\n");
        return;
    }

    Entry e;

    while (fread(&e, sizeof(Entry), 1, f)) {
        encryptDecrypt(e.password);

        printf("\nSite: %s\n", e.site);
        printf("Username: %s\n", e.username);
        printf("Password: %s\n", e.password);

        encryptDecrypt(e.password);
    }

    fclose(f);
}

int main() {
    int choice;

    do {
        printf("\n=== Password Manager ===\n");
        printf("1. Add password\n");
        printf("2. List passwords\n");
        printf("0. Exit\n");
        printf("Choice: ");

        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addPassword();
                break;
            case 2:
                listPasswords();
                break;
            case 0:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid option.\n");
        }

    } while(choice != 0);

    return 0;
}