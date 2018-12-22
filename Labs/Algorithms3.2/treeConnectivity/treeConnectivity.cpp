/*
                             ****XXXXXXXX***                            
                        ***XXXXXXXXXX########XX*                        
                    ****XXXXXXXX################XX**                    
                  *XXXXXXXXXX#######################X**                 
              **XXXXXXXXX##############################X*               
            **XXXXXXX#######X##XXXX######################X*             
         *X*****XXXXXXXXXXXXXXXXX##########################X*           
       *X##XX*****XXXXXXXXXX#################################*          
      XX#X##X#XX**          *****XXXXX########################*         
     X#######XXX**                    ***XXXX##################*        
    *########XXX*                         ****XX################        
    X####X##XXX*                               **XX#############X       
    X####XXXX**                                   **X###########X       
    X###XXXX*                                        *X######X#X#*      
    X#XXXXXX                                           *XX#X***X#X      
    X######X*                                            *******X#      
    *######X*                                                 **X#      
    *X##X#X*                                    ****************XX      
     X##XX*                         ***********XXXXXXXXXXXXXX****X      
     *XXX*                  **XXXXXXXXXXX***XX########XXXXXXXXX**X      
      *XX*           ******XXXX#########X****X#####XXXX####XXXX***      
      ****         **X***X#X*XXX#######X*    X###XXX***XXXXXXX******    
                   ***X#XX**  ****XXXXX*     *XXXXXX*****X**XX****XX    
   XX**             *X*     ***XX**X**        ***XXX*XXX**********X*    
  *XXX**                  **********          **************** ****     
  *XX*  **               *********             ********************     
   *****X*                  **                  *****    *********      
    ** *X*                                       ****    *********      
                        *          *            ******************      
           *          *          **X*  *******XXXXXXXX***********       
                           *  ****X***X############X*************       
                           * ******  X##############X************       
                              ***    X##############X***********        
                                     XXX###########XX***********        
                                    **XXX##XXX####XXXXXX********        
                                  **XXXX*******X**XXXXXXXX******         
                                *XX****   **XXXXXXXXX**********         
                              ***** * ****XXXXXXXXXXXXXX*******         
                            *************XX**XX***********XXXX#*        
                           *******                  ****XXXXX##X*       
                         ********               *****XXXXX#####XXX*     
                         ***XX*****        ******XXXXXX#########XXX*    
                          *****XXXX***XXXXXXXXXXXXX##############XXXX*  
                            ****XXXXXXX############################XXXX*
                  *         ***XXXXXX#X###########################XXXXXX
                  *         ***XXXX###############################XXXXXX
                   *         **XXX##################################XXXX
*/
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct node
{
    node* r;
    node* l;
    node* p;
    unsigned int from;
    unsigned int to;
    
    node(unsigned int from_, unsigned int to_)
    {
        from = from_;
        to = to_;
        r = nullptr;
        l = nullptr;
        p = nullptr;
    }
};

unordered_map<long long unsigned int, node*> edges;

void zig(node* x) //NAS POSADYAT!!!
{
    node* p = x->p;
    if (p->l == x)
    {
        p->l = x->r;
        if(p->l != nullptr)
        {
            p->l->p = p;
        }
        x->p = nullptr;
        p->p = x;
        x->r = p;
    }
    else
    {
        p->r = x->l;
        if(p->r != nullptr)
        {
            p->r->p = p;
        }
        x->p = nullptr;
        p->p = x;
        x->l = p;
    }
}

void zig_zig(node* x) //NAS TOCHNO POSADYAT!!!
{
    node* p = x->p;
    node* g = x->p->p;
    if (p->l == x)
    {
        x->p = g->p;
        if (x->p != nullptr)
        {
            if (g->p->l == g)
            {
                x->p->l = x;
            }
            else
            {
                x->p->r = x;
            }
        }
        g->p = p;
        g->l = p->r;
        if (g->l != nullptr)
        {
            g->l->p = g;
        }
        p->p = x;
        p->l = x->r;
        if (p->l != nullptr)
        {
            p->l->p = p;
        }
        p->r = g;
        x->r = p;
    }
    else
    {
        x->p = g->p;
        if (x->p != nullptr)
        {
            if (g->p->l == g)
            {
                x->p->l = x;
            }
            else
            {
                x->p->r = x;
            }
        }
        g->p = p;
        g->r = p->l;
        if (g->r != nullptr)
        {
            g->r->p = g;
        }
        p->p = x;
        p->r = x->l;
        if (p->r != nullptr)
        {
            p->r->p = p;
        }
        p->l = g;
        x->l = p;
    }
}

void zig_zag(node* x) //NU VSE, ETO KONEC...
{
    node* p = x->p;
    node* g = x->p->p;
    if (p->r == x)
    {
        g->l = x->r;
        if (g->l != nullptr)
        {
            g->l->p = g;
        }
        p->r = x->l;
        if (p->r != nullptr)
        {
            p->r->p = p;
        }
        x->p = g->p;
        if (x->p != nullptr)
        {
            if (g->p->l == g)
            {
                x->p->l = x;
            }
            else
            {
                x->p->r = x;
            }
        }
        g->p = x;
        p->p = x;
        x->r = g;
        x->l = p;
    }
    else
    {
        g->r = x->l;
        if (g->r != nullptr)
        {
            g->r->p = g;
        }
        p->l = x->r;
        if (p->l != nullptr)
        {
            p->l->p = p;
        }
        x->p = g->p;
        if (x->p != nullptr)
        {
            if (g->p->l == g)
            {
                x->p->l = x;
            }
            else
            {
                x->p->r = x;
            }
        }
        g->p = x;
        p->p = x;
        x->l = g;
        x->r = p;
    }
}

void splay(node* x)
{
    while (x->p != nullptr)//BA-DUM-TS
    {
        if (x->p->p == nullptr)
        {
            zig(x);
        }
        else
        {
            if ((x == x->p->l) == (x->p == x->p->p->l))
            {
                zig_zig(x);
            }
            else
            {
                zig_zag(x);
            }
        }
    }
}

void merge(node* u, node* v)
{
    if (v != nullptr && u != nullptr)
    {
        splay(v);
        while (u->p != nullptr)//BA-DUM-TS
        {
            u = u->p;
        }
        while (u->r != nullptr)//BA-DUM-TS
        {
            u = u->r;
        }
        splay(u);
        u->r = v;
        v->p = u;
    }
}

node* split(node* u)
{
    splay(u);
    node* res = u->r;
    if (res != nullptr)
    {
        res->p = nullptr;
        u->r = nullptr;
    }
    return res;
}

bool isConnected(node* u, node* v)
{
    if (u != nullptr && v != nullptr)
    {
        while(u->p != nullptr)//BA-DUM-TS
        {
            u = u->p;
        }
        while(v->p != nullptr)//BA-DUM-TS
        {
            v = v->p;
        }
        return (v == u);
    }
    else
    {
        return false;
    }
}

long long unsigned int evaluateEdge(long long unsigned int a, long long unsigned int b)
{
    return a * 1000000 + b;
}

void dfs(node* v)
{
    if (v->l != nullptr)
    {
        dfs(v->l);
    }
    cout << v->from << ' ' << v->to << endl;
    if (v->p != nullptr && v->p->l != v && v->p->r != v)
    {
        cout << v->from << ' ' << v->to << " PLOHO " << v->p->from << ' ' << v->p->to << ' ' << v->p->l->from << ' ' << v->p->l->to << endl;
    }
    if (v->r != nullptr)
    {
        dfs(v->r);
    }
}

void link(unsigned int x, unsigned int y)
{
    node* u = edges[evaluateEdge(x, x)];
    node* v = edges[evaluateEdge(y, y)];
    node* temp1 = split(u);
    node* to = new node(x, y);
    edges.insert(make_pair(evaluateEdge(x, y), to));
    merge(u, to);
    node* temp2 = split(v);
    merge(to, temp2);
    merge(to, v);
    node* from = new node(y, x);
    edges.insert(make_pair(evaluateEdge(y, x), from));
    merge(v, from);
    merge(from, temp1);
}

void cut(unsigned int x, unsigned int y)
{
    node* u = edges[evaluateEdge(x, y)];
    node* v = edges[evaluateEdge(y, x)];
    node* temp1 = split(u);
    node* del;
    if (u->l != nullptr)
    {
        u = u->l;
        del = u->p;
        u->p = nullptr;
    }
    else
    {
        del = u;
        u = nullptr;
    }
    edges.erase(evaluateEdge(del->from, del->to));
    delete del;
    if (isConnected(temp1, v))
    {
        node* temp2 = split(v);
        v = v->l;
        del = v->p;
        v->p = nullptr;
        edges.erase(evaluateEdge(del->from, del->to));
        delete del;
        merge(u, temp2);
    }
    else
    {
        split(v);
        if (v->l != nullptr)
        {
            v = v->l;
            del = v->p;
            v->p = nullptr;
        }
        else
        {
            del = v;
            v = nullptr;
        }
        edges.erase(evaluateEdge(del->from, del->to));
        delete del;
        merge(v, temp1);
    }
}

int main()
{
    size_t n, m;
    unsigned int x, y;
    string command;
    cin >> n >> m;
    for (size_t i = 0; i < n; ++i)
    {
        edges.insert(make_pair(evaluateEdge(i, i), new node(i, i)));
    }
    for (size_t i = 0; i < m; ++i)
    {
        cin >> command >> x >> y;
        --x;
        --y;
        if (command == "link")
        {
            link(x, y);
        }
        else
        {
            if (command == "cut")
            {
                cut(x, y);
            }
            else
            {
                cout << isConnected(edges[evaluateEdge(x, x)], edges[evaluateEdge(y, y)]) << endl;
            }
        }
    }
    return 0;
}
