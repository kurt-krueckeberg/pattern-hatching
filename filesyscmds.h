#ifndef filesyscmds_h_897233834
#define filesyscmds_h_897233834
#include "Node.h"
#include <string>

std::string head(const std::string& path);
std::string subpath(const std::string& path);
Node *find(std::string& name, Node *pCurrent);
Directory *mkdir(Node *pCurrent, const std::string& subdir_name);
void ls(Node *, const std::string& options); 

#endif
