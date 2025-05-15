## Grammar Rules for BakScript

### Program Structure

Program -> Statement\* EOF

### Statements

Statement -> VarDeclaration
| Assignment
| PrintStatement
| WhenStatement
| RepeatStatement

### Variable Declaration

VarDeclaration -> "make" ( "num" | "string" ) identifier ("=" Expression)? ";"

### Assignment

Assignment -> identifier "=" Expression ";"

### Print Statement

PrintStatement -> "show" identifier ";"

### Conditional (if-else equivalent)

WhenStatement -> "when" Expression ":" Block ("otherwise" ":" Block)?

### Loop

RepeatStatement -> "repeat" ":" Block

### Expressions

Expression -> Term ( ( "+" | "-" ) Term )_
Term -> Factor ( ( "_" | "/" ) Factor )\*
Factor -> identifier
| number
| string
| "(" Expression ")"

### Tokens

identifier -> [a-zA-Z\_][a-zA-Z0-9_]_
number -> [0-9]+
string -> "\"" ._ "\""
