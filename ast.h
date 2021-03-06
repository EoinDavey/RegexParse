#ifndef AST_H
#define AST_H

#include <memory>
#include <iostream>

enum Op {CATOP, STAROP, PLUSOP, OPTOP, OROP, LITOP};
class AST {
    public:
        class Node {
            public:
                Node();
                Op op;
                std::unique_ptr<Node> l,r;
                char v;
            friend std::ostream& operator<< (std::ostream&, const Node&);
        };
        std::unique_ptr<Node> root;
        AST(std::unique_ptr<Node> r);
        AST(void);
    friend std::ostream& operator<< (std::ostream&, const AST&);
};

#endif
