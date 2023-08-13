#ifndef VISITOR_HPP
#define VISITOR_HPP

class Comic;
class Novel;

class Visitor {
 public:
  virtual void Visit(Comic& comic);
  virtual void Visit(Novel& novel);
  virtual ~Visitor() = default;
};

#endif
