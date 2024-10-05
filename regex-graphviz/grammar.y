%scanner-token-function scanner.lex()
%stype std::pair<std::list<Node>::iterator,std::list<Node>::iterator>
%token-path Tokens.h
%token CHAR LPAREN RPAREN ERROR BAR PLUS STAR QUESTION

%%

start       :           {
                            nodes.emplace_front("Start", nodeId++);
                            nodes.emplace_back("?", nodeId++);
                            nextNode = --nodes.end();
                            nodes.front().addEdgeTo(nextNode);
                        }
            regex EOF   {
                            nextNode->setName("Accept");
                        }
            ;

regex       : disjunct
            ;

disjunct    : disjunct BAR concatenate  {
                                        $$ = { nodes.emplace($1.first, "", nodeId++), nextNode };
                                        for (auto& node : nodes) {
                                            for (auto edge : node.getEdges()) {
                                                if (edge == $1.first) {
                                                    node.removeEdgeTo(edge);
                                                    node.addEdgeTo($$.first);
                                                }
                                            }
                                        }
                                        $1.second->removeEdgeTo($3.first);
                                        nextNode->setName("");
                                        $$.first->addEdgeTo($1.first);
                                        $1.second->addEdgeTo($$.second);
                                        $$.first->addEdgeTo($3.first);
                                        $3.second->addEdgeTo($$.second);
                                        nodes.emplace_back("?", nodeId++);
                                        nextNode = --nodes.end();
                                        $$.second->addEdgeTo(nextNode);
                                    }
            | concatenate
            ;

concatenate : concatenate unary     {
                                        $$ = { $1.first, $2.second };
                                    }
            | unary
            ;

unary       : unary STAR            {
                                        $$ = $1;
                                        $$.second->addEdgeTo($$.first);
                                        (--$$.first)->addEdgeTo(nextNode);
                                        ++$$.first;
                                    }
            | unary QUESTION        {
                                        $$ = $1;
                                        (--$$.first)->addEdgeTo(nextNode);
                                        ++$$.first;
                                    }
            | unary PLUS            {
                                        $$ = $1;
                                        $$.second->addEdgeTo($$.first);
                                    }
            | LPAREN regex RPAREN   {
                                        $$ = $2;
                                    }
            | CHAR                  {
                                        $$ = { nextNode, nextNode };
                                        nextNode->setName(scanner.matched());
                                        nodes.emplace_back("?", nodeId++);
                                        nextNode = --nodes.end();
                                        $$.first->addEdgeTo(nextNode);
                                    }
            ;
