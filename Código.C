#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 50
#define MAX_CARRINHO 50

typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

void menu();
void cadastrarProduto(Produto produtos[], int *numProdutos);
void listarProdutos(Produto produtos[], int numProdutos);
void comprarProduto(Produto produtos[], int numProdutos, Carrinho carrinho[], int *numCarrinho);
void visualizarCarrinho(Carrinho carrinho[], int numCarrinho);
void fecharPedido(Carrinho carrinho[], int *numCarrinho);
int temNoCarrinho(Carrinho carrinho[], int numCarrinho, int codigo);
Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo);
void infoProduto(Produto prod);

int main() {
    menu();
    return 0;
}

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
        getchar();

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
                printf("Saindo do sistema. Ate logo!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(opcao != 6);
}

void cadastrarProduto(Produto produtos[], int *numProdutos) {
    if(*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido. Nao e possivel cadastrar mais.\n");
        return;
    }

    Produto novoProduto;
    int codigoExiste = 0;

    printf("\n=== Cadastrar Produto ===\n");
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoProduto.codigo);
    getchar();

    for(int i = 0; i < *numProdutos; i++) {
        if(produtos[i].codigo == novoProduto.codigo) {
            codigoExiste = 1;
            break;
        }
    }

    if(codigoExiste) {
        printf("Codigo ja cadastrado. Tente novamente.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = '\0';

    printf("Digite o preco do produto: ");
    scanf("%f", &novoProduto.preco);
    getchar();

    produtos[*numProdutos] = novoProduto;
    (*numProdutos)++;

    printf("Produto cadastrado com sucesso!\n");
}

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

void comprarProduto(Produto produtos[], int numProdutos, Carrinho carrinho[], int *numCarrinho) {
    if(numProdutos == 0) {
        printf("\nNenhum produto cadastrado para compra.\n");
        return;
    }

    int codigo, quantidade;
    printf("\n=== Comprar Produto ===\n");
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%d", &codigo);
    getchar();

    Produto *prod = pegarProdutoPorCodigo(produtos, numProdutos, codigo);
    if(prod == NULL) {
        printf("Produto nao encontrado. Tente novamente.\n");
        return;
    }

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);
    getchar();

    if(quantidade <= 0) {
        printf("Quantidade invalida. Tente novamente.\n");
        return;
    }

    int pos = temNoCarrinho(carrinho, *numCarrinho, codigo);
    if(pos != -1) {
        carrinho[pos].quantidade += quantidade;
    } else {
        if(*numCarrinho >= MAX_CARRINHO) {
            printf("Carrinho cheio. Nao e possivel adicionar mais produtos.\n");
            return;
        }
        carrinho[*numCarrinho].produto = *prod;
        carrinho[*numCarrinho].quantidade = quantidade;
        (*numCarrinho)++;
    }

    printf("Produto adicionado ao carrinho!\n");
}

void visualizarCarrinho(Carrinho carrinho[], int numCarrinho) {
    if(numCarrinho == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }

    printf("\n=== Carrinho de Compras ===\n");
    printf("%-10s %-30s %-10s %-10s\n", "Codigo", "Nome", "Preco", "Quantidade");
    printf("---------------------------------------------------------------------\n");
    for(int i = 0; i < numCarrinho; i++) {
        printf("%-10d %-30s R$ %-10.2f %-10d\n", carrinho[i].produto.codigo, carrinho[i].produto.nome, carrinho[i].produto.preco, carrinho[i].quantidade);
    }
}

void fecharPedido(Carrinho carrinho[], int *numCarrinho) {
    if(*numCarrinho == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }

    float total = 0.0;

    printf("\n=== Fechamento do Pedido ===\n");
    printf("%-10s %-30s %-10s %-10s %-10s\n", "Codigo", "Nome", "Preco", "Quantidade", "Subtotal");
    printf("---------------------------------------------------------------------------\n");
    for(int i = 0; i < *numCarrinho; i++) {
        float subtotal = carrinho[i].produto.preco * carrinho[i].quantidade;
        printf("%-10d %-30s R$ %-10.2f %-10d R$ %-10.2f\n", carrinho[i].produto.codigo, carrinho[i].produto.nome, carrinho[i].produto.preco, carrinho[i].quantidade, subtotal);
        total += subtotal;
    }

    printf("---------------------------------------------------------------------------\n");
    printf("Total da compra: R$ %.2f\n", total);

    *numCarrinho = 0;
    printf("Pedido fechado com sucesso!\n");
}

int temNoCarrinho(Carrinho carrinho[], int numCarrinho, int codigo) {
    for(int i = 0; i < numCarrinho; i++) {
        if(carrinho[i].produto.codigo == codigo) {
            return i;
        }
    }
    return -1;
}

Produto* pegarProdutoPorCodigo(Produto produtos[], int numProdutos, int codigo) {
    for(int i = 0; i < numProdutos; i++) {
        if(produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;
}

void infoProduto(Produto prod) {
    printf("%-10d %-30s R$ %.2f\n", prod.codigo, prod.nome, prod.preco);
}