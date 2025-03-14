#include "myutils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Less number of arguments.\n");
        printf("./master InputFileName\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }

    // Please keep this function call in the main.
    // This function initializes "output" folder
    // by deleting the folder and all its files,
    // and then creating a clean "output" folder.
    bookeepingCode();

    // Parse input file
    FILE * fp;                                                      // File pointer
    char *line = (char *)malloc(sizeof(char) * LineBufferSize);         // Line buffer where a new line is stored
    size_t len = LineBufferSize;                                        // The size of the line buffer
    ssize_t nread;                                                  // Length of a new line read

    char inputFileName[MaxFileNameLength];
    memset(inputFileName, '\0', MaxFileNameLength);
    sprintf(inputFileName, "input/%s", argv[1]);

    if ((fp = getFilePointer(inputFileName)) == NULL) {             // Open a file and return file pointer to the file
        exit(EXIT_FAILURE);
    }

    // Read the number of data and depth
    int nData;
    int depth = 0;
    if((nread = getLineFromFile(fp, line, len)) != -1) {            // Read next line and write it to line buffer
        sscanf(line, "%d %d\n", &nData, &depth);
    }

    // Read degrees of each level
    int *degrees;
    if (depth > 0) {
        if((nread = getLineFromFile(fp, line, len)) != -1) {            // Read next line and write it to line buffer
           degrees = stringToIntArray(line, depth);
        } else {
            // TODO: handle failure
        }
    } else {
        // if depth is 0 there will be an empty line that needs to be consumed.
        getLineFromFile(fp, line, len);
    }

    // Read input data
    int * input = (int *)malloc(sizeof(int) * nData);
    int aNumber;
    int idxInput = 0;
    while((nread = getLineFromFile(fp, line, len)) != -1) {
        sscanf(line, "%d\n", &aNumber);
        input[idxInput++] = aNumber;
    }

    for (int i = 0; i < nData; i++) {
        printf("%d ", input[i]);
    }
    printf("\n");

    free(line);
    fclose(fp);

    /*
     * Each process is assigned floor(nData/degrees[current_depth])
     */

    // TODO: Spawn child processes and launch childProgram if necessary

    // TODO: Wait all child processes to terminate if necessary

    // TODO: Merge sort or Quick sort (or other leaf node sorting algorithm)


    free(input);
    free(degrees);

    return EXIT_SUCCESS;
}