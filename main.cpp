#include <cstdlib>
#include <string>
#include "File.h"
#include "Directory.h"
#include "CompositePrinter.h"
#include "filesyscmds.h"
#include "SuffixPrintVisitor.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) 
{
    long file_size = 1000; // we hardcode the size
    
    try {
        
        File *ptop_f1 = new File(string("top-File1"), string("12-12-2013"), file_size);
        
        File *ptop_f2  = new File(string("top-File2"), string("12-10-2013"), file_size);
        
        Directory top(string("top-level-dir"), string("12-09-2013"));
        
        top.adopt(ptop_f1);
        top.adopt(ptop_f2);
        
        /* 
         * We could equivalently do this
         *      Node *psubdir_mid = top.getChild(2);
         * to get a pointer to Directory we just created, "subdir-mid" 
         */  
        Directory *psubdir_mid = mkdir(&top, "subdir-mid"); 
           
        Directory *psubdir_lower1 = mkdir(&top, "subdir-mid/subdir-lower1");
        
        /* Node *psubdir_lower1 = psubdir_mid->getChild(0); // alternative to line above. */

        File  *psubdir_lower1_f1 = new File(string("subdir-lower1-File1"), string("12-12-2013"), file_size);
        
        File  *psubdir_lower1_f2 = new File(string("subdir-lower1-File2"), string("12-10-2013"), file_size);
        
        psubdir_lower1->adopt(psubdir_lower1_f1);
        psubdir_lower1->adopt(psubdir_lower1_f2);
        
        File  *psubdir_mid_f1 = new File(string("subdir_mid-File1"), string("12-12-2013"), file_size);
    
        File  *psubdir_mid_f2 = new File(string("subdir-mid_File2"), string("12-10-2013"), file_size);
     
        psubdir_mid->adopt(psubdir_mid_f1);
        psubdir_mid->adopt(psubdir_mid_f2);

        mkdir(&top, "subdir-mid/subdir-lower2");

        /*
         * For illustration purposes only, we call 
         *     psubdir_mid->getChild(3)
         * instead of using the return value of mkdir. Note, the subdirectory subdir-lower2/ is the third child (we index starting
         * at zero) of its immediate parent subdir-mid/.
         */   
        
        Node *psubdir_lower2 = psubdir_mid->getChild(3);

        File  *psubdir_lower2_f1 = new File(string("subdir-lower2-File1"), string("12-12-2013"), file_size);
        
        File  *psubdir_lower2_f2 = new File(string("subdir-lower2-File2"), string("12-10-2013"), file_size);
        
        psubdir_lower2->adopt(psubdir_lower2_f1);
        psubdir_lower2->adopt(psubdir_lower2_f2);
              
        File *ptop_f3 = new File(string("top-File3"), string("12-12-2013"), file_size);
        
        File *ptop_f4  = new File(string("top-File4"), string("12-10-2013"), file_size);
        
        top.adopt(ptop_f3);
        top.adopt(ptop_f4);
        
        cout << "\n ===== top.traverse(CompositePrinter(cout))  =========== \n" << endl;
         
        CompositePrinter printer(cout);

        top.traverse(printer);        
                
        cout << "\n ===== top.print() =========== \n" << endl;

        top.print(cout); 
        
        cout << "\n ====== using external iterator Directory::iterator to loop over composite print to stdou and SuffixPrintVisitor to append Node type. ==== \n" << endl;
        
        Directory::iterator iter_current = top.begin();
        Directory::iterator iter_end = top.end();
        
        SuffixPrintVisitor spv(cout);
                        
        for (;iter_current != iter_end; ++iter_current) {
            
              cout <<  iter_current->getName(); 
              iter_current->accept(spv); 
              
              cout << endl;
        }
                
        cout << "\n ===== using external iterator Directory::const_iterator. Also using SuffixPrintVisitor  ======\n";
        
        const Directory& const_top = top;
        
        Directory::const_iterator const_iter_current = const_top.begin();
        Directory::const_iterator const_iter_end = const_top.end();

        for (;const_iter_current != const_iter_end; ++const_iter_current) {
              
              cout <<  const_iter_current->getName(); 
              const_iter_current->accept(spv); 
              cout << endl;
        }
            
    } catch (std::exception& e) {
            
          cout <<  e.what();
    }
   
    return 0;
}

