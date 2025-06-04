#include <iostream>
#include <limits>
#include <string.h>

using namespace std;

struct Tarefa {
    int ID;
    char descricao[101];
    int prioridade;
};

struct Node {
    Tarefa tarefa;
    Node* next;
};

// Função auxiliar para verificar se um ID já existe na lista
bool idExiste(Node* head, int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->tarefa.ID == id) {
            return true; // ID encontrado
        }
        current = current->next;
    }
    return false; // ID não encontrado
}

Node* buildNode(Tarefa tarefa) {
    Node* newNode = new Node;
    newNode->tarefa = tarefa;
    newNode->next = nullptr;
    return newNode;
}

void inserirTarefa(Node*& head, Tarefa novaTarefa) {
    // Verifica se o ID da nova tarefa já existe
    if (idExiste(head, novaTarefa.ID)) {
        cout << "Aviso: Ja existe uma tarefa com o ID " << novaTarefa.ID << ". Nao foi possivel adicionar." << endl;
        return;
    }

    Node* newNode = buildNode(novaTarefa);
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    cout << "Tarefa inserida com sucesso!" << endl;
}

void removerTarefaID(Node*& head, int id) {
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr && current->tarefa.ID != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Tarefa com ID " << id << " nao encontrada!" << endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next; // Remove o primeiro nó
    } else {
        previous->next = current->next; // Remove o nó do meio ou final
    }

    delete current; // Libera a memória do nó removido
    cout << "Tarefa removida com sucesso!" << endl;
}

void removerTarefaPrioridade(Node*& head, int prioridade) {
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;
    bool removido = false; // Flag para controlar se alguma tarefa foi removida

    Node* tempHead = head; // Usamos um ponteiro temporário para iterar e modificar a lista
    previous = nullptr; // Reinicia previous para a busca
    current = tempHead;

    while (current != nullptr) {
        if (current->tarefa.prioridade == prioridade) {
            if (previous == nullptr) { // Removendo o primeiro nó da lista (ou da sub-lista após remoções)
                head = current->next;
                delete current;
                current = head; // Atualiza current para o novo head
            } else {
                previous->next = current->next;
                delete current;
                current = previous->next; // Atualiza current para o nó após o removido
            }
            cout << "Tarefa com prioridade " << prioridade << " removida com sucesso!" << endl;
            removido = true;
            return;
        } else {
            previous = current;
            current = current->next;
        }
    }


    if (!removido) {
        cout << "Nenhuma tarefa com prioridade " << prioridade << " encontrada!" << endl;
    }
}

void printTarefas(Node* head) { //exibe as informações em ordem de prioridade
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    bool encontrouAlguma = false;
    Node* current;
    cout << endl;
    cout << "=======================================" << endl;
    cout << "        Tarefas por Prioridade" << endl;
    cout << "=======================================" << endl;
    for (int i = 1; i <= 3; i++) { // Assumindo prioridades 1 (Alta), 2 (Media), 3 (Baixa)
        current = head; 
        bool prioridadeHeaderImpresso = false;
        while (current != nullptr) {
            if (current->tarefa.prioridade == i) {
                if(!prioridadeHeaderImpresso){
                    cout << "--- Prioridade " << i << " ---" << endl;
                    prioridadeHeaderImpresso = true;
                }
                encontrouAlguma = true;
                cout << "  ID: " << current->tarefa.ID << endl;
                cout << "  Descricao: " << current->tarefa.descricao << endl;
                // cout << "  Prioridade: " << current->tarefa.prioridade << endl; // Já está no header da prioridade
                cout << "  -------------------------------------" << endl;
            }
            current = current->next;
        }
    }
     cout << "=======================================" << endl;
    if (!encontrouAlguma && head != nullptr) { 
        cout << "Nenhuma tarefa para exibir." << endl;
         cout << "=======================================" << endl;
    }
}

void buscarTarefas(Node* head, int ID) { //exibe as informações de uma tarefa pelo ID
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }
    Node* current = head;
    bool encontrado = false; 

    while (current != nullptr) {
        if (current->tarefa.ID == ID) {
            cout << endl;
            cout << "=======================================" << endl;
            cout << "          Tarefa Encontrada" << endl;
            cout << "=======================================" << endl;
            cout << "ID: " << current->tarefa.ID << endl;
            cout << "Descricao: " << current->tarefa.descricao << endl;
            cout << "Prioridade: " << current->tarefa.prioridade << endl;
            cout << "=======================================" << endl;
            encontrado = true;
            break; 
        }
        current = current->next;
    }

    if (!encontrado) { 
        cout << "Tarefa com ID " << ID << " nao encontrada!" << endl;
    }
}

void liberarLista(Node*& head) {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr; 
}

int main() {
    Node* listaTarefa = nullptr;
    int opcao;

    do {
        cout << endl;
        cout << "=======================================" << endl;
        cout << "            Menu de Tarefas" << endl;
        cout << "=======================================" << endl;
        cout << "1. Inserir Tarefa" << endl;
        cout << "2. Remover Tarefa por ID" << endl;
        cout << "3. Remover Tarefa por Prioridade (primeira ocorrencia)" << endl;
        cout << "4. Exibir Tarefas (por prioridade)" << endl;
        cout << "5. Buscar Tarefa por ID" << endl;
        cout << "0. Sair" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma opcao: ";

        while (!(cin >> opcao)) { 
            cout << "Entrada invalida. Por favor, digite um numero: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar o buffer após ler a opção

        switch (opcao) {
            case 1: {
                Tarefa tarefa;
                cout << "Digite o ID da tarefa: ";
                while (!(cin >> tarefa.ID)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                cout << "Digite a descricao da tarefa (max 100 caracteres): ";
                cin.getline(tarefa.descricao, 101);
                // Validar se a string não ficou vazia, se necessário
                if (strlen(tarefa.descricao) == 0) {
                    cout << "Descricao nao pode ser vazia. Tarefa nao inserida." << endl;
                    break; 
                }


                cout << "Digite a prioridade da tarefa (1-Alta, 2-Media, 3-Baixa): ";
                while (!(cin >> tarefa.prioridade) || tarefa.prioridade < 1 || tarefa.prioridade > 3) {
                    cout << "Prioridade invalida. Digite um valor entre 1 e 3: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                inserirTarefa(listaTarefa, tarefa);
                break;
            }
            case 2: {
                int id;
                if (listaTarefa == nullptr) {
                    cout << "Lista vazia! Nao ha tarefas para remover." << endl;
                    break;
                }
                cout << "Digite o ID da tarefa a ser removida: ";
                while (!(cin >> id)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                removerTarefaID(listaTarefa, id);
                break;
            }
            case 3: {
                int prioridade;
                 if (listaTarefa == nullptr) {
                    cout << "Lista vazia! Nao ha tarefas para remover." << endl;
                    break;
                }
                cout << "Digite a prioridade da tarefa a ser removida (1-3): ";
                while (!(cin >> prioridade) || prioridade < 1 || prioridade > 3) {
                    cout << "Prioridade invalida. Digite um valor entre 1 e 3: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                removerTarefaPrioridade(listaTarefa, prioridade);
                break;
            }
            case 4:
                printTarefas(listaTarefa);
                break;
            case 5: {
                int id;
                if (listaTarefa == nullptr) {
                    cout << "Lista vazia! Nao ha tarefas para buscar." << endl;
                    break;
                }
                cout << "Digite o ID da tarefa a ser buscada: ";
                while (!(cin >> id)) {
                    cout << "ID invalido. Por favor, digite um nuqmero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                buscarTarefas(listaTarefa, id);
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                liberarLista(listaTarefa); 
                cout << "Memoria liberada. Programa encerrado." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0; 
}
