#ifndef Node_H_12122013
#define Node_H_12122013
 /**********************************
 Node: base class for composite class Directory and leaf class File
 \***********************************/
#include <iosfwd>
#include <string>
#include <exception>
#include <stdexcept>  
class Directory;
class Visitor;

class Node { // abstract base class. accept(Visitor&) is pure virtual.
    
  friend class Directory;    
  
public:
    
    class node_logic_error : public std::logic_error {
        public:  
       node_logic_error(const std::string& msg) :  std::logic_error(msg) {} 
             
    };
    
public:    
    static const char directory_separator = '/';
     
    virtual void adopt(Node* p) throw(node_logic_error)
    { 
      throw node_logic_error("This class does not support the add operation");
    }

    virtual void remove(Node *pnode) throw(node_logic_error, std::invalid_argument)
    {
	throw node_logic_error("This class does not support the remove operation");
    }

    virtual Node *getChild(int i)  throw(node_logic_error, std::out_of_range)
    {
	throw node_logic_error("This class does not support the getChild operation");
    }
  
    virtual std::string getName() const  throw(node_logic_error)
    {
	throw node_logic_error("This class does not support the getName operation");
    }
 
    virtual std::string getDateCreated() const throw(node_logic_error)
    {
	throw node_logic_error("This class does not support the getDateCreated operation");
    }    
  
    virtual long getSize() const throw(node_logic_error)
    {
	throw node_logic_error("This class does not support the getSize operation");
    }

    virtual void accept(Visitor& v) const = 0; //++ add const version
    
    friend std::ostream& operator<<(std::ostream& ostr, const Node& c); 
        
    Node() {};

    virtual ~Node() {};
   
};

inline std::ostream& operator<<(std::ostream& ostr, const Node& c) 
{
    ostr << std::string("This is class Node\n");
    return ostr;
}
#endif
