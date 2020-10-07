//
// Created by Shou C on 10/6/20.
//

#include "glob.h"
#include "tst.h"
#define eval \
    if (action == "lookup"){\
        int t = ntst->search(input1);\
        if (t > 0)\
            printf("%s found, count = %d\n", input1.c_str(), t);\
        else printf("%s not found\n", input1.c_str());\
    }\
    if (action == "insert"){\
        printf("%s inserted, new count = %d\n", input1.c_str(), ntst->insert(input1));\
    }\
    if (action == "delete"){\
        int t = ntst->decrease(input1);\
        if (t > 0)\
            printf("%s deleted, new count = %d\n", input1.c_str(), t);\
        else printf("%s deleted\n", input1.c_str());\
    }\
    if (action == "rangesearch"){\
        auto t = ntst->range_search(input1, input2);\
        for (int i = 0; i < t.size(); ++i) {\
            printf("%s\n", t[i].first.c_str());\
        }\
    }
int main(int argc, char *argv[]){
    auto ntst = new tst();
//    ntst->insert("hello");
//    ntst->insert("hello");
//    ntst->insert("yesterday");
//    ntst->insert("yesterday");
//    ntst->insert("yesterday");
//    ntst->insert("band");
//    ntst->insert("bankers");
//    ntst->insert("bat");
//    ntst->insert("cab");
    std::string action = "";
    bool action_set = false;
    std::string input1 = "";
    bool input1_set = false;
    bool last_comma = false;
    std::string input2 = "";
    std::string inp = argv[1];

    for (char& c: inp) {
        switch (c){
            case ' ':
                if (last_comma) {
                    last_comma = false;
                    break;
                }
                if (action == "range") break;
                if (action_set) {
                    if (input1_set && input2 == "to")
                        input2 = "";
                    input1_set = true;
                } else {
                    action_set = true;
                }
                break;
            case ',':
                eval
                action_set = false;
                input1_set = false;
                action = "";
                input1 = "";
                input2 = "";
                last_comma = true;
                break;
            default:
                if (!action_set) action += c;
                else if (!input1_set) input1 += c;
                else input2 += c;
                break;
        }
    }
    eval
//    ntst->insert("c");
//    ntst->insert("b");
//    ntst->insert("c");
//    ntst->insert("d");
//    ntst->insert("d");
//    ntst->insert("d");
//    ntst->insert("d");
//    ntst->insert("d");
//    ntst->insert("b");
//    ntst->insert("a");
//    ntst->insert("a");
//    ntst->decrease("d");
//    ntst->range_search("a", "f");
//    printf("%d", ntst->search("d"));

//    printf("%d", ntst->search("hello"));
//    printf("%d", ntst->insert("goodbye"));
//    printf("%d", ntst->decrease("yesterday"));
//    printf("%d", ntst->insert("hello"));
//    printf("%d", ntst->decrease("goodbye"));
//    ntst->range_search("band", "cat");
}