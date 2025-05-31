#include <iostream>

using namespace std;

struct Tarefa {
    int ID;
    char descricao[101];
    int prioridade;
};

struct Node{
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
    if (head == nullptr){
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

// Código só para testar 
void printTarefas(Node* head) {
    if (head == nullptr) {
        cout << "Lista vazia!" << endl;
        return;
    }
    
    Node* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->tarefa.ID << endl;
        cout << "Descricao: " << current->tarefa.descricao << endl;
        cout << "Prioridade: " << current->tarefa.prioridade << endl;
        cout << "=======================================" << endl;
        current = current->next;
    }
}

int main() {
    Node* listaTarefa = nullptr;
    Tarefa tarefa1 = {1, "Estudar C++", 2};
    Tarefa tarefa2 = {2, "Fazer compras", 1};
    Tarefa tarefa3 = {3, "Limpar a casa", 3};

    printTarefas(listaTarefa);
    
    inserirTarefa(listaTarefa, tarefa1);
    inserirTarefa(listaTarefa, tarefa2);

    printTarefas(listaTarefa);

    
    removerTarefaID(listaTarefa, 1);
    removerTarefaPrioridade(listaTarefa, 1);

    printTarefas(listaTarefa);
    
    return 0;
}