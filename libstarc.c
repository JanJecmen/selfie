
// selfie bootstraps int to uint64_t!
void exit(int code);

uint64_t read(uint64_t fd, uint64_t* buffer, uint64_t bytes_to_read);
uint64_t write(uint64_t fd, uint64_t* buffer, uint64_t bytes_to_write);

// selfie bootstraps char to uint64_t!
uint64_t open(char* filename, uint64_t flags, uint64_t mode);

// selfie bootstraps void* to uint64_t* and unsigned to uint64_t!
void* malloc(unsigned long);

void init_library();

uint64_t two_to_the_power_of(uint64_t p);
uint64_t ten_to_the_power_of(uint64_t p);

uint64_t log_ten(uint64_t n);

uint64_t left_shift(uint64_t n, uint64_t b);
uint64_t right_shift(uint64_t n, uint64_t b);

uint64_t get_bits(uint64_t n, uint64_t i, uint64_t b);

uint64_t absolute(uint64_t n);
uint64_t max(uint64_t a, uint64_t b);

uint64_t signed_less_than(uint64_t a, uint64_t b);
uint64_t signed_division(uint64_t a, uint64_t b);

uint64_t load_character(char* s, uint64_t i);
char* store_character(char* s, uint64_t i, uint64_t c);

char* string_alloc(uint64_t l);
uint64_t string_length(char* s);
char* string_copy(char* s);
void string_reverse(char* s);
uint64_t string_compare(char* s, char* t);

uint64_t atoi(char* s, uint64_t base);
char* itoa(uint64_t n, char* s, uint64_t b, uint64_t d, uint64_t a);

void put_character(uint64_t c);

void print(char* s);
void println();

void print_character(uint64_t c);
void print_string(char* s);
void print_unsigned_integer(uint64_t n);
void print_integer(uint64_t n);
void print_hexadecimal(uint64_t n, uint64_t a);
void print_octal(uint64_t n, uint64_t a);
void print_binary(uint64_t n, uint64_t a);

uint64_t round_up(uint64_t n, uint64_t m);

void zero_memory(uint64_t* memory, uint64_t size);

uint64_t* smalloc(uint64_t size); // use this to allocate memory, not malloc
uint64_t* zmalloc(uint64_t size); // use this to allocate zeroed memory

// ------------------------ GLOBAL CONSTANTS -----------------------

uint64_t BASE_BINARY = 2;
uint64_t BASE_OCTAL = 8;
uint64_t BASE_DECIMAL = 10;
uint64_t BASE_HEXADECIMAL = 16;

uint64_t KILOBYTE = 1024;       // 1KB (KiB: 2^10B)
uint64_t MEGABYTE = 1048576;    // 1MB (MiB: 2^20B)
uint64_t GIGABYTE = 1073741824; // 1GB (GiB: 2^30B)

uint64_t EXITCODE_IOERROR = 15;
uint64_t EXITCODE_SCANNERERROR = 16;
uint64_t EXITCODE_OUTOFVIRTUALMEMORY = 19;

uint64_t CHAR_EOF = -1;         // end of file
uint64_t CHAR_TAB = 9;          // ASCII code 9  = tabulator
uint64_t CHAR_LF = 10;          // ASCII code 10 = line feed
uint64_t CHAR_CR = 13;          // ASCII code 13 = carriage return
uint64_t CHAR_SINGLEQUOTE = 39; // ASCII code 39 = '
uint64_t CHAR_DOUBLEQUOTE = '"';

char* SELFIE_URL = (char*)0;

uint64_t SIZEOFUINT64 = 8;        // in bytes
uint64_t SIZEOFUINT64INBITS = 64; // SIZEOFUINT64 * 8

uint64_t* power_of_two_table;

uint64_t UINT64_MAX; // maximum numerical value of an unsigned 64-bit integer

uint64_t INT64_MAX; // maximum numerical value of a signed 64-bit integer
uint64_t INT64_MIN; // minimum numerical value of a signed 64-bit integer

uint64_t* character_buffer; // buffer for reading and writing characters
char* integer_buffer;       // buffer for formatting integers

void init_library() {
    uint64_t i;

    SELFIE_URL = "selfie.cs.uni-salzburg.at";

    // determine actual size of uint64_t
    SIZEOFUINT64 = (uint64_t)((uint64_t*)SELFIE_URL + 1) - (uint64_t)SELFIE_URL;
    SIZEOFUINT64INBITS = SIZEOFUINT64 * 8;

    // powers of two table with SIZEOFUINT64INBITS entries for 2^0 to
    // 2^(SIZEOFUINT64INBITS - 1)
    power_of_two_table = smalloc(SIZEOFUINT64INBITS * SIZEOFUINT64);

    *power_of_two_table = 1; // 2^0 == 1

    i = 1;

    while (i < SIZEOFUINT64INBITS) {
        // compute powers of two incrementally using this recurrence relation
        *(power_of_two_table + i) = *(power_of_two_table + (i - 1)) * 2;

        i = i + 1;
    }

    // compute 64-bit unsigned integer range using signed integer arithmetic
    UINT64_MAX = -1;

    // compute 64-bit signed integer range using unsigned integer arithmetic
    INT64_MIN = two_to_the_power_of(SIZEOFUINT64INBITS - 1);
    INT64_MAX = INT64_MIN - 1;

    // allocate and touch to make sure memory is mapped for read calls
    character_buffer = smalloc(SIZEOFUINT64);
    *character_buffer = 0;

    // accommodate at least SIZEOFUINT64INBITS numbers for itoa, no mapping
    // needed
    integer_buffer = string_alloc(SIZEOFUINT64INBITS);
}

uint64_t round_up(uint64_t n, uint64_t m) {
    if (n % m == 0)
        return n;
    else
        return n - n % m + m;
}

void zero_memory(uint64_t* memory, uint64_t size) {
    uint64_t i;

    size = round_up(size, SIZEOFUINT64) / SIZEOFUINT64;

    i = 0;

    while (i < size) {
        // erase memory by setting it to 0
        *(memory + i) = 0;

        i = i + 1;
    }
}

uint64_t* smalloc(uint64_t size) {
    // this procedure ensures a defined program exit
    // if no memory can be allocated
    uint64_t* memory;

    memory = malloc(size);

    if (size == 0)
        // any address including 0
        return memory;
    else if (memory == (uint64_t*)0) {
        if (character_buffer)
            // can only print error message if character_buffer has been
            // successfully allocated
            print("malloc out of memory\n");

        exit(EXITCODE_OUTOFVIRTUALMEMORY);
    }

    return memory;
}

uint64_t* zmalloc(uint64_t size) {
    uint64_t* memory;
    size = round_up(size, SIZEOFUINT64);
    memory = smalloc(size);
    zero_memory(memory, size);
    return memory;
}

uint64_t two_to_the_power_of(uint64_t p) {
    // assert: 0 <= p < SIZEOFUINT64INBITS
    return *(power_of_two_table + p);
}

uint64_t ten_to_the_power_of(uint64_t p) {
    // use recursion for simplicity and educational value
    // for p close to 0 performance is not relevant
    if (p == 0)
        return 1;
    else
        return ten_to_the_power_of(p - 1) * 10;
}

uint64_t log_ten(uint64_t n) {
    // use recursion for simplicity and educational value
    // for n < 1000000 performance is not relevant
    if (n < 10)
        return 0;
    else
        return log_ten(n / 10) + 1;
}

uint64_t left_shift(uint64_t n, uint64_t b) {
    // assert: 0 <= b < SIZEOFUINT64INBITS
    return n * two_to_the_power_of(b);
}

uint64_t right_shift(uint64_t n, uint64_t b) {
    // assert: 0 <= b < SIZEOFUINT64INBITS
    return n / two_to_the_power_of(b);
}

uint64_t get_bits(uint64_t n, uint64_t i, uint64_t b) {
    if (i + b < SIZEOFUINT64INBITS)
        // reset all bits from index i + b to SIZEOFUINT64INBITS - 1
        n = n % two_to_the_power_of(i + b);
    else if (i >= SIZEOFUINT64INBITS)
        return 0;

    if (i == 0)
        // redundant fast path
        return n;
    else
        // cancel all bits from index 0 to i - 1
        return right_shift(n, i);
}

uint64_t absolute(uint64_t n) {
    if (signed_less_than(n, 0))
        return -n;
    else
        return n;
}

uint64_t max(uint64_t a, uint64_t b) {
    if (a > b)
        return a;
    else
        return b;
}

uint64_t signed_less_than(uint64_t a, uint64_t b) {
    // INT64_MIN <= n <= INT64_MAX iff
    // INT64_MIN + INT64_MIN <= n + INT64_MIN <= INT64_MAX + INT64_MIN iff
    // -2^64 <= n + INT64_MIN <= 2^64 - 1 (sign-extended to 65 bits) iff
    // 0 <= n + INT64_MIN <= UINT64_MAX
    return a + INT64_MIN < b + INT64_MIN;
}

uint64_t signed_division(uint64_t a, uint64_t b) {
    // assert: b != 0
    // assert: a == INT64_MIN -> b != -1
    if (a == INT64_MIN)
        if (b == INT64_MIN)
            return 1;
        else if (signed_less_than(b, 0))
            return INT64_MIN / absolute(b);
        else
            return -(INT64_MIN / b);
    else if (b == INT64_MIN)
        return 0;
    else if (signed_less_than(a, 0))
        if (signed_less_than(b, 0))
            return absolute(a) / absolute(b);
        else
            return -(absolute(a) / b);
    else if (signed_less_than(b, 0))
        return -(a / absolute(b));
    else
        return a / b;
}

uint64_t load_character(char* s, uint64_t i) {
    // assert: i >= 0
    uint64_t a;

    // a is the index of the word where the
    // to-be-loaded i-th character in s is
    a = i / SIZEOFUINT64;

    // CAUTION: at boot levels higher than 0, s is only accessible
    // in C* at word granularity, not individual characters

    // return i-th 8-bit character in s
    return get_bits(*((uint64_t*)s + a), (i % SIZEOFUINT64) * 8, 8);
}

char* store_character(char* s, uint64_t i, uint64_t c) {
    // assert: i >= 0, 0 <= c < 2^8 (all characters are 8-bit)
    uint64_t a;

    // a is the index of the word where the with c
    // to-be-overwritten i-th character in s is
    a = i / SIZEOFUINT64;

    // CAUTION: at boot levels higher than 0, s is only accessible
    // in C* at word granularity, not individual characters

    // subtract the to-be-overwritten character to reset its bits in s
    // then add c to set its bits at the i-th position in s
    *((uint64_t*)s + a) =
        (*((uint64_t*)s + a) -
         left_shift(load_character(s, i), (i % SIZEOFUINT64) * 8)) +
        left_shift(c, (i % SIZEOFUINT64) * 8);

    return s;
}

char* string_alloc(uint64_t l) {
    // allocates zeroed memory for a string of l characters
    // plus a null terminator aligned to word size
    return (char*)zmalloc(l + 1);
}

uint64_t string_length(char* s) {
    uint64_t i;

    i = 0;

    while (load_character(s, i) != 0)
        i = i + 1;

    return i;
}

char* string_copy(char* s) {
    uint64_t l;
    char* t;
    uint64_t i;

    l = string_length(s);

    t = string_alloc(l);

    i = 0;

    while (i < l) {
        store_character(t, i, load_character(s, i));

        i = i + 1;
    }

    store_character(t, i, 0); // null-terminated string

    return t;
}

void string_reverse(char* s) {
    uint64_t i;
    uint64_t j;
    uint64_t tmp;

    i = 0;
    j = string_length(s) - 1;

    while (i < j) {
        tmp = load_character(s, i);

        store_character(s, i, load_character(s, j));
        store_character(s, j, tmp);

        i = i + 1;
        j = j - 1;
    }
}

uint64_t string_compare(char* s, char* t) {
    uint64_t i;

    i = 0;

    while (1)
        if (load_character(s, i) == 0)
            if (load_character(t, i) == 0)
                return 1;
            else
                return 0;
        else if (load_character(s, i) == load_character(t, i))
            i = i + 1;
        else
            return 0;
}

uint64_t atoi(char* s, uint64_t base) {
    uint64_t i;
    uint64_t n;
    uint64_t c;

    if (base != BASE_BINARY) {
        if (base != BASE_OCTAL) {
            if (base != BASE_DECIMAL) {
                if (base != BASE_HEXADECIMAL) {
                    print("invalid base for number\n");
                    exit(EXITCODE_SCANNERERROR);
                }
            }
        }
    }

    // the conversion of the ASCII string in s to its
    // numerical value n begins with the leftmost digit in s
    i = 0;

    // and the numerical value 0 for n
    n = 0;

    // load character (one byte) at index i in s from memory requires
    // bit shifting since memory access can only be done at word granularity
    c = load_character(s, i);

    // loop until s is terminated
    while (c != 0) {
        // the numerical value of ASCII-encoded decimal digits
        // is offset by the ASCII code of '0' (which is 48)
        if (base == BASE_HEXADECIMAL) {
            if (c >= 'a') {
                c = c - 'a' + 10;
            } else if (c >= 'A') {
                c = c - 'A' + 10;
            } else {
                c = c - '0';
            }
        } else {
            c = c - '0';
        }

        if (base == BASE_BINARY) {
            if (c > 1) {
                print("cannot convert non-binary number\n");
                exit(EXITCODE_SCANNERERROR);
            }
        } else if (base == BASE_OCTAL) {
            if (c > 7) {
                print("cannot convert non-octal number\n");
                exit(EXITCODE_SCANNERERROR);
            }
        } else if (base == BASE_DECIMAL) {
            if (c > 9) {
                print("cannot convert non-decimal number\n");
                exit(EXITCODE_SCANNERERROR);
            }
        } else if (base == BASE_HEXADECIMAL) {
            if (c > 15) {
                print("cannot convert non-hexadecimal number\n");
                exit(EXITCODE_SCANNERERROR);
            }
        }

        // assert: s contains a number in base 2 or 8 or 10 or 16

        // detect wrap around
        if (n < UINT64_MAX / base)
            n = n * base + c;
        else if (n == UINT64_MAX / base)
            if (c <= UINT64_MAX % base)
                n = n * base + c;
            else {
                // s contains a decimal number larger than UINT64_MAX
                print("cannot convert out-of-bound number\n");

                exit(EXITCODE_SCANNERERROR);
            }
        else {
            // s contains a decimal number larger than UINT64_MAX
            print("cannot convert out-of-bound number\n");

            exit(EXITCODE_SCANNERERROR);
        }

        // go to the next digit
        i = i + 1;

        // load character (one byte) at index i in s from memory requires
        // bit shifting since memory access can only be done at word granularity
        c = load_character(s, i);
    }

    return n;
}

char* itoa(uint64_t n, char* s, uint64_t b, uint64_t d, uint64_t a) {
    // assert: b in {2,4,8,10,16}

    uint64_t i;
    uint64_t sign;

    // conversion of the integer n to an ASCII string in s with base b,
    // sign d, and alignment a begins with the leftmost digit in s
    i = 0;

    // for now assuming n is positive
    sign = 0;

    if (n == 0) {
        store_character(s, 0, '0');

        i = 1;
    } else if (d)
        if (signed_less_than(n, 0))
            if (b == 10) {
                // n is represented as two's complement
                // convert n to a positive number but remember the sign
                n = -n;

                sign = 1;
            }

    while (n != 0) {
        if (n % b > 9)
            // the ASCII code of hexadecimal digits larger than 9
            // is offset by the ASCII code of 'A' (which is 65)
            store_character(s, i, n % b - 10 + 'A');
        else
            // the ASCII code of digits less than or equal to 9
            // is offset by the ASCII code of '0' (which is 48)
            store_character(s, i, n % b + '0');

        // convert n by dividing n with base b
        n = n / b;

        i = i + 1;
    }

    if (b == 10) {
        if (sign) {
            store_character(s, i, '-'); // negative decimal numbers start with -

            i = i + 1;
        }

        while (i < a) {
            store_character(s, i, ' '); // align with spaces

            i = i + 1;
        }
    } else {
        while (i < a) {
            store_character(s, i, '0'); // align with 0s

            i = i + 1;
        }

        if (b == 8) {
            store_character(s, i, 'o'); // octal numbers start with 0o
            store_character(s, i + 1, '0');

            i = i + 2;
        } else if (b == 16) {
            store_character(s, i, 'x'); // hexadecimal numbers start with 0x
            store_character(s, i + 1, '0');

            i = i + 2;
        }
    }

    store_character(s, i, 0); // null-terminated string

    // our numeral system is positional hindu-arabic, that is,
    // the weight of digits increases right to left, which means
    // that we need to reverse the string we computed above
    string_reverse(s);

    return s;
}

void put_character(uint64_t c) {
    if (character_buffer) {
        *character_buffer = c;
        write(1, character_buffer, 1);
    } else
        exit(EXITCODE_IOERROR);
}

void print(char* s) {
    uint64_t i;

    if (s == (char*)0)
        print("NULL");
    else {
        i = 0;

        while (load_character(s, i) != 0) {
            put_character(load_character(s, i));

            i = i + 1;
        }
    }
}

void println() { put_character(CHAR_LF); }

void print_character(uint64_t c) {
    put_character(CHAR_SINGLEQUOTE);

    if (c == CHAR_EOF)
        print("end of file");
    else if (c == CHAR_TAB)
        print("tabulator");
    else if (c == CHAR_LF)
        print("line feed");
    else if (c == CHAR_CR)
        print("carriage return");
    else
        put_character(c);

    put_character(CHAR_SINGLEQUOTE);
}

void print_string(char* s) {
    put_character(CHAR_DOUBLEQUOTE);

    print(s);

    put_character(CHAR_DOUBLEQUOTE);
}

void print_unsigned_integer(uint64_t n) {
    print(itoa(n, integer_buffer, 10, 0, 0));
}

void print_integer(uint64_t n) { print(itoa(n, integer_buffer, 10, 1, 0)); }

void print_hexadecimal(uint64_t n, uint64_t a) {
    print(itoa(n, integer_buffer, 16, 0, a));
}

void print_octal(uint64_t n, uint64_t a) {
    print(itoa(n, integer_buffer, 8, 0, a));
}

void print_binary(uint64_t n, uint64_t a) {
    print(itoa(n, integer_buffer, 2, 0, a));
}
