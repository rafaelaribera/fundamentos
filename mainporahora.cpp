//Nuestras librerias
#include <windows.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <math.h>
///Nuestras clases, que finos
#include "Archivero.h"
#include "users.h"

#define MAX 1000
using  namespace std;

///Relativo a login, mains, y algunas cosas general, hecho por Jesus
void modificaruser();
void printBorder(int width, int height);
void printlogo(int centX, int centY);
void postext(int centX, int centY, string text);
float stringtofloat(string input);
void login(int centX, int centY, int paso3);
void signup(int& paso3, Archivero& infodeusuarios, Archivero& usuariosregistrados);
void mainmenuadm(int centX, int centY, int paso3);
void mainmenunormal(int centX, int centY, int paso3);
void rellenarstruct(string lineascondatos[]);
void imprimirUsuarios(int paso3, int centX, int centY);
void veropiniones();
int paso3; bool usuarioactual;
//Relativo a la contabilidad, Hecho por Daniel
void contabilizarusuario(string usuario[], string tipousuario[], string tipousuario1[], int& totalusuarios, int& usuarioscorriente, int& usuariospremium);
void registrargasto(string gastolit[], string gasto[], float gastofl[], int& totalgastos, float& gastostotales);
void listargastos(string gastolit[], string gasto[], float gastofl[], int& totalgastos, float& gastostotales);
void mostrarganancia(string usuario[], string tipousuario[], string tipousuario1[], string gasto[], int totalusuarios, float gastostotales);
void contabilidad();
int stringtoint(string valor1);
//Relativo a las criticas, hecho por Dilan
int opiniones = 0;
void criticas();
void opininion(int calif[], string opinion[]);
int calif[MAX];
string opinion[MAX];
//Relativo a los recordatorios, hecho por Rafa
// Prototipos de funciones
/// Algebra: Hecho por Rafa y Jesus
void mostrarMenucon();
void unionConjuntos(int conjuntoA[], int tamanioA, int conjuntoB[], int tamanioB, int resultado[], int& tamanioResultado);
void interseccionConjuntos(int conjuntoA[], int tamanioA, int conjuntoB[], int tamanioB, int resultado[], int& tamanioResultado);
void diferenciaConjuntos(int conjuntoA[], int tamanioA, int conjuntoB[], int tamanioB, int resultado[], int& tamanioResultado);
void anadirConjunto(char conjunto, int conjunto1[], int& tamanio);
void mostrarConjunto(int conjunto[], int tamanio);
void mostrarRelacion(int relacion[][2], int numPares);
void relaciones();
void conjuntos();
void modificarcon(int conjuntoA[], int& tamanioA);
void ingresarRelacion(int relacion[][2], int& numPares);
void determinarReflexividad(int relacion[][2], int numPares);
void determinarSimetria(int relacion[][2], int numPares);
void mostrarMenuR();
void algebra();
////FUNDAMENTOS DE MATEMATICA, hecho por Laura
void SISTEMA(float A, float B, float C, float D, float E, float F, float& x, float& y);
float unica(float A, float B);
void reales(float A, float B, float C, float& x1, float& x2);
void imaginario(float A, float B, float C, float& xr, float& xi);
double calcularAreaTriangulo(double base, double altura);
double calcularAreaCuadrado(double lado);
float division(float a, float b);
float suma(float a, float b);
float resta(float a, float b);
float mult(float a, float b);
double calcularLogaritmoEnBase(double numero, double base);
double calcularradicacion(int numero, int indice, double resultado);
void matematicas();
///////////////
//mecanica, hecho por Dylan y Daniel
void mecanica();
float calcularVelocidad(float distancia, float tiempo);
float calcularDistancia(float velocidad, float tiempo);
float calcularTiempo(float distancia, float velocidad);
float calcularVelocidadFinal(float velocidadInicial, float aceleracion, float tiempo2);
float calcularDesplazamiento(float velocidadInicial, float aceleracion, float tiempo2);
float calcularTiempoMRUV(float velocidadInicial, float aceleracion, float velocidadFinal);

/// <summary>
/// 
/// </summary>
struct User {
    bool userType;
    int userID;
    string username;
    string password;
    string email;
};
User users[MAX];
struct recordatorio
{
    string nombre;
    string fecha;
    string descripcion;
    bool completado;
};

//Pantalla inicial, el main, creo que hubiera sido muy comico meter aqui el main menu, pero ya se hizo muy grande xd
int main() {
    float opt; string opp; //opciones
    int width; int height; //bloques de la consola
    int centX, centY; //Centro de la pantalla
    COORD coord;//coordenadas en la consola
    string paso1; float paso2;//Para leer el archivo donde se guarda el nro de usuarios registrados, paso3 es variable global
    //para los archivos
    Archivero infodeusuarios("\"usuarios.txt\"");
    Archivero usuariosregistrados("\"tamuser.txt\"");
    paso1 = usuariosregistrados.leer();  paso2 = stringtofloat(paso1); paso3 = paso2;
    string* lineas = infodeusuarios.leerVector();
    string lineascondatos[MAX];
    for (int i = 0; i < paso3; i++) {
        lineascondatos[i] = lineas[i];
    }
    delete[] lineas;
    rellenarstruct(lineascondatos);
    system("cls");
    
    system("color 3F");

    HWND console = GetConsoleWindow();
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    MoveWindow(console, (screenW / 2) - (screenW / 2.75), (screenH / 2) - (screenH / 2.1), 1000, 700, TRUE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
     width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
     height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

     centX = width / 2;
     centY = height / 2;
     

    do {
        printBorder(width, height);
        printlogo(centX, centY);

        postext(centX - centX / 10, centY - centY / 1.15, "U + me");
        postext(centX - (centX / 2.5), centY + (centY / 3), "Pulse un numero segun lo que desee realizar");
        postext(centX - (centX / 10), centY + (centY / 2.5), "1.- Login");
        postext(centX - (centX / 10), centY + (centY / 2.2), "2.- Sing up");
        postext(centX - (centX / 10), centY + (centY / 2), "0.- Cerrar");



        coord.X = centX - (centX / 15);
        coord.Y = centY + (centY / 1.5);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        opp = _getch();

        opt = stringtofloat(opp);
        if (opt == 0) { return 0; }
        else if (opt == -100000.25) {
            postext(centX - (centX / 5), centY + centY / 1.5, "ERROR: PULSE UN NUMERO");
            coord.X = centX - (centX / 3);
            coord.Y = centY + (centY / 1.3);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            system("pause");
        }
        else if ((opt != 1) && (opt != 2)) {
          opt = -100000.25;
        }
        system("cls");
    } while (opt == -100000.25);
    if (opt == 2)  signup(paso3, infodeusuarios, usuariosregistrados);
    else login(centX, centY, paso3);
    return 0;
}
//Todo lo que involucra al registro, no pense que seria mas largo el registro que el login
//la vida esta llena de sorpresas, apoco no ?, sobretodo lo del .txt, que locura ajsjdasd
void signup(int& paso3, Archivero& infodeusuarios, Archivero& usuariosregistrados) {

    users[paso3 + 1].userType = 0;
    users[paso3 + 1].userID = paso3 + 1;
    cout << "Por favor, introduce tu nombre de usuario: ";
    getline(cin, users[paso3 + 1].username);

    cout << "Por favor, introduce tu contraseña: ";
    getline(cin, users[paso3 + 1].password);

    cout << "Por favor, introduce tu correo electrónico: ";
    getline(cin, users[paso3 + 1].email);

    // guarda cuantos usuarios hay, pal for
    usuariosregistrados.sobreescribir(to_string(paso3 + 1));
    // guardar info de los usuarios
    string userInfo = to_string(users[paso3 + 1].userID) + "/ /" + users[paso3 + 1].username + "/ /" + users[paso3 + 1].password + "/ /" + users[paso3 + 1].email + "/ /" + to_string(users[paso3 + 1].userType) + "/ /";
    infodeusuarios.escribir(userInfo);
    paso3++;
    main();
}
//El login, no, yes yes yes
void login(int centX, int centY, int paso3) {
    string username, pass;
    int saveuser = -1;
    COORD coord;
    do {
        system("cls");
        printBorder(centX * 2, centY * 2);
        postext(centX - centX / 3, centY - centY / 1.5, "Ingrese porfavor, su nombre de usuario");
        coord.X = centX - centX / 3;
        coord.Y = centY - centY / 1.6;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        getline(cin, username);
        postext(centX - centX / 3, centY - centY / 1.8, "Ingrese porfavor, su password");
        coord.X = centX - centX / 3;
        coord.Y = centY - centY / 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        getline(cin, pass);
        for (int i = 0; i < paso3; i++) {
            Users users1(users[i].username, users[i].password);
            if (users1.verificarlogin(username, pass) == true) {
                saveuser = users[i].userID;
            }
            
        }if (saveuser == -1) {
            postext(centX - centX / 3, centY - centY / 10, "ERROR: No se ha encontrado su registro");
            postext(centX - centX / 2, centY + centY / 8, "Pulse 0 para salir, cualquier otra tecla para volver a intentar");
            int a= _getch();
            if (a == 48) { main(); }
        }
    } while (saveuser == -1);
    usuarioactual = users[saveuser].userType;
    postext(centX - centX / 3, centY - centY / 10, "BIENVENIDO, "+users[saveuser].username);
    postext(centX - centX / 3, centY + centY / 8, "Pulse una tecla para continuar");
    _getch();
    system("cls");
    if (users[saveuser].userID == 1) {
        mainmenuadm(centX, centY, paso3);}
    else{   mainmenunormal(centX, centY, paso3);
    }
}
void mainmenuadm(int centX , int centY, int paso3) {
    int a;    
    do {
        do {
            system("cls"); system("color 80");
            COORD coord;
            postext(centX - centX / 6, centY - centY / 1.5, "MENU ADMINISTRATIVO");
            postext(centX - centX / 3, centY - centY / 1.7, "Pulse un numero segun lo que usted desee hacer");
            postext(centX - centX / 4.5, centY - centY / 2, "1.- Ver lista de los usuarios");
            postext(centX - centX / 4.5, centY - centY / 2.4, "2.- Administrar la contabilidad");
            postext(centX - centX / 4.5, centY - centY / 2.8, "3.- Ver valoraciones de los usuarios");
            postext(centX - centX / 4.5, centY - centY / 3.2, "4.- Modificar un usuario (Premium/Normal)");
            postext(centX - centX / 4.5, centY - centY / 3.6, "0.- Salir");

            coord.X = centX - (centX / 5);
            coord.Y = centY - (centY / 5);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            a = _getch();
            if ((a < 48) || (a > 53)) {
                postext(centX - centX / 4.5, centY + centY / 20, "INGRESE UN NUMERO VALIDO");
                coord.X = centX - (centX / 5);
                coord.Y = centY + (centY / 7);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); system("pause");
            }
        } while ((a < 49) || (a > 53));
        switch (a) {
        case 48: {system ("cls"); main(); } break;
        case 49: {system("cls"); imprimirUsuarios(paso3, centX, centY); } break;
        case 50: {system("cls");     contabilidad();} break;
        case 51: {system("cls");  veropiniones(); } break;
        case 52: {system("cls"); modificaruser(); } break;
        case 53: { } break;

        }

    } while (a != 48);
}
void modificaruser() {
    int id;
    Archivero infodeusuarios("usuarios.txt");
    cout << "Por favor, introduce el ID del usuario a modificar: ";
    cin >> id;

    string* lineas = infodeusuarios.leerVector();

    for (int i = 0; i <= paso3; i++) {
        if (users[i].userID == id) {
            bool tipo;
            cout << "Por favor, introduce el nuevo tipo de usuario (0 para Normal, 1 para Premium): ";
            cin >> tipo;
            users[i].userType = tipo;
            system("pause");
            break;
        }
    }

    // Reconstruir la información de los usuarios
    string infoUsuarios = "";
    for (int i = 0; i < paso3; i++) {
        infoUsuarios += to_string(users[i].userID) + "/ /" + users[i].username + "/ /" + users[i].password + "/ /" + users[i].email + "/ /" + to_string(users[i].userType) + "/ /\n";
    }

    // Sobreescribir la información de los usuarios con sobreescribir2
    infodeusuarios.sobreescribir2(infoUsuarios);

    delete[] lineas;
}
void mainmenunormal(int centX, int centY, int paso3) {
    int a;
    do {if (usuarioactual == 0) {
         ShellExecute(NULL, L"open", L"https://longdogechallenge.com/", NULL, NULL, SW_SHOWNORMAL);
        }
        do {
            system("cls"); system("color 4f");
            COORD coord;
            postext(centX - centX / 6, centY - centY / 1.5, "MENU USUASRIO");
            postext(centX - centX / 3, centY - centY / 1.7, "Pulse un numero segun lo que usted desee hacer");
            postext(centX - centX / 4.5, centY - centY / 2, "1.- Ver Fundamentos de matematica");
            postext(centX - centX / 4.5, centY - centY / 2.4, "2.- Ver Mecanica");
            postext(centX - centX / 4.5, centY - centY / 2.8, "3.- Ver Algebra");
            postext(centX - centX / 4.5, centY - centY / 3.2, "4.- Ver Recordatorios");
            postext(centX - centX / 4.5, centY - centY / 10, "5. ELIMINAR PUBLICIDAD (ACTUALIZAR A PREMIUM)");
            postext(centX - centX / 4.5, centY , "6. PAGAR POR UNA CLASE PERSONAL");
            postext(centX - centX / 4.5, centY - centY / 3.6, "0.- Salir");

            coord.X = centX - (centX / 5);
            coord.Y = centY - (centY / 5);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            a = _getch();
            if ((a < 48) || (a > 53)) {
                postext(centX - centX / 4.5, centY + centY / 20, "INGRESE UN NUMERO VALIDO");
                coord.X = centX - (centX / 5);
                coord.Y = centY + (centY / 7);
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); system("pause");
            }
        } while ((a < 49) || (a > 53));
        system("cls");
        switch (a) {
        case 48: {main(); } break;
        case 49: { system("cls"); matematicas(); } break;
        case 50: {system("cls");     mecanica(); } break;
        case 51: {system("cls");  algebra(); } break;
        case 52: { system("cls"); } break;
        case 53: { } break;

        }

    } while (a != 48);
}
void printBorder(int width, int height) {
    string topBorder(width, static_cast<char>(219));
    cout << topBorder;

    string sideBorder = string(2, static_cast<char>(219)) + string(width - 4, ' ') + string(2, static_cast<char>(219));
    for (int i = 0; i < height - 2; ++i) {
        cout << "\n" << sideBorder;
    } 
    cout << "\n" << topBorder;
} 
void printlogo(int centX, int centY) {
    string asciiArt;
    asciiArt =
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "       " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "      " + string(4, static_cast<char>(178)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "       " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "      " + string(4, static_cast<char>(178)) + "     " + string(1, static_cast<char>(177)) + string(3, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "       " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "      " + string(4, static_cast<char>(178)) + "     " + string(1, static_cast<char>(177)) + string(3, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "       " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "     " + string(1, static_cast<char>(177)) + string(4, static_cast<char>(178)) + "  " + string(10, static_cast<char>(178)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "       " + string(5, static_cast<char>(178)) + "     " + string(1, static_cast<char>(177)) + string(4, static_cast<char>(178)) + "  " + string(10, static_cast<char>(178)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "       " + string(6, static_cast<char>(178)) + " " + string(2, static_cast<char>(177)) + string(5, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "     " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(177)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "        " + string(13, static_cast<char>(178)) + "      " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(177)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "           " + string(6, static_cast<char>(178)) + string(1, static_cast<char>(177)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "        " + string(3, static_cast<char>(177)) + "     " + string(3, static_cast<char>(177)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "      " + string(7, static_cast<char>(178)) + " " + string(7, static_cast<char>(178)) + "      " + string(1, static_cast<char>(177)) + string(8, static_cast<char>(178)) + string(1, static_cast<char>(177)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "     " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(177)) + string(3, static_cast<char>(178)) + string(4, static_cast<char>(178)) + string(1, static_cast<char>(176)) + string(4, static_cast<char>(178)) + "    " + string(4, static_cast<char>(178)) + string(1, static_cast<char>(177)) + string(2, static_cast<char>(176)) + string(1, static_cast<char>(177)) + string(3, static_cast<char>(178)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(1, static_cast<char>(178)) + "     " + string(1, static_cast<char>(177)) + string(3, static_cast<char>(178)) + "   " + string(1, static_cast<char>(177)) + string(3, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "   " + string(3, static_cast<char>(178)) + string(2, static_cast<char>(177)) + string(11, static_cast<char>(178)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + "    " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "    " + string(3, static_cast<char>(178)) + "    " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(2, static_cast<char>(176)) + string(5, static_cast<char>(178)) + string(6, static_cast<char>(177)) + "\n"
        "" + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + "    " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "    " + string(3, static_cast<char>(178)) + "    " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + " " + string(5, static_cast<char>(178)) + "\n"
        "" + string(2, static_cast<char>(177)) + string(2, static_cast<char>(178)) + "   " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "    " + string(3, static_cast<char>(178)) + "    " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "  " + string(1, static_cast<char>(177)) + string(10, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "\n"
        "" + string(2, static_cast<char>(177)) + string(3, static_cast<char>(178)) + "  " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "    " + string(3, static_cast<char>(178)) + "    " + string(1, static_cast<char>(177)) + string(2, static_cast<char>(178)) + string(1, static_cast<char>(176)) + "   " + string(8, static_cast<char>(177)) + "\n"
        "" + string(4, static_cast<char>(177)) + string(2, static_cast<char>(178)) + "\n"
        "" + string(5, static_cast<char>(177)) + string(4, static_cast<char>(178)) + "\n"
        "" + string(9, static_cast<char>(177)) + string(30, static_cast<char>(178)) + "\n"
        ;
    COORD coord;
    coord.X = centX - asciiArt.find_first_of(" /%#(") / 2 - centX / 3;
    coord.Y = centY - count(asciiArt.begin(), asciiArt.end(), '\n') + centY / 5;

    size_t start = 0;
    size_t end = asciiArt.find('\n');
    while (end != string::npos) {
        string line = asciiArt.substr(start, end - start);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << line;
        start = end + 1;
        end = asciiArt.find('\n', start);
        coord.Y++;
    }
    string line = asciiArt.substr(start);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << line;
}
void postext(int centX, int centY, string text) {
    COORD coord;
    coord.X = centX;
    coord.Y = centY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << text;

}
float stringtofloat(string input) {
    float number;
    try {
        number = stof(input);
    }
    catch (invalid_argument& e) {
        return -100000.25;
    }

    return number;
}
void rellenarstruct(string lineascondatos[]) {
    for (int i = 0; i < paso3; i++) {
        string linea = lineascondatos[i];
        size_t pos = 0;
        string token;
        int counter = 0;

        while ((pos = linea.find("/ /")) != string::npos) {
            token = linea.substr(0, pos);
            switch (counter) {
            case 0: users[i].userID = stoi(token); break;
            case 1: users[i].username = token; break;
            case 2: users[i].password = token; break;
            case 3: users[i].email = token; break;
            case 4: users[i].userType = stoi(token); break;
            }
            linea.erase(0, pos + 3);
            counter++;}; 
    }
}
void imprimirUsuarios(int paso3, int centX, int centY) {
    int offset = 2; // Espacio entre las líneas
    postext(centX - centX / 1.07, centY - centY / 1.15, "NRO DE USER");
    postext(centX - centX / 1.4, centY - centY / 1.15, "  TIPO DE USER");
    postext(centX - centX / 3, centY - centY / 1.15, "NOMBRE DE USER");
    postext(centX, centY - centY / 1.15, "  PASSWORD");
    postext(centX + centX / 3, centY - centY / 1.15, "    Email");
    for (int i = 0; i < paso3; i++) {
        postext(centX - centX / 1.08, centY - centY / 1.15 + offset * (i + 1), to_string(users[i].userID));
        postext(centX - centX / 1.5, centY - centY / 1.15 + offset * (i + 1), (users[i].userType ? "Premium" : "Normal"));
        postext(centX - centX / 3, centY - centY / 1.15 + offset * (i + 1), users[i].username);
        postext(centX, centY - centY / 1.15 + offset * (i + 1), users[i].password);
        postext(centX + centX / 3, centY - centY / 1.15 + offset * (i + 1), users[i].email);
    }
    _getch();
}
///////////////////////////////
//contabilidad
////////////////////////
///////////////////////////////
///////////////////////////////

void contabilidad()
{
    int totalusuarios = 0, usuariospremium = 0, usuarioscorriente = 0, totalgastos = 0;
    float gastostotales = 0, gastofl[MAX];
    string usuario[MAX], tipousuario[MAX], tipousuario1[MAX], gasto[MAX], gastolit[MAX], valor[MAX], valor1[MAX];
    int op;

    do {
        system("pause");
        system("cls");
        cout << "\t MENU \t " << endl;
        cout << " 1. Contabilizar Usuario" << endl;
        cout << " 2. Registrar Gastos" << endl;
        cout << " 3. Listar Gastos" << endl;
        cout << " 4. Mostrar ganancias" << endl;
        cout << " 0. Salir. " << endl;

        do {
            cout << " Teclee el numero de la funcion que desea utilizar: ";
            cin >> op;
            if (op > 4 || op < 0)
            {
                cout << " Ingrese una opcion valida por favor." << endl;
            }
        } while (op > 4 || op < 0);
        switch (op)
        {
        case 1:contabilizarusuario(usuario, tipousuario, tipousuario1, totalusuarios, usuarioscorriente, usuariospremium); break;
        case 2:registrargasto(gastolit, gasto, gastofl, totalgastos, gastostotales); break;
        case 3:listargastos(gastolit, gasto, gastofl, totalgastos, gastostotales); break;
        case 4:mostrarganancia(usuario, tipousuario, tipousuario1, gasto, totalusuarios, gastostotales); break;
        case 0: cout << " Programa Finalizado." << endl; break;
        default: cout << " Por favor seleccione una opcion valida." << endl;
        }
    } while (op != 0);
    return;
}
void contabilizarusuario(string usuario[], string tipousuario[], string tipousuario1[], int& totalusuarios, int& usuarioscorriente, int& usuariospremium)
{
    string tipous;
    int usuarioint, tipousint;
    cin.ignore();
    do {
        cout << "Ingrese el numero de usuario: " << endl;
        getline(cin, usuario[totalusuarios]);
        usuarioint = stringtoint(usuario[totalusuarios]);
        if (usuarioint <= 0)
        {
            cout << "El numero de usuario debe ser mayor que 0. Ingrese un numero de usuario valido por favor." << endl;
        }
    } while (usuarioint <= 0);

    do {
        cout << "Ingresar el numero del tipo de usuario: " << endl;
        cout << "1.- Usuario Premium." << endl;
        cout << "2.- Usuario Corriente." << endl;
        getline(cin, tipous);
        tipousint = stringtoint(tipous);
        if (tipousint == 1)
        {
            tipousuario[usuariospremium] = "Usuario Premium";
            usuariospremium++;
            totalusuarios++;
            cout << "Usuario registrado exitosamente." << endl;
        }
        if (tipousint == 2)
        {
            tipousuario1[usuarioscorriente] = "Usuario Corriente";
            usuarioscorriente++;
            totalusuarios++;
            cout << "Usuario registrado exitosamente." << endl;
        }
        if (tipousint != 1 && tipousint != 2)
        {
            cout << "Seleccione una opcion valida por favor." << endl;
        }
    } while (tipousint != 1 && tipousint != 2);
}
void registrargasto(string gastolit[], string gasto[], float gastofl[], int& totalgastos, float& gastostotales)
{
    string numgastos;
    int numgastosint;
    cin.ignore();
    do {
        cout << "Ingrese cuantos gastos quiere registrar: ";
        getline(cin, numgastos);
        numgastosint = stringtoint(numgastos);
        if (numgastosint <= 0)
        {
            cout << "Ingrese un numero de gastos valido por favor, debe ser un numero entero." << endl;
        }
    } while (numgastosint <= 0);

    for (int i = 0; i < numgastosint; i++)
    {
        cout << "Ingrese el tipo de gasto: " << endl;
        getline(cin, gastolit[i]);
        do {
            cout << "Ingrese el monto del gasto: " << endl;
            getline(cin, gasto[i]);
            gastofl[i] = stringtofloat(gasto[i]);
            if (gastofl[i] < 0)
            {
                cout << "El monto del gasto debe ser mayor a 0." << endl;
            }
        } while (gastofl[i] < 0);
        gastostotales = gastostotales + gastofl[i];
    }
    cout << "Gasto registrado exitosamente." << endl;
    totalgastos = totalgastos + numgastosint;
}
void listargastos(string gastolit[], string gasto[], float gastofl[], int& totalgastos, float& gastostotales)
{
    cout << "Lista de gastos registrados:" << endl;

    for (int i = 0; i < totalgastos; i++) {
        cout << "Gasto en: " << gastolit[i] << " | Monto: Bs. " << gastofl[i] << endl;
    }
    cout << "Los gatos totales son: Bs. " << gastostotales << endl;
}
void mostrarganancia(string usuario[], string tipousuario[], string tipousuario1[], string gasto[], int totalusuarios, float gastostotales)
{
    float gananciaTotal = 0;
    // Calcular ganancias basadas en usuarios
    for (int i = 0; i < totalusuarios; i++)
    {
        if (tipousuario[i] == "Usuario Premium")
        {
            gananciaTotal += 20; // 20 bs por usuario premium
        }
        if (tipousuario1[i] == "Usuario Corriente")
        {
            gananciaTotal += 2; // 2 bs por usuario corriente
        }
    }
    // Restar gastos
    gananciaTotal = gananciaTotal - gastostotales;

    cout << "Ganancia total: Bs. " << gananciaTotal << endl;
}
int stringtoint(string valor1)
{
    float number1;
    try {
        number1 = stoi(valor1);
    }
    catch (invalid_argument& e) {
        return -100000.25;
    }
    return number1;
}
///////////////////////////////
//opiniones
///////////////////////////////

void opininion(int calif[], string opinion[]);
void criticas()
{
    string select;
    cout << "Su opinion es importante para nosotros" << endl;
    cout << "¿Desea ingresar una calificacion y opinion ( escriba si/no)?:  ";
    cin >> select;

    while (select == "si" || select == "Si" || select == "SI") {
        opininion(calif, opinion);
        cout << "¿Desea ingresar otra calificacion y opinion (si/no)?: ";
        cin >> select;
    }
    return;
}
void opininion(int calif[], string opinion[])
{ 
    cout << "Ingrese una calificacion cuantitativa del 1 al 5: ";
    cin >> calif[opiniones];

    cout << "Ingrese una opinion o sugerencia: ";
    cin.ignore();
    getline(cin, opinion[opiniones]);
    opiniones++;
}
void veropiniones()
{
    cout << "OPINIONES" << endl;
    if (opiniones == 0) { cout << "No hay opiniones" << endl; 
    _getch(); system("pause");
    return; }
    else{    for (int i = 0; i < opiniones;i++) {
        cout << "Calificacion nro " << i + 1 << calif[i]<<endl;
        cout<<"Opinion nro: "<<endl;
        cout << opinion[i]<<endl;
    }}
};
///////////////////////////////
//RECORDATORIOS
///////////////////////////////
///////////////////////////////

///////////////////////////////
///////////////////////////////
//ALGEBRA
///////////////////////////////
///////////////////////////////
void algebra()
{
    int opcion;

    do {
        if (usuarioactual == 0) {
         ShellExecute(NULL, L"open", L"https://longdogechallenge.com/", NULL, NULL, SW_SHOWNORMAL);
        }
        cout << "Menu de Operaciones de Algebra Elemental:" << endl;
        cout << "1. Operaciones con Conjuntos" << endl;
        cout << "2. Operaciones con Relaciones" << endl;;
        cout << "0. Salir" << endl;

        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
        {system("cls"); conjuntos(); }
            break;
        case 2:
        {system("cls");    relaciones(); }
            break;
        case 0:
        {system("cls");   cout << "Saliendo del programa." << endl; }
            break;
        default:
        {system("cls");   cout << "Opcion no valida" << endl; }
        
        }

    } while (opcion != 0);

}
void relaciones()
{
    int relacion[MAX][2];
    int numPares = 0, opcion;
    do {
        mostrarMenuR();
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Ingrese la relacion:\n";
            ingresarRelacion(relacion, numPares);
            break;

        case 2:
            cout << "Relacion ingresada:\n";
            mostrarRelacion(relacion, numPares);
            break;

        case 3:
            determinarReflexividad(relacion, numPares);
            break;

        case 4:
            determinarSimetria(relacion, numPares);
            break;
        case 0:
            cout << "Saliendo del programa. ¡Hasta luego!\n";
            break;

        default:
            cout << "Opcion no valida. Intente nuevamente.\n";
        }

    } while (opcion != 0);
}
void mostrarMenuR() {
    cout << "\n--- Menu ---" << endl;
    cout << "1. Ingresar relacion" << endl;
    cout << "2. Mostrar relacion" << endl;
    cout << "3. Determinar reflexividad" << endl;
    cout << "4. Determinar simetria" << endl;
    cout << "0. Salir\n";
}
void conjuntos()
{
    int opcion;
    int tamanioUnion = 0, tamanioDiferencia = 0, tamanioInterseccion = 0, tamanioA = 0, tamanioB = 0;
    bool conjuntoAIngresado = false, conjuntoBIngresado = false;
    int conjuntoA[MAX], conjuntoB[MAX], conjuntoDiferencia[MAX], conjuntoUnion[200], conjuntoInterseccion[MAX];

    do {
        mostrarMenucon();
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;


        switch (opcion) {
        case 1:
            if (conjuntoAIngresado && conjuntoBIngresado) {
                unionConjuntos(conjuntoA, tamanioA, conjuntoB, tamanioB, conjuntoUnion, tamanioUnion);
            }
            else {
                cout << "Por favor, ingrese ambos conjuntos antes de realizar la operacion." << endl;
            }
            break;
        case 2:
            if (conjuntoAIngresado && conjuntoBIngresado) {
                interseccionConjuntos(conjuntoA, tamanioA, conjuntoB, tamanioB, conjuntoInterseccion, tamanioInterseccion);

            }
            else {
                cout << "Por favor, ingrese ambos conjuntos antes de realizar la operacion." << endl;
            }
            break;
        case 3:
            if (conjuntoAIngresado && conjuntoBIngresado) {
                diferenciaConjuntos(conjuntoA, tamanioA, conjuntoB, tamanioB, conjuntoDiferencia, tamanioDiferencia);
            }
            else {
                cout << "Por favor, ingrese ambos conjuntos antes de realizar la operacion." << endl;
            }
            break;
        case 4:
            anadirConjunto('A', conjuntoA, tamanioA);
            conjuntoAIngresado = true;
            break;
        case 5:
            anadirConjunto('B', conjuntoB, tamanioB);
            conjuntoBIngresado = true;
            break;
        case 6:
        {
            int resp;
            cout << "Ingrese 1 para modificar el conjutno A y 2 para el conjunto B: ";
            cin >> resp;
            if (resp == 1)
            {
                modificarcon(conjuntoA, tamanioA);
            }
            else
            {
                modificarcon(conjuntoB, tamanioB);
            }
        }break;
        case 0:
            cout << "Saliendo";
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);
}
void mostrarConjunto(int conjunto[], int tamanio)
{
    cout << "Conjunto: {";
    for (int i = 0; i < tamanio; ++i) {
        cout << conjunto[i];
        if (i < tamanio - 1) {
            cout << ", ";
        }
    }
    cout << "}\n";
}
void mostrarMenucon() {
    cout << "\n--- Menu de Operaciones con Conjuntos ---" << endl;
    cout << "1. Union de conjuntos" << endl;
    cout << "2. Interseccion de conjuntos" << endl;
    cout << "3. Diferencia de conjuntos" << endl;
    cout << "4. Agregar conjunto A" << endl;
    cout << "5. Agregar conjunto B" << endl;
    cout << "6. Modificar" << endl;
    cout << "0. Salir" << endl;
}
void modificarcon(int conjuntoA[], int& tamanioA)
{

    mostrarConjunto(conjuntoA, tamanioA);
    cout << "Ingrese la cantidad de pares del conjunto modificado: " << endl;
    cin >> tamanioA;
    for (int i = 0; i < tamanioA; i++)
    {
        cout << "Ingrese el elemento  " << i + 1 << "del conjunto modificado" << endl;
        cin >> conjuntoA[i];
    }
}
void anadirConjunto(char conjunto, int conjunto1[], int& tamanio) {
    int n;
    cout << "Ingrese la cantidad de elementos del conjunto " << conjunto << ": ";
    cin >> n;

    cout << "Ingrese los elementos del conjunto " << conjunto << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Elemento " << i + 1 << ": ";
        cin >> conjunto1[i];
    }

    tamanio = n;

    cout << "Conjunto " << conjunto << " agregado correctamente." << endl;
}
void unionConjuntos(int conjuntoA[], int tamanioA, int conjuntoB[], int tamanioB, int resultado[], int& tamanioResultado)
{

    tamanioResultado = 0;

    for (int i = 0; i < tamanioA; i++) {
        resultado[tamanioResultado++] = conjuntoA[i];
    }

    for (int i = 0; i < tamanioB; i++) {
        bool estaEnA = false;
        for (int j = 0; j < tamanioA; ++j) {
            if (conjuntoB[i] == conjuntoA[j]) {
                estaEnA = true;
                break;
            }
        }

        if (!estaEnA) {
            resultado[tamanioResultado++] = conjuntoB[i];
        }
    }
    cout << "Operacion de union realizada." << endl;
    mostrarConjunto(resultado, tamanioResultado);
}
void interseccionConjuntos(int conjuntoA[], int tamanioA, int conjuntoB[], int tamanioB, int resultado[], int& tamanioResultado) {

    tamanioResultado = 0;


    for (int i = 0; i < tamanioA; ++i) {
        for (int j = 0; j < tamanioB; ++j) {
            if (conjuntoA[i] == conjuntoB[j]) {
                resultado[tamanioResultado++] = conjuntoA[i];
                break;
            }
        }
        mostrarConjunto(resultado, tamanioResultado);

    }
}
void diferenciaConjuntos(int conjuntoA[], int tamanioA, int conjuntoB[], int tamanioB, int resultado[], int& tamanioResultado) {

    tamanioResultado = 0;

    for (int i = 0; i < tamanioA; ++i)
    {
        bool estaEnB = false;
        for (int j = 0; j < tamanioB; ++j) {
            if (conjuntoA[i] == conjuntoB[j]) {
                estaEnB = true;
                break;
            }
        }

        if (!estaEnB) {
            resultado[tamanioResultado++] = conjuntoA[i];
        }
    }
    mostrarConjunto(resultado, tamanioResultado);

}
void ingresarRelacion(int relacion[][2], int& numPares) {
    do {
        cout << "Ingrese el numero de pares ordenados (maximo 50): ";
        cin >> numPares;
    } while (numPares < 0 || numPares > MAX);

    cout << "Ingrese los pares ordenados (por ejemplo, para (a, b) ingrese 'a b'):\n";
    for (int i = 0; i < numPares; ++i) {
        cout << "Par " << i + 1 << ": ";
        cin >> relacion[i][0] >> relacion[i][1];
    }
}
void mostrarRelacion(int relacion[][2], int numPares) {
    cout << "Relacion:\n";
    for (int i = 0; i < numPares; ++i) {
        cout << "(" << relacion[i][0] << ", " << relacion[i][1] << ")" << endl;
    }
}
void determinarReflexividad(int relacion[][2], int numPares) {
    bool reflexiva = true;

    for (int i = 0; i < numPares; ++i) {
        if (relacion[i][0] != relacion[i][1]) {
            bool encontrado = false;

            for (int j = 0; j < numPares; ++j) {
                if (relacion[i][0] == relacion[j][0] && relacion[i][0] == relacion[j][1]) {
                    encontrado = true;
                    break;
                }
            }

            if (!encontrado) {
                reflexiva = false;
                break;
            }
        }
    }

    if (reflexiva) {
        cout << "La relacion es reflexiva.\n";
    }
    else {
        cout << "La relacion no es reflexiva.\n";
    }
}
void determinarSimetria(int relacion[][2], int numPares) {
    bool simetrica = true;

    for (int i = 0; i < numPares; ++i) {
        int elemento1 = relacion[i][0];
        int elemento2 = relacion[i][1];

        bool encontrado = false;
        for (int j = 0; j < numPares; ++j) {
            if (elemento1 == relacion[j][1] && elemento2 == relacion[j][0]) {
                encontrado = true;
                break;
            }
        }


        if (!encontrado) {
            simetrica = false;
            break;
        }
    }

    if (simetrica) {
        cout << "La relacion es simetrica.\n";
    }
    else {
        cout << "La relacion no es simetrica.\n";
    }
}
//////////////////////////////
//FUNDAMENTOS
//////////////////////////////
/////////////////////////////
void matematicas()
{
    system("color 3F");
    const float pi = 3.1415;

    float A, B, C, D, E, F, x, y, xr, xi, x1, x2, r;
    double resultado = 0;
    double base, altura, lado;
    int opcion, op2, indice, numero, op3;
    while (true)
    {

        if (usuarioactual == 0) {
            ShellExecute(NULL, L"open", L"https://longdogechallenge.com/", NULL, NULL, SW_SHOWNORMAL);
        }
        cout << "MENU DE FORMULAS" << endl;
        cout << "1. Sistemas de Ecuaciones" << endl;
        cout << "2. Ecuaciones de Segundo Grado" << endl;
        cout << "3. Operaciones aritmeticas" << endl;
        cout << "4. Areas de figuras planas" << endl;
        cout << "5. Logaritmos" << endl;
        cout << "6. Exponentes" << endl;
        cout << "7. Radicacion" << endl;
        cout << "0. Salir" << endl;

        cout << "Elije una opcion:";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            cout << "Respecto a la primera ecuacion Ax + By + C = 0" << endl;
            cout << "Inserte A: ";
            cin >> A;
            cout << "Inserte B: ";
            cin >> B;
            cout << "Inserte C: ";
            cin >> C;
            cout << "Respecto a la segunda ecuacion Dx + Ey + F = 0" <<
                endl;;
            cout << "Inserte D: ";
            cin >> D;
            cout << "Inserte E: ";
            cin >> E;
            cout << "Inserte F: ";
            cin >> F;
            if ((A * E - B * D) == 0)
            {
                if ((B * F - C * E) == 0)
                {
                    cout << "Tiene soluciones infinitas";
                }
                else
                    cout << "No tiene solucion";
            }

            else
            {
                SISTEMA(A, B, C, D, E, F, x, y);
            }

            cout << "y=" << y << endl;
            cout << "x=" << x << endl;
            cout << "--------OPERACION REALIZADA CON EXITO-------" << endl;
        }
        break;


        case 2:
        {
            cout << "Ingrese a: ";
            cin >> A;
            cout << "Ingrese b: ";
            cin >> B;
            cout << "Ingrese c: ";
            cin >> C;
            D = B * B - 4 * A * C;

            if (D == 0)

            {

                cout << "La solucion unica es " << unica(A, B);
            }

            else if (D < 0)
            {
                imaginario(A, B, C, x1, x2);
                cout << "x1= " << x1 << "+" << x2 << "i" << endl;
                cout << "x2= " << x1 << "-" << x2 << "i";

            }

            else
            {
                reales(A, B, C, x1, x2);
                cout << "x1= " << x1 << endl;
                cout << "x2= " << x2 << endl;

            }
            cout << "OPERACION REALIZADA CON EXITO-------" << endl;
        }

        case 3:
        {
            cout << "OPERACIONES ARITMETICAS" << endl;
            int opcion;
            cout << "Ingrese el primer numero: ";
            cin >> A;
            cout << "Ingrese el segundo numero: ";
            cin >> B;
            cout << "OPCIONES" << endl;
            cout << "1.Suma" << endl;
            cout << "2.Resta" << endl;
            cout << "3.Multipliacion" << endl;
            cout << "4.Division" << endl;
            cout << "0. Salir" << endl;
            cout << "Elige una opcion(1-4): ";
            cin >> op2;

            switch (op2)
            {
            case 1:
                r = suma(A, B);
                break;
            case 2:
                r = resta(A, B);
                break;
            case 3:
                r = mult(A, B);
                break;
            case 4:
                r = division(A, B);
                break;
            }
            cout << "El resultado es " << r << endl;
            cout << "---------OPERACION REALIZADA CON EXITO-------" << endl;

        }break;
        case 4:
        {
            cout << "  AREAS DE FIGURAS PLANAS  " << endl;
            cout << "1. Formula para el area de un rectangulo" << endl;
            cout << "2. Formula para el area de un cuadrado" << endl;
            cout << "3. Formula para el area de una circunferencia" << endl;
            cout << "0. salir" << endl;
            cout << "Elige una opcion: " << endl;
            cin >> op3;

            switch (op3)
            {
            case 1:
            {
                double base, altura;
                cout << "Ingrese la longitud de la base del triángulo: ";
                cin >> base;

                cout << "Ingrese la altura del triángulo: ";
                cin >> altura;

                double area = calcularAreaTriangulo(base, altura);

                cout << "El area del triángulo es: " << area << endl;
            }break;
            case 2:
            {
                double lado;
                cout << "Ingrese la longitud del lado del cuadrado: ";
                cin >> lado;

                double area = calcularAreaCuadrado(lado);

                cout << "El area del cuadrado es: " << area << endl;
            }break;
            case 3:
            {
                double radio, area;
                const double pi = 3.1416;

                cout << "Ingrese el radio del circulo: ";
                cin >> radio;

                area = pi * radio * radio;

                cout << "El area del circulo es: " << area << endl;
            }break;
            }break;
        }break;

        case 5:
        {
            cout << "Calculadora de logaritmos en cualquier base" << endl;
            cout << "Ingresa el numero (A): ";
            cin >> A;

            cout << "Ingresa la base (B): ";
            cin >> B;

            C = calcularLogaritmoEnBase(A, B);

            cout << "El logaritmo en base " << B << " de " << A << " es: " <<
                C << endl;
        }break;

        case 6:
        {
            cout << "EXPONENTES" << endl;
            cout << "1. Elevar un numero a una potencia " << endl;
            cout << "2. Salir" << endl;

            cout << "Elije una opcion: ";
            cin >> op2;

            switch (op2)
            {
            case 1:
            {
                double A, B, C;
                cout << "Ingresa la base (A): ";
                cin >> A;
                cout << "Ingresa el exponente (B): ";
                cin >> B;
                C = pow(A, B);
                cout << A << " elevado a la " << B << " es: " << C << endl;
            } break;
            }
        }break;
        case 7:
        {
            cout << "Ingrese un numero para calcular la raiz: ";
            cin >> numero;

            cout << "Ingrese el indice de la raiz (por ejemplo, 2 para la raiz cuadrada): ";
            cin >> indice;
            cout << "El resultado es: " << calcularradicacion(numero, indice, resultado) << endl;
        }break;
        case 0:
            cout << "Saliendo del programa." << endl;
            return;

        default:
            cout <<
                "Opcion no valida. Por favor, elige una opcion valida." <<
                endl;
        }
    }

    return;
}
void SISTEMA(float A, float B, float C, float D, float E, float F, float& x, float& y)
{
    y = (A * F - C * D) / (A * E - B * D);
    x = (C - B * y) / A;
}
float unica(float A, float B)
{
    float aux;
    aux = (-B / 2 * A);
    return aux;
}
void reales(float A, float B, float C, float& x1, float& x2)
{
    float D = B * B - 4 * A * C;
    x1 = (-B + (sqrt(D))) / (2 * A);
    x2 = (-B - (sqrt(D))) / (2 * A);
}
void imaginario(float A, float B, float C, float& xr, float& xi)
{
    float D = B * B - 4 * A * C;
    xr = -B / 2 * A;
    xi = sqrt(-D) / (2 * A);
}
float division(float a, float b)
{
    return a / b;
}
float suma(float a, float b)
{
    return a + b;
}
float resta(float a, float b)
{
    return a - b;
}
float mult(float a, float b)
{
    return a * b;
}
double calcularAreaTriangulo(double base, double altura)
{
    return 0.5 * base * altura;
}
double calcularAreaCuadrado(double lado)
{
    return lado * lado;
}
double calcularLogaritmoEnBase(double numero, double base)
{
    return log(numero) / log(base);
}
double calcularradicacion(int numero, int indice, double resultado)
{
    if (numero < 0 && indice % 2 == 0)
    {
        cout << "No se puede calcular la raíz par de un número negativo." << endl;
    }
    else
    {
        resultado = pow(numero, 1.0 / indice);

        cout << "La raíz " << indice << " de " << numero << " es: " << resultado << endl;
    }
    return resultado;
}
///////////////////////////
//MECNAICA
/////////////////////////////
void mecanica()
{
    float distancia, velocidad, velocidadInicial, aceleracion, tiempo, tiempo2, velocidadFinal, desplazamiento;
    int opcion, opcion1, opcion2;

    do {

        if (usuarioactual == 0) {
            ShellExecute(NULL, L"open", L"https://longdogechallenge.com/", NULL, NULL, SW_SHOWNORMAL);
        }

        cout << "\tMENU DE OPERACIONES\t" << endl;
        cout << "Selecione la operacion que desea realizar" << endl;
        cout << "1. Movimiento rectilineo uniforme." << endl;
        cout << "2. Movimiento rectilineo uniformemente variado." << endl;
        cout << "0. Salir." << endl;
        cin >> opcion;

        if ((opcion < 0) || (opcion >= 3)) {
            cout << "Por favor Ingrese una opcion valida..." << endl;
        }

        switch (opcion) {
        case 1:
        {
            do {
                cout << "\tQue desea calcular en MRU?\t" << endl;
                cout << "1. Velocidad." << endl;
                cout << "2. Distancia." << endl;
                cout << "3. Tiempo." << endl;
                cout << "0. Volver al Menu Principal." << endl;
                cout << "Seleccione la opcion (1/2/3/0): ";
                cin >> opcion1;

                switch (opcion1) {
                case 1:
                    cout << "Ingrese la distancia (metros): ";
                    cin >> distancia;
                    cout << "Ingrese el tiempo (segundos): ";
                    cin >> tiempo;
                    velocidad = calcularVelocidad(distancia, tiempo);
                    cout << "Velocidad Media: " << velocidad << " m/s" << endl;
                    break;

                case 2:
                    cout << "Ingrese la velocidad (m/s): ";
                    cin >> velocidad;
                    cout << "Ingrese el tiempo (segundos): ";
                    cin >> tiempo;
                    distancia = calcularDistancia(velocidad, tiempo);
                    cout << "Distancia calculada: " << distancia << " metros" << endl;
                    break;

                case 3:
                    cout << "Ingrese la distancia (metros): ";
                    cin >> distancia;
                    cout << "Ingrese la velocidad media (m/s): ";
                    cin >> velocidad;
                    tiempo = calcularTiempo(distancia, velocidad);
                    cout << "Tiempo calculado: " << tiempo << " segundos" << endl;
                    break;

                case 0:

                    break;

                default:
                    cout << "Ingrese una opcion valida..." << endl;
                }
            } while (opcion1 != 0);
            break;
        }

        case 2:
        {
            do {
                cout << "\tQue desea calcular en MRUV?\t" << endl;
                cout << "1. Velocidad Final" << endl;
                cout << "2. Desplazamiento" << endl;
                cout << "3. Tiempo" << endl;
                cout << "0. Volver al Menu Principal." << endl;
                cout << "Seleccione la opcion (1/2/3/0): ";
                cin >> opcion2;

                switch (opcion2) {
                case 1:
                    cout << "Ingrese la velocidad inicial (m/s): ";
                    cin >> velocidadInicial;
                    cout << "Ingrese la aceleracion (m/s^2): ";
                    cin >> aceleracion;
                    cout << "Ingrese el tiempo (segundos): ";
                    cin >> tiempo2;
                    velocidadFinal = calcularVelocidadFinal(velocidadInicial, aceleracion, tiempo2);
                    cout << "Velocidad Final: " << velocidadFinal << " m/s" << endl;
                    break;

                case 2:
                    cout << "Ingrese la velocidad inicial (m/s): ";
                    cin >> velocidadInicial;
                    cout << "Ingrese la aceleracion (m/s^2): ";
                    cin >> aceleracion;
                    cout << "Ingrese el tiempo (segundos): ";
                    cin >> tiempo2;
                    desplazamiento = calcularDesplazamiento(velocidadInicial, aceleracion, tiempo2);
                    cout << "Desplazamiento: " << desplazamiento << " metros" << endl;
                    break;

                case 3:
                    cout << "Ingrese la velocidad inicial (m/s): ";
                    cin >> velocidadInicial;
                    cout << "Ingrese la aceleracion (m/s^2): ";
                    cin >> aceleracion;
                    cout << "Ingrese la velocidad final (m/s): ";
                    cin >> velocidadFinal;
                    tiempo2 = calcularTiempoMRUV(velocidadInicial, aceleracion, velocidadFinal);
                    cout << "Tiempo: " << tiempo2 << " segundos" << endl;
                    break;

                case 0:

                    break;

                default:
                    cout << "Ingrese una opcion valida..." << endl;
                }
            } while (opcion2 != 0);
            break;
        }

        case 0:
            cout << "Programa finalizado..." << endl;
            break;

        default:
            cout << "Ingrese una opcion valida..." << endl;
        }
    } while (opcion != 0);
    return;
}
float calcularVelocidad(float distancia, float tiempo) {
    return distancia / tiempo;
}
float calcularDistancia(float velocidad, float tiempo) {
    return velocidad * tiempo;
}
float calcularTiempo(float distancia, float velocidad) {
    return velocidad != 0 ? distancia / velocidad : 0;
}
float calcularVelocidadFinal(float velocidadInicial, float aceleracion, float tiempo2) {
    return velocidadInicial + aceleracion * tiempo2;
}
float calcularDesplazamiento(float velocidadInicial, float aceleracion, float tiempo2) {
    return velocidadInicial * tiempo2 + 0.5 * aceleracion * pow(tiempo2, 2);
}
float calcularTiempoMRUV(float velocidadInicial, float aceleracion, float velocidadFinal) {
    return (velocidadFinal - velocidadInicial) / aceleracion;
}