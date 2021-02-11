
// libcstar procedures for printing
void init_library();
void print(uint64_t* s);
void print_unsigned_integer(uint64_t n);
void print_hexadecimal(uint64_t n, uint64_t a);
void println();

uint64_t main() {
  // initialize selfie's libcstar library
  init_library();

  // print_hexadecimal(0x, 8);
  // println();
  // print("0x6787 in decimal: ");
  // print_unsigned_integer(0x6787);
  // print(" ");
  // print_hexadecimal(0x6787, 8);
  // println();

  print("0x0 in decimal: ");
  print_unsigned_integer(0x0);
  print(" ");
  print_hexadecimal(0X0, 8);
  println();

  print("0x10 in decimal: ");
  print_unsigned_integer(0x10);
  print(" ");
  print_hexadecimal(0x10, 8);
  println();

  print("0x2a in decimal: ");
  print_unsigned_integer(0x2a);
  print(" ");
  print_hexadecimal(0x2a, 8);
  println();

  print("0x00001 in decimal: ");
  print_unsigned_integer(0x00001);
  print(" ");
  print_hexadecimal(0x00001, 8);
  println();

  return 0;
}
