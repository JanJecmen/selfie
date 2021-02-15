// libcstar procedures for printing
void init_library();
void print(uint64_t* s);
void print_binary(uint64_t n, uint64_t a);
void println();

uint64_t main() {
    init_library();

    print("Tests for | (bitwise OR)\n");
    if ((0b1010 | 0b0101) == 0b1111) print("okay\n"); else { print_binary(0b1010 | 0b0101, 8); print(" - fail\n"); }
    if ((0b101010 | 0b0) == 0b101010) print("okay\n"); else { print_binary(0b101010 | 0b0, 8); print(" - fail\n"); }
    if ((0b1010 | 0b1111) == 0b1111) print("okay\n"); else { print_binary(0b1010 | 0b1111, 8); print(" - fail\n"); }

    print("Tests for ^ (bitwise XOR)\n");
    if ((0b1010 ^ 0b0101) == 0b1111) print("okay\n"); else { print_binary(0b1010 ^ 0b0101, 8); print(" - fail\n"); }
    if ((0b101010 ^ 0b0) == 0b101010) print("okay\n"); else { print_binary(0b101010 ^ 0b0, 8); print(" - fail\n"); }
    if ((0b1010 ^ 0b1111) == 0b0101) print("okay\n"); else { print_binary(0b1010 ^ 0b1111, 8); print(" - fail\n"); }

    print("Tests for & (bitwise AND)\n");
    if ((0b1010 & 0b0101) == 0b0) print("okay\n"); else { print_binary(0b1010 & 0b0101, 8); print(" - fail\n"); }
    if ((0b101010 & 0b0) == 0b0) print("okay\n"); else { print_binary(0b101010 & 0b0, 8); print(" - fail\n"); }
    if ((0b1010 & 0b1111) == 0b1010) print("okay\n"); else { print_binary(0b1010 & 0b1111, 8); print(" - fail\n"); }

    print("Tests for ~ (bitwise NOT)\n");
    if (~0b0101 == -6) print("okay\n"); else { print_binary(~0b0101, 8); print(" - fail\n"); }
    if (~0b0 == -1) print("okay\n"); else { print_binary(~0b0, 8); print(" - fail\n"); }
    if (~0b1111 == -16) print("okay\n"); else { print_binary(~0b1111, 8); print(" - fail\n"); }

    print("Tests for << (bitwise SHIFT LEFT)\n");
    if ((0b1010 << 0) == 0b1010) print("okay\n"); else { print_binary(0b1010 << 0, 8); print(" - fail\n"); }
    if ((0b101010 << 0b1) == 0b1010100) print("okay\n"); else { print_binary(0b101010 << 0b1, 8); print(" - fail\n"); }
    if ((0b1010 << 3) == 0b1010000) print("okay\n"); else { print_binary(0b1010 << 3, 8); print(" - fail\n"); }

    print("Tests for >> (bitwise SHIFT RIGHT)\n");
    if ((0b1010 >> 0) == 0b1010) print("okay\n"); else { print_binary(0b1010 >> 0, 8); print(" - fail\n"); }
    if ((0b101010 >> 1) == 0b10101) print("okay\n"); else { print_binary(0b101010 >> 1, 8); print(" - fail\n"); }
    if ((0b1010 >> 0b11) == 0b1) print("okay\n"); else { print_binary(0b1010 >> 0b11, 8); print(" - fail\n"); }

    return 0;
}
