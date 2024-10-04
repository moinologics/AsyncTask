#include <Arduino.h>

#include "AsyncTask.h"

AsyncTask::AsyncTask() {
  this->taskList = nullptr;
  this->currentTime = 0;
  this->nextId = 1;
}

// Method to add a one-time task
void AsyncTask::once(Callback callback, unsigned long timeout) {
  this->addTask(callback, ONCE, timeout);
}

// Method to add a repeating task
void AsyncTask::repeat(Callback callback, unsigned long interval) {
  this->addTask(callback, REPEAT, interval);
}

// Private method to add a task with auto-generated ID
void AsyncTask::addTask(Callback callback, TaskMode mode, unsigned long interval) {
  Task *newTask = new Task();
  newTask->id = nextId++;  // Assign and increment the ID
  newTask->callback = callback;
  newTask->mode = mode;
  newTask->lastRun = 0;
  newTask->interval = interval;
  newTask->next = nullptr;
  if (this->taskList ==
      nullptr) {  // If the list is empty, newTask becomes the head
    this->taskList = newTask;
  } else {  // Otherwise, find the last task in the list
    Task *current = this->taskList;
    while (current->next != nullptr) {
      current = current->next;  // Move to the next task
    }
    // Set the new task as the next of the last task
    current->next = newTask;
  }
}

// Method to remove a task by id
void AsyncTask::removeTask(int id) {
  Task *current = this->taskList;
  Task *previous = nullptr;

  while (current != nullptr) {
    if (current->id == id) {
      if (previous != nullptr) {
        previous->next = current->next;
      } else {
        this->taskList = current->next;  // Remove head
      }
      delete current;  // Free memory
      return;
    }
    previous = current;
    current = current->next;
  }
}

// Method to run tasks based on the time gap
void AsyncTask::loop() {
  currentTime = millis();  // Get the current time

  Task *current = this->taskList;
  while (current != nullptr) {
    // Check if it's time to run the task
    if (currentTime - current->lastRun >= current->interval) {
      current->callback();             // Execute the callback
      current->lastRun = currentTime;  // Update last run time

      // Check if the task is ONCE and should be removed
      if (current->mode == ONCE) {
        Task *toDelete = current;
        current = current->next;         // Move to next task
        this->removeTask(toDelete->id);  // Remove the task
      } else {
        current = current->next;  // Move to next task
      }
    } else {
      current = current->next;  // Move to next task
    }
  }
}

// A method to clear all tasks (e.g., during cleanup)
void AsyncTask::clearAllTasks() {
  while (taskList != nullptr) {
    this->removeTask(taskList->id);
  }
}

/** Example Usage

void task() {
  Serial.println("named task executed");
}

AsyncTask asyncTask;

void setup() {
  Serial.begin(9600);
  // Add some tasks
  asyncTask.once([]() { Serial.println("anonymous Task executed"); }, 1000);
//Run once every 1000ms asyncTask.repeat(task, 2000);  // Run every 2000ms
}

void loop() {
  asyncTask.run();  // Call to check and run tasks
}

**/
