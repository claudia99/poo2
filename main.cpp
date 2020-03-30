#include <iostream>
#include <stdlib.h>
using namespace std;
class nod
{
protected:
    int info;
    nod* next;
public:
    nod()
    {
        this->info=0;
        this->next=NULL;
    }
    nod(int info,nod* next)
    {
        this->info=info;
        this->next=next;
    }
    ~nod()
    {
        this->info=NULL;
        this->next=NULL;
    }
    virtual void citire(istream& in)
    {
        cout<<"Introduceti o valoare"<<endl;
        in>>info;
    }
    friend istream& operator>>(istream&in,nod& n)
    {
        n.citire(in);
        return in;
    }
    virtual void afis(ostream& out)
    {
        out<<info;
        // out<<endl<<"sunt in nod"<<endl;
    }
    friend ostream& operator<<(ostream& out,nod& n)
    {
        n.afis(out);
        return out;
    }
    friend class ldi;
};
class nod_dublu:public nod
{
protected:
    nod* ante;
public:
    nod_dublu();
    nod_dublu(int info,nod* next,nod* ant);
    ~nod_dublu()
    {

    }
    virtual void citire(istream& in)
    {
        nod::citire(in);
        cout<<"sunt aici";
    }
    friend istream& operator>>(istream& in,nod_dublu& d)
    {
        d.citire(in);
        return in;
    }
    virtual void afis(ostream& out)
    {
        nod::afis(out);
        // out<<"sunt in nod_dublu"<<endl;
    }
    friend ostream& operator<<(ostream& out,nod_dublu& d)
    {
        d.afis(out);
        return out;
    }
    friend class ldi;
};

nod_dublu::nod_dublu()
{
    ante=NULL;
}
nod_dublu::nod_dublu(int info,nod* next,nod* ant):nod(info,next)
{
    ante=ant;
}
class ldi
{
protected:
    nod_dublu* prim;
    nod_dublu* ultim;
public:
    ldi();
    ldi(nod_dublu* p,nod_dublu* u);
    int isempty();
    nod_dublu* caut(int info);
    void adaug(int n);
    virtual void afis(ostream& out);
    virtual void citire(istream& in);
    friend istream& operator>>(istream&in,ldi& l)
    {
        l.citire(in);
        return in;
    }
    friend ostream& operator<<(ostream& out,ldi& l)
    {
        l.afis(out);
        return out;
    }
    void inserare(int n);
    void traversare();
    ldi* insertionsort();
};
ldi* ldi::insertionsort()
{
    nod*p=prim;
    int nr=0;
    while(p!=NULL)
    {
        nr++;
        p=p->next;
    }
    //cout<<nr<<endl;
    p=prim;
    ldi* ls=new ldi;

    //cout<<*ls<<endl;
    for(int i=0; i<nr; i++)
    {
        int val=p->info;
        ls->inserare(val);
        p=p->next;
    }
    // cout<<*ls;
    return ls;
}
void ldi::traversare()
{
    nod *p=prim;
    while(p!=NULL)
    {
        cout<<p->info<<" ";
        p=p->next;
    }
}
void ldi::inserare(int n)
{
    nod *p=prim;
    int ok=0;
    if(p==NULL)
    {
        //cout<<"buna";
        nod_dublu *pr=new nod_dublu;
        pr->info=n;
        pr->next=NULL;
        pr->ante=NULL;
        prim=pr;
        return;
    }
    if(p->info>n)
    {
        //inserez la inceput
        nod_dublu* aux=new nod_dublu;
        nod_dublu* nou=new nod_dublu;
        nou->info=p->info;
        nou->next=p->next;
        nou->ante=NULL;
        aux->info=n;
        aux->next=nou;
        aux->ante=NULL;
        nou->ante=aux;
        prim=aux;
        return;
    }
    nod*in=new nod;
    while(p!=NULL&&ok==0)
    {
        if(p->info>n)
            ok=1;
        else
        {
            in=p;
            p=p->next;
        }
    }
    if(ok==0||p==NULL)
    {
        nod_dublu* nou=new nod_dublu;
        nou->info=n;
        nou->next=NULL;
        nou->ante=in;
        in->next=nou;
    }//inserez la sf
    else
    {
// cout<<in->info<<endl;
//        cout<<p->info;// se opreste pe ala mai mare decat n
        nod_dublu* aux=new nod_dublu;
        nod_dublu* nou=new nod_dublu;
        nou->info=p->info;
        nou->next=p->next;
        nou->ante=in;
        aux->info=n;
        aux->next=p;
        aux->ante=in;
        nou->ante=aux;
        in->next=aux;

    }

}
ldi::ldi()
{
    prim=NULL;
    ultim=NULL;
}
ldi::ldi(nod_dublu* p,nod_dublu* u)
{
    prim=p;
    ultim=u;
}
int ldi:: isempty()
{
    if(prim==NULL)
        return 0;//lista e goala
    return 1;//lista contine noduri
}
void ldi::adaug(int n)
{
    if(isempty()==0)
    {
        prim=new nod_dublu(n,NULL,NULL);
        // cout<<"am pus primul nod pe "<<n<<endl;

    }
    else
    {
        nod* ptr=prim;
        while(ptr->next!=NULL)
            ptr=ptr->next;
        nod_dublu* nou=new nod_dublu;
        nou->info=n;
        nou->next=NULL;
        nou->ante=ptr;
        ptr->next=nou;


    }
}
void ldi::citire(istream& in)
{
    cout<<"Cate elemente are lista? ";
    int nr,x;
    in>>nr;
    if(x<0)
        cout<<"Numar invalid";
    else
    {
        cout<<"Introduceti elementele"<<endl;
        for(int i=0; i<nr; i++)
        {
            in>>x;
            adaug(x);
        }
    }
}
void ldi::afis(ostream& out)
{

    nod* p=prim;
    if(isempty()==0)
        out<<"lista e goala";
    else
    {
        while(p!=NULL)
        {
            out<<p->info<<endl;
            p=p->next;
        }
    }
}
class lsi:public ldi
{
public:
    lsi();

    void citire(istream& in);
    friend istream& operator<<(istream& in,lsi& ls);
    void afis(ostream& out);
    friend ostream& operator<<(ostream& out,lsi& ls);
};
void lsi::citire(istream&in)
{
    ldi::citire(in);
    cout<<"buna";
}
istream& operator<<(istream& in,lsi& ls)
{
    ls.citire(in);
    return in;
}
void lsi::afis(ostream& out)
{
    ldi::afis(out);
    cout<<"pa";
}
ostream& operator<<(ostream& out,lsi& ls)
{
    ls.afis(out);
    return out;
}
void menu_output()
{
    cout<<"Apostol Claudia grupa 211 - tema 1"<<endl;
    cout<<endl<<"MENIU"<<endl;
    cout<<"---------------------------------------"<<endl;
    cout<<endl;
    cout<<"1. Citirea unei liste dublu inlantuite"<<endl;
    cout<<"2. Adaugare elemente in lista dublu inlantuita"<<endl;
    cout<<"3. Afisarea unei liste dublu inlantuite"<<endl;
    cout<<"4. Citirea unei liste simplu inlantuite"<<endl;
    cout<<"5. Adaugare elemente in lista simplu inlantuita"<<endl;
    cout<<"6. Sortare prin insertie directa utilizand o lista dublu inlantuita"<<endl;
    cout<<"0. Iesire"<<endl;
}
void menu()
{
    int option,ok=0;
    ldi *l;
    l=new ldi;
    do
    {   menu_output();
        cout<<endl<<"Introduceti numarul optiunii ";
        cin>>option;
        if(option<0||option>6)
            cout<<"Selectie invalida"<<endl;
        if(option==0)
            cout<<endl<<"EXIT"<<endl;
        if(option==1)
            {cin>>*l; ok=1;}
        if(option==3)
            {if(ok==1)
                cout<<*l;
            else cout<<"Nu a fost efectuata citirea"<<endl;}
        if(option==2)
            cin>>*l;
        if(option==6)
        {
            if(ok==0)
                cout<<"Nu a fost efectuata citirea"<<endl<<endl;
            else{l=l->insertionsort();
            cout<<*l;}
        }


    system("pause");
    system("cls");
    }
    while(option!=0);
}
int main()
{
    menu();
    // nod *n;
    // n=new nod;
//    cin>>*n;
//    cout<<*n;
//    nod_dublu *d;
//    d=new nod_dublu;
//   cin>>*d;
//    cout<<*d;
    //cin>>*l;
    //l->traversare();
    cout<<endl;
    //l->inserare(10);
//    cout<<*l;
   // l->inserare(20);
    //cout<<*l;
    // int n=10;   l->inserare(n,*l);
    // l=l->insertionsort();
    //cout<<endl<<*l;
//    cin>>*l;
//    cout<<*l;
    return 0;
}
