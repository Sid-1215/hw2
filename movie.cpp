#include "movie.h"
#include <sstream>
#include <iomanip>
#include "util.h"

using namespace std;

Movie::Movie(const std::string& name, double price, int qty, 
          const std::string& genre, const std::string& rating)
        : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{ }

Movie::~Movie() { }

std::set<std::string> Movie::keywords() const {
  set<string> mKey;
  // break up movie name and then add it to keywords list
  set<string> name = parseStringToWords(name_);
  mKey.insert(name.begin(), name.end());
  // convert genre to lowercase and then add it
  mKey.insert(convToLower(genre_));

  return mKey;
}

std::string Movie::displayString() const {
  stringstream ss;
  // print output in correct format with 2 decimal places
  ss << name_ << endl;
  ss << "Genre: " << genre_ << " Rating: " << rating_ << endl;
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

  return ss.str();
}

void Movie::dump(std::ostream& os) const {
  Product::dump(os);
  // add the item specific information
  os << genre_ << endl;
  os << rating_ << endl;
}