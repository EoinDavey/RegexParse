#include "dfa.h"

#include <cstdio>
#include <queue>
#include <set>

Edge::Edge(vptr v, bool eps, char m) : dest(v), eps(eps), match(m) {}

Vertex::Vertex() {}

DFA Node2DFA(const AST::Node& n) {
    switch(n.op) {
        case CATOP:
            {
                DFA l = Node2DFA(*n.l);
                DFA r = Node2DFA(*n.r);
                for(vptr& v : l.ends)
                    v->edges.push_back(Edge(r.start, true, '\0'));
                l.ends = std::move(r.ends);
                return l;
            }
        case LITOP:
            {
                vptr st = std::make_shared<Vertex>();
                vptr end = std::make_shared<Vertex>();
                Edge e = Edge(end, false, n.v);
                st->edges.push_back(std::move(e));
                DFA out;
                out.start = std::move(st);
                out.ends.push_back(std::move(end));
                return out;
            }
        case OROP:
            {
                DFA l = Node2DFA(*n.l);
                DFA r = Node2DFA(*n.r);
                DFA n;
                vptr v = std::make_shared<Vertex>();
                v->edges.push_back(Edge(l.start, true, '\0'));
                v->edges.push_back(Edge(r.start, true, '\0'));
                n.start = std::move(v);
                n.ends.insert(n.ends.end(),
                        std::make_move_iterator(l.ends.begin()),
                        std::make_move_iterator(l.ends.end()));
                n.ends.insert(n.ends.end(),
                        std::make_move_iterator(r.ends.begin()),
                        std::make_move_iterator(r.ends.end()));
                return n;
            }
        case OPTOP:
            {
                DFA l = Node2DFA(*n.l);
                l.ends.push_back(l.start);
                return l;
            }
        case STAROP:
            {
                DFA l = Node2DFA(*n.l);
                vptr u = std::make_shared<Vertex>();
                u->edges.push_back(Edge(l.start, true, '\0'));
                for(vptr& v: l.ends)
                    v->edges.push_back(Edge(l.start, true, '\0'));
                l.start = std::move(u);
                l.ends.push_back(l.start);
                return l;
            }
        case PLUSOP:
            {
                DFA l = Node2DFA(*n.l);
                for(vptr& v: l.ends)
                    v->edges.push_back(Edge(l.start, true, '\0'));
                return l;
            }
        default:
            printf("FUkd");
    }
}

DFA AST2DFA(const AST& a) {
    return Node2DFA(*a.root);
}

void crawl(const DFA& d) {
    std::set<vptr> acc(d.ends.begin(), d.ends.end());
    std::queue<std::pair<vptr, std::string> > q;
    printf("Limit: ");
    int cnt = 0;
    int lim; scanf("%d", &lim);
    q.push({d.start,""});
    while(!q.empty() && cnt < lim) {
        auto v = q.front(); q.pop();

        if(acc.find(v.first) != acc.end())
            std::cout << v.second << std::endl, cnt++;

        for(const Edge& e : v.first->edges)
            q.push({e.dest, e.eps ? v.second : v.second+e.match});
    }
}
