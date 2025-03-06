grammar Hello;   // Define a grammar called Hello
main: (greetings | bye)*;
greetings:'hello' name;  // match keyword hello followed by an identifier
bye: 'bye' name;
name: word+;
word: ID;
ID : [a-zA-Z]+ ;  // match lower−case identifiers
WS : [ \t\r\n]+ -> skip;   // skip spaces, tabs, newlines, \r (Windows)
