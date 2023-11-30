#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an event
typedef struct Event {
    char date[12];   // Date in format YYYY-MM-DD
    char description[100];
} Event;

// Function to add an event to the calendar
void addEvent(Event *calendar, int *eventCount) {
    if (*eventCount >= 100) {
        printf("Calendar is full. Cannot add more events.\n");
        return;
    }

    Event newEvent;
    printf("Enter event date (YYYY-MM-DD): ");
    scanf("%s", newEvent.date);
    printf("Enter event description: ");
    getchar();  // Consume newline left in the buffer
    fgets(newEvent.description, sizeof(newEvent.description), stdin);

    calendar[*eventCount] = newEvent;
    (*eventCount)++;
    printf("Event added successfully!\n");
}

// Function to view events for a specific date
void viewEvents(Event *calendar, int eventCount, char *date) {
    printf("Events for %s:\n", date);
    for (int i = 0; i < eventCount; i++) {
        if (strcmp(calendar[i].date, date) == 0) {
            printf("- %s", calendar[i].description);
        }
    }
    printf("\n");
}

// Function to view all events
void viewAllEvents(Event *calendar, int eventCount) {
    printf("All Events:\n");
    for (int i = 0; i < eventCount; i++) {
        printf("Date: %s\n", calendar[i].date);
        printf("Description: %s", calendar[i].description);
    }
    printf("\n");
}

// Function to save events to a text file
void saveEventsToFile(Event *calendar, int eventCount, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < eventCount; i++) {
        fprintf(file, "%s\n", calendar[i].date);
        fprintf(file, "%s", calendar[i].description);
    }

    fclose(file);
}

// Function to load events from a text file
int loadEventsFromFile(Event *calendar, int *eventCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;  // File doesn't exist or cannot be opened
    }

    while (fscanf(file, "%s", calendar[*eventCount].date) != EOF) {
        fgetc(file);  // Consume newline
        fgets(calendar[*eventCount].description, sizeof(calendar[*eventCount].description), file);
        (*eventCount)++;
    }

    fclose(file);
    return 1;  // File successfully loaded
}

int main() {
    Event calendar[100];  // Array to store events
    int eventCount = 0;   // Number of events in the calendar

    // Try loading events from a file, create a new file if not found
    if (!loadEventsFromFile(calendar, &eventCount, "events.txt")) {
        printf("No saved events found. Creating a new calendar.\n");
    }

    while (1) {
        printf("\nOptions:\n");
        printf("1. Add Event\n");
        printf("2. View Events for a Date\n");
        printf("3. View All Events\n");
        printf("4. Save Events to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEvent(calendar, &eventCount);
                break;
            case 2: {
                char date[12];
                printf("Enter date (YYYY-MM-DD): ");
                scanf("%s", date);
                viewEvents(calendar, eventCount, date);
                break;
            }
            case 3:
                viewAllEvents(calendar, eventCount);
                break;
            case 4:
                saveEventsToFile(calendar, eventCount, "events.txt");
                printf("Events saved to file.\n");
                break;
            case 5:
                printf("Exiting...\n");
                // Save events before exiting
                saveEventsToFile(calendar, eventCount, "events.txt");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}