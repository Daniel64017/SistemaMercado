     Sistema de Supermercado em C

●Descrição do Projeto

Este projeto consiste em um sistema de supermercado simples, desenvolvido em C, que implementa funcionalidades básicas de gerenciamento de produtos e carrinho de compras. O sistema permite cadastrar produtos-1, listar produtos-2, adicionar produtos ao carrinho-3, visualizar o carrinho-4 e finalizar compras-5, utilizando conceitos de structs, arrays e funções.

●Funcionalidades Implementadas:

1. Cadastrar Produto: Permite o cadastro de produtos com código único, nome e preço.


2. Listar Produtos: Exibe todos os produtos cadastrados com seus detalhes (código, nome e preço).


3. Comprar Produto: Adiciona produtos ao carrinho, utilizando o código do produto e definindo a quantidade desejada.


4. Visualizar Carrinho: Exibe o conteúdo do carrinho de compras, mostrando os produtos, quantidades e preços.


5. Fechar Pedido: Calcula o valor total da compra, exibe um resumo detalhado e esvazia o carrinho.


6. Sair do Sistema: Encerra a execução do programa.



●Estrutura do Sistema

O sistema é organizado em funções que dividem as operações principais, como:

menu(): Gerencia o fluxo do programa e apresenta o menu principal.

cadastrarProduto(), listarProdutos(), comprarProduto(): Funções relacionadas ao gerenciamento de produtos e do carrinho.

fecharPedido(): Exibe o valor final da compra e reseta o carrinho.


Além disso, utiliza as seguintes estruturas de dados:

Produto: Struct que armazena o código, nome e preço de um produto.

Carrinho: Struct que armazena o produto e sua quantidade.


●Como Compilar e Executar

-Compilação

Para compilar o programa, utilize o compilador gcc no terminal da seguinte maneira:

gcc sistema_supermercado.c -o supermercado

-Execução

Após a compilação, execute o sistema com o comando:

./supermercado

-Ambiente de Desenvolvimento

Linguagem: C

IDE/Compilador: Visual Studio Code

Sistema Operacional: Compatível com sistemas baseados em Unix como Linux, MacOS e Windows(via compilador adequado)


●Exemplos de Uso

-Cadastro de Produto

Ao selecionar a opção "1" no menu, você poderá cadastrar um novo produto inserindo um código, nome e preço.

-Listagem dos Produtos

Na opção "2" todos os produtos que foram cadastrados com código, nome, preço e quantidade serão listados na tela.

-Adição de Produtos ao Carrinho

Escolha a opção "3" e insira o código do produto desejado, seguido da quantidade a ser comprada.

-Visualizar o Carrinho

Escolha a opção "4" para visualizar todos os produtos que adicionou no carrinho, e o total a pagar.

-Fechamento de Pedido

Após adicionar os produtos ao carrinho, selecione a opção "5" para fechar o pedido, visualizar o total e esvaziar o carrinho.