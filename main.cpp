//
//  main.cpp
//  BinaryTrees
//
//  Created by RAMAN TYAGI on 24/08/21.
//  Copyright © 2021 RAMAN TYAGI. All rights reserved.
//
/*
 ##########################################################
 -->Generic tress mein base condition ki zarurat nhi hoti kyuki uska for loop jo children pe lgta hai vo chlta hi ni hai agr children nhi hai !!
 -->Pr Binary Trees ke case mein base condition lgani pdegi kyuki function recursively chlega or Null pe pauch jaega -> infinite loop chl jaega agr base condition nhi lgayi to!!
 ##########################################################
~~~~~~~~~~~~~CONSTRUCTOR OF A BINARY TREE~~~~~~~~~~~~~~~~~~
 INTUITION:
 ##
 Pair class{
 Node *node
 int state;
 }
 ##
 0. if arr[i] == -1 then check for state!
 1.If state == 0 left mein push krke state bdha do & i++
 2.If state == 1 right mein push krke state bdha do & i++
 3.If state == 2 Sirf pop krna hai!
 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include <iostream>
#include<stack>
#include<queue>
using namespace std;
class Node
{
public:
    Node *left;
    int data;
    Node *right;
};
class Pair
{
public:
    Node *t;
    int state;
};
/*
~~PreOrder mein traverse krte jao Or left -> data <- right print krte jao ~~
 */
void Display(Node *p)
{
    if(p==NULL)
        return;
    if(p->left!=NULL)
        cout<<p->left->data;
    else
        cout<<".";
    cout<<"->"<<p->data<<"<-";
    if(p->right!=NULL)
        cout<<p->right->data;
    else
        cout<<".";
    cout<<"\n";
    Display(p->left);
    Display(p->right);
}
/*
 ~~~~~~~~Recursion->FAITH(HIGH LEVEL THINKING)~~~~~~~~~~~~~
 Size --> left ka size lao + right ka size lao +1 krke return !
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int Size(Node *p)
{
    if(p==NULL)
        return 0;
    int x = Size(p->left);
    int y = Size(p->right);
    return x+y+1;
}
/*
~~~~~~~~Recursion->FAITH(HIGH LEVEL THINKING)~~~~~~~~~~~~~
SUM --> left ka sum lao + right ka sum lao + p->data krke return !
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int Sum(Node *p)
{
    if(p==NULL)
        return 0;
    int x = Sum(p->left);
    int y = Sum(p->right);
    return x+y+p->data;
}
/*
~~~~~~~~Recursion->FAITH(HIGH LEVEL THINKING)~~~~~~~~~~~~~
MAX --> left ka max lao , right ka max lao , p->data teeno mein check kro jo maximum h use return !
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int Max(Node *p)
{
    if(p==NULL)
        return INT_MIN;
    int x = Max(p->left);
    int y = Max(p->right);
    return max(max(x,y),p->data);
}
/*
~~~~~~~~Recursion->FAITH(HIGH LEVEL THINKING)~~~~~~~~~~~~~
HEIGHT --> left ki height lao , right ka height lao
          Dono mein jo zyda hai use +1 krke return krdo!!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int Height(Node *p)
{
    if(p==NULL)
        return -1;
    int x = Height(p->left);
    int y = Height(p->right);
    return x>y?x+1:y+1;
}
/*
 APPROACH : RPA(Remove -> Print -> Add)
 ->Ek main queue li jisme ek ek krke hr node ko dalenge!
 ->Ek child queue li jisme curr element ke sare children dal denge !
 **main queue ka size = 0 hote hi :**
 #mq=cq;
 #cq->empty
 ~~~~~~~~~~space zyda lg rha hai is approach mein~~~~~~~~~~
 */
void levelOrder1(Node *p)
{
    queue<Node*> mq;
    queue<Node*> cq;
    mq.push(p);
    while(mq.size()!=0)
    {
        p=mq.front();
        mq.pop();
        cout<<p->data<<" ";
        if(p->left!=NULL)
            cq.push(p->left);
        if(p->right!=NULL)
            cq.push(p->right);
        if(mq.size()==0)
        {
            cout<<"\n";
            queue<Node*> temp;
            temp=mq;
            mq=cq;
            cq=temp;
        }
    }
}
/*
 Approach:
 ->Ek hi queue li hai !
 ->Jb tk queue empty ni hojati tb tk size check krte jao !
 ->Us size pe for loop lga ke Remove -> print -> add lga do!
 ->for loop khtm hote hi new line lga do!
 */
void levelOrder2(Node *p)
{
    queue<Node*> qt;
    qt.push(p);
    while(qt.size()!=0)
    {
        int size=qt.size();
        for(int i=0;i<size;i++)
        {
            p=qt.front();
            qt.pop();
            cout<<p->data<<" ";
            if(p->left!=NULL)
                qt.push(p->left);
            if(p->right!=NULL)
                qt.push(p->right);
        }
        cout<<"\n";
    }
}
static string pre = " ";
static string in = " ";
static string post = " ";
class Tra_Pair
{
public:
    Node *node;
    int state;
};
/*
 ***********************IMP********************************
 Intuition:
 1.If state == 0 -> preorder mein add krdo -> state bdha do -> left children ko push krdo state = 0 ke sath!
 2.If state == 1 -> inorder mein add krdo -> state bdha do -> right children ko push krdo state = 0 ke sath!
 3. if state == 2 -> postorder mein add krdo -> st.pop() krdo!
 ***********************IMP********************************
 */
void iterativeTraversal(Node *p)
{
    stack<Tra_Pair> st;
    Tra_Pair tp;
    tp.node=p;
    tp.state=0;
    st.push(tp);
    while(st.size()!=0)
    {
        if(st.top().state==0)
        {
            pre+=to_string(st.top().node->data)+" ";
            st.top().state++;
            if(st.top().node->left!=NULL)
            {
                Tra_Pair temp;
                temp.node=st.top().node->left;
                temp.state=0;
                st.push(temp);
            }
        }
        else if(st.top().state==1)
        {
            in+=to_string(st.top().node->data)+" ";
            st.top().state++;
            if(st.top().node->right!=NULL)
            {
             Tra_Pair temp;
             temp.node=st.top().node->right;
             temp.state=0;
             st.push(temp);
            }
         
        }
        else
        {
            post+=to_string(st.top().node->data)+" ";
            st.pop();
        }
    }
    
}
/*
 Approach:
 1.Agr p->data == data hai to return true krdo!
 2.Left side pe find lgaya agr vhn mil gya to sidha return true krte jao!
 3.Agr left side pe nhi mila to right side pe dhundo -> agr vhn mil gya to sidha return true krte jao!
 ~~~~~~~~~~~~~~True milte hi root ki trf bhagega~~~~~~~~~~~
 ##############Adha Euler chlta hai us case mein###########
 */
bool find(Node *p,int data)
{
    if(p==NULL)
        return false;
    if(p->data==data)
        return true;
    bool lc = find(p->left,data);
    if(lc==true)
        return true;
    bool rc = find(p->right,data);
    if(rc==true)
        return true;
    return false;
}
/*
Approach:
1.Agr p->data == data hai -> to ek vector mein us data ko dalkr return krdo!
2.Left side pe dhundo jakr agr vhn mil gya to vector mein daldo agr left se jo vector aaya hai uska size > 0 --> current node ke data ko vector mein dalo or vector ko return krte jao!!!
3.Right side pe dhundo jakr agr vhn mil gya to vector mein daldo agr right se jo vector aaya hai uska size > 0 --> current node ke data ko vector mein dalo or vector ko return krte jao!!!
~~~~~~~~~~~~~size >0 hote hi root ki trf bhagega~~~~~~~~~~~
##############Adha Euler chlta hai us case mein###########
*/
vector<Node *> nodeToRootPath(Node *p,int data)
{
    vector<Node *> res;
    if(p==NULL)
        return res;
    if(p->data==data)
    {
        res.push_back(p);
        return res;
    }
    vector<Node *> ls = nodeToRootPath(p->left,data);
    if(ls.size()>0)
    {
        ls.push_back(p);
        return ls;
    }
    vector<Node *> rs = nodeToRootPath(p->right, data);
    if(rs.size()>0)
    {
        rs.push_back(p);
        return rs;
    }
    return res;
}
/*
 Jse Jse Depth increase hogi -> level ko km krte jao
 or jb level == 0 hojae iska mtlb apne Level pe paunch gye h ->print krdo fir to!!
 */
void printKLevelsDown(Node *p,int k)
{
    if(p==NULL)
        return;
    if(k==0)
        cout<<p->data<<" ";
    printKLevelsDown(p->left, k-1);
    printKLevelsDown(p->right,k-1);
}
/*
Jse Jse Depth increase hogi -> level ko km krte jao
or jb level == 0 hojae iska mtlb apne Level pe paunch gye h ->print krdo fir to!!
 ~~~~~Blocker bs ek particular trf traverse krne se rokega~~~~
*/
void printKLevelsDown2(Node *t,int k,Node *blocker)
{
    if(t==NULL||k<0||t==blocker)
        return;
    if(k==0)
        cout<<t->data<<" ";
    printKLevelsDown2(t->left, k-1,blocker);
    printKLevelsDown2(t->right,k-1,blocker);
}
/*
 ************************VIMP*********************************
 ########################AMAZON###############################
 Approach:
 1.Us particular node ka node to root path nikal lia!
 2.Fir jo resultant vector hai uspe for loop chlaya or hr upr wala element jo h node to root path mein uska level k-i krdia
 ~~~~~~~Yahn pr Important part hai blocker pass krna~~~~~~~~~~
 Jo ki node to root path mein just phle wala element hai ek particular element se!
~~~~~Blocker bs ek particular trf traverse krne se rokega~~~~~
*************************VIMP*********************************
 */
void printKLevelsFar(Node *p,int data,int k)
{
    vector<Node*> path=nodeToRootPath(p, data);
    int m=path.size();
    for(int i=0;i<m;i++)
    {
        printKLevelsDown2(path[i], k-i,i==0?NULL:path[i-1]);
    }
}
/*
**************************IMP*********************************
 --->PREORDER TRAVERSAL<--
Approach:
 1.Left mein leaf tk jakr dekha -> hr step pe path and sum mein add krte gye!
 2.Right mein leaf tk jakr dekha -> hr step pe path and sum mein add krte gye!
 Agr leaf node aagyi to uska sum dekha:
 If sum is in range ->path mein us particular element ko add krke , path ko print krdo!
 **************************IMP*********************************
 */
void pathToLeafFromRoot(Node *p,string path,int sum,int lo,int hi)
{
    if(p==NULL)
        return ;
    if(p->left==NULL&p->right==NULL)
    {
        sum+=p->data;
     if(sum>=lo&&sum<=hi)
     {
         path+=to_string(p->data)+" ";
         cout<<path<<"\n";
     }
    }
    pathToLeafFromRoot(p->left, path+to_string(p->data)+" ",sum+p->data, lo, hi);
    pathToLeafFromRoot(p->right, path+to_string(p->data)+" ",sum+p->data, lo, hi);
}
/*
 **************************VIMP*******************************
 #Intuition:
 Faith rkhenge -> left child and right child apna kaam krna jante hai!
 *left child ko call krke lcr laye!
 *right child ko call krke rcr laye!
 *ek nya node n1 bnaya jiska data p ke data ke equal hai!
 *is nyi node ka left child lcr ko bnao or right child -> NULL
 *p ke left mein n1 ko daldo & right mein rcr dalkr return!!
 **************************VIMP*******************************
 */
Node * transformToLeftClonedTree(Node *p)
{
    if(p==NULL)
        return NULL;
    Node *lcr = transformToLeftClonedTree(p->left);
    Node *rcr = transformToLeftClonedTree(p->right);
    Node *n1 = new Node;
    n1->data=p->data;
    n1->left=lcr;
    n1->right=NULL;
    p->left=n1;
    p->right=rcr;
    return p;
}
/*
**************************VIMP*****************************
Uchal - uchal ke call krenge left mein!!
 #Intuition:
lnn -> left normalized node
rnn -> right normalized node
 *lnn ko p->left->left se nikala
 *rnn ko p->right se nikala
 *p->left=lnn & p->right=rnn
 *return p
**************************VIMP*****************************
*/
Node* transformBackLeftClonedTree(Node *p)
{
    if(p==NULL)
        return NULL;
    Node *lnn=transformBackLeftClonedTree(p->left->left);
    Node *rnn=transformBackLeftClonedTree(p->right);
    p->left=lnn;
    p->right=rnn;
    return p;
}
/*
 Approach:
 *left mein call kri p ko parent bna dia or uske left ko uska children!
 *right mein call kri p ko parent bna dia or uske right ko uska children!
 ##Agr khi bhi single child parent ka nikalta hai to child ke data ko print krdo!!
 */
void  printSingleChildNodes(Node *p,Node *parent)
{
    if(p==NULL)
        return ;
    if(parent!=NULL&&parent->left==p&&parent->right==NULL)
    {
        cout<<p->data<<"\n";
    }
    else if(parent!=NULL&&parent->right==p&&parent->left==NULL)
    {
        cout<<p->data<<"\n";
    }
    
    printSingleChildNodes(p->left, p);
    printSingleChildNodes(p->right, p);
}
/*
 ######################FAITH###############################
 *Left pe call kri -> left ki sari leaf nodes udd gyi!
 *Right pe call kri -> right ki sari leaf nodes udd gyi!
 ##########################################################
 Approach:
 *Agr leaf node h to NULL return krado!!
 *Jo bhi value return kr rhe ho use collect krne ko bhi to koi chaie!
 *Agr left ki leaves remove kr rhe ho to return krao p->left mein!
 *Agr right ki leaves remove kr rhe ho to return krao p->right mein
 *bss fir p return krdo!
 */
Node * removeLeaves(Node *p)
{
    if(p==NULL)
        return NULL;
    if(p->left==NULL&&p->right==NULL)
        return NULL;
   p->left = removeLeaves(p->left);
    p->right = removeLeaves(p->right);
    return p;
}
/*
*********************VIMP**********************************
 ~~~DIAMETER: number of edges between two farthest nodes!~~
 ##faith:
 ->ld= left ka diameter aa jaega!
 ->rd=right ka diameter aa jaega!
 ->f=height(p->left)+height(p->right)+2
 ->return max(ld,rd,f)
 T = O(n2) --> Height call hori hai recursively ,recursive function ke andr!!!
 ---->Post order mein dobara recursion chl rhi hai isme<---
***********************************************************
 */
int diameter1(Node *p)
{
    if(p==NULL)
        return 0;
    int ld=diameter1(p->left);
    int rd=diameter1(p->right);
    int f =Height(p->left)+Height(p->right)+2;
    return max(f,max(ld,rd));
}
class DiaPair
{
public:
    int ht;
    int dia;
};
/*
*********************VIMP**********************************
 Optimized version(O(n))
 -->Return pe hme diameter & height dono miljaenge!
 -->Dono questions ki recursion ek sath krli!
*********************VIMP**********************************
 */
DiaPair diameter2(Node *p)
{
    if(p==NULL)
    {
        DiaPair bp;
        bp.ht=-1;
        bp.dia=0;
        return bp;
    }
    DiaPair lp=diameter2(p->left);
    DiaPair rp=diameter2(p->right);
    DiaPair mp;
    mp.ht=max(lp.ht,rp.ht)+1;
    int fes=lp.ht+rp.ht+2;
    mp.dia=max(fes,max(lp.dia,rp.dia));
    return mp;
}
/*
 Approach:
 Sum wale function mein bs tilt or niklate gye:
 tilt+=abs(x-y)
 */
static int net_tilt=0;
int tilt(Node *p)
{
    if(p==NULL)
        return 0;
    int x = tilt(p->left);
    int y = tilt(p->right);
    net_tilt+=abs(x-y);
    return x+y+p->data;
}
/*
*********************VIMP**********************************
 #Immediate left and immediate right se compare krke sidha bst ni bolna!!
 #All on the left hand side should be small & all on the right hand side should be larger than the particular element!!
 Approach:
 ~~Agr root apne lp(left pair) ke maximum value se bdi hai or rp(right pair) ke minimum value se choti hai to vo bst hai ~~
 -->Islie mini and maxi bhi nikala hai hr node pe <--
 Tree ke bst hone ke lie check:
 *vo particular node bst h!
 *lp bst h!
 *rp bst h!
 #########################################################
 isBST mein thodi modifications krke usse hi largest BST nikal lenge!!
 ->Agr bst hai to usi node ko root bnado largest ki
 or size nikal lo left ka size + left ka size +1
 ->Agr nhi to check kro left ka bda hai size to use hi root bnao , size bhi uska daldo!
 ->Agr right ka size bda hai to use hi root bnao , size bhi uska hi daldo!
 #########################################################
*********************VIMP**********************************
 */
class BSTPair{
public:
    bool isBST;
    int mini;
    int maxi;
    Node *root_largest;
    int size_largest;
};
BSTPair isBST(Node *p)
{
    if(p==NULL)
    {
        BSTPair bp;
        bp.isBST=true;
        bp.mini=INT_MAX;
        bp.maxi=INT_MIN;
        bp.root_largest=NULL;
        bp.size_largest=0;
        return bp;
    }
    BSTPair lp = isBST(p->left);
    BSTPair rp = isBST(p->right);
    BSTPair mp;
mp.isBST=lp.isBST&&rp.isBST&&p->data<=rp.mini&&p->data>-lp.maxi;
    mp.mini=min(p->data,min(lp.mini,rp.mini));
    mp.maxi=max(p->data,max(lp.maxi,rp.maxi));
    if(mp.isBST)
    {
        mp.root_largest=p;
        mp.size_largest=lp.size_largest+rp.size_largest+1;
    }
    else if(lp.size_largest>rp.size_largest)
    {
        mp.root_largest=lp.root_largest;
        mp.size_largest=lp.size_largest;
   }
    else if(rp.size_largest>lp.size_largest)
    {
        mp.root_largest=rp.root_largest;
        mp.size_largest=rp.size_largest;
    }
    return mp;
}
class balancePair
{
public:
    int ht;
    bool isBalance;
};
/*
*********************VIMP**********************************
 isBalance -> |left ki height - right ki height| <=1
 Approach:
 ->Ek balancePair class bnali jisme height or isBalance dono daldie!
 -> lp : left se dono chize lekr aae!
 -> rp : right se dono chize lekr aae!
 -> EK mypair mp bnaya or uski height and uska isBalance check kia And return mp!
 ##Sirf node ke balance hone se kuch ni hoga uska left and right dono tree balance hone chaie tb jakr tree balance hoga!##
 
*********************VIMP**********************************
 */
balancePair isBalanced(Node *p)
{
    if(p==NULL)
    {
        balancePair bp;
        bp.ht=-1;
        bp.isBalance=true;
        return bp;
    }
    balancePair lp = isBalanced(p->left);
    balancePair rp = isBalanced(p->right);
    balancePair mp;
    mp.ht=max(lp.ht,rp.ht)+1;
    mp.isBalance=(abs(lp.ht-rp.ht)<=1)&&lp.isBalance&&rp.isBalance;
    return mp;
}
int main() {
    // insert code here...
int arr[]={50,25,12,-1,-1,37,30,-1,-1,-1,75,62,-1,70,-1,-1,87,-1,-1};
    stack<Pair> st;
    Pair p;
    p.t=new Node;
    p.t->data=arr[0];
    p.t->left=NULL;
    p.t->right=NULL;
    p.state=0;
    st.push(p);
    Node *root=p.t;
    int i = 1;
    while(st.size()!=0)
    {
        if(arr[i]==-1)
        {
            if(st.top().state==2)
            {
                st.pop();
            }
            else{
                st.top().state++;
                 i++;
            }
           
        }
        else
        {
               if(st.top().state==0)
                   {
                       Pair temp;
                       temp.t=new Node;
                       temp.t->left=NULL;
                       temp.t->data=arr[i];
                       temp.t->right=NULL;
                       temp.state=0;
                       st.top().state++;
                       st.top().t->left=temp.t;
                       st.push(temp);
                       i++;
                   }
                   else if(st.top().state==1)
                   {
                       Pair temp;
                       temp.t=new Node;
                       temp.t->left=NULL;
                       temp.t->data=arr[i];
                       temp.t->right=NULL;
                       temp.state=0;
                       st.top().state++;
                       st.top().t->right=temp.t;
                       st.push(temp);
                       i++;
                   }
                   else if(st.top().state==2)
                   {
                       st.pop();
                   }
        }
     
    }
    // Display(root);
    cout<<"SIZE OF THE BINARY TREE:";
    cout<<Size(root);
    cout<<"\n";
    cout<<"SUM OF THE BINARY TREE:";
    cout<<Sum(root);
    cout<<"\n";
    cout<<"MAX VALUE IN THE BINARY TREE:";
    cout<<Max(root);
    cout<<"\n";
    cout<<"HEIGHT OF THE BINARY TREE:";
    cout<<Height(root);
    cout<<"\n";
    cout<<"LEVEL ORDER TRAVERSAL OF THE BINARY TREE:";
    levelOrder2(root);
    /*cout<<"\n";
    iterativeTraversal(root);
    cout<<"DIFFERENT TYPES OF TRAVERSAL ON THE BINARY TREE:";
    cout<<"\n PreOrder traversal on the binary tree:";
    cout<<pre;
    cout<<"\n InOrder traversal on the binary tree:";
    cout<<in;
    cout<<"\n PostOrder traversal on the binary tree:";
    cout<<post;*/
   /* cout<<"\n";
    cout<<"FIND A PARTICULAR ELEMENT IN THE BINARY TREE:";
    cout<<find(root,87);*/
    /*cout<<"\n";
    cout<<"FIND NODE TO ROOT PATH OF A PARTICULAR ELEMENT IN THE BINARY TREE:";
    vector<int> ans = nodeToRootPath(root,70);
    for(int i=0;i<ans.size();i++)
        cout<<ans[i]<<" ";*/
    /*cout<<"\nPRINT K LEVEL DOWN IN A BINARY TREE:";
    printKLevelsDown(root,2);*/
     /*cout<<"\nPRINT K LEVELS FAR IN A BINARY TREE:";
    printKLevelsFar(root,30,3);*/
    /*cout<<"\n PATH TO LEAF FROM ROOT NODE IN A BINARY TREE:";
    pathToLeafFromRoot(root," ",0,140,212);*/
    /*cout<<"\nTRANSFORM TO A LEFT CLONED TREE:";
    transformToLeftClonedTree(root);
     levelOrder2(root);
    cout<<"\nTRANSFORM BACK FROM A LEFT CLONED TREE:";
    transformBackLeftClonedTree(root);
     levelOrder2(root);*/
    /*cout<<"\nPRINT SINGLE CHILD NODES:";
    printSingleChildNodes(root,NULL);*/
    /*cout<<"\n REMOVING LEAF NODES:";
    removeLeaves(root);
    levelOrder2(root);*/
    /*cout<<"\n DIAMETER OF THE BINARY TREE:";
    DiaPair tp;
    tp=diameter2(root);
    cout<<tp.dia;*/
    /*cout<<"\nTILT OF THE BINARY TREE:";
    tilt(root);
    cout<<net_tilt;*/
    /*cout<<"\n Checking whether the binary tree is a binary search tree:";
    BSTPair tp;
    tp=isBST(root);
    cout<<tp.root_largest->data<<"@"<<tp.size_largest;*/
    cout<<"\n CHECKING WHEHTER THE BINARY TREE IS A BALANCED BINARY TREE";
    balancePair tp;
    tp=isBalanced(root);
    cout<<tp.isBalance;
    return 0;
}
