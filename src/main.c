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
    char* commandCopy = strdup(command);
    if (commandCopy == NULL) {
        perror("Failed to allocate memory");
        return;
    }

    char* comment = strstr(commandCopy, "//");
    if (comment != NULL) {
        *comment = '\0';
    }

    size_t len = strlen(commandCopy);
    while (len > 0 && isspace(commandCopy[len - 1])) {
        commandCopy[len - 1] = '\0';
        len--;
    }

    if (strlen(commandCopy) == 0) {
        free(commandCopy);
        return;
    }

    if (strncmp(commandCopy, "BLZ:Respond=", 12) == 0) {
        const char* response = commandCopy + 12;

        printf("%s\n", response);
    } 
    else if (strncmp(commandCopy, "BLZ:Open=", 9) == 0) {
        const char* executablePath = commandCopy + 9;

        printf("Opening \"%s\"\n", executablePath);

        int result = system(executablePath);

        if (result == 0) {
            printf("Successfully launched: %s\n", executablePath);
        } else {
            printf("Failed to launch: %s\n", executablePath);
        }
    }
    else if (strcmp(commandCopy, "BLZ:BSOD") == 0) {
        printf("Executing BSOD command...\n");
        int result = BlueScreen();
        if (result == 0) {
            printf("BSOD executed successfully!\n");
        } else {
            printf("Failed to execute BSOD.\n");
        }
    }
    else if (strncmp(commandCopy, "BLZ:DLB=", 8) == 0) {
        const char* dialogue = commandCopy + 8;

        int msgboxID = MessageBox(NULL, dialogue, "Blitz Script Dialogue Box", MB_OK | MB_ICONINFORMATION);
        if (msgboxID == IDOK) {
            printf("User clicked OK\n");
        }
    }
    else {
        printf("Invalid Blitz Script command: %s\n", commandCopy);
    }

    free(commandCopy);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        getchar();
        return 1;
    }

    const char* inputFile = argv[1];
    const char* fileExtension = strrchr(inputFile, '.');

    if (fileExtension == NULL || strcmp(fileExtension, ".btz") != 0) {
        printf("Woah man, this isn't a blitz script file, make sure it's properly formatted - Blitz\n");
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
        processBlitzScriptCommand(line);
    }

    fclose(file);

    getchar();

    return 0;
}
