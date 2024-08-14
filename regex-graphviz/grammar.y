%scanner-token-function scanner.lex()
%stype std::pair<int,int>
%token-path Tokens.h
%token CHAR PLUS STAR QUESTION BAR LPAREN RPAREN ERROR

%%

start       :           {
                            nodes.emplace_back("Start", 0);
                            nodes.front().addEdgeTo(1);
                        }
            regex EOF   {
                            nodes.emplace_back("Accept", nodes.size());
                        }
            ;

regex       : regex STAR            {
                                        $$ = $1;
                                        nodes.at($$.first - 1).addEdgeTo(nodes.size());
                                        nodes.at($$.second).addEdgeTo($$.first);
                                    }
            | regex QUESTION        {
                                        $$ = $1;
                                        nodes.at($$.first - 1).addEdgeTo(nodes.size());
                                    }
            | regex PLUS            {
                                        $$ = $1;
                                        nodes.at($$.second).addEdgeTo($$.first);
                                    }
            | regex regex           {   
                                        $$ = { $1.first, $2.second };
                                        nodes.at($1.second).addEdgeTo($2.first);
                                        nodes.at($2.second).addEdgeTo(nodes.size());
                                    }
            | regex BAR regex       {
                                        $$ = { $1.first, nodes.size() };
                                        nodes.at($1.second).addEdgeTo($$.second);
                                        nodes.at($$.first - 1).addEdgeTo($3.first);
                                        nodes.at($3.second).addEdgeTo($$.second);
                                        nodes.emplace_back("", $$.second);
                                        nodes.at($$.second).addEdgeTo(nodes.size());
                                    }
            | LPAREN regex RPAREN   {
                                        $$ = $2;
                                    }
            | CHAR                  {
                                        $$ = { nodes.size(), nodes.size() };
                                        nodes.emplace_back(scanner.matched(), $$.first);
                                    }
            ;
