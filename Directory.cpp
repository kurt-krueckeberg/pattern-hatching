#include "Directory.h"
#include <stack>
#include <iostream>
#include <iterator>

using namespace std;

// Return the child, or 0 if not found.
Node *Directory::getChild(int i) throw(node_logic_error, out_of_range)
{
    // check if i is in range
    int size = nodeList.size();

    if ( i >= size || i < 0) {
        
        throw out_of_range("the index is out of range");
    }

    list<Node *>::iterator iter = nodeList.begin();
    list<Node *>::iterator iter_end = nodeList.end();
    
    Node *pNode = 0;
    
    for(auto index = 0;  iter != iter_end; ++iter, ++index) {
        
           pNode = *iter;    
           
           if (i == index){
               break;
           }
    }

    return pNode;
}
/*
 * getSize() is defined recursively.
 */
long Directory::getSize() const throw(node_logic_error)
{ 
    long total = 0;

    int size = nodeList.size();

    //--list<Node *>::iterator iter = nodeList.begin();
    //--list<Node *>::iterator iter_end = nodeList.end();
    list<Node *>::const_iterator iter = nodeList.begin();
    list<Node *>::const_iterator iter_end = nodeList.end();
    
    for(; iter != iter_end; ++iter) {
        
           const Node *child = *iter;    
           total += child->getSize(); 
    }

    return total;
}

/*
 * 
 */
void Directory::remove(Node *pNode) throw(node_logic_error, invalid_argument)
{
    // make sure it exists
    list<Node *>::iterator iter = nodeList.begin();
    list<Node *>::iterator iter_end = nodeList.end();
    
    for(; iter != iter_end; ++iter) {
        
           if (pNode == *(iter.operator->())) { // DirectoryIterator::operator->() returns Node **    
               
              nodeList.remove(pNode);
              return;
           } 
    }

    throw invalid_argument("The node at that address is not a child");
}
    
Directory::Directory(const std::string& dir_name, const std::string& created) : name(dir_name), date_created(created)
{    
}

void Directory::adopt(Node *pNode) throw(node_logic_error)
{
    nodeList.push_back(pNode);
}

Directory::const_iterator Directory::begin() const
{
    return ConstDirectoryIterator(*this); 
}

Directory::const_iterator Directory::end() const
{
    return ConstDirectoryIterator(); 
}
 
/*
bool Directory::DirectoryIterator::hasNext()
{
   if (iters_stack.empty()) {

	return false;

   } else {

	pair<list<Node*>::iterator, list<Node*>::iterator>& pair_ = iters_stack.top();
        list<Node*>::iterator& list_iter = pair_.first;
        list<Node*>::iterator& list_iter_end = pair_.second;

	 if (list_iter == list_iter_end) {

	     iters_stack.pop();

	     return hasNext();

	} else {

	      return true;
	}
   }
}

Node *Directory::DirectoryIterator::next()
{
  if (hasNext()) {

        list<Node*>::iterator& list_iter = iters_stack.top().first;
        list<Node*>::iterator& list_iter_end = iters_stack.top().second;

        Node *pNode = *list_iter;
        ++list_iter; 

        if (dynamic_cast<Directory *>(pNode)) {

             Directory *pDir = static_cast<Directory *>(pNode);
             iters_stack.push( make_pair(pDir->nodeList.begin(), pDir->nodeList.end()) );
        }

        return pNode; 
 
  } else {

     return 0;
  }
}
*/

//  Since base class destructor is virtual, this will cause recursive descent
Directory::~Directory()
{
  list<Node*>::iterator list_iter     = nodeList.begin();
  list<Node*>::iterator list_iter_end = nodeList.end();

  for (;list_iter != list_iter_end; ++list_iter) { 
  
     delete *list_iter; 
  }   
}

/* Succcessfully tested
 * prints in-order. Thus, if dir1 and dir2 were added to top/ before file top_f1, the output will look like:
  top/
  top/dir1
  top/dir1/dir_f1
  top/dir2
  top/dir2/dir2_f1
  top/top_f1
 */ 
void Directory::print(Directory *pdir, string path) const
{
    pdir = (pdir != 0) ? pdir : const_cast<Directory *>(this);
    
    list<Node *>::iterator list_iter = pdir->nodeList.begin();
    list<Node *>::iterator end_iter = pdir->nodeList.end();
    
    string dir_name = pdir->getName();
                
    path += dir_name + "/";
        
    cout << path << "\n";

    for (; list_iter != end_iter; ++list_iter) {
        
         Node *pNode = *list_iter;
         
         if (dynamic_cast<Directory *>(pNode)) {

               Directory *p = static_cast<Directory *>(pNode);
               print(p, path);
               
         } else { 
             
            cout << path << pNode->getName() << "\n"; 
         }   
    }
    
    return;
}


Directory::DirectoryIterator::DirectoryIterator(const DirectoryIterator& rhs) : pDirectory(rhs.pDirectory), pCurrentNode(rhs.pCurrentNode),
        iters_stack(rhs.iters_stack) 
{
} 

Directory::DirectoryIterator::DirectoryIterator(Directory& dir) : pDirectory(&dir) 
{
  iters_stack.push(make_pair(dir.nodeList.begin(), dir.nodeList.end()) ); 
  pCurrentNode = pDirectory; 
}

Directory::DirectoryIterator& Directory::DirectoryIterator::operator=(const DirectoryIterator& rhs)
{
  pCurrentNode = rhs.pCurrentNode;
  pDirectory = rhs.pDirectory;        
  iters_stack = rhs.iters_stack; 
  return *this;
}

bool Directory::DirectoryIterator::operator==(const DirectoryIterator& rhs) const
{
 /* 
  * pCurentNode is only set to 0 when we we have iterated over the entire composite. It is also implies iters_stack.empty() will be true, so
  * we do not have to separately check for that here.  
  */
   
  bool bReturn;
  if (rhs.pDirectory == 0) { // implies this is an end() iterator...
      // ...and simply need to check that pCurrentNode is 0, which only occurs when iters_stack is empty and we have iterated
      // over the entire composite
      bReturn = pCurrentNode == 0;
        
  } else { // otherwise, we need to check that 
     // 1. are iterating over the same composite: pDirectory == rhs.pDirectory, and
     // 2. we are at the same Node.
        
     bool bReturn = (pDirectory == rhs.pDirectory && pCurrentNode == rhs.pCurrentNode);
   }
    
   return bReturn; 
}

Node *Directory::DirectoryIterator::operator->() const
{
  if (!iters_stack.empty()) {

     return pCurrentNode;

  } else {

     return 0;
  } 
}
 
Directory::DirectoryIterator&  Directory::DirectoryIterator::operator++() 
{
  if (iters_stack.empty()) {

        pCurrentNode = 0;

  } else {

	list<Node*>::iterator& list_iter     = iters_stack.top().first;
	list<Node*>::iterator& list_iter_end = iters_stack.top().second;
        
	 if (list_iter == list_iter_end) {

	     iters_stack.pop();

	     return this->operator++(); // recurse

	} else {
              /* pCurrentNode initially to this->pDirectory in ctor. */
              
              pCurrentNode = *list_iter; 
              ++list_iter;  

              if (dynamic_cast<Directory *>(pCurrentNode)) {

                  Directory *pDir = static_cast<Directory *>(pCurrentNode);
                  iters_stack.push( make_pair(pDir->nodeList.begin(), pDir->nodeList.end()) );
              }
	}
  }
  
  return *this;
}

Directory::iterator  Directory::DirectoryIterator::operator++(int) //postfix
{
   DirectoryIterator tmp(*this);
   ++*this;
   return tmp;
}

Directory::ConstDirectoryIterator Directory::ConstDirectoryIterator::operator++(int) //postfix
{
   ConstDirectoryIterator tmp(*this);
   ++*this;
   return tmp;
}
