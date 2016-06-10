#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//define as variaveis de escopo global da app

#define PRODUCT_LIMIT 100
int MENU = 0;
int PRODUCT_CODES[PRODUCT_LIMIT];
int PRODUCT_STOCK[PRODUCT_LIMIT];
float PRODUCT_PRICES[PRODUCT_LIMIT];

int main()
{
    system("cls");
    do {
        //exibe opcoes do menu e atribui o numero da opc na variavel MENU
        menu_choose();
        //executa a ação do menu
        switch(MENU) {
            case 1:
                system("cls");
                add_product();
            break;
        }
    } while (MENU>0 && MENU <=5);

    printf("---------------\n");
    printf(" Opc invalida! \n");
    printf("---------------\n");
}

//opcs do menu
int menu_choose() {
    printf("\n");
    printf("\n");
    printf(" Selecione uma opc no menu: \n\n");
    printf(" Produtos \n");
    printf("--------------------------\n");
    printf(" 1 - Incluir cadastro \n");
    printf(" 2 - Atualizar cadastro \n");
    printf(" 3 - Remover cadastro \n\n");
    printf(" Relatorios \n");
    printf("--------------------------\n");
    printf(" 4 - Todos os produtos \n");
    printf(" 5 - Produto especifico \n");
    printf("\n");
    printf("\n : ");
    scanf("%i",&MENU);
}

//adiciona novo produto
int add_product() {
 //printf("%i",MENU);
    int code;
    printf("\n");
    printf(" Insira o codigo do produto: ");
    scanf("%i",&code);

    //se nao tiver codigo digitado, volta pro menu principal
    if (!code) {
       main();
    }else{
        //verifica se existe codigo de produto cadastrado
        if (verify_product(code)) {
            //pegar preço
            float price = get_price();
            int stock = get_stock();
            if (price && stock) {
                //pega a proxima posição disponivel no vetor
                int position = get_next_position();

                //salva nos vetores
                PRODUCT_CODES[position] = code;
                PRODUCT_PRICES[position] = price;
                PRODUCT_STOCK[position] = stock;

                //saida
                system("cls");
                printf("---------------------------------\n");
                printf(" Produto cadastrado com sucesso! \n");
                printf("---------------------------------\n");
                printf(" Deseja cadastrar outro produto? \n\n 1 - sim | 0 - nao => ");
                printf("\n");

                //pergunta se quer continuar
                int continues = 1;
                scanf("%i",&continues);

                if(continues)
                    add_product();
                else
                    main();
            }else{
                printf("\n");
                printf("------------------------\n");
                printf(" Erro: Valor incorreto! \n");
                printf("------------------------\n");
                add_product(); //reinicia logica de inserção do produto
            }
        }else{
            printf("-----------------------------------\n");
            printf(" Este codigo de produto ja existe! \n");
            printf("-----------------------------------\n");
            add_product();
        }
    }
}

//verifica se existe codigo de produto cadastrado
int verify_product(code) {
    int i;
    //loop pra verificar se existe produto
    for (i=0;i<PRODUCT_LIMIT;i++) {
      //caso existir, retorna 0. equivalente a false
      if (PRODUCT_CODES[i] == code) return 0;
    }
    //caso nao existir, retorna 1. equivalente a true
    return 1;
}

//retorna a proxima posicao disponivel no vetor de codigos
int get_next_position() {
    int i;
    //loop pra pegar proxima posicao disponivel
    for (i=0;i<PRODUCT_LIMIT;i++) {
      if (!PRODUCT_CODES[i]) return i;
    }
    return 0;
}

//pegar preço do produto e verificar se eh valido
int get_price() {
    float price;
    printf("\n");
    printf(" Valor do produto em R$: ");
    scanf("%f",&price);

    if (price > 0)
        return price;
    else
        return 0;
}

//pegar quantidade do stock e verificar se eh valido
int get_stock() {
    int stock;
    printf("\n");
    printf(" Quantidade no estoque: ");
    scanf("%i",&stock);

    if (stock >= 0)
        return stock;
    else
        return 0;
}
