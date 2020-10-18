//
// Created by Shou C on 10/6/20.
//

#include "tst.h"
#include "glob.h"
#define _insert(loc) current_node->loc = insert_helper(current_node, current_node->loc, key, v);break;

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
        current_node->r_count = current_node->l_count;\
        current_node->l_name = key;\
        current_node->l_count = 1;\
    } else {\
        current_node->r_name = key;\
        current_node->r_count = 1;\
    }\
    v = 1;\
    return current_node;


node* insert_helper(node* parent, node* current_node, const std::string& key, int& v) {
    if (current_node == nullptr){
        node* new_node = new node;
        new_node->l_name = key;
        new_node->l_count = 1;
        new_node->r_count = 0;
        new_node->left = nullptr;
        new_node->middle = nullptr;
        new_node->right = nullptr;
        new_node->parent = parent;
        v = 1;
        return new_node;
    }
    if (key == current_node->l_name) {
        v = ++current_node->l_count;
        return current_node;
    }
    if (current_node->l_count == 0 || current_node->r_count == 0){
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
    this->root = insert_helper(nullptr, this->root, name, v);
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


#define node_pair std::pair<node*, node*>

node_pair find_largest(node* current_node){
    if (current_node->right == nullptr)
        return std::make_pair(nullptr, current_node);
    if (current_node->right != nullptr && current_node->right->right == nullptr)
        return std::make_pair(current_node, current_node->right);
    return find_largest(current_node->right);
}

node_pair find_smallest(node* current_node){
    if (current_node->left == nullptr){
        return std::make_pair(nullptr, current_node);
    }
    if (current_node->left != nullptr && current_node->left->left == nullptr){
        return std::make_pair(current_node, current_node->left);
    }
    return find_smallest(current_node->left);
}
#define del_release(d1,d2) \
    if (ns.first == nullptr){\
        delete current_node->d1;\
        current_node->d1 = nullptr;\
    } else {\
        delete ns.first->d2;\
        ns.first->d2 = nullptr;\
    }
bool delete_helper(node* current_node, bool is_left){
    if (current_node->left == nullptr && current_node->middle == nullptr && current_node->right == nullptr){
        if (is_left) {
            if (current_node->r_count == 0){
                return true;
            } else {
                current_node->l_count = current_node->r_count;
                current_node->l_name = current_node->r_name;
                current_node->r_count = 0;
                current_node->r_name = "";
            }
        } else {
            current_node->r_name = "";
            current_node->r_count = 0;
        }
    } else {
        if (is_left) {
            if (current_node->left != nullptr){
                bool use_left = false;
                node_pair ns = find_largest(current_node->left);
                node* largest_node = ns.second;
                if (largest_node->r_count == 0) use_left = true;
                if (use_left){
                    current_node->l_name = largest_node->l_name;
                    current_node->l_count = largest_node->l_count;
                } else {
                    current_node->l_name = largest_node->r_name;
                    current_node->l_count = largest_node->r_count;
                }

                if (delete_helper(largest_node, use_left)){
                    del_release(left, right)
                }
            } else if (current_node->middle != nullptr){
                node_pair ns =find_smallest(current_node->middle);
                node* smallest_node = ns.second;
                current_node->l_name = smallest_node->l_name;
                current_node->l_count = smallest_node->l_count;
                if (delete_helper(smallest_node, true)){
                    del_release(middle, left)
                }
            } else {
                bool use_left = false;
                node_pair ns = find_largest(current_node->right);
                node* largest_node = ns.second;
                if (largest_node->r_count == 0)
                    use_left = true;
                current_node->l_name = current_node->r_name;
                current_node->l_count = current_node->r_count;
                if (use_left){
                    current_node->r_name = largest_node->l_name;
                    current_node->r_count = largest_node->l_count;
                } else {
                    current_node->r_name = largest_node->r_name;
                    current_node->r_count = largest_node->r_count;
                }
                current_node->middle = current_node->right;
                current_node->right = nullptr;
                if (delete_helper(largest_node, use_left)){
                    if (ns.first == nullptr){
                        delete current_node->middle;
                        current_node->middle = nullptr;
                    } else {
                        delete ns.first->right;
                        ns.first->right = nullptr;
                    }
                }
            }
        } else {
            if (current_node->right != nullptr){
                node_pair ns = find_smallest(current_node->right);
                node* smallest_node = ns.second;
                current_node->r_name = smallest_node->l_name;
                current_node->r_count = smallest_node->l_count;
                if (delete_helper(smallest_node, true)){
                    del_release(right, left)
                }
            } else if (current_node->middle != nullptr){
                bool use_left = false;
                node_pair ns = find_largest(current_node->middle);
                node* largest_node = ns.second;
                if (largest_node->r_count == 0) use_left = true;
                if (use_left){
                    current_node->r_name = largest_node->l_name;
                    current_node->r_count = largest_node->l_count;
                } else {
                    current_node->r_name = largest_node->r_name;
                    current_node->r_count = largest_node->r_count;
                }
                if (delete_helper(largest_node, use_left)){
                    del_release(middle, right)
                }
            } else {
                node_pair ns = find_smallest(current_node->left);
                node* smallest_node = ns.second;
                current_node->r_name = current_node->l_name;
                current_node->r_count = current_node->l_count;
                current_node->l_name = smallest_node->l_name;
                current_node->l_count = smallest_node->l_count;
                current_node->middle = current_node->left;
                current_node->left = nullptr;
                if (delete_helper(smallest_node, true)){
                    if (ns.first == nullptr){
                        delete current_node->middle;
                        current_node->middle = nullptr;
                    } else {
                        delete ns.first->left;
                        ns.first->left = nullptr;
                    }
                }
            }
        }
    }
    return false;
}


int dec_helper(node* parent, int l, node* current_node, std::string key){
    if (current_node == nullptr) {
        return 0;
    }
    if (key < current_node->l_name) return dec_helper(current_node, 1, current_node->left, key);
    if (key == current_node->l_name) {
        int v = --current_node->l_count;
        if (v == 0) {

            if (delete_helper(current_node, true)){
                assert(l != 0);
                switch (l){
                    case 1:
                        delete parent->left;
                        parent->left = nullptr;
                        break;
                    case 2:
                        delete parent->middle;
                        parent->middle = nullptr;
                        break;
                    case 3:
                        delete parent->right;
                        parent->right = nullptr;
                        break;
                }
            }
        }
        return v;
    }
    if (current_node->r_name.empty()) {
        return 0;
    }
    if (key > current_node->l_name && key < current_node->r_name)
        return dec_helper(current_node, 2, current_node->middle, key);
    if (key == current_node->r_name) {
        int v = --current_node->r_count;
        if (v == 0) {
            if (delete_helper(current_node, false)){
                assert(l != 0);
                switch (l){
                    case 1:
                        delete parent->left;
                        parent->left = nullptr;
                        break;
                    case 2:
                        delete parent->middle;
                        parent->middle = nullptr;
                        break;
                    case 3:
                        delete parent->right;
                        parent->right = nullptr;
                        break;
                }
            }
        }
        return v;
    }
    if (key > current_node->r_name) return dec_helper(current_node, 3, current_node->right, key);
}


int tst::decrease(std::string key){
    if (root){
        if (root->l_name == key && root->l_count == 1 && root->r_name.empty()){
            delete root;
            root = nullptr;
            return 0;
        }
    }
    int i;
    return dec_helper(nullptr, 0, this->root, key);
}



//void dec_helper(node* current_node, std::string key, int& v) {
//    if (current_node == nullptr) {
//        v = 0;
//        return;
//    }
//    if (key < current_node->l_name) return dec_helper(current_node->left, key, v);
//    if (key == current_node->l_name) {
//        v = --current_node->l_count;
//        return;
//    }
//    if (current_node->r_name.empty()) {
//        v = 0;
//        return;
//    }
//    if (key > current_node->l_name && key < current_node->r_name)
//        return dec_helper(current_node->middle, key, v);
//    if (key == current_node->r_name) {
//        v = --current_node->r_count;
//        return;
//    }
//    if (key > current_node->r_name) return dec_helper(current_node->right, key, v);
//}
//
//int tst::decrease(std::string key) {
//    int v;
//    dec_helper(this->root, key, v);
//    return v;
//}


#define rr_result std::vector<std::pair<std::string, int> >

void range_search_helper(node* current_node, std::string start, std::string end, rr_result& cnter){
    if (current_node == nullptr) return;

    if (current_node->l_name > start){
        range_search_helper(current_node->left, start, end, cnter);
    }

    if (start <= current_node->l_name && end >= current_node->l_name)
        cnter.emplace_back(current_node->l_name, current_node->l_count);
    if (!(current_node->l_name > end || current_node->r_name < start))
        range_search_helper(current_node->middle, start, end, cnter);

    if (current_node->r_name.empty()) return;

    if (start <= current_node->r_name && end >= current_node->r_name)
        cnter.emplace_back(current_node->r_name, current_node->r_count);

    if (current_node->r_name < end) {
        range_search_helper(current_node->right, start, end, cnter);
    }
}
rr_result tst::range_search(std::string start, std::string end) {
    rr_result cnter;
    range_search_helper(this->root, start, end, cnter);
    return cnter;
}


void del_helper(node* current_node){
    if (current_node == nullptr) return;
    del_helper(current_node->left);
    del_helper(current_node->right);
    del_helper(current_node->middle);
    delete current_node;
}
tst::~tst() {
    del_helper(root);
}

tst::tst() {
    root = nullptr;
}




