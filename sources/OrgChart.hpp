#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
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
    

    public:
        
        string* begin_preorder();
        string* end_print_level_order(); 
        string* reverse_order();
        string* begin_level_order();
        OrgChart();
        ~OrgChart();
        OrgChart &add_sub(string father, string son);
        OrgChart &add_root(string name);
        string* begin_reverse_order();
        friend ostream &operator<<(ostream &out,OrgChart &root);
        string* end_preorder();
        string* begin_print_level_order();
        string* end_level_order();
        string* begin(){
            return begin_level_order();
            }
        string* end(){
            return end_level_order();
            }
    private:
        vector<string> b_print_level_order;
        vector<string> b_preorder;
        vector<string> b_reverse_order;
        vector<string> b_level_order;
        Node root;
        void fill_q_for_print_level_order(Node &node, string s, bool isLast);
        bool find_sub(Node &node, string &father, string &son);
        void fill_q_for_reverse_order(Node &node);
        void fill_q_for_preorder(Node &node);
        void fill_q_for_level_order(Node &node);
        };

}