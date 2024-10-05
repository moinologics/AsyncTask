# AsyncTask ⚡ Library for Arduino

AsyncTask is a lightweight, simple task management library for Arduino that allows you to schedule non-blocking tasks with ease. You can run tasks either once or repeatedly at defined intervals, without using `delay()`. This makes it ideal for managing background processes without blocking the main loop.

## Features

- Schedule tasks to run **once** or **repeatedly** at specified intervals.
- Non-blocking, event-driven task execution.
- Dynamically manages tasks using a linked list structure.
- Automatically removes tasks after they are executed (for one-time tasks).
- Supports adding multiple tasks, which will run in the background during the main loop.

## Installation

1. **Manual Installation**:
    - Download this repository as a `.zip` file.
    - In the Arduino IDE, go to **Sketch** → **Include Library** → **Add .ZIP Library...**.
    - Select the downloaded `.zip` file.
    
2. **Library Manager Installation** (if published in the Arduino Library Manager):
    - In the Arduino IDE, go to **Tools** → **Manage Libraries**.
    - Search for "AsyncTask" in the Library Manager and install it.

## Usage

### 1. Include the Library

At the beginning of your sketch, include the `AsyncTask` library:

```cpp
#include <AsyncTask.h>
```

### 2. Creating the AsyncTask Object
Create an instance of the AsyncTask class:

```cpp
AsyncTask asyncTask;
```

### 3. Adding a One-Time Task
To add a task that runs only once after a specified interval (in milliseconds), use the once() method:

```cpp
asyncTask.once(yourCallbackFunction, 1000);  // Run the callback after 1000 ms (1 second)
```

### 4. Adding a Repeating Task
To add a task that repeats at a specified interval, use the repeat() method:

```cpp
asyncTask.repeat(yourCallbackFunction, 2000);  // Run the callback every 2000 ms (2 seconds)

```

### 5. Running the Task Scheduler
In the `loop()` function, call `asyncTask.run()` to let the scheduler execute any pending tasks:

```cpp
void loop() {
  asyncTask.run();  // Continuously check and run tasks
}
```

### 6. Callback Functions
You can define your task's callback function like this:

```cpp
void yourCallbackFunction() {
  Serial.println("Task executed!");
}
```

or it is also possible to directly pass anonymous function like this

```cpp
asyncTask.once([]() {
  Serial.println("i'm anonymous function task");
}, 1000);
```

## Example Sketch
Here's an example of using AsyncTask in a sketch:

```cpp
#include <AsyncTask.h>

AsyncTask asyncTask;

void setup() {
  Serial.begin(9600);

  // Run this task once after 1 second
  asyncTask.once(taskOne, 1000);

  // Run this task every 2 seconds
  asyncTask.repeat(taskTwo, 2000);

  // Run this anonymous task once after 3 second
  asyncTask.once([]() {
    Serial.println("i'm anonymous function task");
  }, 3000);
}

void loop() {
  // Check and run scheduled tasks
  asyncTask.loop();
}

void taskOne() {
  Serial.println("Task One executed (once)!");
}

void taskTwo() {
  Serial.println("Task Two executed (repeating)!");
}
```

### Clearing All Tasks (Optional)
If needed, you can clear all the tasks using:

```cpp
asyncTask.clearAllTasks();
```


### API Reference
  `void once(Callback callback, unsigned long timeout)`
  - Description: Adds a task that runs once after the specified time.
  - Parameters:
    - `callback`: The function to call when the task runs.
    - `interval`: The time delay (in milliseconds) before the task is executed.

 `void repeat(Callback callback, unsigned long interval)`
  - Description: Adds a task that runs repeatedly at the specified time interval.
  - Parameters:
    - `callback`: The function to call when the task runs.
    - `interval`: The interval (in milliseconds) between each execution of the task.

 `void run()`
  - Description: Checks all scheduled tasks and executes any that are due to run. This method should be called frequently in the loop() to ensure that tasks are executed on time.

 `void clearAllTasks()`
  - Description: Clears all scheduled tasks from the task list.

### License
This library is open-sourced under the MIT License.

## Contributions
Feel free to submit issues and pull requests to contribute to the development of this library. All contributions are welcome!