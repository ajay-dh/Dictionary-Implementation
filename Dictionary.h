//
//  Dictionary.h
//  PROJECT 4 REAL
//
//  Created by Ajayvir Dhaliwal on 6/4/18.
//  Copyright © 2018 Ajayvir Dhaliwal. All rights reserved.
//

#ifndef DICTIONARY_INCLUDED
#define DICTIONARY_INCLUDED

// Dictionary class for maintaining an anagram dictionary
//     Dictionary d;         // create an empty dictionary
//     d.insert("hello");    // insert "hello" into the dictionary
//     d.lookup("idte", f);  // call the function f for every anagram of "idte"
//                           //     found in the dictionary

#include <string>

class DictionaryImpl;

class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
    // We prevent a Dictionary object from being copied or assigned
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;
    
private:
    DictionaryImpl* m_impl;
};

#endif // DICTIONARY_INCLUDED

