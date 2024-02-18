#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio2.h>
#include <ctype.h>
#define tf 30
struct Rdata
{
	int d,m,a;
};
struct Rprod
{
	int cod, estoque,codForne,status;
	float preco;
	Rdata validade;
	char desc[tf];
};
struct Rforne
{
	int codForne,status;
	char nomeForne[tf],cidadeForne[tf];
};
struct Rcli
{
	long int cpf;
	int qntdCompra,status; // status para exclusão logica 1 ativo 0 excluido
	float ValorTotComprado;
	char NomeCli[tf];	
};
struct Rvendas
{
	int CodVenda,CpfCli,status;
	float TotVenda;
	Rdata DVenda;
	
};
struct RvendasProdutos
{
	int CodVenda,CodProd,qntd,status;
	float ValorUni;
};
void limpartela()
{
	int i;
	for(i=7;i <= 20;i++)
	{
		gotoxy(3,i);
		for(int j=2;j<=77;j++)
		{
			printf(" ");
		}
	}
}
void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i;
	textcolor(CorT);
	textbackground(CorF);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1; i<CF; i++)
	{
		gotoxy(i,LI); printf("%c",205);
		gotoxy(i,LF); printf("%c",205);
	}
	for(i=LI+1; i<LF; i++)
	{
		gotoxy(CI,i); printf("%c",186);
		gotoxy(CF,i); printf("%c",186);
	} 
	
	textcolor(7);
	textbackground(0);
}
void Formulario(void)
{
	system("cls");
	Moldura(1,1,80,25,0,9); //Moldura geral

	
//	 moldura(2,2,79,4,14,1); moldura do titulo 
//	Moldura(2,5,27,21,12,7); Moldura lateral esquerda
	//MenuPrincipal();
	// Moldura(2,22,79,24,11,4); moldur da mensagem
	gotoxy(4,23);
	textcolor(1);
	printf("Mensagem: ");

	Moldura(2,5,79,21,8,7);  // moldura da lateral direita
}
char menu(void)
{
	int op;
	limpartela();
	textcolor(15);
	gotoxy(5,7);
	printf("[1] Cadastrar");
	gotoxy(5,8);
	printf("[2] Consulta");
	gotoxy(5,9);
	printf("[3] Venda");
	gotoxy(5,10);
	printf("[4] Exclusao Logica");
	gotoxy(5,11);
	printf("[5] Exclusao Fisica");
	gotoxy(5,12);
	printf("[6] Nota fiscal");
    gotoxy(5,13);
	printf("[7] Relatorio");
	gotoxy(5,14);
	printf("[8] Alterar");
	gotoxy(5,15);
	printf("[9] Aumentar");
	gotoxy(5,16);
	printf("[10] Inserir Dados");
	gotoxy(5,17);
	printf("[0] Sair\n");
	gotoxy(5,18);
	printf("Opcao desejada: ");
	scanf("%d",&op);
	getchar();
	return op;
	
}
char subMenu(void)
{
	int op;
	gotoxy(5,7);
	printf("[1] Fornecedor");
	gotoxy(5,8);
	printf("[2] Produto");
	gotoxy(5,9);
	printf("[3] Cliente");
	gotoxy(5,10);
	printf("[4] Vendas");
	gotoxy(5,12);
	printf("Opcao desejada: ");
	scanf ("%d",&op);
	return op;
}
char subCad(void)
{
	int op;
	gotoxy(5,7);
	printf("[1] Fornecedor");
	gotoxy(5,8);
	printf("[2] Produto");
	gotoxy(5,9);
	printf("[3] Cliente");
	gotoxy(5,12);
	printf("Opcao desejada: ");
	scanf ("%d",&op);
	return op;
}
// fazendo as ordenação
void Ordenarforne(void)
{
	int a,b,QtdeReg;
	Rforne RA, RB;
	FILE *Ptr = fopen("Fornecedor.dat","rb+");
		
			fseek(Ptr,0,2); //Deslocar o Ponteiro para o final do Arquivo
			QtdeReg = ftell(Ptr)/sizeof(Rforne);
			
			for(a=0; a<QtdeReg-1; a++)
				for(b=a+1; b<QtdeReg; b++)
				{
					fseek(Ptr,a*sizeof(Rforne),0);
					fread(&RA,sizeof(Rforne),1,Ptr);
					
					fseek(Ptr,b*sizeof(Rforne),0);
					fread(&RB,sizeof(Rforne),1,Ptr);
					
					if(RA.codForne > RB.codForne)
					{
						fseek(Ptr,a*sizeof(Rforne),0);
						fwrite(&RB,sizeof(Rforne),1,Ptr);
						
						fseek(Ptr,b*sizeof(Rforne),0);
						fwrite(&RA,sizeof(Rforne),1,Ptr);
					}
				}
			fclose(Ptr);
}

int buscaProdVp(FILE *ptr,int venda,int codp)
{
	RvendasProdutos Reg;
	fseek(ptr,0,0);
	fread(&Reg,sizeof(RvendasProdutos),1,ptr);
	while (!feof(ptr) && Reg.CodProd == codp)
	{
		if(Reg.CodVenda == venda )
		{
			return ftell(ptr)-sizeof(RvendasProdutos);
		}
		fread(&Reg,sizeof(RvendasProdutos),1,ptr);
	}
		
	if(!feof(ptr))
		return -1;	
		 
}
// FAZENDO AS BUSCAS 
int BuscaForne (FILE *ptr,int cod)
{
	// busca seguencial
	Rforne Reg;
	rewind(ptr); // manda o ponteiro para o inicio
	fread(&Reg,sizeof(Rforne),1,ptr);
	while (!feof(ptr) && cod!=Reg.codForne && Reg.status== 1)
		fread(&Reg,sizeof(Rforne),1,ptr);
	
	if (!feof(ptr)) // achou 
		return ftell(ptr)-sizeof(Rforne);
	else // não achou
		return -1;
}
//int BuscaForne(FILE *ptr, int cod) {
//    Rforne Reg;
//    int posicao = 0;

//    rewind(ptr); // Manda o pro começo
//    fread(&Reg, sizeof(Rforne), 1, ptr);

//    while (!feof(ptr) && cod > Reg.codForne) {
//        fread(&Reg, sizeof(Rforne), 1, ptr);
//    }
//    if (cod == Reg.codForne) 
//	{
//    return ftell(ptr)-sizeof(Rforne);
//	}
//	else
//	{
//			return -1;
//	}
//}

int BuscaCli (FILE *ptr,int cod)
{
	// busca seguencial
	Rcli Reg;
	rewind(ptr); // manda o ponteiro para o inicio
	fread(&Reg,sizeof(Rcli),1,ptr);
	while (!feof(ptr) && cod!=Reg.cpf && Reg.status== 1)
		fread(&Reg,sizeof(Rcli),1,ptr);
	
	if (!feof(ptr)) // achou 
		return ftell(ptr)-sizeof(Rcli);
	else // não achou
		return -1;
}
int BuscaProd (FILE *ptr,int cod)
{
	// busca seguencial
	Rprod Reg;
	rewind(ptr); // manda o ponteiro para o inicio
	fread(&Reg,sizeof(Rprod),1,ptr);
	while (!feof(ptr) && cod!=Reg.cod && Reg.status== 1)
		fread(&Reg,sizeof(Rprod),1,ptr);
	
	if (!feof(ptr)) // achou 
		return ftell(ptr)-sizeof(Rprod);
	else // não achou
		return -1;
}
//int BuscaCli(FILE *ptr,int cpf)
//{
//	
//	Rcli Reg;
//	rewind(ptr); // manda o ponteiro para o inicio
//	fread(&Reg,sizeof(Rcli),1,ptr);
//	
//	while (!feof(ptr) && cpf > Reg.cpf && Reg.status == 1 )
//		fread(&Reg,sizeof(Rcli),1,ptr);
//		
//	if(!feof(ptr) && cpf == Reg.cpf)
//		return ftell(ptr)-sizeof(Rcli);
//	else
//		return -1;
//		
//}
int BuscaVenda (FILE *ptr,int cod)
{
	// busca seguencial
	Rvendas Reg;
	rewind(ptr); // manda o ponteiro para o inicio
	fread(&Reg,sizeof(Rvendas),1,ptr);
	while (!feof(ptr) && cod!=Reg.CodVenda && Reg.status== 1)
		fread(&Reg,sizeof(Rvendas),1,ptr);
	
	if (!feof(ptr)) // achou 
		return ftell(ptr)-sizeof(Rvendas);
	else // não achou
		return -1;
}
int BuscaVendaP (FILE *ptrvp,int codvenda,int codVp)
{
	// busca seguencial
	Rvendas RegV;
	RvendasProdutos RegVp;
	rewind(ptrvp); // manda o ponteiro para o inicio
	fread(&RegVp,sizeof(RvendasProdutos),1,ptrvp);
	while (!feof(ptrvp))
	{
		if (codvenda == RegVp.CodVenda)
			return ftell(ptrvp)-sizeof(RvendasProdutos);
			
		fread(&RegVp,sizeof(RvendasProdutos),1,ptrvp);
	}
		
	
}

// FAZENDO CADASTRO
void CadastroForne (void)
{
	Rforne Reg;
	int pos;
	char opc;
	//abrindo o arq
	FILE *ptr = fopen("Fornecedor.dat","ab+");
	

	
	gotoxy(27,3);
	printf("* * * Cadastro de Fornecedor * * *");
	gotoxy(5,7);
	printf("Digite o Codigo do Fornecedor: ");
	scanf("%d", &Reg.codForne);
	while (Reg.codForne > 0)
	{
		pos=BuscaForne(ptr,Reg.codForne);  // fazer busca de fornecedor
		
		if (pos == -1)
		{
			// não achou o fornecedor então vc faz o cadastro
			gotoxy(5,8);
			printf("Digite o nome do Fornecedor: ");
			fflush(stdin);
			gets(Reg.nomeForne);
			gotoxy(5,9);
			printf("Digite a cidade do Fornecedor: ");
			fflush(stdin);
			gets(Reg.cidadeForne);
			Reg.status = 1;
			fwrite(&Reg,sizeof(Rforne),1,ptr);
			gotoxy(5,10);
			printf("Novo Cadastro? S|N:  ");
			opc = toupper(getche());
			if(opc=='S')
			{
				limpartela();
				gotoxy(5,7);
				printf("Digite o Codigo do Fornecedor: ");
				scanf("%d",&Reg.codForne);	
			}
			else
			{
				Reg.codForne = 0;
				limpartela();
			}
			
		}
		else
		{
			limpartela();
			gotoxy(5,7);
			fseek(ptr,pos,0);
			fread(&Reg,sizeof(Rforne),1,ptr);
			printf("Nome: %s | Codigo: %d",Reg.nomeForne,Reg.codForne);
			gotoxy(17,23);
			
			printf("*** FORNECEDOR JA CADASTRADO ***");
			getch();
			system("cls");
			Formulario();
			gotoxy(5,7);
			printf("Novo Cadastro? S|N:  ");
			opc = toupper(getche());
			if(opc=='S')
			{
				limpartela();
				gotoxy(5,7);
				printf("Digite o Codigo do Fornecedor: ");
				scanf("%d",&Reg.codForne);	
			}
			else
			{
				Reg.codForne = 0;
				limpartela();
			}
		}
		
	}
	
	fclose(ptr);
	Ordenarforne();
}
void CadastroCli(void)
{
	Rcli Reg;
	int pos=0;
	char opc;
	
	// abrindo o arq
	FILE *ptr = fopen("Cliente.dat","ab+");
	
	gotoxy(27,3);
	printf("*** Cadastro de Cliente ***");
	gotoxy(5,7);
	printf("Digite o CPF: ");
	scanf("%ld",&Reg.cpf);
	
	while(Reg.cpf > 0)
	{
//		printf("entrou");
		pos = BuscaCli(ptr,Reg.cpf);
		
		if(pos == -1) // aqui não achou faz o cad
		{
			gotoxy(5,8);
			printf("Digite o nome: ");
			fflush(stdin);
			gets(Reg.NomeCli);
			// qntd posso zerar aqui e nma venda fazer uma alteração ?
			// valor vendido tmb?
			Reg.qntdCompra = 0;
			Reg.ValorTotComprado = 0.0;
			Reg.status=1;
			fwrite(&Reg,sizeof(Rcli),1,ptr);
			
			gotoxy(5,10);
			printf("Novo Cadastro? S|N:  ");
			opc = toupper(getche());
			if(opc=='S')
			{
				limpartela();
				gotoxy(5,7);
				printf("Digite o CPF: ");
				scanf("%ld",&Reg.cpf);
			}
			else
			{
				Reg.cpf = 0;
				limpartela();
			}
		}
		else
		{
			gotoxy(17,23);
			printf("*** Cliente ja cadastrado ***");
			gotoxy(5,7);
			fseek(ptr,pos,0);
			fread(&Reg,sizeof(Rcli),1,ptr);
			printf("Nome: %s | CPF: %ld",Reg.NomeCli,Reg.cpf);
			getch();
			
			system("cls");
			Formulario();
			gotoxy(5,7);
			printf("Novo Cadastro? S|N:  ");
			opc = toupper(getche());
			if(opc=='S')
			{
				limpartela();
				gotoxy(5,7);
				printf("Digite o CPF: ");
				scanf("%ld", &Reg.cpf);
			}
			else
			{
				Reg.cpf = 0;
				limpartela();
			}
		}
	}
	fclose(ptr);
}
void CadastroProd (void)
{
	FILE *ptr = fopen("Produtos.dat","ab+");
	Rprod Reg;
	int pos=0,posforne=0;
	char opc;
	
	
	gotoxy(27,3);
	printf("* * * Cadastro de Produtos * * *");
	gotoxy(5,7);
	printf("Codigo do Produto: ");
	scanf("%d",&Reg.cod);
	while(Reg.cod > 0)
	{
		pos = BuscaProd(ptr,Reg.cod);
		if(pos==-1)
		{
			gotoxy(5,8);
			printf("Digite o codigo do Fornecedor: ");
			scanf("%d",&Reg.codForne);
			FILE * ptrforne = fopen("fornecedor.dat","rb");
			// abro aqui o arq do fornecedor ? ou la em cima e fecho onde?
			
			posforne = BuscaForne(ptrforne,Reg.codForne);
			if (posforne==-1)
			{
				gotoxy(17,23);
				printf("*** FORNECEDOR NAO LOCALIZADO");
				getch(); 
				
				system("cls");
				Formulario();
				gotoxy(27,3);
				printf("* * * Cadastro de Produtos * * *");
				gotoxy(5,7);
				printf("Novo Cadastro? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Codigo do Produto: ");
					scanf("%d",&Reg.cod);
				}
				else
				{
					Reg.cod = 0;
					limpartela();
					
				}
			 fclose(ptrforne);
			}
				
			else
			{
				gotoxy(5,9);
				printf("Descricao do Produto: ");
				fflush(stdin);
				gets(Reg.desc);
				gotoxy(5,10);
				printf("Valor Unitario: ");
				scanf("%f", &Reg.preco);
				gotoxy(5,11);
				printf("Quantidade em Estoque: ");
				scanf("%d", &Reg.estoque);
				gotoxy(5,12);
				printf("Digite a data de Validade [DD MM AAAA]: ");
				scanf("%d %d %d", &Reg.validade.d,&Reg.validade.m,&Reg.validade.a);
				Reg.status = 1;
				fwrite(&Reg,sizeof(Rprod),1,ptr);
				
				gotoxy(17,23);
				printf("* Produto Cadastrado!! *");
				getch();
				
				system("cls");
				Formulario();
				gotoxy(27,3);
				printf("* * * Cadastro de Produtos * * *");
				gotoxy(5,7);
				printf("Novo Cadastro? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Codigo do Produto: ");
					scanf("%d",&Reg.cod);
				}
				else
				{
					Reg.cod = 0;
					limpartela();
					
				}
			}
			
		}
		else
		{
			limpartela();
			gotoxy(5,7);
			printf("Produto ja cadastrado!!");
			fseek(ptr,pos,0);
			fread(&Reg,sizeof(Rprod),1,ptr);
			gotoxy(5,8);
			printf("Produto: %d | Descricao: %s",Reg.cod,Reg.desc);
			getch();
		
		
			system("cls");
			Formulario();
			gotoxy(27,3);
			printf("* * * Cadastro de Produtos * * *");
			gotoxy(5,7);
			printf("Novo Cadastro? S|N:  ");
			opc = toupper(getche());
			if(opc=='S')
			{
				limpartela();
				gotoxy(5,7);
				printf("Codigo do Produto: ");
				scanf("%d",&Reg.cod);
			}
			else
			{
				Reg.cod = 0;
				limpartela();	
			}
		}
	}
	fclose(ptr);
}
void ConsulProd(void)
{
	int pos;
	char opc;
	Rprod Reg;
	FILE *ptr = fopen("Produtos.dat","rb+");
	gotoxy(27,3);
	printf("*** Consulta de Produtos ***");
	if (ptr == NULL)
	{
		gotoxy(5,7);
		printf("Erro de Abertura!");
		getch();
		limpartela();	
	}
	else
	{
		gotoxy(5,7);
		printf("Codigo do produto: ");
		scanf("%d",&Reg.cod);
		
		while (Reg.cod > 0)
		{
			pos = BuscaProd(ptr,Reg.cod);
			if(pos == -1)
			{
				limpartela();
				gotoxy(5,7);
				printf("Produto nao encontrado!");
				getch();
				limpartela();
				gotoxy(5,7);
				printf("Nova Consulta? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Codigo do produto: ");
					scanf("%d",&Reg.cod);
				}
				else
				{
					Reg.cod = 0;
					limpartela();	
				}
			}
			else
			{
				fseek(ptr,pos,0);
				fread(&Reg,sizeof(Rprod),1,ptr);
				limpartela();
				gotoxy(5,7);
				printf("-----------------------------------------------------------------");
				gotoxy(5,8);
				printf("ID: %d | Nome: %s | Estoque: %d | Preco: %.2f ",Reg.cod,Reg.desc,Reg.estoque,Reg.preco);
				gotoxy(5,9);
				printf("Data de validade: %d/%d/%d | ID Fornecedor: %d ",Reg.validade,Reg.codForne);
				gotoxy(5,10);
				printf("-----------------------------------------------------------------");
				
				gotoxy(5,12);
				printf("Nova Consulta? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Codigo do produto: ");
					scanf("%d",&Reg.cod);
				}
				else
				{
					Reg.cod = 0;
					limpartela();	
				}
			}
		}
		fclose(ptr);
	}
}
void Consulforne(void)
{
	int pos;
	char opc;
	Rforne Reg;
	FILE *ptr = fopen("Fornecedor.dat","rb+");
	gotoxy(27,3);
	printf("*** Consulta de Fornecedor ***");
	if (ptr == NULL)
	{
		gotoxy(5,7);
		printf("Erro de Abertura!");
		getch();
		limpartela();	
	}
	else
	{
		gotoxy(5,7);
		printf("Codigo do Fornecedor: ");
		scanf("%d",&Reg.codForne);
		
		while (Reg.codForne > 0)
		{
			pos = BuscaForne(ptr,Reg.codForne);
			if(pos == -1)
			{
				limpartela();
				gotoxy(5,7);
				printf("fornecedor nao encontrado!");
				getch();
				limpartela();
				gotoxy(5,7);
				printf("Nova Consulta? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Codigo do Fornecedor: ");
					scanf("%d",&Reg.codForne);
				}
				else
				{
					Reg.codForne = 0;
					limpartela();	
				}			
			}
			else
			{
				fseek(ptr,pos,0);
				fread(&Reg,sizeof(Rforne),1,ptr);
				limpartela();
				gotoxy(5,7);
				printf("-----------------------------------------------------------------");
				gotoxy(5,8);
				printf("ID: %d | Nome: %s | Cidade: %s | Status: %d",Reg.codForne,Reg.nomeForne,Reg.cidadeForne,Reg.status);
				gotoxy(5,9);
				printf("-----------------------------------------------------------------");
				getch();
				
				limpartela();
				gotoxy(5,7);
				printf("Nova Consulta? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Codigo do Fornecedor: ");
					scanf("%d",&Reg.codForne);
				}
				else
				{
					Reg.codForne = 0;
					limpartela();	
				}
			}
		}
		fclose(ptr);
	}
}
void ConsulCli(void)
{
	int pos;
	char opc;
	Rcli Reg;
	FILE *ptr = fopen("Cliente.dat","rb+");
	gotoxy(27,3);
	printf("*** Consulta de Clientes ***");
	if (ptr == NULL)
	{
		gotoxy(5,7);
		printf("Erro de Abertura!");
		getch();
		limpartela();	
	}
	else
	{
		gotoxy(5,7);
		printf("CPF do Cliente: ");
		scanf("%ld",&Reg.cpf);
		
		while(Reg.cpf > 0)
		{
		
			pos = BuscaCli(ptr,Reg.cpf);
			if(pos == -1)
			{
				limpartela();
				gotoxy(5,7);
				printf("Cliente nao encontrado!");
				getch();
				limpartela();
				gotoxy(5,7);
				printf("Nova Consulta? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("CPF do Cliente: ");
					scanf("%ld",&Reg.cpf);
				}
				else
				{
					Reg.cpf = 0;
					limpartela();	
				}

			}
			else
			{
				fseek(ptr,pos,0);
				fread(&Reg,sizeof(Rcli),1,ptr);
				limpartela();
				gotoxy(5,7);
				printf("-----------------------------------------------------------------");
				gotoxy(5,8);
				printf("CPF: %d | Nome: %s |Status: %d",Reg.cpf,Reg.NomeCli,Reg.status);
				gotoxy(5,9);
				printf("Qtde comprada: %d | Total: %.2f",Reg.qntdCompra,Reg.ValorTotComprado);
				gotoxy(5,10);
				printf("-----------------------------------------------------------------");
				gotoxy(5,11);
				printf("Nova Consulta? S|N:  ");
				opc = toupper(getche());
				if(opc=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("CPF do Cliente: ");
					scanf("%ld",&Reg.cpf);
				}
				else
				{
					Reg.cpf = 0;
					limpartela();	
				}
			}
		}
		fclose(ptr);
	}
}
void ExcLoProd(void)
{
	Rprod Reg;
	int pos;
	char opc;
	FILE *ptr =fopen("Produtos.dat","rb+");
	gotoxy(27,3);
	printf("*** Exclusao Logica de Produto ***");
	
	gotoxy(5,7);
	printf("Qual codigo produto deseja Excluir: ");
	scanf("%d",&Reg.cod);
	
	while(Reg.cod > 0)
	{
		pos =BuscaProd(ptr,Reg.cod);
		
		if(pos == -1)
		{
			limpartela();
			gotoxy(5,7);
			printf("Produto nao encontrado!");
			getch();
			limpartela();
			
			gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("Qual codigo produto deseja Excluir: ");
						scanf("%d",&Reg.cod);
					}
					else
					{
						Reg.cod = 0;
						limpartela();	
					}
		}
		else
		{
			limpartela();
			fseek(ptr,pos,0);
			fread(&Reg,sizeof(Rprod),1,ptr);
				gotoxy(5,7);
				printf("-----------------------------------------------------------------");
				gotoxy(5,8);
				printf("ID: %d | Nome: %s | Estoque: %d | Preco: %.2f ",Reg.cod,Reg.desc,Reg.estoque,Reg.preco);
				gotoxy(5,9);
				printf("Data de validade: %d/%d/%d | ID Fornecedor: %d ",Reg.validade,Reg.codForne);
				gotoxy(5,10);
				printf("-----------------------------------------------------------------");
				
				gotoxy(5,11);
				printf("\n Deseja Excluir?  S|N: ");
				if(toupper(getche())=='S')
				{
					Reg.status=0;
					fseek(ptr,pos,0);
					fwrite(&Reg,sizeof(Rprod),1,ptr);
					
					gotoxy(5,13);
					printf("*** Produto Excluido ***");
					getch();
					
					
					limpartela();
					gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("Qual codigo produto deseja Excluir: ");
						scanf("%d",&Reg.cod);
					}
					else
					{
						Reg.cod = 0;
						limpartela();	
					}
				}
				else
				{
					gotoxy(5,13);
					printf("*** Exclusao Cancelada!! ***");
					getch();
					
					limpartela();
					gotoxy(5,7);
					printf("Novo Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("Qual codigo produto deseja Excluir: ");
						scanf("%d",&Reg.cod);
					}
					else
					{
						Reg.cod = 0;
						limpartela();	
					}
				}
		
		}
	}
	fclose(ptr);
}
void ExcLoForne (void)
{
	Rforne Reg;
	int pos;
	char opc;
	FILE *ptr =fopen("Fornecedor.dat","rb+");
	gotoxy(27,3);
	printf("*** Exclusao Logica de Fornecedor ***");
	
	gotoxy(5,7);
	printf("Codigo do fornecedor que deseja Excluir: ");
	scanf("%d",&Reg.codForne);
	
	while(Reg.codForne > 0)
	{
		pos =BuscaForne(ptr,Reg.codForne);
		
		if(pos == -1)
		{
			limpartela();
			gotoxy(5,7);
			printf("Fornecedor nao encontrado!");
			getch();
			limpartela();
			gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("Codigo do fornecedor que deseja Excluir: ");
						scanf("%d",&Reg.codForne);
					}
					else
					{
						Reg.codForne = 0;
						limpartela();	
					}
		}
		else
		{
			limpartela();
			fseek(ptr,pos,0);
			fread(&Reg,sizeof(Rforne),1,ptr);
				gotoxy(5,7);
				printf("-----------------------------------------------------------------");
				gotoxy(5,8);
				printf("ID: %d | Nome: %s | Cidade: %s | Status: %d",Reg.codForne,Reg.nomeForne,Reg.cidadeForne,Reg.status);
				gotoxy(5,9);
				printf("-----------------------------------------------------------------");
				getch();
				
				gotoxy(5,11);
				printf(" Deseja Excluir?  S|N: ");
				if(toupper(getche())=='S')
				{
					Reg.status=0;
					fseek(ptr,pos,0);
					fwrite(&Reg,sizeof(Rprod),1,ptr);
					
					gotoxy(5,13);
					printf("*** Fornecedor Excluido ***");
					getch();
					
					
					limpartela();
					gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("Codigo do fornecedor que deseja Excluir: ");
						scanf("%d",&Reg.codForne);
					}
					else
					{
						Reg.codForne = 0;
						limpartela();	
					}
				}
				else
				{
					gotoxy(5,13);
					printf("*** Exclusao Cancelada!! ***");
					getch();
					
					limpartela();
					gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("Codigo do fornecedor que deseja Excluir: ");
						scanf("%d",&Reg.codForne);
					}
					else
					{
						Reg.codForne = 0;
						limpartela();	
					}
				}
		
		}
	}
	fclose(ptr);
}
void ExcLoCli (void)
{
	Rcli Reg;
	int pos;
	char opc;
	FILE *ptr =fopen("Cliente.dat","rb+");
	gotoxy(27,3);
	printf("*** Exclusao Logica de Cliente ***");
	
	gotoxy(5,7);
	printf("CPF do Cliente que deseja Excluir: ");
	scanf("%d",&Reg.cpf);
	
	while(Reg.cpf > 0)
	{
		pos =BuscaCli(ptr,Reg.cpf);
		
		if(pos == -1)
		{
			limpartela();
			gotoxy(5,7);
			printf("Cliente nao encontrado!");
			getch();
			limpartela();
			gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("CPF do Cliente que deseja Excluir: ");
						scanf("%d",&Reg.cpf);
					}
					else
					{
						Reg.cpf = 0;
						limpartela();	
					}
		}
		else
		{
			limpartela();
			fseek(ptr,pos,0);
			fread(&Reg,sizeof(Rcli),1,ptr);
				gotoxy(5,7);
				printf("-----------------------------------------------------------------");
				gotoxy(5,8);
				printf("CPF: %d | Nome: %s | Qtde comprada: %d | Total: %.2f",Reg.cpf,Reg.NomeCli,Reg.qntdCompra,Reg.ValorTotComprado);
				gotoxy(5,9);
				printf("Status: %d",Reg.status);
				gotoxy(5,10);
				printf("-----------------------------------------------------------------");
				gotoxy(5,11);
				printf("Deseja Excluir?  S|N: ");
				if(toupper(getche())=='S')
				{
					Reg.status=0;
					fseek(ptr,pos,0);
					fwrite(&Reg,sizeof(Rcli),1,ptr);
					
					gotoxy(5,13);
					printf("*** Cliente Excluido ***");
					getch();
					
					
					limpartela();
					gotoxy(5,7);
					printf("Nova Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("CPF do Cliente que deseja Excluir: ");
						scanf("%d",&Reg.cpf);
					}
					else
					{
						Reg.cpf = 0;
						limpartela();	
					}
				}
				else
				{
					gotoxy(5,13);
					printf("*** Exclusao Cancelada!! ***");
					getch();
					
					limpartela();
					gotoxy(5,7);
					printf("Novo Exlusao? S|N:  ");
					opc = toupper(getche());
					if(opc=='S')
					{
						limpartela();
						gotoxy(5,7);
						printf("CPF do Cliente que deseja Excluir: ");
						scanf("%d",&Reg.cpf);
					}
					else
					{
						Reg.cpf = 0;
						limpartela();	
					}
				}
		
		}
	}
	fclose(ptr);	
}
void ExlFisTot(void)
{
	
	char opc;
	Rcli RegCli;
	Rforne RegForne;
	Rprod RegProd;
	Rvendas RegV;
	RvendasProdutos RegVp;
	
	gotoxy(28,3);
	printf("*** Exclusão Fisica ***");
	gotoxy(5,8);
	printf("*** ATENCAO ***");
	gotoxy(5,9);
	printf("*** Para Fazer a exclusao fisica, faca a exclusao logica antes ***");
	getch();
	limpartela();
	gotoxy(5,8);
	printf("Deseja Excluir os Clientes selecionados? S|N :  ");
	if (toupper(getche())=='S')
	{
		FILE *ptrCli = fopen("Cliente.dat","rb");
		FILE *PtrTemp = fopen("TempCli.dat","wb");
		fseek(ptrCli,0,0);
		fread(&RegCli,sizeof(Rcli),1,ptrCli);
		while(!feof(ptrCli))
		
		{
			if (RegCli.status == 1)
				{
				fwrite(&RegCli,sizeof(Rcli),1,PtrTemp);
				}
			fread(&RegCli,sizeof(Rcli),1,ptrCli);
		}
		fclose(ptrCli);
		fclose(PtrTemp);
		remove("Cliente.dat");
		rename("TempCli.dat","Cliente.dat");
		gotoxy(5,9);
		printf("*** CLIENTES EXCLUIDOS ***");
		getche();
	}
	gotoxy(5,10);
	printf("Deseja Excluir os Fornecedores selecionados? S|N :  ");
	if (toupper(getche())=='S')
	{
		FILE *ptrForne = fopen("Fornecedor.dat","rb");
		FILE *PtrTemp = fopen("TempForne.dat","wb");
		fseek(ptrForne,0,0);
		fread(&RegForne,sizeof(Rforne),1,ptrForne);
		while(!feof(ptrForne))
		
		{
			if (RegForne.status == 1)
				{
				fwrite(&RegForne,sizeof(Rforne),1,PtrTemp);
				}
			fread(&RegForne,sizeof(Rforne),1,ptrForne);
		}
		fclose(ptrForne);
		fclose(PtrTemp);
		remove("Fornecedor.dat");
		rename("TempForne.dat","Fornecedor.dat");
		gotoxy(5,11);
		printf("*** FORNECEDOR EXCLUIDOS ***");
		getche();
	}
	gotoxy(5,12);
	printf("Deseja Excluir os Produto selecionados? S|N :  ");
	if (toupper(getche())=='S')
	{
		FILE *ptrProd = fopen("Produtos.dat","rb");
		FILE *PtrTemp = fopen("TempProd.dat","wb");
		fseek(ptrProd,0,0);
		fread(&RegProd,sizeof(Rprod),1,ptrProd);
		while(!feof(ptrProd))
		
		{
			if (RegProd.status == 1)
				{
				fwrite(&RegProd,sizeof(Rprod),1,PtrTemp);
				}
			fread(&RegProd,sizeof(Rprod),1,ptrProd);
		}
		fclose(ptrProd);
		fclose(PtrTemp);
		remove("Produtos.dat");
		rename("TempProd.dat","Produtos.dat");
		gotoxy(5,13);
		printf("*** PEODUTOS EXCLUIDOS ***");
		getche();
	}
	
}

void venda (void)
{
	
	FILE *ptrV = fopen("Vendas.dat","ab+"); // abrindo os arq iniciais
	FILE *ptrCli = fopen("Cliente.dat","rb+");
	FILE *ptrVp = fopen("VendasProd.dat","ab+");
	int qntd=0,poscli,posprod,aux,posBVP,cpf,uni=0;
	int cont=0;
	float totv;
	char opc;
	
	
	Rprod RegProd;
	Rvendas RegVenda;
	Rcli RegCli;
	RvendasProdutos RegVp;

 fseek(ptrV, 0, SEEK_END);
    if (ftell(ptrV) > 0) 
	{
        cont = ftell(ptrV) / sizeof(Rvendas);
    }
	gotoxy(28,3);
	printf("*** Vendas ***");
	gotoxy(5,8);
	printf("CPF do Cliente: ");
	scanf("%ld", &cpf);
	
	while(cpf > 0)
	{
		//RegVenda.TotVenda = 0;
		
		poscli =BuscaCli(ptrCli,cpf); // tem q puxar o reg dele e gravar o valor da compra e a compra
		fseek(ptrCli,poscli,0);
		fread(&RegCli,sizeof(Rcli),1,ptrCli);
		
		if (poscli == -1)  //  nao achou o queridi
		{
			gotoxy(5,10);
			printf("*** CPF NÃO ENCONTRADO ***");
			getch();
		
			limpartela();
			//gotoxy(5,7);
//			printf("Nova Venda? S|N:  ");
//			opc = toupper(getche());
//			if(opc=='S')
//			{
//				limpartela();
//				gotoxy(5,8);
//				printf("CPF do Cliente: ");
//				scanf("%ld", &RegCli.cpf);
//			}
//			else
//			{
//				RegCli.cpf = 0;
//				limpartela();	
//			}
		}
		else
		{
	
			//RegVenda.CpfCli = RegCli.cpf;
			// lendo o cli
					
			gotoxy(5,7);
			printf("Venda: %d",cont+1);
			gotoxy(5,9);
			printf("Data da Venda [dd mm aaaa]: ");
			scanf("%d %d %d",&RegVenda.DVenda.d,&RegVenda.DVenda.m,&RegVenda.DVenda.a);
			// Reg de venda recebe a data 
			
			
			// repetiçãõ para mais de um produto
				
				FILE *ptrProd = fopen("Produtos.dat","rb+");
				
			do
			{
				limpartela();
				gotoxy(5,7);
				printf("Venda: %d",cont+1);
				gotoxy(5,8);
				printf("Codigo do Produto: ");
				scanf("%d",&RegProd.cod);
				
				posprod = BuscaProd(ptrProd,RegProd.cod);
			
				
				// verificar se o prod já foi vendido outras vezes na mesma venda
				
				if(posprod == -1)
				{
					gotoxy(5,10);
					printf("*** PRODUTO NAO ENCONTRADO ***");
					getch();
				}
				else
				{
					fseek(ptrProd,posprod,0);
					fread(&RegProd,sizeof(Rprod),1,ptrProd);
						gotoxy(5,9);
						printf("Produto: %s", RegProd.desc);
						gotoxy(5,10);
						printf("Quantidade Comprada: ");
						scanf("%d",&uni); // qntd indo pra tabela de Venda prod
						qntd = qntd + RegVp.qntd;
						
						// vendo se tem qntd da venda
						if(RegProd.estoque >= uni && uni > 0) // tem prod pra venda 
						{
							// atualizando o arq de  prod
							RegProd.estoque = RegProd.estoque - uni;
							fseek(ptrProd,posprod,0);
							fwrite(&RegProd,sizeof(Rprod),1,ptrProd);
							
							// venda recebe o total da compra
							totv += qntd*RegProd.preco;
							RegVenda.TotVenda =totv; 
							
							//gotoxy(17,23);
	//						printf("%f",RegVenda.TotVenda);
	
							// Venda Prod recebe o cod do prod
							RegVp.CodProd = RegProd.cod;
							// vp recebe  valor uni
							RegVp.ValorUni = RegProd.preco;
							//vp recebe o Cod da Venda
							RegVp.status = 1;
							RegVp.CodVenda = cont +1;
							
							
							// gravando no arq de VP
							fseek(ptrVp,0,SEEK_END);
							fwrite(&RegVp,sizeof(RvendasProdutos),1,ptrVp);
							
								
						}
						else
						{
							gotoxy(5,15);
							
							printf("*** Quantidade Utrapassa o Estoque ***");
							getch();
						}
						
					
				}
				

			 // aqui mais prod	
				gotoxy(5,13);
				printf("Outro Produto? S|N: ");
				opc = toupper(getche());		
			}while( opc=='S');
			
			fclose(ptrProd); //esses fclose ta dando erro  pq porra
			
			fclose(ptrVp);
			
			// cliente recebe o valor da venda e qntd
		RegCli.ValorTotComprado = totv;
		RegCli.qntdCompra = RegCli.qntdCompra +1;
		//gotoxy(5,15);
//		printf("%f",RegCli.ValorTotComprado);
		fseek(ptrCli,poscli,0);
		fwrite(&RegCli,sizeof(Rcli),1,ptrCli);
		fclose(ptrCli);
		
		// gravando o codigo da venda 
		RegVenda.status = 1;
		RegVenda.CodVenda = cont + 1;
		cont ++;
		qntd=0;
		gotoxy(5,15);
		printf("*** Venda Concluida ***");
		// gravando a venda
		fseek(ptrV,0,SEEK_END);
		fwrite(&RegVenda,sizeof(Rvendas),1,ptrV);
		getch();

		}		
		
		// perguntar nova venda
		limpartela();
		gotoxy(5,7);
		printf("Novo Venda? S|N:  ");
		opc = toupper(getche());
		if(opc=='S')
		{
			limpartela();
			gotoxy(5,8);
			printf("CPF do Cliente: ");
			scanf("%ld", &RegCli.cpf);
		}
		else
		{
			cpf = 0;
			limpartela();	
		}

 }
	fclose(ptrV);
}
void NotaFiscal(void) 
{
	int auxcod,i,pos,codigoVenda,posCliente;
	
	Rvendas V;
	Rcli C;
	
	FILE *PtrVenda = fopen("Vendas.dat","rb");
	
	if (PtrVenda == NULL){

		gotoxy(4,8);
		printf("Não há dados!");
		getch();
		
	} else {
	
		gotoxy(5, 7);
		printf("Codigo da Venda (ou 0 para sair): ");
		gotoxy(5, 8);
		scanf("%d", &auxcod);
		
		while(auxcod > 0)
		{
		
		int y=11;
		
		pos = BuscaVenda(PtrVenda, auxcod);
		
		fseek(PtrVenda,pos,0);
		fread(&V,sizeof(Rvendas),1,PtrVenda);
    
	    if (pos != -1) {

	    	
	
			FILE *PtrCli = fopen("Cliente.dat","rb");
	    	
	    	limpartela();
	    	
	    	posCliente = BuscaCli(PtrCli, V.CpfCli);
    
	    	fseek(PtrCli,posCliente,0);
			fread(&C,sizeof(Rcli),1,PtrCli);
		
			gotoxy(27,3);
			printf("*** NOTA FISCAL ***");	
			    	
			gotoxy(5,7);
			printf("Codigo da Venda: %d",V.CodVenda);
			
			gotoxy(50,7);
			printf("Data da Venda: %d/%d/%d\n", V.DVenda);
			
			gotoxy(5,8);
			printf("Nome: %s\n", C.NomeCli);
			
			gotoxy(50,8);
		    printf("CPF: %d\n", C.cpf);
				
			gotoxy(5,9);
			printf("Codigo");
			
			gotoxy(15,9);
			printf("Produto");
			
			gotoxy(35,9);
			printf("QTD");
			
			gotoxy(45,9);
			printf("Valor");
			
			gotoxy(60,9);
			printf("Sub.Total");
			
			
			RvendasProdutos VP;
	
			FILE *PtrVendaProd = fopen("VendasProd.dat","rb");
			
			
			fread(&VP,sizeof(RvendasProdutos),1,PtrVendaProd);
			while (!feof(PtrVendaProd))
			{
			
			    	if (VP.CodVenda == auxcod)
			    	{
				    	Rprod P;
		
						FILE *PtrProd = fopen("Produtos.dat","rb");
				    		
						int posProd = BuscaProd(PtrProd, VP.CodProd);
						
						fseek(PtrProd,posProd,0);
						fread(&P,sizeof(Rprod),1,PtrProd);
							                   
						gotoxy(5, y);
				        printf("%d", VP.CodProd);
				        gotoxy(15, y);
				        printf("%s", P.desc);
				        gotoxy(35, y);
				        printf("%d", VP.qntd);
				        gotoxy(45, y);
				        printf("R$ %.2f", VP.ValorUni);
				        gotoxy(60, y);
				        printf("R$ %.2f", VP.ValorUni * VP.qntd);
				        y++;
						
	    				fclose(PtrProd);
					}
					
					fread(&VP,sizeof(RvendasProdutos),1,PtrVendaProd);
			}
			
			gotoxy(5,y);
			printf("------------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("Total R$ %.2f",V.TotVenda);
			y++;
			gotoxy(5,y);
			printf("------------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			
			fclose(PtrCli);
			fclose(PtrVendaProd);
		}
		else{
			gotoxy(5,10);
			printf("Venda não foi encontrada!");
		}
	    
	    getch();
	
	    limpartela();
	    
	    gotoxy(5, 7);
		printf("Novo código da Venda (ou 0 para sair): ");
		gotoxy(5, 8);
		scanf("%d", &auxcod);
	
		}
		
		fclose(PtrVenda);
	}
}
void RelatorioCli (void)
{
	FILE *ptr = fopen("Cliente.dat","rb+");
	
	Rcli Reg;
	int pos,y=7;
	char opc;
	gotoxy(27,3);
	printf("* Relatorio de Clientes *");	
	
	fread(&Reg,sizeof(Rcli),1,ptr);
	while (!feof(ptr))
	{
	
		if(Reg.status == 1){
		
			gotoxy(5,y);
			printf("-----------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("CPF: %d | Nome: %s | Qntd Comprada: %d | Total: %.2f ",Reg.cpf,Reg.NomeCli,Reg.qntdCompra,Reg.ValorTotComprado);	
			y++;
			if (y>13)
			{
				gotoxy(5,y+1);
				printf("Aperte E para mostrar mais Clientes;");
				opc =toupper(getch());
				if(opc == 'E')
				{
					limpartela();
					y=7;
				}
			}
			
		}
			
			
		fread(&Reg,sizeof(Rcli),1,ptr);
	}
	fclose(ptr);
	getch();
	
}
void RelatorioForne (void)
{
	FILE *ptr = fopen("Fornecedor.dat","rb+");
	
	Rforne Reg;
	int pos,y=7;
	char opc;
	gotoxy(27,3);
	printf("*** Relatorio de Fornecedor ***");	
	
	fread(&Reg,sizeof(Rforne),1,ptr);
	while (!feof(ptr))
	{
	
		if(Reg.status == 1){
		
			gotoxy(5,y);
			printf("-----------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("ID: %d | Nome: %s | Cidade: %s ",Reg.codForne,Reg.nomeForne,Reg.cidadeForne);
			y++;
			if (y>13)
			{
				gotoxy(5,y+1);
				printf("Aperte E para mostrar mais Fornecedor;");
				opc =toupper(getch());
				if(opc == 'E')
				{
					limpartela();
					y=7;
				}
			}
			
		}
		fread(&Reg,sizeof(Rforne),1,ptr);
	}
	fclose(ptr);
	getch();
	
}
void RelatorioProd (void)
{
	FILE *ptr = fopen("Produtos.dat","rb+");

	Rprod Reg;
	int pos,y=7;
	char opc;
	gotoxy(27,3);
	printf("*** Relatorio de Fornecedor ***");	
	
	gotoxy(5,7);
	//printf("Digite o nome do Fornecedor: ");
//	fflush(stdin);
//	gets(Regforne.nomeForne);
	
	fread(&Reg,sizeof(Rprod),1,ptr);
	while (!feof(ptr))
	{
		if(Reg.status == 1 ){
		
			gotoxy(5,y);
			printf("-------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("ID: %d | Nome: %s | Estoque: %d | Preco Uni: %.2f ",Reg.cod,Reg.desc,Reg.estoque,Reg.preco);
			y++;
			gotoxy(5,y);
			printf("Data de validade: %d %d %d | ID Fornecedor: %d ",Reg.validade,Reg.codForne);
			y++;
			if (y>13)
			{
				gotoxy(5,y+1);
				printf("Aperte E para mostrar mais Produtos;");
				opc =toupper(getch());
				if(opc == 'E')
				{
					limpartela();
					y=7;
				}
			}
			
		}
		fread(&Reg,sizeof(Rprod),1,ptr);
	}
	fclose(ptr);
	getch();
	
}
void RelatorioVendas (void)
{
	FILE *ptr = fopen("Vendas.dat","rb+");
	
	
	Rvendas Reg;
	
	int pos,y=7;
	char opc;
	gotoxy(27,3);
	printf("*** Relatorio de Vendas ***");	
	if (ptr==NULL)
	{
		gotoxy(5,7);
		printf("Erro de abertura");
		getch();
	}
	else
	{
	
	fread(&Reg,sizeof(Rvendas),1,ptr);
	while (!feof(ptr))
	{
	
		if(Reg.status == 1){
		
			gotoxy(5,y);
			printf("-------------------------------------------------------------------");
			y++;
			gotoxy(5,y);
			printf("ID: %d | CPF: %ld | Data: %d | Total: %.2f",Reg.CodVenda,Reg.CpfCli,Reg.DVenda,Reg.TotVenda);

			if (y>13)
			{
				gotoxy(5,y+1);
				printf("Aperte E para mostrar mais Vendas;");
				opc =toupper(getch());
				if(opc == 'E')
				{
					limpartela();
					y=7;
				}
			}
			
		}
		fread(&Reg,sizeof(Rvendas),1,ptr);
	}
	fclose(ptr);
}
}
void AlteraCli (void)
{
 FILE *ptr = fopen("Cliente.dat","rb+");
 Rcli Reg;
 int pos;
 gotoxy(27,3);
 printf("*** Alteracao de Funcionarios ***\n");
	if (ptr == NULL)
	{
		printf("\nErro de Abertura!\n");
		limpartela();
			gotoxy(5,12);
			printf("Nova Alteracao ? S|N: ");
			if (toupper(getche())=='S')
			{
				gotoxy(5,7);
				printf("CPF do Cliente: ");
				scanf("%ld",&Reg.cpf);
			}
			else
			{
				Reg.cpf = 0;
				limpartela();
			}
	}
		
	else
	{
		gotoxy(5,7);
		printf("CPF do Cliente: ");
		scanf("%ld",&Reg.cpf);
		while (Reg.cpf>0)
		{
			pos = BuscaCli(ptr,Reg.cpf);
			
			if(pos == -1)
			{
				gotoxy(5,8);
				printf("*** Cliente nao encontrado ***");
				
				// repetição para nova alteração
			}
			else
			{
				fseek(ptr,pos,0);
				fread(&Reg,sizeof(Rcli),1,ptr);
				limpartela();
				gotoxy(5,7);
				printf("*** Detalhe de Registro ***");
				gotoxy(5,9);
				printf("CPF: %d | Nome: %s |Status: %d",Reg.cpf,Reg.NomeCli,Reg.status);
				gotoxy(5,10);
				printf("Qtde comprada: %d | Total: %.2f",Reg.qntdCompra,Reg.ValorTotComprado);
				gotoxy(5,11);
				printf("-----------------------------------------------------------------");
				gotoxy(5,13);
				printf("Alterar? S|N: ");
				if(toupper(getche()) == 'S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Novo CPF: ");
					scanf("%ld",&Reg.cpf);
					gotoxy(5,8);
					printf("Novo Nome: ");
					fflush(stdin);
					gets(Reg.NomeCli);
					
					gotoxy(5,9);
					printf("Confirmar Alteracao? S|N: ");
					if(toupper(getche())=='S')
					{
						fseek(ptr,pos,0);
						fwrite(&Reg,sizeof(Rcli),1,ptr);
						gotoxy(5,11);
						printf("Registro atualizado!!");
						limpartela();
						gotoxy(5,7);
						printf("*** Detalhe de Registro ***");
						gotoxy(5,9);
						printf("CPF: %d | Nome: %s |Status: %d",Reg.cpf,Reg.NomeCli,Reg.status);
						gotoxy(5,10);
						printf("Qtde comprada: %d | Total: %.2f",Reg.qntdCompra,Reg.ValorTotComprado);
						gotoxy(5,11);
						printf("-----------------------------------------------------------------");
						getche();
					}					
				}
				
			}
			gotoxy(5,12);
			printf("Nova Alteracao ? S|N: ");
			if (toupper(getche())=='S')
			{
				gotoxy(5,7);
				printf("CPF do Cliente: ");
				scanf("%ld",&Reg.cpf);
			}
			else
			{
				Reg.cpf = 0;
				limpartela();
			}
		}
		fclose(ptr);
		
	}
 
}

void AlteraProd (void)
{
 FILE *ptr = fopen("Produtos.dat","rb+");
 Rprod Reg;
 int pos,posforne;
 gotoxy(27,3);
 printf("*** Alteracao de Produto ***\n");
	if (ptr == NULL)
	{
		gotoxy(5,7);
		printf("Erro de Abertura!");
		getche();
	}
		
	else
	{
		gotoxy(5,7);
		printf("ID do produto: ");
		scanf("%d",&Reg.cod);
		while (Reg.cod>0)
		{
			pos = BuscaProd(ptr,Reg.cod);
			
			if(pos == -1)
			{
				gotoxy(5,8);
				printf("*** Produto  nao encontrado ***");
				
				gotoxy(5,12);
				printf("Nova Alteracao ? S|N: ");
				if (toupper(getche())=='S')
				{
					gotoxy(5,7);
					printf("ID do produto: ");
					scanf("%d",&Reg.cod);
				}
				else
				{
					Reg.cod = 0;
					limpartela();
				}
				// repetição para nova alteração
			}
			else
			{
				fseek(ptr,pos,0);
				fread(&Reg,sizeof(Rprod),1,ptr);
				limpartela();
				gotoxy(5,7);
				printf("*** Detalhe de Registro ***");
				gotoxy(5,8);
				printf("ID: %d | Nome: %s | Estoque: %d | Preco: %.2f | Status: %d",Reg.cod,Reg.desc,Reg.estoque,Reg.preco,Reg.status);
				gotoxy(5,9);
				printf("Data de validade: %d/%d/%d | ID Fornecedor: %d ",Reg.validade,Reg.codForne);
				gotoxy(5,10);
				printf("-----------------------------------------------------------------");
				gotoxy(5,13);
				printf("Alterar? S|N: ");
				if(toupper(getche()) == 'S')
				{
					// lendo novas info
					limpartela();
					gotoxy(5,7);
					printf("Novo ID: ");
					scanf("%d",&Reg.cod);
					gotoxy(5,8);
					printf("Novo Nome: ");
					fflush(stdin);
					gets(Reg.desc);
					gotoxy(5,9);
					printf("Novo preco: ");
					scanf("%f",&Reg.preco);
					gotoxy(5,10);
					printf("Nova data de Validade: ");
					scanf("%d",&Reg.validade);
					gotoxy(5,11);
					printf("Id novo Fornecedor: ");
					scanf("%d",&Reg.codForne);
					
					FILE *ptrforne = fopen("Fornecedor.dat","rb+");
					
					posforne = BuscaForne(ptrforne,Reg.codForne);
					
					if (posforne == -1)
					{
						gotoxy(5,12);
						printf("*** Fornecedor  nao encontrado ***");
						
						gotoxy(5,13);
						printf("Nova Alteracao ? S|N: ");
						if (toupper(getche())=='S')
						{
							gotoxy(5,7);
							printf("ID do produto: ");
							scanf("%d",&Reg.cod);
						}
						else
						{
							Reg.cod = 0;
							limpartela();
						}
					}
					else
					{
						gotoxy(5,9);
						printf("Confirmar Alteracao? S|N: ");
						if(toupper(getche())=='S')
						{
							fseek(ptr,pos,0);
							fwrite(&Reg,sizeof(Rforne),1,ptr);
							gotoxy(5,11);
							printf("Registro atualizado!!");
							limpartela();
							gotoxy(5,7);
							printf("*** Detalhe de Registro ***");
							gotoxy(5,8);
							printf("ID: %d | Nome: %s | Estoque: %d | Preco: %.2f | Status: %d",Reg.cod,Reg.desc,Reg.estoque,Reg.preco,Reg.status);
							gotoxy(5,9);
							printf("Data de validade: %d/%d/%d | ID Fornecedor: %d ",Reg.validade,Reg.codForne);
							gotoxy(5,10);
							printf("-----------------------------------------------------------------");
							getche();
						}						
					}
					
										
				}
				
			}
			gotoxy(5,12);
			printf("Nova Alteracao ? S|N: ");
			if (toupper(getche())=='S')
			{
				gotoxy(5,7);
				printf("ID do produto: ");
				scanf("%d",&Reg.cod);
			}
			else
			{
				Reg.cod = 0;
				limpartela();
			}
		}
		fclose(ptr);
		
	}
 
}
void AlteraForne (void)
{
 FILE *ptr = fopen("Fornecedor.dat","rb+");
 Rforne Reg;
 int pos;
 gotoxy(27,3);
 printf("*** Alteracao de Fornecedor ***\n");
	if (ptr == NULL)
	{
		printf("\nErro de Abertura!\n");
		limpartela();
			gotoxy(5,12);
		printf("Nova Alteracao ? S|N: ");
			if (toupper(getche())=='S')
			{
				gotoxy(5,7);
				printf("ID do fornecedor: ");
				scanf("%d",&Reg.codForne);
			}
			else
			{
				Reg.codForne = 0;
				limpartela();
			}
	}
		
	else
	{
		gotoxy(5,7);
		printf("ID do fornecedor: ");
		scanf("%d",&Reg.codForne);
		while (Reg.codForne>0)
		{
			pos = BuscaForne(ptr,Reg.codForne);
			
			if(pos == -1)
			{
				gotoxy(5,8);
				printf("*** Fornecedor nao encontrado ***");
				gotoxy(5,9);
				printf("Nova Alteracao ? S|N: ");
				if (toupper(getche())=='S')
				{
					limpartela();
					gotoxy(5,7);
					printf("ID do fornecedor: ");
					scanf("%d",&Reg.codForne);
				}
				else
				{
					Reg.codForne = 0;
					limpartela();
				}
			}
			else
			{
				fseek(ptr,pos,0);
				fread(&Reg,sizeof(Rforne),1,ptr);
				limpartela();
				gotoxy(5,7);
				printf("*** Detalhe de Registro ***");
				gotoxy(5,8);
				printf("ID: %d | Nome: %s | Cidade: %s  ",Reg.codForne,Reg.nomeForne,Reg.cidadeForne);
				gotoxy(5,9);
				printf("-----------------------------------------------------------------");
				gotoxy(5,13);
				printf("Alterar? S|N: ");
				if(toupper(getche()) == 'S')
				{
					limpartela();
					gotoxy(5,7);
					printf("Novo ID: ");
					scanf("%d",&Reg.codForne);
					gotoxy(5,8);
					printf("Novo Nome: ");
					fflush(stdin);
					gets(Reg.nomeForne);
					gotoxy(5,8);
					printf("NoVa Cidade: ");
					fflush(stdin);
					gets(Reg.cidadeForne);
					
					gotoxy(5,9);
					printf("Confirmar Alteracao? S|N: ");
					if(toupper(getche())=='S')
					{
						fseek(ptr,pos,0);
						fwrite(&Reg,sizeof(Rforne),1,ptr);
						gotoxy(5,11);
						printf("Registro atualizado!!");
						limpartela();
						gotoxy(5,7);
						printf("*** Detalhe de Registro ***");
						gotoxy(5,9);
						printf("ID: %d | Nome: %s | Cidade: %s  ",Reg.codForne,Reg.nomeForne,Reg.cidadeForne);
						gotoxy(5,10);
						printf("-----------------------------------------------------------------");
						getche();
					}					
				}
				
			}
			gotoxy(5,12);
			printf("Nova Alteracao ? S|N: ");
			if (toupper(getche())=='S')
			{
				gotoxy(5,7);
				printf("ID do fornecedor: ");
				scanf("%d",&Reg.codForne);
			}
			else
			{
				Reg.codForne = 0;
				limpartela();
			}
		}
		fclose(ptr);
		
	}
 
}
void Aumentopreco (void)
{
	FILE *ptrf = fopen("Fornecedor.dat","rb+");
	FILE *ptrp = fopen("Produtos.dat","rb+");
	
	Rprod Regp;
	Rforne Regf;
	int pos;
	float aum,cal,aux;
	
	gotoxy(27,3);
	printf("*** Aumento de Preco ***");
	 
	gotoxy(5,7);
	printf("Digite o ID do Fornecedor: ");
	scanf("%d",&Regf.codForne);
	
	while(Regf.codForne > 0)
	{
		pos = BuscaForne(ptrf,Regf.codForne);
		if(pos == -1)
		{
			gotoxy(5,9);
			printf("*** FORNECEDOR NAO LOCALIZADO *** ");
			getche();
		}
		else
		{
			gotoxy(5,8);
			printf("valor do aumento: ");
			scanf("%f",&aum);
			fseek(ptrp,0,0);
			fread(&Regp,sizeof(Rprod),1,ptrp);
			while(!feof(ptrp))
			{
				if (Regp.codForne == Regf.codForne)
				{
					aux = Regp.preco;
					cal= aux * aum/100;
					cal = cal +aux;
					Regp.preco=cal;
					gotoxy(5,15);
					printf("%.2f",Regp.preco);
					fwrite(&Regp,sizeof(Rprod),1,ptrp);
				}
				fread(&Regp,sizeof(Rprod),1,ptrp);
			}
	
		}
		gotoxy(5,9);
		printf("Aumento Concluido!!");
		getche();
		limpartela();		
		printf("Novo Aumento ? S|N: ");
			if (toupper(getche())=='S')
			{
				
				gotoxy(5,7);
				printf("Digite o ID do Fornecedor: ");
				scanf("%d",&Regf.codForne);
			}
			else
			{
				Regf.codForne = 0;
				limpartela();
			}	
	}
	fclose(ptrf);
	fclose(ptrp);
}
void inserirdados(void)
{
	FILE *ptrc = fopen("Cliente.dat","ab+");
	FILE *ptrf = fopen("Fornecedor.dat","ab+");
	FILE *ptrp = fopen("Produtos.dat","ab+");
	
	
	Rprod Regp;
	
	
	Regp.cod = 6;
    strcpy(Regp.desc, "Bolacha");
    Regp.estoque = 50;
    Regp.preco = 2.25;
    Regp.validade.d = 10;
    Regp.validade.m = 12;
    Regp.validade.a = 2024;
    Regp.codForne =2525 ;
    Regp.status = 1;
    fseek(ptrp,0,SEEK_END);
	fwrite(&Regp, sizeof(Rprod), 1, ptrp);

    Regp.cod = 7;
    strcpy(Regp.desc, "Leite");
    Regp.estoque = 500;
    Regp.preco = 8;
    Regp.validade.d = 12;
    Regp.validade.m = 1;
    Regp.validade.a = 2025;
    Regp.codForne = 3030;
    Regp.status = 1;
	fseek(ptrp,0,SEEK_END);
	fwrite(&Regp, sizeof(Rprod), 1, ptrp);

    Regp.cod = 8;
    strcpy(Regp.desc, "Feijão");
    Regp.estoque = 30;
    Regp.preco = 4.50;
    Regp.validade.d = 25;
    Regp.validade.m = 9;
    Regp.validade.a = 1515;
    Regp.codForne = 1515;
    Regp.status = 1;
	fseek(ptrp,0,SEEK_END);
	fwrite(&Regp, sizeof(Rprod), 1, ptrp);

    Regp.cod = 9;
    strcpy(Regp.desc, "Macarrão");
    Regp.estoque = 40;
    Regp.preco = 3.00;
    Regp.validade.d = 8;
    Regp.validade.m = 11;
    Regp.validade.a = 2024;
    Regp.codForne = 1515;
    Regp.status = 1;
	fseek(ptrp,0,SEEK_END);
	fwrite(&Regp, sizeof(Rprod), 1, ptrp);

    Regp.cod = 10;
    strcpy(Regp.desc, "Sabonete");
    Regp.estoque = 100;
    Regp.preco = 1.75;
    Regp.validade.d = 10;
    Regp.validade.m = 3;
    Regp.validade.a = 2025;
    Regp.codForne = 1515;
    Regp.status = 1;
	fseek(ptrp,0,SEEK_END);
	fwrite(&Regp, sizeof(Rprod), 1, ptrp);

    fclose(ptrp);
    
    Rcli Regc;
    
    Regc.cpf = 1010;
    strcpy(Regc.NomeCli,"Ruan Caetano");
    Regc.qntdCompra=0;
    Regc.ValorTotComprado=0;
    Regc.status=1;
    fseek(ptrc,0,SEEK_END);
	fwrite(&Regc,sizeof(Rcli), 1, ptrc);
    
    Regc.cpf = 1515;
    strcpy(Regc.NomeCli,"Pedro Joao");
    Regc.qntdCompra=0;
    Regc.ValorTotComprado=0;
    Regc.status=1;
    fseek(ptrc,0,SEEK_END);
	fwrite(&Regc,sizeof(Rcli), 1, ptrc);
    
    fclose(ptrc);
    
    Rforne Regf;
    
    Regf.codForne=1515;
	strcpy(Regf.nomeForne,"Coca-Cola");
	strcpy(Regf.cidadeForne,"Floripa");
	Regf.status = 1;
	fseek(ptrf,0,SEEK_END);
	fwrite(&Regf,sizeof(Rforne), 1, ptrf);
	
	Regf.codForne=2525;
	strcpy(Regf.nomeForne,"Nestle");
	strcpy(Regf.cidadeForne,"Sao paulo");
	Regf.status = 1;
	fseek(ptrf,0,SEEK_END);
	fwrite(&Regf,sizeof(Rforne), 1, ptrf);
	
	fclose(ptrf);
}
int main(void)
{
	int opc,op;
	Formulario();
	 
	 gotoxy(27,3);
	 textcolor(1);
	 printf(" * * * Produtos * * * ");
	 
	 do
	 {

		 gotoxy(4,5);
		 op = menu();
		 switch(op)
		 {
		 	case 1: 
		 		system("cls");
		 		Formulario();
		 		limpartela();
		 		opc=subCad();
		 		switch (opc)
		 		{
			 			case 1:
			 				limpartela();
			 				CadastroForne();
			 				break;
			 			case 2:
			 				limpartela();
			 				CadastroProd();
			 				break;
			 			case 3:
			 				limpartela();
			 				CadastroCli();
			 				break;
			 			
				 }
		 	
		 		break;
		 	case 2: 
		 	system("cls");
		 		Formulario();
		 		limpartela();
		 		opc=subMenu();
		 		switch (opc)
		 		{
		 			do
			 		{
			 			case 1:
			 				limpartela();
			 				Consulforne();
			 				break;
			 			case 2:
			 				limpartela();
			 				ConsulProd();
			 				break;
			 			case 3:
			 				limpartela();
			 				ConsulCli();
			 				break;

					}while(opc != 27);
			 	}
		 		
		 		break;
		 	case 3:
		 		system("cls");
		 		Formulario();
		 		limpartela();
		 		venda();
		 		break;
		 	case 4:
		 		system("cls");
		 		Formulario();
		 			limpartela();
		 			opc=subMenu();
		 			switch (opc)
		 			{
		 				case 1:
		 					limpartela();
		 					ExcLoForne();
		 					break;
		 				case 2:
		 					limpartela();
		 					ExcLoProd();
		 					break;
		 				case 3:
		 					limpartela();
		 					ExcLoCli();
		 					break;
		 			}
		 		break;
		 	case 5:
		 		system("cls");
		 		Formulario();
		 		limpartela();
		 		ExlFisTot();
		 		break;
		 	case 6:
		 		system("cls");
		 		Formulario();
		 		limpartela();
		 		NotaFiscal();
		 		break;
		 	case 7:
		 		system("cls");
		 		Formulario();
				limpartela();
		 		opc = subMenu();
		 		switch (opc)
		 			{
		 				case 1:
		 					limpartela();
		 					RelatorioForne();
		 					break;
		 				case 2:
		 					limpartela();
		 					RelatorioProd();
		 					break;
		 				case 3:
		 					limpartela();
		 					RelatorioCli();
		 					break;
		 				case 4:
			 				limpartela();
			 				RelatorioVendas();
		 			}
		 		break;
		 	case 8:
		 		system("cls");
		 		Formulario();
		 		limpartela();
		 		opc = subCad();
		 		switch (opc)
		 			{
		 				case 1:
		 					limpartela();
		 					AlteraProd();
		 					break;
		 				case 2:
		 					limpartela();
		 					AlteraProd();
		 					break;
		 				case 3:
		 					limpartela();
		 					AlteraCli();
		 		
				 			break;
		 			}
		 		break;
		 	case 9:
		 		system("cls");
		 		Formulario();
		 		limpartela();
		 		Aumentopreco();
		 		break;
		 	case 10:
		 		limpartela();
		 		inserirdados();
		 		break;
		}
	}while(op != 0);
	system("cls");
}


