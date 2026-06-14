C SOURCE CODE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HABITS 100

typedef struct {
    char name[50];
    int streak;
    int points;
    int completedToday;
    int startTime;
    int endTime;
} Habit;

Habit habits[MAX_HABITS];
int habitCount = 0;

void saveToFile() {
    FILE *fp = fopen("habits.txt", "w");
    if (!fp) {
        printf("Error saving file!\n");
        return;
    }

    fprintf(fp, "%d\n", habitCount);

    for (int i = 0; i < habitCount; i++) {
        fprintf(fp, "%s\n%d %d %d %d %d\n",
                habits[i].name,
                habits[i].streak,
                habits[i].points,
                habits[i].completedToday,
                habits[i].startTime,
                habits[i].endTime);
    }

    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("habits.txt", "r");
    if (!fp) return;

    fscanf(fp, "%d\n", &habitCount);

    for (int i = 0; i < habitCount; i++) {
        fgets(habits[i].name, 50, fp);
        habits[i].name[strcspn(habits[i].name, "\n")] = 0;

        fscanf(fp, "%d %d %d %d %d\n",
               &habits[i].streak,
               &habits[i].points,
               &habits[i].completedToday,
               &habits[i].startTime,
               &habits[i].endTime);
    }

    fclose(fp);
}

void addHabit() {
    if (habitCount >= MAX_HABITS) {
        printf("Max habits reached!\n");
        return;
    }

    printf("Enter habit name: ");
    getchar();
    fgets(habits[habitCount].name, 50, stdin);
    habits[habitCount].name[strcspn(habits[habitCount].name, "\n")] = 0;

    printf("Enter start time (HHMM): ");
    scanf("%d", &habits[habitCount].startTime);

    printf("Enter end time (HHMM): ");
    scanf("%d", &habits[habitCount].endTime);

    habits[habitCount].streak = 0;
    habits[habitCount].points = 0;
    habits[habitCount].completedToday = 0;

    habitCount++;
    saveToFile();

    printf("Habit added!\n");
}

void deleteHabit() {
    if (habitCount == 0) {
        printf("No habits to delete!\n");
        return;
    }

    printf("\nSelect habit to delete:\n");
    for (int i = 0; i < habitCount; i++) {
        printf("%d. %s\n", i + 1, habits[i].name);
    }

    int choice;
    printf("Enter number: ");
    scanf("%d", &choice);
    choice--;

    if (choice < 0 || choice >= habitCount) {
        printf("Invalid choice!\n");
        return;
    }

    for (int i = choice; i < habitCount - 1; i++) {
        habits[i] = habits[i + 1];
    }

    habitCount--;
    saveToFile();

    printf("Habit deleted!\n");
}

void editHabit() {
    if (habitCount == 0) {
        printf("No habits to edit!\n");
        return;
    }

    printf("\nSelect habit to edit:\n");
    for (int i = 0; i < habitCount; i++) {
        printf("%d. %s\n", i + 1, habits[i].name);
    }

    int choice;
    printf("Enter number: ");
    scanf("%d", &choice);
    choice--;

    if (choice < 0 || choice >= habitCount) {
        printf("Invalid choice!\n");
        return;
    }

    Habit *h = &habits[choice];

    printf("Enter new name (or press Enter to keep same): ");
    getchar();

    char newName[50];
    fgets(newName, 50, stdin);

    if (newName[0] != '\n') {
        newName[strcspn(newName, "\n")] = 0;
        strcpy(h->name, newName);
    }

    printf("Enter new start time (HHMM): ");
    scanf("%d", &h->startTime);

    printf("Enter new end time (HHMM): ");
    scanf("%d", &h->endTime);

    saveToFile();
    printf("Habit updated!\n");
}

void checkInHabit() {
    if (habitCount == 0) {
        printf("No habits to check!\n");
        return;
    }

    printf("Enter current time (HHMM): ");
    int now;
    scanf("%d", &now);

    printf("\nAvailable habits:\n");
    for (int i = 0; i < habitCount; i++) {
        printf("%d. %s (Time: %d - %d)\n",
               i + 1,
               habits[i].name,
               habits[i].startTime,
               habits[i].endTime);
    }

    printf("Select habit number: ");
    int choice;
    scanf("%d", &choice);
    choice--;

    if (choice < 0 || choice >= habitCount) {
        printf("Invalid choice!\n");
        return;
    }

    Habit *h = &habits[choice];

    if (now < h->startTime || now > h->endTime) {
        printf("You cannot check in now. Not within habit time range!\n");
        return;
    }

    printf("Did you complete the habit? (1 = yes / 0 = no): ");
    int done;
    scanf("%d", &done);

    if (done == 1) {
        h->points += 10;
        h->streak++;
        printf("Habit completed! +10 points.\n");

        if (h->streak == 7) {
            printf("BONUS! Streak reached 7. +10 bonus points!\n");
            h->points += 10;
        }
    } else {
        h->points -= 5;
        h->streak = 0;
        printf("Habit failed. -5 points. Streak reset.\n");
    }

    saveToFile();
}

void viewHabits() {
    if (habitCount == 0) {
        printf("No habits added yet.\n");
        return;
    }

    for (int i = 0; i < habitCount; i++) {
        printf("\nHabit %d:\n", i + 1);
        printf("Name: %s\n", habits[i].name);
        printf("Streak: %d\n", habits[i].streak);
        printf("Points: %d\n", habits[i].points);
        printf("Time: %d - %d\n",
               habits[i].startTime,
               habits[i].endTime);
    }
}

int main() {
    loadFromFile();

    while (1) {
        printf("\n=== Habit Tracker ===\n");
        printf("1. Add Habit\n");
        printf("2. Check-in Habit\n");
        printf("3. View Habits\n");
        printf("4. Edit Habit\n");
        printf("5. Delete Habit\n");
        printf("6. Exit\n");
        printf("Choose option: ");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1: addHabit(); break;
            case 2: checkInHabit(); break;
            case 3: viewHabits(); break;
            case 4: editHabit(); break;
            case 5: deleteHabit(); break;
            case 6:
                saveToFile();
                return 0;
            default:
                printf("Invalid option!\n");
        }
    }
}


JAVA SOURCE CODE

import java.io.*;
import java.util.*;

class Habit {
    String name;
    int streak;
    int points;
    int completedToday;
    int startTime;
    int endTime;

    public Habit(String name, int startTime, int endTime) {
        this.name = name;
        this.startTime = startTime;
        this.endTime = endTime;
        this.streak = 0;
        this.points = 0;
        this.completedToday = 0;
    }
}

public class HabitTracker {
    static ArrayList<Habit> habits = new ArrayList<>();
    static Scanner sc = new Scanner(System.in);

    // 🔹 Save to file
    static void saveToFile() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter("habits.txt"))) {
            bw.write(habits.size() + "\n");

            for (Habit h : habits) {
                bw.write(h.name + "\n");
                bw.write(h.streak + " " + h.points + " " + h.completedToday + " " + h.startTime + " " + h.endTime + "\n");
            }
        } catch (IOException e) {
            System.out.println("Error saving file!");
        }
    }

    // 🔹 Load from file
    static void loadFromFile() {
        try (BufferedReader br = new BufferedReader(new FileReader("habits.txt"))) {
            int count = Integer.parseInt(br.readLine());

            for (int i = 0; i < count; i++) {
                String name = br.readLine();
                String[] data = br.readLine().split(" ");

                Habit h = new Habit(name,
                        Integer.parseInt(data[3]),
                        Integer.parseInt(data[4]));

                h.streak = Integer.parseInt(data[0]);
                h.points = Integer.parseInt(data[1]);
                h.completedToday = Integer.parseInt(data[2]);

                habits.add(h);
            }
        } catch (Exception e) {
            // file might not exist first time
        }
    }

    // 🔹 Add habit
    static void addHabit() {
        System.out.print("Enter habit name: ");
        sc.nextLine(); // clear buffer
        String name = sc.nextLine();

        System.out.print("Enter start time (HHMM): ");
        int start = sc.nextInt();

        System.out.print("Enter end time (HHMM): ");
        int end = sc.nextInt();

        habits.add(new Habit(name, start, end));
        saveToFile();

        System.out.println("Habit added!");
    }

    // 🔹 Delete habit
    static void deleteHabit() {
        if (habits.isEmpty()) {
            System.out.println("No habits to delete!");
            return;
        }

        for (int i = 0; i < habits.size(); i++) {
            System.out.println((i + 1) + ". " + habits.get(i).name);
        }

        System.out.print("Enter number: ");
        int choice = sc.nextInt() - 1;

        if (choice < 0 || choice >= habits.size()) {
            System.out.println("Invalid choice!");
            return;
        }

        habits.remove(choice);
        saveToFile();

        System.out.println("Habit deleted!");
    }

    // 🔹 Edit habit
    static void editHabit() {
        if (habits.isEmpty()) {
            System.out.println("No habits to edit!");
            return;
        }

        for (int i = 0; i < habits.size(); i++) {
            System.out.println((i + 1) + ". " + habits.get(i).name);
        }

        System.out.print("Enter number: ");
        int choice = sc.nextInt() - 1;

        if (choice < 0 || choice >= habits.size()) {
            System.out.println("Invalid choice!");
            return;
        }

        Habit h = habits.get(choice);

        sc.nextLine(); // clear buffer
        System.out.print("Enter new name (or press Enter to keep same): ");
        String newName = sc.nextLine();

        if (!newName.isEmpty()) {
            h.name = newName;
        }

        System.out.print("Enter new start time: ");
        h.startTime = sc.nextInt();

        System.out.print("Enter new end time: ");
        h.endTime = sc.nextInt();

        saveToFile();
        System.out.println("Habit updated!");
    }

    // 🔹 Check-in
    static void checkInHabit() {
        if (habits.isEmpty()) {
            System.out.println("No habits!");
            return;
        }

        System.out.print("Enter current time (HHMM): ");
        int now = sc.nextInt();

        for (int i = 0; i < habits.size(); i++) {
            Habit h = habits.get(i);
            System.out.println((i + 1) + ". " + h.name + " (" + h.startTime + "-" + h.endTime + ")");
        }

        System.out.print("Select habit: ");
        int choice = sc.nextInt() - 1;

        if (choice < 0 || choice >= habits.size()) {
            System.out.println("Invalid!");
            return;
        }

        Habit h = habits.get(choice);

        if (now < h.startTime || now > h.endTime) {
            System.out.println("Not within time range!");
            return;
        }

        System.out.print("Completed? (1=yes / 0=no): ");
        int done = sc.nextInt();

        if (done == 1) {
            h.points += 10;
            h.streak++;
            System.out.println("Completed! +10 points");

            if (h.streak == 7) {
                h.points += 10;
                System.out.println("BONUS! +10 points");
            }
        } else {
            h.points -= 5;
            h.streak = 0;
            System.out.println("Failed! -5 points");
        }

        saveToFile();
    }

    // 🔹 View habits
    static void viewHabits() {
        if (habits.isEmpty()) {
            System.out.println("No habits yet.");
            return;
        }

        for (int i = 0; i < habits.size(); i++) {
            Habit h = habits.get(i);

            System.out.println("\nHabit " + (i + 1));
            System.out.println("Name: " + h.name);
            System.out.println("Streak: " + h.streak);
            System.out.println("Points: " + h.points);
            System.out.println("Time: " + h.startTime + "-" + h.endTime);
        }
    }

    // 🔹 Main
    public static void main(String[] args) {
        loadFromFile();

        while (true) {
            System.out.println("\n=== Habit Tracker ===");
            System.out.println("1. Add Habit");
            System.out.println("2. Check-in Habit");
            System.out.println("3. View Habits");
            System.out.println("4. Edit Habit");
            System.out.println("5. Delete Habit");
            System.out.println("6. Exit");
            System.out.print("Choose: ");

            int option = sc.nextInt();

            switch (option) {
                case 1 -> addHabit();
                case 2 -> checkInHabit();
                case 3 -> viewHabits();
                case 4 -> editHabit();
                case 5 -> deleteHabit();
                case 6 -> {
                    saveToFile();
                    System.out.println("Goodbye!");
                    return;
                }
                default -> System.out.println("Invalid option!");
            }
        }
    }
}

