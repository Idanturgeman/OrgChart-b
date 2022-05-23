// I got help from dvir gev about the data structures
#include "OrgChart.hpp"
using namespace std;

namespace ariel
{
    static int numOfOrgCharts = 0;
    OrgChart::OrgChart(/* args */)
    {
        numOfOrgCharts++;
        this->root.name = "";
    }

    OrgChart::~OrgChart()
    {
        numOfOrgCharts--;
    }
    static int numOfRoots = 0;
    OrgChart &OrgChart::add_root(string name)
    {
        if(name.empty()){
           throw invalid_argument("this name is empty!");
        }
        this->root.name = move(name);
        numOfRoots++;
        return *this;
    }
    static int numOfSubs = 0;
    OrgChart &OrgChart::add_sub(string father, string son)
    {
        if(son.empty()){
            throw invalid_argument("this son is empty!");
        }
        numOfSubs++;
        if (!find_sub(this->root, father, son))
        {
            throw invalid_argument("you dont have this father");
        }
        return *this;
    }
    int fnd = 0;
    bool OrgChart::find_sub(Node &node, string &father, string &son)
    {
        int ans = 0;
        int b = node.name.compare(father);
        if (b == 0)
        {
            ans++;
            Node temp;
            temp.name = son;
            node.sones.push_back(temp);
            return true;
        }
        int fnd = 0;
        for (size_t i = 0; i < node.sones.size(); i++)
        {
            fnd++;
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
        int level = 0;
        vector<Node *> q;
        q.push_back(&node);
        for (size_t i = 0; i < q.size(); i++)
        {
            level++;
            Node *tmp = q[i];
            b_level_order.push_back(tmp->name);
            int fqflo = 0;
            for (size_t j = 0; j < tmp->sones.size(); j++)
            {
                fqflo++;
                q.push_back(&(tmp->sones[j]));
            }
        }
    }
    // reverse order
    void OrgChart::fill_q_for_reverse_order(Node &node)
    {
        int rvrs = 0;
        vector<Node *> q;
        q.push_back(&node);
        for (size_t i = 0; i < q.size(); i++)
        {
            rvrs++;
            Node *tmp = q[i];
            for (int j = int(tmp->sones.size() - 1); j >= 0; j--)
            {
                rvrs++;
                q.push_back(&(tmp->sones[(size_t)j]));
            }
        }
        int temp = 0;
        for (int i = int(q.size() - 1); i >= 0; i--)
        {
            rvrs++;
            string n = q[(size_t)i]->name;
            b_reverse_order.push_back(n);
        }
    }
    // preorder
    int pre = 0;
    void OrgChart::fill_q_for_preorder(Node &node)
    {
        int fqfp = 0;
        b_preorder.push_back(node.name);
        for (size_t i = 0; i < node.sones.size(); i++)
        {
            pre++;
            fill_q_for_preorder(node.sones.at(i));
        }
    }
    // print
    void OrgChart::fill_q_for_print_level_order(Node &node, string s, bool isLast)
    {
        int fqfplo = 0;
        b_print_level_order.push_back(s);
        int levelOrder = 0;
        if (isLast)
        {
            fqfplo++;
            b_print_level_order.push_back(" └─");
            s += "   ";
        }
        else
        {
            fqfplo++;
            b_print_level_order.push_back(" ├─");
            s += " │ ";
        }
        int p = 0; 
        b_print_level_order.push_back(node.name + "\n");
        for (size_t i = 0; i < node.sones.size(); i++)
        {
            levelOrder++;
            bool j = (i == node.sones.size() - 1);
            fill_q_for_print_level_order(node.sones.at(i), s, j);
        }
    }
    // ******************* level order**************
    string *OrgChart::begin_level_order()
    {
        int begin = 0;
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        int level = 0;
        this->b_level_order.clear();
        // this->b_level_order.push_back(this->root.name);
        fill_q_for_level_order(root);
        return &this->b_level_order[0];
    }
    string *OrgChart::end_level_order()
    {
        int end = 0;
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        return &this->b_level_order[this->b_level_order.size()];
    }
    // ******************* reverse order**************
    string *OrgChart::begin_reverse_order()
    {
        int bro = 0;
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
        int ro = 0;
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        return &this->b_reverse_order[b_reverse_order.size()];
    }
    // ******************* preorder order**************
    int bp = 0;
    string *OrgChart::begin_preorder()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        this->b_preorder.clear();
        fill_q_for_preorder(root);
        bp++;
        return &this->b_preorder[0];
    }
    int ep = 0;
    string *OrgChart::end_preorder()
    {
        if (root.name.empty())
        {
            throw invalid_argument("the tree is empty!");
        }
        ep++;
        return &this->b_preorder[b_preorder.size()];
    }
    // ******************* print order**************
    string *OrgChart::begin_print_level_order()
    {
        int bplo = 0;
        this->b_print_level_order.clear();
        fill_q_for_print_level_order(root, "", true);
        return &this->b_print_level_order[0];
    }
    string *OrgChart::end_print_level_order()
    {
        int eplo = 0;
        return &this->b_print_level_order[b_print_level_order.size()];
    }

    ostream &operator<<(ostream &out, OrgChart &root)
    {
        int os = 0;
        for (auto *i = root.begin_print_level_order(); i != root.end_print_level_order(); i++)
        {
            out << (*i);
        }
        return out;
    }

}