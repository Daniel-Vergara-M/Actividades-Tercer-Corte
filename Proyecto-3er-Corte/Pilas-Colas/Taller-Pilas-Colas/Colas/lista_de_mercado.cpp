#include "../methods.h"
#include <stack>
#include <string>
#include <queue>

/*
Crear una lista para hacer mercados (Queue).
El sistema debe permitir ver la lista e ir sacando los elementos del mercado
desde el primero hasta el último.
*/

using namespace std;

struct Producto
{
    string nombre;
    Producto(string nombre) : nombre(nombre) {}
};

class ListaMercado
{
private:
    queue<Producto *> productos;

public:
    ListaMercado() : productos(){};
    ~ListaMercado()
    {
        while (!productos.empty())
        {
            productos.pop();
        }
    }
    void agregarProducto(Producto *producto)
    {
        productos.push(producto);
    }

    void mostrarLista()
    {
        queue<Producto *> temp = productos;
        int i = 1;
        while (!temp.empty())
        {
            print(to_string(i) + ". " + temp.front()->nombre);
            temp.pop();
            i++;
        }
    }

    void sacarProducto()
    {
        if (productos.empty())
        {
            print(RED + "No hay productos en la lista" + CLEAR);
            return;
        }
        Producto *producto = productos.front();
        print("Sacando producto: " + producto->nombre);
        productos.pop();
    }

    void sacarProductos()
    {
        while (!productos.empty())
        {
            sacarProducto();
        }
    }

    Producto *getProducto()
    {
        if (!productos.empty())
        {
            return productos.front();
        }
        return nullptr;
    }

    int getSize()
    {
        return productos.size();
    }

    bool isEmpty()
    {
        return productos.empty();
    }
};

int main()
{
    ListaMercado lista = ListaMercado();
    int option ;
    do
    {
        print("1. Agregar producto");
        print("2. Mostrar lista");
        print("3. Sacar producto");
        print("4. Sacar todos los productos");
        print("5. Salir");
        option = input<int>("Opción: ");
        switch (option)
        {
        case 1:
        {
            string nombre;
            cout << "Nombre del producto: ";
            cin >> nombre;
            Producto *producto = new Producto(nombre);
            lista.agregarProducto(producto);
            break;
        }
        case 2:
            lista.mostrarLista();
            break;
        case 3:
            lista.sacarProducto();
            break;
        case 4:
            lista.sacarProductos();
            break;
        case 5:
            break;
        default:
            print(RED + "[!] Invalid option" + CLEAR);
        }
    } while (option != 5);
    return 0;
}