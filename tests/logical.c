// libcstar procedures for printing
void init_library();
void print(uint64_t* s);
void println();

uint64_t eval(uint64_t i) {
    return i;
}

uint64_t dont_eval(uint64_t i) {
    print("\n!!! THIS SHOULD NOT BE PRINTED !!!\n\n");
    return i;
}

uint64_t main() {
    uint64_t a;
    uint64_t b;

    init_library();

    print("Tests for && (logical AND)\n");
    a = 1; b = 1; if (eval(a) && eval(b)) print("okay\n"); else print("fail\n");
    a = 1; b = 0; if (eval(a) && eval(b)) print("fail\n"); else print("okay\n");
    a = 0; b = 1; if (eval(a) && dont_eval(b)) print("fail\n"); else print("okay\n");
    a = 0; b = 0; if (eval(a) && dont_eval(b)) print("fail\n"); else print("okay\n");
    a = 1; b = 0; if (eval(a) && eval(b) && dont_eval(b) && dont_eval(b)) print("fail\n"); else print("okay\n");

    print("Tests for || (logical OR)\n");
    a = 1; b = 1; if (eval(a) || dont_eval(b)) print("okay\n"); else print("fail\n");
    a = 1; b = 0; if (eval(a) || dont_eval(b)) print("okay\n"); else print("fail\n");
    a = 0; b = 1; if (eval(a) || eval(b)) print("okay\n"); else print("fail\n");
    a = 0; b = 0; if (eval(a) || eval(b)) print("fail\n"); else print("okay\n");
    a = 0; b = 1; if (eval(a) || eval(b) || dont_eval(b) || dont_eval(a)) print("okay\n"); else print("fail\n");

    print("Tests for ! (logical NOT)\n");
    a = 1; if (!a) print("fail\n"); else print("okay\n");
    a = 0; if (!a) print("okay\n"); else print("fail\n");
    a = 1; if (!!a) print("okay\n"); else print("fail\n");

    return 0;
}
