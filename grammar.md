Copyright (c) 2015-2021, the Selfie Project authors. All rights reserved. Please see the AUTHORS file for details. Use of this source code is governed by a BSD license that can be found in the LICENSE file.

Selfie is a project of the Computational Systems Group at the Department of Computer Sciences of the University of Salzburg in Austria. For further information and code please refer to:

http://selfie.cs.uni-salzburg.at

This is the grammar of the C Star (C\*) programming language.

C\* is a tiny subset of the programming language C. C\* features global variable declarations with optional initialization as well as procedures with parameters and local variables. C\* has five statements (assignment, while loop, if-then-else, procedure call, and return) and standard arithmetic (`+`, `-`, `*`, `/`, `%`) and comparison (`==`, `!=`, `<`, `<=`, `>`, `>=`) operators. C\* includes the unary `*` operator for dereferencing pointers hence the name but excludes data types other than `uint64_t` and `uint64_t*`, bitwise and Boolean operators, and many other features. The C\* grammar is LL(1) with 6 keywords and 22 symbols. Whitespace as well as single-line (`//`) and multi-line (`/*` to `*/`) comments are ignored.

C\* Keywords: `uint64_t`, `void`, `if`, `else`, `while`, `return`

C\* Symbols: `integer_literal`, `character_literal`, `string_literal`, `identifier`, `,`, `;`, `(`, `)`, `{`, `}`, `+`, `-`, `*`, `/`, `%`, `=`, `==`, `!=`, `<`, `<=`, `>`, `>=`

with:

```
binary_integer_literal = ( "0b" | "0B" ) binary_digit { binary_digit } .

octal_integer_literal = ( "0o" | "0O" ) { octal_digit } .

decimal_integer_literal = decimal_digit { decimal_digit } .

hexadecimal_integer_literal = ( "0x" | "0X" ) hexadecimal_digit { hexadecimal_digit } .

integer_literal   = binary_integer_literal | octal_integer_literal |
                      decimal_integer_literal | hexadecimal_integer_literal .

character_literal = "'" printable_character "'" .

string_literal    = """ { printable_character } """ .

identifier        = letter { letter | digit | "_" } .
```

and:

```
binary_digit  = "0" | "1" .

octal_digit  = "0" | ... | "7" .

decimal_digit  = "0" | ... | "9" .

hexadecimal_digit  = "0" | ... | "9" | "a" | ... | "f" | "A" | ... | "F" .

letter = "a" | ... | "z" | "A" | ... | "Z" .
```

C\* Grammar:

```
cstar             = { type identifier
                      [ "=" [ cast ] [ "-" ] ( integer_literal | character_literal ) ] ";" |
                    ( "void" | type ) identifier procedure } .

type              = "uint64_t" [ "*" ] .

cast              = "(" type ")" .

procedure         = "(" [ variable { "," variable } ] ")" ( ";" |
                    "{" { variable ";" } { statement } "}" ) .

variable          = type identifier .

statement         = ( [ "*" ] identifier | "*" "(" expression ")" ) "=" expression ";" |
                    call ";" | while | if | return ";" .

call              = identifier "(" [ expression { "," expression } ] ")" .

expression        = simple_expression
                    [ ( "==" | "!=" | "<" | ">" | "<=" | ">=" ) simple_expression ] .

simple_expression = term { ( "+" | "-" ) term } .

term              = factor { ( "*" | "/" | "%" ) factor } .

factor            = [ cast ] [ "-" ] [ "*" ]
                    ( integer_literal | character_literal | string_literal |
                      identifier | call | "(" expression ")" ) .

while             = "while" "(" expression ")"
                      ( statement | "{" { statement } "}" ) .

if                = "if" "(" expression ")"
                      ( statement | "{" { statement } "}" )
                    [ "else"
                      ( statement | "{" { statement } "}" ) ] .

return            = "return" [ expression ] .
```