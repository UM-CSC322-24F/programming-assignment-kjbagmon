#include <stdio.h>
#include <stdlib.h>
#include "boat.h"

#define MAX_BOATS 120







void displayMenu() {
    printf("(I)nventory, (A)dd, (R)emove, (P)ayment, e(X)it:\n");
}

int main() {
    Boat *boats[MAX_BOATS];
    int boatCount = 0;
    char choice;
    char buffer[256];
    char boatName[128];
    float paymentAmount;

    loadBoatsFromFile("BoatData.csv", boats, &boatCount);

    while (1) {
        displayMenu();
        scanf(" %c", &choice);
        switch (choice) {
            case 'I':
            case 'i':
                printBoats(boats, boatCount);
                break;
            case 'A':
            case 'a':
                printf("Enter boat data (Name, Length, Type, Extra Info, Amount Owed): ");
                scanf(" %[^\n]", buffer);
                if (!addBoat(boats, &boatCount, buffer)) {
                    printf("Failed to add boat.\n");
                }
                break;
            case 'R':
            case 'r':
                printf("Enter the name of the boat to remove: ");
                scanf(" %[^\n]", boatName);
                if (removeBoat(boats, &boatCount, boatName)) {
                    printf("Boat removed successfully.\n");
                } else {
                    printf("Boat not found.\n");
                }
                break;
            case 'P':
            case 'p':
                printf("Enter the name of the boat for payment: ");
                scanf(" %[^\n]", boatName);
                printf("Enter the payment amount: ");
                scanf("%f", &paymentAmount);
                makePayment(boats, boatCount, boatName, paymentAmount);
                break;
            case 'X':
            case 'x':

		printf("Exiting the Boat Management System\n");
                for (int i = 0; i < boatCount; i++) {
                    free(boats[i]);
                }
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}













