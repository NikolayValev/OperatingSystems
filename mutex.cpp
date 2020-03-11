int main() {
  // One mutex per resourse not per thread!
  Mutex m;
  m.lock();
  m.unlock();
}