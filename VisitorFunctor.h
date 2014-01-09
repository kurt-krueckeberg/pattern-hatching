#ifndef VisitorFunctor_h_2973294723
#define VisitorFunctor_h_2973294723
class VistorFunctor {

   Visitor &visitor;

public:

  VisitorFunctor(Visitor& v) : visitor(v) {}

  void operator()(Node& node)
  {
     return node.accept(visitor);
  }
};
#endif