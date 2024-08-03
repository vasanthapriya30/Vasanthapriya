#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& taskDescription) {
        tasks.emplace_back(taskDescription);
        cout << "Task added successfully.\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". [" << (tasks[i].completed ? "x" : " ") << "] " << tasks[i].description << '\n';
        }
    }

    void markTaskAsCompleted(size_t taskIndex) {
        if (taskIndex < 1 || taskIndex > tasks.size()) {
            cout << "Invalid task index.\n";
            return;
        }
        tasks[taskIndex - 1].completed = true;
        cout << "Task marked as completed.\n";
    }

    void removeTask(size_t taskIndex) {
        if (taskIndex < 1 || taskIndex > tasks.size()) {
            cout << "Invalid task index.\n";
            return;
        }
        tasks.erase(tasks.begin() + taskIndex - 1);
        cout << "Task removed successfully.\n";
    }
};

void showMenu() {
    cout << "\nTo-Do List Manager\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Remove Task\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    ToDoList toDoList;
    int choice;
    string taskDescription;
    size_t taskIndex;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                cin.ignore(); // to ignore leftover newline character from previous input
                getline(cin, taskDescription);
                toDoList.addTask(taskDescription);
                break;

            case 2:
                toDoList.viewTasks();
                break;

            case 3:
                cout << "Enter task index to mark as completed: ";
                cin >> taskIndex;
                toDoList.markTaskAsCompleted(taskIndex);
                break;

            case 4:
                cout << "Enter task index to remove: ";
                cin >> taskIndex;
                toDoList.removeTask(taskIndex);
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
