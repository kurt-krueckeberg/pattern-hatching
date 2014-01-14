#include "filesyscmds.h"
#include <string>
#include "Directory.h"
using namespace std;

/* Evidently,...
 * When subpath("subdirA/subdirB/newsubDir") is first called, it returns everything after the first Node::directory_separator or "subDirB/newsubDir"; and head()
 * returns "subDirA" or everything before the first slash.
 * When subpath("subdirB/newsubDir") is next called, it returns "newsubDir"; and head() returns "subDirB".
 * When subpath("newsubDir") is next called, it returns an empty string because there is nothing after the slash.
 */ 
string subpath(const std::string& path)
{
   int slash_pos = path.find(Node::directory_separator);

   if (slash_pos != string::npos) {

       return path.substr(slash_pos + 1);

   } else {
       // return empty string
      return string(""); 
   }
}

string head(const std::string& path)
{
   int slash_pos = path.find(Node::directory_separator);

   if (slash_pos != string::npos) {

       return path.substr(0, slash_pos);

   } else {
       // return empty string?
      return string(""); 
  }
}
/*
 * pCurrentDir is the directory to search.  
 * Note: If mkdir() passes a File* as pCurrent instead of a Directory*, this will result in
 * File::getChild(int) throwing node_logic_error.
 */
Node *find(std::string& name, Node *pCurrent) 
{
  Node *pChild = 0;

  // getChild(int) returns 0 if no child found. 
  for (int i = 0; (pChild = pCurrent->getChild(i)); i++) {

       if (name == pChild->getName())  {
             
	    break;
       }                   
  } 

  return pChild;
}
/*
 * We must handle not only cases like
 *    mkdir newsubdir
 * but also
 *    mkdir subdirA/subdirB/newsubdir
 * Logic in the later case is:
 * 1. find subdirA (reporting and error if it doesn't exist)
 * 2. find subdirB (reporting and error if it doesn't exist)
 * 3. have subdirB add newsubdir to its children.
 *
 */
//--void mkdir(Node *pCurrent, const string& path)
Directory* mkdir(Node *pCurrent, const string& path)
{
   
   string sub_path = subpath(path); 

   if (sub_path.empty()) {

        // The time is hardcode for now
        Directory *pDir = new Directory(path, std::string("10/10/2013")); 
        pCurrent->adopt(pDir);
        return pDir;
      
   } else {

      string name = head(path); 

      Node *pChild = find(name, pCurrent);

      if (pChild) {

         return mkdir(pChild, sub_path);
         
      } else {

         cerr << name << " is  nonexistent." << endl;
         return 0; 
      }
   }
}

void ls(Node *, const std::string& options)
{
    // TODO
}