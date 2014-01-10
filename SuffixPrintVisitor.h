#ifndef SuffixPrintVisitor_h_239472934
#define SuffixPrintVisitor_h_239472934
#include "Visitor.h"
#include <iosfwd>
#include <ostream>
class File;  // forward declarations
class Directory;

class SuffixPrintVisitor : public Visitor {
    
     std::ostream& ostr; 
     
 public:
     
    SuffixPrintVisitor(std::ostream& o)  : ostr(o) {}
    
    void visit(const File *pFile);
    void visit(const Directory *pDir);
    
};

inline void SuffixPrintVisitor::visit(const File *pFile)
{
    ostr << '@';
}

inline void SuffixPrintVisitor::visit(const Directory *pDir)
{
    ostr << "/";
}
#endif
