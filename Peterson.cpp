bool lock = true;
int main() {}

bool tsl(bool &lock) {
  bool before = lock;
  lock = true;
  return before;
}
void fun1() {
  do {
    while (tsl(&lock))
      ;
    // Critical section
    lock = false;
    // non CS
  } while (true);
}

void fun2() {
  do {
    while (tsl(&lock))
      ;
    // Critical section
    lock = false;
    // non CS
  } while (true);
}