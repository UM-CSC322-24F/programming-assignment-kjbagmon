#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boat.h"


int compareBoats(const void *a, const void *b) {
    Boat *boatA = *(Boat **)a;
    Boat *boatB = *(Boat **)b;
    return strcmp(boatA->name, boatB->name);
}

bool addBoat(Boat **boats, int *boatCount, const char *data) {
    if (*boatCount >= 120) return false;

    Boat *newBoat = malloc(sizeof(Boat));
    if (!newBoat) return false;

    char type[10];
    sscanf(data, "%127[^,],%f,%9[^,],%[^,],%f", newBoat->name, &newBoat->length, type, newBoat->extra.trailerTag, &newBoat->amountOwed);

    if (strcmp(type, "slip") == 0) {
        newBoat->boats = SLIP;
        sscanf(newBoat->extra.trailerTag, "%d", &newBoat->extra.slipNumber);
    } else if (strcmp(type, "land") == 0) {
        newBoat->boats = LAND;
        newBoat->extra.bayLetter = newBoat->extra.trailerTag[0];
    } else if (strcmp(type, "trailer") == 0) {  
        newBoat->boats = TRAILOR;
        strncpy(newBoat->extra.trailerTag, newBoat->extra.trailerTag, sizeof(newBoat->extra.trailerTag) - 1);
        newBoat->extra.trailerTag[sizeof(newBoat->extra.trailerTag) - 1] = '\0';
    } else if (strcmp(type, "storage") == 0) {
        newBoat->boats = STORAGE;
        sscanf(newBoat->extra.trailerTag, "%d", &newBoat->extra.storageNumber);
    }

    boats[*boatCount] = newBoat;
    (*boatCount)++;
    return true; 
}

void printBoats(Boat **boats, int boatCount) {

    qsort(boats, boatCount, sizeof(Boat *), compareBoats);

    for (int i = 0; i < boatCount; i++) {
        printf("%-20s %-5.1f ", boats[i]->name, boats[i]->length);
        switch (boats[i]->boats) {
            case SLIP:
                printf("Slip %d", boats[i]->extra.slipNumber);
                break;
            case LAND:
                printf("Land, Bay %c", boats[i]->extra.bayLetter);
                break;
            case TRAILOR:
                printf("Trailer, Tag %s", boats[i]->extra.trailerTag);
                break;
            case STORAGE:
                printf("Storage, Space %d", boats[i]->extra.storageNumber);
                break;
        }
        printf(" Owes $%.2f\n", boats[i]->amountOwed);
    }
}

bool removeBoat(Boat **boats, int *boatCount, const char *boatName) {
    for (int i = 0; i < *boatCount; i++) {
        if (strcmp(boats[i]->name, boatName) == 0) {
            free(boats[i]);
            for (int j = i; j < *boatCount - 1; j++) {
                boats[j] = boats[j + 1];
            }
            (*boatCount)--;
            return true;
        }
    }
    return false;
}

void makePayment(Boat **boats, int boatCount, const char *boatName, float amount) {
    for (int i = 0; i < boatCount; i++) {
        if (strcmp(boats[i]->name, boatName) == 0) {
            boats[i]->amountOwed -= amount;
            if (boats[i]->amountOwed < 0) boats[i]->amountOwed = 0; // Prevent negative amounts
            return;
        }
    }
}
