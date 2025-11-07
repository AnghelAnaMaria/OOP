#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class IOinterface ///clasa interfata/ abstracta
{
public:
    virtual istream& citire(istream& in)=0; ///functie virtuala pura
    virtual ostream& afisare (ostream& out) const =0; ///fct virtuala pura & metoda constanta
};

class Produs: public IOinterface{
protected: ///atribute protected
    string nume;
    int pret;
public:
    Produs(); ///constructor fara parametrii
    Produs(string nume, int pret);///constructor cu parametrii
    Produs(const Produs& p);///copy-constructor
    Produs& operator= (const Produs& p);///operatorul =
    istream& citire (istream& in); ///functia citire
    ostream& afisare (ostream& out) const;///functia afisare
    friend istream& operator>> (istream& in,Produs& p); ///supraincarcare operator>>
    friend ostream& operator<< (ostream& out, const Produs& p);///supraincarcare operator<<
    virtual int detalii(){  ///functie virtuala &functionalitate
      cout<<"Pretul integral este "<<this->pret<<endl;
    }
    virtual double calculeazaReducere(){ ///functie virtuala
       cout<<"Pretul redus este "<<this->pret - (10* this->pret)/100<<endl;
       return this->pret - (10* this->pret)/100;
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
istream& Produs::citire(istream& in){
    cout<<"Nume produs="<<endl;
    in>>this->nume;
    cout<<"Pret produs="<<endl;
    in>>this->pret;

    return in;
}
istream& operator>> (istream& in,Produs& p){
    return p.citire(in);

}
ostream& Produs::afisare(ostream& out) const{
    out<<"Numele este "<<this->nume<<endl;
    out<<"Pretul este "<<this->pret<<endl;
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
    Produs* listaProduse;
public:
    Farmacie();
    Farmacie(string nume, int nrProduse, Produs* listaProduse);
    Farmacie(const Farmacie& farmacie);
    Farmacie& operator=(const Farmacie& farmacie);
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Farmacie& farmacie);
    friend ostream& operator<<(ostream& out, const Farmacie& farmacie);
    void afisareProduseScumpe();
    ~Farmacie();

};
Farmacie:: Farmacie(){
    this->nume="anonim";
    this-> nrProduse=0;
    this->listaProduse=NULL;
}
Farmacie::Farmacie(string nume, int nrProduse, Produs* listaProduse){
    this->nume=nume;
    this->nrProduse=nrProduse;
    this->listaProduse=new Produs[this->nrProduse];
    for(int i=0;i<this->nrProduse; i++){
        this->listaProduse[i]=listaProduse[i];
    }
}
Farmacie:: Farmacie(const Farmacie& farmacie){
    this->nume=farmacie.nume;
    this->nrProduse=farmacie.nrProduse;
    this->listaProduse=new Produs[this->nrProduse];
    for(int i=0;i<this->nrProduse; i++){
        this->listaProduse[i]=farmacie.listaProduse[i];
    }
}
Farmacie& Farmacie::operator=(const Farmacie& farmacie){
    if(this !=&farmacie)
    {
        this->nume=farmacie.nume;
        this->nrProduse=farmacie.nrProduse;
        if (this->listaProduse !=NULL)
            delete [] this->listaProduse;
        this->listaProduse=new Produs[this->nrProduse];
        for(int i=0;i<this->nrProduse; i++){
            this->listaProduse[i]=farmacie.listaProduse[i];
        }
    }
    return *this;

}
istream& Farmacie::citire(istream& in){
    cout<<"Nume farmacie= "<<endl;
    in>>this->nume;
    cout<<"Numar produse= "<<endl;
    in>>this->nrProduse;
    if(this->listaProduse!= NULL)
        delete [] this->listaProduse;
    this->listaProduse=new Produs[this->nrProduse];
    for(int i=0;i<this->nrProduse; i++){
            cout<<"Produsul numarul "<<i+1<<" :"<<endl;
            in>>this->listaProduse[i];
        }


    return in;

}
istream& operator>>(istream& in, Farmacie& farmacie){
    return farmacie.citire(in);
}

ostream& Farmacie::afisare(ostream& out) const{
    out<<"Nume farmacie= "<<this->nume<<endl;
    out<<"Numar produse= "<<this->nrProduse<<endl;
    if(this->listaProduse!= NULL)
    {
        for(int i=0;i<this->nrProduse; i++){
            out<<"Produsul numarul "<<i+1<<" : "<<this->listaProduse[i]<<endl;
        }
    }
    return out;

}
ostream& operator<<(ostream& out, const Farmacie& farmacie){
    return farmacie.afisare(out);
}

void Farmacie::afisareProduseScumpe(){
    if(this->listaProduse!=NULL){
         for(int i=0;i<this->nrProduse; i++){
               if ((this->listaProduse[i]).getPret()>500)
               {
                   cout<<"Produsul este scump. "<<endl;
               }
        }
    }
}
Farmacie::~Farmacie(){
   if(this->listaProduse!=NULL){
      delete [] this->listaProduse;
   }
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
    double calculeazaReducere();/// implemenare functie virtuala din clasa parinte
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
   cout<<"Ingredient dermato(nume)= "<<endl;
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
   cout<<"Pretul redus este "<<this->pret - (30* this->pret)/100<<endl;
   return this->pret - (30* this->pret)/100;

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
    cout<<"Tip Produs(nume)="<<endl;
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
     cout<<"Ingredient dermato(nume)= "<<endl;
     in>>this->ingredientDermato;
     cout<<"Tip Produs(nume)="<<endl;
     in>>this->tipProdus;
     cout<<"Eficienta(de la 1 la 10)= "<<endl;
     in>>this->eficienta;
     cout<<"Ten normal (1-da/0-nu)"<<endl;
     in>>this->tenNormal;
     cout<<"Nr concentratii= "<<endl;
     in>>this->nrConcentratii;
     if(this->concentratieAcizi!=NULL)
        delete [] this->concentratieAcizi;
     this->concentratieAcizi=new float[this->nrConcentratii];
     for (int i=0;i<this->nrConcentratii;i++){
        cout<<"Concentratie acid nr "<<i+1 <<" = "<<endl;
        in>>this->concentratieAcizi[i];
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
     out<<"Eficienta= "<<this->eficienta<<endl;
     out<<"Ten normal (1-da/0-nu)"<<this->tenNormal<<endl;
     out<<"Nr concentratii= "<<this->nrConcentratii<<endl;
     for (int i=0;i<this->nrConcentratii;i++){
        out<<"Concentratie acid nr "<<i+1 <<" = "<<this->concentratieAcizi[i]<<endl;
    }
    return out;

}
ostream& operator<<(ostream& out,const DermatoCosmetic& dercos)
{
    return dercos.afisare(out);
}
double DermatoCosmetic::calculeazaReducere(){
   cout<<"Pretul redus este "<<this->pret - (30* this->pret)/100<<endl;
   return this->pret - (30* this->pret)/100;

}
int DermatoCosmetic::detalii(){
   if (this->eficienta>5)
      cout<<"Produsul este recomandat dermatologic"<<endl;
   else
      cout<<"Produsul nu este recomandat dermatologic"<<endl;
   return this->pret;

}
DermatoCosmetic::~DermatoCosmetic(){
    if (this->concentratieAcizi!= NULL)
        delete [] this->concentratieAcizi;

}





int main()
{

    list <Produs*> listaDeProduse;
    list<Farmacie*> listaFarmacie;
    int k=1;
    while (k==1)
    {
        cout<<"-------------------Meniu-------------------"<<endl;
        cout<<"1: add &create (produs dermato)"<<endl;
        cout<<"2: add &create (produs cosmetic)"<<endl;
        cout<<"3: add &create (produs dermato-cosmetic)"<<endl;
        cout<<"4: show list"<<endl;
        cout<<"5: delete produse"<<endl;
        cout<<"6: functionalitate farmacie"<<endl;
        cout<<"7: functionalitate produs"<<endl;
        cout<<"8: functionalitate produs dermato"<<endl;
        cout<<"9: functionalitate produs cosmetic"<<endl;
        cout<<"10: functionalitate produs dermato-cosmetic"<<endl;
        cout<<"11: stop"<<endl;
        int s;
        cin>>s;

        switch(s)
        {
        case 1:
            {///add &create
                ProdusDermato p;
                cin>>p;
                listaDeProduse.push_back(new ProdusDermato(p));
                break;
            }
        case 2:
            {///add &create
                ProdusCosmetic p;
                cin>>p;
                listaDeProduse.push_back(new ProdusCosmetic(p));
                break;
            }
        case 3:
            {///add &create
                DermatoCosmetic p;
                cin>>p;
                listaDeProduse.push_back(new DermatoCosmetic(p));
                break;
            }
        case 4:
            { ///show list
                cout<<"Lista produse: "<<endl;
                list <Produs*>::iterator it;
                for (it=listaDeProduse.begin();it != listaDeProduse.end();++it)
                      cout<<**it<<endl;
                cout<<"Lisa farmacii: "<<endl;
                list <Farmacie*>::iterator it2;
                for (it2=listaFarmacie.begin();it2 != listaFarmacie.end();++it2)
                      cout<<**it2<<endl;
                break;
            }
        case 5:
            {///delete
                int index;
                cin>>index;
                while (!listaDeProduse.empty())
                     listaDeProduse.pop_back();
            }
        case 6:
            {///functionalitate farmacie
                Farmacie farmacie;
                cin>>farmacie;
                listaFarmacie.push_back(new Farmacie(farmacie));
                farmacie.afisareProduseScumpe();
                break;
            }
        case 7:
            {///functionalitate produs

                Produs p;
                cin>>p;
                p.calculeazaReducere();
                p.detalii();
                break;
            }
        case 8:
            {///functionalitate produsDermato
                ProdusDermato p;
                cin>>p;
                p.calculeazaReducere();
                p.detalii();
                break;
            }
        case 9:
            {///functionalitate produsCosmetic
                ProdusCosmetic p;
                cin>>p;
                p.calculeazaReducere();
                p.detalii();
                break;
            }
        case 10:
            {///functionalitate dermatoCosmetice
                DermatoCosmetic dercos;
                cin>>dercos;
                dercos.calculeazaReducere();
                dercos.detalii();
                break;
            }
        case 11:
            {
                k=0;
                break;
            }


        }

    }


   return 0;
}
