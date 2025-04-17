grammar Fraction;

main: (NEWLINE | (stat ';' NEWLINE?))* EOF;

stat : assignment #AssignmentStat
|print #PrintStat;  

print : 'print' expr;

assignment : expr '->' ID;

expr: expr op=('+' | '-') expr #ExprAddSub
|expr op=(':' | '*') expr #ExprDivMul
|'(' expr ')'             #ExprParent
|expr '^' expr #ExprPot
|num                      #ExprInt
|num '/' num             #ExprFrac
|'reduce' expr #ReduceExpr
|ID                      #ExprID;

num: op=('+' | '-')? INTEGER #ExprUnary;

NEWLINE : [\n\r];
ID : [a-zA-Z_]+;
INTEGER : [0-9]+;
WS : [ \t] -> skip;
