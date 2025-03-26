#ifndef ASYNCTASK_H
#define ASYNCTASK_H

class AsyncTask {
 private:
  // Task Modes
  enum TaskMode { ONCE, REPEAT };

  // Struct for a single task
  struct Task {
    unsigned int id;         // Unique task ID
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
  unsigned int nextId;        // Auto-incrementing task ID

  // Private method to add a task with auto-generated ID
  unsigned int addTask(Callback callback, TaskMode mode, unsigned long interval);

 public:
  // Constructor
  AsyncTask();

  // Method to add a one-time task
  unsigned int once(Callback callback, unsigned long timeout);

  // Method to add a repeating task
  unsigned int repeat(Callback callback, unsigned long interval);

  // Method to remove a task by id
  void remove(unsigned int id);
 
  // Method to be put inside sketch loop 
  void loop();

  // A method to clear all tasks (e.g., during cleanup)
  void clearAllTasks();
};

#endif
