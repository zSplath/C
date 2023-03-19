#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define true 1
#define false -1
#define carrinho 10

typedef struct
{
    char nome[100];
    char pront[11];
}
usuario;

typedef struct
{
   char Nome[100];
   char Desc[100];
   int  peso;
   float  preco;
}
REGISTRO;

typedef struct ELEMENTO
{
	REGISTRO reg;
	struct ELEMENTO * PROX;
}
ELEMENTO;

typedef ELEMENTO * PONT;

typedef struct
{
	PONT topo;
}
PILHA;

typedef struct
{
   PONT inicio;
   PONT fim;
}
fila;

int ordena();

PILHA gondola[11];
fila esteira;

int cadastrar ()
{
    int i;
    usuario padrao[29] =
    {
        {"Domingos Lucas Latorre de Oliveira",  "CJ146456"},
        {"Leandro Pinto Santana",               "CP220383"},
        {"Rodrigo Ribeiro de Oliveira",         "RG134168"},
        {"Andre Luiz da Silva",                 "SP030028"},
        {"Claudia Miyuki Werhmuller",           "SP030041"},
        {"Claudete de Oliveira Alves",          "SP03020X"},
        {"Francisco Verissimo Luciano",         "SP030247"},
        {"Luk Cho Man",                         "SP060380"},
        {"Ivan Francolin Martinez",             "SP060835"},
        {"Joao Vianei Tamanini",                "SP060914"},
        {"Jose Oscar Machado Alexandre",        "SP070038"},
        {"Jose Braz de Araujo",                 "SP070385"},
        {"Paulo Roberto de Abreu",              "SP070816"},
        {"Eurides Balbino da Silva",            "SP07102X"},
        {"Domingos Bernardo Gomes Santos",      "SP090888"},
        {"Andre Evandro Lourenco",              "SP100092"},
        {"Miguel Angelo Tancredi Molina",       "SP102763"},
        {"Antonio Airton Palladino",            "SP112197"},
        {"Luis Fernando Aires Branco Menegueti","SP145385"},
        {"Antonio Ferreira Viana",              "SP200827"},
        {"Leonardo Bertholdo",                  "SP204973"},
        {"Marcelo Tavares de Santana",          "SP20500X"},
        {"Daniel Marques Gomes de Morais",      "SP220097"},
        {"Alexandre Beletti Ferreira",          "SP226117"},
        {"Vladimir Camelo Pinto",               "SP240291"},
        {"Leonardo Andrade Motta de Lima",      "SP24031X"},
        {"Aldo Marcelo Paim",                   "SP240497"},
        {"Cesar Lopes Fernandes",               "SP890534"},
        {"Josceli Maria Tenorio",               "SZ124382"}
    };
    FILE * cadastro = fopen("USUARIOS.DAT", "r");
    if (cadastro == NULL)
    {
        fclose(cadastro);
        cadastro = fopen("USUARIOS.DAT", "a");
        if (cadastro == NULL)
        printf ("\n Erro ao abrir USUARIOS.DAT");
        else
        for ( i = 0; i < 29; i++ )
        {
            fwrite ( &padrao[i], sizeof(padrao[i]), 1, cadastro );
            if (ferror(cadastro))
            {
                printf ("\n Erro ao Cadastrar na linha %i", ++i);
                getch();
                i = 1337;
            }
        }
        fclose(cadastro);
        ordena();
    }
    else
    fclose(cadastro);
    if (i<1337) return 1;
    return -1;
}

int lerdat ()
{
    usuario reg;
    FILE * Arq;
    Arq = fopen("USUARIOS.DAT", "r");
    if ( Arq == NULL )
    {
    	return -1;
	}
	system ("cls");
	system("mode 90,40");
    while ( !feof(Arq) )
    {
        fread ( &reg , sizeof(reg), 1, Arq );
        if ( !feof(Arq) )
           printf("\n %-60s | %-11s ", reg.nome, reg.pront);
	}
    fclose (Arq);
    getch();
    return 1;
}

int contador ()
{
    int counter=0;
    usuario reg;
    FILE * Arq;
    Arq = fopen("USUARIOS.DAT", "r");
    if ( Arq == NULL )
    {
    	return -1;
	}
    while ( !feof(Arq) )
    {
        fread ( &reg , sizeof(reg), 1, Arq );
        if ( !feof(Arq) )
        {
           counter++;
		}
	}
    fclose (Arq);
    return counter;
}

void troca (usuario *A, usuario *B)
{
    usuario aux = *A;
    *A = *B;
    *B = aux;
}

void bubble_sort(usuario * linha, int tamanho)
{
    int i, j;
    for ( j = 0; j<tamanho-1; j++)
        for ( i = 0; i<tamanho-1-j; i++)
            if ( strcmp (linha[i].nome, linha[i+1].nome) > 0)
                troca(&linha[i], &linha[i+1]);
}

int ordena()
{
    int i, total;
    usuario *leitura;
    FILE *registro;

    total = contador();
    leitura = (usuario*) malloc(total * sizeof(usuario));

    registro = fopen("USUARIOS.DAT", "r");

    if (registro == NULL)
    {
        printf ("\n Erro ao abrir USUARIOS.DAT");
        getch();
        exit(0);
    }
    i = 0;
    while (!feof(registro))
	{
		fread (&leitura[i], sizeof(leitura[i]), 1, registro);
		if (ferror(registro))
		{
			printf ("\n Erro ao ler USUARIOS.DAT");
			getch();
			exit(0);
		}
		i++;
	}
	fclose(registro);

	bubble_sort(leitura, total);

	registro = fopen("USUARIOS.DAT", "w");
    if (registro == NULL)
    {
        printf ("\n Erro ao abrir USUARIOS.DAT para reescrever");
        getch();
        return -1;
    }
    for ( i = 0; i < total; i++ )
    {
        fwrite ( &leitura[i], sizeof(leitura[i]), 1, registro );
        if (ferror(registro))
        {
            printf ("\n Erro ao Cadastrar na linha %i", ++i);
            getch();
            i = total + 2;
        }
    }
    /** if (i!=total+2) printf(" deu"); getch(); */
    fclose(registro);
    return total;
}

int busca_binaria (usuario login)
{
    int i, ini, fim, meio, nome;
    usuario *leitura;
    FILE *registro;

    ini = 0;
    fim = contador()-1;

    leitura = (usuario*) malloc((fim+1) * sizeof(usuario));

    if (leitura == NULL)
    {
        printf ("\n Erro ao alocar memória");
        getch();
        exit(0);
    }

    registro = fopen("USUARIOS.DAT", "r");

    if (registro == NULL)
    {
        printf ("\n Erro ao abrir USUARIOS.DAT");
        getch();
        exit(0);
    }

    i = 0;
    while (!feof(registro))
	{
		fread (&leitura[i], sizeof(leitura[i]), 1, registro);
		if (ferror(registro))
		{
			printf ("\n Erro ao ler USUARIOS.DAT");
			getch();
			exit(0);
		}
		i++;
	}
	fclose(registro);

    while (ini<=fim)
    {
        meio=(ini+fim)/2;
        nome = strcmp(login.nome, leitura[meio].nome);
        if(nome==0)
        {
            if ( strcmp(login.pront, leitura[meio].pront) == 0 )
                 return 1;
            else return 0;
        }
        if(nome<0)
            fim = meio-1;
        else
            ini = meio+1;
    }
    return -1;
}

void inicializarPilhas (void)
{
  int i;
  for (i=0; i<10; i++)
    gondola[i].topo = NULL;
}

int tamanho (int numpil)
{
   PONT end = gondola[numpil].topo;
   int tam = 0;
   while (end != NULL)
   {
      tam++;
      end = end->PROX;
   }
   return tam;
}

void exibirPilhas (void)
{
   PONT end;
   int i;
   for (i = 0; i < 10; i++)
   {
       system ("cls");
       end = gondola[i].topo;
       printf(" Pilha [%i]: Nome - Descrição - Peso - Preço\n", i+1);
       while (end != NULL)
       {
            printf("\n[%s - %s - %i g - %.2f Reais]",
            end->reg.Nome, end->reg.Desc, end->reg.peso, end->reg.preco);
            end = end->PROX;
       }
       getch();
   }
}

REGISTRO oqueInserir (void)
{
    REGISTRO r;
    system("cls");
	printf("\n Nome do Produto: "); fflush (stdin); gets(r.Nome);
	printf("\n Descrição: ");       fflush (stdin); gets(r.Desc);
	printf("\n Peso  (g): ");       fflush (stdin); scanf("%i", &r.peso);
	printf("\n Preço (Reais): ");   fflush (stdin); scanf("%f", &r.preco);
	return r;
}

int inserirPilha(int numpil)
{
   PONT novo;
   int quantidade;

   quantidade = tamanho(numpil);

   if (quantidade > 4)
   {
       system("cls");
       printf("\n\t\t pilha %i lotada \n\t\t com %i elementos", numpil+1, quantidade);
       getch();
       return false;
   }

   novo  = (PONT) malloc(sizeof(ELEMENTO));
   if (novo==NULL)
   {
      printf ("\n Erro ao alocar memória para novo elemento.");
      printf ("\n Não foi possível inserir na pilha!");
      getch();
      return false;
   }
   novo->reg  = oqueInserir();
   novo->PROX = gondola[numpil].topo;
   gondola[numpil].topo = novo;
   return true;
}

int inserirPilhaPadrao(int numpil, REGISTRO padrao)
{
   PONT novo;
   int quantidade;

   quantidade = tamanho(numpil);

   if (quantidade > 4)
   {
       return false;
   }

   novo  = (PONT) malloc(sizeof(ELEMENTO));

   novo->reg  = padrao;
   novo->PROX = gondola[numpil].topo;
   gondola[numpil].topo = novo;
   return true;
}

void cadastrogondolas (void)
{
    REGISTRO produtos[13] =
    {
        {"Picanha",         "Carne bovina",                 500, 20},
        {"Frango",          "Carne de Frango",              500, 15},
        {"Linguiça",        "Carne Suina",                  400, 10},

        {"Alho",            "Usado como tempero",           120,  2},

        {"Alpino",          "Chocolate da Nestle",          92,   5},
        {"Diamante Negro",  "Chocolate da Lacta",           90,   4},

        {"Ruffles",         "Salgadinho sabor churrasco",   57,   6},
        {"Fandangos",       "Carne bovina",                 90,   4},
        {"Passatempo",      "Biscoito",                     80,   3},
        {"Pringles",        "Salgadinho",                   114, 10},

        {"Pão de Queijo",   "Congelado para uso no forno",  400, 12},

        {"Queijo prato",    "Queijo em barra",              200, 15},
        {"Mussarela",       "Queijo Mussarela Fatiado",     100,  8}
    };

    inserirPilhaPadrao(0, produtos[0]);
    inserirPilhaPadrao(0, produtos[1]);
    inserirPilhaPadrao(0, produtos[2]);

    inserirPilhaPadrao(1, produtos[3]);

    inserirPilhaPadrao(2, produtos[4]);
    inserirPilhaPadrao(2, produtos[5]);

    inserirPilhaPadrao(4, produtos[6]);
    inserirPilhaPadrao(4, produtos[7]);
    inserirPilhaPadrao(4, produtos[8]);
    inserirPilhaPadrao(4, produtos[9]);

    inserirPilhaPadrao(6, produtos[10]);

    inserirPilhaPadrao(8, produtos[11]);
    inserirPilhaPadrao(8, produtos[12]);
}

int excluirElemPilha(int numpil, REGISTRO* reg)
{
   PONT apagar;
   if (gondola[numpil].topo == NULL)
      return false;
   *reg = gondola[numpil].topo->reg;
   apagar = gondola[numpil].topo;
   gondola[numpil].topo = apagar->PROX;
   free(apagar);
   return true;
}

void exibircarrinho (void)
{
    PONT end;

    system ("cls");
    end = gondola[carrinho].topo;
    printf(" Carrinho: Nome - Descrição - Peso - Preço\n");
    while (end != NULL)
    {
        printf("\n    [%s - %s - %i g - %.2f Reais]",
        end->reg.Nome, end->reg.Desc, end->reg.peso, end->reg.preco);
        end = end->PROX;
    }
    getch();
}

int inserirCarrinho(int numpil)
{
   PONT novo;
   int quantidade;

   quantidade = tamanho(numpil);

   if (quantidade == 0)
   {
       system("cls");
       printf("\n\t\t Gôndola %i Vazia", numpil+1);
       getch();
       return false;
   }

   novo  = (PONT) malloc(sizeof(ELEMENTO));
   if (novo==NULL)
   {
      printf ("\n Erro ao alocar memória para novo elemento.");
      printf ("\n Não foi possível inserir na pilha!");
      getch();
      return false;
   }
   excluirElemPilha(numpil, &novo->reg);
   novo->PROX = gondola[carrinho].topo;
   gondola[carrinho].topo = novo;
   exibircarrinho();
   return true;
}

void abastecer ()
{
    int numpil;
    char opc;
    REGISTRO excluido;
    while (true)
    {
        do
        {
            system("cls");
            printf("____________________________________________________________\n\n");
            printf("                          Abastecer                         \n");
            printf("____________________________________________________________\n\n");
            printf("                    1. Exibir                               \n");
            printf("                    2. Colocar no Carrinho                  \n");
            printf("                    3. Tirar do Carrinho                    \n");
            printf("                    4. Ver Carrinho                         \n");
            printf("                    0. Voltar                               \n");
            printf("\n");
            printf("                    Opção desejada: ");
            opc = getche();
            if (opc != '0' && opc != '1' && opc != '2' && opc != '3' && opc != '4')
            {
                system("cls");
                printf("\n\n\n\n\n [%c] não é uma opção válida", opc);
                Sleep(800);
            }
        } while(opc != '0' && opc != '1' && opc != '2' && opc != '3' && opc != '4');
        if (opc == '1')
            exibirPilhas();
        if (opc == '2')
        {
            system("cls");
            do {
            printf("\n\n Numero da pilha: ");
            fflush(stdin); scanf("%i", &numpil);
            if (numpil < 1 || numpil > 10)
                printf("\n Numero inválido \n Deve estar entre 1 e 10");
            } while (numpil < 1 || numpil > 10);
            numpil--;
            inserirCarrinho(numpil);
        }
        if (opc == '3')
        {
            excluirElemPilha(carrinho,&excluido);
            system("cls");
            printf("\n\n [%s - %s - %i g - %.2f Reais] Foi retirado",
            excluido.Nome, excluido.Desc, excluido.peso, excluido.preco);
            getch();
        }
        if (opc == '4')
            exibircarrinho();
        if (opc == '0')
            return;
    }
}

void abastecermaster()
{
    int numpil;
    char opc;
    REGISTRO excluido;
    while (true)
    {
        do
        {
            system("cls");
            printf("____________________________________________________________\n\n");
            printf("                          Abastecer                         \n");
            printf("____________________________________________________________\n\n");
            printf("                    1. Inserir                              \n");
            printf("                    2. Excluir                              \n");
            printf("                    3. Exibir                               \n");
            printf("                    4. Colocar no Carrinho                  \n");
            printf("                    5. Tirar do Carrinho                    \n");
            printf("                    6. Ver Carrinho                         \n");
            printf("                    0. Voltar                               \n");
            printf("\n");
            printf("                    Opção desejada: ");
            opc = getche();
            if (opc != '0' && opc != '1' && opc != '2' && opc != '3' && opc != '4' && opc != '5' && opc != '6')
            {
                system("cls");
                printf("\n\n\n\n\n [%c] não é uma opção válida", opc);
                Sleep(800);
            }
        } while(opc != '0' && opc != '1' && opc != '2' && opc != '3' && opc != '4' && opc != '5' && opc != '6');
        if (opc == '1')
        {
            system("cls");
            do {
            printf("\n\n Numero da pilha: ");
            fflush(stdin); scanf("%i", &numpil);
            if (numpil < 1 || numpil > 10)
                printf("\n Numero inválido \n Deve estar entre 1 e 10");
            } while (numpil < 1 || numpil > 10);
            numpil--;
            inserirPilha(numpil);
        }
        if (opc == '2')
        {
            system("cls");
            do {
            printf("\n\n Numero da pilha: ");
            fflush(stdin); scanf("%i", &numpil);
            if (numpil < 1 || numpil > 10)
                printf("\n Numero inválido \n Deve estar entre 1 e 10");
            } while (numpil < 1 || numpil > 10);
            numpil--;
            excluirElemPilha(numpil,&excluido);
            printf("\n[%s - %s - %i g - %.2f Reais] Foi excluido",
            excluido.Nome, excluido.Desc, excluido.peso, excluido.preco);
            getch();
        }
        if (opc == '3')
            exibirPilhas();
        if (opc == '4')
        {
            system("cls");
            do {
            printf("\n\n Numero da pilha: ");
            fflush(stdin); scanf("%i", &numpil);
            if (numpil < 1 || numpil > 10)
                printf("\n Numero inválido \n Deve estar entre 1 e 10");
            } while (numpil < 1 || numpil > 10);
            numpil--;
            inserirCarrinho(numpil);
        }
        if (opc == '5')
        {
            excluirElemPilha(carrinho,&excluido);
            system("cls");
            printf("\n\n [%s - %s - %i g - %.2f Reais] Foi retirado",
            excluido.Nome, excluido.Desc, excluido.peso, excluido.preco);
            getch();
        }
        if (opc == '6')
            exibircarrinho();
        if (opc == '0')
            return;
    }
}

void inserirNaFila (fila * f, REGISTRO elem)
{
   PONT novo = (PONT) malloc(sizeof(ELEMENTO));
   if ( novo == NULL )
   {
      printf ("\n Erro ao colocar na fila");
      getch();
      exit(0);
   }

   novo->reg = elem;
   novo->PROX = NULL;
   if (f->inicio==NULL)
      f->inicio = novo;
   else
      f->fim->PROX = novo;
   f->fim = novo;

}

void reinicializarFila(fila * f)
{
   PONT end = f->inicio;
   PONT apagar;
   while (end != NULL)
   {
      apagar = end;
	  end = end->PROX;
	  free(apagar);
   }
   f->inicio = NULL;
   f->fim = NULL;
}

void caixa()
{
    REGISTRO produtofila;
    int n, i;
    float total = 0;

    n = tamanho(carrinho);

    system("cls");
    printf("\n");
    printf(" Caixa\n");
    for (i = 0; i < n; i++)
    {
        excluirElemPilha(carrinho,&produtofila);
        inserirNaFila(&esteira, produtofila);

        printf("\n [%s - %s - %i g - %.2f Reais]",
        produtofila.Nome, produtofila.Desc,
        produtofila.peso, produtofila.preco);

        total += produtofila.preco;
    }

    reinicializarFila(&esteira);

    printf("\n\n Valor total = %.2f Reais", total);
    getch();
}

void cadastrarnovos()
{
    usuario novo;
    FILE * cadastro = fopen("USUARIOS.DAT", "a");

    system("cls");
    printf("\n");

    if (cadastro == NULL)
    {
        printf ("\n Erro ao abrir USUARIOS.DAT");
        fclose(cadastro);
        getch();
        return;
    }

    printf("       Nome do usuário: ");
    fflush(stdin); gets(novo.nome);
    printf("\n");
    printf(" Prontuário do usuário: ");
    fflush(stdin); gets(novo.pront);

    fwrite ( &novo, sizeof(novo), 1, cadastro );

    if (ferror(cadastro))
    {
        printf ("\n Erro ao Cadastrar ");
        getch();

    }

    fclose(cadastro);
    system("cls");
    printf("\n Usuário %s", novo.nome);
    printf("\n Com Prontuário %s", novo.pront);
    printf("\n Cadastrado com Sucesso ");
    ordena();
}

void gerenciar()
{
    char opc;

    while (true)
    {
        do {
        system("cls");
        system("mode 60,15");
        printf("____________________________________________________________\n\n");
        printf("                     Gerenciar Usuários                     \n");
        printf("____________________________________________________________\n\n");
        printf("                    1. Cadastrar                            \n");
        printf("                    2. Visualizar                           \n");
        printf("                    0. Voltar                               \n");
        printf("\n");
        printf("                    Opção desejada: ");
        opc = getche();
            if (opc != '0' && opc != '1' && opc != '2')
            {
                system("cls");
                printf("\n\n\n\n\n [%c] não é uma opção válida", opc);
                Sleep(800);
            }
        } while(opc != '0' && opc != '1' && opc != '2');
        if (opc == '0')
            return;
        if (opc == '1')
            cadastrarnovos();
        if (opc == '2')
            lerdat();
    }
}

int menu ()
{
    char opc;
    system("mode 60,15");
    do  {
        system("cls");
        printf("____________________________________________________________\n\n");
        printf("            SISTEMA GERENCIADOR DE SUPERMERCADO             \n");
        printf("____________________________________________________________\n\n");
        printf("                    1. Abastecer gôndolas                   \n");
        printf("                    2. Caixa/PVD                            \n");
        printf("                    3. Gerenciar usuários                   \n");
        printf("                    0. Sair                                 \n");
        printf("\n");
        printf("                    Opção desejada: ");
        opc = getche();
        if (opc != '0' && opc != '1' && opc != '2' && opc != '3')
        {
            system("cls");
            printf("\n\n\n\n\n [%c] não é uma opção válida", opc);
            Sleep(800);
        }
        } while ( opc != '0' && opc != '1' && opc != '2' && opc != '3');
    if (opc == '1')
        return 1;
    if (opc == '2')
        return 2;
    if (opc == '3')
        return 3;
    if (opc == '0')
        exit(0);
    return -1;
}

int main()
{
    int i;
    usuario login;

    system("mode 60,10");
    setlocale(LC_ALL,"");
    cadastrar();
    cadastrogondolas();

    do
    {
        system("cls");
        printf("\n");
        printf("       Nome do usuário: ");
        fflush(stdin); gets(login.nome);

        if (strcmp(login.nome, "MASTER")==0)
            i = 1;
        else
        {
            printf("\n");
            printf(" Prontuário do usuário: ");
            fflush(stdin); gets(login.pront);
            i = busca_binaria(login);
            system("cls");
            printf("\n ");
            if (i == -1 || i == 0)
            {
                printf(" Usuário não cadastrado e/ou Prontuário errado");
                Sleep(1000);
            }
        }
    } while (i != 1);
    while (true)
    {
        i = menu();
        switch (i)
        {
            case 1: if (strcmp(login.nome, "MASTER")==0)
                        abastecermaster();
                    else abastecer();
                                    break;
            case 2: caixa();        break;
            case 3: gerenciar();    break;
        }
    }
    return 0;
}
