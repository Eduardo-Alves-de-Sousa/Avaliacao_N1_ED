#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Função para encontrar o nó com a chave mínima (usada na remoção)
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Função para remover um nó da árvore
Node* removeNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = removeNode(root->left, key);
    } else if (key > root->key) {
        root->right = removeNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = removeNode(root->right, temp->key);
    }

    return root;
}

// Função para buscar um nó na árvore
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// Função para imprimir a árvore em ordem
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Função principal para testar a árvore binária de busca
int main() {
    Node* root = NULL;
    int choice, key;

    do {
        // Menu de operações
        printf("\n1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Buscar\n");
        printf("4. Imprimir em ordem\n");
        printf("5. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Inserir um nó na árvore
                printf("Digite a chave para inserir: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;

            case 2:
                // Remover um nó da árvore
                printf("Digite a chave para remover: ");
                scanf("%d", &key);
                root = removeNode(root, key);
                break;

            case 3:
                // Buscar um nó na árvore
                printf("Digite a chave para buscar: ");
                scanf("%d", &key);
                if (search(root, key) != NULL) {
                    printf("Chave %d encontrada na árvore.\n", key);
                } else {
                    printf("Chave %d não encontrada na árvore.\n", key);
                }
                break;

            case 4:
                // Imprimir a árvore em ordem
                printf("Árvore em ordem: \n");
                inorderTraversal(root);
                printf("\n");
                break;

            case 5:
                // Sair do programa
                printf("Encerrando o programa.\n");
                break;

            default:
                // Opção inválida
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (choice != 5);

    return 0;
}
