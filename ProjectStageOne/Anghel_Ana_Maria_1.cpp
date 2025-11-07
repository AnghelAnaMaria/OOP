#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class Locatie
{
private:
    string tara;
    string oras;
    string sector;
    string magazin;
    int* rating;
    int nrRating;
public:
    Locatie();///constructor fara param.
    Locatie(string tara, string oras, string sector, int* rating, int nrRating);///constructor cu param.
    Locatie(string tara, string oras, string sector, string magazin, int* rating, int nrRating);///constructor cu param.
    Locatie(const Locatie& locatie);///cc

    void setTara(string tara);///set
    void setOras(string oras);
    void setSector(string sector);
    void setMagazin(string magazin);
    void setRating(int* rating, int nrRating);

    string getTara() const;///get
    string getOras() const;
    string getSector() const;
    string getMagazin() const;
    const int* getRating() const;

    const Locatie& operator++(); ///pre-incrementare
    const Locatie operator++(int);///post-incrementare

    Locatie operator+(const Locatie& loc);/// supraincarcare op +
    Locatie operator-(const Locatie& loc);/// supraincarcare op -

    Locatie& operator=(const Locatie& locatie);///operator de atribuire

    bool operator==(const Locatie& loc);///supraincarcarea op ==
    bool operator<(const Locatie& loc);///supraincarcarea op <

    friend ostream& operator<<(ostream& out, const Locatie& locatie);/// supraincarcare op <<
    friend istream& operator>>(istream& in, Locatie& locatie);/// supraincarcare op >>
    explicit operator int() ///supraincararea operatorului cast
    {
        return (int)this->nrRating;
    }

    int operator[](int index){  ///supraincarcare op []
        if (this->rating!=NULL)
        {

            if ((0 <= index) & (index < this->nrRating))
                return this->rating[index];
            cout << "Index introdus gresit";
        }
    }

    void afisareRatinguri(); ///functionalitate-> afiseaza rating-urile unei locatii

    ~Locatie();///destructor

};

Locatie:: Locatie(){
    this->nrRating=0;
    this->tara=" ";
    this->oras=" ";
    this->sector=" ";
    this->magazin=" ";
    this->rating=NULL;
}

Locatie:: Locatie(string tara, string oras, string sector, int* rating, int nrRating){
    this->nrRating=nrRating;
    this->tara=tara;
    this->oras=oras;
    this->sector=sector;
    this->magazin=" ";
    this->rating=new int[this->nrRating];
    for (int i=0;i<this->nrRating;i++)
    {
        this->rating[i]=rating[i];
    }

}

Locatie:: Locatie(string tara, string oras, string sector, string magazin, int* rating, int nrRating){
    this->nrRating=nrRating;
    this->tara=tara;
    this->oras=oras;
    this->sector=sector;
    this->magazin=magazin;
    this->rating=new int[this->nrRating];
    for (int i=0;i<this->nrRating;i++)
    {
        this->rating[i]=rating[i];
    }
}

Locatie:: Locatie(const Locatie& locatie){
    this->nrRating=locatie.nrRating;
    this->tara=locatie.tara;
    this->oras=locatie.oras;
    this->sector=locatie.sector;
    this->magazin=locatie.magazin;
    this->rating=new int[locatie.nrRating];
    for (int i=0;i<locatie.nrRating;i++)
    {
        this->rating[i]=locatie.rating[i];
    }
}

Locatie& Locatie:: operator= (const Locatie& locatie){
    if (this!=&locatie)
    {
        delete this->rating;
        this->rating=new int[locatie.nrRating];
        for (int i=0;i<locatie.nrRating;i++)
        {
            this->rating[i]=locatie.rating[i];
        }
        this->nrRating=locatie.nrRating;
        this->tara=locatie.tara;
        this->oras=locatie.oras;
        this->sector=locatie.sector;
        this->magazin=locatie.magazin;
    }
    return *this;
}


void Locatie::setTara(string tara){
    this->tara=tara;
}

void Locatie::setOras(string oras){
    this->oras= oras;
}

void Locatie::setSector(string sector){
    this->sector=sector;
}

void Locatie::setMagazin(string magazin){
    this->magazin=magazin;
}

void Locatie::setRating(int* rating, int nrRating){
    if(this->rating!=NULL)
        delete[] this->rating;
    this->rating=new int[nrRating];
    for(int i=0; i<nrRating;i++)
    {
        this->rating[i]=rating[i];
    }
}

string Locatie:: getTara()const{
    return this->tara;
}
string Locatie:: getOras()const{
    return this->oras;
}
string Locatie:: getSector()const{
    return this->sector;
}
string Locatie:: getMagazin()const{
    return this->magazin;
}
const int* Locatie::getRating() const {

    return this->rating;
}

Locatie Locatie::operator+(const Locatie& loc){
    Locatie aux(*this);
    aux.magazin= this->magazin+loc.magazin;
    return aux;

}

Locatie Locatie::operator-(const Locatie& loc){
    if (this->rating!=NULL && loc.rating!=NULL)
    {
        if( this->rating[0]> loc.rating[0])
            this->rating[0]=this->rating[0]-loc.rating[0];
        else
            this->rating[0]=loc.rating[0]-this->rating[0];
        return *this;
    }
}

bool Locatie::operator==(const Locatie& loc){
    if (this->oras==loc.oras && this->tara== loc.tara && this->sector==loc.sector)
        return true;
    else
        return false;

}

bool Locatie::operator<(const Locatie& loc){
    if (this->rating!=NULL && loc.rating!=NULL)
    {

        if (this->rating[0]< loc.rating[0])
            return true;

        return false;
    }
}

const Locatie& Locatie::operator++(){
    if (this->rating!=NULL)
    {

        this->rating[0]++;

    }
    return *this;
}


const Locatie Locatie::operator++(int){
    if(this->rating!=NULL)
    {

        Locatie aux(*this);
        this->rating[0]++;
        return aux;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Locatie& locatie){
    out<<"Tara:"<<" "<<locatie.tara<<endl;
    out<<"Orasul:"<<" "<<locatie.oras<<endl;
    out<<"Sectorul:"<<" "<<locatie.sector<<endl;
    out<<"Magazinul:"<<" "<<locatie.magazin<<endl;
    if (locatie.rating!=NULL )
    {
        for (int i=0; i<locatie.nrRating;i++)
        {
            out<<"Rating-ul"<<" "<<i+1<<" este:"<<" "<<locatie.rating[i]<<endl;
        }
    }
    return out;
}

istream& operator>>(istream& in, Locatie& locatie){
    cout<<"Tara"<<endl;
    in>>locatie.tara;
    cout<<"Oras"<<endl;
    in>>locatie.oras;
    cout<<"Sector"<<endl;
    in>>locatie.sector;
    cout<<"Magazin"<<endl;
    in>>locatie.magazin;
    cout<<"Cate rating-uri"<<endl;
    in>>locatie.nrRating;
    if(locatie.rating!=NULL)
        delete[] locatie.rating;
    locatie.rating=new int[locatie.nrRating];
    for (int i=0; i<locatie.nrRating;i++)
    {

        cout<<"Rating-ul"<<" "<<i<<" "<<"este:"<< " "<<endl;
        in>>locatie.rating[i];

    }
    return in;

}

void Locatie::afisareRatinguri(){
    if (this->rating!=NULL)
    {
        for (int i=0; i<this->nrRating;i++)
        {

            cout<<"Rating-urile locatiei sunt:"<<" "<<this->rating[i]<<endl;
        }
    }

}

Locatie::~Locatie(){
    if(this->rating!=NULL)
        delete[] this->rating;

}

class Produs
{
private:
    char* nume;///atribute
    char material[100];
    bool rezistentaLaApa;
    string culoare;
    string brand;
    float pret;
    Locatie* disponibilitateInMagazin;/// vector alocat dinamic (de obiecte din clasa Locatie)
    const int codProdus;///atribut constant
    static int contorCod;///atribut static
    int nrMagazine;
public:
    Produs();/// constructor fara parametri (prototip)
    Produs(char* nume, char material[], bool rezistenta, string culoare, string brand, float pret, Locatie* disponibilitateInMagazin, int nrMagazine);///constructor cu parametri
    Produs(const Produs& produs);///cc
    const char* getMaterial() const;///get
    const char* getNume() const;
    bool getRezistenta()const;
    string getCuloare()const;
    string getBrand() const;
    float getPret() const;
    int getNrMagazine() const;
    const int getCodProdus() const;
    void setCuloare(string culoare);///set
    void setNume(char* nume);
    void setMaterial(char material[]);
    void setRezistentaLaApa(bool rezistent);
    void setBrand(string brand);
    void setNrMagazine(int numar);
    void setPret(float pret);

    explicit operator int() ///supraincararea operatorului cast
    {
        return (int)this->pret;
    }
    bool operator==(const Produs& produs);///supraincarcare op==
    Produs& operator++();
    Produs operator++(int);

    Produs& operator=(const Produs& produs);///operator de atribuire
    Locatie operator[] (int index);///supraincarcare op []
    friend Produs operator+(Produs p, const Locatie& loc);///operatie de adunare intre clase +comutativitate
    friend Produs operator+(const Locatie& loc, Produs p);///adunare intre clase
    friend istream& operator>>(istream& in, Produs& produs);///operator flux de citire
    friend ostream& operator<<(ostream& out, const Produs& produs);///operator flux de afisare

    void afisare();///functionalitate-> afiseaza diverse caracteristici ale produsului cautat
    ~Produs();///destructor
};
Produs:: Produs():codProdus(contorCod++){
    this->disponibilitateInMagazin=NULL;
    nume= new char[strlen("neinitializat")+1];
    strcpy(this->nume,"neinitializat");
    this->rezistentaLaApa= true;
    this->culoare="-";
    strcpy(this->material,"-");
    this->brand="-";
    this->pret=0;
    this->disponibilitateInMagazin=NULL;
    this->nrMagazine=0;
}

Produs:: Produs(char* nume, char material[], bool rezistenta, string culoare, string brand, float pret, Locatie* disponibilitateInMagazin, int nrMagazine):codProdus(contorCod++){
    this->nrMagazine=nrMagazine;
    this->disponibilitateInMagazin=new Locatie[nrMagazine];
    for(int i=0;i<nrMagazine;i++)
    {
        this->disponibilitateInMagazin[i]=disponibilitateInMagazin[i];
    }
    this->nume= new char[strlen(nume)+1];
    strcpy(this->nume,nume);
    strcpy(this->material,material);
    this->rezistentaLaApa=rezistenta;
    this->culoare=culoare;
    this->brand=brand;
    this->pret=pret;
}

Produs:: Produs(const Produs& produs):codProdus(produs.codProdus){
    this->nrMagazine=produs.nrMagazine;
    this->disponibilitateInMagazin=new Locatie[produs.nrMagazine];
    for(int i=0;i<produs.nrMagazine;i++)
    {
        this->disponibilitateInMagazin[i]=produs.disponibilitateInMagazin[i];
    }
    nume= new char[strlen(produs.nume)+1];
    strcpy(this->nume,produs.nume);
    strcpy(this->material,produs.material);
    this->rezistentaLaApa=produs.rezistentaLaApa;
    this->culoare=produs.culoare;
    this->brand=produs.brand;
    this->pret=produs.pret;
}

Produs& Produs::operator=(const Produs& produs){
    if( this!= &produs)
    {
        if(this->nume !=NULL)
            delete[] this->nume;
        this->nume= new char[strlen(produs.nume)+1];
        strcpy(this->nume, produs.nume);
        this->brand=produs.brand;
        this-> culoare= culoare;
        this->pret=produs.pret;
        strcpy( this->material, produs.material);
        this->nrMagazine=produs.nrMagazine;
        if (this->disponibilitateInMagazin!=NULL)
            delete[] this->disponibilitateInMagazin;
        this->disponibilitateInMagazin= new Locatie[produs.nrMagazine];
        for (int i=0;i<produs.nrMagazine;i ++)
        {
            this->disponibilitateInMagazin[i]=produs.disponibilitateInMagazin[i];
        }

    }
    return *this;

}

const char* Produs::getMaterial() const{
    return &material[0];
}

const char* Produs::getNume() const{
    return this->nume;
}

bool Produs:: getRezistenta()const{
    return this->rezistentaLaApa;
}

string Produs:: getCuloare()const {
    return this->culoare;
}

string Produs:: getBrand() const{
    return this->brand;
}

float Produs:: getPret() const{
    return this->pret;
}

const int Produs:: getCodProdus() const{
    return this->contorCod;
}

int Produs:: getNrMagazine() const{
    return this->nrMagazine;
}

void Produs:: setMaterial(char material[]){
    strcpy(this->material, material);
}

void Produs::setCuloare(string culoare){
    this->culoare= culoare;
}

void Produs::setNume(char* nume){
    if (this->nume !=NULL)
        delete[] this->nume;
    this->nume= new char[strlen(nume)+1];
    strcpy(this->nume,nume);
}

void Produs:: setBrand(string brand){
    this->brand=brand;
}

void Produs:: setPret(float pret){
    this->pret=pret;
}

void Produs:: setRezistentaLaApa(bool rezistent){
    this->rezistentaLaApa=rezistent;
}

void Produs:: setNrMagazine(int numar){
    this->nrMagazine=numar;
}

Produs& Produs:: operator++()
{
    this->nrMagazine++;
    return *this;
}

Produs Produs:: operator++(int)
{
    Produs aux(*this);
    this->nrMagazine++;
    return aux;
}

Produs operator+(Produs p, const Locatie& loc){
    Locatie* disponibilitateInMagazinAux;
    disponibilitateInMagazinAux=new Locatie[p.nrMagazine];
    for (int i=0;i<p.nrMagazine;i++)
    {
        disponibilitateInMagazinAux[i]=p.disponibilitateInMagazin[i];
    }
    if (p.disponibilitateInMagazin!=NULL)
        delete[] p.disponibilitateInMagazin;
    p.nrMagazine++;

    p.disponibilitateInMagazin=new Locatie[p.nrMagazine];
    for (int i=0; i<p.nrMagazine-1; i++)
    {
        p.disponibilitateInMagazin[i]= disponibilitateInMagazinAux[i];
    }
    p.disponibilitateInMagazin[p.nrMagazine-1]=loc;
    if (disponibilitateInMagazinAux!=NULL)
        delete[] disponibilitateInMagazinAux;
    return p;

}

Produs operator+(const Locatie& loc, Produs p){
    Locatie* disponibilitateInMagazinAux;
    disponibilitateInMagazinAux=new Locatie[p.nrMagazine];
    for (int i=0;i<p.nrMagazine;i++)
    {
        disponibilitateInMagazinAux[i]=p.disponibilitateInMagazin[i];
    }
    if (p.disponibilitateInMagazin!=NULL)
        delete[] p.disponibilitateInMagazin;
    p.nrMagazine++;

    p.disponibilitateInMagazin=new Locatie[p.nrMagazine];
    for (int i=0; i<p.nrMagazine-1; i++)
    {
        p.disponibilitateInMagazin[i]= disponibilitateInMagazinAux[i];
    }
    p.disponibilitateInMagazin[p.nrMagazine-1]=loc;
    if (disponibilitateInMagazinAux!=NULL)
        delete[] disponibilitateInMagazinAux;

    return p;

}

bool Produs::operator==(const Produs& produs){
    if (this->culoare==produs.culoare && this->brand==produs.brand)
        return true;
    return false;
}

istream& operator>>(istream& in, Produs& produs){
    char aux[100];
    cout<<"Nume produs:"<<endl;
    in>>aux;

    if (produs.nume !=NULL)
        delete[] produs.nume;

    produs.nume= new char[strlen(aux)+1];
    strcpy(produs.nume,aux);

    cout<<"Material produs:"<<endl;
    in>>produs.material;
    cout<<"Rezistenta la apa (1- este rezistent, 0- nu este rezistent)"<<endl;
    in>>produs.rezistentaLaApa;
    cout<<"Culoare:"<<endl;
    in>>produs.culoare;
    cout<<"Brand:"<<endl;
    in>>produs.brand;
    cout<<"Pret:"<<endl;
    in>>produs.pret;
    cout<<"nr magazine:"<<endl;
    in>>produs.nrMagazine;
    produs.disponibilitateInMagazin = new Locatie[produs.nrMagazine];
    for(int i=0; i<produs.nrMagazine; i++)
    {
        cout<<"citeste locatia "<<" "<<i+1<<" "<<":"<<endl;
        in>>produs.disponibilitateInMagazin[i];
    }


    return in;
}

Locatie Produs:: operator[] (int index){
    if(0<=index && index<this->nrMagazine)
        return this->disponibilitateInMagazin[index];
    cout<<"Index ales gresit"<<endl;
}

ostream& operator<<(ostream& out, const Produs& produs){
    out<<"Numele produsului este"<<" "<<produs.nume<<endl;
    out<<"Materialul produsului este"<<" "<<produs.material<<endl;
    out<<"Rezistenta la apa este"<<" "<<produs.rezistentaLaApa<<endl;
    out<<"Culoarea produsului este"<<" "<<produs.culoare<<endl;
    out<<"Brandul este"<<" "<<produs.brand<<endl;
    out<<"Pretul este"<<" "<<produs.pret<<endl;
    out<<"Produsul se gaseste in "<<" "<<produs.nrMagazine<<" "<<"magazine"<<endl;
    for(int i=0; i<produs.nrMagazine; i++)
    {
        out<<"Locatia"<<" "<<i+1<<" "<<"in care se gaseste produsul cautat este"<<produs.disponibilitateInMagazin[i]<<endl;
    }

    return out;
}

void Produs::afisare(){
    cout<<"Produsul vestimentar ales: "<<" "<<this->nume<<endl;
    cout<<"Codul produsului este"<<" "<<this->codProdus<<endl;
    cout<<"Meterialul produsului este"<<" "<<this->material<<endl;
    cout<<"Produsul";
    if (this->rezistentaLaApa== true)
        cout<<" "<<"este rezistent la apa"<<endl;
    else
        cout<<" "<<"nu este rezistent la apa"<<endl;
    cout<<"Produsul are culoarea"<<" "<<this->culoare<<endl;
    cout<<"Brandul produsului este"<<" "<<this->brand<<endl;
    if (this->pret>19)
        cout<<"Pretul este de"<<" "<<this->pret<<" "<<"de lei"<<endl;
    else
        cout<<"Pretul este de"<<" "<<this->pret<<" "<<"lei"<<endl;

    cout<<endl;
}

Produs::~Produs(){
    if (this->nume !=NULL)
        delete[] this->nume;
    if( this->disponibilitateInMagazin!=NULL)
        delete[] this->disponibilitateInMagazin;

}
int Produs::contorCod=1000;



class Accesoriu
{private:
    string numeAccesoriu;///atribute
    bool vineLaSet;
    double pret;

    float* reduceriRecente;///vector alocat dinamic
    int nrReduceri;

public:
    Accesoriu();///constructor fara param
    Accesoriu(string numeAccesoriu, bool vineLaSet);///constructor cu param
    Accesoriu(string numeAccesoriu, bool vineLaSet ,double pret ,int nrReduceri ,float* reduceriRecente);///constructor cu param
    Accesoriu(const Accesoriu& accesoriu);///cc
    Accesoriu& operator=(const Accesoriu& accesoriu);///operator de atribuire

    void setNumeAccesoriu(string numeAccesoriu);///set
    void setVineLaSet( bool vineLaSet);
    void setPret(double pret);
    void setReduceriRecente(float* reduceriRecente,int nrReduceri);

    string getNumeAccesoriu() const;///get
    bool getVineLaSet() const;
    double getPret() const;
    const float* getReduceriRecente() const;

    Accesoriu operator+(const Accesoriu& accesoriu);///supraincarcarea op + (operatie la nivel de clasa)
    Accesoriu operator-(const Accesoriu& accesoriu);///supraincarcarea op-
    const Accesoriu& operator++();///pre-incrementare
    const Accesoriu operator++(int);///post-incrementare
    bool operator>= (const Accesoriu& accesoriu);/// operatorul >=
    bool operator==(const Accesoriu& accesoriu);/// operatorul ==
    float operator[] (int index);///operatorul []
    explicit operator int() ///supraincararea operatorului cast
    {
        return (int)this->pret;
    }

    friend istream& operator>>(istream& in, Accesoriu& accesoriu);///functie prietena; supraincarcarea op>>
    friend ostream& operator<<(ostream& out,const Accesoriu& accesoriu);///supraincarcarea op<<
    void afisareReduceriRecente();///functionalitate-> afiseaza accesoriile care vin la set
    ~Accesoriu();///destructor

};

Accesoriu::Accesoriu(){
    this->numeAccesoriu=" ";
    this->vineLaSet= true;
    this->pret=0;
    this->nrReduceri=0;
    this->reduceriRecente=NULL;
}

Accesoriu::Accesoriu(string numeAccesoriu, bool vineLaSet){
    this->numeAccesoriu=numeAccesoriu;
    this->vineLaSet= vineLaSet;
    this->pret=0;
    this->nrReduceri=0;
    this->reduceriRecente=NULL;
}

Accesoriu::Accesoriu(string numeAccesoriu, bool vineLaSet ,double pret ,int nrReduceri ,float* reduceriRecente){
    this->numeAccesoriu=numeAccesoriu;
    this->vineLaSet= vineLaSet;
    this->pret=pret;
    this->nrReduceri=nrReduceri;
    this->reduceriRecente=new float[this->nrReduceri];
    for(int i=0; i<nrReduceri; i++)
    {
        this->reduceriRecente[i]=reduceriRecente[i];
    }
}

Accesoriu:: Accesoriu(const Accesoriu& accesoriu){
    this->numeAccesoriu=accesoriu.numeAccesoriu;
    this->vineLaSet= accesoriu.vineLaSet;
    this->pret=accesoriu.pret;
    this->nrReduceri=accesoriu.nrReduceri;
    this->reduceriRecente=new float[accesoriu.nrReduceri];
    for(int i=0; i<accesoriu.nrReduceri; i++)
    {
        this->reduceriRecente[i]=accesoriu.reduceriRecente[i];
    }
}

Accesoriu& Accesoriu::operator=(const Accesoriu& accesoriu){
    if(this != &accesoriu)
    {
        this->numeAccesoriu=accesoriu.numeAccesoriu;
        this->vineLaSet= accesoriu.vineLaSet;
        this->pret=accesoriu.pret;
        this->nrReduceri=accesoriu.nrReduceri;
        if (this->reduceriRecente!=NULL)
            delete[] this->reduceriRecente;
        this->reduceriRecente= new float[accesoriu.nrReduceri];
        for(int i=0; i< accesoriu.nrReduceri; i++)
        {
            this->reduceriRecente[i]==accesoriu.reduceriRecente[i];
        }
    }
    return *this;
}

void Accesoriu::setNumeAccesoriu(string numeAccesoriu){ ///set
    this->numeAccesoriu=numeAccesoriu;
}

void Accesoriu::setVineLaSet( bool vineLaSet){
    this->vineLaSet=vineLaSet;
}

void Accesoriu::setPret(double pret){
    this->pret=pret;
}

void Accesoriu::setReduceriRecente(float* reduceriRecente,int nrReduceri){
    if(this->reduceriRecente!=NULL)
        delete[] this->reduceriRecente;
    this->nrReduceri=nrReduceri;
    this->reduceriRecente=new float[nrReduceri];
    for(int i=0; i<nrReduceri; i++)
    {
        this->reduceriRecente[i]=reduceriRecente[i];
    }
}

string Accesoriu::getNumeAccesoriu() const{ ///get
    return this->numeAccesoriu;
}

bool Accesoriu::getVineLaSet() const{
    return this->vineLaSet;
}

double Accesoriu::getPret() const{
    return this->pret;
}

const float* Accesoriu::getReduceriRecente() const{
    return this->reduceriRecente;
}


Accesoriu Accesoriu::operator+(const Accesoriu& accesoriu){
    this->pret= this->pret+ accesoriu.pret;
    return *this;
}

Accesoriu Accesoriu::operator-(const Accesoriu& accesoriu){
    if(this->pret >= accesoriu.pret)
        this->pret= this->pret- accesoriu.pret;
    else
        this->pret= accesoriu.pret- this->pret;
    return *this;
}

const Accesoriu& Accesoriu::operator++(){
    this->pret++;
    return *this;

}

const Accesoriu Accesoriu::operator++(int){
    Accesoriu aux (*this);
    this->pret++;
    return aux;

}

bool Accesoriu::operator>= (const Accesoriu& accesoriu){
    if(this->nrReduceri>= accesoriu.nrReduceri)
        return true;
    return false;
}

bool Accesoriu::operator==(const Accesoriu& accesoriu){
    if (this->reduceriRecente!=NULL && accesoriu.reduceriRecente!=NULL)
    {
        if(this->reduceriRecente==accesoriu.reduceriRecente)
            return true;
        return false;
    }
    return true;
}

float Accesoriu::operator[] (int index){
    if(this->reduceriRecente!=NULL)
        if(0<=index && index<this->nrReduceri)
            return this->reduceriRecente[index];
    cout<<"Index ales gresit"<<endl;
    return 0;
    cout<<"Vector nul"<<endl;
    return 0;
}

istream& operator>>(istream& in, Accesoriu& accesoriu){
    cout<<"Numele accesoriului este"<<endl;
    in>>accesoriu.numeAccesoriu;
    cout<<"Accesoriul face parte dintr-un set? (Selectati 1 daca face parte si 0 daca nu face parte)"<<endl;
    in>>accesoriu.vineLaSet;
    cout<<"Pretul accesoriului este"<<endl;
    in>>accesoriu.pret;
    cout<<"Numarul reducerilor recente"<<endl;
    in>>accesoriu.nrReduceri;
    if(accesoriu.reduceriRecente!=NULL)
        delete[] accesoriu.reduceriRecente;
    accesoriu.reduceriRecente= new float[accesoriu.nrReduceri];
    for(int i=0; i<accesoriu.nrReduceri; i++)
    {
        cout<<"Pentru reducerea"<<" "<<i+1<<" "<<"pretul accesoriului este de"<<endl;
        in>>accesoriu.reduceriRecente[i];
    }
    return in;
    cout<<endl;
}

ostream& operator<<(ostream& out,const Accesoriu& accesoriu){
    out<<"Numele accesoriului este"<<" "<<accesoriu.numeAccesoriu<<endl;
    if(accesoriu.vineLaSet==true)
        out<<"Accesoriul face parte dintr-un set"<<endl;
    else
        out<<"Accesoriul nu face parte dintr-un set"<<endl;
    out<<"Pretul accesoriului este"<<" "<<accesoriu.pret<<endl;
    out<<"Numarul reducerilor recente este"<<" "<<accesoriu.nrReduceri<<endl;
    for(int i=0; i<accesoriu.nrReduceri; i++)
    {
        out<<"Pentru reducerea"<<" "<<i+1<<" "<<"pretul accesoriului este de"<<" "<<accesoriu.reduceriRecente[i]<<endl;
    }
    return out;

}

void Accesoriu::afisareReduceriRecente(){
    if(this->reduceriRecente!=NULL)
    {
        cout<<"Pentru accesoriul"<<" "<<this->numeAccesoriu<<" "<<"avem urmatoarele reduceri aferente"<<endl;
        for(int i=0; i<this->nrReduceri; i++)
        {
            cout<<"Pentru reducerea"<<" "<<i+1<<" "<<"pretul accesoriului este de"<<" "<<this->reduceriRecente[i]<<endl;
        }

    }
    cout<<endl;
}

Accesoriu::~Accesoriu(){
    if( this->reduceriRecente!=NULL)
        delete[] this->reduceriRecente;
}


class Brand
{private:
    char* numeBrand;///vector dinamic de caractere (caracterele numelui)
    const int idBrand;///atribut constant
    static int contorId;///atribut static
    int nrAccesorii;
    int nrProduse;
    Accesoriu* gamaAccesorii;///vector dinamic de accesorii
    Produs* gamaProduse;///vector dinamic de produse
public:
    Brand();///constructor fara parametri
    Brand(char* numeBrand);/// constructor cu parametri
    Brand(char* numeBrand,int nrAccesorii, int nrProduse, Accesoriu* gamaAccesorii, Produs* gamaProduse);/// constructor cu parametri
    Brand(const Brand& brand);///copy constructor
    Brand& operator=(const Brand& brand);///operator de atribuire

    void setNumeBrand(char* numeBrand);///set
    void setGamaAccesorii(Accesoriu* gamaAccesorii, int nrAccesorii);
    void setGamaProduse(Produs* gamaProduse, int nrProduse);

    const char* getNumeBrand() const;///get
    const Accesoriu* getGamaAccesorii() const;
    const Produs* getGamaProduse() const;

    const Brand& operator++();///pre-incrementare
    const Brand operator++(int);///post-incrementare
    Produs operator[](int index);/// operatorul []
    explicit operator int() ///supraincararea operatorului cast
    {
        return (int)this->nrAccesorii;
    }

    Brand operator+(int numar);///adunacre intre obiect si intreg
    Brand operator+(const Brand& brand);/// adunare intre doua obiecte (din aceeasi clasa)
    Brand operator/(const Brand& brand);/// operatorul matematic /
    bool operator<=(const Brand& brand);///operator conditional
    bool operator==(const Brand& brand);/// operator pentru egalitate
    friend ostream& operator<<(ostream& out, const Brand& brand);/// supraincarcarea op<<
    friend istream& operator>>(istream& in, Brand& brand);/// supraincarcarea op>>
    void afisareGamaProduse();/// functionalitate-> afiseaza produsele care apartin unui anumit Brand
    ~Brand();///destructor

};

Brand::Brand():idBrand(contorId++){
    this->nrAccesorii=0;
    this->nrProduse=0;
    this->numeBrand=new char[strlen("anonim")+1];
    strcpy(this->numeBrand,"anonim");
    this->gamaAccesorii=NULL;
    this->gamaProduse=NULL;

}

Brand::Brand(char* numeBrand):idBrand(contorId++){
    this->nrAccesorii=0;
    this->nrProduse=0;
    this->numeBrand=new char[strlen(numeBrand)+1];
    strcpy(this->numeBrand,numeBrand);
    this->gamaAccesorii=NULL;
    this->gamaProduse=NULL;

}

Brand::Brand(char* numeBrand,int nrAccesorii, int nrProduse, Accesoriu* gamaAccesorii, Produs* gamaProduse):idBrand(contorId++){
    this->nrAccesorii= nrAccesorii;
    this->nrProduse=nrProduse;
    this->numeBrand=new char[strlen(numeBrand)+1];
    strcpy(this->numeBrand,numeBrand);
    this->gamaAccesorii=new Accesoriu[nrAccesorii];
    for (int i=0; i<nrAccesorii; i++)
    {
        this->gamaAccesorii[i]==gamaAccesorii[i];
    }
    this->gamaProduse=new Produs[nrProduse];
    for (int i=0; i<nrProduse; i++)
    {
        this->gamaProduse[i]==gamaProduse[i];
    }
}

Brand::Brand(const Brand& brand):idBrand(brand.idBrand){
    this->nrAccesorii= brand.nrAccesorii;
    this->nrProduse=brand.nrProduse;
    this->numeBrand=new char[strlen(brand.numeBrand)+1];
    strcpy(this->numeBrand,brand.numeBrand);
    this->gamaAccesorii=new Accesoriu[brand.nrAccesorii];
    for (int i=0; i<brand.nrAccesorii; i++)
    {
        this->gamaAccesorii[i]==brand.gamaAccesorii[i];
    }
    this->gamaProduse=new Produs[brand.nrProduse];
    for (int i=0; i<brand.nrProduse; i++)
    {
        this->gamaProduse[i]==brand.gamaProduse[i];
    }

}

Brand& Brand::operator=(const Brand& brand){
    if (this!= &brand)
    {

        this->nrAccesorii=brand.nrAccesorii;
        this->nrProduse= brand.nrProduse;

        if (this->numeBrand!=NULL)
            delete[] this->numeBrand;
        this->numeBrand=new char[strlen(brand.numeBrand)+1];
        strcpy(this->numeBrand, brand.numeBrand);

        if (this->gamaAccesorii!=NULL)
            delete[] this->gamaAccesorii;
        this->gamaAccesorii= new Accesoriu[brand.nrAccesorii];
        for (int i=0; i<brand.nrAccesorii; i++)
        {
            this->gamaAccesorii[i]==brand.gamaAccesorii[i];
        }

        if (this->gamaProduse!=NULL)
            delete[] this->gamaProduse;
        this->gamaProduse=new Produs[brand.nrProduse];
        for (int i=0; i<brand.nrProduse; i++)
        {
            this->gamaProduse[i]==brand.gamaProduse[i];
        }

    }
    return *this;

}

void Brand::setNumeBrand(char* numeBrand){  ///set
    if (this->numeBrand!=NULL)
        delete[] this->numeBrand;
    this->numeBrand=new char[strlen(numeBrand)+1];
    strcpy(this->numeBrand, numeBrand);

}

void Brand::setGamaAccesorii(Accesoriu* gamaAccesorii, int nrAccesorii){
    this->nrAccesorii= nrAccesorii;
    if (this->gamaAccesorii!=NULL)
        delete[] this->gamaAccesorii;
    this->gamaAccesorii= new Accesoriu[nrAccesorii];
    for (int i=0; i<nrAccesorii; i++)
    {
        this->gamaAccesorii[i]==gamaAccesorii[i];
    }

}

void Brand::setGamaProduse(Produs* gamaProduse, int nrProduse){
    this->nrProduse= nrProduse;
    if (this->gamaProduse!=NULL)
        delete[] this->gamaProduse;
    this->gamaProduse=new Produs[nrProduse];
    for (int i=0; i<nrProduse; i++)
    {
        this->gamaProduse[i]==gamaProduse[i];
    }

}

const char* Brand::getNumeBrand() const{   ///get
    return this->numeBrand;
}

const Accesoriu* Brand::getGamaAccesorii() const{
    return this->gamaAccesorii;
}

const Produs* Brand::getGamaProduse() const{
    return this->gamaProduse;
}

const Brand& Brand::operator++(){
    this->nrProduse++;
    return *this;

}

const Brand Brand::operator++(int){
    Brand aux(*this);
    this->nrProduse++;
    return aux;

}

Produs Brand::operator[](int index){
    if(this->gamaProduse!=NULL)
    {
        if(0<= index && index<this->nrProduse)
            return this->gamaProduse[index];
        cout<<"Index introdus gresit"<<endl;
    }

}

Brand Brand::operator+(int numar){
    this-> nrAccesorii= this-> nrAccesorii+ numar;
    return *this;
}

Brand Brand::operator+(const Brand& brand){
    this->nrAccesorii= this->nrAccesorii + brand.nrAccesorii;
    return *this;

}

Brand Brand::operator/(const Brand& brand){
    if (this->nrAccesorii !=0)
    {
        this->nrAccesorii= brand.nrAccesorii/ this->nrAccesorii;
        return *this;
    }
    else
    {
        if (brand.nrAccesorii!=0)
        {

            this->nrAccesorii= this->nrAccesorii/ brand.nrAccesorii;
            return *this;
        }
    }
    cout<<"Nu se poate realiza operatia"<<endl;
    return *this;
}

bool Brand::operator<=(const Brand& brand){
    if(this->nrAccesorii <= brand.nrAccesorii)
        return true;
    return false;


}

bool Brand::operator==(const Brand& brand){
    if(this->nrAccesorii == brand.nrAccesorii)
        return true;
    return false;

}

ostream& operator<<(ostream& out, const Brand& brand){
    out<<"Numele brandului este"<<" "<<brand.numeBrand<<endl;
    if(brand.nrProduse<20)
        out<<"Avem"<<" "<<brand.nrProduse<<" "<<"produse"<<endl;
    else
        out<<"Avem"<<" "<<brand.nrProduse<<" "<<"de produse"<<endl;
    if (brand.gamaProduse!=NULL)
    {

        for(int i=0; i<brand.nrProduse; i++)
        {
            out<<"Produsul"<<" "<<i+1<<" "<<"este"<<" "<<brand.gamaProduse[i]<<endl;

        }
    }
    if (brand.nrAccesorii<20)
        out<<"Avem"<<" "<<brand.nrAccesorii<<" "<<"accesorii"<<endl;
    else
        out<<"Avem"<<" "<<brand.nrAccesorii<<" "<<"de accesorii"<<endl;
    if (brand.gamaAccesorii!=NULL)
    {

        for(int i=0; i<brand.nrAccesorii; i++)
        {
            out<<"Accesoriul"<<" "<<i+1<<" "<<"este"<<" "<<brand.gamaAccesorii[i]<<endl;

        }
    }
    return out;

}

istream& operator>>(istream& in, Brand& brand){
    char aux[100];
    cout<<"Numele brandului este"<<endl;
    in>>aux;
    if (brand.numeBrand!=NULL)
        delete[] brand.numeBrand;
    brand.numeBrand=new char[strlen(aux)+1];
    strcpy(brand.numeBrand, aux);

    cout<<"Numarul de produse este"<<endl;
    in>>brand.nrProduse;
    cout<<"Numarul de accesorii este"<<endl;
    in>>brand.nrAccesorii;

    if (brand.gamaProduse!=NULL)
        delete brand.gamaProduse;
    brand.gamaProduse= new Produs[brand.nrProduse];
    for(int i=0; i<brand.nrProduse; i++)
    {
        cout<<"Produsul"<<" "<<i+1<<" "<<"este"<<endl;
        in>>brand.gamaProduse[i];

    }

    if (brand.gamaAccesorii!=NULL)
        delete[] brand.gamaAccesorii;
    brand.gamaAccesorii= new Accesoriu[brand.nrAccesorii];
    for(int i=0; i<brand.nrAccesorii; i++)
    {
        cout<<"Accesoriul"<<" "<<i+1<<" "<<"este"<<endl;
        in>>brand.gamaAccesorii[i];

    }


    return in;


}

void Brand::afisareGamaProduse(){
    if (this->gamaProduse!=NULL)
    {
        for(int i=0; i<this->nrProduse; i++)
        {
            cout<<"Produsul"<<" "<<i+1<<" "<<"este"<<" "<<this->gamaProduse[i]<<endl;

        }
    }


}

Brand::~Brand(){
    if (this->numeBrand!=NULL)
        delete[] this->numeBrand;
    if (this->gamaProduse!=NULL)
        delete[] this->gamaProduse;
    if (this->gamaAccesorii!=NULL)
        delete[] this->gamaAccesorii;

}
int Brand::contorId=1000;

void MeniuLocatii(vector <Locatie> &listaLocatii){
        cout<<"========= Meniu locatii ========"<<endl;
        cout<<"Apasati 1 pentru a adauga o locatie in lista"<<endl;
        cout<<"Apasati 2 pentru a actualiza tara unei locatiI din lista"<<endl;
        cout<<"Apasati 3 pentru a sterge o locatie din lista"<<endl;
        cout<<"Apasati 4 pentru a afisa lista de locatii"<<endl;

        int opt;
        cout<<"Dati numarul optiunii: ";
        cin>>opt;
        switch(opt) {
            case 1: {
                // create + read
                Locatie *loc = new Locatie();
                cin>>*loc;
                listaLocatii.push_back(*loc);
                break;
            }
            case 2: {
                // update
                int index;
                cout<<"Dati indexul locatiei din lista(incepand de la 0): ";
                cin>>index;
                string numeTara;
                cout<<"Dati numele tarii: ";
                cin>>numeTara;
                listaLocatii[index].setTara(numeTara);
                cout<<"Locatia a fost modificata cu succes"<<endl;
                cout<<listaLocatii[index];
                break;
            }
            case 3: {
                // delete
                int index;
                cout<<"Dati indexul locatiei din lista pe care vreti sa o stergeti(incepand de la 0): ";
                cin>>index;
                listaLocatii.erase(listaLocatii.begin() + index);
                break;
            }
            case 4: {
                // show list
                bool show = false;
                for (Locatie  element : listaLocatii) {
                    show = true;
                    cout<<"======== Locatie ==========="<<endl;
                    cout<<element;
                }
                if(show == false){
                    cout<<"Nu este niciun element in lista"<<endl;
                }
                break;
            }
        }

}

void MeniuProduse(vector <Produs> &listaProduse){
    cout<<"========= Meniu produse ========"<<endl;
    cout<<"Apasati 1 pentru a adauga un produs in lista"<<endl;
    cout<<"Apasati 2 pentru a actualiza numele unui produs din lista"<<endl;
    cout<<"Apasati 3 pentru a sterge un produs din lista"<<endl;
    cout<<"Apasati 4 pentru a afisa lista de produse"<<endl;

    int opt;
    cout<<"Dati numarul optiunii: ";
    cin>>opt;
    switch(opt) {
        case 1: {
            // create + read
            Produs *prod = new Produs();
            cin>>*prod;
            listaProduse.push_back(*prod);
            break;
        }
        case 2: {
            // update
            int index;
            cout<<"Dati indexul prdusului din lista(incepand de la 0): ";
            cin>>index;
            char numeProdus[20];
            cout<<"Dati numele nou al produsului: ";

            cin.get();
            cin.getline(numeProdus, 20);
            listaProduse[index].setNume(numeProdus);
            cout<<"Produsul a fost modificata cu succes"<<endl;
            cout<<listaProduse[index];
            break;
        }
        case 3: {
            // delete
            int index;
            cout<<"Dati indexul produsului din lista pe care vreti sa-l stergeti(incepand de la 0): ";
            cin>>index;
            listaProduse.erase(listaProduse.begin() + index);
            break;
        }
        case 4: {
            // show list
            bool show = false;
            for (Produs  element : listaProduse) {
                show = true;
                cout<<"======== Produs ==========="<<endl;
                cout<<element;
            }
            if(show == false){
                cout<<"Nu este niciun element in lista"<<endl;
            }
            break;
        }
    }

}

void MeniuAccesorii(vector <Accesoriu> &listaAccesorii){
    cout<<"========= Meniu accesorii ========"<<endl;
    cout<<"Apasati 1 pentru a adauga un accesoriu in lista"<<endl;
    cout<<"Apasati 2 pentru a actualiza numele unui accesoriu din lista"<<endl;
    cout<<"Apasati 3 pentru a sterge un accesoriu din lista"<<endl;
    cout<<"Apasati 4 pentru a afisa lista de accesorii"<<endl;

    int opt;
    cout<<"Dati numarul optiunii: ";
    cin>>opt;
    switch(opt) {
        case 1: {
            // create + read
            Accesoriu *accesoriu= new Accesoriu();
            cin>>*accesoriu;
            listaAccesorii.push_back(*accesoriu);
            break;
        }
        case 2: {
            // update
            int index;
            cout<<"Dati indexul accesoriului din lista(incepand de la 0): ";
            cin>>index;
            string numeAccesoriu;
            cout<<"Dati numele nou al accesoriului: ";
            cin>>numeAccesoriu;
            listaAccesorii[index].setNumeAccesoriu(numeAccesoriu);
            cout<<"Accesoriul a fost modificat cu succes"<<endl;
            cout<<listaAccesorii[index];
            break;
        }
        case 3: {
            // delete
            int index;
            cout<<"Dati indexul produsului din lista pe care vreti sa-l stergeti(incepand de la 0): ";
            cin>>index;
            listaAccesorii.erase(listaAccesorii.begin() + index);
            break;
        }
        case 4: {
            // show list
            bool show = false;
            for (Accesoriu  element : listaAccesorii) {
                show = true;
                cout<<"======== Accesoriu ==========="<<endl;
                cout<<element;
            }
            if(show == false){
                cout<<"Nu este niciun element in lista"<<endl;
            }
            break;
        }
    }

}

void MeniuBranduri(vector <Brand> &listaBranduri){
    cout<<"========= Meniu branduri ========"<<endl;
    cout<<"Apasati 1 pentru a adauga un brand in lista"<<endl;
    cout<<"Apasati 2 pentru a actualiza numele unui brand din lista"<<endl;
    cout<<"Apasati 3 pentru a sterge un brand din lista"<<endl;
    cout<<"Apasati 4 pentru a afisa lista de branduri"<<endl;

    int opt;
    cout<<"Dati numarul optiunii: ";
    cin>>opt;
    switch(opt) {
        case 1: {
            // create + read
            Brand *brand= new Brand();
            cin>>*brand;
            listaBranduri.push_back(*brand);
            break;
        }
        case 2: {
            // update
            int index;
            cout<<"Dati indexul brandului din lista(incepand de la 0): ";
            cin>>index;
            char numeBrand[20];
            cout<<"Dati numele nou al brandului: ";
            cin.get();
            cin.getline(numeBrand,20);
            listaBranduri[index].setNumeBrand(numeBrand);
            cout<<"Brandul a fost modificat cu succes"<<endl;
            cout<<listaBranduri[index];
            break;
        }
        case 3: {
            // delete
            int index;
            cout<<"Dati indexul brandului din lista pe care vreti sa-l stergeti(incepand de la 0): ";
            cin>>index;
            listaBranduri.erase(listaBranduri.begin() + index);
            break;
        }
        case 4: {
            // show list
            bool show = false;
            for (Brand  element :listaBranduri) {
                show = true;
                cout<<"========= Brand ==========="<<endl;
                cout<<element;
            }
            if(show == false){
                cout<<"Nu este niciun element in lista"<<endl;
            }
            break;
        }
    }

}

int optiuniMeniuPrincipal(){
    cout<<"========= Meniu principal ========"<<endl;
    cout<<"Apasati 1 pentru meniul magazinelor"<<endl;
    cout<<"Apasati 2 pentru meniul produselor"<<endl;
    cout<<"Apasati 3 pentru meniul accesoriilor"<<endl;
    cout<<"Apasati 4 pentru meniul cu branduri"<<endl;

    int opt;
    cout<<"Dati numarul optiunii: ";
    cin>>opt;
    return opt;
}

int main(){

    vector <Locatie> listaLocatii;
    vector <Produs> listaProduse;
    vector <Accesoriu> listaAccesorii;
    vector <Brand> listaBranduri;
    do{
        int opt = optiuniMeniuPrincipal();
        switch(opt) {
            case 1: {
                MeniuLocatii(listaLocatii);
                break;
            }
            case 2: {
                MeniuProduse(listaProduse);
                break;
            }
            case 3: {
                MeniuAccesorii(listaAccesorii);
                break;
            }
            case 4: {
                MeniuBranduri(listaBranduri);
                break;
            }
        }
        cout<<"Vreti sa continuati (1-da/0-nu)?";
        cin>>opt;
        if(opt == 0){
            break;
        }
    }
    while(true);
}



