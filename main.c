#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct Task {
    int id;
    char title[50];
    int priority;   // 1 = High, 2 = Medium, 3 = Low
};

struct Task tasks[MAX];
int count = 0;

// Utility function to convert priority number to text
const char* getPriorityText(int priority) {
    switch(priority) {
        case 1: return "High";
        case 2: return "Medium";
        case 3: return "Low";
        default: return "Unknown";
    }
}

// Load tasks from file
void loadTasksFromFile() {
    FILE *f = fopen("tasks.txt", "r");
    if (!f) return; // file doesn't exist yet

    count = 0;
    while (fscanf(f, "%d|%49[^|]|%d\n", &tasks[count].id, tasks[count].title, &tasks[count].priority) == 3) {
        count++;
        if (count >= MAX) break;
    }
    fclose(f);
}

// Save tasks to file
void saveTasksToFile() {
    FILE *f = fopen("tasks.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%d\n", tasks[i].id, tasks[i].title, tasks[i].priority);
    }
    fclose(f);
}

// Function to add a task
void addTask() {
    if (count >= MAX) {
        printf("Task list full!\n");
        return;
    }

    printf("Enter Task ID: ");
    scanf("%d", &tasks[count].id);

    printf("Enter Task Title: ");
    scanf(" %[^\n]", tasks[count].title);

    do {
        printf("Enter Priority (1-High, 2-Medium, 3-Low): ");
        scanf("%d", &tasks[count].priority);
        if (tasks[count].priority < 1 || tasks[count].priority > 3)
            printf("Invalid priority. Please enter 1, 2, or 3.\n");
    } while(tasks[count].priority < 1 || tasks[count].priority > 3);

    count++;
    saveTasksToFile();
    printf("Task added successfully!\n");
}

// Function to display tasks
void displayTasks() {
    if (count == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n--- Task List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Title: %s | Priority: %s\n",
               tasks[i].id, tasks[i].title, getPriorityText(tasks[i].priority));
    }
}

// Sort tasks by priority (Bubble Sort)
void sortByPriority() {
    struct Task temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
    printf("Tasks sorted by priority!\n");
}

// Search task by ID
void searchTask() {
    int id;
    printf("Enter Task ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            printf("Task Found: %s | Priority: %s\n",
                   tasks[i].title, getPriorityText(tasks[i].priority));
            return;
        }
    }
    printf("Task not found.\n");
}

// Delete task by ID
void deleteTask() {
    int id;
    printf("Enter Task ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            count--;
            saveTasksToFile();
            printf("Task deleted successfully!\n");
            return;
        }
    }
    printf("Task not found.\n");
}

// Clear screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Main function
int main() {
    loadTasksFromFile();
    int choice;

    do {
        clearScreen();
        printf("\n--- Smart Task Manager ---\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Sort Tasks by Priority\n");
        printf("4. Search Task\n");
        printf("5. Delete Task\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: displayTasks(); break;
            case 3: sortByPriority(); break;
            case 4: searchTask(); break;
            case 5: deleteTask(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
        if(choice != 6) {
            printf("\nPress Enter to continue...");
            getchar(); // consume newline
            getchar(); // wait for user
        }
    } while (choice != 6);

    return 0;
}
