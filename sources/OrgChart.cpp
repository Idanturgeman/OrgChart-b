// I got help from dvir gev about the data structures
#include "OrgChart.hpp"
using namespace std;

namespace ariel
{
    OrgChart::OrgChart(/* args */)
    {
        this->root.name = "";
    }

    OrgChart::~OrgChart()
    {
    }
    OrgChart &OrgChart::add_root(string name)
    {
        if(name.empty()){
           throw invalid_argument("this name is empty!");
        }
        this->root.name = move(name);
        return *this;
    }
    OrgChart &OrgChart::add_sub(string father, string son)
    {
        if(son.empty()){
            throw invalid_argument("this son is empty!");
        }
        if (!find_sub(this->root, father, son))
        {
            throw invalid_argument("you dont have this father");
        }
        return *this;
    }
    bool OrgChart::find_sub(Node &node, string &father, string &son)
    {
        int b = node.name.compare(father);
        if (b == 0)
        {
            Node temp;
            temp.name = son;
            node.sones.push_back(temp);
            return true;
        }
        for (size_t i = 0; i < node.sones.size(); i++)
        {
            if (find_sub(node.sones[i], father, son))
            {
                return true;
            }
        }
        return false;
    }

    // **************** fill for the q ******************
    // level order
    void OrgChart::fill_q_for_level_order(Node &node)
    {
        vector<Node *> q;
        q.push_back(&node);
        for (size_t i = 0; i < q.size(); i++)
        {
            Node *tmp = q[i];
            b_level_order.push_back(tmp->name);
            for (size_t j = 0; j < tmp->sones.size(); j++)
            {
                q.push_back(&(tmp->sones[j]));
            }
        }
    }
    // reverse order
    void OrgChart::fill_q_for_reverse_order(Node &node)
    {
        vector<Node *> q;
        q.push_back(&node);
        for (size_t i = 0; i < q.size(); i++)
        {
            Node *tmp = q[i];
            for (int j = int(tmp->sones.size() - 1); j >= 0; j--)
            {
                q.push_back(&(tmp->sones[(size_t)j]));
            }
        }
        for (int i = int(q.size() - 1); i >= 0; i--)
        {
            string n = q[(size_t)i]->name;
            b_reverse_order.push_back(n);
        }
    }
    // preorder
    void OrgChart::fill_q_for_preorder(Node &node)
    {
        b_preorder.push_back(node.name);
        for (size_t i = 0; i < node.sones.size(); i++)
        {
            fill_q_for_preorder(node.sones.at(i));
        }
    }
    // print
    void OrgChart::fill_q_for_print_level_order(Node &node, string s, bool isLast)
    {
        b_print_level_order.push_back(s);
        if (isLast)
        {
            b_print_level_order.push_back(" └─");
            s += "   ";
        }
        else
        {
            b_print_level_order.push_back(" ├─");
            s += " │ ";
        }
        b_print_level_order.push_back(node.name + "\n");
        for (size_t i = 0; i < node.sones.size(); i++)
        {
            bool j = (i == node.sones.size() - 1);
            fill_q_for_print_level_order(node.sones.at(i), s, j);
        }
    }
    // ******************* level order**************
    string *OrgChart::begin_level_order()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        this->b_level_order.clear();
        // this->b_level_order.push_back(this->root.name);
        fill_q_for_level_order(root);
        return &this->b_level_order[0];
    }
    string *OrgChart::end_level_order()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        return &this->b_level_order[this->b_level_order.size()];
    }
    // ******************* reverse order**************
    string *OrgChart::begin_reverse_order()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        this->b_reverse_order.clear();
        fill_q_for_reverse_order(root);
        return &b_reverse_order[0];
    }
    string *OrgChart::reverse_order()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        return &this->b_reverse_order[b_reverse_order.size()];
    }
    // ******************* preorder order**************
    string *OrgChart::begin_preorder()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        this->b_preorder.clear();
        fill_q_for_preorder(root);
        return &this->b_preorder[0];
    }
    string *OrgChart::end_preorder()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        return &this->b_preorder[b_preorder.size()];
    }
    // ******************* print order**************
    string *OrgChart::begin_print_level_order()
    {
        this->b_print_level_order.clear();
        fill_q_for_print_level_order(root, "", true);
        return &this->b_print_level_order[0];
    }
    string *OrgChart::end_print_level_order()
    {
        return &this->b_print_level_order[b_print_level_order.size()];
    }

    ostream &operator<<(ostream &out, OrgChart &root)
    {
        for (auto *i = root.begin_print_level_order(); i != root.end_print_level_order(); i++)
        {
            out << (*i);
        }
        return out;
    }

}