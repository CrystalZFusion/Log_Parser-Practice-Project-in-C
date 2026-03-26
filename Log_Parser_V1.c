#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    char fileName[100];
    char line[256];
    int errorCount = 0;
    time_t now;
    time(&now);
    char *timeStr = ctime(&now);
    timeStr[strlen(timeStr)-1] = '\0';

if (argc < 3) {
        printf("Usage: ./program <search_term>\n");
        return 1;
    }
    sprintf(fileName, "%s_results.txt", argv[2]);
    FILE *outputFile = fopen ( fileName, "w" );
    FILE *file = fopen(argv[1], "r");
if (file == NULL) {
        perror("Still can't find it\n");
    fclose(outputFile);
        return 1;
    }

    printf("--- LOG ERROR REPORT ---\n");

    while (fgets(line, sizeof(line), file) != NULL) {
        char *match = strstr(line, argv[2]);
        if (match != NULL) {
            char nextChar = match[strlen(argv[2])];
            if (nextChar == '\n' || nextChar == '\0' || nextChar == '\r' || nextChar == ' ') {
                printf("[CRITICAL]: %s\n", line);
            errorCount++;
                fprintf(outputFile, "[TIME]: %s [CRITICAL]: %s\n", timeStr, line);}
        }
    }
    fclose(outputFile);
    if (errorCount == 0) {
        printf("Warning: No matches found for '%s'. Check your spelling!\n", argv[2]);
        remove(fileName);
        printf("Empty result file '%s' has been removed.\n", fileName);
    }
    printf("TOTAL %s: %d\n", argv[2], errorCount);


    fclose(file);
    return 0;
}