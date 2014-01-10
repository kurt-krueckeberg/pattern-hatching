#ifndef FILE_H_12122013
#define  FILE_H_12122013
#include <string>
#include "Node.h"
#include "Visitor.h"

class Directory;

class File : public Node {

    std::string name;
    std::string date_created;
    int file_size; 

    File(const File&); // can't have duplicate files

    public:   
  
    File(const std::string& file_name, const std::string& created_date, int size) : name(file_name), date_created(created_date), file_size(size)
    {
    }
    
    virtual std::string getName() const throw(node_logic_error)
    {
        return name;
    }
    
    virtual std::string getDateCreated() const  throw(node_logic_error)
    {
        return date_created;
    }

    virtual long getSize() const  throw(node_logic_error)
    {
        return file_size;
    }
    
    virtual void accept(Visitor &v) const //++
    {
         v.visit(this); // implies that visit() has a prototype of "visit(const Node&)"
    }
};
#endif
