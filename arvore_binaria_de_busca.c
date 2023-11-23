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
    // Aloca dinamicamente na memória para um novo nó
    Node* newNode = (Node*)malloc(sizeof(Node));
    // Inicializa a chave e os ponteiros esquerdo e direito como valores nulos
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
Node* insert(Node* root, int key) {
    if (root == NULL) {
        // Se a árvore estiver vazia, cria um novo nó
        return createNode(key);
    }

    if (key < root->key) {
        // Se a chave for menor que a chave do nó atual, insere à esquerda
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        // Se a chave for maior que a chave do nó atual, insere à direita
        root->right = insert(root->right, key);
    }

    return root;
}

// Função para encontrar o nó com a chave mínima (usada na remoção)
Node* findMin(Node* root) {
    while (root->left != NULL) {
        // Percorre continuamente os nós mais à esquerda até encontrar o último nó
        root = root->left;
    }
    return root;
}

// Função para remover um nó da árvore
Node* removeNode(Node* root, int key) {
    if (root == NULL) {
        // Se a árvore estiver vazia, retorna o nó atual
        return root;
    }

    if (key < root->key) {
        // Se a chave for menor que a chave do nó atual, remove da subárvore esquerda
        root->left = removeNode(root->left, key);
    } else if (key > root->key) {
        // Se a chave for maior que a chave do nó atual, remove da subárvore direita
        root->right = removeNode(root->right, key);
    } else {
        // Se a chave for igual à chave do nó atual, executa a remoção
        if (root->left == NULL) {
            // Se o nó tem apenas um filho ou nenhum filho à esquerda
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Se o nó tem apenas um filho à esquerda
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Se o nó tem dois filhos, encontra o sucessor in-order (mínimo na subárvore à direita)
        Node* temp = findMin(root->right);
        // Copia a chave do sucessor in-order para o nó atual
        root->key = temp->key;
        // Remove o sucessor in-order
        root->right = removeNode(root->right, temp->key);
    }

    return root;
}

// Função para buscar um nó na árvore
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) {
        // Se a árvore estiver vazia ou a chave for encontrada, retorna o nó atual
        return root;
    }

    if (key < root->key) {
        // Se a chave for menor que a chave do nó atual, busca na subárvore esquerda
        return search(root->left, key);
    }

    // Se a chave for maior que a chave do nó atual, busca na subárvore direita
    return search(root->right, key);
}

// Função para imprimir a árvore em ordem
void inorderTraversal(Node* root) {
    if (root != NULL) {
        // Realiza uma travessia em ordem na árvore
        inorderTraversal(root->left);
        // Imprime a chave do nó atual
        printf("%d ", root->key);
        // Continua a travessia na subárvore direita
        inorderTraversal(root->right);
    }
}

// Função para calcular a altura da árvore
int height(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        // Calcula a altura da subárvore esquerda e direita
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        // Retorna a altura máxima entre a subárvore esquerda e direita, acrescida de 1 (altura do nó atual)
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
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
        printf("5. Altura da árvore\n");
        printf("6. Sair\n");
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
                // Calcular a altura da árvore
                printf("Altura da árvore: %d\n", height(root));
                break;

            case 6:
                // Sair do programa
                printf("Encerrando o programa.\n");
                break;

            default:
                // Opção inválida
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (choice != 6);

    return 0;
}
