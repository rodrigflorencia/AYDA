#ifndef ESTADOASIGNACIONBNB_H
#define ESTADOASIGNACIONBNB_H
#include <iostream>
#include <vector>
class EstadoAsignacionBnB
{
public:

    EstadoAsignacionBnB(int N);
    EstadoAsignacionBnB();
    EstadoAsignacionBnB(const EstadoAsignacionBnB & padre);
    virtual ~EstadoAsignacionBnB();

    void asignar ( int decision, int **B);

    unsigned int getCotaLocal () const;
    unsigned int getBeneficio () const;
    int getSize() const;
    int getNivel() const;
    bool estaAsignada (int decision ) const;
    int getAsignada (int decision) const;
    void mostrar() const;
    void mostrar(std::string * niveles, std::string * decisiones) const;
    EstadoAsignacionBnB& operator =(const EstadoAsignacionBnB &otro);
private:
    int nivel;
    std::vector <int> asignacion;
    int beneficio_acumulado;
    int cota_local;
    int size_;
};

#endif // ESTADOASIGNACIONBNB_H
