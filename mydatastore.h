#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {
public: 
  MyDataStore();
  ~MyDataStore();
  // all of datastore's virtual functions
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);
  // addToCart function
  void addToCart(const std::string& username, Product* p);
  // viewCart function
  void viewCart(const std::string& username);
  // buyCart function
  void buyCart(const std::string& username);

private:
// need to store products in a vector, users in a map (for lookup),
// map of vectors for shopping cart 
  std::vector<Product*> products_;
  std::map<std::string, User*> users_;
  std::map<std::string, std::vector<Product*>> carts_;
// store all keywords in keyword index (store in map for quicker lookup)
  std::map<std::string, std::set<Product*>> keywords_;
};

#endif




