#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Book Structure
typedef struct Book {
    int id;
    char title[100];
    char author[100];
    int category; // 1: Science, 2: History, 3: Magazine, 4: Poems, 5: References
    struct Book* next;
} Book;

Book* head = NULL;

// Function Declarations
void insertSampleBooks();
void displayAllBooksByCategory();
void guestMenu();
void readBookGuest();
void staffMenu();
void displayBooksByCategory(int category);
void showRentalMenu();
void manageCategoryBooks(int category);
void addBook(int category);
void searchBook(int category);
void displayCategoryBooks(int category);
void deleteBook(int category);
void readBookInCategory(int category);

// Helper for category name
const char* getCategoryName(int cat) {
    switch (cat) {
        case 1: return "Science";
        case 2: return "History";
        case 3: return "Magazine";
        case 4: return "Poems";
        case 5: return "References";
        default: return "Unknown";
    }
}

int main() {
    insertSampleBooks();
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("        LIBRARY MANAGEMENT SYSTEM       \n");
        printf("========================================\n");
        printf(" Please select your role:\n");
        printf(" [1] Staff\n");
        printf(" [2] Guest\n");
        printf(" [0] Exit\n");
        printf("----------------------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                staffMenu();
                break;
            case 2:
                guestMenu();
                break;
            case 0:
                printf("\nThank you for using the system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void staffMenu() {
    int choice;
    do {
        printf("\n========================================\n");
        printf("               STAFF MENU               \n");
        printf("========================================\n");
        printf(" [1] Add Book\n");
        printf(" [2] Search Book\n");
        printf(" [3] Display All Books\n");
        printf(" [4] Delete Book\n");
        printf(" [5] Read Book\n");
        printf(" [0] Back to Main Menu\n");
        printf("----------------------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 3:
                displayAllBooksByCategory();
                break;
            case 5:
                readBookGuest();
                break;
            case 0:
                break;
            default:
                printf("Functionality not implemented.\n");
        }
    } while (choice != 0);
}

void guestMenu() {
    int choice;
    do {
        printf("\n========================================\n");
        printf("               GUEST MENU               \n");
        printf("========================================\n");
        printf(" [1] Display All Books\n");
        printf(" [2] Read Book\n");
        printf(" [0] Back\n");
        printf("----------------------------------------\n");
        printf(" Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAllBooksByCategory();
                break;
            case 2:
                readBookGuest();
                break;
            case 0:
                break;
            default:
                printf("Invalid input. Try again.\n");
        }
    } while (choice != 0);
}

void displayAllBooksByCategory() {
    if (head == NULL) {
        printf("\nNo books available in the library.\n");
        return;
    }

    printf("\n+------------+----------+------------------------------+--------------------------+\n");
    printf("| Category   | Book ID  | Title                        | Author                   |\n");
    printf("+------------+----------+------------------------------+--------------------------+\n");

    for (int cat = 1; cat <= 5; cat++) {
        Book* temp = head;
        int first = 1;
        while (temp) {
            if (temp->category == cat) {
                if (first) {
                    printf("| %-10s |", getCategoryName(cat));
                    first = 0;
                } else {
                    printf("| %-10s |", "");
                }
                printf(" %-8d | %-28s | %-24s |\n", temp->id, temp->title, temp->author);
            }
            temp = temp->next;
        }
    }
    printf("+------------+----------+------------------------------+--------------------------+\n");
}

void readBookGuest() {
    int cat;
    printf("\nSelect a Book Category to Read:\n");
    printf(" [1] Science\n [2] History\n [3] Magazine\n [4] Poems\n [5] References\n [0] Back\n");
    printf("Enter your choice: ");
    scanf("%d", &cat);

    if (cat < 1 || cat > 5) return;

    manageCategoryBooks(cat);
}

void manageCategoryBooks(int category) {
    int choice;
    do {
        printf("\nManage %s Books:\n", getCategoryName(category));
        printf(" [1] Add Book\n");
        printf(" [2] Search Book\n");
        printf(" [3] Display All Books\n");
        printf(" [4] Delete Book\n");
        printf(" [5] Read Book\n");
        printf(" [0] Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(category);
                break;
            case 2:
                searchBook(category);
                break;
            case 3:
                displayCategoryBooks(category);
                break;
            case 4:
                deleteBook(category);
                break;
            case 5:
                readBookInCategory(category);
                break;
            case 0:
                break;
            default:
                printf("Invalid input.\n");
        }
    } while (choice != 0);
}

void displayCategoryBooks(int cat) {
    Book* temp = head;
    int found = 0;
    printf("\nAvailable Books in %s:\n", getCategoryName(cat));
    printf("+---------+------------------------------+------------------------------+\n");
    printf("| Book ID | Title                        | Author                       |\n");
    printf("+---------+------------------------------+------------------------------+\n");
    while (temp) {
        if (temp->category == cat) {
            printf("| %-7d | %-28s | %-28s |\n", temp->id, temp->title, temp->author);
            found = 1;
        }
        temp = temp->next;
    }
    printf("+---------+------------------------------+------------------------------+\n");
    if (!found) printf("No books found in this category.\n");
}

void readBookInCategory(int category) {
    int id;
    displayCategoryBooks(category);
    printf("Enter Book ID to read: ");
    scanf("%d", &id);
    // Optionally validate ID here
    showRentalMenu();
}

void showRentalMenu() {
    int option;
    printf("\n\x9D Rental Price List:\n");
    printf(" [1] 1–5 Days     = RM3\n");
    printf(" [2] 6–10 Days    = RM6\n");
    printf(" [3] 15 Days      = RM10\n");
    printf(" [4] 1 Month      = RM20\n");
    printf("Select rental duration (1-4): ");
    scanf("%d", &option);
    printf("You selected option %d\n", option);
}

void addBook(int category) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->category = category;
    printf("Enter Book ID: ");
    scanf("%d", &newBook->id);
    printf("Enter Title: ");
    scanf(" %[^\n]", newBook->title);
    printf("Enter Author: ");
    scanf(" %[^\n]", newBook->author);
    newBook->next = head;
    head = newBook;
    printf("Book added successfully!\n");
}

void searchBook(int category) {
    int id;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);
    Book* temp = head;
    while (temp) {
        if (temp->id == id && temp->category == category) {
            printf("Book Found: %s by %s\n", temp->title, temp->author);
            return;
        }
        temp = temp->next;
    }
    printf("Book not found in this category.\n");
}

void deleteBook(int category) {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    Book *temp = head, *prev = NULL;
    while (temp) {
        if (temp->id == id && temp->category == category) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            free(temp);
            printf("Book deleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Book not found in this category.\n");
}

void insertSampleBooks() {
    const char* titles[5][5] = {
        {"Physics Basics", "Chemistry World", "Biology Guide", "Astronomy Today", "Science Facts"},
        {"World History", "Ancient Civilizations", "Modern Wars", "Historical Heroes", "Empire Chronicles"},
        {"Tech Monthly", "Travel Explorer", "Health Digest", "Art Weekly", "Sports Central"},
        {"Love Poems", "Nature Verses", "Haiku Collection", "Romantic Lines", "Soul Words"},
        {"English Grammar", "Math Formulas", "Physics Handbook", "Programming in C", "Dictionary of Terms"}
    };
    const char* authors[5][5] = {
        {"Dr. Smith", "Prof. Allen", "Dr. Clark", "Dr. Lee", "Prof. Green"},
        {"Mr. Carter", "Ms. Brown", "Mr. Davis", "Dr. Baker", "Prof. Adams"},
        {"Editor A", "Editor B", "Editor C", "Editor D", "Editor E"},
        {"Poet One", "Poet Two", "Poet Three", "Poet Four", "Poet Five"},
        {"Mr. Lang", "Mr. Math", "Dr. Phys", "Mr. Code", "Ms. Lexi"}
    };

    int id = 100;
    for (int cat = 1; cat <= 5; cat++) {
        for (int i = 4; i >= 0; i--) {
            Book* newBook = (Book*)malloc(sizeof(Book));
            newBook->id = id++;
            strcpy(newBook->title, titles[cat - 1][i]);
            strcpy(newBook->author, authors[cat - 1][i]);
            newBook->category = cat;
            newBook->next = head;
            head = newBook;
        }
    }
}

