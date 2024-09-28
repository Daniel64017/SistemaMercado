Detalhe do código Linha a Linha:



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

// Estrutura para armazenar informações de um produto
typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

// Estrutura para armazenar informações de um item no carrinho
typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

// Prototipação das funções
void menu();
void cadastrarProduto(Produto produtos[], int *numProdutos);
void listarProdutos(Produto produtos[], int numProdutos);
void comprarProduto(Produto produtos[], int numProdutos, Carrinho carrinho[], int *numCarrinho);
void visualizarCarrinho(Carrinho carrinho[], int numCarrinho);
void fecharPedido(Carrinho carrinho[], int *numCarrinho);
int temNoCarrinho(Carrinho carrinho[], int numCarrinho, int codigo);
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo);
void infoProduto(Produto prod);

// Função principal
int main() {
    menu();
    return 0;
}

// Função para exibir o menu e gerenciar o fluxo do programa
void menu() {
    Produto produtos[MAX_PRODUTOS];
    int numProdutos = 0;

    Carrinho carrinho[MAX_CARRINHO];
    int numCarrinho = 0;

    int opcao;

    do {
        printf("\n=== Sistema de Supermercado ===\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("4. Visualizar Carrinho\n");
        printf("5. Fechar Pedido\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch(opcao) {
            case 1:
                cadastrarProduto(produtos, &numProdutos);
                break;
            case 2:
                listarProdutos(produtos, numProdutos);
                break;
            case 3:
                comprarProduto(produtos, numProdutos, carrinho, &numCarrinho);
                break;
            case 4:
                visualizarCarrinho(carrinho, numCarrinho);
                break;
            case 5:
                fecharPedido(carrinho, &numCarrinho);
                break;
            case 6:
                printf("Saindo do sistema. Até logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 6);
}

// Função para cadastrar um novo produto
void cadastrarProduto(Produto produtos[], int *numProdutos) {
    if(*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido. Não é possível cadastrar mais.\n");
        return;
    }

    Produto novoProduto;
    int codigoExiste = 0;

    printf("\n=== Cadastrar Produto ===\n");
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigo);
    getchar(); // Limpar o buffer

    // Verificar se o código já existe
    for(int i = 0; i < *numProdutos; i++) {
        if(produtos[i].codigo == novoProduto.codigo) {
            codigoExiste = 1;
            break;
        }
    }

    if(codigoExiste) {
        printf("Codigo já cadastrado. Tente novamente.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    // Remover o caractere de nova linha
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

    printf("Digite o preco do produto: ");
    scanf("%f", &novoProduto.preco);
    getchar(); // Limpar o buffer

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;

    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar todos os produtos cadastrados
void listarProdutos(Produto produtos[], int numProdutos) {
    if(numProdutos == 0) {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    printf("\n=== Lista de Produtos ===\n");
    printf("%-10s %-30s %-10s\n", "Codigo", "Nome", "Preco");
    printf("-------------------------------------------------------------\n");
    for(int i = 0; i < numProdutos; i++) {
        printf("%-10d %-30s R$ %.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
}

// Função para adicionar um produto ao carrinho
void comprarProduto(Produto produtos[], int numProdutos, Carrinho carrinho[], int *numCarrinho) {
    if(numProdutos == 0) {
        printf("\nNenhum produto cadastrado para compra.\n");
        return;
    }

    int codigo, quantidade;
    printf("\n=== Comprar Produto ===\n");
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &codigo);
    getchar(); // Limpar o buffer

    Produto *prod = pegarProdutoPorCodigo(produtos, numProdutos, codigo);
    if(prod == NULL) {
        printf("Produto nao encontrado. Tente novamente.\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    getchar(); // Limpar o buffer

    if(quantidade <= 0) {
        printf("Quantidade invalida. Tente novamente.\n");
        return;
    }

    int pos = temNoCarrinho(carrinho, *numCarrinho, codigo);
    if(pos != -1) {
        // Produto já está no carrinho, incrementar a quantidade
        carrinho[pos].quantidade += quantidade;
    } else {
        if(*numCarrinho >= MAX_CARRINHO) {
            printf("Carrinho cheio. Não é possivel adicionar mais produtos.\n");
            return;
        }
        // Adicionar novo produto ao carrinho
        carrinho[*numCarrinho].produto = *prod;
        carrinho[*numCarrinho].quantidade = quantidade;
        (*numCarrinho)++;
    }

    printf("Produto adicionado ao carrinho com sucesso!\n");
}

// Função para visualizar os produtos no carrinho
void visualizarCarrinho(Carrinho carrinho[], int numCarrinho) {
    if(numCarrinho == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }

    printf("\n=== Carrinho de Compras ===\n");
    printf("%-10s %-30s %-10s %-10s\n", "Codigo", "Nome", "Quantidade", "Subtotal");
    printf("---------------------------------------------------------------------\n");
    float total = 0.0;
    for(int i = 0; i < numCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        total += subtotal;
        printf("%-10d %-30s %-10d R$ %.2f\n", carrinho[i].produto.codigo, carrinho[i].produto.nome, carrinho[i].quantidade, subtotal);
    }
    printf("---------------------------------------------------------------------\n");
    printf("Total: R$ %.2f\n", total);
}

// Função para fechar o pedido, exibir a fatura e limpar o carrinho
void fecharPedido(Carrinho carrinho[], int *numCarrinho) {
    if(*numCarrinho == 0) {
        printf("\nCarrinho vazio. Adicione produtos antes de fechar o pedido.\n");
        return;
    }

    printf("\n=== Fatura Detalhada ===\n");
    printf("%-10s %-30s %-10s %-10s\n", "Codigo", "Nome", "Quantidade", "Subtotal");
    printf("---------------------------------------------------------------------\n");
    float total = 0.0;
    for(int i = 0; i < *numCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        total += subtotal;
        printf("%-10d %-30s %-10d R$ %.2f\n", carrinho[i].produto.codigo, carrinho[i].produto.nome, carrinho[i].quantidade, subtotal);
    }
    printf("---------------------------------------------------------------------\n");
    printf("Total a pagar: R$ %.2f\n", total);

    // Limpar o carrinho
    *numCarrinho = 0;
    printf("Pedido fechado com sucesso! Carrinho esvaziado.\n");
}

// Função auxiliar para verificar se um produto já está no carrinho
int temNoCarrinho(Carrinho carrinho[], int numCarrinho, int codigo) {
    for(int i = 0; i < numCarrinho; i++) {
        if(carrinho[i].produto.codigo == codigo) {
            return i; // Retorna a posição no carrinho
        }
    }
    return -1; // Não encontrado
}

// Função auxiliar para pegar um produto pelo código
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo) {
    for(int i = 0; i < numProdutos; i++) {
        if(produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;
}

// Função auxiliar para exibir informações de um produto
void infoProduto(Produto prod) {
    printf("Codigo: %d\n", prod.codigo);
    printf("Nome: %s\n", prod.nome);
    printf("Preco: R$ %.2f\n", prod.preco);
}
