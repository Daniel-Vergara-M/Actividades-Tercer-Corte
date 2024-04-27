#include "../methods.h"
#include <stack>
#include <string>
#include <queue>

/*
Crear un sistema que permita introducir texto. (Stack)
El sistema debe permitir hacer modificaciones y que el sistema pueda mostrar
la anterior modificación o volver a la misma

Editor de texto
*/

using namespace std;

struct Text
{
    string text;
    Text(string text) : text(text) {}
};

class TextEditor
{
private:
    stack<Text *> texts;
    queue<Text *> undo;

public:
    TextEditor() : texts(), undo(){};
    ~TextEditor()
    {
        while (!texts.empty())
        {
            texts.pop();
        }
        while (!undo.empty())
        {
            undo.pop();
        }
    }

    void addText(Text *text)
    {
        texts.push(text);
    }

    void removeText()
    {
        if (!texts.empty())
        {
            undo.push(texts.top());
            texts.pop();
        }
    }

    void undoText()
    {
        if (!undo.empty())
        {
            texts.push(undo.front());
            undo.pop();
        }
    }

    Text *getText()
    {
        if (!texts.empty())
        {
            return texts.top();
        }
        return nullptr;
    }

    void run()
    {
        string text;
        int option;
        do
        {
            print("1. Add text");
            print("2. Remove text");
            print("3. Undo text");
            print("4. Show text");
            print("5. Exit");
            option = input<int>("Option: ");
            switch (option)
            {
            case 1:
                text = input<string>("Text: ");
                addText(new Text(text));
                break;
            case 2:
                removeText();
                break;
            case 3:
                undoText();
                break;
            case 4:
            {
                Text *text = getText();
                print(text->text);
                break;
            }
            case 5:
                break;
            default:
                print(RED + "[!] Invalid option" + CLEAR);
                break;
            }
        } while (option != 5);
    }

    void clear()
    {
        while (!texts.empty())
        {
            texts.pop();
        }
        while (!undo.empty())
        {
            undo.pop();
        }
    }
};

int main()
{
    TextEditor editor = TextEditor();
    editor.run();
    editor.clear();
    return 0;
}