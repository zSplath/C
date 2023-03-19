/* bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>

/* prot�tipos */
void inicio     (void);
void menu       (void);
void cadastrar  (void);
void vizualizar (void);
void realizar   (void);
void sobre      (void);

void gotoxy     (int x, int y);

/* estruturas */
typedef struct
{
    int  num;
    char frase[100];
    int  cinestesico;
    char item_1[100];
	int  auditivo;
	char item_2[100];
	int  visual;
	char item_3[100];
	int  digital;
	char item_4[100];
} regdat;

/* vari�veis globais */
regdat linha[5] =
{
	{
	    1, "Eu tomo decis�es importantes baseado em",
        0, "intui��o",
        0, "o que me soa melhor",
        0, "o que me parece melhor",
        0, "um estudo preciso e minucioso do assunto"
    }
    ,
	{
	    2, "Durante uma discuss�o sou mais influenciado por",
        0, "se eu entro em contato ou n�o com os sentimentos reais do outro",
        0, "o tom da voz da outra pessoa",
        0, "se eu posso ou n�o ver o argumento da outra pessoa",
        0, "a l�gica do argumento da outra pessoa"
    }
    ,
    {
        3, "Eu comunico mais facilmente o que passa comigo",
        0, "pelos sentimentos que compartilho",
        0, "pelo tom da minha voz",
        0, "do modo como me visto e aparento",
        0, "pelas palavras que escolho"
    }
    ,
    {
        4, "� muito f�cil pra mim",
        0, "escolher os m�veis mais confort�veis",
        0, "achar o volume e a sintonia ideais num sistema de som",
        0, "escolher as combina��es de cores mais ricas e atraentes",
        0, "selecionar o ponto mais relevante relativo a um assunto interessante"
    }
    ,
    {
        5, "Eu me percebo assim",
        0, "eu sou muito sens�vel � maneira como a roupa veste o meu corpo",
        0, "se estou muito em sintonia com os sons dos ambientes",
        0, "eu respondo fortemente �s cores e � apar�ncia de uma sala",
        0, "se sou muito capaz de raciocinar com fatos dados novos"
    }

};

char nome[50], prontuario[10];
int i;

/* corpo da fun��o*/
int main()
{
    system ("mode 52,17");
    system ("color F0");
    setlocale(LC_ALL,"");
    inicio();
    system("cls");
    printf("\n DIGITE SEU NOME: ");
    gets(nome);
    for (i = 0; i <= strlen(nome); i++)
        nome[i] = toupper(nome[i]);
    /* verifica se o usu�rio digitado � o master */
    if (strcmp(nome, "MASTER") == 0)
        menu();
    else
        {
            printf("\n DIGITE SEU PRONTU�RIO: ");
            gets(prontuario);
            for (i = 0; i <= strlen(prontuario); i++)
                prontuario[i] = toupper(prontuario[i]);
            realizar();
        }
    return 0;
}

/* inicia o programa com uma tela de apresenta��o */
void inicio     (void)
{
    char aux[24] = "Sistema Representacional";
    printf("\n\n\n\n\n\n\n            ");
    for (i=0; i<24; i++)
    {
        printf("%c", aux[i]);
        Sleep(70);
    }
    Sleep(500);
}

/* abre o menu inicial para sele��o para o usu�rio master */
void menu       (void)
{
    char escolha;
    do { do {
    system ("cls");
    printf ("|==================================================|\n");
    printf ("|       TESTE DOS SISTEMAS REPRESENTACIONAIS       |\n");
    printf ("|==================================================|\n");
    printf ("|       1. Cadastrar Question�rio                  |\n");
    printf ("|       2. Vizualizar Question�rio                 |\n");
    printf ("|       3. Realizar Teste                          |\n");
    printf ("|       4. Sobre o Teste                           |\n");
    printf ("|       F. Fim                                     |\n");
    printf ("|==================================================|\n");
    printf ("|        Escolha ->                                |\n");
    printf ("|==================================================|\n");
    gotoxy(0, 9);
    printf ("|        Escolha -> ");
    escolha = getche();
    escolha = toupper(escolha);
    if ( escolha != '1' && escolha != '2' && escolha != '3' && escolha != '4' && escolha != 'F' )
    {
        system("cls");
        printf("\n Escolha inv�lida!! ");
        printf("\n Op��es: [1],[2],[3],[4],[F] \n");
        printf("\n Pressione qualquer tecla para voltar ao menu... ");
        getch();
    }
    }while ( escolha != '1' && escolha != '2' && escolha != '3' && escolha != '4' && escolha != 'F' );

         if (escolha == '1') cadastrar();
    else if (escolha == '2') vizualizar();
    else if (escolha == '3') realizar();
    else if (escolha == '4') sobre();
    else exit(0);

    } while (1);
}

/* op��o de cadastro do arquivo .dat localmente */
void cadastrar  (void)
{
    system("cls");
    FILE * cadastro = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "w");
    if (cadastro == NULL)
        printf ("\n Erro ao abrir TESTE_SISTEMA_REPRESENTACIONAL.DAT");
    else {
    for ( i = 0; i < 5; i++ )
	{
		fwrite ( &linha[i], sizeof(linha[i]), 1, cadastro );
		if (ferror(cadastro))
		{
			printf ("\n Erro ao Cadastrar A linha %i", ++i);
			getch();
			i = 1337;
		}
	}
    if (i==5) printf("\n\n\n\n\n\n\t\tCadastro finalizado com sucesso!");
    }
    fclose(cadastro);
    getch();
}

/* op��o de viualizar o arquivo .dat */
void vizualizar (void)
{
    FILE *dat,*txt;
    regdat temp;
    do {
    txt = fopen ("QUESTION�RIO_1.TXT", "w");
	if (txt == NULL)
	{
		printf ("\n Erro ao abrir QUESTION�RIO_1.TXT");
		getch();
		break;
	}
	dat = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "r");
	if (dat == NULL)
	{
		printf ("\n Erro ao abrir TESTE_SISTEMA_REPRESENTACIONAL.DAT");
		getch();
		break;
	}
	fprintf (txt, "\n Nro frase");
	fprintf (txt, "                ");
	fprintf (txt, " Frase ");
	fprintf (txt, "                          ");
	fprintf (txt, " C   Item_1 ");
	fprintf (txt, "                                                             ");
	fprintf (txt, " A   Item_2 ");
	fprintf (txt, "                                                  ");
	fprintf (txt, " V   Item_3 ");
	fprintf (txt, "                                                     ");
	fprintf (txt, " D   Item_4 ");
	fprintf (txt, "\n");
	for (i=0; i<334; i++)
        fprintf (txt, "=");
	while (!feof(dat))
	{
		fread (&temp, sizeof(temp), 1, dat);
		if (ferror(dat))
		{
			printf ("\n Erro ao ler TESTE_SISTEMA_REPRESENTACIONAL.DAT");
			getch();
			break;
		}
		if (!feof(dat))
		{
		   fprintf (txt,
           "\n|%3i |%50s |%3i | %-65s |%3i | %-54s |%3i | %-57s |%3i | %-68s |",
		   temp.num,
		   temp.frase,
		   temp.cinestesico,
		   temp.item_1,
		   temp.auditivo,
           temp.item_2,
           temp.visual,
           temp.item_3,
           temp.digital,
           temp.item_4);
	    }
  	}
	fprintf (txt, "\n");
	for (i=0; i<334; i++)
        fprintf (txt, "=");
	fclose (txt);
	fclose (dat);
	system ("notepad QUESTION�RIO_1.TXT");
    } while (1 == 2);
}

/* realizar o question�rio, tanto pelo usu�rio master quanto pelo padr�o */
void realizar   (void)
{
    system("cls");
    system ("mode 74,17");
    FILE *txt, *dat;
    regdat temp[5];
    int cinestesico_total, auditivo_total, visual_total, digital_total, maior, perfil;
    char nometxt[115], notepad[150];

	dat = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "r");
	if (dat == NULL)
	{
		printf ("\n Erro ao abrir TESTE_SISTEMA_REPRESENTACIONAL.DAT");
		getch();
		exit(0);
	}

	for( i = 0; i < 5; i++)
	{
		fread (&temp[i], sizeof(temp[i]), 1, dat);
		if (ferror(dat))
		{
			printf ("\n Erro ao ler TESTE_SISTEMA_REPRESENTACIONAL.DAT");
			printf ("\n Erro na Linha %i", i);
			getch();
			break;
		}
  	}

    fclose(dat);

  	cinestesico_total = 0;
  	auditivo_total    = 0;
  	visual_total      = 0;
  	digital_total     = 0;

  	for (i = 0; i < 5; i++)
    {
        system("cls");
        printf (" Nas frases a seguir, pontue com:             ");
        printf ("\n 4 a que melhor descreve voc�;              ");
        printf ("\n 3 a pr�xima melhor descri��o;              ");
        printf ("\n 2 a pr�xima melhor; e                      ");
        printf ("\n 1 aquela que menos descreve voc�.          ");
        printf ("\n--------------------------------------------------------------------------");
        printf ("\n Frase %i: ", temp[i].num);
        printf ("\n %-50s   \n", temp[i].frase);
        printf ("\n-> _ %-70s ", temp[i].item_1);
        printf ("\n-> _ %-70s ", temp[i].item_2);
        printf ("\n-> _ %-70s ", temp[i].item_3);
        printf ("\n-> _ %-70s ", temp[i].item_4);

        do {
        gotoxy(0, 9);
        printf("-> ");
        fflush(stdin);
        temp[i].cinestesico = getche()-48;

        if ( temp[i].cinestesico != 1 && temp[i].cinestesico != 2 &&
             temp[i].cinestesico != 3 && temp[i].cinestesico != 4    )
        {
            gotoxy(0,0);
            printf("                      S� s�o aceitos os valores:               ");
            printf("\n                          [1] [2] [3] [4]                    ");
            printf("\n                  (N�o s�o aceitos valores repetidos)        ");
            printf("\n                                                             ");
            gotoxy(0,4);
            printf("                 Aperte qualquer tecla para continuar...");
            system("color cf");
            Sleep(100);
            system("color fc");
            getch();
            gotoxy(0,0);
            system("color f0");
            printf (" Nas frases a seguir, pontue com:                         ");
            printf ("\n 4 a que melhor descreve voc�;                          ");
            printf ("\n 3 a pr�xima melhor descri��o;                          ");
            printf ("\n 2 a pr�xima melhor; e                                  ");
            printf ("\n 1 aquela que menos descreve voc�.                      ");
            gotoxy(0, 9);
            printf("-> _");
        }
        } while ( temp[i].cinestesico != 1 && temp[i].cinestesico != 2 &&
                  temp[i].cinestesico != 3 && temp[i].cinestesico != 4    );

        do {
        gotoxy(0,11);
        printf("-> ");
        fflush(stdin);
        temp[i].auditivo = getche()-48;

        if ( (temp[i].auditivo != 1 && temp[i].auditivo != 2 &&
              temp[i].auditivo != 3 && temp[i].auditivo != 4) ||
              temp[i].auditivo == temp[i].cinestesico)
        {
            gotoxy(0,0);
            printf("                      S� s�o aceitos os valores:               ");
            printf("\n                          [1] [2] [3] [4]                    ");
            printf("\n                  (N�o s�o aceitos valores repetidos)        ");
            printf("\n                                                             ");
            gotoxy(0,4);
            printf("                 Aperte qualquer tecla para continuar...");
            system("color cf");
            Sleep(100);
            system("color fc");
            getch();
            gotoxy(0,0);
            system("color f0");
            printf (" Nas frases a seguir, pontue com:                         ");
            printf ("\n 4 a que melhor descreve voc�;                          ");
            printf ("\n 3 a pr�xima melhor descri��o;                          ");
            printf ("\n 2 a pr�xima melhor; e                                  ");
            printf ("\n 1 aquela que menos descreve voc�.                      ");
            gotoxy(0,11);
            printf("-> _");
        }
        } while ( (temp[i].auditivo != 1 && temp[i].auditivo != 2  &&
                   temp[i].auditivo != 3 && temp[i].auditivo != 4) ||
                   temp[i].auditivo == temp[i].cinestesico         );

        do {
        gotoxy(0,13);
        printf("-> ");
        fflush(stdin);
        temp[i].visual = getche()-48;

        if ( (temp[i].visual != 1 && temp[i].visual != 2  &&
              temp[i].visual != 3 && temp[i].visual != 4) ||
              temp[i].visual == temp[i].cinestesico       ||
              temp[i].visual == temp[i].auditivo          )
        {
            gotoxy(0,0);
            printf("                      S� s�o aceitos os valores:               ");
            printf("\n                          [1] [2] [3] [4]                    ");
            printf("\n                  (N�o s�o aceitos valores repetidos)        ");
            printf("\n                                                             ");
            gotoxy(0,4);
            printf("                 Aperte qualquer tecla para continuar...");
            system("color cf");
            Sleep(100);
            system("color fc");
            getch();
            gotoxy(0,0);
            system("color f0");
            printf (" Nas frases a seguir, pontue com:                         ");
            printf ("\n 4 a que melhor descreve voc�;                          ");
            printf ("\n 3 a pr�xima melhor descri��o;                          ");
            printf ("\n 2 a pr�xima melhor; e                                  ");
            printf ("\n 1 aquela que menos descreve voc�.                      ");
            gotoxy(0,13);
            printf("-> _");
        }
        } while ( (temp[i].visual != 1 && temp[i].visual != 2  &&
                   temp[i].visual != 3 && temp[i].visual != 4) ||
                   temp[i].visual == temp[i].cinestesico       ||
                   temp[i].visual == temp[i].auditivo          );

        gotoxy(0,15);
        printf("-> ");
        if(temp[i].cinestesico!=1 && temp[i].auditivo!=1 && temp[i].visual!=1)
        temp[i].digital = 1;
        else if(temp[i].cinestesico!=2 && temp[i].auditivo!=2 && temp[i].visual!=2)
        temp[i].digital = 2;
        else if(temp[i].cinestesico!=3 && temp[i].auditivo!=3 && temp[i].visual!=3)
        temp[i].digital = 3;
        else temp[i].digital = 4;
        printf ("%i", temp[i].digital);
        gotoxy(0,15);
        printf("-> ");

        cinestesico_total += temp[i].cinestesico;
        auditivo_total    += temp[i].auditivo;
        visual_total      += temp[i].visual;
        digital_total     += temp[i].digital;

        getch();
    }

    dat = fopen ("TESTE_SISTEMA_REPRESENTACIONAL.DAT", "w");
	if (dat == NULL)
	{
		printf ("\n Erro ao abrir TESTE_SISTEMA_REPRESENTACIONAL.DAT");
		getch();
	}

    for ( i = 0; i < 5; i++ )
	{
		fwrite ( &temp[i], sizeof(temp[i]), 1, dat);
		if (ferror(dat))
		{
			system("cls");
			printf ("\n Erro ao Registrar respostas na linha %i", ++i);
			getch();
			i = 1337;
		}
	}

	fclose(dat);

    cinestesico_total *= 2;
    auditivo_total    *= 2;
    digital_total     *= 2;
    visual_total      *= 2;

    maior  = cinestesico_total;
    perfil = 1;

    if (auditivo_total > maior)
    {
        maior  = auditivo_total;
        perfil = 2;
    }

    if (visual_total > maior)
    {
        maior  = visual_total;
        perfil = 3;
    }

    if (digital_total > maior)
    {
        maior  = digital_total;
        perfil = 4;
    }

    for (i = 0; i <= strlen(nome); i++)
        if(nome[i] == 32) nome[i] = '_';

    if (strcmp(nome, "MASTER") == 0)
    {
        strcat(nometxt,"RESULTADO_");
        strcat(nometxt,nome);
        strcat(nometxt,".TXT");
    }
    else
    {
        strcat(nometxt,"RESULTADO_");
        strcat(nometxt,nome);
        strcat(nometxt,"_");
        strcat(nometxt,prontuario);
        strcat(nometxt,".TXT");
    }

	txt = fopen (nometxt, "w");

	if (txt == NULL)
	{
		system ("cls");
		printf ("\n Erro ao abrir %s", nometxt);
		getch();
	}

    fprintf ( txt, "                        PERFIL REPRESENTACIONAL DE %s \n", nome);
	fprintf ( txt, "===============================================================================================\n");
	fprintf ( txt, "        %i%% Visual       %i%% Auditivo        %i%% Cinest�sico        %i%% Digital            \n",
                           visual_total,      auditivo_total,     cinestesico_total,       digital_total              );
	fprintf ( txt, "===============================================================================================\n");
	fprintf ( txt, "Algumas pessoas captam melhor as mensagens do mundo exterior atrav�s da audi��o, \n");
    fprintf ( txt, "s�o as pessoas chamadas auditivas. \n\n");
    fprintf ( txt, "Outras pessoas sentem necessidade de perguntar muito, necessitam de muitas informa��es e fatos.\n");
    fprintf ( txt, "Estas s�o as digitais. \n\n");
    fprintf ( txt, "As cinest�sicas aprendem melhor por meio das sensa��es t�teis, \n");
    fprintf ( txt, "como o tato, a temperatura, a umidade, as sensa��es internas e as emo��es. \n\n");
    fprintf ( txt, "J� as pessoas visuais aprendem melhor quando se valendo da vis�o. \n\n");
    fprintf ( txt, "===============================================================================================\n");
    fprintf ( txt, " Seu perfil � ");
         if (perfil==1) fprintf ( txt, " CINEST�SICO \n");
    else if (perfil==2) fprintf ( txt, " AUDITIVO    \n");
    else if (perfil==3) fprintf ( txt, " VISUAL      \n");
    else                fprintf ( txt, " DIGITAL     \n");
    fprintf ( txt, "===============================================================================================\n");
    fclose(txt);

    strcat(notepad,"notepad ");
    strcat(notepad,nometxt);

    system(notepad);
    getch();
}

/* trazer informa��es sobre os crit�rios do teste */
void sobre      (void)
{
    FILE * text = fopen("REFERENCIAL_TEORICO.TXT", "w");
    if (text == NULL)
        printf ("\n Erro ao abrir REFERENCIAL_TEORICO.TXT");
    else {
    fprintf ( text, "REFERENCIAL TEORICO \n");
    fprintf ( text, "=================== \n");
    fprintf ( text, "\nSegundo Albert Merabian, em seu livro �Silent Messages�, o poder de influ�ncia das palavras n�o passa de 7%%,");
    fprintf ( text, "\nenquanto a forma como as palavras s�o ditas e a fisiologia representam 38%% e 55%% deste poder, respectivamente.\n");
    fprintf ( text, "\nPara Merabian 55%% do impacto da comunica��o � n�o-verbal. Corresponde � postura, gestos e contato visual da");
    fprintf ( text, "\npessoa enquanto se comunica.\n");
    fprintf ( text, "\nO tom da voz representa 38%% do impacto da comunica��o.\n");
    fprintf ( text, "\nPor fim, as palavras propriamente ditas det�m 7%% do impacto da comunica��o.\n");
    fprintf ( text, "\nAssim sendo, conclui Merabian, n�o � o que dizemos, mas como dizemos que faz a diferen�a na comunica��o.\n");
    fprintf ( text, "\nAs portas da percep��o s�o os nossos sentidos, nossos olhos, nariz, ouvidos, boca e pele, nossos �nicos pontos de");
    fprintf ( text, "\ncontato com o mundo exterior. Da mesma forma que utilizamos os sentidos para filtrarmos as experi�ncias,");
    fprintf ( text, "\nutilizamos os sentidos para estruturar nosso pensamento e nossa comunica��o.\n");
    fprintf ( text, "\nDe acordo com a Programa��o Neurolingu�stica existem os seguintes sistemas representacionais.\n");
    fprintf ( text, "\n- Auditivo");
    fprintf ( text, "\n- Digital");
    fprintf ( text, "\n- Cinest�sico");
    fprintf ( text, "\n- Visual");
    fprintf ( text, "\n\nAlgumas pessoas captam melhor as mensagens do mundo exterior atrav�s da audi��o, s�o as pessoas chamadas");
    fprintf ( text, "\nauditivas.");
    fprintf ( text, "\nOutras pessoas sentem necessidade de perguntar muito, necessitam de muitas informa��es e fatos. Estas s�o as");
    fprintf ( text, "\ndigitais.");
    fprintf ( text, "\nAs cinest�sicas aprendem melhor por meio das sensa��es t�teis, como o tato, a temperatura, a umidade, as");
    fprintf ( text, "\nsensa��es internas e as emo��es.");
    fprintf ( text, "\nJ� as pessoas visuais aprendem melhor quando se valendo da vis�o.\n");
    fprintf ( text, "\nCada pessoa tem um sistema representacional predominante e adequar a comunica��o ao sistema representacional");
    fprintf ( text, "\ndominante dela � fundamental para di�logos eficientes.\n");
    fclose  (text);
    system  ("notepad REFERENCIAL_TEORICO.TXT");
    }
    getch();
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
