#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/**
    v.2
    2023-06-23 -
    -
**/

int is_int_in_array(int value, int array[], int arraySize) {
    // Check if a value is in an array.

    int arrayLength = arraySize / sizeof(array[0]); // Calculate the length of the array
    int i; // Loop variable

    for (i = 0; i < arrayLength; i++) {
        if (value == array[i]) {
            return 1; // Value is found in the array, return 1
        }
    }

    return 0; // Value is not found in the array, return 0
}


int is_input_expected(void *data, void *array, int dataType) {
   // Check if input is not an int

   switch (dataType) {
       case 1:
            if (scanf("%d", &action) != 1) {
            printf("\nInvalid input. Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue; // Restart the loop
        }
        break;


   }


}



int start_screen() {
    // Allow user to choose between logging in or creating a new account.

    // Define variables
    int userAction = 0; // User's chosen action
    int possibleActions[] = {1, 2}; // Array of possible actions
    printf("==== Welcome to The Bank ====\n");

    while(1) {
        // Display available choices
        printf("Enter the number for the corresponding action.\n");
        printf("1 Log in to existing account\n2 Create new account\n");
        printf("> ");

        // Check if input is not an int
        if (scanf("%d", &userAction) != 1) {
            printf("\nInvalid input. Try again.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue; // Restart the loop
        }
        printf("\n");

        // Check if chosen action is allowed
        int isActionAllowed = is_int_in_array(userAction, possibleActions, sizeof(possibleActions));

        if (isActionAllowed == 1) {
            break; // Action is allowed, exit the loop
        }
        else {
            printf("\nInvalid input. Try again.\n"); // Action is not allowed, prompt the user to try again

        }
    }

    return userAction; // Return the selected action
}


int create_file(char folderPath[20], char fName[20]) {
    // Create a new account file

    FILE *newFile; // File pointer

    enum {
        FILE_CREATED,
        FILE_NAME_TAKEN,
        CREATING_FILE_FAILED,
        PATH_NOT_DIR,
        DIR_NOT_FOUND
    };

    // Test for folder
    struct stat st;
    int dirStatus = stat(folderPath, &st);

    if (dirStatus == -1) {
        return DIR_NOT_FOUND; // Folder not found
    } else {
        if (!S_ISDIR(st.st_mode)) {
            return PATH_NOT_DIR; // Path is not a directory
        }
    }

    char fPath[100];
    snprintf(fPath, sizeof(fPath), "%s/%s", folderPath, fName); // Create full file path

    newFile = fopen(fPath, "r");

    // File already exists
    if (newFile != NULL) {
        fclose(newFile);
        return FILE_NAME_TAKEN; // File name is already taken
    }

    // Create file
    newFile = fopen(fPath, "w");

    // File creation failed
    if (newFile == NULL) {
        return CREATING_FILE_FAILED; // File creation failed
    }

    fclose(newFile);
    return FILE_CREATED; // File created successfully
}


void create_account() {
     // Creates a new account file

    // Variable declaration
    const int NAME_SIZE = 20;
    const char dir[] = "account_files";

    char acntName[NAME_SIZE];     // Account name
    char file[NAME_SIZE + 4];     // File name (account name + ".txt")
    char filePath[100];           // File path

    enum {
        HAS_NOT_RUN = -1,
        FILE_CREATED,
        FILE_NAME_TAKEN,
    };
    int fCreationRes = HAS_NOT_RUN;    // File creation result

    printf("Enter the account username. Max 20 characters are allowed.\n");
    printf("If you want to go back enter '1'.\n> ");

    getchar();
    fgets(acntName, sizeof(acntName), stdin);
    acntName[strcspn(acntName, "\n")] = '\0';  // Remove buggy newline character

    // Name confirmation
    printf("Is the username %s correct? Enter Y/n for yes and no respectivley.\n> ", acntName);
    scanf("%c", );




    sprintf(file, "%s.txt", acntName);     // Merge account name with ".txt" to form file name
    fCreationRes = create_file(dir, file); // Create file
    sprintf(filePath, "%s/%s", dir, file); // Merge directory path with file name

    switch (fCreationRes) {
        case FILE_CREATED:
            printf("An account named %s was created.\n", acntName);

            FILE *newFile = fopen(filePath, "a");
            fprintf(newFile, "info\n");  // Write to file
            break;

        case FILE_NAME_TAKEN:
            printf("Error: account %s already exists.\n", acntName);
            break;

        default:
            printf("Error:: creating account failed. Error code %s\n", fCreationRes);
    }

    return;
}


int log_in() {
}


int main() {
    // Define variables
    enum {
        LOG_IN = 1,
        CREATE_ACCOUNT = 2
    };

    int startScreenChoice;

    // Logic start
    startScreenChoice = start_screen();
    switch (startScreenChoice) {
        case LOG_IN:
            printf("Logging in...");

            break;

        case CREATE_ACCOUNT:
            create_account();

            break;
    }

    return 0;
}
