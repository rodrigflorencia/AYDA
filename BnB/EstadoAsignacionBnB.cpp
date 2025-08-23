#include "EstadoAsignacionBnB.H"
#define VACIA -1

EstadoAsignacionBnB::EstadoAsignacionBnB(int N)
{
    this->size_=N;
    this->nivel=-1;
    this->beneficio_acumulado=0;
    this->cota_local=0;
    this->asignacion.insert(this->asignacion.begin(),N,VACIA);
}

EstadoAsignacionBnB::EstadoAsignacionBnB()
{
    this->size_=0;
    this->nivel=-1;
    this->beneficio_acumulado=0;
    this->cota_local=0;
}

EstadoAsignacionBnB::EstadoAsignacionBnB(const EstadoAsignacionBnB & padre)
{
    this->size_=padre.getSize();
    this->nivel=padre.getNivel();
    this->beneficio_acumulado=padre.getBeneficio();
    this->cota_local=padre.getCotaLocal();
    this->asignacion.insert(this->asignacion.begin(),padre.asignacion.begin(),padre.asignacion.end());

}

EstadoAsignacionBnB::~EstadoAsignacionBnB() {}

void EstadoAsignacionBnB::asignar (int decision, int **B)
{
    this->nivel+=1;
    this->asignacion[decision]=this->nivel;
    this->beneficio_acumulado+=B[this->nivel][decision];
    this->cota_local=this->beneficio_acumulado;
    for (int d=0; d<this->getSize(); d++)
        if (d!=decision)
        {
            int max_=0;
            for (int n=this->nivel + 1; n<this->getSize(); n++)
            {
                if (max_< B[n][d])
                    max_ =  B[n][d];
            }
            this->cota_local+=max_;
        }
}

unsigned int EstadoAsignacionBnB::getCotaLocal () const
{
    return this->cota_local;
}

unsigned int EstadoAsignacionBnB::getBeneficio () const
{
    return this->beneficio_acumulado;
}

int EstadoAsignacionBnB::getNivel() const
{
    return this->nivel;
}

int EstadoAsignacionBnB::getSize() const
{
    return this->size_;
}

bool EstadoAsignacionBnB::estaAsignada (int decision ) const
{
    return (decision<this->getSize() && this->asignacion[decision]!=VACIA);
}

int EstadoAsignacionBnB::getAsignada (int decision) const
{
    return (decision < this->getSize()) ? this->asignacion[decision] : VACIA;
}

void EstadoAsignacionBnB::mostrar() const
{
    std::cout<<"Nivel: "<<this->nivel<< "\tCL: "<<this->getCotaLocal() <<"\tBeneficio acumulado: "<<this->getBeneficio()<<std::endl;
    for (int i=0; i<this->getSize(); i++)
    {
        std::cout<<i<<"->"<<this->asignacion[i]<<std::endl;
    }
    std::cout<<std::endl;
}

void EstadoAsignacionBnB::mostrar(std::string * niveles, std::string * decisiones) const
{
    std::cout<<"Nivel: "<<this->getNivel()<< "\tCL: "<<this->getCotaLocal() <<"\tBeneficio acumulado: "<<this->getBeneficio()<<std::endl;
    for (int i=0; i<this->getSize(); i++)
        std::cout<<decisiones[i]<<"->"<<niveles[this->asignacion[i]]<<std::endl;
    std::cout<<std::endl;
}

EstadoAsignacionBnB& EstadoAsignacionBnB::operator =(const EstadoAsignacionBnB &otro)
{
    if (this != &otro)
    {
        this->size_=otro.getSize();
        this->nivel=otro.getNivel();
        this->beneficio_acumulado=otro.getBeneficio();
        this->cota_local=otro.getCotaLocal();
        this->asignacion.insert(this->asignacion.begin(),otro.asignacion.begin(),otro.asignacion.end());

        // for (int i=0;i<otro.getSize();i++)
        //   this->asignacion[i]=otro.getAsignada(i);

    }
    return *this;
}
