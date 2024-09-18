#ifndef USER_H
#define USER_H

#include <string>

class user{
    private:
    std::string nombre;
    std::string apellido;
    std::string fechaN;
    std::string correoE;
    std::string pass;

public:

// Constructor del usuario
user(const std::string& nombre, const std::string& apellido, const std::string& fechaN, const std::string& correoE, const std::string& pass);

    std::string getnombre() const;
    std::string getapellido() const;
    std::string getfechaN() const;
    std::string getcorreoE() const;
    std::string getpass() const;

    void setnombre(const std::string& nombre);
    void setapellido(const std::string& apellido);
    void setfechaN(const std::string& fechaN);
    void setcorreoE(const std::string& correoE);
    void setpass(const std::string& pass);


};

#endif // USER_H
