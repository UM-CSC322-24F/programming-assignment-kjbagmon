#ifndef BOAT_H
#define BOAT_H

#include <stdbool.h>

typedef enum {
    SLIP,
    LAND,
    TRAILOR,
    STORAGE
} BoatType;

typedef struct {
    int slipNumber;
    char bayLetter;
    char trailerTag[10];
    int storageNumber;
} ExtraInfo;

typedef struct {
    char name[128];
    float length;
    BoatType boats;
    ExtraInfo extra;
    float amountOwed;
} Boat;

bool addBoat(Boat **boats, int *boatCount, const char *data);
void printBoats(Boat **boats, int boatCount);
void loadBoatsFromFile(const char *filename, Boat **boats, int *boatCount);

bool removeBoat(Boat **boats, int *boatCount, const char *boatName);
void makePayment(Boat **boats, int boatCount, const char *boatName, float amount);

#endif // BOAT_H

