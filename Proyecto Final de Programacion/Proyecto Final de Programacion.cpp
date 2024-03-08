#include <iostream>
#include <fstream>
#include <string>
#include <Lmcons.h>
#include <windows.h>
#include <filesystem>
#include <direct.h>

using namespace std;

// ------------------------------- CONSTANTES DE COLORES EN CONSOLA -------------------------------------

#define Azul "\33[94m"
#define Rojo "\33[91m"
#define Verde "\33[92m"
#define Negro "\33[90m"
#define Blanco "\33[0;7m"
#define Reset "\33[0m"

// ------------------------------------------- ESTRUCTURAS ----------------------------------------------

struct student
{
    string ID, name, lastname, faculty, semester, career;
};

struct teacher
{
    string ID, name, lastname, dependency, position;
    int salary;
};

// ------------------------------------ VARIABLES GLOBALES -----------------------------------------------

char username[UNLEN + 1];
DWORD username_len = UNLEN + 1;
filesystem::path RutaActual = filesystem::current_path();

int N_Estudiantes = 0, N_Docentes = 0;
student Estudiante;
teacher Docente;
string RutaDescargas = "C:/Users/";
string RutaPrograma = RutaActual.string();

// -------------------------------------- FUNCIONES PROTOTIPO -----------------------------------------------

void IngresarEstudiante();
void IngresarDocente();
int Menu(string usuario);
void Mostrar(string ruta, string archivo);
void Eliminar(string carpeta, string archivo, int& cantidad);
void Busqueda(string carpeta, string archivo);
void Modificar(string carpeta, string archivo);

string obtenerID(string usuario, string motivo);
string BuscarID(string registro, string ID);
string SustantivoPropio(string Palabra);

// ---------------------------------------- FUNCION PRINCIPAL -------------------------------------------------

int main()
{
    GetUserNameA(username, &username_len);
    RutaDescargas += string(username) + "/Downloads/";

    ofstream Registro_E, Registro_D;

    if (!_mkdir((RutaPrograma + "/Base de Datos").c_str()))
        cout << Verde << "\n✅ ¡Carpeta Base de Datos creada exitosamente! ✅" << endl;

    if (!_mkdir((RutaPrograma + "/Base de Datos/Estudiantes").c_str()) && !_mkdir((RutaPrograma + "/Base de Datos/Docentes").c_str()))
        cout << Verde << "✅ ¡Carpetas Estudiantes y Docentes creadas exitosamente! ✅" << endl;

    Registro_E.open((RutaPrograma + "/Base de Datos/Estudiantes/Base_Estudiantes.txt").c_str(), ios::out);

    Registro_E << "\t\t\t\t\tESCUELA DE FORMACION DE TECNOLOGOS - ESFOT" << endl;
    Registro_E << "\t\t\t\t\t\tREPORTE DE ''ESTUDIANTES''" << endl;
    Registro_E << " " << endl
        << "Periodo: 2023A" << endl;
    Registro_E << " " << endl
        << "N°\tID\t\tNombre\t\tApellido\t\tFacultad\t\tSemestre\t\tCarrera" << endl;

    Registro_D.open((RutaPrograma + "/Base de Datos/Docentes/Base_Docentes.txt").c_str(), ios::out);

    Registro_D << "\t\t\t\t\tESCUELA DE FORMACION DE TECNOLOGOS - ESFOT" << endl;
    Registro_D << "\t\t\t\t\t\tREPORTE DE ''DOCENTES''" << endl;
    Registro_D << " " << endl
        << "Periodo: 2023A" << endl;
    Registro_D << " " << endl
        << "N°\tID\t\tNombre\t\tApellido\t\tDependencia\t\tCargo\t\tSueldo" << endl;

    Registro_E.close();
    Registro_D.close();

    int Opcion_M = 0;
    while (Opcion_M != 3)
    {
        cout << endl
            << Negro << "==================================== " << Reset << " MENÚ PRINCIPAL 🏫 📋" << Negro << " ====================================" << endl;
        cout << endl
            << "1." << Azul << " Estudiantes";
        cout << endl
            << Negro << "2." << Azul << " Docentes";
        cout << endl
            << Negro << "3." << Azul << " Salir";
        cout << endl
            << endl
            << "Escoja la opción deseada: " << Reset;
        cin >> Opcion_M;

        while (Opcion_M > 3 && Opcion_M < 1)
        {
            cout << Rojo << "❌ ¡Opción inválida! ❌";
            cout << endl
                << Azul << "Escoja la opción deseada: " << Reset;
            cin >> Opcion_M;
        }

        if (Opcion_M == 1)
        {
            int Opcion_E = 1;
            while (Opcion_E != 6)
            {
                Opcion_E = Menu("Estudiante");
                switch (Opcion_E)
                {
                case 1:
                    IngresarEstudiante();
                    break;
                case 2:
                    if (N_Estudiantes > 0)
                        Mostrar(RutaPrograma + "/Base de Datos/Estudiantes/", "Base_Estudiantes.txt");
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún estudiante! ❌" << endl;
                    break;
                case 3:
                    if (N_Estudiantes > 0)
                        Eliminar("Estudiantes", "Base_Estudiantes.txt", N_Estudiantes);
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún estudiante! ❌" << endl;
                    break;
                case 4:
                    if (N_Estudiantes > 0)
                        Busqueda("Estudiantes", "Base_Estudiantes.txt");
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún estudiante! ❌" << endl;
                    break;
                case 5:
                    if (N_Estudiantes > 0)
                        Modificar("Estudiantes", "Base_Estudiantes.txt");
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún estudiante! ❌" << endl;
                    break;
                }
            }
        }
        else if (Opcion_M == 2)
        {
            int Opcion_D = 1;
            while (Opcion_D != 6)
            {
                Opcion_D = Menu("Docente");

                switch (Opcion_D)
                {
                case 1:
                    IngresarDocente();
                    break;
                case 2:
                    if (N_Docentes > 0)
                        Mostrar(RutaPrograma + "/Base de Datos/Docentes/", "Base_Docentes.txt");
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún docente! ❌" << endl;
                    break;
                case 3:
                    if (N_Docentes > 0)
                        Eliminar("Docentes", "Base_Docentes.txt", N_Docentes);
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún docente! ❌" << endl;
                    break;
                case 4:
                    if (N_Docentes > 0)
                        Busqueda("Docentes", "Base_Docentes.txt");
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún docente! ❌" << endl;
                    break;
                case 5:
                    if (N_Docentes > 0)
                        Modificar("Docentes", "Base_Docentes.txt");
                    else
                        cout << Rojo << endl
                        << "❌ ¡Aún no se registra ningún docente! ❌" << endl;
                    break;
                }
            }
        }
    }

    cout << endl
        << Rojo << "Saliendo del programa... 👋" << endl
        << endl
        << Reset;
    return 0;
}

// ------------------------------------------- REGISTRO ESTUDIANTES ------------------------------------------------

void IngresarEstudiante()
{
    char Nuevo = 'y';
    ofstream Registro;

    Registro.open((RutaPrograma + "/Base de Datos/Estudiantes/Base_Estudiantes.txt").c_str(), ios::app);

    if (Registro.fail())
        cout << endl
        << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

    do
    {
        bool Existe = false;
        cout << endl
            << Negro << "===========================================================================================" << endl;
        cout << endl
            << Verde << "Ingresar Nuevo Estudiante 👨‍🎓👩‍🎓" << endl;

        Estudiante.ID = obtenerID("estudiante", "crear");

        if (BuscarID("Estudiantes", Estudiante.ID) != "")
            Existe = true;
        if (BuscarID("Docentes", Estudiante.ID) != "")
            Existe = true;

        if (!Existe)
        {
            cout << Azul << "Ingrese el primer nombre del estudiante: " << Reset;
            cin >> Estudiante.name;
            Estudiante.name = SustantivoPropio(Estudiante.name);
            cout << Azul << "Ingrese el primer apellido del estudiante: " << Reset;
            cin >> Estudiante.lastname;
            Estudiante.lastname = SustantivoPropio(Estudiante.lastname);
            cin.ignore();

            cout << Azul << "Ingrese la facultad del estudiante: " << Reset;
            getline(cin, Estudiante.faculty);
            Estudiante.faculty = SustantivoPropio(Estudiante.faculty);
            cout << Azul << "Ingrese el semestre del estudiante: " << Reset;
            cin >> Estudiante.semester;
            Estudiante.semester = SustantivoPropio(Estudiante.semester);

            cin.ignore();
            cout << Azul << "Ingrese la carrera que estudia el estudiante: " << Reset;
            getline(cin, Estudiante.career);
            Estudiante.career = SustantivoPropio(Estudiante.career);

            Registro << N_Estudiantes + 1 << "\t" << Estudiante.ID << "\t" << Estudiante.name << "\t\t" << Estudiante.lastname << "\t\t" << Estudiante.faculty << "\t\t" << Estudiante.semester << "\t\t" << Estudiante.career << endl;
            N_Estudiantes++;

            cout << Verde << endl
                << "✅ ¡Estudiante registrado existosamente en Base_Estudiantes.txt! ✅" << endl;
        }
        else
            cout << Rojo << "❌ ¡ID ya existente! (Recuerde que nadie en la institución puede tener el mismo ID) ❌" << endl;

        do
        {
            cout << Blanco << "❔ ¿Desea ingresar otro estudiante? (y/n) ❔: " << Reset;
            cin >> Nuevo;
            Nuevo = tolower(Nuevo);
        } while (Nuevo != 'y' && Nuevo != 'n');

    } while (Nuevo == 'y');

    Registro.close();
}

// --------------------------------------------- REGISTRO DOCENTES -------------------------------------------------

void IngresarDocente()
{
    char Nuevo = 'y';
    ofstream Registro;

    Registro.open((RutaPrograma + "/Base de Datos/Docentes/Base_Docentes.txt").c_str(), ios::app);

    if (Registro.fail())
        cout << endl
        << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

    cout << endl
        << Negro << "===========================================================================================" << endl;

    do
    {
        bool Existe = false;

        cout << endl
            << Verde << "Ingresar Nuevo Docente "
            << "👨‍🏫👩‍🏫" << endl;

        Docente.ID = obtenerID("docente", "crear");

        if (BuscarID("Docentes", Docente.ID) != "")
            Existe = true;
        if (BuscarID("Estudiantes", Docente.ID) != "")
            Existe = true;

        if (!Existe)
        {
            cout << Azul << "Ingrese el primer nombre del docente: " << Reset;
            cin >> Docente.name;
            Docente.name = SustantivoPropio(Docente.name);
            cout << Azul << "Ingrese el primer apellido del docente: " << Reset;
            cin >> Docente.lastname;
            Docente.lastname = SustantivoPropio(Docente.lastname);
            cin.ignore();

            cout << Azul << "Ingrese la dependencia del docente: " << Reset;
            getline(cin, Docente.dependency);
            Docente.dependency = SustantivoPropio(Docente.dependency);
            cout << Azul << "Ingrese el cargo del docente (Ocasional o Tecnico): " << Reset;
            getline(cin, Docente.position);
            Docente.position = SustantivoPropio(Docente.position);

            while (Docente.position != "Ocasional" && Docente.position != "Tecnico")
            {
                cout << Rojo << "❌ ¡Cargo inválido! (Ingrese una de las dos opciones mencionadas) ❌" << endl;
                cout << Azul << "Ingrese el cargo del docente (Ocasional o Tecnico): " << Reset;
                getline(cin, Docente.position);
                Docente.position = SustantivoPropio(Docente.position);
            }

            if (Docente.position == "Ocasional")
                Docente.salary = 2300;
            else
                Docente.salary = 1700;

            Registro << N_Docentes + 1 << "\t" << Docente.ID << "\t" << Docente.name << "\t\t" << Docente.lastname << "\t\t" << Docente.dependency << "\t\t" << Docente.position << "\t\t" << Docente.salary << endl;
            N_Docentes++;

            cout << Verde << endl
                << "✅ ¡Docente registrado existosamente en Base_Docentes.txt! ✅" << endl;
        }
        else
            cout << Rojo << "❌ ¡ID ya existente! (Recuerde que nadie en la institución puede tener el mismo ID) ❌" << endl;

        do
        {
            cout << endl
                << Blanco << "❔ ¿Desea ingresar otro docente? (y/n) ❔: " << Reset;
            cin >> Nuevo;
        } while (tolower(Nuevo) != 'y' && tolower(Nuevo) != 'n');

    } while (tolower(Nuevo) == 'y');

    Registro.close();
}

// ------------------------------------------ FUNCIONES COMUNES ------------------------------------------------

void Mostrar(string ruta, string archivo)
{
    ifstream lectura;
    ofstream guardado;
    string linea, nombre_guardar, rutaLectura, rutaGuardar;
    char respuesta;

    rutaLectura = ruta + archivo;
    lectura.open(rutaLectura.c_str(), ios::in);

    if (lectura.fail())
        cout << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

    cout << endl
        << Negro << "===========================================================================================" << endl;
    cout << endl
        << Verde << "Mostrar Registro 📋" << endl;

    while (getline(lectura, linea))
        cout << Reset << linea << endl;

    lectura.close();

    do
    {
        cout << Blanco << "❔ ¿Desea imprimir el reporte? (y/n) ❔: " << Reset;
        cin >> respuesta;
    } while (respuesta != 'y' && respuesta != 'n');

    cin.ignore();
    if (respuesta == 'y')
    {
        cout << Azul << "Ingrese el nombre para el archivo (sin la extension .txt): " << Reset;
        getline(cin, nombre_guardar);

        lectura.open(rutaLectura.c_str(), ios::in);

        rutaGuardar = RutaDescargas + nombre_guardar + ".txt";
        guardado.open(rutaGuardar.c_str(), ios::out);

        if (guardado.fail())
            cout << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

        while (getline(lectura, linea))
            guardado << linea << endl;

        cout << Verde << endl
            << "✅ ¡El archivo " << nombre_guardar << ".txt creado exitosamente! (Revise su carpeta de Descargas) ✅" << endl;
    }

    lectura.close();
    guardado.close();
}

void Eliminar(string carpeta, string archivo, int& cantidad)
{
    ifstream lectura;
    ofstream nuevo;
    string linea, usuario, buscar, eliminar, informacion, Ruta = RutaPrograma + "/Base de Datos/" + carpeta + "/";
    char respuesta, seguir = 'y';

    while (tolower(seguir) == 'y')
    {
        if (carpeta == "Estudiantes")
        {
            informacion = "N°\tID\t\tNombre\t\tApellido\t\tFacultad\t\tSemestre\t\tCarrera";
            usuario = "estudiante";
        }
        else if (carpeta == "Docentes")
        {
            informacion = "N°\tID\t\tNombre\t\tApellido\t\tDependencia\t\tCargo\t\tSueldo";
            usuario = "docente";
        }

        buscar = obtenerID(usuario, "eliminar");

        eliminar = BuscarID(carpeta, buscar);

        if (eliminar != "")
        {
            cout << Verde << endl
                << "Los datos del " << usuario << " son:" << endl;
            cout << Azul << endl
                << informacion << Reset << endl
                << eliminar << endl;
            cout << endl
                << Blanco << "❓ ¿Está seguro de querer eliminarlo? (y/n) ❓: " << Reset;
            cin >> respuesta;

            while (respuesta != 'y' && respuesta != 'n')
            {
                cout << endl
                    << Blanco << "❓ ¿Está seguro de querer eliminarlo? (y/n) ❓: " << Reset;
                cin >> respuesta;
            }
        }
        else
            cout << Rojo << "❌ ¡ID de " << usuario << " no existente! ❌" << endl;

        if (respuesta == 'y')
        {

            lectura.open((Ruta + archivo).c_str(), ios::in);

            if (lectura.fail())
                cout << endl
                << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

            nuevo.open((Ruta + "Temporal.txt").c_str(), ios::out);

            if (nuevo.fail())
                cout << endl
                << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

            while (getline(lectura, linea))
                if (linea != eliminar)
                    nuevo << linea << endl;

            cout << Verde << endl
                << "✅ ¡El " << usuario << " se ha eliminado exitosamente del registro! ✅" << endl;

            cantidad--;

            lectura.close();
            nuevo.close();

            remove((Ruta + archivo).c_str());
            rename((Ruta + "temporal.txt").c_str(), (Ruta + archivo).c_str());
        }

        if (cantidad > 0)
        {
            cout << endl
                << Blanco << "❔ ¿Desea eliminar otro " << usuario << "? (y/n) ❔: " << Reset;
            cin >> seguir;

            while (tolower(seguir) != 'y' && tolower(seguir) != 'n')
            {
                cout << Blanco << "❔ ¿Desea eliminar otro " << usuario << "? (y/n) ❔: " << Reset;
                cin >> seguir;
            }
        }
        else
            seguir = 'n';
    }

    lectura.close();
}

void Busqueda(string carpeta, string archivo)
{
    string linea, usuario, ID, buscar, informacion, Ruta = RutaPrograma + "/Base de Datos/" + carpeta + "/";
    char respuesta, seguir = 'y';

    while (tolower(seguir) == 'y')
    {
        if (carpeta == "Estudiantes")
        {
            informacion = "N°\tID\t\tNombre\t\tApellido\t\tFacultad\t\tSemestre\t\tCarrera";
            usuario = "estudiante";
        }
        else if (carpeta == "Docentes")
        {
            informacion = "N°\tID\t\tNombre\t\tApellido\t\tDependencia\t\tCargo\t\tSueldo";
            usuario = "docente";
        }

        cout << endl
            << Negro << "===========================================================================================" << endl;
        cout << endl
            << Verde << "Buscar Informacion de un " << SustantivoPropio(usuario) << " 📋" << endl;

        ID = obtenerID(usuario, "buscar");

        buscar = BuscarID(carpeta, ID);

        if (buscar != "")
        {
            cout << Verde << endl
                << "Los datos del " << usuario << " son:" << endl;
            cout << Azul << endl
                << informacion << Reset << endl
                << buscar << endl;
        }
        else
            cout << Rojo << "❌ ¡No se encontro a ningun " << usuario << " con ese ID! ❌" << endl;

        do
        {
            cout << Blanco << "\n❔ ¿Desea buscar otro " << usuario << "? (y/n) ❔: " << Reset;
            cin >> seguir;
        } while (tolower(seguir) != 'y' && tolower(seguir) != 'n');
    }
}

void Modificar(string carpeta, string archivo)
{
    ifstream lectura;
    ofstream nuevo;
    string linea, usuario, buscar, modificar, informacion, Ruta = RutaPrograma + "/Base de Datos/" + carpeta + "/";
    char respuesta, seguir = 'y';

    while (tolower(seguir) == 'y')
    {
        if (carpeta == "Estudiantes")
        {
            informacion = "N°\tID\t\tNombre\t\tApellido\t\tFacultad\t\tSemestre\t\tCarrera";
            usuario = "estudiante";
        }
        else if (carpeta == "Docentes")
        {
            informacion = "N°\tID\t\tNombre\t\tApellido\t\tDependencia\t\tCargo\t\tSueldo";
            usuario = "docente";
        }

        cout << endl
            << Negro << "===========================================================================================" << endl;
        cout << endl
            << Verde << "Modificar Informacion de un " << SustantivoPropio(usuario) << " 📋" << endl;

        buscar = obtenerID(usuario, "modificar");

        modificar = BuscarID(carpeta, buscar);

        if (modificar != "")
        {
            cout << Verde << endl
                << "Los datos del " << usuario << " son:" << endl;
            cout << Azul << endl
                << informacion << Reset << endl
                << modificar << endl;
            cout << endl
                << Blanco << "❓ ¿Está seguro de querer modificarlo? (y/n) ❓: " << Reset;
            cin >> respuesta;

            while (respuesta != 'y' && respuesta != 'n')
            {
                cout << endl
                    << Blanco << "❓ ¿Está seguro de querer modificarlo? (y/n) ❓: " << Reset;
                cin >> respuesta;
            }
        }
        else
            cout << Rojo << "❌ ¡ID de " << usuario << " no existente! ❌" << endl;

        if (respuesta == 'y')
        {
            lectura.open((Ruta + archivo).c_str(), ios::in);

            if (lectura.fail())
            {
                cout << endl
                    << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;
            }

            nuevo.open((Ruta + "Temporal.txt").c_str(), ios::out);

            if (nuevo.fail())
                cout << endl
                << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

            int palabras = 0, posicion_a_modificar;

            for (int i = 0; i < modificar.length(); i++)
            {
                if (modificar[i] == '\t' && modificar[i + 1] != ' ')
                {
                    palabras++;
                    if (palabras == 5)
                    {
                        posicion_a_modificar = i;
                        break;
                    }
                }
            }

            string nueva_info = modificar.substr(0, posicion_a_modificar);

            if (carpeta == "Estudiantes")
            {
                cin.ignore();
                cout << endl
                    << endl
                    << Azul << "Ingrese la facultad del estudiante: " << Reset;
                getline(cin, Estudiante.faculty);
                Estudiante.faculty = SustantivoPropio(Estudiante.faculty);
                cout << Azul << "Ingrese el semestre del estudiante: " << Reset;
                cin >> Estudiante.semester;
                Estudiante.semester = SustantivoPropio(Estudiante.semester);
                cin.ignore();
                cout << Azul << "Ingrese la carrera que estudia el estudiante: " << Reset;
                getline(cin, Estudiante.career);
                Estudiante.career = SustantivoPropio(Estudiante.career);

                nueva_info += "\t\t" + Estudiante.faculty + "\t\t" + Estudiante.semester + "\t\t" + Estudiante.career;
            }
            else
            {
                cin.ignore();
                cout << Azul << endl
                    << endl
                    << "Ingrese la dependencia del docente: " << Reset;
                getline(cin, Docente.dependency);
                Docente.dependency = SustantivoPropio(Docente.dependency);
                cout << Azul << "Ingrese el cargo del docente (Ocasional o Tecnico): " << Reset;
                getline(cin, Docente.position);
                Docente.position = SustantivoPropio(Docente.position);

                while (Docente.position != "Ocasional" && Docente.position != "Tecnico")
                {
                    cout << Rojo << "❌ ¡Cargo inválido! (Ingrese una de las dos opciones mencionadas) ❌" << endl;
                    cout << Azul << "Ingrese el cargo del docente (Ocasional o Tecnico): " << Reset;
                    getline(cin, Docente.position);
                    Docente.position = SustantivoPropio(Docente.position);
                }

                if (Docente.position == "Ocasional")
                    Docente.salary = 2300;
                else
                    Docente.salary = 1700;

                nueva_info += "\t\t" + Docente.dependency + "\t\t" + Docente.position + "\t\t" + to_string(Docente.salary);
            }

            while (getline(lectura, linea))
            {
                if (linea != modificar)
                    nuevo << linea << endl;
                else
                    nuevo << nueva_info << endl;
            }

            cout << Verde << endl
                << "✅ ¡El " << usuario << " se ha modificado exitosamente del registro! ✅" << endl;

            lectura.close();
            nuevo.close();

            remove((Ruta + archivo).c_str());
            rename((Ruta + "Temporal.txt").c_str(), (Ruta + archivo).c_str());
        }

        do
        {
            cout << Blanco << "❔ ¿Desea modificar la informacion de otro " << usuario << "? (y/n) ❔: " << Reset;
            cin >> seguir;
        } while (tolower(seguir) != 'y' && tolower(seguir) != 'n');
    }

    lectura.close();
}

// ------------------------------------------- FUNCIONES DE APOYO ----------------------------------------------

int Menu(string usuario)
{
    int opcion;
    string usuarioUpper, emojis;
    if (usuario == "Estudiante")
    {
        usuarioUpper = "ESTUDIANTE";
        emojis = "👨‍🎓👩‍🎓";
    }
    else if (usuario == "Docente")
    {
        usuarioUpper = "DOCENTE";
        emojis = "👨‍🏫👩‍🏫";
    }

    cout << endl
        << Negro << "================================= " << Reset << "MENÚ " + usuarioUpper + "S " + emojis << Negro << " =================================" << endl;
    cout << endl
        << "1." << Azul << " Ingresar Nuevo " + usuario;
    cout << endl
        << Negro << "2." << Azul << " Mostrar Lista de " + usuario + "s";
    cout << endl
        << Negro << "3." << Azul << " Eliminar " + usuario;
    cout << endl
        << Negro << "4." << Azul << " Buscar " + usuario;
    cout << endl
        << Negro << "5." << Azul << " Modificar " + usuario;
    cout << endl
        << Negro << "6." << Azul << " Volver al Menú Principal";
    cout << endl
        << endl
        << "Escoja la opción deseada: " << Reset;
    cin >> opcion;

    while (opcion > 6 || opcion <= 0)
    {
        cout << Rojo << "❌ ¡Opción inválida! ❌";
        cout << endl
            << Azul << "Escoja la opción deseada: " << Reset;
        cin >> opcion;
    }

    return opcion;
}

string obtenerID(string usuario, string motivo)
{
    string ID;
    cout << endl
        << Azul << "Ingrese el ID del " << usuario << " a " + motivo + ": " << Reset;
    cin >> ID;

    while (ID.length() != 9)
    {
        cout << Rojo << "❌ ¡ID inválido! (Debe contener 9 caracteres) ❌";
        cout << endl
            << Azul << "Ingrese el ID del " << usuario << " a " + motivo + ": " << Reset;
        cin >> ID;
    }

    return ID;
}

string BuscarID(string registro, string ID)
{
    ifstream Busqueda;
    string Ruta = RutaPrograma + "\\Base de Datos\\" + registro + "\\Base_" + registro + ".txt", Linea;
    int Encontrado;

    Busqueda.open(Ruta.c_str(), ios::in);

    if (Busqueda.fail())
        cout << Rojo << "❌ ¡No se pudo encontrar el archivo! ❌" << endl;

    while (getline(Busqueda, Linea))
    {
        Encontrado = Linea.find(ID);
        if (Encontrado != string::npos && Encontrado != 0)
        {
            return Linea;
        }
    }

    Busqueda.close();
    return "";
}

string SustantivoPropio(string Palabra)
{
    for (int i = 0; i < Palabra.length(); i++)
    {
        if (i == 0)
        {
            Palabra[i] = toupper(Palabra[i]);
        }
        else if (Palabra[i] == ' ')
        {
            Palabra[i + 1] = toupper(Palabra[i + 1]);
        }
        else
        {
            Palabra[i] = tolower(Palabra[i]);
        }
    }
    return Palabra;
}