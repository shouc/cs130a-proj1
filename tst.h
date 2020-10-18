//
// Created by Shou C on 10/6/20.
//

#ifndef CS130A_PROJ1_TST_H
#define CS130A_PROJ1_TST_H

#include "glob.h"

class node {
public:
    node* left;
    node* middle;
    node* right;
    node* parent;
    int l_count;
    std::string l_name;
    int r_count;
    std::string r_name;
    bool is_all_set;
};

class tst {
public:
    tst();
    node* root;
    int insert(std::string name);
    int search(std::string name);
    int decrease(std::string name);
    std::vector<std::pair<std::string, int> > range_search(std::string, std::string);
    ~tst();
};



#endif //CS130A_PROJ1_TST_H
