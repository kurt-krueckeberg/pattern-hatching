#ifndef  Directory_H_121223013
#define  Directory_H_121223013
#include <iosfwd>
#include <iostream> 
#include <list>
#include <string>
#include <stack>
#include "Node.h"
#include "Visitor.h"

class Directory : public Node {

    std::list<Node *> nodeList;

    std::string name;
    std::string date_created;

    friend class DirectoryIterator;
    friend class ConstDirectoryIterator;
    template<typename F> void DoRecursive(F& f, const Directory *pdir=nullptr, std::string path=""); 
 
  public:

     // nested stl-compliant forward iterator classes. They iterate the entire Directoy tree structure in order.
     class DirectoryIterator : public std::iterator<std::forward_iterator_tag, Node *> { 
   
          friend class Directory;
          typedef  std::pair< std::list<Node *>::iterator, std::list<Node *>::iterator>  iterators_pair;         
          
          std::stack< iterators_pair >  iters_stack;
          
          Node *pCurrentNode;   // TODO: Change to iterators_pair& ?         
          Directory *pDirectory;  // This is the top level directory which will be iterated.
                  
        public:
                
          explicit DirectoryIterator(Directory & dir); 
        
          // Required forward iterator methods follow
          DirectoryIterator();                          
          DirectoryIterator(const DirectoryIterator&);
          DirectoryIterator& operator=(const DirectoryIterator& other);
          /* 
          Node *next();
          bool hasNext();
          */ 
          Node &operator*() const;  
          Node *operator->() const; 
          DirectoryIterator& operator++();
          DirectoryIterator operator++(int);
                   
          bool operator==(const DirectoryIterator& x) const;
          bool operator!=(const DirectoryIterator& x) const;
     };

     class ConstDirectoryIterator : public std::iterator<std::forward_iterator_tag, const Node *> { 

          friend class Directory;

           DirectoryIterator inner_iter; 
        public:
                
          explicit ConstDirectoryIterator(const Directory & dir); 
          
          // This ctor will function as a cast operator, to convert a DirectoryIterator into a ConstDirectoryIterator
          ConstDirectoryIterator(const DirectoryIterator &iter); 
          
          // Required forward iterator methods follow
          ConstDirectoryIterator();                          
          ConstDirectoryIterator(const ConstDirectoryIterator&);
          ConstDirectoryIterator& operator=(const ConstDirectoryIterator& other);
          
          const Node &operator*() const; 
          const Node *operator->() const;  
          
          ConstDirectoryIterator& operator++();
          ConstDirectoryIterator operator++(int);
                           
          bool operator==(const ConstDirectoryIterator& x) const;
          bool operator!=(const ConstDirectoryIterator& x) const;
     };
    
    typedef DirectoryIterator iterator;   
    typedef ConstDirectoryIterator const_iterator;   
    
    iterator begin();
    iterator end();
    
    const_iterator begin() const;
    const_iterator end() const;
    
    Directory(const std::string& dir_name, const std::string& created);
    
    void print(std::ostream&, Directory *pdir=nullptr, std::string path= "") const;

    template<typename F> void traverse(F& f);

    /*
     * All these methods are virtual in Node 
     */
    void adopt(Node *pnode) throw(node_logic_error);
    Node *getChild(int i)  throw(node_logic_error, std::out_of_range);
    
    void remove(Node *pnode) throw(node_logic_error, std::invalid_argument);
  
    std::string getName() const throw(node_logic_error)
    {
        return name;
    }
    
    std::string getDateCreated() const throw(node_logic_error)
    {
        return date_created;
    }
     
    long getSize() const throw(node_logic_error);

    void accept(Visitor& v) const;

    ~Directory();
};

inline void Directory::accept(Visitor& v) const
{
   v.visit(this);
}

// recursive generic method
template<typename Functor> void Directory::DoRecursive(Functor& F, const Directory *pdir, std::string parent_path)
{
    std::list<Node *>::const_iterator list_iter = pdir->nodeList.begin();
    std::list<Node *>::const_iterator end_iter  = pdir->nodeList.end();
    
    std::string dir_name = pdir->getName();
                
    F(pdir, parent_path);     
    
    parent_path += dir_name + "/";

    for (; list_iter != end_iter; ++list_iter) {
        
         const Node *pNode = *list_iter;
         
         if (dynamic_cast<const Directory *>(pNode)) {

               const Directory *p = static_cast<const Directory *>(pNode);
               DoRecursive(F, p, parent_path);
                              
         } else { 
             
            F(pNode, parent_path);
         }   
    }
}

template<typename F> void Directory::traverse(F& f)
{
   this->DoRecursive(f, this, std::string("")); 
}

inline Node &Directory::DirectoryIterator::operator *() const
{
  return *pCurrentNode;
}

inline Directory::DirectoryIterator::DirectoryIterator() : pDirectory(0), pCurrentNode(0), iters_stack()
{
}        

inline Directory::DirectoryIterator Directory::begin()
{
    return DirectoryIterator(*this); 
}

inline Directory::DirectoryIterator Directory::end()
{
    return DirectoryIterator(); 
}

inline bool Directory::DirectoryIterator::operator!=(const DirectoryIterator& rhs) const
{
    return !operator==(rhs);
}

inline Directory::ConstDirectoryIterator::ConstDirectoryIterator(const Directory & dir) : inner_iter(const_cast<Directory &>(dir))
{
    
}

inline Directory::ConstDirectoryIterator::ConstDirectoryIterator() : inner_iter()                          
{
}

inline Directory::ConstDirectoryIterator::ConstDirectoryIterator(const ConstDirectoryIterator& citer) : inner_iter(citer.inner_iter) 
{
}

inline Directory::ConstDirectoryIterator::ConstDirectoryIterator(const DirectoryIterator& iter) : inner_iter(iter) 
{
}

inline  Directory::ConstDirectoryIterator& Directory::ConstDirectoryIterator::operator++()
{
   ++inner_iter;
   return *this;
}

inline const Node &Directory::ConstDirectoryIterator::operator*() const
{
    return const_cast<const Node &>(*inner_iter);
} 
 
inline const Node *Directory::ConstDirectoryIterator::operator->() const  
{
     return const_cast<const Node *>(inner_iter.operator->());
}

inline bool Directory::ConstDirectoryIterator::operator==(const ConstDirectoryIterator& x) const
{
    return inner_iter == x.inner_iter;
}

inline bool Directory::ConstDirectoryIterator::operator!=(const ConstDirectoryIterator& x) const
{
     return inner_iter != x.inner_iter; 
}
inline Directory::ConstDirectoryIterator& Directory::ConstDirectoryIterator::operator=(const ConstDirectoryIterator& rhs)
{
    inner_iter = rhs.inner_iter;
    return *this;
}
       
#endif
