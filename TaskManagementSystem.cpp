#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Task structure to store task details
struct Task {
    int id;
    string description;
    bool completed;
};

// Function to add a new task
void addTask(vector<Task>& tasks, const string& desc) {
    Task newTask;
    newTask.id = tasks.empty() ? 1 : tasks.back().id + 1;
    newTask.description = desc;
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added: ID " << newTask.id << endl;
}

// Function to view all tasks
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }
    for (const auto& task : tasks) {
        cout << "ID: " << task.id << ", Description: " << task.description
             << ", Status: " << (task.completed ? "Completed" : "Pending") << endl;
    }
}

// Function to update task status
void updateTask(vector<Task>& tasks, int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = !task.completed;
            cout << "Task ID " << id << " updated to "
                 << (task.completed ? "Completed" : "Pending") << endl;
            return;
        }
    }
    cout << "Task ID " << id << " not found.\n";
}

// Function to delete a task
void deleteTask(vector<Task>& tasks, int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            cout << "Task ID " << id << " deleted.\n";
            return;
        }
    }
    cout << "Task ID " << id << " not found.\n";
}

// Function to save tasks to a file
void saveTasks(const vector<Task>& tasks, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    for (const auto& task : tasks) {
        outFile << task.id << "|" << task.description << "|" << task.completed << endl;
    }
    outFile.close();
    cout << "Tasks saved to " << filename << endl;
}

// Function to load tasks from a file
void loadTasks(vector<Task>& tasks, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No existing task file found.\n";
        return;
    }
    tasks.clear();
    string line;
    while (getline(inFile, line)) {
        Task task;
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1 + 1);
        task.id = stoi(line.substr(0, pos1));
        task.description = line.substr(pos1 + 1, pos2 - pos1 - 1);
        task.completed = (line.substr(pos2 + 1) == "1");
        tasks.push_back(task);
    }
    inFile.close();
    cout << "Tasks loaded from " << filename << endl;
}

int main() {
    vector<Task> tasks;
    string filename = "tasks.txt";
    loadTasks(tasks, filename);
    int choice;

    while (true) {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n2. View Tasks\n3. Update Task\n4. Delete Task\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        if (choice == 1) {
            string desc;
            cout << "Enter task description: ";
            getline(cin, desc);
            addTask(tasks, desc);
            saveTasks(tasks, filename);
        } else if (choice == 2) {
            viewTasks(tasks);
        } else if (choice == 3) {
            int id;
            cout << "Enter task ID to update: ";
            cin >> id;
            updateTask(tasks, id);
            saveTasks(tasks, filename);
        } else if (choice == 4) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            deleteTask(tasks, id);
            saveTasks(tasks, filename);
        } else if (choice == 5) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}