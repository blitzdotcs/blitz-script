#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

void processBlitzScriptCommand(const char* command) {
    if (strncmp(command, "BLZ:Respond=", 12) == 0) {
        const char* response = command + 12;

        printf("%s\n", response);
    } 
    else if (strncmp(command, "BLZ:Open=", 9) == 0) {
        const char* executablePath = command + 9;

        printf("Opening \"%s\"\n", executablePath);

        int result = system(executablePath);

        if (result == 0) {
            printf("Successfully launched: %s\n", executablePath);
        } else {
            printf("Failed to launch: %s\n", executablePath);
        }
    }
    else {
        printf("Invalid Blitz Script command: %s\n", command);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file.btz>\n", argv[0]);
        return 1;
    }

    SetConsoleTitle("Blitz Script Interpreter");

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    mode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
    SetConsoleMode(hInput, mode);

    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        processBlitzScriptCommand(line);
    }

    fclose(file);

    getchar();

    return 0;
}
