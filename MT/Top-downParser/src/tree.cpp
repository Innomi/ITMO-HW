#include <iostream>
#include "tree.hpp"

tree::tree(std::string && node) : _node(std::move(node)) {};

tree::tree(tree && other) noexcept : 
    _node(std::move(other._node)), _children(std::move(other._children)) {};
    
std::string tree::get_name()
{
    return _node;
};

std::string tree::to_str()
{
    std::string res = "\"" + _node + "\"(";
    for (tree & child : _children)
    {
        res += child.to_str() + ", ";
    }
    if (!_children.empty())
    {
        res.pop_back();
        res.pop_back();
    }
    res += ")";
    return res;
};

void tree::draw(std::string && filename)
{
    Agraph_t* g;
    GVC_t* gvc;
    gvc = gvContext();
    g = agopen("parse_tree", Agstrictdirected, NULL);
    agattr(g, AGNODE, "label", "");
    agattr(g, AGNODE, "color", "black");
    Agnode_t* agn = agnode(g, "", 1);
    rec_draw(g, agn, "");
    gvLayout(gvc, g, "dot");
    filename += ".png";
    gvRenderFilename(gvc, g, "png", filename.c_str());
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
};

void tree::rec_draw(Agraph_t* g, Agnode_t* agn, char* node)
{
    char* label = new char[_node.length() + 1];
    strcpy(label, _node.c_str());
    agset(agn, "label", label);
    if (_children.size() == 0)
    {
        agset(agn, "color", "red");
    }
    char* child_node = new char[256];
    strcpy(child_node, node);
    strcat(child_node, "_a");
    size_t len = strlen(child_node);
    for (tree & child : _children)
    {
        Agnode_t* child_agn = agnode(g, child_node, 1);
        agedge(g, agn, child_agn, "", 1);
        child.rec_draw(g, child_agn, child_node);
        size_t pos = len - 1;
        while (child_node[pos] == 'z')
        {
            child_node[pos] = 'a';
            --pos;
        }
        if (child_node[pos] == '_')
        {
            strcat(child_node, "a");
            ++len;
        }
        else
        {
            ++child_node[pos];
        }
    }
    delete[] label;
    delete[] child_node;
};
