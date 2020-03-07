/*
    clearBiTree中data=0即为清空
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// #include <initializer_list>
#include "./stack.h"

// #define Status bool

template<typename Elemtype>
struct BiTNode
{
    Elemtype data;
    struct BiTNode *lChrilde;
    struct BiTNode *rChrilde;
    BiTNode():data(0),lChrilde(nullptr),rChrilde(nullptr) {};
    ~BiTNode(){};
};

template<typename Elemtype>
class BiTree
{
    private:
        
    public:
        BiTNode<Elemtype> *root;
        BiTree();
        ~BiTree();
        bool InitBiTree();
        bool DestoryBiTree();
        bool ClearBiTree();
        bool BiTreeEmpty();
        bool Assign(BiTNode<Elemtype>* p,Elemtype e);
        Elemtype Value(BiTNode<Elemtype>* p);
        //插入子树不为空=>false,插入子树为空=>true
        bool InsertChild(BiTNode<Elemtype>* p,int LR,BiTree<Elemtype>* t);
        bool DeleteChild(BiTNode<Elemtype>* p,int LR);
        int BiTreeDeepth();
        BiTNode<Elemtype> *Parent(BiTNode<Elemtype>* p);
        BiTNode<Elemtype> *LeftChild(BiTNode<Elemtype>* p);
        BiTNode<Elemtype> *RightChild(BiTNode<Elemtype>* p);
        BiTNode<Elemtype> *LeftSibling(BiTNode<Elemtype>* p);
        BiTNode<Elemtype> *RightSibling(BiTNode<Elemtype>* p);
        // Elemtype Value(int pos);
        template<int N>
        bool CreateBiTree(Elemtype (&define)[N]);
        template<typename Fun>
        bool PreOrderTraverse(Fun &visit);
        template<typename Fun>
        bool InOrderTraverse(Fun &visit);
        template<typename Fun>
        bool PostOrderTraverse(Fun &visit);
        // bool recursionCreateBiTree();
};

template<typename Elemtype>
BiTree<Elemtype>::BiTree():root(nullptr) {}

template<typename Elemtype>
BiTree<Elemtype>::~BiTree()
{
}


template<typename Elemtype>
bool BiTree<Elemtype>::InitBiTree(){
    root = new BiTNode<Elemtype>;
    return root == nullptr?false:true;
}

template<typename Elemtype>
bool BiTree<Elemtype>::DestoryBiTree(){
    //???
    delete this;
    return true;
}

template<typename Elemtype>
bool BiTree<Elemtype>::ClearBiTree(){
    auto fun = [](BiTNode<Elemtype>* p){
        p->data = 0;
    };
    return PreOrderTraverse(fun) ? true : false;
}

template<typename Elemtype>
bool BiTree<Elemtype>::BiTreeEmpty(){
    return root == nullptr ? true : false;
}

template<typename Elemtype>
int BiTree<Elemtype>::BiTreeDeepth(){
    int maxDeepth = 0,curDeepth = 0;
    auto fun = [&maxDeepth,&curDeepth](BiTNode<Elemtype>* p){
        static Stack<BiTNode<Elemtype>*> S;
        //第一次才初始化栈,并判断是否树空，不空入栈
        if(maxDeepth == 0)
        {
            InitStack<bool,BiTNode<Elemtype>*>(S);
            if(p == nullptr)
                return 0;
            Push<bool,BiTNode<Elemtype>*>(S,p);
            curDeepth++;
        }
        else
        {
            int i;
            bool pop = false;
            StackNode<BiTNode<Elemtype>*>* tmp = S.base;
            for (i = 0; tmp != S.top; i++)
            {
                // std::cout<<&(S.base[1])<<"  "<<S.top<<sizeof(StackNode<Elemtype>);
                if(p == tmp->data->rChrilde){
                    pop = true;
                    S.top = tmp->next;
                    Push<bool,BiTNode<Elemtype>*>(S,p);
                    curDeepth = i + 1;
                    break;
                }
                tmp = tmp->next;
            }
            if(!pop){
                Push<bool,BiTNode<Elemtype>*>(S,p);
                curDeepth++;
            }
        }
        if(curDeepth > maxDeepth)
            maxDeepth = curDeepth;
    };
    PreOrderTraverse(fun);
    // std::cout<<maxDeepth;
    return maxDeepth;
}

template<typename Elemtype>
Elemtype BiTree<Elemtype>::Value(BiTNode<Elemtype>* p){
    if(p == nullptr)
        return (Elemtype)'#';
    else
        return p->data;
}

template<typename Elemtype>
bool BiTree<Elemtype>::Assign(BiTNode<Elemtype>* p,Elemtype e){
    if(p == nullptr)
        return false;
    else
    {
        p->data = e;
        return true;
    }
    
}

template<typename Elemtype>
BiTNode<Elemtype>* BiTree<Elemtype>::Parent(BiTNode<Elemtype>* p){
    if(p == nullptr){
        return nullptr;
    }
    BiTNode<Elemtype> *node = nullptr;
    auto fun = [&node,&p](BiTNode<Elemtype>* tmp){
        if(tmp->lChrilde == p || tmp->rChrilde == p){
            node = tmp;
        }
    };
    PreOrderTraverse(fun);
    return node;
}

template<typename Elemtype>
BiTNode<Elemtype>* BiTree<Elemtype>::LeftChild(BiTNode<Elemtype>* p){
    if(p == nullptr){
        return nullptr;
    }
    BiTNode<Elemtype> *node = nullptr;
    auto fun = [&node,&p](BiTNode<Elemtype>* tmp){
        if(tmp == p){
            node = tmp->lChrilde;
        }
    };
    PreOrderTraverse(fun);
    return node;
}

template<typename Elemtype>
BiTNode<Elemtype>* RightChild(BiTNode<Elemtype>* p){
    if(p == nullptr){
        return nullptr;
    }
    BiTNode<Elemtype> *node = nullptr;
    auto fun = [&node,&p](BiTNode<Elemtype>* tmp){
        if(tmp == p){
            node = tmp->rChrilde;
        }
    };
    PreOrderTraverse(fun);
    return node;
}

template<typename Elemtype>
BiTNode<Elemtype>* BiTree<Elemtype>::LeftSibling(BiTNode<Elemtype>* p){
    if(p == nullptr){
        return nullptr;
    }
    BiTNode<Elemtype> *node = nullptr;
    auto fun = [&node,&p](BiTNode<Elemtype>* tmp){
        if(tmp->rChrilde == p){
            node = tmp->lChrilde;
        }
    };
    PreOrderTraverse(fun);
    return node;
}

template<typename Elemtype>
BiTNode<Elemtype>* BiTree<Elemtype>::RightSibling(BiTNode<Elemtype>* p){
    if(p == nullptr){
        return nullptr;
    }
    BiTNode<Elemtype> *node = nullptr;
    auto fun = [&node,&p](BiTNode<Elemtype>* tmp){
        if(tmp->lChrilde == p){
            node = tmp->rChrilde;
        }
    };
    PreOrderTraverse(fun);
    return node;
}

template<typename Elemtype>
bool BiTree<Elemtype>::InsertChild(BiTNode<Elemtype>* p,int LR,BiTree<Elemtype>* t){
    if (LR > 1 || LR < 0 || t->root == nullptr)
        // std::cout<<"\nfalse"<<std::endl;
        return false;
    else if( (LR == 0 && p->lChrilde == nullptr) || (LR == 1 && p->rChrilde == nullptr) ){
        BiTNode<Elemtype>** pp = LR == 0 ? &(p->lChrilde) : &(p->rChrilde);
        *pp = t->root;
        return true;
    }
    else
        return false;
    
}

template<typename Elemtype>
bool BiTree<Elemtype>::DeleteChild(BiTNode<Elemtype>* p,int LR){
    if (LR > 1 || LR < 0 || root == nullptr)
        // std::cout<<"\nfalse"<<std::endl;
        return false;
    else if( (LR == 0 && p->lChrilde != nullptr) || (LR == 1 && p->rChrilde != nullptr) ){
        BiTNode<Elemtype>** pp = LR == 0 ? &(p->lChrilde) : &(p->rChrilde);
        BiTree<Elemtype> tmpTree;
        auto fun = [](BiTNode<Elemtype>* p){
            delete p;
        };
        tmpTree.InitBiTree();
        tmpTree.root = *pp;
        tmpTree.PostOrderTraverse(fun);
        *pp = nullptr;
        return true;
    }
    else
        return false;
}

template<typename Elemtype>
template<typename Fun>
bool BiTree<Elemtype>::PreOrderTraverse(Fun &visit){
    // Stack<BiTNode<Elemtype>*> S;
    // InitStack<bool,BiTNode<Elemtype>*>(S);
    // BiTNode<Elemtype> *p = root;
    // while (p != nullptr)
    // {
    //     visit(p);
    //     if(p->rChrilde != nullptr) 
    //         Push<bool,BiTNode<Elemtype>*>(S,p->rChrilde);

    //     if(p->lChrilde != nullptr) 
    //         p = p->lChrilde;
    //     else
    //         if(!Pop<bool,BiTNode<Elemtype>*>(S,p))
    //             p = nullptr;
    // }
    Stack<BiTNode<Elemtype>*> S;
    InitStack<bool,BiTNode<Elemtype>*>(S);
    BiTNode<Elemtype> *p = root;
    while (p || !StackEmpty<bool,BiTNode<Elemtype>*>(S)){
        if (p != nullptr){
            //存入栈中  
            Push<bool,BiTNode<Elemtype>*>(S,p);
            //访问节点
            visit(p);
            //遍历左子树  
            p = p->lChrilde;
         }
        else{
            //退栈
            Pop<bool,BiTNode<Elemtype>*>(S,p); 
            //访问右子树  
            p = p->rChrilde;
        }
    }
    return true;
}
template<typename Elemtype>
template<typename Fun>
bool BiTree<Elemtype>::InOrderTraverse(Fun &visit){
    Stack<BiTNode<Elemtype>*> S;
    InitStack<bool,BiTNode<Elemtype>*>(S);
    BiTNode<Elemtype> *p = root;

    /*功能没问题，但是却是失败的实践,实现复杂了
        while (p != nullptr )
        {
                左不空往左走 左为空visit根 右不空右为根 右空pop到右不空
                四种情况
                左 中 右
                0  1  0 =>visit中 出栈直到右不为空的设右为根
                0  1  1 =>右为根 continue
                1  1  0 =>继续左
                1  1  1 =>继续左
            
            if(p->lChrilde == nullptr){
                visit(p);
            }
            //我故意放出来的，为了好看。。。
            //前面是左为空和不为空的情况，后面是左为空 && 右 空||不空 的情况
            if(p->lChrilde == nullptr && p->rChrilde == nullptr){
                while( Pop<bool,BiTNode<Elemtype>*>(S,p) && p->rChrilde == nullptr ){
                    visit(p);
                }
                //遍历结束的标志是左右为空&&栈空
                //还有一种只有左子树循环到顶栈空
                if(StackEmpty<bool,BiTNode<Elemtype>*>(S)){
                    break;
                }
                if( p->rChrilde != nullptr ){
                    visit(p);
                    p = p->rChrilde;
                }
            }
            else if(p->lChrilde == nullptr && p->rChrilde != nullptr){
                p = p->rChrilde;
            }
            else
            {
                Push<bool,BiTNode<Elemtype>*>(S,p);
                p = p->lChrilde;
            }
        }
    */
   while (p || !StackEmpty<bool,BiTNode<Elemtype>*>(S)){
        if (p != nullptr){
            //存入栈中  
            Push<bool,BiTNode<Elemtype>*>(S,p);
            //遍历左子树  
            p = p->lChrilde;
         }
        else{
            //退栈
            Pop<bool,BiTNode<Elemtype>*>(S,p);
            //对树中的结点进行操作
            visit(p); 
            //访问右子树  
            p = p->rChrilde;
        }
    }
    return true;
}
template<typename Elemtype>
template<typename Fun>
bool BiTree<Elemtype>::PostOrderTraverse(Fun &visit){
    //tmp
        // Stack<BiTNode<Elemtype>*> S,tmp;
        // InitStack<bool,BiTNode<Elemtype>*>(S);
        // InitStack<bool,BiTNode<Elemtype>*>(tmp);
        // BiTNode<Elemtype> *p= root,*preP = p;
        // while (p || !StackEmpty<bool,BiTNode<Elemtype>*>(S)){
        //     if (p != nullptr){
        //         //存入栈中  
        //         Push<bool,BiTNode<Elemtype>*>(S,p);
        //         Push<bool,BiTNode<Elemtype>*>(tmp,p);
        //         //遍历左子树  
        //         preP = p;
        //         p = p->lChrilde;
        //      }
        //     else{
        //         //退栈
        //         Pop<bool,BiTNode<Elemtype>*>(S,p);
        //         if(index<BiTNode<Elemtype>*>(tmp,p) < index<BiTNode<Elemtype>*>(tmp,preP)){
        //                 // BiTNode<Elemtype> *pp = preP;
        //             int i = index<BiTNode<Elemtype>*>(tmp,preP);
        //             while ( (index<BiTNode<Elemtype>*>(tmp,preP) - 1) != index<BiTNode<Elemtype>*>(tmp,p))
        //             {
        //                 visit(preP);
        //                 Pop<bool,BiTNode<Elemtype>*>(tmp,preP);
        //             }
        //         }
        //         //对树中的结点进行操作
        //         // visit(p); 
        //         //访问右子树  
        //         p = p->rChrilde;
        //     }
        //}
    //tmp
    Stack<BiTNode<Elemtype>*> S,tmp;
    InitStack<bool,BiTNode<Elemtype>*>(S);
    InitStack<bool,BiTNode<Elemtype>*>(tmp);
    BiTNode<Elemtype> *p = root;
    while (p || !StackEmpty<bool,BiTNode<Elemtype>*>(S)){
        if (p != nullptr){
            //存入栈中  
            Push<bool,BiTNode<Elemtype>*>(S,p);
            Push<bool,BiTNode<Elemtype>*>(tmp,p);
            //遍历右子树  
            p = p->rChrilde;
         }
        else{
            //退栈
            Pop<bool,BiTNode<Elemtype>*>(S,p);
            //访问左子树  
            p = p->lChrilde;
        }
    }
    while (!StackEmpty<bool,BiTNode<Elemtype>*>(tmp))
    {
        Pop<bool,BiTNode<Elemtype>*>(tmp,p);
        visit(p);
    }
    
    return true;
}

//非递归
template<typename Elemtype>
template<int N>
bool BiTree<Elemtype>::CreateBiTree(Elemtype (&define)[N]){
    //早期实现，过于复杂   
        // int i = 0;
        // BiTNode<Elemtype> *p = new BiTNode<Elemtype>;
        // if(define[i] != 0)
        //     root = p;
        // else{
        //     delete p;
        //     return true;
        // }
        // Stack<BiTNode<Elemtype>*> S;
        // InitStack<bool,BiTNode<Elemtype>*>(S);
        // while (p != nullptr || !StackEmpty<bool,BiTNode<Elemtype>*>(S))
        // {
        //     p->data = define[i];
        //     if(define[i+1] != 0){
        //         Push<bool,BiTNode<Elemtype>*>(S,p);
        //         p->lChrilde = new BiTNode<Elemtype>;
        //         p = p->lChrilde;
        //     }
        //     else
        //     {
        //         int j;
        //         for (j = 2; define[i+j] == 0 && (i+j) < sizeof(define) / sizeof(Elemtype); j++)
        //         {
        //             Pop<bool,BiTNode<Elemtype>*>(S,p);
        //         }
        //         if((i+j) == sizeof(define) / sizeof(Elemtype))
        //             break;
        //         p->rChrilde = new BiTNode<Elemtype>;
        //         p = p->rChrilde;
        //         //because the end of while has a i++;
        //         i += j-1;
        //     }
        //     i++;
        // }
        // return true;
    //
    // 优化版本，感觉失败了。。。
    int i = 0;
    Stack<BiTNode<Elemtype>*> S;
    InitStack<bool,BiTNode<Elemtype>*>(S);
    BiTNode<Elemtype> *p = new BiTNode<Elemtype>;
    if(define[i] != 0)
        root = p;
    else{
        delete p;
        return false;
    }
    // std::cout<<sizeof(define) / sizeof(define[0]);
    while (i < sizeof(define) / sizeof(define[0]) - 2 || !StackEmpty<bool,BiTNode<Elemtype>*>(S)){
        if (define[i+1] != '#'){
            p->data = define[i];
            Push<bool,BiTNode<Elemtype>*>(S,p); 
            p->lChrilde = new BiTNode<Elemtype>;
            p = p->lChrilde;
            i++;
        }
        else if(define[i+2] != '#'){
            p->data = define[i];
            p->rChrilde = new BiTNode<Elemtype>;
            p = p->rChrilde;
            i+=2;
        }
        else
        {
            p->data = define[i];
            i+=3;
            Pop<bool,BiTNode<Elemtype>*>(S,p);
            while (define[i] == '#' && !StackEmpty<bool,BiTNode<Elemtype>*>(S))
            {
                Pop<bool,BiTNode<Elemtype>*>(S,p);
                i++;
            }
            if(define[i] != '#'){
                p->rChrilde = new BiTNode<Elemtype>;
                p = p->rChrilde;
            }
        }
    }
    return true;
}

template<typename Elemtype>
bool recursionCreateBiTree(BiTNode<Elemtype> *&p){
    Elemtype elem;
    std::cin>>elem;
    //?
    elem = (Elemtype)elem;
    if(elem == '#') p = nullptr;
    else
    {
        if( !(p = new BiTNode<Elemtype>) ) return false;
        p->data = elem;
        recursionCreateBiTree<Elemtype>(p->lChrilde);
        recursionCreateBiTree<Elemtype>(p->rChrilde);
    }
    return true;
}
//输入要遍历的树与遍历方式 0：先序 1：中序 2：后序
template<typename Elemtype>
bool printTree(BiTree<Elemtype> T,int i){
    auto fun = [](BiTNode<Elemtype>* p){
        std::cout<<p->data;
    };
    switch (i)
    {
    case 0:
        T.PreOrderTraverse(fun);
        break;
    case 1:
        T.InOrderTraverse(fun);
        break;
    case 2:
        T.PostOrderTraverse(fun);
        break;
    default:
        std::cout<<"input number error";
        break;
    }
    // T.PostOrderTraverse(fun);
    return true;
}

int main(){
    // int a[] = {1,2,3,4,0,0,5,0,0,6,7,0,0,8,0,0,9,10,11,0,0,12,0,0,13,14,0,0,15,0,0};
    // char a[] = {'a','b','c','#','#','d','#','#','#'};
    // char a[] = {'a','b','c','d','#','#','#','#','#'};
    BiTree<char> Tree,t;
    Tree.InitBiTree();
    // t.InitBiTree();
    recursionCreateBiTree<char>(Tree.root);
    Tree.DeleteChild(Tree.root,0);
    // std::cout<<"\nnext"<<std::endl;
    // recursionCreateBiTree<char>(t.root);
    // std::cout<<"\ndone"<<std::endl;
    // if(Tree.InsertChild(Tree.root,1,&t))
    //     std::cout<<"\nInsert ok"<<std::endl;
    // Tree.CreateBiTree(a);
    // printTree<char>(Tree,0);
    // Tree.ClearBiTree();
    // Tree.BiTreeDeepth();
    // BiTNode<char> *tmp = Tree.Parent(Tree.root->lChrilde->lChrilde);
    // if(tmp != nullptr)
    //     std::cout<<tmp->data;
    // else
    //     std::cout<<"mdzz";
    printTree<char>(Tree,0);
    system("pause");
    return 0;
}
