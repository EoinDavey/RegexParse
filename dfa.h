#ifndef DFA_H
#define DFA_H

#include <memory>
#include <vector>
#include "ast.h"

struct Edge;
struct Vertex;
typedef std::shared_ptr<Vertex> vptr;

struct Edge {
    vptr dest;
    bool eps;
    char match;
    Edge(vptr, bool, char);
};

struct Vertex {
    std::vector<Edge> edges;
    Vertex();
};

struct DFA {
    vptr start;
    std::vector<vptr> ends;
};

DFA AST2DFA(const AST&);

void crawl(const DFA&);

#endif
