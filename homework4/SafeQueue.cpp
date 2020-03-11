#include <iostream>
#define SIZE 20

#include <condition_variable>
#include <mutex>
class SafeQueue {
public:
  // constructor for an object of type SafeQueue
  SafeQueue(int size = SIZE);
  // destructor for an object of type SafeQueue
  ~SafeQueue();
  // return false if the queue contains
  // data, true if empty. Should return immediately.
  bool isEmpty();
  // Puts the double at the “front” of the queue into “value”
  // If the queue is currently empty (see discussion below),
  // this function should BLOCK.
  void read(double &value);

  // Puts “value” at the back of the queue.
  // Returns false if anything goes wrong (full queue?)
  // Returns true if all goes smoothly.
  int write(double value);
  int size();
  bool isEmpty();
  bool isFull();
  int peek();

private:
  int *arr;     // array to store the elements in the queue
  int capacity; // max capacity
  int front;    // first element
  int back;     // last element
  int count;    // current size
  mutable std::mutex m;
  std::condition_variable c;
};
// Constructor to initialize queue
SafeQueue::SafeQueue(int size) {
  arr = new int[size];
  capacity = size;
  front = 0;
  back = -1;
  count = 0;
}
SafeQueue::~SafeQueue() { delete arr; }
void SafeQueue::read(double &value) {
  // check for queue underflow
  std::unique_lock<std::mutex> lock(m);
  if (isEmpty()) {
    c.wait(lock);
  }
  value = arr[front];
  front = (front + 1) % capacity;
  count--;
  // c.notify_one(); dont need it
}
int SafeQueue::write(double value) { // check for queue overflow
  std::lock_guard<std::mutex> lock(m);
  if (isFull()) {
    std::cerr << "OverFlow\nProgram Terminated\n";
    exit(EXIT_FAILURE);
  }
  back = (back + 1) % capacity;
  arr[back] = value;
  count++;
  c.notify_one();
}
// Utility function to return the size of the queue
int SafeQueue::size() { return count; }

// Utility function to check if the queue is empty or not
bool SafeQueue::isEmpty() { return (size() == 0); }

// Utility function to check if the queue is full or not
bool SafeQueue::isFull() { return (size() == capacity); }

int SafeQueue::peek() {
  if (isEmpty()) {
    std::cout << "UnderFlow\nProgram Terminated\n";
    exit(EXIT_FAILURE);
  }
  return arr[front];
}
