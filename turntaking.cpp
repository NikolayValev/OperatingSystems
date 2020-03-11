
int turn = 0;
bool interest[2];
int main() {}
void fun1() {
  do {
    interest[0] = true;
    turn = 1;
    while (interest[1] && turn == 1)
      ;
    // Critical section
    interest[0] = false;
    // non CS
  } while (true);
}

void fun2() {
  do {
    interest[1] = true;
    turn = 0;
    while (interest[0] && turn == 0)
      ;
    // Critical section
    interest[1] = false;
    // non CS
  } while (true);
}