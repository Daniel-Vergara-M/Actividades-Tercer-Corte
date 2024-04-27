#include "../methods.h"
#include <stack>
#include <string>
#include <queue>

/*
Sistema para fila virtual
El usuario ingresa al sistema y lo pone en fila. (Queue)
Mostrar en que posición esta y cuanto se demora para salir de la fila
Mostrar cuando ya llegue para comprar la boleta
*/

using namespace std;

struct Persona
{
    string nombre;
    Persona(string nombre) : nombre(nombre) {}
};

class FilaVirtual
{
private:
    queue<Persona *> personas;
    public:
    FilaVirtual() : personas(){};
    ~FilaVirtual()
    {
        while (!personas.empty())
        {
            personas.pop();
        }
    }
    void agregarPersona(Persona *persona)
    {
        personas.push(persona);
    }

    void mostrarFila()
    {
        queue<Persona *> temp = personas;
        int i = 1;
        while (!temp.empty())
        {
            Persona *per = temp.front();
            print(to_string(i) + ". " + per->nombre);
            temp.pop();
            i++;
        }
    }

    void salirFila()
    {
        if (personas.empty())
        {
            print(RED + "No hay personas en la fila" + CLEAR);
            return;
        }
        Persona *persona = personas.front();
        print("Saliendo de la fila: " + persona->nombre);
        personas.pop();
    }

    void salirFilas()
    {
        while (!personas.empty())
        {
            salirFila();
        }
    }

    void mostrarPosicion(Persona *persona)
    {
        queue<Persona *> temp = personas;
        int i = 1;
        while (!temp.empty())
        {
            Persona *per = temp.front();
            if (per->nombre == persona->nombre)
            {
                print("Posición: " + to_string(i));
                return;
            }
            temp.pop();
            i++;
        }
        print(RED + "No se encontró a la persona" + CLEAR);
    }

    void mostrarTiempo(Persona *persona)
    {
        queue<Persona *> temp = personas;
        int i = 1;
        while (!temp.empty())
        {
            Persona *per = temp.front();
            if (per->nombre == persona->nombre)
            {
                print("Tiempo estimado: " + to_string(i * 5) + " minutos");
                return;
            }
            temp.pop();
            i++;
        }
        print(RED + "No se encontró a la persona" + CLEAR);
    }

    Persona *getPersona()
    {
        if (!personas.empty())
        {
            return personas.front();
        }
        return nullptr;
    }

    void mostrarFaltaSalir()
    {
        if (personas.empty())
        {
            print(RED + "No hay personas en la fila" + CLEAR);
            return;
        }
    }

    int size()
    {
        return personas.size();
    }

    void run()
    {
        int option;
        do
        {
            showMenu();
            option = input<int>("Option: ");
            switch (option)
            {
            case 1:
            {
                string nombre = input<string>("Nombre: ");
                agregarPersona(new Persona(nombre));
                break;
            }
            case 2:
                salirFila();
                break;
            case 3:
                mostrarFila();
                break;
            case 4:
            {
                string nombre = input<string>("Nombre: ");
                mostrarPosicion(new Persona(nombre));
                break;
            }
            case 5:
            {
                string nombre = input<string>("Nombre: ");
                mostrarTiempo(new Persona(nombre));
                break;
            }
            case 6:
                break;
            default:
                print(RED + "[!] Invalid option" + CLEAR);
            }
        } while (option != 6);
    }

    void clear()
    {
        while (!personas.empty())
        {
            personas.pop();
        }
    }

    void show()
    {
        print("Fila:");
        mostrarFila();
    }

    void showPending()
    {
        print("Falta por salir:");
        mostrarFaltaSalir();
    }

    void showMenu()
    {
        print("1. Agregar persona");
        print("2. Salir de la fila");
        print("3. Mostrar fila");
        print("4. Mostrar posición");
        print("5. Mostrar tiempo");
        print("6. Salir");
    }    
};

int main()
{
    FilaVirtual fila = FilaVirtual();
    fila.run();
    fila.clear();
    return 0;
}
