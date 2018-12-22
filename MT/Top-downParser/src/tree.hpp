#pragma once

#include <graphviz/gvc.h>
#include <list>
#include <string>
#include <utility>

class tree
{
public:
    template <class... Children>
    tree(std::string && node, Children&&... children) : 
        _node(std::move(node))
    {
        init<Children...>(std::move(children)...);
    };
    
    tree(const tree & other) = default;
    tree(tree && other) noexcept;
    tree(std::string && node);
    std::string get_name();
    std::string to_str();
    void draw(std::string && filename);

private:
    template <class T, class... Children>
    void init(T&& t, Children&&... children)
    {
        _children.push_back(std::move(t));
        init<Children...>(std::move(children)...);
    };
    
    template <class T>
    void init(T&& t)
    {
        _children.push_back(std::move(t));
    };
    
    void rec_draw(Agraph_t* g, Agnode_t* agn, char* node);

    std::string _node;
    std::list<tree> _children;
};
