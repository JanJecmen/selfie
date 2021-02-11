
// libcstar procedures for printing
void init_library();
void print(uint64_t* s);
void print_unsigned_integer(uint64_t n);
void print_binary(uint64_t n, uint64_t a);
void println();

uint64_t main() {
  // initialize selfie's libcstar library
  init_library();

  // print_binary(0b, 8);
  // println();
  // print("0b102 in decimal: ");
  // print_unsigned_integer(0b102);
  // print(" ");
  // print_binary(0b102, 8);
  // println();

  print("0b0 in decimal: ");
  print_unsigned_integer(0b0);
  print(" ");
  print_binary(0B0, 8);
  println();

  print("0b10 in decimal: ");
  print_unsigned_integer(0b10);
  print(" ");
  print_binary(0b10, 8);
  println();

  print("0b101010 in decimal: ");
  print_unsigned_integer(0b101010);
  print(" ");
  print_binary(0b101010, 8);
  println();

  print("0b00001 in decimal: ");
  print_unsigned_integer(0b00001);
  print(" ");
  print_binary(0b00001, 8);
  println();

  return 0;
}
