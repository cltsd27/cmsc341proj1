#include "Llama.cpp"

int main() {

  Llama<int, 5> llama1;
  llama1.push(5);
  llama1.push(1);
  llama1.push(1);
  llama1.push(1);
  llama1.push(2);
  llama1.push(3);
  llama1.push(2);
  llama1.push(2);
  llama1.push(5);
  llama1.push(7);
  llama1.push(2);
  llama1.push(4);
  llama1.push(2);
  llama1.push(1);
  llama1.push(3);
  llama1.push(2);
  llama1.dump();
  return 0;
}
