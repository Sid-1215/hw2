#include "clothing.h"
#include <sstream>
#include <iomanip>
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string& name, double price, int qty, 
          const std::string& size, const std::string& brand)
        : Product("clothing", name, price, qty), size_(size), brand_(brand)
{ }

Clothing::~Clothing() { }

std::set<std::string> Clothing::keywords() const {
  set<string> cKey;
  // break up clothing name and then add it to keywords list
  set<string> name = parseStringToWords(name_);
  cKey.insert(name.begin(), name.end());
  // break up brand name and then add it to keywords list
  set<string> brand = parseStringToWords(brand_);
  cKey.insert(brand.begin(), brand.end());

  return cKey;
}

std::string Clothing::displayString() const {
  stringstream ss;
  // print output in correct format with 2 decimal places
  ss << name_ << endl;
  ss << "Size: " << size_ << " Brand: " << brand_ << endl;
  ss << fixed << setprecision(2) << price_ << " " << qty_ << " left.";

  return ss.str();
}

void Clothing::dump(std::ostream& os) const {
  Product::dump(os);
  // add the item specific information
  os << size_ << endl;
  os << brand_ << endl;
}