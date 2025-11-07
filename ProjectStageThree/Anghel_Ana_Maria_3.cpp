#include <iostream>
#include <cstring>
#include <string.h>
#include <list>
#include <map>
#include <vector>
#include <set>
using namespace std;

template <class C=int>///clasa template
class Comparare
{private:
    C a;
    C b;
public:
    Comparare(C valoare1, C valoare2)
    {
       a=valoare1;
       b=valoare2;
    }
    void ElementMinim()
    {
        try{   ///exceptie
        if (a<b)
            cout<<"Elementul mai ieftin este "<<a<<endl;
        else if (b<a)
            cout<<"Elementul mai ieftin este "<<b<<endl;
        else
            throw(a);
        }catch(C val){
            cout<<"Elementele au acelasi pret."<<endl;
         }
    }
};

template <class C1, class C2> ///functie template
C2 Adaugare(C1 element,C2 lista)
{
    return element+lista;
}

template <class C>  ///fct template
bool Compara(C &a, C &b)
{
    return a<b ;
}

template<class C>  ///fct template
void Interschimbare(C &a, C &b)
{
    C aux;
    aux= a;
    a=b;
    b=aux;
}

class IOinterface ///clasa interfata/ abstracta
{
public:
    virtual istream& citire(istream& in)=0; ///functie virtuala pura
    virtual ostream& afisare(ostream& out) const =0; ///fct virtuala pura & metoda constanta
};

class Produs: public IOinterface{
protected: ///atribute protected
    string nume;
    double pret;
public:
    Produs(); ///constructor fara parametrii
    Produs(string nume, int pret);///constructor cu parametrii
    Produs(const Produs& p);///copy-constructor
    Produs& operator= (const Produs& p);///operatorul =
    bool operator<(const Produs& p);
    istream& citire (istream& in); ///functia citire
    ostream& afisare (ostream& out) const;///functia afisare
    friend istream& operator>> (istream& in,Produs& p); ///supraincarcare operator>>
    friend ostream& operator<< (ostream& out, const Produs& p);///supraincarcare operator<<
    virtual int detalii(){  ///functie virtuala &functionalitate
      cout<<"Pretul integral este "<<this->pret<<endl;
    }
    virtual double calculeazaReducere(){ ///functie virtuala
       cout<<"produs"<<endl;
       double a;
       a=(this->pret - (10* this->pret)/100);
       cout<<"Pretul redus este "<<a<<endl;
       return a;
    }
    int getPret() const; ///getter (pentru functionalitatea din Farmacie)
    virtual ~Produs(){}; ///destructor
};

Produs::Produs(){
    this->nume="anonim";
    this->pret=0;
}
Produs::Produs(string nume, int pret):nume(nume),pret(pret){}
Produs::Produs(const Produs& p){
    this->nume=p.nume;
    this->pret=p.pret;
}
Produs& Produs::operator= (const Produs& p){
    if(this !=&p)
    {
        this->nume=p.nume;
        this->pret=p.pret;
    }
    return *this;
}

bool Produs::operator<(const Produs& p)
{
    if (this->pret<p.pret)
    {
        cout<<"Primul este mai mic."<<endl;
        return true;
    }
    return false;
}

istream& Produs::citire(istream& in){
    cout<<"Nume produs : "<<endl;
    in>>this->nume;
    int p=1;
    while(p!=0)
    {
         cout<<"Pret produs : "<<endl;
         string pretAux;
         in>>pretAux;
         try{
             if(stoi(pretAux))
             {
                 p=0;
                 this->pret=stoi(pretAux);
             }
              else throw(pretAux);

         }catch(...){
             cout<<"Nu ai dat o valoare buna."<<endl;

         }

    }


    return in;
}
istream& operator>> (istream& in,Produs& p){
    return p.citire(in);

}
ostream& Produs::afisare(ostream& out) const{
    out<<"Nume produs : "<<this->nume<<endl;
    try{   ///exceptie
        if(this->pret==0)
            throw 77;
        else
            cout<<"Pret produs : "<<this->pret<<endl;


    }catch(int x){
        cout<<"Pretul nu a fost stabilit inca."<<endl;
    }

    return out;
}
ostream& operator<<(ostream& out, const Produs& p){
    return p.afisare(out);
}
int Produs::getPret()const {
    return this->pret;
}

class Farmacie:public IOinterface{ ///mostenire
private:
    string nume;
    int nrProduse;
    list <Produs> listaProduse;
public:
    Farmacie();
    Farmacie(string nume, int nrProduse, list <Produs> listaProduse);
    Farmacie(const Farmacie& farmacie);
    Farmacie& operator=(const Farmacie& farmacie);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend Farmacie& operator+(const Produs& p, Farmacie& f);
    friend istream& operator>>(istream& in, Farmacie& farmacie);
    bool operator<(const Farmacie& f);
    friend ostream& operator<<(ostream& out, const Farmacie& farmacie);
    void afisareProduseScumpe();
    string getNume()
    {
        return this->nume;
    }
    ~Farmacie();

};
Farmacie:: Farmacie(){
    this->nume="anonim";
    this-> nrProduse=0;
    this->listaProduse={};
}
Farmacie::Farmacie(string nume, int nrProduse, list <Produs> listaProduse){
    this->nume=nume;
    this->nrProduse=nrProduse;
    this->listaProduse=listaProduse;
}
Farmacie:: Farmacie(const Farmacie& farmacie){
    this->nume=farmacie.nume;
    this->nrProduse=farmacie.nrProduse;
    this->listaProduse=farmacie.listaProduse;

}
Farmacie& Farmacie::operator=(const Farmacie& farmacie){
    if(this !=&farmacie)
    {
        this->nume=farmacie.nume;
        this->nrProduse=farmacie.nrProduse;
        if (this->listaProduse.empty()==0)
             this->listaProduse.clear();
        this->listaProduse=farmacie.listaProduse;
    }
    return *this;

}

Farmacie& operator+(const Produs& p, Farmacie& f){
     f.listaProduse.push_back(p);

     return f;

}

bool Farmacie::operator<(const Farmacie& f)
{
     if (this->nrProduse < f.nrProduse)
        return true;
     else if (this->nrProduse == f.nrProduse)
        return true;
     return false;
}

istream& Farmacie::citire(istream& in){
    cout<<"Nume farmacie : "<<endl;
    in>>this->nume;
    int p=1;
    while(p!=0)
    {
        cout<<"Numar produse : "<<endl;
        string n;
        in>>n;
        try{
            if(stoi(n))
            {
                p=0;
                this->nrProduse=stoi(n);
            }
            else throw(n);
        } catch(...){
            cout<<"Nu ati dat o valoare buna."<<endl;

        }
    }
    if(this->listaProduse.empty()==0)
        this->listaProduse.clear();
    for(int i=0; i<this->nrProduse;i++)
    {
        Produs p;
        cin>>p;
        this->listaProduse.push_back(Produs(p));
    }


    return in;

}
istream& operator>>(istream& in, Farmacie& farmacie){
    return farmacie.citire(in);
}

ostream& Farmacie::afisare(ostream& out) const{
    out<<"Nume farmacie : "<<this->nume<<endl;
    out<<"Numar produse : "<<this->nrProduse<<endl;
    out<<"----Produsele----"<<endl;
    list <Produs>::iterator it;
    for (auto it=listaProduse.begin();it!=listaProduse.end();it++)
    {
        out<<*it<<endl;
    }


    return out;

}
ostream& operator<<(ostream& out, const Farmacie& farmacie){
    return farmacie.afisare(out);
}

void Farmacie::afisareProduseScumpe(){

         list<Produs>::iterator it;
         for( it=listaProduse.begin();it!=listaProduse.end();it++)
         {
            try{
               if (it->getPret()>300)
               {
                   int b=1;
                   cout<<"Produsul "<<b++<<" este scump si are pretul "<<it->getPret()<<endl;
                   cout<<*it<<endl;
                   cout<<endl;
               }
               else
                throw 99;
            }catch(int a){
                cout<<"Produsul nu este scump."<<endl;
                cout<<"Produsul are pretul "<<it->getPret()<<endl;
                cout<<endl;

            }
        }

}
Farmacie::~Farmacie(){
   if(this->listaProduse.empty()==0){
      this->listaProduse.clear();
   }
}

class Companie:public IOinterface
{
private:
    int nrFarmacii;
    int rating;
    set<pair<int,string>> listaRatingFarmacii;
public:
    Companie();
    Companie(int nrFarmacii, int rating, set<pair<int,string>> listaRatingFarmacii);
    Companie(const Companie& c);
    Companie& operator=(const Companie& c);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Companie& c);
    friend ostream& operator<<(ostream& out, const Companie& c);
    ~Companie();
};
Companie:: Companie()
{
    this->nrFarmacii=0;
    this->rating=0;
    this->listaRatingFarmacii={};
}
Companie:: Companie(int nrFarmacii, int rating, set<pair<int,string>> listaRatingFarmacii)
{
    this->nrFarmacii=nrFarmacii;
    this->rating=rating;
    this->listaRatingFarmacii= listaRatingFarmacii;
}
Companie:: Companie(const Companie& c)
{
    this->nrFarmacii=c.nrFarmacii;
    this->rating=c.rating;
    this->listaRatingFarmacii=c.listaRatingFarmacii;
}
Companie& Companie::operator=(const Companie& c)
{
    if(this!=&c)
    {
        this->nrFarmacii=c.nrFarmacii;
        if (this->listaRatingFarmacii.empty()==0)
            this->listaRatingFarmacii.clear();
            this->rating=c.rating;
        this->listaRatingFarmacii=c.listaRatingFarmacii;
    }
    return *this;
}
istream& Companie::citire(istream& in)
{
    if (this->listaRatingFarmacii.empty()==0)
        this->listaRatingFarmacii.clear();
    int p=1;
    while (p!=0)
    {
        string nr;
        cout<<"Dati numarul de farmacii al companiei."<<endl;
        in>>nr;
        try{
            if(stoi(nr)){
                  p=0;
                  this->nrFarmacii=stoi(nr);

            }
            else throw(nr);
        }catch(...){
            cout<<"Nu ati dat o valoare buna. Incercati din nou."<<endl;

        }
    }

    for( int i=0; i< this->nrFarmacii; i++)
    {
        Farmacie f;
        cout<<"Dati o farmacie."<<endl;
        cin>>f;
        int p=1;
        while(p!=0)
        {
            cout<<"Dati un rating pt farmacie. "<<endl;
            string h;
            in>>h;
            try{
                if (stoi(h))
                {
                    p=0;
                    this->rating=stoi(h);
                }
                else throw(h);

            }catch(...){
                cout<<"Nu ai dat o valoare buna."<<endl;

            }
        }
        this->listaRatingFarmacii.insert(make_pair(rating,f.getNume()));
    }

    return in;
}

istream& operator>>(istream& in, Companie& c)
{
    return c.citire(in);
}

ostream& Companie::afisare(ostream& out) const
{
    if (this->listaRatingFarmacii.empty()==0)
    {
        out<<"Avem "<<this->nrFarmacii<<" farmacii care tin de companie."<<endl;
        out<<"------------Rating si nume----------- "<<endl;
        for(auto it=this->listaRatingFarmacii.begin();it!=this->listaRatingFarmacii.end();it++)
        {
            out<<"Rating : "<<(*it).first<<";"<<" Nume : "<<(*it).second<<endl;
            out<<endl;
        }
    }
    else
    {
        out<<"Nu avem nicio farmacie"<<endl;
    }

    return out;
}

ostream& operator<<(ostream& out,const Companie& c)
{
    return c.afisare(out);
}

Companie::~Companie()
{
     if (this->listaRatingFarmacii.empty()==0)
        this->listaRatingFarmacii.clear();
}

class ProdusDermato:public virtual Produs{
protected:
    string ingredientDermato;
public:
    ProdusDermato();
    ProdusDermato(string nume, int pret, string ingredientDermato);
    ProdusDermato(const ProdusDermato& p);
    ProdusDermato& operator=(const ProdusDermato& p);
    istream& citire (istream& in);
    friend istream& operator>>(istream& in, ProdusDermato& p);
    friend ostream& operator<<(ostream& out, const ProdusDermato& p);
    ostream& afisare (ostream& out) const;
    double calculeazaReducere();/// implementare functie virtuala din clasa parinte
    ~ProdusDermato(){};

};
ProdusDermato::ProdusDermato():Produs(){
   this->ingredientDermato="anonim";
}
ProdusDermato::ProdusDermato(string nume, int pret, string ingredientDermato):Produs(nume, pret){
   this->ingredientDermato=ingredientDermato;
}
ProdusDermato::ProdusDermato(const ProdusDermato& p):Produs(p){
   this->ingredientDermato=p.ingredientDermato;
}
ProdusDermato& ProdusDermato:: operator=(const ProdusDermato& p){
   if(this != &p)
   {
       Produs::operator=(p);
       this->ingredientDermato=p.ingredientDermato;
   }

   return *this;
}
istream& ProdusDermato::citire (istream& in){
   Produs::citire(in);
   cout<<"Ingredient dermato(nume) : "<<endl;
   in>>this->ingredientDermato;

   return in;
}
istream& operator>>(istream& in, ProdusDermato& p){
    return p.citire(in);
}
ostream& ProdusDermato::afisare(ostream& out) const{
   Produs::afisare(out);
   out<<"Ingredientul dermato este "<<this->ingredientDermato<<endl;

   return out;
}
ostream& operator<<(ostream& out, const ProdusDermato& p){
   return p.afisare(out);
}
double ProdusDermato::calculeazaReducere(){
    cout<<"produs dermato"<<endl;
    double a;
    a=(this->pret - (30* this->pret)/100);
   cout<<"Pretul redus este "<<a<<endl;
   return a;

}


class ProdusCosmetic:public virtual Produs{
protected:
    string tipProdus;
public:
    ProdusCosmetic();
    ProdusCosmetic(string nume, int pret, string tipProdus);
    ProdusCosmetic(const ProdusCosmetic& p);
    ProdusCosmetic& operator=(const ProdusCosmetic& p);
    istream& citire(istream& in);
    friend istream& operator>>(istream& in, ProdusCosmetic& p);
    friend ostream& operator<<(ostream& out, const ProdusCosmetic& p);
    ostream& afisare(ostream& out) const;///metoda constanta
    double calculeazaReducere();///implementare fct virtuala
    ~ProdusCosmetic(){};
};
ProdusCosmetic::ProdusCosmetic():Produs(){
    this->tipProdus="anonim";
}
ProdusCosmetic::ProdusCosmetic(string nume, int pret, string tipProdus):Produs(nume,pret){
    this->tipProdus=tipProdus;
}
ProdusCosmetic::ProdusCosmetic(const ProdusCosmetic& p):Produs(p){
    this->tipProdus=p.tipProdus;
}
ProdusCosmetic& ProdusCosmetic::operator=(const ProdusCosmetic& p){
    if(this != &p)
    {
        Produs::operator=(p);
        this->tipProdus=p.tipProdus;
    }
    return *this;
}
istream& ProdusCosmetic::citire(istream& in){
    Produs::citire(in);
    cout<<"Tip Produs(nume) : "<<endl;
    in>>this->tipProdus;

    return in;

}
istream& operator>>(istream& in, ProdusCosmetic& p){
    return p.citire(in);
}
ostream& ProdusCosmetic::afisare(ostream& out) const{
    Produs::afisare(out);
    out<<"Tipul produsului este "<<this->tipProdus<<endl;

    return out;
}
ostream& operator<<(ostream& out, const ProdusCosmetic& p){
    return p.afisare(out);
}
double ProdusCosmetic::calculeazaReducere(){
    cout<<"produs cosmetic"<<endl;
    cout<<"Pretul redus este "<<this->pret - (30* this->pret)/100<<endl;
    return this->pret - (30* this->pret)/100;

}

class DermatoCosmetic: public virtual ProdusDermato, public virtual ProdusCosmetic{ ///mostenire in diamant
private:
    int eficienta;
    bool tenNormal;
    int nrConcentratii;
    float* concentratieAcizi;
public:
    DermatoCosmetic();
    DermatoCosmetic(string nume, int pret, string ingredientDermato, string tipProdus, int eficienta, bool tenNormal, int nrConcentratii, float* concentratieAcizi);
    DermatoCosmetic(const DermatoCosmetic& dercos);
    DermatoCosmetic& operator=(const DermatoCosmetic& dercos);
    istream& citire(istream& in);
    friend istream& operator>>(istream& in, DermatoCosmetic& dercos);
    friend ostream& operator<<(ostream& out,const DermatoCosmetic& dercos);
    ostream& afisare(ostream& out) const;
    double calculeazaReducere();
    int detalii();
    void specificatii();
    ~DermatoCosmetic();
};
DermatoCosmetic::DermatoCosmetic():Produs(),ProdusDermato(), ProdusCosmetic(){
    this->eficienta=0;
    this->tenNormal=1;
    this->nrConcentratii=0;
    this->concentratieAcizi=NULL;
}
DermatoCosmetic:: DermatoCosmetic(string nume, int pret, string ingredientDermato, string tipProdus, int eficienta, bool tenNormal, int nrConcentratii, float* concentratieAcizi):Produs(nume,pret),ProdusDermato(nume,pret,ingredientDermato),ProdusCosmetic(nume,pret,tipProdus){

    this->eficienta=eficienta;
    this->tenNormal=tenNormal;
    this->nrConcentratii=nrConcentratii;
    this->concentratieAcizi=new float[this->nrConcentratii];
    for (int i=0;i<this->nrConcentratii;i++){

        this->concentratieAcizi[i]=concentratieAcizi[i];
    }
}
DermatoCosmetic::DermatoCosmetic(const DermatoCosmetic& dercos):Produs(dercos),ProdusDermato(dercos),ProdusCosmetic(dercos){
    this->eficienta=dercos.eficienta;
    this->tenNormal=dercos.tenNormal;
    this->nrConcentratii=dercos.nrConcentratii;
    this->concentratieAcizi=new float[this->nrConcentratii];
    for (int i=0;i<this->nrConcentratii;i++){

        this->concentratieAcizi[i]=dercos.concentratieAcizi[i];
    }
}
DermatoCosmetic& DermatoCosmetic::operator=(const DermatoCosmetic& dercos){
    if (this!=&dercos)
    {
        Produs::operator=(dercos);
        ProdusDermato::operator=(dercos);
        ProdusCosmetic::operator=(dercos);
        this->eficienta=dercos.eficienta;
        this->tenNormal=dercos.tenNormal;
        this->nrConcentratii=dercos.nrConcentratii;
        if (this->concentratieAcizi!=NULL)
            delete [] this->concentratieAcizi;
        this->concentratieAcizi=new float[this->nrConcentratii];
        for (int i=0;i<this->nrConcentratii;i++){

            this->concentratieAcizi[i]=dercos.concentratieAcizi[i];
        }
    }

    return *this;
}
istream& DermatoCosmetic::citire(istream& in){
     Produs::citire(in);
     cout<<"Ingredient dermato(nume) : "<<endl;
     in>>this->ingredientDermato;
     cout<<"Tip Produs(nume)="<<endl;
     in>>this->tipProdus;
     int r=1;
     while(r!=0)
     {
         cout<<"Eficienta(de la 1 la 10) : "<<endl;
         string st;
         in>>st;
         try{
             if(stoi(st))
             {
                 if(0<stoi(st)&&stoi(st)<11)
                 {
                     r=0;
                     this->eficienta=stoi(st);

                 }
                 else throw(st);

             }
             else throw(st);
         }catch(...){
             cout<<"Nu ati dat o valoare buna."<<endl;

         }
     }
     int k=1;
     while(k!=0)
     {
     cout<<"Ten normal (1-da/0-nu)"<<endl;
     string a;
     cin>>a;
     try{  ///exceptie
        if (a=="1")
        {
            this->tenNormal=1;
            k=0;
        }
        else if (a=="0")
        {
            this->tenNormal=0;
            k=0;
        }
        else
            throw(a);

     } catch(string b) {
             cout<<"Nu ai dat o valoare buna"<<endl;
    }
    }
     int y=1;
     while(y!=0)
     {
         cout<<"Nr concentratii : "<<endl;
         string h;
         in>>h;
         try{
             if(stoi(h))
             {
                 y=0;
                 this->nrConcentratii=stoi(h);
             }
             else throw(h);
         }catch(...){
             cout<<"Nu ati dat o valoare buna."<<endl;

         }
     }
     if(this->concentratieAcizi!=NULL)
        delete [] this->concentratieAcizi;
     this->concentratieAcizi=new float[this->nrConcentratii];
     for (int i=0;i<this->nrConcentratii;i++){
             int y=1;
             while(y!=0)
             {
             cout<<"Concentratie acid nr "<<i+1 <<" : "<<endl;
             string hh;
             in>>hh;
             try{
                 if(stoi(hh))
                 {
                     y=0;
                     this->concentratieAcizi[i]=stoi(hh);
                 }
                 else throw(hh);

             }catch(...){
                 cout<<"Valoarea data nu e buna."<<endl;
             }
             }
    }
    return in;

}
istream& operator>>(istream& in, DermatoCosmetic& dercos)
{
    return dercos.citire(in);
}
ostream& DermatoCosmetic:: afisare(ostream& out)const {
     Produs:: afisare(out);
     out<<"Ingredientul dermato este "<<this->ingredientDermato<<endl;
     out<<"Tipul produsului este "<<this->tipProdus<<endl;
     out<<"Eficienta : "<<this->eficienta<<endl;
     out<<"Ten normal (1-da/0-nu)"<<this->tenNormal<<endl;
     out<<"Nr concentratii : "<<this->nrConcentratii<<endl;
     for (int i=0;i<this->nrConcentratii;i++){
        out<<"Concentratie acid nr "<<i+1 <<" : "<<this->concentratieAcizi[i]<<endl;
    }
    return out;

}
ostream& operator<<(ostream& out,const DermatoCosmetic& dercos)
{
    return dercos.afisare(out);
}
double DermatoCosmetic::calculeazaReducere(){
    cout<<"dermato cosmetic"<<endl;
   cout<<"Pretul redus este "<<this->pret - (30* this->pret)/100<<endl;
   return this->pret - (30* this->pret)/100;

}
int DermatoCosmetic::detalii(){
    try{
        if (this->eficienta>5)
            cout<<"Produsul este recomandat dermatologic"<<endl;
        else throw (8);
    }catch(int j){
        cout<<"Produsul nu este recomandat dermatologic"<<endl;

    }
    return this->eficienta;

}

void DermatoCosmetic::specificatii(){

   cout<<"prod dermato cosmetic"<<endl;
}

DermatoCosmetic::~DermatoCosmetic(){
    if (this->concentratieAcizi!= NULL)
    {
        delete [] this->concentratieAcizi;
        this->concentratieAcizi=NULL;
    }
    cout<<"~DermatoCosmetic"<<endl;

}

class MeniuInteractiv
{private:
    static MeniuInteractiv* ob;
    int contor;

    MeniuInteractiv()
    {
        contor=0;
    }
public:
    static MeniuInteractiv* getInstance()
    {
       if (!ob)
           ob= new MeniuInteractiv;
       return ob;
    }

    void setContor(int contor)
    {
       this->contor=contor;
    }

    int getConor()
    {
        return this->contor;
    }

    void meniu()
    {
       vector <Produs*> listaProduse;
       map <int, Farmacie> listaFarmacii;
       int indexF=1;
       int k=1;
       while (k!=0)
       {
           cout<<"---------------------Meniu--------------------"<<endl;
           cout<<"1-pentru diamantul de clase"<<endl;
           cout<<"2-pentru farmacie"<<endl;
           cout<<"3-pentru functionalitati produse"<<endl;
           cout<<"4-pentru alte functionalitati (clasa template, exceptii, funcii template)"<<endl;
           cout<<"5-pentru a va opri"<<endl;
           int p=1;
           int opt;
           while(p!=0)
           {
               string h;
               cin>>h;
               try{
                   if (h=="1")
                   {
                    opt=1;
                    p=0;
                   }
                   else if (h=="2")
                    {
                    opt=2;
                    p=0;
                   }
                   else if (h=="3")
                    {
                    opt=3;
                    p=0;
                   }
                   else if (h=="4")
                    {
                    opt=4;
                    p=0;
                   }
                   else if (h=="5")
                    {
                    opt=5;
                    p=0;
                   }
                   else
                     throw (h);

               }catch( string j){
                   cout<<"Nu ati introdus o valoare buna. "<<endl;

               }
           }
           switch(opt)
           {

           case 1:
            {
                system("CLS");
                int l=1;
                while(l!=0)
                {
                    cout<<"1-pentru a adauga si crea un produs"<<endl;
                    cout<<"2-pentru a adauga si crea un produs dermato"<<endl;
                    cout<<"3-pentru a adauga si crea un produs cosmetic"<<endl;
                    cout<<"4-pentru a adauga si crea un produs dermato-cosmetic"<<endl;
                    cout<<"5-pentru a vedea produsele"<<endl;
                    cout<<"6-pentru a sterge produsele"<<endl;
                    cout<<"7-pentru upcasing"<<endl;
                    cout<<"8-pentru downcasting"<<endl;
                    cout<<"9-pentru a va opri"<<endl;
                   int p=1;
                   int opt2;
                   while(p!=0)
                   {
                       string h;
                       cin>>h;
                       try{
                           if (h=="1")
                           {
                            opt2=1;
                            p=0;
                           }
                           else if (h=="2")
                            {
                            opt2=2;
                            p=0;
                           }
                           else if (h=="3")
                            {
                            opt2=3;
                            p=0;
                           }
                           else if (h=="4")
                            {
                            opt2=4;
                            p=0;
                           }
                           else if (h=="5")
                            {
                            opt2=5;
                            p=0;
                           }
                           else if (h=="6")
                            {
                            opt2=6;
                            p=0;
                           }
                           else if (h=="7")
                            {
                            opt2=7;
                            p=0;
                           }
                           else if (h=="8")
                            {
                            opt2=8;
                            p=0;
                           }
                           else if (h=="9")
                            {
                            opt2=9;
                            p=0;
                           }
                           else
                             throw(h);

                       }catch( string j){
                           cout<<"Nu ati introdus o valoare buna. "<<endl;

                       }
                   }
                    switch(opt2)
                    {
                    case 1:
                        {
                            Produs p;
                            cin>>p;
                            listaProduse.push_back(new Produs(p));
                            break;
                        }
                    case 2:
                        {
                            ProdusDermato p;
                            cin>>p;
                            listaProduse.push_back(new ProdusDermato(p));///upcasting
                            break;
                        }
                    case 3:
                        {
                            ProdusCosmetic p;
                            cin>>p;
                            listaProduse.push_back(new ProdusCosmetic(p));
                            break;
                        }
                    case 4:
                        {
                            DermatoCosmetic d;
                            cin>>d;
                            listaProduse.push_back(new DermatoCosmetic(d));
                            break;
                        }
                    case 5:
                        {
                            for (int i=0; i<listaProduse.size();i++)
                            {
                                cout<<*listaProduse[i]<<endl;
                            }
                            break;
                        }
                    case 6:
                        {
                            while (!listaProduse.empty())
                                listaProduse.pop_back();
                            break;
                        }
                    case 7:
                        {
                            ProdusDermato p;
                            cout<<"Dati produs dermato"<<endl;
                            cin>>p;
                            ProdusCosmetic d;
                            cout<<"Dati produs cosmetic"<<endl;
                            cin>>d;
                            DermatoCosmetic r;
                            cout<<"Dati produs dermato-cosmetic"<<endl;
                            cin>>r;
                            Produs** listaProd= new Produs*[3];
                            listaProd[0]=new ProdusDermato(p);
                            listaProd[1]=new ProdusCosmetic(d);
                            listaProd[2]=new DermatoCosmetic(r);

                            listaProd[0]->calculeazaReducere();
                            listaProd[1]->calculeazaReducere();
                            listaProd[2]->calculeazaReducere();
                            break;
                        }
                    case 8:
                        {
                            cout<<"----------------"<<endl;
                            cout<<"Dati un produs dermato cosmetic"<<endl;
                            DermatoCosmetic dc;
                            cin>>dc;
                            cout<<dc;
                            ProdusDermato* d= new DermatoCosmetic(dc);
                            DermatoCosmetic* a;
                            if(a==NULL)
                                throw runtime_error("off");
                            {

                                a= dynamic_cast<DermatoCosmetic*> (d);
                                a->specificatii();
                            }
                            break;
                        }
                    case 9:
                        {
                            l=0;
                            break;
                        }
                    }
                }
                break;
            }

                    case 2:
                        {
                            system("CLS");
                            int pt=1;
                            while(pt!=0)
                            {
                                cout<<"1-pentru a crea si adauga o farmacie"<<endl;
                                cout<<"2-pentru functionalitatea unei farmacii"<<endl;
                                cout<<"3-pentru afisarea farmaciilor din lista"<<endl;
                                cout<<"4-pentru a sterge farmaciile din lista"<<endl;
                                cout<<"5-pentru a adauga farmacii si ratinguri"<<endl;
                                cout<<"6-pentru a va opri"<<endl;
                                int p=1;
                               int opt3;
                               while(p!=0)
                               {
                                   string h;
                                   cin>>h;
                                   try{
                                       if (h=="1")
                                       {
                                        opt3=1;
                                        p=0;
                                       }
                                       else if (h=="2")
                                        {
                                        opt3=2;
                                        p=0;
                                       }
                                       else if (h=="3")
                                        {
                                        opt3=3;
                                        p=0;
                                       }
                                       else if (h=="4")
                                        {
                                        opt3=4;
                                        p=0;
                                       }
                                       else if (h=="5")
                                        {
                                        opt3=5;
                                        p=0;
                                       }
                                       else if (h=="6")
                                        {
                                        opt3=6;
                                        p=0;
                                       }
                                       else
                                         throw(h);

                                   }catch( string j){
                                       cout<<"Nu ati introdus o valoare buna. "<<endl;

                                   }
                               }
                                switch(opt3)
                                {

                                case 1:
                                    {
                                        Farmacie f;
                                        cin>>f;
                                        listaFarmacii.insert(pair<int,Farmacie> (indexF++,f));
                                        break;
                                    }
                                case 2:
                                    {
                                        map<int,Farmacie>::iterator it;
                                        for(it=listaFarmacii.begin();it!=listaFarmacii.end();it++)
                                        {
                                            cout<<"Pentru farmacia "<<it->first<<" :"<<endl;
                                            (it->second).afisareProduseScumpe();
                                        }
                                        break;
                                    }
                                case 3:
                                    {
                                        map<int,Farmacie>::iterator it;
                                        for(it=listaFarmacii.begin();it!=listaFarmacii.end();it++)
                                        {
                                            cout<<it->second<<endl;
                                        }
                                        break;
                                    }
                                case 4:
                                    {
                                        auto it1=listaFarmacii.find(1);
                                        auto it2=listaFarmacii.find(listaFarmacii.size()+1);
                                        listaFarmacii.erase(it1, it2);
                                        break;
                                    }
                                case 5:
                                    {
                                        Companie c;
                                        cin>>c;
                                        cout<<c;
                                        break;
                                    }
                                case 6:
                                    {
                                        pt=0;
                                        break;
                                    }
                                    }
                            }
                            break;
                        }

                                case 3:
                                    {
                                        system("CLS");
                                        int a=1;
                                        int b;
                                        while(a!=0)
                                        {
                                            int ss=1;
                                            string j;
                                            while(ss!=0)
                                            {
                                                cout<<"1-pentru functionalitate produs dermato"<<endl;
                                                cout<<"2-pentru functionalitate produs cosmetic"<<endl;
                                                cout<<"3-pentru functionalitate produs dermato-cosmetic"<<endl;
                                                cout<<"4-pentru a va opri"<<endl;
                                                cin>>j;
                                                try{
                                                    if(stoi(j))
                                                    {
                                                        if(0<stoi(j)&&stoi(j)<5)
                                                        {
                                                            b=stoi(j);
                                                            ss=0;
                                                        }
                                                        else throw(j);

                                                    }
                                                    else throw(j);
                                                }catch(...){
                                                    cout<<"Nu ati dat o valoare buna."<<endl;
                                                }
                                            }
                                            switch(b)
                                            {

                                            case 1:
                                                {
                                                   ProdusDermato p;
                                                   cin>>p;
                                                   p.calculeazaReducere();
                                                   p.detalii();
                                                   break;

                                                }
                                            case 2:
                                                {
                                                    ProdusCosmetic p;
                                                    cin>>p;
                                                    p.calculeazaReducere();
                                                    p.detalii();
                                                    break;
                                                }
                                            case 3:
                                                {
                                                    DermatoCosmetic p;
                                                    cin>>p;
                                                    p.calculeazaReducere();
                                                    p.detalii();
                                                    break;
                                                }
                                            case 4:
                                                {
                                                    a=0;
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                            case 4:
                                                {
                                                    system("CLS");
                                                    int o=1;
                                                    while(o!=0)
                                                    {
                                                        int y; ///optiunea
                                                        int tt=1;
                                                        while(tt!=0)
                                                        {
                                                            cout<<"1-pentru clasa template"<<endl;
                                                            cout<<"2-pentru fct template adaugare"<<endl;
                                                            cout<<"3-pentru fct template compara"<<endl;
                                                            cout<<"4-pentru functia template interschimbare"<<endl;
                                                            cout<<"5-pentru a va opri"<<endl;
                                                            string me;
                                                            cin>>me;
                                                            try{
                                                                if(stoi(me))
                                                                {
                                                                    if(0<stoi(me)&&stoi(me)<6)
                                                                    {
                                                                        tt=0;
                                                                        y=stoi(me);
                                                                    }
                                                                    else throw(me);
                                                                }
                                                                else throw(me);
                                                            }catch(...){
                                                                cout<<"Nu ati dat o valoare buna."<<endl;
                                                            }
                                                        }
                                                        switch(y)
                                                        {
                                                        case 1:
                                                            {
                                                                Produs a;
                                                                cout<<"Dati a"<<endl;
                                                                cin>>a;
                                                                Produs b;
                                                                cout<<"Dati b"<<endl;
                                                                cin>>b;
                                                                Comparare<Produs> c(a,b) ;
                                                                c.ElementMinim();
                                                                break;

                                                            }
                                                        case 2:
                                                            {
                                                                Produs p;
                                                                cout<<"Dati produs care sa fie adaugat in lista "<<endl;
                                                                cin>>p;
                                                                cout<<"Dati farmacie"<<endl;
                                                                Farmacie f;
                                                                cin>>f;
                                                                cout<<"Noua lista de produse: "<<endl;
                                                                cout<< Adaugare<Produs&,Farmacie&> (p,f)<<endl;
                                                                break;
                                                            }
                                                        case 3:
                                                            {
                                                                Produs a;
                                                                cout<<"Dati a"<<endl;
                                                                cin>>a;
                                                                Produs b;
                                                                cout<<"Dati b"<<endl;
                                                                cin>>b;
                                                                if(Compara<Produs> (a,b)==true)
                                                                    cout<<"a mai ieftin decat b"<<endl;
                                                                else cout<<"b mai ieftin decat a"<<endl;
                                                                break;
                                                            }
                                                        case 4:
                                                            {
                                                                ProdusDermato a;
                                                                cout<<"Dati a"<<endl;
                                                                cin>>a;
                                                                ProdusDermato b;
                                                                cout<<"Dati b"<<endl;
                                                                cin>>b;
                                                                Interschimbare(a,b);
                                                                cout<<"a este: "<<endl;
                                                                cout<<a<<endl;
                                                                cout<<"b este:"<<endl;
                                                                cout<<b<<endl;
                                                                break;
                                                            }
                                                         case 5:
                                                            {
                                                                o=0;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                    break;
                                                }
                                                         case 5:
                                                            {
                                                                k=0;
                                                                break;
                                                            }

           }
       }

    }
};
MeniuInteractiv* MeniuInteractiv::ob=0;

int main()
{
   MeniuInteractiv* meniu;
   if(meniu==NULL)
    throw runtime_error("aici");
   meniu=meniu->getInstance();
   meniu->setContor(1);
   meniu->meniu();
   return 0;
}
