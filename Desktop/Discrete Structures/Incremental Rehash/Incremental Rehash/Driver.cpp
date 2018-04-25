// File: Driver.cpp
//
// My test file
//
//
//


#include <iostream>
#include <cstdlib>
#include <set>
#include <string.h>
#include "words.h"
using namespace std ;

#include "HashTable.h"


int main() {
    HashTable T(107) ;
    
    
    
    cout<<"----------Original Table Inserts wrap around-----------"<<endl;
    cout<<endl;
    T.insert("Four");
    T.insert(words[43756]);
    T.insert("Mazda");
    T.insert(words[37359]);
    T.insert(words[29968]);
    T.insert(words[55238]);
    T.insert(words[6937]);
    T.insert(words[41772]);
    T.insert(words[19690]);
    T.insert(words[11045]);
    T.insert("tributes") ;	// 21
    T.insert("skulduggery") ;	// 22
    T.insert("convulse") ;	// 23
    T.insert("frothed") ;	// 24
    T.insert("horrify") ;	// 25
    T.insert("blackmailers") ;	// 26
    T.insert("defenestrated") ;	// 27
    T.insert("garrison") ;	// 23 -> 28
    T.insert("lidless") ;	// 22 -> 29
    T.insert("insanity") ;       // 105
    T.insert("enthronement") ;   // 105 -> 106
    T.insert("falsifiers") ;     // 105 -> 0
    T.insert("ignominious") ;    // 105 -> 1
    T.insert("mummified") ;      // 105 -> 2
    T.dump();
    
    const char* str;
    char* ptr;
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Search and Remove function also wrap around properly-----------"<<endl;
    
    if(T.find("mummified"))
    {
        cout<<"Found mummified"<<endl;
    }
    else
    {
        cout<<"mummified not found"<<endl;
    }
    
    ptr = T.remove(str= "mummified");
    if (ptr == NULL) {
        cout << "String " << str << " not found, not removed"<<endl;
    } else {
        cout << "Removed string = " << ptr << endl ;
        free(ptr) ;
    }
    
    T.dump();
    
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Should start a rehash-----------"<<endl;
    cout<<endl;
    T.insert("eye") ;            // 21 -> 30, should trigger inc. rehash
    T.dump();
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Multiple finds to consolidate down to one table-----------"<<endl;
    cout<<endl;
    if(T.find("Four"))
    {
        cout<<"Found Four"<<endl;
    }
    else
    {
        cout<<"Four not found"<<endl;
    }
    
    if(T.find("pillowcase"))
    {
        cout<<"Found pillowcase"<<endl;
    }
    else
    {
        cout<<"pillowcase not found"<<endl;
    }
    
    if(T.find("costed"))
    {
        cout<<"Found costed"<<endl;
    }
    else
    {
        cout<<"costed not found"<<endl;
    }
    
    if(T.find("unwarranted"))
    {
        cout<<"Found unwarranted"<<endl;
    }
    else
    {
        cout<<"unwarranted not found"<<endl;
    }
    
    if(T.find("regardless"))
    {
        cout<<"Found regardless"<<endl;
    }
    else
    {
        cout<<"regardless not found"<<endl;
    }
    
    if(T.find("Mazda"))
    {
        cout<<"Found Mazda"<<endl;
    }
    else
    {
        cout<<"Mazda not found"<<endl;
    }
    
    if(T.find("insanity"))
    {
        cout<<"Found insanity"<<endl;
    }
    else
    {
        cout<<"insanity not found"<<endl;
    }
    
    if(T.find("temp"))
    {
        cout<<"Found temp"<<endl;
    }
    else
    {
        cout<<"temp not found"<<endl;
    }
    
    T.dump();
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Multiple adds to trigger .5 size to capacity ratio rehash-----------"<<endl;
    cout<<endl;
    
    for(int i = 0; i < 38; i++)
    {
        T.insert(words[i]);
    }
    T.dump();
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Doing a couple of searches to rehash a couple objects-----------"<<endl;
    cout<<endl;
    
    if(T.find("aardwolf"))
    {
        cout<<"Found aardwolf"<<endl;
    }
    else
    {
        cout<<"aardwolf not found"<<endl;
    }
    T.find("abbreviated");
    T.find("skulduggery");
    T.find("Mazda");
    T.find("unwarranted");
    if(T.find("eye"))
    {
        cout<<"Found eye"<<endl;
    }
    else
    {
        cout<<"eye not found"<<endl;
    }
    if(T.find("temperature"))
    {
        cout<<"Found temperature"<<endl;
    }
    else
    {
        cout<<"temperature not found"<<endl;
    }
    if(T.find("heat"))
    {
        cout<<"Found heat"<<endl;
    }
    else
    {
        cout<<"heat not found"<<endl;
    }
    T.dump();
    
    
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Doing a couple of deletes to test if it works-----------"<<endl;
    cout<<endl;
    
    ptr = T.remove(str= "tributes");
    if (ptr == NULL) {
        cout << "String " << str << " not found, not removed"<<endl;
    } else {
        cout << "Removed string = " << ptr << endl ;
        free(ptr) ;
    }
    
    ptr = T.remove(str= "abashed");
    if (ptr == NULL) {
        cout << "String " << str << " not found, not removed"<<endl;
    } else {
        cout << "Removed string = " << ptr << endl ;
        free(ptr) ;
    }
    
    ptr = T.remove(str= "Mazda");
    if (ptr == NULL) {
        cout << "String " << str << " not found, not removed"<<endl;
    } else {
        cout << "Removed string = " << ptr << endl ;
        free(ptr) ;
    }
    
    T.dump();
    cout<<endl;
    cout<<endl;
    cout<<"----------Reinserting Mazda last time it had to probe to 89 from 88 should insert into 88 now-----------"<<endl;
    cout<<endl;
    
    T.insert("Mazda");
    T.dump();
    
    /*int hash;
     int code;
     for(int i = 0; i < 4000; i++)
     {
     hash = T.hashCode(words[i]);
     code = hash % 211;
     if(code == 177 || code == 176 || code == 179 || code == 180 || code == 183 || code == 184)
     {
     cout<<words[i]<<", "<<code<<endl;
     }
     }*/
    cout<<endl;
    cout<<endl;
    cout<<"----------Inserting to cause the second table to resort which will consolidate everything to 1 table-----------"<<endl;
    cout<<endl;
    
    T.insert("astounds");
    T.insert("avoidance");
    T.insert("bade");
    T.insert("baffler");
    T.insert("aristocracies");
    T.insert("ascender");
    T.dump();
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Copying the old object into a new object-----------"<<endl;
    cout<<endl;
    
    HashTable *T2ptr = new HashTable(T) ;
    HashTable T3(*T2ptr) ;
    delete T2ptr;
    
    bool isSame = true;
    if(T.A != NULL)
    {
        for(int i = 0; i < T.ACapacity; i++)
        {
            if(T.A[i] != NULL)
            {
                if(strcmp(T.A[i], T3.A[i]) != 0)
                {
                    isSame = false;
                }
            }
        }
    }
    if(T.B != NULL)
    {
        for(int i = 0; i < T.BCapacity; i++)
        {
            if(T.B[i] != NULL)
            {
                if(strcmp(T.B[i], T3.B[i]) != 0)
                {
                    isSame = false;
                }
            }
        }
    }
    if(T.C != NULL)
    {
        for(int i = 0; i < T.CCapacity; i++)
        {
            if(T.C[i] != NULL)
            {
                if(strcmp(T.C[i], T3.C[i]) != 0)
                {
                    isSame = false;
                }
            }
        }
    }
    if(isSame)
    {
        cout<<"T and T3 are identical"<<endl;
    }
    else{
        cout<<"T and T3 are not identical"<<endl;
    }
    
    HashTable T4;
    
    cout<<endl;
    cout<<endl;
    cout<<"----------Using the equals operator to copy the Hash Table-----------"<<endl;
    cout<<endl;
    
    T4 = T;
    
    isSame = true;
    if(T.A != NULL)
    {
        for(int i = 0; i < T.ACapacity; i++)
        {
            if(T.A[i] != NULL)
            {
                if(strcmp(T.A[i], T3.A[i]) != 0)
                {
                    isSame = false;
                }
            }
        }
    }
    if(T.B != NULL)
    {
        for(int i = 0; i < T.BCapacity; i++)
        {
            if(T.B[i] != NULL)
            {
                if(strcmp(T.B[i], T3.B[i]) != 0)
                {
                    isSame = false;
                }
            }
        }
    }
    if(T.C != NULL)
    {
        for(int i = 0; i < T.CCapacity; i++)
        {
            if(T.C[i] != NULL)
            {
                if(strcmp(T.C[i], T3.C[i]) != 0)
                {
                    isSame = false;
                }
            }
        }
    }
    if(isSame)
    {
        cout<<"T and T4 are identical"<<endl;
    }
    else{
        cout<<"T and T4 are not identical"<<endl;
    }
}





