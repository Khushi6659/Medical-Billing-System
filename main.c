#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEDICINES 50
#define MAX_NAME_LENGTH 50

// Structure to represent a medicine
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Medicine;

// Predefined list of medicines with prices
Medicine predefinedMedicines[] = {
    {"Paracetamol", 2.50, 100},
    {"Aspirin", 1.75, 50},
    {"Antibiotic", 5.20, 200},
    {"Cough Syrup", 3.40, 150},
    {"Adderall" ,5.35,0},
    {"Ativan",4.50,0},
    // Add more medicines here if needed
};
int numPredefinedMedicines = sizeof(predefinedMedicines) / sizeof(predefinedMedicines[0]);

// Function to calculate the total amount for a medicine
float calculateMedicineTotal(Medicine med) {
    return med.price * med.quantity;
}

int main() {
    Medicine userMedicines[MAX_MEDICINES];
    int numUserMedicines = 0;
    char choice;
    float discount = 0.0;
    char cardUserID[50];
    char cardUserName[50];
    float specialOffer = 0.0;
    char paymentMethod[20];
    char cardNumber[20];
    char cardPin[10];

    printf("Welcome to the Medical Billing System\n");

    // Check if the customer has a health card
    printf("\nDo you have a health card? (yes/no): ");
    char healthCardChoice[5];
    scanf("%s", healthCardChoice);

    if (strcmp(healthCardChoice, "yes") == 0) {
        printf("Enter health card user ID: ");
        scanf("%s", cardUserID);
        printf("Enter health card user name: ");
        scanf("%s", cardUserName);
        discount = 10.0; // Fixed discount for health card users
    }

    // Input special offer
    printf("\nEnter special offer percentage (if any, otherwise enter 0): ");
    scanf("%f", &specialOffer);

    // Main billing loop
    do {
        // Input medicine name
        printf("\nEnter Medicine Name: ");
        scanf("%s", userMedicines[numUserMedicines].name);

        // Search for medicine in the predefined list
        int found = 0;
        for (int i = 0; i < numPredefinedMedicines; i++) {
            if (strcmp(userMedicines[numUserMedicines].name, predefinedMedicines[i].name) == 0) {
                userMedicines[numUserMedicines].price = predefinedMedicines[i].price;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Sorry, %s is out of stock.\n", userMedicines[numUserMedicines].name);
            continue;
        }

        // Input quantity
        printf("Enter Quantity: ");
        scanf("%d", &userMedicines[numUserMedicines].quantity);

        // Increment the number of medicines
        numUserMedicines++;

        // Ask if the user wants to add more medicines
        printf("\nDo you want to add more medicines? (y/n): ");
        scanf(" %c", &choice);

    } while ((choice == 'y' || choice == 'Y') && numUserMedicines < MAX_MEDICINES);

    // Display the bill
    printf("\n\n========== Bill ==========\n");
    printf("Medicine Name\tQuantity\tPrice\tTotal\n");
    float totalAmount = 0;
    for (int i = 0; i < numUserMedicines; i++) {
        float medicineTotal = calculateMedicineTotal(userMedicines[i]);
        totalAmount += medicineTotal;
        printf("%s\t\t%d\t\t%.2f\t%.2f\n", userMedicines[i].name, userMedicines[i].quantity, userMedicines[i].price, medicineTotal);
    }

    // Apply discount
    totalAmount -= (totalAmount * (discount + specialOffer) / 100);

    printf("\nDiscount Applied: %.2f%%\n", discount + specialOffer);
    printf("Special Offer: %.2f%%\n", specialOffer);
    printf("Total Amount after Discount and Special Offer: %.2f\n", totalAmount);

    printf("===========================\n");

    // Payment
    printf("\nSelect Payment Method (cash/credit/debit): ");
    scanf("%s", paymentMethod);

    if (strcmp(paymentMethod, "credit") == 0 || strcmp(paymentMethod, "debit") == 0) {
        printf("Enter %s card number: ", paymentMethod);
        scanf("%s", cardNumber);
        printf("Enter %s card PIN: ", paymentMethod);
        scanf("%s", cardPin);
    }

    printf("\nThank you for using the Medical Billing System!\n");

    return 0;
}

