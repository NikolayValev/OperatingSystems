#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int fib(int n) {
  if (n <= 1)
    return 1;
  return fib(n - 1) + fib(n - 2);
}
void fileoutput(int n) {
  std::string outputFilename = "Fib-";
  outputFilename += to_string(n);
  outputFilename += ".txt";
  ofstream output;
  output.open(outputFilename);
  for (size_t i = 0; i < n; i++) {
    output << i + 1 << ". " << fib(i) << std::endl;
  }
  output.close();
}

int main() {
  vector<std::thread> workers;
  while (true) {
    int n;
    std::cout << "Enter a number to which to display the fibonacci numbers"
              << std::endl;
    std::cin >> n;
    if (n == -1) {
      for (int i = 0; i < workers.size(); i++) {
        workers.at(i).join();
      }
      std::cout << "Thank you! \nExiting." << std::endl;
      return 0;
    }
    workers.push_back(std::thread(fileoutput, n));
  }
}