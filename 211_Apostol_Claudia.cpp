#include <iostream>
#include <stdlib.h>
#include <typeinfo>
using namespace std;
class nod
{
protected:
    int info;
    nod* next;
    static int nrnod;
public:
    nod()
    {
        nrnod++;
        this->info=0;
        this->next=NULL;
    }
    nod(int info,nod* next)
    {
        nrnod++;
        this->info=info;
        this->next=next;
    }
    nod(const nod& n)
    {
        nod* newnode;
        // cout<<"SUNT AICI";
        newnode=new nod(n.info,n.next);
        info=newnode->info;
        next=newnode->next;
    }
    nod& operator=(nod& n)
    {
        //cout<<"SUNT IN = in NOD";
        info=n.info;
        next=n.next;
        return (*this);
    }
    ~nod()
    {
//        this->info=NULL;
//        this->next=NULL;
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
    //friend class ldi;
    friend class lsi;
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
    nod_dublu(const nod_dublu& n);
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
    //this->ante=NULL;
}
nod_dublu::nod_dublu():nod()
{
    this->ante=NULL;
}
nod_dublu::nod_dublu(int info,nod* next,nod* ant):nod(info,next)
{
    ante=ant;
}
nod_dublu::nod_dublu(const nod_dublu &n):nod(n)
{
    //cout<<"sunt in copy const la nod dublu";
    ante=n.ante;

}
nod_dublu& nod_dublu::operator=(nod_dublu& n)
{
    this->nod::operator=(n);
    this->ante=ante;
    //cout<<"aici";
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
    ldi(const ldi&l)
    {
        //cout<<"SUNT AICI";
        nod_dublu* temp=l.prim;
        this->prim=new nod_dublu;
        (this->prim)->info=temp->info;
        (this->prim)->next=temp->next;
        (this->prim)->ante=NULL;
        nod_dublu* nou=this->prim;
        nod_dublu* t=(nod_dublu*)temp->next;
        while(t!=NULL)
        {
            nou->next=new nod_dublu;
            nou=(nod_dublu*)nou->next;
            nou->info=t->info;
            t=(nod_dublu*)t->next;

        }
        n++;
    }
    virtual ~ldi()
    {

        //cout<<*prim;
        cout<<"destructor ldi";
            nod_dublu* p=prim;//cout<<*p;;
            // if(p==NULL)
            nod_dublu* u;

            while(p!=NULL)
            {

                u=(nod_dublu*)p->next;
                delete p;
                p=u;
            }
            prim=NULL;

        //delete p;
    }
    ldi& operator=(ldi& l)
    {
        // cout<<"sunt in = in ldi";
        //this->prim=l.prim;
        nod_dublu* temp=l.prim;
        this->prim=new nod_dublu;
        (this->prim)->info=temp->info;
        (this->prim)->next=temp->next;
        (this->prim)->ante=NULL;
        nod_dublu* nou=this->prim;
        nod_dublu* t=(nod_dublu*)temp->next;
        while(t!=NULL)
        {
            nou->next=new nod_dublu;
            nou=(nod_dublu*)nou->next;
            nou->info=t->info;
            t=(nod_dublu*)t->next;

        }
        t=NULL;
        return *this;
    }
    static void nrlistedi()
    {
        cout<<endl<<"Au fost create "<<n<<" liste"<<endl;
        cout<<"(cu una in plus din cauza down castului)"<<endl;
    }
    virtual void adaug(int n);
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
    virtual void inserare(int n);
    int isempty()
    {
        if(prim==NULL)
            return 1;//daca e goala
        return 0;
    }
    ldi& insertionsort();
};
int ldi::n;
ldi& ldi::insertionsort()
{
    nod_dublu*p=prim;
    int nr=0;
    ldi* ls=new ldi;
    while(p!=NULL)
    {
        nr++;
        p=(nod_dublu*)p->next;
    }
    //cout<<nr<<endl;
    p=prim;


    //cout<<*ls<<endl;
    for(int i=0; i<nr; i++)
    {
        int val=p->info;
        ls->inserare(val);
        p=(nod_dublu*)p->next;
    }
    // cout<<*ls;
    return *ls;
}

void ldi::inserare(int n)
{
    nod_dublu *p=prim;
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
    nod_dublu*in=new nod_dublu;
    while(p!=NULL&&ok==0)
    {
        if(p->info>n)
            ok=1;
        else
        {
            in=p;
            p=(nod_dublu*)p->next;
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
    // cout<<"constructor ldi"<<endl;
//    ultim=NULL;
}
ldi::ldi(nod_dublu* p)
{
    prim=p;
    n++;
    // ultim=u;
}

void ldi::adaug(int n)
{
    if(prim==NULL)
    {
        prim=new nod_dublu(n,NULL,NULL);
        // cout<<"am pus primul nod pe "<<n<<endl;

    }
    else
    {
        nod_dublu* ptr=prim;
        while(ptr->next!=NULL)
            ptr=(nod_dublu*)ptr->next;
        nod_dublu* nou=new nod_dublu;
        nou->info=n;
        nou->next=NULL;
        nou->ante=ptr;
        ptr->next=nou;


    }
}
void ldi::citire(istream& in)
{
    cout<<endl<<"Cate elemente citesc? ";
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

    nod_dublu* p=prim;
    if(prim==NULL)
        out<<"Lista e goala"<<endl;
    else
    {
        while(p!=NULL)
        {
            out<<p->info<<endl;
            p=(nod_dublu*)p->next;
        }
    }
}
class lsi:public ldi
{
public:
    lsi():ldi()
    {
        //cout<<"constr lsi";
    }
    lsi(nod_dublu *prim):ldi(prim)
    {
    }
    ~lsi()
    {
    }
    lsi(const lsi&l)
    {
        // cout<<"BUNA";
        nod *p=l.prim;
        while(p!=NULL)
        {
            adaug(p->info);
            p=p->next;
        }
    }
    lsi& operator=(lsi& l)
    {
        //cout<<"AICI";
        //this->prim=l.prim;
        nod* temp=(nod*)l.prim;
        this->prim=new nod_dublu;
        (this->prim)->info=temp->info;
        (this->prim)->next=temp->next;
        nod* nou=this->prim;
        nod* t=temp->next;
        while(t!=NULL)
        {
            nou->next=new nod;
            nou=nou->next;
            nou->info=t->info;
            t=t->next;

        }
        t=NULL;
        return *this;


    }
    void citire(istream& in);
    void adaug(int n);
    friend istream& operator<<(istream& in,lsi& ls);
    void afis(ostream& out);
    void inserare(int n);
    friend ostream& operator<<(ostream& out,lsi& ls);
};
void lsi::inserare(int n)
{
    nod *p=prim;
    int ok=0;
    if(p==NULL)
    {
        prim=new nod_dublu();
        prim->info=n;
        prim->next=NULL;
        return;
    }
    if(p->info>n)
    {
        //inserez la inceput
        nod_dublu* aux;
        aux->info=n;
        aux->next=prim;
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
        nod* nou=new nod;
        nou->info=n;
        nou->next=NULL;
        in->next=nou;
    }//inserez la sf
    else
    {
// se opreste pe ala mai mare decat n
        nod* aux=new nod;
        aux->info=n;
        aux->next=p;
        in->next=aux;
    }
//cout<<"LSI";
}
void lsi::adaug(int n)
{
    //cout<<"sunt in adaug lsi";
    if(prim==NULL)
    {
        prim=new nod_dublu;
        prim->info=n;
        prim->next=NULL;

    }
    else
    {
        nod* ptr=prim;
        while(ptr->next!=NULL)
            ptr=ptr->next;
        nod* nou=new nod;
        nou->info=n;
        nou->next=NULL;
        ptr->next=nou;


    }
    //cout<<"sunt in lsi";
}

void lsi::citire(istream&in)
{
    ldi::citire(in);
    //cout<<"buna";
}
istream& operator<<(istream& in,lsi& ls)
{
    ls.citire(in);
    return in;
}
void lsi::afis(ostream& out)
{
    ldi::afis(out);

    //cout<<"pa";
}
ostream& operator<<(ostream& out,lsi& ls)
{
    ls.afis(out);
    return out;
}

void tip(ldi *&l,int &i)
{
    char s;
    cout<<"Lista "<<i<<": dublu inlantuita sau simplu inlantuita? (d/s) "<<endl;
    cin>>s;
    if(s=='s')
    {
        l=new lsi;
        cin>>*l;

        i++;
    }
    else if(s=='d')
    {
        l=new ldi;
        cin>>*l;
        i++;
    }
    else
        cout<<"Caracterul introdus nu este corect"<<endl;
    ///downcast
    lsi*ls=(lsi*)new ldi; ///se va crea o noua lista

}
void menu_output()
{
    cout<<"Apostol Claudia grupa 211 - tema 1"<<endl;
    cout<<endl<<"MENIU"<<endl;
    cout<<"---------------------------------------"<<endl;
    cout<<endl;
    cout<<"1. Citirea a n liste"<<endl;
    cout<<"2. Adaugare elemente intr-o lista "<<endl;
    cout<<"3. Afisarea a n liste "<<endl;
    cout<<"4. Afisare cate liste au fost create "<<endl;
    cout<<"5. Sortare prin insertie directa utilizand o lista dublu inlantuita"<<endl;
    //cout<<"6.test"<<endl;
    cout<<"0. Iesire"<<endl;
}
void menu()
{
    int option,ok=0,nr,nrl,j=0;
    ldi **l;
    do
    {
        menu_output();
        cout<<endl<<"Introduceti numarul optiunii: ";
        cin>>option;
        if(option<0||option>5)
            cout<<"Selectie invalida"<<endl;
        if(option==0)
            cout<<endl<<"EXIT"<<endl;
        if(option==1)
        {
            cout<<endl<<"Introduceti numarul de liste citite: ";
            cin>>nr;

            //l=new ldi[nr+1];
            try
            {
                l=new ldi*[nr];
                for(int i=1; i<=nr; )
                {
                    tip(l[i],i);
                }
            }
            catch(bad_alloc var)
            {
                cout<<"bad alloc"<<endl;
                exit(EXIT_FAILURE);
            }
            ok=1;
        }
        if(option==3)
        {
            if(ok==1)
                for(int i=1; i<=nr; i++)
                {
                    cout<<endl<<"Lista "<<i;
                    if(typeid(*l[i])==typeid(ldi))
                        cout<<" (dublu inlanduita)"<<endl;
                    else
                        cout<<" (simplu inlantuita)"<<endl;
                    cout<<*l[i];
                }
            else
                cout<<"Nu a fost efectuata citirea"<<endl;
        }
        if(option==2)
        {

            if(ok==1)
            {
                cout<<"Introduceti lista in care adaug elemente: ";
                int a;
                cin>>a;
                if(a<1||a>nr)
                    cout<<"Nu exista aceasta lista"<<endl;
                else
                    cin>>*l[a];
            }
            else
                cout<<"Nu a fost efectuata citirea"<<endl;
        }
        if(option==5)
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
                    if(typeid(*l[a])==typeid(ldi))
                    {
                        if(l[a]->isempty()==0)
                            *l[a]=l[a]->insertionsort ();
                        cout<<*l[a];
                    }
                    else
                        cout<<"Nu este o lista dublu inlantuita. Introduceti indicele unei liste dublu inlantuite!"<<endl;
                }
            }
        }
        if(option==4) ///test cate liste creez
            ldi::nrlistedi(); /// va afisa cu una in plus din cauza down castului
//        if(option==7)
//            nod::noduri();
        system("pause");
        system("cls");
    }
    while(option!=0);
}
int main()
{
    menu();
        return 0;
}
