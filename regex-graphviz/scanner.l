letter  [a-z]
%%
{letter}    return Tokens::CHAR;
"+"         return Tokens::PLUS;
"*"         return Tokens::STAR;
"?"         return Tokens::QUESTION;
"|"         return Tokens::BAR;
"("         return Tokens::LPAREN;
")"         return Tokens::RPAREN;
.|\n        return Tokens::ERROR;
