#include <stdio.h>
#include <stdlib.h>
//define as variaveis de escopo global da app

#define PRODUCT_LIMIT 100
int MENU = 0;
int PRODUCT_CODES[PRODUCT_LIMIT];
int PRODUCT_STOCK[PRODUCT_LIMIT];
float PRODUCT_PRICES[PRODUCT_LIMIT];

int main()
{
    //exibe opcoes do menu e atribui o numero da opc na variavel MENU
    menu_choose();

    //vamos fazer o que tiver que ser feito de acordo com a opc selecionada
    switch(MENU) {
        case 1:
        add_product();
        break;
    }

    system('pause');
    return 0;
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
    printf("\n");
    printf(" Insira o codigo do produto: ");
    scanf("%i",&code);

    //se nao tiver codigo digitado, ou for 0, volta pro menu principal
    if (!code) {
       main();
    }else{
        //verifica se existe codigo de produto cadastrado
        if (verify_product(code)) {
            int continues = 1;
            PRODUCT_CODES[get_code_position()] = code;
            printf("---------------------------------\n");
            printf(" Produto cadastrado com sucesso! \n");
            printf("---------------------------------\n");
            printf(" Deseja cadastrar outro produto? \n\n 1 - sim | 0 - nao => ");
            scanf("%i",&continues);
            printf("\n");

            if(continues)
                add_product();
            else
                main();
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
int get_code_position() {
    int i;
    //loop pra pegar proxima posicao disponivel
    for (i=0;i<PRODUCT_LIMIT;i++) {
      if (!PRODUCT_CODES[i]) return i;
    }
    return 0;
}
