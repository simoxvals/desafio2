#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Surtidor
{
private:
    string codigo;
    int litrosE;
    int litrosP;
    int litrosR;
    string nombre;
    bool activo;

public:
    Surtidor(string c, int e, int p, int r) : codigo(c), litrosE(e), litrosP(p), litrosR(r), activo(true) {}

    void desactivar()
    {
        activo = false;
        cout << "Surtidor " << codigo << " desactivado." << endl;
    }

    void activar() {
        activo = true;
        cout << "Surtidor " << codigo << " activado." << endl;
    }

    void simularVenta(char tipoCombustible, int cantidad, Surtidor* surtidores[], int numeroSurtidores, string nombre) {
        if (!activo) {
            cout << "Surtidor desactivado, no se puede realizar la venta." << endl;
            return;
        }

        ofstream archivo("ventas.txt", ios::app);

        if (tipoCombustible == 'E')
        {
            if (cantidad > litrosE && litrosE > 0)
            {
                litrosE = 0;
                cout << "Venta realizada de " << litrosE << " litros de EcoExtra en la estacion: " << nombre << endl;

                archivo << "Venta en surtidor " << codigo << ": " << litrosE << " litros de EcoExtra en la estacion: " << nombre<< endl;

            }
            else if (litrosE >= cantidad)
            {
                litrosE -= cantidad;
                cout << "Venta realizada de " << cantidad << " litros de EcoExtra en la estacion: "<< nombre << endl;

                archivo << "Venta en surtidor " << codigo << ": " << cantidad << " litros de EcoExtra en la estacion: " << nombre << endl;
            }
            else
            {
                cout << "No hay suficiente combustible tipo EcoExtra en la estacion: " << nombre << endl;
            }
        }
        else if (tipoCombustible == 'P')
        {
            if (cantidad > litrosP && litrosP > 0)
            {
                litrosP = 0;
                cout << "Venta realizada de " << litrosP << " litros de Premium en la estacion: " << nombre << endl;

                archivo << "Venta en surtidor " << codigo << ": " << litrosP << " litros de Premium en la estacion: "<< nombre  << endl;

            }
            else if (litrosP >= cantidad)
            {
                litrosP -= cantidad;
                cout << "Venta realizada de " << cantidad << " litros de Premium en la estacion: "<< nombre << endl;

                archivo << "Venta en surtidor " << codigo << ": " << cantidad << " litros de Premium en la estacion: "<<nombre << endl;
            }
            else
            {
                cout << "No hay suficiente combustible tipo Premium en la estacion: "<< nombre << endl;
            }
        }
        else if (tipoCombustible == 'R')
        {
            if (cantidad > litrosR && litrosR > 0)
            {
                litrosR = 0;
                cout << "Venta realizada de " << litrosR << " litros de Regular en la estacion: " << nombre << endl;

                archivo << "Venta en surtidor " << codigo << ": " << litrosR << " litros de Regular en la estacion: "<< nombre << endl;

            }
            else if (litrosR >= cantidad)
            {
                litrosR -= cantidad;
                cout << "Venta realizada de " << cantidad << " litros de Regular en la estacion: " << nombre << endl;

                archivo << "Venta en surtidor " << codigo << ": " << cantidad << " litros de Regular en la estacion: "<< nombre << endl;
            }
            else
            {
                cout << "No hay suficiente combustible tipo Regular en la estacion: "<< nombre << endl;
            }
        }
        else {
            cout << "Tipo de combustible no valido." << endl;
        }

        archivo << "Registro de todos los surtidores:\n";
        for (int i = 0; i < numeroSurtidores; i++) {
            archivo << "Surtidor: " << surtidores[i]->getCodigo()
            << " - Litros E: " << surtidores[i]->getLitrosE()
            << " - Litros P: " << surtidores[i]->getLitrosP()
            << " - Litros R: " << surtidores[i]->getLitrosR()
            << endl;
        }

        archivo.close();
        cout << "Registro de ventas guardado\n" << endl;
    }

    string getCodigo() const { return codigo; }
    int getLitrosE() const { return litrosE; }
    int getLitrosP() const { return litrosP; }
    int getLitrosR() const { return litrosR; }
    bool isActivo() const { return activo; }
};

class Estacion
{
private:

    string codigo;
    string nombre;
    int numeroSurtidores;
    string ubicacion;
    Surtidor* surtidores[10];
    float precioE, precioP, precioR;

public:
    Estacion(string c, string u, string n) : codigo(c),ubicacion(u), nombre(n), numeroSurtidores(0), precioE(0), precioP(0), precioR(0){}

    void agregarSurtidor(string codigoSurtidor, int litrosE, int litrosP, int litrosR) {
        if (numeroSurtidores < 10)
        {
            surtidores[numeroSurtidores] = new Surtidor(codigoSurtidor, litrosE, litrosP, litrosR);
            numeroSurtidores++;
            cout << "Surtidor agregado correctamente." << endl;
        } else {
            cout << "No se pueden agregar mas surtidores." << endl;
        }
    }


    string getCodigo() const
    {
        return codigo;
    }

    string getUbicacion() const
    {
        return ubicacion;
    }

    string getNombre() const
    {
        return nombre;
    }

    int getNumeroSurtidores() const {
        return numeroSurtidores;
    }

    Surtidor* getSurtidor(int index) {
        if (index >= 0 && index < numeroSurtidores) {
            return surtidores[index];
        }
        return nullptr;
    }

    Surtidor* buscarSurtidor(const string& codigoSurtidor) {
        for (int i = 0; i < numeroSurtidores; i++) {
            if (surtidores[i]->getCodigo() == codigoSurtidor) {
                return surtidores[i];
            }
        }
        return nullptr;
    }


    void guardar(Estacion* estaciones[], int numeroEstaciones, Surtidor* surtidores[], int numeroSurtidores) {
        ofstream archivo("Estaciones.txt", ios::app);

        for (int i = 0; i < numeroEstaciones; i++) {
            archivo << "Estacion: " << estaciones[i]->getNombre() << endl;
            archivo << "Codigo: " << estaciones[i]->getCodigo() << endl;
            archivo << "Ubicacion: " << estaciones[i]->getUbicacion() << endl;

            for (int j = 0; j < estaciones[i]->getNumeroSurtidores(); j++) {
                Surtidor* surtidor = estaciones[i]->getSurtidor(j);
                archivo << "Surtidor: " << surtidor->getCodigo()<< endl;
                archivo << "E: " << surtidor->getLitrosE() << endl;
                archivo << "P: " << surtidor->getLitrosP() << endl;
                archivo << "R: " << surtidor->getLitrosR() << endl;
            }
        }

        archivo.close();
    }

    void eliminarSurtidor(Estacion* estaciones[], int &numeroEstaciones, Surtidor* surtidores[], int &numeroSurtidores, string& codigoEstacion, string& codigoSurtidor) {
        for (int i = 0; i < numeroEstaciones; i++) {
            if (estaciones[i]->getCodigo() == codigoEstacion) {
                Surtidor* surtidor = estaciones[i]->buscarSurtidor(codigoSurtidor);
                if (surtidor != nullptr) {
                    for (int j = 0; j < numeroSurtidores; j++) {
                        if (surtidores[j]->getCodigo() == codigoSurtidor) {
                            surtidores[j] = surtidores[numeroSurtidores - 1];
                            surtidores[numeroSurtidores - 1] = nullptr;
                            numeroSurtidores--;
                            cout << "Surtidor " << codigoSurtidor << " eliminado de la estacion " << codigoEstacion << "." << endl;
                            guardar(estaciones, numeroEstaciones, surtidores, numeroSurtidores);
                            return;
                        }
                    }
                } else {
                    cout << "Error: Surtidor con codigo " << codigoSurtidor << " no encontrado en la estacion " << codigoEstacion << "." << endl;
                    return;
                }
            }
        }
        cout << "Error: Estación con codigo " << codigoEstacion << " no encontrada." << endl;
    }


    void desactivarSurtidor(Estacion* estaciones[], int numeroEstaciones, string& codigoEstacion,string& codigoSurtidor)
    {
        for (int i = 0; i < numeroEstaciones; i++)
        {
            if (estaciones[i]->getCodigo() == codigoEstacion)
            {
                Surtidor* surtidor = estaciones[i]->buscarSurtidor(codigoSurtidor);
                if (surtidor != nullptr)
                {
                    surtidor->desactivar();
                    cout << "Surtidor " << codigoSurtidor << " desactivado correctamente." << endl;
                    return;
                }
                else
                {
                    cout << "\nError: Surtidor con codigo " << codigoSurtidor << " no encontrado en la estacion: " << codigoEstacion << "." << endl;
                    return;
                }
            }
        }
        cout << "Error: Estacion con codigo " << codigoEstacion << " no encontrada." << endl;
    }

    void activarSurtidor(Estacion* estaciones[], int numeroEstaciones, string& codigoEstacion, string& codigoSurtidor)
    {
        for (int i = 0; i < numeroEstaciones; i++)
        {
            if (estaciones[i]->getCodigo() == codigoEstacion)
            {
                Surtidor* surtidor = estaciones[i]->buscarSurtidor(codigoSurtidor);
                if (surtidor != nullptr)
                {
                    surtidor->activar();
                    cout << "Surtidor " << codigoSurtidor << " activado correctamente." << endl;
                    return;
                }
                else
                {
                    cout << "Error: Surtidor con código " << codigoSurtidor << " no encontrado en la estación " << codigoEstacion << "." << endl;
                    return;
                }
            }
        }
        cout << "Error: Estación con código " << codigoEstacion << " no encontrada." << endl;
    }


    void simularVenta(string codigoSurtidor, char tipoCombustible, int cantidad) {
        for (int i = 0; i < numeroSurtidores; i++) {
            if (surtidores[i]->getCodigo() == codigoSurtidor) {
                surtidores[i]->simularVenta(tipoCombustible, cantidad, surtidores, numeroSurtidores, getNombre());
                return;
            }
        }
        cout << "Surtidor no encontrado." << endl;
    }

    void fijarPrecios(float e, float p, float r) {
        precioE = e;
        precioP = p;
        precioR = r;
        cout << "Precios de combustibles actualizados." << endl;
    }
};

void mostrarMenu() {
    cout << "\nMenu de gestion\n";
    cout << "1. Agregar estacion\n";
    cout << "2. Eliminar estacion\n";
    cout << "3. Agregar surtidor a una estacion\n";
    cout << "4. Eliminar surtidor de una estacion\n";
    cout << "5. Desactivar surtidor\n";
    cout << "6. Activar surtidor\n";
    cout << "7. Fijar precios de combustibles\n";
    cout << "8. Guardar estaciones y surtidores\n";
    cout << "9. Simular venta\n";
    cout << "10.Ver historico de ventas por surtidor\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

void cargarEstaciones(Estacion* estaciones[], int &numeroEstaciones, Surtidor* surtidores[], int &numeroSurtidores) {
    ifstream archivo("Estaciones.txt");
    string linea;

    string nombreEstacion, codigoEstacion, ubicacionEstacion;
    string codigoSurtidor;
    int litrosE = 0, litrosP = 0, litrosR = 0;

    while (getline(archivo, linea))
    {
        if (linea.find("Estacion:") != string::npos) {
            nombreEstacion = linea.substr(10);
        } else if (linea.find("Codigo:") != string::npos) {
            codigoEstacion = linea.substr(8);
        } else if (linea.find("Ubicacion:") != string::npos) {
            ubicacionEstacion = linea.substr(11);
            estaciones[numeroEstaciones] = new Estacion(codigoEstacion, ubicacionEstacion, nombreEstacion);
            numeroEstaciones++;
            cout << "Estacion cargada: Codigo: " << codigoEstacion
                 << ", Nombre: " << nombreEstacion
                 << ", Ubicacion: " << ubicacionEstacion << endl;

            codigoSurtidor.clear();
            litrosE = litrosP = litrosR = 0;
        } else if (linea.find("Surtidor:") != string::npos) {
            if (!codigoSurtidor.empty()) {
                estaciones[numeroEstaciones - 1]->agregarSurtidor(codigoSurtidor, litrosE, litrosP, litrosR);
            }
            codigoSurtidor = linea.substr(10);
        } else if (linea.find("E:") != string::npos) {
            litrosE = stoi(linea.substr(3));
        } else if (linea.find("P:") != string::npos) {
            litrosP = stoi(linea.substr(3));
        } else if (linea.find("R:") != string::npos) {
            litrosR = stoi(linea.substr(3));
        }
    }

    estaciones[numeroEstaciones - 1]->agregarSurtidor(codigoSurtidor, litrosE, litrosP, litrosR);
    archivo.close();
    cout << "Base de datos cargada." << endl;
}



int main()
{

    Estacion* estaciones[10];
    Surtidor* surtidores[10];
    int numeroEstaciones = 0;
    int numeroSurtidores = 0;
    string nombre;

    int opcion;
    cargarEstaciones(estaciones, numeroEstaciones, surtidores, numeroSurtidores);
    for (int i = 0; i < numeroSurtidores; i++)
    {
        cout << "Surtidor cargado: " << surtidores[i]->getCodigo() << endl;
    }


    do {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1)
        {

            string codigoEstacion, ubicacion, nombre;
            cout<< "Ingresa el nombre de la nueva estacion: " << endl;
            cin >> nombre;
            cout << "Ingrese el codigo de la nueva estacion: "<<endl;
            cin >> codigoEstacion;
            cout<< "Ingrese su ubicacion (Centro/Sur/Norte): "<< endl;
            cin >> ubicacion;
            estaciones[numeroEstaciones] = new Estacion(codigoEstacion, ubicacion, nombre);
            numeroEstaciones++;
            cout << "Estacion agregada correctamente." << endl;


        } else if (opcion == 2)
        {
            string codigoEstacion;
            cout << "Ingrese el codigo de la estacion a eliminar: ";
            cin >> codigoEstacion;
            bool encontrada = false;

            for (int i = 0; i < numeroEstaciones; i++)
            {
                if (estaciones[i]->getCodigo() == codigoEstacion)
                {
                    delete estaciones[i];
                    estaciones[i] = estaciones[numeroEstaciones - 1];
                    numeroEstaciones--;
                    cout << "Estacion eliminada correctamente." << endl;
                    encontrada = true;
                    break;
                }
            }
            if (!encontrada)
            {
                cout << "No se encontro estacion con tal codigo" << endl;
            }


        } else if (opcion == 3)
        {
            string codigoEstacion, codigoSurtidor;
            int litrosE, litrosP, litrosR;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->getCodigo() == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor: ";
                    cin >> codigoSurtidor;
                    cout << "Ingrese litros para combustible E: ";
                    cin >> litrosE;
                    cout << "Ingrese litros para combustible P: ";
                    cin >> litrosP;
                    cout << "Ingrese litros para combustible R: ";
                    cin >> litrosR;
                    estaciones[i]->agregarSurtidor(codigoSurtidor, litrosE, litrosP, litrosR);
                    break;
                }
            }

        } else if (opcion == 4)
        {
            string codigoEstacion, codigoSurtidor;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;

            bool estacionEncontrada = false;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->getCodigo() == codigoEstacion) {
                    estacionEncontrada = true;
                    cout << "Ingrese el codigo del surtidor a eliminar: ";
                    cin >> codigoSurtidor;
                    estaciones[i]->eliminarSurtidor(estaciones, numeroEstaciones, surtidores, numeroSurtidores, codigoEstacion, codigoSurtidor);
                    break;
                }
            }
            if (!estacionEncontrada) {
                cout << "Error: Estacion con codigo " << codigoEstacion << " no encontrada." << endl;
            }

        } else if (opcion == 5) {
            string codigoEstacion, codigoSurtidor;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->getCodigo() == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor a desactivar: ";
                    cin >> codigoSurtidor;
                    estaciones[i]->desactivarSurtidor(estaciones, numeroEstaciones,codigoEstacion, codigoSurtidor);
                    break;
                }
            }


        } else if (opcion == 6)
        {
            string codigoEstacion, codigoSurtidor;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->getCodigo() == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor a activar: ";
                    cin >> codigoSurtidor;
                    estaciones[i]->activarSurtidor(estaciones, numeroEstaciones, codigoEstacion, codigoSurtidor);
                    break;
                }
            }


        } else if (opcion == 7)
        {
            string codigoEstacion;
            float precioE, precioP, precioR;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->getCodigo() == codigoEstacion) {
                    cout << "Ingrese el precio de combustible E: ";
                    cin >> precioE;
                    cout << "Ingrese el precio de combustible P: ";
                    cin >> precioP;
                    cout << "Ingrese el precio de combustible R: ";
                    cin >> precioR;
                    estaciones[i]->fijarPrecios(precioE, precioP, precioR);
                    break;
                }
            }


        } else if (opcion == 8)
        {
            for (int i = 0; i < numeroEstaciones; i++)
            {
                estaciones[i]->guardar(estaciones, numeroEstaciones, surtidores, numeroSurtidores);
            }


        } else if (opcion == 9)
        {
            string codigoEstacion, codigoSurtidor;
            char tipoCombustible;
            int cantidad;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->getCodigo() == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor: ";
                    cin >> codigoSurtidor;
                    cout << "Ingrese el tipo de combustible (E, P, R): ";
                    cin >> tipoCombustible;
                    cout << "Ingrese la cantidad de litros: ";
                    cin >> cantidad;
                    estaciones[i]->simularVenta(codigoSurtidor, tipoCombustible, cantidad);
                    break;
                }
            }
        }

        else if (opcion == 10) {
            ifstream archivo("ventas.txt");
            string linea;

            if (!archivo.is_open()) {
                cout << "Error al abrir el archivo de ventas." << endl;
            } else {
                cout << "Registro de ventas:\n";
                while (getline(archivo, linea)) {
                    if (linea.find("Venta en surtidor") != string::npos) {
                        cout << linea << endl;
                    }
                }
                archivo.close();
            }
        }


    } while (opcion != 0);

    for (int i = 0; i < numeroEstaciones; i++)
    {
        delete estaciones[i];
    }

    for (int j = 0; j < numeroSurtidores; j++)
    {
        delete surtidores[j];
    }


    cout << "Saliendo del programa..." << endl;
    return 0;
}
