#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define STARTING_ACCOUNT_NUMBER 1001  // Start account numbers from 1001

// Define the customer structure
typedef struct {
    int accountNumber;
    char name[50];
    double balance;
} Customer;

// Global array to store customers and count of current customers
Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

// Function prototypes
void displayMenu();
void createAccount();
void deposit();
void withdraw();
void balanceEnquiry();
int findAccountIndex(int accountNumber);

// Main menu
void displayMenu() {
    int choice;
    do {
        printf("\n=== Banking System Operations ===\n");
        printf("1. Open New Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: balanceEnquiry(); break;
            case 0: printf("Exiting the program.\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}

// Function to create a new account
void createAccount() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Customer limit reached. Cannot create a new account.\n");
        return;
    }

    Customer newCustomer;
    newCustomer.accountNumber = STARTING_ACCOUNT_NUMBER + customerCount;  // Assign a unique account number
    printf("Enter customer name: ");
    scanf(" %[^\n]", newCustomer.name);
    newCustomer.balance = 0.0;  // Initial balance is 0

    customers[customerCount++] = newCustomer;
    printf("Account created successfully! Account Number: %d\n", newCustomer.accountNumber);
}

// Function to deposit money into an account
void deposit() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    customers[index].balance += amount;
    printf("Deposit successful! New balance: %.2f\n", customers[index].balance);
}

// Function to withdraw money from an account
void withdraw() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    if (amount > customers[index].balance) {
        printf("Insufficient balance! Available balance: %.2f\n", customers[index].balance);
        return;
    }

    customers[index].balance -= amount;
    printf("Withdrawal successful! New balance: %.2f\n", customers[index].balance);
}

// Function to check the balance of an account
void balanceEnquiry() {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    int index = findAccountIndex(accountNumber);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Account Number: %d\n", customers[index].accountNumber);
    printf("Customer Name: %s\n", customers[index].name);
    printf("Available Balance: %.2f\n", customers[index].balance);
}

// Helper function to find the index of an account by account number
int findAccountIndex(int accountNumber) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1; // Account not found
}

// Main function
int main() {
    displayMenu();
    return 0;
}
