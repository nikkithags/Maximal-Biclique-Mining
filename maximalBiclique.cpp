#include <iostream>
#include <fstream>


using namespace std;
int n;

struct Node
{
    int r[100];
    int c[100];
    Node* next;
};

class Maximal
{
    Node *Front;

public:

    Maximal()
    {
        Front==NULL;
    }

    void Insert(Node *N)
    {
        int i,j,Count,a,b,check=0;
        Node *p=Front,*prev;

        p=Front;
        while(p!=NULL)
        {
            Count=0;
            a=b=0;
            for(i=0;i<n;i++)
            {
                if(p->r[i]==N->r[i])
                    Count++;
                if(p->c[i]==1)
                    a++;
                if(N->c[i]==1)
                    b++;
            }
            if(Count==n&&a>=b)
                return;
            else if(Count==n&&a<b)
            {
                for(i=0;i<n;i++)
                    p->c[i]=N->c[i];
                return;
            }
            p=p->next;
        }
        p=Front;
        while(p!=NULL)
        {
            Count=0;
            a=b=0;
            for(i=0;i<n;i++)
            {
                if(p->c[i]==N->c[i])
                    Count++;
                if(p->r[i]==1)
                    a++;
                if(N->r[i]==1)
                    b++;
            }
            if(Count==n&&a>=b)
                return;
            else if(Count==n&&a<b)
            {
                if(p==Front)
                    Front=Front->next;
                else
                    prev->next=p->next;
                break;
            }
            prev=p;
            p=p->next;
        }

        p=Front;
        while(p!=NULL)
        {
            Count=0;
            for(i=0;i<n;i++)
            {
                if(p->r[i]==N->c[i])
                    Count++;
            }
            if(Count==n)
                return;
            else if(Count==n&&a<b)
            {
                if(p==Front)
                    Front=Front->next;
                else
                    prev->next=p->next;
                break;
            }
            prev=p;
            p=p->next;
        }

        Node *q=new Node;
        for(i=0;i<n;i++)
        {
            q->r[i]=N->r[i];
            q->c[i]=N->c[i];
        }

        q->next=Front;
        Front=q;

    }
    void display()
    {
        Node *p=Front;
        int i;

        cout<<"\nMaximals: \n\n";
        while(p!=NULL)
        {
            for(i=0;i<n;i++)
            {
                if(p->r[i]==1)
                    cout<<"r"<<i+1;
            }
            cout<<" - ";
            for(i=0;i<n;i++)
            {
                if(p->c[i]==1)
                    cout<<"c"<<i+1;
            }
            cout<<endl<<endl;
            p=p->next;
        }
    }
}m;

int zeropruned(Node *p)
{
    int i,c=0,d=0;
    for(i=0;i<5;i++)
    {
        c+=p->r[i];
        d+=p->c[i];
    }
    if(c==0||d==0)
        return 1;
    return 0;
}

int maximal(Node *p,int a[][100])
{
    int i,j,r=0,c=0;
    for(i=0;i<n;i++)
    {
        if(p->r[i]==1)
        {
            r=c=0;
            for(j=0;j<n;j++)
            {
                if(p->c[j]==1)
                {
                    r++;
                    if(a[i][j]==1)
                        c++;
                }
            }
            if(r!=c&&c<r)
                return 0;
        }o
    }
    m.Insert(p);
    return 1;
}

int pruned(Node *p,int a[][100])
{
    int i,j;
    int r=0,c=0;
    for(i=0;i<n;i++)
    {
        if(p->r[i]==0)
        {
            r=c=0;
            for(j=0;j<n;j++)
            {
                if(p->c[j]==1)
                {
                    r++;
                    if(a[i][j]==1)
                        c++;
                }
            }
            if(r==c&&r!=0)
                return 1;
        }
    }
    return 0;
}

void Function(int a[100][100],Node* p,int s=0)
{
    Node *left=new Node;
    Node *right=new Node;

    int lr[n],lc[n],rr[n],rc[n];
    int i,j,row;

    if(zeropruned(p))
        return;
    if(maximal(p,a))
        return;
    if(s==1)
        if(pruned(p,a)==1)
            return;

    for(i=0;i<n;i++)
    {
        left->c[i]=p->c[i];
        right->r[i]=p->r[i];
    }

    for(i=0;i<n;i++)
    {
        if(p->r[i]==1)
        {
            for(j=0;j<n;j++)
            {
                if(a[i][j]==0)
                {
                    if(p->c[j]==1)
                    {
                        row=i;
                        goto next;
                    }
                }
            }
        }
    }
    next:
    for(i=0;i<n;i++)
    {
        if(row==i)
            left->r[i]=0;
        else
            left->r[i]=p->r[i];
    }
    for(i=0;i<n;i++)
    {
        if(a[row][i]==0)
            right->c[i]=0;
        else
            right->c[i]=p->c[i];
    }

    for(i=0;i<n;i++)
    {
        lr[i]=left->r[i];
        lc[i]=left->c[i];
        rr[i]=right->r[i];
        rc[i]=right->c[i];
    }

    Function(a,left);

    for(i=0;i<n;i++)
    {
        left->r[i]=lr[i];
        left->c[i]=lc[i];
        right->r[i]=rr[i];
        right->c[i]=rc[i];
    }
    Function(a,right,1);
}

int main()
{
    ifstream file;
    string line;

    file.open("/home/karunyav/Downloads/Documents/sem2/package/oop/matrix_array.txt",ios::in);
    while(getline(file,line))
        n++;
    n--;
    file.close();

    file.open("/home/karunyav/Downloads/Documents/sem2/package/oop/matrix_array.txt",ios::in);
    char ch;
    int Map[100][100],i=0,j=0;
    while(!file.eof())
    {
        file.get(ch);
        if(ch=='\n')
        {
            j=0;
            i++;
        }
        else
            Map[i][j++]=ch-48;
    }
    file.close();

    Node *Front= new Node;
    for(int i=0;i<n;i++)
        Front->r[i]=Front->c[i]=1;

    Function(Map,Front);
    m.display();

    return 0;
}


