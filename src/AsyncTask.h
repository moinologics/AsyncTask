#ifndef ASYNCTASK_H
#define ASYNCTASK_H

class AsyncTask {
 private:
  // Task Modes
  enum TaskMode { ONCE, REPEAT };

  // Struct for a single task
  struct Task {
    int id;                  // Unique task ID
    void (*callback)();      // Pointer to a function
    TaskMode mode;           // Task mode: ONCE or REPEAT
    unsigned long lastRun;   // Timestamp of the last execution
    unsigned long interval;  // Time gap between runs (ms)
    Task* next;              // Pointer to the next task
  };

  // Define a type alias for the callback function pointer
  using Callback = void (*)();

  Task* taskList;             // Head of the linked list
  unsigned long currentTime;  // Current time for task management
  int nextId;                 // Auto-incrementing task ID

  // Private method to add a task with auto-generated ID
  void addTask(Callback callback, TaskMode mode, unsigned long interval);

  // Method to remove a task by id (used internally)
  void removeTask(int id);

 public:
  // Constructor
  AsyncTask();

  // Method to add a one-time task
  void once(Callback callback, unsigned long timeout);

  // Method to add a repeating task
  void repeat(Callback callback, unsigned long interval);

  // Method to be put inside sketch loop 
  void loop();

  // A method to clear all tasks (e.g., during cleanup)
  void clearAllTasks();
};

#endif
