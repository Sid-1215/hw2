#include "book.h"
#include <sstream>
#include <iomanip>
#include "util.h"

using namespace std;

Book::Book(const std::string& name, double price, int qty, 
          const std::string& isbn, const std::string& author)
        : Product("book", name, price, qty), isbn_(isbn), author_(author)
{ }

Book::~Book() { }

std::set<std::string> Book::keywords() const {
  set<string> bKey;
  // break up book name and then add it to keywords list
  set<string> name = parseStringToWords(name_);
  bKey.insert(name.begin(), name.end());
  // break up author name and then add it to keywords list
  set<string> author = parseStringToWords(author_);
  bKey.insert(author.begin(), author.end());
  // in case the isbn has letters just lowercase it
  bKey.insert(convToLower(isbn_));

  return bKey;
}

std::string Book::displayString() const {
  stringstream ss;
  // print output in correct format with 2 decimal places
  ss << name_ << endl;
  ss << "Author: " << author_ << " ISBN: " << isbn_ << endl;
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

  return ss.str();
}

void Book::dump(std::ostream& os) const {
  Product::dump(os);
  // add the item specific information
  os << isbn_ << endl;
  os << author_ << endl;
}