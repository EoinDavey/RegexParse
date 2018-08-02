#include "ast.h"
#define IND(s) for(int i = 0; i < s; ++i) printf("  ");

const char * opStrs[] = {"CATOP", "STAROP", "OROP", "LITOP"};
AST::AST() {}
AST::AST(std::unique_ptr<Node> r) : root(std::move(r)) {}

AST::Node::Node() : v('\0') {}

std::ostream& prnode(std::ostream& out, const AST::Node& d, int dpt) {
    IND(dpt);
    out << opStrs[d.op] << std::endl;
    if(d.l) {
        IND(dpt);
        out << "l: " << std::endl;
        prnode(out, *(d.l), dpt+1);
    }
    if(d.r) {
        IND(dpt);
        out << "r: " << std::endl;
        prnode(out, *(d.r), dpt+1);
    }
    if(d.v) {
        IND(dpt);
        out << "v: " << d.v << std::endl;
    }
    return out;
}

std::ostream& operator<< (std::ostream& out, const AST::Node& d) {
    out << "op: " << opStrs[d.op];
    if(d.l)
        out << " l: {" << *(d.l) << "}";
    if(d.r)
        out << " r: {" << *(d.r) << "}";
    if(d.v)
        out << " v: " << d.v;
    return out;
}

std::ostream& operator<< (std::ostream& out, const AST& a) {
    if(a.root)
        prnode(out,*(a.root),0);
    return out;
}
