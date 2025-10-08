#include <iomanip>
#include <iostream>
#include "util.h"
#include "mydatastore.h"
#include "datastore.h"

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
  // delete products_
  for (size_t i = 0; i <products_.size() ; i++) {
    delete products_[i];
  }
  // delete users_
  // since users_ is a map, use an iterator to go through it and delete each item
  for (map<string, User*>::iterator i = users_.begin(); i != users_.end() ; ++i) {
    delete i->second;
  }
}

// all of datastore's virtual functions
void MyDataStore::addProduct(Product* p) {
  // add p to product_
  products_.push_back(p);
  // get p's keywords
  set<string> pKeywords = p->keywords();
  // add each of p's keywords to keywords_
  for (set<string>::iterator i = pKeywords.begin(); i != pKeywords.end() ; ++i) {
    keywords_[*i].insert(p);
  }
}

void MyDataStore::addUser(User* u) {
  // u to users_
  // use u->getName and convToLower to insert u into users_
  users_[convToLower(u->getName())] = u;
}

// type 0 = AND search (intersection of results for each term) while
// type 1 = OR search (union of results for each term)
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  
  // create a return set for search result
  set<Product*> sResult;
  // case 1: no terms
  if (terms.empty()) {
    return vector<Product*>();
  }
  
  // case 2: 
    // get all products related to keyword terms[0]
    map<string, set<Product*>>::iterator it = keywords_.find(terms[0]);
    // check if .find() != .end()
    if (it != keywords_.end()) {
      sResult = it -> second;
    }
    // process all remaining terms, loop through
    for (size_t i = 1; i < terms.size(); i++) {
      set<Product*> set2; // acts as a comparison set to sResult

      it = keywords_.find(terms[i]);
      if (it != keywords_.end()) {
        set2 = it->second;
      }

      // type == 0 then do set intersection
      if (type == 0) {
        sResult = setIntersection(sResult, set2);
      } else if (type == 1) { // type == 1 then do set union
        sResult = setUnion(sResult, set2);
      }

      
    
    }
    vector<Product*> vResult(sResult.begin(), sResult.end());
    return vResult;

}

void MyDataStore::dump(std::ostream& ofile) {
  // write products 
  ofile << "<products>" << endl;
  // loop through products
  for (size_t i = 0; i < products_.size(); i++) {
    products_[i]->dump(ofile);
  }
  ofile << "</products>" << endl;

  // write users
  ofile << "<users>" << endl;
  // loop through users, using iterators since it is a map
  for (map<string, User*>::iterator i = users_.begin(); i !=users_.end(); ++i) {
    i->second->dump(ofile);
  }
  ofile << "</users>" << endl;
}

// addToCart function
void MyDataStore::addToCart(const std::string& username, Product* pAdd) {
  // convToLower(username)
  string user = convToLower(username);
  // check if username exists, if not return "Invalid username"
  if (users_.find(user) == users_.end()) {
    cout << "Invalid request" << endl;
    return;
  }
  // add product to user's cart
  carts_[user].push_back(pAdd);
}

// viewCart function
void MyDataStore::viewCart(const std::string& username) {
  // convToLower(username)
  string user = convToLower(username);
  // check if username exists, if not return "Invalid username"
  if (users_.find(user) == users_.end()) {
    cout << "Invalid username" << endl;
    return;
  }
  // get cart for user and loop through to print it
  vector<Product*>& cart = carts_[user];

  for (size_t i = 0; i < cart.size(); i++) {
    cout << "Item " << (i+1) << endl;
    cout << cart[i]->displayString() << endl;
    cout << endl;
  }
}

// buyCart function
void MyDataStore::buyCart(const std::string& username) {
  // convToLower(username)
  string user = convToLower(username);
  // check if username exists, if not return "Invalid username"
  if (users_.find(user) == users_.end()) {
    cout << "Invalid username" << endl;
    return;
  }
  // get cart 
  // get user
  User* u = users_[user];
  vector<Product*>& uCart = carts_[user];
  // go through cart in order:
  vector<Product*> itemsLeft;

  for (size_t i = 0; i < uCart.size(); i++) {
    Product* p = uCart[i];
    // (1) are there any p in stock
    // p->getQty() > 0
    // (2) does u have enough money for p
    // u->getBalance() >= p->getPrice()
    if ((p->getQty() > 0) && (u->getBalance() >= p->getPrice())) {
      // if (1) & (2) are true then subtractQty(1) & deductAmount(p->getPrice())
      p->subtractQty(1);
      u->deductAmount(p->getPrice());
    } else { // if not true then leave it in cart and goto the next item
      itemsLeft.push_back(p);
    }
  }

  carts_[user] = itemsLeft;
  
}