#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <Ntstatus.h>

int BlueScreen()
{
    BOOLEAN bl;
    LONG Response;

    if (RtlAdjustPrivilege(19, TRUE, FALSE, &bl) == 0)
    {
        NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response);
    }

    return 0;
}

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
    else if (strcmp(command, "BLZ:BSOD") == 0) {
        printf("Executing BSOD command...\n");
        int result = BlueScreen();
        if (result == 0) {
            printf("BSOD executed successfully!\n");
        } else {
            printf("Failed to execute BSOD.\n");
        }
    }
    else {
        printf("Invalid Blitz Script command: %s\n", command);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Yo! Make sure to drag and drop a .btz file for this to actually work! - Blitz", argv[0]);
        getchar();
        return 1;
    }

    const char* inputFile = argv[1];
    const char* fileExtension = strrchr(inputFile, '.');

    if (fileExtension == NULL) {
        printf("Woah man, this isn't a blitz script file, make sure it's properly formatted - Blitz\n");
        getchar();
        return 1;
    }
    
    if (strcmp(fileExtension, ".btz") != 0) {
        if (strcmp(fileExtension, ".1340") == 0) {
            printf("Abdu stop tryna run your own file lol - Blitz\n");
        } else {
            printf("Woah man, this isn't a blitz script file, make sure it's properly formatted - Blitz\n");
        }
        getchar();
        return 1;
    }

    SetConsoleTitle("Blitz Script Interpreter");

    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    mode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
    SetConsoleMode(hInput, mode);

    FILE* file = fopen(inputFile, "r");

    if (file == NULL) {
        perror("Failed to open file");
        getchar();
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
