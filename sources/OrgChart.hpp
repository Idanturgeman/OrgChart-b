#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
using namespace std;


namespace ariel
{
    struct Node
    {
        string name;
        vector<Node> sones;
    };

    class OrgChart
    {
    private:
        Node root;
        bool find_sub(Node &node, string &father, string &son);
        void fill_q_for_level_order(Node &node);
        void fill_q_for_print_level_order(Node &node, string s, bool isLast);
        void fill_q_for_reverse_order(Node &node);
        void fill_q_for_preorder(Node &node);
        vector<string> b_level_order;
        vector<string> b_print_level_order;
        vector<string> b_reverse_order;
        vector<string> b_preorder;

    public:
        OrgChart();
        OrgChart &add_root(string name);
        OrgChart &add_sub(string father, string son);

        friend ostream &operator<<(ostream &out,OrgChart &root);
        string* begin_level_order();
        string* end_level_order();
        string* begin_print_level_order();
        string* end_print_level_order(); 
        string* begin_reverse_order();
        string* reverse_order();
        string* begin_preorder();
        string* end_preorder();
        string* begin(){
            return begin_level_order();
            }
        string* end(){
            return end_level_order();
            }

        ~OrgChart();
        };

}