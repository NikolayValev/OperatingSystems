#include <fstream>
#include <iostream>
#include <string>
int term[1000];
// Fibonacci Series using memoized Recursion
int fib(int n) {
  if (n <= 1)
    return n;
  if (term[n] != 0)
    return term[n];
  else {
    term[n] = fib(n - 1) + fib(n - 2);
    return term[n];
  }
  // Critical section
  // safeQueue->write (fibonnaci number);
}
void fileoutput(int n) {
  std::string outputFilename = "Fib-";
  outputFilename += std::to_string(n);
  outputFilename += ".txt";
  std::ofstream output;
  output.open(outputFilename);
  for (size_t i = 0; i < n; i++) {
    output << i + 1 << ". " << fib(i) << std::endl;
    /*
    //Critical section
    safeQueue->read(num);
    write num to file
    */
  }
  output.close();
}

int main() { return 0; }