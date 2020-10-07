//
// Created by Shou C on 10/6/20.
//

#include "tst.h"
#include "glob.h"
#define _insert(loc) current_node->loc = insert_helper(current_node->loc, key, v);break;

// 0 -> key < l
// 1 -> key mid
// 2 -> key > r
inline int comp(node* n, std::string key) {
    if (key < n->l_name)
        return 0;
    if (key < n->r_name)
        return 1;
    return 2;
}

#define insert_to_node(key) \
    if (key < current_node->l_name) {\
        current_node->r_name = current_node->l_name; \
        current_node->l_name = key;\
        current_node->r_count = 1;\
    } else {\
        current_node->r_name = key;\
        current_node->r_count = 1;\
    }\
    current_node->is_all_set = true;\
    v = 1;\
    return current_node;


node* insert_helper(node* current_node, const std::string& key, int& v) {
    if (current_node == nullptr){
        node* new_node = new node;
        new_node->l_name = key;
        new_node->l_count = 1;
        new_node->r_count = 1;
        new_node->left = nullptr;
        new_node->middle = nullptr;
        new_node->right = nullptr;
        v = 1;
        return new_node;
    }
    if (key == current_node->l_name) {
        v = ++current_node->l_count;
        return current_node;
    }
    if (!current_node->is_all_set){
        insert_to_node(key)
    }
    if (key == current_node->r_name) {
        v = ++current_node->r_count;
        return current_node;
    }
    switch (comp(current_node, key)){
        case 0:
            _insert(left)
        case 1:
            _insert(middle)
        case 2:
            _insert(right)
    }
    return current_node;
}

int tst::insert(std::string name) {
    int v;
    this->root = insert_helper(this->root, name, v);
    return v;
}

int search_helper(node* current_node, const std::string& key){
    if (current_node == nullptr) return 0;
    if (key < current_node->l_name) return search_helper(current_node->left, key);
    if (key == current_node->l_name) return current_node->l_count;
    if (current_node->r_name.empty()) return 0;
    if (key > current_node->l_name && key < current_node->r_name)
        return search_helper(current_node->middle, key);
    if (key == current_node->r_name) return current_node->r_count;
    if (key > current_node->r_name) return search_helper(current_node->right, key);
    return 0;
}

int tst::search(std::string key) {
    return search_helper(this->root, key);
}

void dec_helper(node* current_node, std::string key, int& v) {
    if (current_node == nullptr) {
        v = 0;
        return;
    }
    if (key < current_node->l_name) return dec_helper(current_node->left, key, v);
    if (key == current_node->l_name) {
        v = --current_node->l_count;
        return;
    }
    if (current_node->r_name.empty()) {
        v = 0;
        return;
    }
    if (key > current_node->l_name && key < current_node->r_name)
        return dec_helper(current_node->middle, key, v);
    if (key == current_node->r_name) {
        v = --current_node->r_count;
        return;
    }
    if (key > current_node->r_name) return dec_helper(current_node->right, key, v);
}

int tst::decrease(std::string key) {
    int v;
    dec_helper(this->root, key, v);
    return v;
}

std::vector<std::pair<std::string, int>> cnter;


void range_search_helper(node* current_node, std::string start, std::string end){
    if (current_node == nullptr) return;
    if (start <= current_node->l_name && end >= current_node->l_name)
        cnter.emplace_back(current_node->l_name, current_node->l_count);

    if (start < current_node->l_name) {
        range_search_helper(current_node->left, start, end);
        range_search_helper(current_node->middle, start, end);
    }

    if (current_node->r_name.empty()) return;
    if (start <= current_node->r_name && end >= current_node->r_name)
        cnter.emplace_back(current_node->r_name, current_node->r_count);

    if (end > current_node->r_name) {
        range_search_helper(current_node->right, start, end);
    }
}

std::vector<std::pair<std::string, int>> tst::range_search(std::string start, std::string end) {
    range_search_helper(this->root, start, end);
    return cnter;
}




