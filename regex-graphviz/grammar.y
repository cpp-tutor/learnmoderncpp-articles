%scanner-token-function scanner.lex()
%stype std::shared_ptr<Node>
%token-path Tokens.h
%token CHAR LPAREN RPAREN ERROR BAR PLUS STAR QUESTION

%%

start       : regex EOF  {
                            nodes = Node::makeStart(std::move($1), ++nodeId);
                            $$ = nodes;
                        }
            ;

regex       : disjunct              { $$ = std::move($1); }
            ;

disjunct    : disjunct BAR concatenate  {
                                        $$ = Node::makeDisjunct(std::move($1), std::move($3));
                                    }
            | concatenate           { $$ = std::move($1); }
            ;

concatenate : concatenate unary     {
                                        $$ = Node::makeConcat(std::move($1), std::move($2));
                                    }
            | unary                 { $$ = std::move($1); }
            ;

unary       : unary STAR            {
                                        $$ = Node::makeStar(std::move($1));
                                    }
            | unary QUESTION        {
                                        $$ = Node::makeQuestion(std::move($1));
                                    }
            | unary PLUS            {
                                        $$ = Node::makePlus(std::move($1));
                                    }
            | LPAREN regex RPAREN   {
                                        $$ = std::move($2);
                                    }
            | CHAR                  {
                                        $$ = Node::makeLetter(++nodeId, scanner.matched());
                                    }
            ;
