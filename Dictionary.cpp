//
//  Dictionary.cpp
//  PROJECT 4 REAL
//
//  Created by Ajayvir Dhaliwal on 6/4/18.
//  Copyright © 2018 Ajayvir Dhaliwal. All rights reserved.
//

// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
using namespace std;
const int TABLE_SIZE=50000;
const int HASH_DIVIDE=49993;// largest prime number under 50000
const int HASH_GEN[26]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};// hard coded array of first 26 prime numbers
void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);

// This class does the real work of the implementation.

class DictionaryImpl
{
public:
    DictionaryImpl():hash_table() {}; // sets all buckets to NULL in initializer list
    ~DictionaryImpl(){}; // default destructor of std::list takes care of destruction of list<buckets> in array
    void insert(string &word);// insert function
    void lookup(string &letters, void callback(string)) const; // lookup function that finds a matching anagram in dictionary
private:
    struct Bucket // data struct that holds string value, as well as the datas corresponding key in hash table
    {
        Bucket(string input, size_t inKey): val(input), key(inKey){ }
        string val;
        size_t key;
        size_t val_size= val.size();
    };
    size_t toHash(string word) const;
    list<Bucket> hash_table[TABLE_SIZE]; // closed hash table with 50,000 "buckets", represented by a list of buckets
};
size_t DictionaryImpl::toHash(string word) const // hash function using prime numbers
{
    removeNonLetters(word);
    size_t hash=1;
    for(int i=0; i<word.size();i++)
    {
        size_t hash_multiplier= HASH_GEN[word[i]-97];// multiplier starts from 0 as we subtracted using ASCII, yielding a prime number from the prime number array
        hash=hash*hash_multiplier;// multiply hash by the multipler
    }
    return hash% HASH_DIVIDE; //utilizing modulus operator, we return a hashed value of the word
}
void DictionaryImpl::insert(string &word)
{
    size_t key= toHash(word);// retrieve hash key
    hash_table[key].emplace_back(Bucket(word, key)); // construct a new bucket and push it into hash table
}
void DictionaryImpl::lookup(string &letters, void callback(string)) const
{
    if (callback == nullptr) // if callback functino returns null, end lookup algorithm
        return;
    if (letters.empty())// if there is no word to check, break
        return;
    size_t key= toHash(letters); //retrieve hash key
    for(list<Bucket>::const_iterator itr=hash_table[key].begin();itr!=hash_table[key].end(); ++itr) //iterate through hash table
    {
        removeNonLetters(letters);
        if(letters.size() == itr->val_size && key==itr->key) // if size of words and hash keys match
        {
            //second check- sort both words using std function and check wether they are the same
            string compare1 = letters;
            sort(compare1.begin(), compare1.end());
            string compare2 =(itr->val);
            sort(compare2.begin(), compare2.end());
            if (compare1 == compare2)
            {
               callback(itr->val); //if all conditions met, call parameter callback function
            }
            
        }
    }
    
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

// Each successive call to this function generates the next permutation of the
// characters in the parameter.  For example,
//    string s = "eel";
//    generateNextPermutation(s);  // now s == "ele"
//    generateNextPermutation(s);  // now s == "lee"
//    generateNextPermutation(s);  // now s == "eel"
// You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;
    
    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
