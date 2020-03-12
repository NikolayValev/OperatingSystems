#include <fstream>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <thread>
#include <vector>
#define SIZE 20
int term[1000];
class SafeQueue {
public:
  // constructor for an object of type SafeQueue
  SafeQueue(int size = SIZE) {
    arr = new int[size];
    capacity = size;
    front = 0;
    back = -1;
    count = 0;
  }
  // destructor for an object of type SafeQueue
  ~SafeQueue() { delete arr; }
  // return false if the queue contains
  // data, true if empty. Should return immediately.
  bool isEmpty() { return (size() == 0); }
  // Puts the double at the “front” of the queue into “value”
  // If the queue is currently empty, this function should BLOCK.
  void read(double &value) {
    // check for queue underflow
    if (isEmpty()) {
      sem_wait(&sem);
    }
    pthread_mutex_lock(&lock);
    value = arr[front];
    front = (front + 1) % capacity;
    count--;
    pthread_mutex_unlock(&lock);
    sem_post(&sem);
  }
  // Puts “value” at the back of the queue.
  // Returns true if all goes smoothly.
  int write(double value) { // check for queue overflow
    if (isFull()) {
      sem_wait(&sem);
    }
    pthread_mutex_lock(&lock);
    back = (back + 1) % capacity;
    arr[back] = value;
    count++;
    pthread_mutex_unlock(&lock);
    sem_post(&sem);
    return 1;
  }
  int size() { return count; }
  bool isFull() { return (size() == capacity); }

private:
  int *arr;     // array to store the elements in the queue
  int capacity; // max capacity
  int front;    // first element
  int back;     // last element
  int count;    // current size
  sem_t sem;
  pthread_mutex_t lock;
};
SafeQueue queue;
int fib(int n) {
  if (n <= 1)
    return n;
  if (term[n] != 0)
    return term[n];
  else {
    return term[n] = fib(n - 1) + fib(n - 2);
    // return term[n];
  }
}
void calculating(int n) {
  for (size_t i = 0; i < n; i++) {
    queue.write(fib(i));
  }
}
void fileoutput(int n) {
  std::string outputFilename = "Fib-";
  outputFilename += std::to_string(n);
  outputFilename += ".txt";
  std::ofstream output;
  output.open(outputFilename);
  for (size_t i = 0; i < n; i++) {
    double temp = 0;
    queue.read(temp);
    output << i + 1 << ". " << temp << std::endl;
  }
  output.close();
}

int main() {
  int n = 0;
  std::cout << "The program to print numbers, enter -1 to exit." << std::endl;
  std::cout << "Enter a number" << std::endl;
  std::cin >> n;
  if (n == -1) {
    return 0;
  }

  std::thread printer(fileoutput, n);
  std::thread calculator(calculating, n);
  printer.join();
  calculator.join();
  return 0;
}