#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Surtidor {
public:
    string codigo;
    int litrosE;
    int litrosP;
    int litrosR;
    bool activo;

    Surtidor(string c, int e, int p, int r) : codigo(c), litrosE(e), litrosP(p), litrosR(r), activo(true) {}

    void desactivar() {
        activo = false;
        cout << "Surtidor " << codigo << " desactivado." << endl;
    }

    void activar() {
        activo = true;
        cout << "Surtidor " << codigo << " activado." << endl;
    }

    void simularVenta(char tipoCombustible, int cantidad) {
        if (!activo) {
            cout << "Surtidor desactivado, no se puede realizar la venta." << endl;
            return;
        }

        if (tipoCombustible == 'E') {
            if (litrosE >= cantidad) {
                litrosE -= cantidad;
                cout << "Venta realizada de " << cantidad << " litros de E." << endl;
            } else {
                cout << "No hay suficiente combustible tipo E." << endl;
            }
        } else if (tipoCombustible == 'P') {
            if (litrosP >= cantidad) {
                litrosP -= cantidad;
                cout << "Venta realizada de " << cantidad << " litros de P." << endl;
            } else {
                cout << "No hay suficiente combustible tipo P." << endl;
            }
        } else if (tipoCombustible == 'R') {
            if (litrosR >= cantidad) {
                litrosR -= cantidad;
                cout << "Venta realizada de " << cantidad << " litros de R." << endl;
            } else {
                cout << "No hay suficiente combustible tipo R." << endl;
            }
        } else {
            cout << "Tipo de combustible no valido." << endl;
        }
    }
};

class Estacion {
public:
    string codigo;
    Surtidor* surtidores[10];
    int numeroSurtidores;
    float precioE, precioP, precioR;

    Estacion(string c) : codigo(c), numeroSurtidores(0), precioE(0), precioP(0), precioR(0) {}

    void agregarSurtidor(string codigoSurtidor, int litrosE, int litrosP, int litrosR) {
        if (numeroSurtidores < 10) {
            surtidores[numeroSurtidores] = new Surtidor(codigoSurtidor, litrosE, litrosP, litrosR);
            numeroSurtidores++;
            cout << "Surtidor agregado correctamente." << endl;
        } else {
            cout << "No se pueden agregar mas surtidores." << endl;
        }
    }

    void eliminarSurtidor(string codigoSurtidor) {
        for (int i = 0; i < numeroSurtidores; i++) {
            if (surtidores[i]->codigo == codigoSurtidor) {
                delete surtidores[i];
                surtidores[i] = surtidores[numeroSurtidores - 1];
                numeroSurtidores--;
                cout << "Surtidor eliminado correctamente." << endl;
                return;
            }
        }
        cout << "Surtidor no encontrado." << endl;
    }

    void desactivarSurtidor(string codigoSurtidor) {
        for (int i = 0; i < numeroSurtidores; i++) {
            if (surtidores[i]->codigo == codigoSurtidor) {
                surtidores[i]->desactivar();
                return;
            }
        }
        cout << "Surtidor no encontrado." << endl;
    }

    void activarSurtidor(string codigoSurtidor) {
        for (int i = 0; i < numeroSurtidores; i++) {
            if (surtidores[i]->codigo == codigoSurtidor) {
                surtidores[i]->activar();
                return;
            }
        }
        cout << "Surtidor no encontrado." << endl;
    }

    void simularVenta(string codigoSurtidor, char tipoCombustible, int cantidad) {
        for (int i = 0; i < numeroSurtidores; i++) {
            if (surtidores[i]->codigo == codigoSurtidor) {
                surtidores[i]->simularVenta(tipoCombustible, cantidad);
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

    void guardarEstacion() {
        ofstream archivo("estaciones.txt", ios::app);
        archivo << "Estacion: " << codigo << endl;
        for (int i = 0; i < numeroSurtidores; i++) {
            archivo << "Surtidor: " << surtidores[i]->codigo
                    << " E: " << surtidores[i]->litrosE
                    << " P: " << surtidores[i]->litrosP
                    << " R: " << surtidores[i]->litrosR
                    << " Activo: " << (surtidores[i]->activo ? "Si" : "No") << endl;
        }
        archivo.close();
        cout << "Datos de la estacion guardados correctamente." << endl;
    }
};

void mostrarMenu() {
    cout << "\nMenu de Gestion de Estaciones\n";
    cout << "1. Agregar estacion\n";
    cout << "2. Eliminar estacion\n";
    cout << "3. Agregar surtidor a una estacion\n";
    cout << "4. Eliminar surtidor de una estacion\n";
    cout << "5. Desactivar surtidor\n";
    cout << "6. Activar surtidor\n";
    cout << "7. Fijar precios de combustibles\n";
    cout << "8. Guardar estaciones y surtidores\n";
    cout << "9. Simular venta\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    Estacion* estaciones[10];
    int numeroEstaciones = 0;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            string codigoEstacion;
            cout << "Ingrese el codigo de la nueva estacion: ";
            cin >> codigoEstacion;
            estaciones[numeroEstaciones] = new Estacion(codigoEstacion);
            numeroEstaciones++;
            cout << "Estacion agregada correctamente." << endl;
        } else if (opcion == 2) {
            string codigoEstacion;
            cout << "Ingrese el codigo de la estacion a eliminar: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
                    delete estaciones[i];
                    estaciones[i] = estaciones[numeroEstaciones - 1];
                    numeroEstaciones--;
                    cout << "Estacion eliminada correctamente." << endl;
                    break;
                }
            }
        } else if (opcion == 3) {
            string codigoEstacion, codigoSurtidor;
            int litrosE, litrosP, litrosR;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
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
        } else if (opcion == 4) {
            string codigoEstacion, codigoSurtidor;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor a eliminar: ";
                    cin >> codigoSurtidor;
                    estaciones[i]->eliminarSurtidor(codigoSurtidor);
                    break;
                }
            }
        } else if (opcion == 5) {
            string codigoEstacion, codigoSurtidor;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor a desactivar: ";
                    cin >> codigoSurtidor;
                    estaciones[i]->desactivarSurtidor(codigoSurtidor);
                    break;
                }
            }
        } else if (opcion == 6) {
            string codigoEstacion, codigoSurtidor;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
                    cout << "Ingrese el codigo del surtidor a activar: ";
                    cin >> codigoSurtidor;
                    estaciones[i]->activarSurtidor(codigoSurtidor);
                    break;
                }
            }
        } else if (opcion == 7) {
            string codigoEstacion;
            float precioE, precioP, precioR;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
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
        } else if (opcion == 8) {
            for (int i = 0; i < numeroEstaciones; i++) {
                estaciones[i]->guardarEstacion();
            }
        } else if (opcion == 9) {
            string codigoEstacion, codigoSurtidor;
            char tipoCombustible;
            int cantidad;
            cout << "Ingrese el codigo de la estacion: ";
            cin >> codigoEstacion;
            for (int i = 0; i < numeroEstaciones; i++) {
                if (estaciones[i]->codigo == codigoEstacion) {
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
    } while (opcion != 0);

    cout << "Saliendo del programa..." << endl;
    return 0;
}
