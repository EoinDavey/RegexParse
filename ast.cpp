#include "ast.h"

const char * opStrs[] = {"CATOP", "STAROP", "OROP", "LITOP"};
AST::AST() {}
AST::AST(std::unique_ptr<Node> r) : root(std::move(r)) {}

std::ostream& operator<< (std::ostream& out, const AST::Node& d) {
    out << "op: " << opStrs[d.op];
    if(d.l)
        out << " l: {" << *(d.l) << "}";
    if(d.r)
        out << " r: {" << *(d.r) << "}";
    if(d.v.size() > 0)
        out << " v: " << d.v;
    return out;
}

std::ostream& operator<< (std::ostream& out, const AST& a) {
    if(a.root)
        out << *(a.root);
    return out;
}
