#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//define as variaveis de escopo global da app

#define PRODUCT_LIMIT 100
int MENU = 0; //guarda menu do momento
int PRODUCT_CODES[PRODUCT_LIMIT]; //vetor de codigos
int PRODUCT_STOCK[PRODUCT_LIMIT]; //vetor de estoque
float PRODUCT_PRICES[PRODUCT_LIMIT]; //vetor de preços

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
            case 2:
                system("cls");
                edit_product();
            break;
            case 3:
                system("cls");
                delete_product();
            break;
            default:
                system("exit");
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
    printf(" Outros \n");
    printf("--------------------------\n");
    printf(" 0 - Voltar ao menu principal \n");
    printf("\n");
    scanf("%i",&MENU);
}

//adiciona novo produto
int add_product() {
    int code;
    printf("\n");
    printf(" Insira o codigo do produto: ");
    scanf("%i",&code);

    //se nao tiver codigo digitado, volta pro menu principal
    if (!code) {
       main();
    }else{
        //verifica se ja nao existe codigo de produto cadastrado
        if (!product_exists(code)) {
            //pegar preço
            float price = get_price();
            int stock = get_stock();
            if (price && stock) {
                //pega a proxima posição disponivel no vetor
                int New = next_position();

                //salva nos vetores
                PRODUCT_CODES[New] = code;
                PRODUCT_PRICES[New] = price;
                PRODUCT_STOCK[New] = stock;

                //saida
                system("cls");
                printf("---------------------------------\n");
                printf(" Produto cadastrado com sucesso! \n");
                printf("---------------------------------\n");
                printf(" Deseja cadastrar outro produto? \n\n 1 - sim | 0 - nao => ");

                //pergunta se quer continuar
                int continues = 1;
                scanf("%i",&continues);

                if(continues) {
                    system("cls");
                    add_product();
                }else{
                    main();
                }
            }else{
                printf("\n");
                printf("------------------------\n");
                printf(" Erro: Valor incorreto! \n");
                printf("------------------------\n");
                add_product(); //reinicia logica de inserção do produto
            }
        }else{
            system("cls");
            printf("-----------------------------------\n");
            printf(" Este codigo de produto ja existe! \n");
            printf("-----------------------------------\n");
            add_product();
        }
    }
}

//edita um produto
int edit_product() {
    int code;
    printf("\n");
    printf(" Insira o codigo do produto: ");
    scanf("%i",&code);

    //se nao tiver codigo digitado, volta pro menu principal
    if (!code) {
        main();
    }else{
        //pego a posicao do codigo do produto, caso ele existir
        int exists = get_position(code);
        //se nao existir produto
        if (exists == -1) {
            system("cls");
            printf("------------------------------------\n");
            printf(" Este codigo de produto nao existe! \n");
            printf("------------------------------------\n");
            edit_product(); //recomeço a edição
        }else{
            system("cls");
            printf("----------------------------------------------\n");
            printf(" Produto encontrado, prossiga com a alteracao \n");
            printf("----------------------------------------------\n");
            //produto existe, prosseguir com a alteração
            float price = get_price();
            int stock = get_stock();

            if (price && stock) {
                //salva nos vetores
                PRODUCT_PRICES[exists] = price;
                PRODUCT_STOCK[exists] = stock;

                //saida
                system("cls");
                printf("---------------------------------\n");
                printf(" Produto atualizado com sucesso! \n");
                printf("---------------------------------\n");
                printf(" Deseja alterar outro produto? \n\n 1 - sim | 0 - nao => ");

                //pergunta se quer continuar
                int continues = 1;
                scanf("%i",&continues);

                if(continues) {
                    system("cls");
                    edit_product();
                }else{
                    main();
                }
            }else{
                system("cls");
                printf("--------------------------\n");
                printf(" Erro: valores incorretos \n");
                printf("--------------------------\n");
                edit_product(); //recomeço a edição
            }
        }
    }
}

//deleta um produto
int delete_product() {
    int code;
    printf("\n");
    printf(" Insira o codigo do produto a ser excluido: ");
    scanf("%i",&code);

    //se nao tiver codigo digitado, volta pro menu principal
    if (!code) {
        main();
    }else{
        //pego a posicao do codigo do produto, caso ele existir
        int exists = get_position(code);
        //se nao existir produto
        if (exists == -1) {
            system("cls");
            printf("------------------------------------\n");
            printf(" Este codigo de produto nao existe! \n");
            printf("------------------------------------\n");
            edit_product(); //recomeço a edição
        }else{
            system("cls");
            printf("-----------------------------------------------------------------------\n");
            printf(" Produto encontrado, tem certeza que deseja prosseguir com a exclusao? \n");
            printf("-----------------------------------------------------------------------\n");
            printf(" Deseja alterar outro produto? \n\n 1 - sim | 0 - nao => ");

             //pergunta se quer continuar
             int continues = 0;
             scanf("%i",&continues);
             if(continues) {
                 while (exists < product_total()) {
                    PRODUCT_PRICES[exists] = PRODUCT_PRICES[exists+1];
                    PRODUCT_STOCK[exists] = PRODUCT_STOCK[exists+1];
                    PRODUCT_CODES[exists] = PRODUCT_CODES[exists+1];
                    exists++;
                }

                system("cls");
                printf("--------------------------------\n");
                printf(" Produto excluido com sucesso ! \n");
                printf("--------------------------------\n");
                main();

            }else{
                main(); //retorna ao menu principal
            }
        }
    }
}


//retorna total de produtos cadastrados
int product_total() {
    int i, total = 0;
    for (i=0;i<PRODUCT_LIMIT;i++) {
      if (PRODUCT_CODES[i]) total++;
    }
    return total;
}


//verifica se existe codigo de produto cadastrado
int product_exists(code) {
    int i;
    //loop pra verificar se existe produto
    for (i=0;i<PRODUCT_LIMIT;i++) {

      //caso existir, retorna a posicao da existencia.
      if (PRODUCT_CODES[i] == code) return 1;
    }
    //caso nao existir, retorna 0. equivalente a true
    return 0;
}

//retorna a proxima posicao disponivel no vetor de codigos
int next_position() {
    int i;
    //loop pra pegar proxima posicao disponivel
    for (i=0;i<PRODUCT_LIMIT;i++) {
      if (!PRODUCT_CODES[i]) return i;
    }
    return 0;
}

//retorna a posicao do codigo solicitado
int get_position(code) {
    int i;
    //loop pra pegar proxima posicao disponivel
    for (i=0; i<PRODUCT_LIMIT; i++) {
      if (PRODUCT_CODES[i] == code) return i;
    }
    return -1;
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
