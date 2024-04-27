#include "../methods.h"
#include <stack>
#include <string>
#include <queue>

/**
 Hacer un sistema que permita llevar un orden en las impresiones en una oficina
    (Queue).
 Mostrar lo que imprime y mostrar lo que le falta imprimir.
*/

using namespace std;

struct Documento
{
   string nombre;
   Documento(string nombre) : nombre(nombre) {}
};

class Impresora
{
private:
   queue<Documento *> documentos;

public:
   Impresora() : documentos(){};
   ~Impresora()
   {
      while (!documentos.empty())
      {
         documentos.pop();
      }
   }
   void agregarDocumento(Documento *documento)
   {
      documentos.push(documento);
   }

   void mostrarDocumentos()
   {
      queue<Documento *> temp = documentos;
      int i = 1;
      while (!temp.empty())
      {
         Documento *doc = temp.front();
         print(to_string(i) + ". " + doc->nombre);
         temp.pop();
         i++;
      }
   }

   void imprimirDocumento()
   {
      if (documentos.empty())
      {
         print(RED + "No hay documentos en la lista" + CLEAR);
         return;
      }
      Documento *documento = documentos.front();
      print("Imprimiendo documento: " + documento->nombre);
      documentos.pop();
   }

   void imprimirDocumentos()
   {
      while (!documentos.empty())
      {
         imprimirDocumento();
      }
   }

   Documento *getDocumento()
   {
      if (!documentos.empty())
      {
         return documentos.front();
      }
      return nullptr;
   }

   void mostrarFaltaImprimir()
   {
      if (documentos.empty())
      {
         print(RED + "No hay documentos en la lista" + CLEAR);
         return;
      }
      print(RED + "Falta imprimir:" + CLEAR);
      mostrarDocumentos();
   }

   int size()
   {
      return documentos.size();
   }

   void showMenu()
   {
      print("1. Agregar documento");
      print("2. Imprimir documento");
      print("3. Imprimir todos los documentos");
      print("4. Mostrar documentos");
      print("5. Mostrar documentos pendientes");
      print("6. Salir");
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
            agregarDocumento(new Documento(input<string>("Nombre del documento: ")));
            break;
         case 2:
            imprimirDocumento();
            break;
         case 3:
            imprimirDocumentos();
            break;
         case 4:
            mostrarDocumentos();
            break;
         case 5:
            mostrarFaltaImprimir();
            break;
         case 6:
            break;
         default:
            print(RED + "[!] Invalid option" + CLEAR);
         }
      } while (option != 6);
   }

   void clear()
   {
      while (!documentos.empty())
      {
         documentos.pop();
      }
   }

   void show()
   {
      if (documentos.empty())
      {
         print(RED + "[!] No documents to show" + CLEAR);
         return;
      }
      queue<Documento *> temp = documentos;
      int i = 1;
      while (!temp.empty())
      {
         Documento *doc = temp.front();
         print(to_string(i) + ". " + doc->nombre);
         temp.pop();
         i++;
      }
   }
};

int main()
{
   Impresora impresora = Impresora();
   impresora.run();
   impresora.clear();
   return 0;
}
