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

public class HabitQuest {
    static ArrayList<Habit> habits = new ArrayList<>();
    static Scanner sc = new Scanner(System.in);

    //  Save to file
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

    //  Load from file
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

    //  Add habit
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

    //  Delete habit
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

    //  Edit habit
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

    //  Check-in
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

    //  View habits
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

    //  Main
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
                case 1:
                    addHabit();
                    break;

                case 2:
                    checkInHabit();
                    break;

                case 3:
                    viewHabits();
                    break;

                case 4:
                    editHabit();
                    break;

                case 5:
                    deleteHabit();
                    break;

                case 6:
                    saveToFile();
                    System.out.println("Goodbye!");
                    return;

                default:
                    System.out.println("Invalid option!");
}
        }
    }
}