#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boat.h"

void loadBoatsFromFile(const char *filename, Boat **boats, int *boatCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) && *boatCount < 120) {
        if (!addBoat(boats, boatCount, buffer)) {
            printf("Failed to add boat\n");
        }
    }

    fclose(file);
}

void printBoatDetails(Boat **boats, int boatCount) {
    for (int i = 0; i < boatCount; i++) {
        printf("%s, %s, %.2f, %.2f\n",
            boats[i]->name,
            boats[i]->boats == SLIP ? boats[i]->extra.slipNumber : boats[i]->extra.bayLetter,
            boats[i]->amountOwed);
    }
}

