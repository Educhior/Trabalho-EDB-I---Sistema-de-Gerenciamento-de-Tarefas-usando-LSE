#include <iostream>
#include <limits>

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

Node* buildNode(Tarefa tarefa) {
    Node* newNode = new Node;
    newNode->tarefa = tarefa;
    newNode->next = nullptr;
    return newNode;
}

void inserirTarefa(Node*& head, Tarefa tarefa) {
    Node* newNode = buildNode(tarefa);
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

    // Procura a primeira tarefa com a prioridade especificada
    while (current != nullptr && current->tarefa.prioridade != prioridade) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Tarefa com prioridade " << prioridade << " nao encontrada!" << endl;
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

void printTarefas(Node* head) { //exibe as informações em ordem de prioridade
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }

    bool encontrouAlguma = false;
    Node* current;
    for (int i = 1; i <= 3; i++) { // Assumindo prioridades 1, 2, 3
        current = head; //resetar o current.
        while (current != nullptr) {
            if (current->tarefa.prioridade == i) {
                encontrouAlguma = true;
                cout << "ID: " << current->tarefa.ID << endl;
                cout << "Descricao: " << current->tarefa.descricao << endl;
                cout << "Prioridade: " << current->tarefa.prioridade << endl;
                cout << "=======================================" << endl;
            }
            current = current->next;
        }
    }
    if (!encontrouAlguma && head != nullptr) { // Se a lista não estiver vazia mas nada foi impresso (ex: prioridades erradas)
        cout << "Nenhuma tarefa para exibir com as prioridades definidas (1-3)." << endl;
    }
}

void buscarTarefas(Node* head, int ID) { //exibe as informações de uma tarefa pelo ID
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }
    Node* current = head;
    bool encontrado = false; // Flag para verificar se a tarefa foi encontrada

    while (current != nullptr) {
        if (current->tarefa.ID == ID) {
            cout << "ID: " << current->tarefa.ID << endl;
            cout << "Descricao: " << current->tarefa.descricao << endl;
            cout << "Prioridade: " << current->tarefa.prioridade << endl;
            cout << "=======================================" << endl;
            encontrado = true;
            break; // Interrompe o loop assim que a tarefa é encontrada
        }
        current = current->next;
    }

    if (!encontrado) { // Se não encontrou após percorrer a lista
        cout << "Tarefa com ID " << ID << " nao encontrada!" << endl;
    }
}

// Nova função para liberar toda a memória da lista
void liberarLista(Node*& head) {
    Node* current = head;
    Node* nextNode = nullptr;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr; // Garante que o ponteiro head não aponte para memória liberada
}

int main() {
    Node* listaTarefa = nullptr;
    int opcao;

    do {
        cout << "=======================================" << endl;
        cout << "            Menu de Tarefas" << endl;
        cout << "=======================================" << endl;
        cout << "1. Inserir Tarefa" << endl;
        cout << "2. Remover Tarefa por ID" << endl;
        cout << "3. Remover Tarefa por Prioridade" << endl;
        cout << "4. Exibir Tarefas" << endl;
        cout << "5. Buscar Tarefa por ID" << endl;
        cout << "0. Sair" << endl;
        cout << "=======================================" << endl;
        cout << "Escolha uma opcao: ";

        while (!(cin >> opcao)) { // Validação de entrada para opção do menu
            cout << "Entrada invalida. Por favor, digite um numero: ";
            cin.clear(); // Limpa flags de erro do cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta entrada incorreta
        }

        switch (opcao) {
            case 1: {
                Tarefa tarefa;
                cout << "Digite o ID da tarefa: ";
                while (!(cin >> tarefa.ID)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar o buffer do cin (importante após 'cin >>')

                cout << "Digite a descricao da tarefa: ";
                cin.getline(tarefa.descricao, 101);

                cout << "Digite a prioridade da tarefa (1-Alta, 2-Media, 3-Baixa): ";
                while (!(cin >> tarefa.prioridade) || tarefa.prioridade < 1 || tarefa.prioridade > 3) {
                    cout << "Prioridade invalida. Digite um valor entre 1 e 3: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar o buffer após a leitura da prioridade

                inserirTarefa(listaTarefa, tarefa);
                break;
            }
            case 2: {
                int id;
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
                cout << "Digite o ID da tarefa a ser buscada: ";
                while (!(cin >> id)) {
                    cout << "ID invalido. Por favor, digite um numero inteiro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                buscarTarefas(listaTarefa, id);
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                liberarLista(listaTarefa); // Libera a memória antes de sair
                cout << "Memoria liberada. Programa encerrado." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}