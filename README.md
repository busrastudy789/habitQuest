# Habit Tracker

A simple console-based Habit Tracker application implemented in both **C** and **Java**. The program helps users build positive habits by tracking daily completions, maintaining streaks, awarding points, and storing progress in a local file.

## Features

* Add new habits
* Edit existing habits
* Delete habits
* Track habit completion within a specified time range
* Maintain streak counts
* Earn points for successful habit completion
* Receive bonus points for reaching a 7-day streak
* Persist data using file storage (`habits.txt`)
* View all habits and their statistics

---

## Habit Rules

### Successful Completion

* User completes a habit within its assigned time range.
* Rewards:

  * +10 points
  * +1 streak

### Streak Bonus

* When a habit reaches a streak of **7 consecutive completions**:

  * +10 bonus points

### Failed Completion

* If the user marks a habit as incomplete:

  * -5 points
  * Streak resets to 0

### Time Restriction

A habit can only be checked in during its configured time window.

Example:

Start Time: 0800
End Time: 1000

A check-in at 0900 is allowed.
A check-in at 1100 is not allowed.

---

## Data Structure

Each habit stores the following information:

| Field           | Description                          |
| --------------- | ------------------------------------ |
| Name            | Habit title                          |
| Streak          | Current consecutive completion count |
| Points          | Total earned points                  |
| Completed Today | Daily completion status              |
| Start Time      | Beginning of valid check-in period   |
| End Time        | End of valid check-in period         |

---

## File Storage

The application automatically saves all habit data into:

```text
habits.txt
```

Data is loaded when the program starts and saved whenever:

* A habit is added
* A habit is edited
* A habit is deleted
* A habit is checked in
* The program exits

---

## Menu Options

```text
=== Habit Tracker ===

1. Add Habit
2. Check-in Habit
3. View Habits
4. Edit Habit
5. Delete Habit
6. Exit
```

### Add Habit

Create a new habit by entering:

* Habit name
* Start time (HHMM)
* End time (HHMM)

### Check-in Habit

Mark a habit as completed or failed for the day.

### View Habits

Display:

* Habit name
* Current streak
* Total points
* Active time range

### Edit Habit

Modify:

* Habit name
* Start time
* End time

### Delete Habit

Remove a habit permanently.

---

## C Version

### Compile

```bash
gcc habit_tracker.c -o habit_tracker
```

### Run

```bash
./habit_tracker
```

---

## Java Version

### Compile

```bash
javac HabitTracker.java
```

### Run

```bash
java HabitTracker
```

---

## Example Usage

```text
Enter habit name: Exercise
Enter start time (HHMM): 0700
Enter end time (HHMM): 0900

Habit added!
```

```text
Enter current time (HHMM): 0800
Select habit: 1
Completed? (1=yes / 0=no): 1

Completed! +10 points
```

---

## Future Improvements

Potential enhancements include:

* Automatic system time detection
* Daily reset functionality
* Multiple streak milestones
* Achievement badges
* Statistics and reporting
* Weekly and monthly progress tracking
* Graphical User Interface (GUI)
* Database integration

---

## Technologies Used

### C Version

* C Language
* Standard Library (`stdio.h`, `stdlib.h`, `string.h`)

### Java Version

* Java
* Collections Framework (`ArrayList`)
* File I/O (`BufferedReader`, `BufferedWriter`)
* Exception Handling

---

## License

This project is intended for educational purposes and habit-tracking practice. Feel free to modify and extend it according to your needs.
