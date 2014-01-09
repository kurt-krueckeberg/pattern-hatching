#ifndef SuffixPrintVisitor_h_239472934
#define SuffixPrintVisitor_h_239472934
#include "Visitor.h"
#include <iostream>

class File;  // forward declarations
class Directory;

class SuffixPrintVisitor : public Visitor {

 public:
    void visit(const File *pFile);
    void visit(const Directory *pDir);
    
};

inline void SuffixPrintVisitor::visit(const File *pFile)
{
    std::cout << '@';
}

inline void SuffixPrintVisitor::visit(const Directory *pDir)
{
    std::cout << "/";
}
#endif
