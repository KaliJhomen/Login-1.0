#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;
//funciones adicionales para un correcto funcionamiento
void pausa() {
    cout << "\n\nPresiona Enter para continuar...";
    fflush(stdin);
    cin.get();
    system("CLS");
}

void comprobarArchivo() {
    ifstream archivo;

    archivo.open("usuarios.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de registros o a\243n no se ha registrado ning\243n usuario";
        cout << "\n\n";
        pausa();
        system("CLS");
    }
}
void error() {
    cout << "\t\t\tError cr\241tico\t\t\t";
}

//declaracion de una clase Usuario
class Usuario {
private:
    string nya;
    string correo;
    string contraseña;
    string edad;
    string codigo;
    string carrera;
public:
    void menuPrincipal();
    void registrarUsuario();
    void iniciarSesion();
    void menuPriv();
    void detallesUsuario();
};
//Metodo que proporciona la estructura y funcionalidad de un menu principal
void Usuario::menuPrincipal() {
    int opcion = 0;
    do {
        cout << "\t\t***Bienvenido al Interfaz de Usuario***\n";
        cout << "1. Registrarse\n";
        cout << "2. Iniciar Sesi\242n\n";
        cout << "3. Salir\n";
        cin >> opcion;
        cin.ignore();
        system("CLS");
        switch (opcion) {
            default:
                cout << "Opci\242n no v\240lida\n";
                break;
            case 1:
                registrarUsuario();
                break;
            case 2:
                iniciarSesion();
                break;
            case 3:
                break;
        }
    } while (opcion != 3);
}
//Metodo que permite al usuario registrar sus datos personales y guardarlos en un .txt
void Usuario::registrarUsuario() {
    ofstream escritura;
    ifstream lectura;
    string _codigo;
    bool coincidencia = false;

    lectura.open("usuarios.txt", ios::in);
    escritura.open("usuarios.txt", ios::app);
    if (escritura.is_open() && lectura.is_open()) {
        cout << "\t\t\t\t\tRegistrarse\t\t\t\t\n";
        fflush(stdin);

        cout << "Ingrese un c\242digo \243nico: ";
        getline(cin, _codigo);
        fflush(stdin);

        if (_codigo.empty()) {
            do {
                cout << "Ingrese datos v\240lidos\n";
                getline(cin, _codigo);
            } while (_codigo.empty());
        }

        do {
            lectura.seekg(0);
            getline(lectura, codigo);
            while (!lectura.eof()) {
                getline(lectura, contraseña);
                getline(lectura, nya);
                getline(lectura, edad);
                getline(lectura, correo);
                getline(lectura, carrera);
                if (codigo == _codigo) {
                    coincidencia = true;
                    cout << "\t\t**Ya existe este c\242digo**\n";
                    cout << "El c\242digo est\240 vinculado a: " << nya << "\n\n";
                    cout << "Ingrese el c\242digo correctamente\n";
                    getline(cin, _codigo);
                    if (_codigo.empty()) {
                        do {
                            cout << "C\242digo no v\240lido: \n";
                            getline(cin, _codigo);
                        } while (_codigo.empty());
                    }
                    break;
                }
                getline(lectura, codigo);
            }
            if (lectura.eof() && _codigo != codigo)
                coincidencia = false;
        } while (coincidencia);

        system("CLS");
        codigo = _codigo;
        cout << "\t\t\t\tRegistro de Usuario\t\t\t\t\n";
        cout << "Tu c\240digo: " << codigo << "\n\n";
        cout << "Ingresa una contrase\244a\n";
        getline(cin, contraseña);
        cout << "\n";
        fflush(stdin);
        cout << "Ingresa tu nombre: \n";
        getline(cin, nya);
        cout << "\n";
        fflush(stdin);
        cout << "Ingresa tu edad: \n";
        getline(cin, edad);
        cout << "\n";
        fflush(stdin);
        cout << "Ingresa tu correo\n";
        getline(cin, correo);
        cout << "\n";
        cout << "Ingresa tu carrera\n";
        getline(cin, carrera);
        cout << "\n";

        cout << "Registrado Satisfactoriamente\n";
        escritura   << codigo << endl
                    << contraseña << endl
                    << nya << endl
                    << edad << endl
                    << correo << endl
                    << carrera << endl;
    } else {
        error();
    }

    escritura.close();
    lectura.close();
    pausa();
}
//metodo que mediante la lectura del .txt comprueba si el "codigo" y "contraseña" ingresados son iguales a los que pertenecen a una "cuenta"
void Usuario::iniciarSesion() {
    ifstream comprobar;
    string _codigo;
    string _contraseña;
    bool coincidencia = false;

    comprobar.open("usuarios.txt", ios::in);
    if (comprobar.is_open()) {
        cout << "\t\t\t\t\tInicio de Sesi\242n\n";
        cout << "C\242digo: ";
        getline(cin, _codigo);
        cout << "Contrase\244a: ";
        getline(cin, _contraseña);
        do {
            getline(comprobar, codigo);
            getline(comprobar, contraseña);
            if (_codigo == codigo && _contraseña == contraseña) {
                coincidencia = true;
                getline(comprobar, nya);
                cout << "\t\tInicio de Sesi\242n Satisfactorio!\n";
                pausa();
                menuPriv();
                break;
            }
        } while (!comprobar.eof());
        if (!coincidencia) {
            cout << "C\242digo o contrase\244a inv\240lidos, intente de nuevo";
        }
        comprobar.close();
    } else {
        error();
    }
}
//Metodo encargado de proporcionar un menu para el usuario que inició sesión
void Usuario::menuPriv() {
    int opcion1 = 0;

    do {
        cout << "\t\t***Bienvenido " << nya << "!!***\n";
        cout << "\tQu\202 deseas hacer?\n";
        cout << "1. Mostrar Detalles de un Usuario\n";
        cout << "2. Aportar\n";
        cout << "3. Cerrar Sesi\242n\n";
        cin >> opcion1;
        cin.ignore();
        system("CLS");
        string ans;
        switch (opcion1) {
            default:
                cout << "Opci\242n no v\240lida\n";
                break;
            case 1:
                detallesUsuario();
                break;
            case 2:
                break;
            case 3: {
                cout << "Seguro que deseas cerrar sesi\242n? (Si/No)\n";
                getline(cin, ans);
                if (ans == "s" || ans == "S" || ans == "si" || ans == "Si" || ans == "sI") {
                    system("CLS");
                    menuPrincipal();
                    break;
                } else {
                    cout << "Redirigi\202ndote...";
                    pausa();
                    menuPriv();
                }
            }
                break;
        }
    } while (opcion1 != 3);
}
//Metodo que lee el archivo .txt y busca un usuario con el codigo proporcionado, si no encuentra uno, tira un mensaje predeterminado
void Usuario::detallesUsuario() {
    string _codigo;
    ifstream mostrar;
    bool encontrado = false;

    mostrar.open("usuarios.txt", ios::in);
    if (mostrar.is_open()) {
        fflush(stdin);
        cout << "\t\t\t\t\tB\243squeda de Usuarios\t\t\t\t\t\n\n";
        getline(mostrar, codigo);
        if (mostrar.eof()) {
            cout << "No se encontr\242 ning\243n registro";
        } else {
            mostrar.seekg(0);
            cout << "Ingrese el c\242digo del usuario a encontrar: ";
            getline(cin, _codigo);
            while (getline(mostrar, codigo) && getline(mostrar, contraseña) && getline(mostrar, nya) && getline(mostrar, edad) && getline(mostrar, correo) && getline(mostrar, carrera)) {
                if (_codigo == codigo) {
                    encontrado = true;
                    cout << "\n\nRegistro Encontrado\n\n";
                    cout << "C\242digo: " << codigo << endl;
                    cout << "Nombres y Apellidos: " << nya << endl;
                    cout << "Edad: " << edad << endl;
                    cout << "Correo: " << correo << endl;
                    cout << "Carrera: " << carrera << endl;
                    cout << "\n\n";
                }
            }
            if (!encontrado) {
                cout << "Registro no encontrado, intente nuevamente ";
            }
        }
    } else {
        error();
    }
    mostrar.close();
    pausa();
}

int main() {
    Usuario inicio;
    comprobarArchivo();
    inicio.menuPrincipal();
    return 0;
}

