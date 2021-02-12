
// libcstar procedures for printing
void init_library();
void print(uint64_t* s);
void print_unsigned_integer(uint64_t n);
void print_octal(uint64_t n, uint64_t a);
void println();

uint64_t main() {
    // initialize selfie's libcstar library
    init_library();

    // print_octal(0o, 8);
    // println();
    // print("0o6787 in decimal: ");
    // print_unsigned_integer(0o6787);
    // print(" ");
    // print_octal(0o6787, 8);
    // println();

    print("0o0 in decimal: ");
    print_unsigned_integer(0o0);
    print(" ");
    print_octal(0O0, 8);
    println();

    print("0o10 in decimal: ");
    print_unsigned_integer(0o10);
    print(" ");
    print_octal(0o10, 8);
    println();

    print("0o52 in decimal: ");
    print_unsigned_integer(0o52);
    print(" ");
    print_octal(0o52, 8);
    println();

    print("0o00001 in decimal: ");
    print_unsigned_integer(0o00001);
    print(" ");
    print_octal(0o00001, 8);
    println();

    return 0;
}
