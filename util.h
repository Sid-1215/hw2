#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> intsec;
  //create an iterator for s1 and s2
  typename std::set<T>::iterator i1 = s1.begin();
  typename std::set<T>::iterator i2 = s2.begin();

  while ((i1 != s1.end()) && (i2 != s2.end())) {
    if (*i1 < *i2) {
      ++i1; //move up in s1
    } else if (*i2 < *i1) {
      ++i2; //move up in s2
    } else {
      intsec.insert(*i1); //insert into the return set and increment both s1 and s2 iterators
      ++i1;
      ++i2;
    }
  }
  return intsec;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> uni;
  typename std::set<T>::iterator i;
  //insert all s1 values into i
  for (i = s1.begin(); i != s1.end(); ++i) {
    uni.insert(*i);
  } //insert all s2 values into i
  for (i = s2.begin(); i != s2.end(); ++i) {
    uni.insert(*i);
  }

  return uni;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
