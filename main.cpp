#include <iostream>
#include <stdlib.h>
using namespace std;
class nod
{
protected:
    int info;
    nod* next;
    static int nrnod;
public:
    nod()
    {   nrnod++;
        this->info=0;
        this->next=NULL;
    }
    nod(int info,nod* next)
    {   nrnod++;
        this->info=info;
        this->next=next;
    }
    nod(const nod& n)//copy constructor
    {
        cout<<"SUNT AICI";
        this->info=n.info;
        this->next=n.next;
        nrnod++;

    }
     nod& operator=(nod& n)
    {   cout<<"SUNT IN = in NOD";
        info=n.info;
        next=n.next;
        return (*this);
    }
    ~nod()
    {
        this->info=NULL;
        this->next=NULL;
    }
    static void noduri()
    {
        cout<<endl<<"S-au creat "<<nrnod<<" noduri"<<endl;
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
int nod::nrnod;
class nod_dublu:public nod
{
protected:
    nod* ante;
public:
    nod_dublu();
    nod_dublu(int info,nod* next,nod* ant);
    ~nod_dublu();
    nod_dublu(nod_dublu& n);
     void citire(istream& in)
    {
        nod::citire(in);
       // cout<<"sunt aici";
    }
    friend istream& operator>>(istream& in,nod_dublu& d)
    {
        d.citire(in);
        return in;
    }
     void afis(ostream& out)
    {
        nod::afis(out);
        // out<<"sunt in nod_dublu"<<endl;
    }
    friend ostream& operator<<(ostream& out,nod_dublu& d)
    {
        d.afis(out);
        return out;
    }
    nod_dublu& operator=(nod_dublu& n);
    friend class ldi;
};
nod_dublu::~nod_dublu()
{

}
nod_dublu::nod_dublu()
{
    ante=NULL;
}
nod_dublu::nod_dublu(int info,nod* next,nod* ant):nod(info,next)
{
    ante=ant;
}
nod_dublu::nod_dublu(nod_dublu &n):nod(n)
{cout<<"sunt in copy const la nod dublu";
    ante=n.ante;

}
nod_dublu& nod_dublu::operator=(nod_dublu& n)
{
  // cout<<"NU STIU CE FAC";

    this->nod::operator=(n);
    return *this;
}
class ldi
{
protected:
    nod_dublu* prim;
    static int n;
    //nod_dublu* ultim;
public:
    ldi();
    ldi(nod_dublu* p);
    ldi(ldi&l)
    {
        nod_dublu* temp=l.prim;
        this->prim=new nod_dublu;
        (this->prim)->info=temp->info;
        (this->prim)->next=temp->next;
        (this->prim)->ante=NULL;
        nod* nou=this->prim;
        nod* t=temp->next;
        while(t!=NULL)
        {
            nou->next=new nod;
            nou=nou->next;
            nou->info=t->info;
            t=t->next;

        }
        //prim=l.prim;
        n++;
        cout<<"sunt in copy constr de la ldi";
    }
    ~ldi()
    {

    }
    ldi& operator=(ldi& l)
    {
        cout<<"sunt in = in ldi";
        this->prim=l.prim;
    }
    static void nrlistedi()
    {
        cout<<endl<<"Exista "<<n<<" liste"<<endl;
    }
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
    ldi& insertionsort();
};
int ldi::n;
ldi& ldi::insertionsort()
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
    return *ls;
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
    n++;
//    ultim=NULL;
}
ldi::ldi(nod_dublu* p)
{
    prim=p;
    n++;
   // ultim=u;
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
    cout<<endl<<"Cate elemente are lista? ";
    int nr,x;
    in>>nr;
    if(nr==0)
        return;
    if(nr<0)
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
        out<<"lista e goala"<<endl;
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
    lsi(nod_dublu* prim);
    lsi();
    void citire(istream& in);
    friend istream& operator<<(istream& in,lsi& ls);
    void afis(ostream& out);
    friend ostream& operator<<(ostream& out,lsi& ls);
};
lsi::lsi()
{

}
lsi::lsi(nod_dublu* prim):ldi(prim)
{

}
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
    cout<<"1. Citirea a n liste dublu inlantuite"<<endl;
    cout<<"2. Adaugare elemente intr-o lista dublu inlantuita"<<endl;
    cout<<"3. Afisarea a n liste dublu inlantuite"<<endl;
    cout<<"4. Citirea unei liste simplu inlantuite"<<endl;
    cout<<"5. Adaugare elemente in lista simplu inlantuita"<<endl;
    cout<<"6. Sortare prin insertie directa utilizand o lista dublu inlantuita"<<endl;
    cout<<"7.test"<<endl;
    cout<<"0. Iesire"<<endl;
}
void menu()
{
    int option,ok=0,nr,nrl;
    ldi *l;
    lsi *ls;
    do
    {
        menu_output();
        cout<<endl<<"Introduceti numarul optiunii: ";
        cin>>option;
        ///sa nu uit sa modific
        if(option<0||option>7)
            cout<<"Selectie invalida"<<endl;
        if(option==0)
            cout<<endl<<"EXIT"<<endl;
        if(option==1)
        {
            cout<<endl<<"Introduceti numarul de liste citite: ";
            cin>>nr;
            l=new ldi[nr+1];
            for(int i=1; i<=nr; i++)
            {
                cout<<endl<<"Citesc lista "<<i;
                cin>>l[i];
            }
            ok=1;
        }
        if(option==3)
        {
            if(ok==1)
                for(int i=1; i<=nr; i++)
                {
                    cout<<endl<<"Lista "<<i<<endl;
                    cout<<l[i];
                }
            else
                cout<<"Nu a fost efectuata citirea"<<endl;
        }
        if(option==2)
        {
            cout<<"Introduceti lista in care adaug elemente: ";
            int a;
            cin>>a;
            if(a<1||a>nr)
                cout<<"Nu exista aceasta lista"<<endl;
            else
                cin>>l[a];
        }
        if(option==6)
        {
            if(ok==0)
                cout<<"Nu a fost efectuata citirea"<<endl<<endl;
            else
            {
                cout<<"Introduceti lista pe care aplic insertion sort: ";
                int a;
                cin>>a;
                if(a<1||a>nr)
                    cout<<"Nu exista aceasta lista"<<endl;
                else
                {

                    l[a]=l[a].insertionsort();
                    cout<<l[a];
                }
            }
        }
            if(option==4)
            {
                cout<<"Cate liste simplu inlantuite citesc? ";
                cin>>nrl;
                ls=new lsi[nrl+1];
                for(int i=1;i<=nrl;i++)
                    {
                        cout<<endl<<"Citesc lista "<<i<<endl;
                        cin>>ls[i];
                    }

            }
        if(option==5) ///test cate liste creez
            ldi::nrlistedi();
        if(option==7)
            nod::noduri();
        system("pause");
        system("cls");
    }
    while(option!=0);
}
int main()
{
   // menu();
//cout<<"testez copy constr in nod"<<endl;
nod *a=new nod;
//nod*b=new nod;
nod p1;
cin>>p1;
cin>>*a;
nod::noduri();
cout<<p1;
//nod b(p1);
nod *b=new nod(*a);
delete a;
cout<<"Copiez valoarea:"<<endl;
//cout<<*a; 
cout<<*b;
//nod::noduri();
//nod *c=new nod;
//*c=*a;
//cout<<endl<<"I am atribuit valoarea"<<endl;
//nod::noduri();
//cout<<*c;
//cout<<"Testez copy constructor"<<endl;
//nod_dublu *p=new nod_dublu;
//cin>>*p;
//nod_dublu p1;
//cin>>p1;
//nod_dublu r(p1);
//nod*b=new nod_dublu(*p);
//nod::noduri();
//cout<<*b;
//nod_dublu *c=new nod_dublu;
//*c=*p;
//cout<<*c;
    ldi *l=new ldi;
    cin>>*l;
    ldi::nrlistedi();
    ldi *d=new ldi(*l);
   cout<<*d;
   ldi::nrlistedi();
//    ldi *f=new ldi;
//    *d=*l;
//    ldi::nrlistedi();
    return 0;
}
