#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>
#define TFC 20
#define TFPI 20
#define TFP 40
#define TFM 10
//------------------- STRUCT
struct TpCliente {
	char telefone[15],nome[15],endereco[25],cidade[15],cep[10],status;
};
struct TpPizza {
	int cod;
	char descr[15],status;
	float valor;
};
struct TpData {
	int dia,mes,ano;
};
struct TpMoto {
	char cpf[15],telefone[15],nome[15],endereco[25],status;
	struct TpData data;
};
struct TpPedido {
	int numero,cod,situacao;
	char telefone[15],cpf[15],status;
	struct TpData data;
};
struct TpRank{
	int cont;
	char nome[15];
};
//--------------------- FUNÇÔES
//Moldura APP
void Moldura(int CI,int LI,int CF,int LF) {
	// Contorno
	int i;
	textcolor(15);
	gotoxy(CI,LI);
	printf("%c",201);
	gotoxy(CF,LI);
	printf("%c",187);
	gotoxy(CI,LF);
	printf("%c",200);
	gotoxy(CF,LF);
	printf("%c",188);
	for(i=CI+1; i<CF; i++) {
		gotoxy(i,LI);
		printf("%c",205);
		gotoxy(i,LF);
		printf("%c",205);
	}
	for(i=LI+1; i<LF; i++) {
		gotoxy(CI,i);
		printf("%c",186);
		gotoxy(CF,i);
		printf("%c",186);
	}
	// Menu
	textcolor(12);
	gotoxy(2,2);
	printf("%c",201);
	gotoxy(25,2);
	printf("%c",187);
	gotoxy(2,24);
	printf("%c",200);
	gotoxy(25,24);
	printf("%c",188);
	for(i=3; i<25; i++) {
		gotoxy(i,2);
		printf("%c",205);
		gotoxy(i,24);
		printf("%c",205);
	}
	for(i=3; i<24; i++) {
		gotoxy(2,i);
		printf("%c",186);
		gotoxy(25,i);
		printf("%c",186);
	}
	gotoxy(6,3);
	printf("### M E N U ###");
	for(i=3; i<25; i++) {
		gotoxy(i,4);
		printf("%c",205);
	}
	// Nome
	textcolor(12);
	gotoxy(26,2);
	printf("%c",201);
	gotoxy(79,2);
	printf("%c",187);
	gotoxy(26,4);
	printf("%c",200);
	gotoxy(79,4);
	printf("%c",188);
	for(i=27; i<79; i++) {
		gotoxy(i,2);
		printf("%c",205);
		gotoxy(i,4);
		printf("%c",205);
	}
	for(i=3; i<4; i++) {
		gotoxy(26,i);
		printf("%c",186);
		gotoxy(79,i);
		printf("%c",186);
	}
	gotoxy(42,3);
	printf("### P I Z Z A R I A ###");
	// Processo
	textcolor(15);
	gotoxy(26,5);
	printf("%c",201);
	gotoxy(79,5);
	printf("%c",187);
	gotoxy(26,24);
	printf("%c",200);
	gotoxy(79,24);
	printf("%c",188);
	for(i=27; i<79; i++) {
		gotoxy(i,5);
		printf("%c",205);
		gotoxy(i,24);
		printf("%c",205);
	}
	for(i=6; i<24; i++) {
		gotoxy(26,i);
		printf("%c",186);
		gotoxy(79,i);
		printf("%c",186);
	}
	for(i=27; i<79; i++) {
		gotoxy(i,22);
		printf("%c",205);
	}
}
void LimpaTela(void) {
	int i;
	for(i=6; i<22; i++) {
		gotoxy(28,i);
		printf("                                                  ");
	}
}
// ORDENAÇÕES
void OrdenaInserDir(FILE *PtrPizza) //pizza
{
	TpPizza RegPizza;
	TpPizza RegAux;
	int i;
	fseek(PtrPizza, 0,2);
	i = ftell(PtrPizza)/sizeof(TpPizza)-1;
	fseek(PtrPizza,sizeof(TpPizza) * i, 0);
	fread(&RegPizza, sizeof(TpPizza), 1, PtrPizza);
	fseek(PtrPizza,sizeof(TpPizza) * (i-1), 0);
	fread(&RegAux, sizeof(TpPizza), 1, PtrPizza);
	while(i > 0 && RegPizza.cod < RegAux.cod)
	{
		fseek(PtrPizza, sizeof(TpPizza) * i, 0);
		fwrite(&RegAux,sizeof(TpPizza), 1, PtrPizza);
		fseek(PtrPizza,sizeof(TpPizza) * (i-1), 0);
		fwrite(&RegPizza,sizeof(TpPizza), 1,PtrPizza);		
		i--;
		fseek(PtrPizza,sizeof(TpPizza) * i, 0);
		fread(&RegPizza, sizeof(TpPizza), 1, PtrPizza);
		fseek(PtrPizza,sizeof(TpPizza) * (i-1), 0);
		fread(&RegAux, sizeof(TpPizza), 1, PtrPizza);	
	}
}

void OrdenaBubbleSort (FILE *PtrMoto) // Moto
{
	TpMoto RegMoto;
	TpMoto RegAux;
	char AuxCPF[15];
	int i,qtde;
	
	fseek(PtrMoto,0,2);
	qtde = ftell(PtrMoto) / sizeof (TpMoto);
	
	while(qtde >0)
	{
		for(i=0 ; i<qtde-1 ; i++)
		{
			fseek(PtrMoto,i*sizeof(TpMoto),0);
			fread(&RegMoto.cpf,sizeof(TpMoto),1,PtrMoto);
			fseek(PtrMoto,(i+1)*sizeof(TpMoto),0);
			fread(&RegAux.cpf,sizeof(TpMoto),1,PtrMoto);
			if(strcmp(RegMoto.cpf,RegAux.cpf) > 0)
			{
				fseek(PtrMoto,(i+1)*sizeof(TpMoto),0);
				fwrite(&RegMoto.cpf,sizeof(TpMoto),1,PtrMoto);
				fseek(PtrMoto,i*sizeof(TpMoto),0);
				fwrite(&RegAux.cpf,sizeof(TpMoto),1,PtrMoto);
			}
		}
		qtde--;
	}
	
}

void OrdenaSelecDir (FILE *PtrPedido) // Pedido
{
	TpPedido RegPedido;
	TpPedido RegAux;
	int i,maior,TL;
	fseek(PtrPedido,0,2);
	TL = ftell(PtrPedido) / sizeof(TpPedido);
	
	while(TL>0)
	{
		maior = 0;
		for(i=1;i<TL;i++)
		{
			fseek(PtrPedido,maior * sizeof(TpPedido),0);
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
			fseek(PtrPedido,i*sizeof(TpPedido),0);
			fread(&RegAux,sizeof(TpPedido),1,PtrPedido);
			if(RegAux.numero > RegPedido.numero)
				maior = i;
		}
		if(maior < TL -1)
		{
			fseek(PtrPedido,maior*sizeof(TpPedido),0);
			fwrite(&RegAux,sizeof(TpPedido),1,PtrPedido);
			fseek(PtrPedido,(TL-1)*sizeof(TpPedido),0);
			fwrite(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		}
		TL--;
	}
}
// validaçoes
char ValidaCPF (char cpf[15])
{  
	int icpf[12];  
	int i=0, somador=0, digito1, result1, result2, digito2, valor;  
	   
	for(i=0;i<11;i++)  
	{  
		icpf[i]=cpf[i]-48;  
	}    
	  
	for(i=0;i<9;i++)  
	{  
		somador+=icpf[i]*(10-i);  
	}  
	  
	result1=somador%11;  
	  
	if( (result1==0) || (result1==1) )  
	{  
		digito1=0;  
	}  
	  
	else  
	{  
		digito1 = 11-result1;  
	}  
	  
	somador=0;  
	  
	for(i=0;i<10;i++)  
	{  
		somador+=icpf[i]*(11-i);  
	}  
	  
	valor=(somador/11)*11;  
	result2=somador-valor;  
	  
	if( (result2==0) || (result2==1) )  
	{  
		digito2=0;  
	}  
	  
	else  
	{  
		digito2=11-result2;  
	}  
	  
	if((digito1==icpf[9]) && (digito2==icpf[10]))  
		return 1;  /*Valido*/
	else  
		return 0; /*Errado*/
}  
// CLIENTE

int BuscaCliente(FILE *PtrCliente, char AuxTel[15]) // sequencial indexada
{
	TpCliente RegCliente;
	rewind(PtrCliente);
	fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	while(!feof(PtrCliente) && strcmp(AuxTel,RegCliente.telefone)!=0)
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	
	if(!feof(PtrCliente) && RegCliente.status == 'A')
		return ftell(PtrCliente) - sizeof(TpCliente);
	else
		return -1;
}

void CADCliente (void)
{
	textcolor(15);
	TpCliente RegCliente;
	char AuxTel[15];
	int pos;
	FILE *PtrCliente = fopen("Clientes.dat","ab+");
	LimpaTela();
	gotoxy(38,6);
	printf("### CADASTRO DE CLIENTES ###");
	gotoxy(28,8);
	printf("Telefone: ");
	fflush(stdin);
	gets(AuxTel);
	while(strcmp(AuxTel,"\0")!=0)
	{
		pos = BuscaCliente (PtrCliente,AuxTel);
		if(pos==-1)
		{
			fseek(PtrCliente,0,2);
			gotoxy(40,23);
			printf("Cliente nao cadastrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			strcpy(RegCliente.telefone,AuxTel);
			gotoxy(28,9);
			printf("Nome: ");
			fflush(stdin);
			gets(RegCliente.nome);
			gotoxy(28,10);
			printf("Endereco: ");
			fflush(stdin);
			gets(RegCliente.endereco);
			gotoxy(28,11);
			printf("Cidade: ");
			fflush(stdin);
			gets(RegCliente.cidade);
			gotoxy(28,12);
			printf("CEP: ");
			fflush(stdin);
			gets(RegCliente.cep);
			RegCliente.status = 'A';
			gotoxy(40,23);
			printf("Cadastro feito!");
			Sleep(1000);
			gotoxy(40,23);
			printf("                             ");
			fwrite(&RegCliente,sizeof(TpCliente),1,PtrCliente);
		}
		else
		{
			fseek(PtrCliente,pos,0);
			fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
			gotoxy(40,23);
			printf("Cliente ja cadastrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
			gotoxy(28,9);
			printf("Nome: %s",RegCliente.nome);
			gotoxy(28,10);
			printf("Endereco: %s",RegCliente.endereco);
			gotoxy(28,11);
			printf("Cidade: %s",RegCliente.cidade);
			gotoxy(28,12);
			printf("CEP: %s",RegCliente.cep);
			getch();
		}
	LimpaTela();
	gotoxy(38,6);
	printf("### CADASTRO DE CLIENTES ###");
	gotoxy(28,8);
	printf("Telefone: ");
	fflush(stdin);
	gets(AuxTel);
	}
	fclose(PtrCliente);
}

// Pizza

int BuscaPizza (FILE *PtrPizza, int cod) // busca binária
{
	TpPizza RegPizza;
	int inicio=0,meio,fim;
	fseek(PtrPizza,0,2);
	fim = ftell(PtrPizza)/sizeof(TpPizza)-1;
	meio = fim/2;
	fseek(PtrPizza,sizeof(TpPizza)*meio,0);
	fread(&RegPizza, sizeof(TpPizza),1,PtrPizza);
	while(inicio < fim && RegPizza.cod != cod)
	{
		if (RegPizza.cod > cod)
			fim = meio - 1;
		else
			inicio = meio+1;
		meio = (inicio+fim)/2;
		fseek(PtrPizza,sizeof(TpPizza)*meio,0);
		fread(&RegPizza, sizeof(TpPizza),1,PtrPizza);
	}
	if(RegPizza.cod == cod && RegPizza.status == 'A')
		return ftell(PtrPizza) - sizeof(TpPizza);
	else
		return -1;
}

void CADPizza ()
{
	FILE *PtrPizza = fopen("Pizzas.dat","rb+");
	TpPizza RegPizza;
	int pos,AuxPizza;
	textcolor(15);
	LimpaTela();
	gotoxy(41,6);
	printf("### CADASTRO DE PIZZA ###");
	gotoxy(28,8);
	printf("Cod Pizza: ");
	scanf("%d",&AuxPizza);
	while(AuxPizza > 0)
	{
		pos = BuscaPizza(PtrPizza,AuxPizza);
		fseek(PtrPizza,0,2);
		if(pos==-1) 
		{
			gotoxy(40,23);
			printf("Pizza nao cadastrada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			RegPizza.cod= AuxPizza;
			gotoxy(28,9);
			printf("Sabor: ");
			fflush(stdin);
			gets(RegPizza.descr);
			gotoxy(28,10);
			printf("Valor: ");
			scanf("%f",&RegPizza.valor);
			RegPizza.status = 'A';
			fwrite(&RegPizza,sizeof(TpPizza),1,PtrPizza);
			gotoxy(40,23);
			printf("Pizza cadastrada!");
			Sleep(1000);
			gotoxy(40,23);
			printf("                             ");
			OrdenaInserDir(PtrPizza);
		}
		else
		{
			fseek(PtrPizza,pos,0);
			fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
			gotoxy(40,23);
			printf("Pizza ja cadastrada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			gotoxy(28,9);
			printf("Sabor: %s",RegPizza.descr);
			gotoxy(28,10);
			printf("Valor: R$ %.2f",RegPizza.valor);
			getch();
		}
		LimpaTela();
		gotoxy(41,6);
		printf("### CADASTRO DE PIZZA ###");
		gotoxy(28,8);
		printf("Cod Pizza: ");
		scanf("%d",&AuxPizza);
	}
	fclose(PtrPizza);
}

// MOTOBOY

/*int BuscaSentinela (FILE *PtrMoto,char AuxCPF[15]) // busca com sentinela apenas para cadastro
{
	int fim;
	TpMoto RegMoto;	
	strcpy(RegMoto.cpf,AuxCPF);
	RegMoto.status='A';
	fseek(PtrMoto,0,2);
	fwrite(&RegMoto, sizeof(TpMoto), 1, PtrMoto);
	rewind(PtrMoto);
	fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);	
	while(stricmp(RegMoto.cpf, AuxCPF) != 0 || RegMoto.status != 'A') 											
	
	fread(&RegMoto,sizeof(TpMoto),1,PtrMoto); // redirecionar o ponteiro (N vai até fim de arquivo)
	if(!feof(PtrMoto))
	{
		fseek(PtrMoto,0,2);
		fim = ftell(PtrMoto) - sizeof(TpMoto);
		RegMoto.status= 'I';
		fseek(PtrMoto,fim,0);
		fwrite(&RegMoto,sizeof(TpMoto),1,PtrMoto);
		return ftell(PtrMoto) - sizeof(TpMoto);
	}
	else
		return -1;
}*/ 
// A busca funciona no cadastro apenas, quando chamada em outra função, não encontra a posição ou retorna lixo. Tentei mexer no fseek, gravar em cima, nada... Considera um pouco ai :)

int BuscaMoto (FILE *PtrMoto, char AuxCPF[15]) // sequencial indexada
{
	TpMoto RegMoto;
	rewind(PtrMoto);
	fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
	while(!feof(PtrMoto) && strcmp(AuxCPF,RegMoto.cpf)!=0)
		fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
	
	if(!feof(PtrMoto) && RegMoto.status == 'A')
		return ftell(PtrMoto) - sizeof(TpMoto);
	else
		return -1;
}

void CADMoto ()
{
	TpMoto RegMoto;
	FILE *PtrMoto = fopen("Motos.dat","rb+");
	int pos,auxpos;
	char AuxCPF[15];
	textcolor(15);
	LimpaTela();
	gotoxy(38,6);
	printf("### CADASTRO DE MOTOBOY ###");
	gotoxy(28,8);
	printf("CPF: ");
	fflush(stdin);
	gets(AuxCPF);
	while (strcmp(AuxCPF,"\0")!=0)
	{
		if(ValidaCPF(AuxCPF))
		{
			gotoxy(44,23);
			printf("CPF VALIDO!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			pos = BuscaMoto(PtrMoto,AuxCPF);
			if(pos == -1)
			{
				gotoxy(40,23);
				printf("Motoboy nao cadastrado!");
				Sleep(600);
				gotoxy(40,23);
				printf("                             ");
				strcpy(RegMoto.cpf,AuxCPF);
				gotoxy(28,9);
				printf("Nome: ");
				fflush(stdin);
				gets(RegMoto.nome);
				gotoxy(28,10);
				printf("Endereco: ");
				fflush(stdin);
				gets(RegMoto.endereco);
				gotoxy(28,11);
				printf("Telefone: ");
				fflush(stdin);
				gets(RegMoto.telefone);
				gotoxy(28,12);
				printf("Data de Admissao: ");
				scanf("%d %d %d", &RegMoto.data.dia, &RegMoto.data.mes, &RegMoto.data.ano);
				RegMoto.status = 'A';
				gotoxy(28,13);
				fwrite(&RegMoto,sizeof(TpMoto),1,PtrMoto);
				Sleep(1000);
			}
			else
			{
				fseek(PtrMoto,pos,0);
				fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
				gotoxy(40,23);
				printf("Motoboy ja cadastrado!");
				Sleep(600);
				gotoxy(40,23);
				printf("                             ");
				gotoxy(28,9);
				printf("Nome: %s", RegMoto.nome);
				gotoxy(28,10);
				printf("Endereco: %s", RegMoto.endereco);
				gotoxy(28,11);
				printf("Telefone: %s", RegMoto.telefone);
				gotoxy(28,12);
				printf("Data de Admissao: %d/%d/%d", RegMoto.data.dia, RegMoto.data.mes, RegMoto.data.ano);
				gotoxy(28,13);
				getch();
			}
			LimpaTela();
			gotoxy(38,6);
			printf("### CADASTRO DE MOTOBOY ###");
			gotoxy(28,8);
			printf("CPF: ");
			fflush(stdin);
			gets(AuxCPF);
		}
		else
		{
			gotoxy(40,23);
			printf("CPF INVALIDO!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			LimpaTela();
			gotoxy(38,6);
			printf("### CADASTRO DE MOTOBOY ###");
			gotoxy(28,8);
			printf("CPF: ");
			fflush(stdin);
			gets(AuxCPF);
		}
	}
	OrdenaBubbleSort(PtrMoto);
	fclose(PtrMoto);
}

// PEDIDO

int BuscaPedido (FILE *PtrPedido,int AuxPedido) //Busca Sequencial Indexada
{
	TpPedido RegPedido;
	rewind(PtrPedido);

	fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	while(!feof(PtrPedido) && RegPedido.numero != AuxPedido)
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		
	if(RegPedido.numero == AuxPedido)
		return ftell(PtrPedido) - sizeof(TpPedido);
	else
		return -1;
	
}
void CADPedido()
{
	TpPedido RegPedido;
	int AuxPedido,AuxCod,AuxSit,pos;
	char AuxCPF[15],AuxTel[15];
	FILE *PtrPedido = fopen("Pedidos.dat","rb+");
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	FILE *PtrPizza = fopen("Pizzas.dat","rb");
	FILE *PtrMoto = fopen("Motos.dat","rb");
	textcolor(15);
	LimpaTela();
	
	gotoxy(41,6);
	printf("### P E D I D O S ###");
	gotoxy(28,8);
	printf("Numero do pedido: ");
	scanf("%d",&AuxPedido);
	while (AuxPedido >0)
	{
		pos = BuscaPedido(PtrPedido,AuxPedido);
		if(pos==-1) 
		{
			gotoxy(40,23);
			printf("Pedido nao cadastrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			gotoxy(28,9);
			printf("Numero do cliente: ");
			fflush(stdin);
			gets(AuxTel);
			pos= BuscaCliente(PtrCliente,AuxTel);
			if(pos==-1) 
			{
				gotoxy(40,23);
				printf("Cliente nao cadastrado!");
				Sleep(600);
				gotoxy(40,23);
				printf("                             ");
			} 
			else 
			{
				gotoxy(40,23);
				printf("Cliente encontrado!");
				Sleep(600);
				gotoxy(40,23);
				printf("                             ");
				gotoxy(28,10);
				printf("Cod da Pizza: ");
				scanf("%d",&AuxCod);
				pos = BuscaPizza(PtrPizza,AuxCod);
				if(pos==-1) 
				{
					gotoxy(40,23);
					printf("Pizza nao encontrada!");
					Sleep(600);
					gotoxy(40,23);
					printf("                             ");
				} 
				else 
				{
					gotoxy(40,23);
					printf("Pizza encontrada!");
					Sleep(600);
					gotoxy(40,23);
					printf("                             ");
					gotoxy(28,11);
					printf("CPF do Motoboy:");
					fflush(stdin);
					gets(AuxCPF);
					pos = BuscaMoto(PtrMoto,AuxCPF);
					if(pos==-1) 
					{
						gotoxy(40,23);
						printf("Motoboy nao encontrado!");
						Sleep(600);
						gotoxy(40,23);
						printf("                             ");
					} 
					else 
					{
						gotoxy(40,23);
						printf("Motoboy encontrado!");
						Sleep(600);
						gotoxy(40,23);
						printf("                             ");
						RegPedido.numero = AuxPedido;
						RegPedido.cod = AuxCod;
						strcpy(RegPedido.telefone,AuxTel);
						strcpy(RegPedido.cpf,AuxCPF);
						gotoxy(28,12);
						printf("Data do pedido: ");
						scanf("%d %d %d", &RegPedido.data.dia, &RegPedido.data.mes, &RegPedido.data.ano);
						gotoxy(28,14);
						printf("Situacao do pedido:");
						gotoxy(28,15);
						printf("[1] Em preparo");
						gotoxy(28,16);
						printf("[2] A caminho");
						gotoxy(28,17);
						printf("[3] Entregue");
						gotoxy(28,19);
						printf("Situacao: ");
						scanf("%d",&AuxSit);
						RegPedido.situacao=AuxSit;
						RegPedido.status = 'A';
						fwrite(&RegPedido,sizeof(TpPedido),1,PtrPedido);
					}
				}
			}
		} 
		else 
		{
			fseek(PtrPedido,pos,0);
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
			gotoxy(40,23);
			printf("Pedido cadastrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			gotoxy(28,9);
			printf("Numero do cliente: %s",RegPedido.telefone);
			gotoxy(28,10);
			printf("Cod da Pizza: %d",RegPedido.cod);
			gotoxy(28,11);
			printf("CPF Motoboy: %s",RegPedido.cpf);
			gotoxy(28,12);
			printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
			gotoxy(28,13);
			switch(RegPedido.situacao) 
			{
				case 1:
					printf("Situacao: Em preparo");
					break;
				case 2:
					printf("Situacao: A caminho");
					break;
				case 3:
					printf("Situacao: Entregue");
					break;
			}
			getch();
		}
		LimpaTela();
		gotoxy(41,6);
		printf("### P E D I D O S ###");
		gotoxy(28,8);
		printf("Numero do pedido: ");
		scanf("%d",&AuxPedido);
	}
	OrdenaSelecDir(PtrPedido);
	fclose(PtrPedido);
	fclose(PtrPizza);
	fclose(PtrMoto);
	fclose(PtrCliente);
}

// CONSULTA
void ConsultaCliente ()
{
	TpCliente RegCliente;
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	textcolor(15);
	rewind(PtrCliente);
	fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	while(!feof(PtrCliente)) 
	{
		if(RegCliente.status=='A')
		{
			LimpaTela();
			gotoxy(44,6);
			printf("### RELATORIOS ###");
			gotoxy(28,8);
			printf("Telefone: %s",RegCliente.telefone);
			gotoxy(28,9);
			printf("Nome: %s",RegCliente.nome);
			gotoxy(28,10);
			printf("Endereco: %s",RegCliente.endereco);
			gotoxy(28,11);
			printf("Cidade: %s",RegCliente.cidade);
			gotoxy(28,12);
			printf("CEP: %s",RegCliente.cep);
			gotoxy(28,15);
			printf("Pressione Enter para continuar");
		}
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
		getch();
	}
	fclose(PtrCliente);
}
void ConsultaPizza () 
{
	TpPizza RegPizza;
	FILE *PtrPizza = fopen("Pizzas.dat","rb");
	textcolor(15);
	rewind(PtrPizza);
	fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
	while(!feof(PtrPizza)) 
	{
		if(RegPizza.status == 'A')
		{
			LimpaTela();
			gotoxy(44,6);
			printf("### RELATORIOS ###");
			gotoxy(28,8);
			printf("Codigo: %d",RegPizza.cod);
			gotoxy(28,9);
			printf("Sabor: %s",RegPizza.descr);
			gotoxy(28,10);
			printf("Valor: R$ %.2f",RegPizza.valor);
			gotoxy(28,12);
			printf("Pressione Enter para Continuar");
		}
		fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
		getch();
	}
	fclose(PtrPizza);
}
void ConsultaMoto () 
{
	TpMoto RegMoto;
	FILE *PtrMoto = fopen("Motos.dat","rb");
	textcolor(15);
	rewind(PtrMoto);
	fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
	while(!feof(PtrMoto)) 
	{
		if(RegMoto.status == 'A')
		{
			LimpaTela();
			gotoxy(44,6);
			printf("### RELATORIOS ###");
			gotoxy(28,8);
			printf("CPF: %s", RegMoto.cpf);
			gotoxy(28,9);
			printf("Nome: %s", RegMoto.nome);
			gotoxy(28,10);
			printf("Endereco: %s", RegMoto.endereco);
			gotoxy(28,11);
			printf("Telefone: %s", RegMoto.telefone);
			gotoxy(28,12);
			printf("Data de Admissao: %d/%d/%d", RegMoto.data.dia, RegMoto.data.mes, RegMoto.data.ano);
			gotoxy(28,14);
			printf("Pressione Enter para Continuar");
		}
		fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
		getch();
	}
	fclose(PtrMoto);
}
void ConsultaPedido () 
{
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	textcolor(15);
	rewind(PtrPedido);
	fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	while(!feof(PtrPedido))
	{
		if(RegPedido.status == 'A')
		{
			LimpaTela();
			gotoxy(44,6);
			printf("### RELATORIOS ###");
			gotoxy(28,8);
			printf("Numero do pedido: %d",RegPedido.numero);
			gotoxy(28,9);
			printf("Numero do cliente: %s",RegPedido.telefone);
			gotoxy(28,10);
			printf("Cod da Pizza: %d",RegPedido.cod);
			gotoxy(28,11);
			printf("CPF Motoboy: %s",RegPedido.cpf);
			gotoxy(28,12);
			printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
			gotoxy(28,13);
			switch(RegPedido.situacao) 
			{
				case 1:
					printf("Situacao: Em preparo");
					break;
				case 2:
					printf("Situacao: A caminho");
					break;
				case 3:
					printf("Situacao: Entregue");
					break;
			}
			gotoxy(28,15);
			printf("Pressione Enter para Continuar");
		}
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		getch();
	}
	fclose(PtrPedido);
}
char ConsultaPrincipal () {
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### RELATORIOS ###");
	gotoxy(28,9);
	printf("[A] Clientes");
	gotoxy(28,10);
	printf("[B] Pizza");
	gotoxy(28,11);
	printf("[C] Motoboy");
	gotoxy(28,12);
	printf("[D] Pedidos");
	gotoxy(28,14);
	printf("Opcao: ");
	fflush(stdin);
	return toupper(getch());
}

// EXCLUSÃO LÓGICA
void ExcluirCliente () 
{
	TpCliente RegCliente;
	int pos;
	char AuxTel[15],op;
	FILE *PtrCliente = fopen("Clientes.dat","rb+");
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### EXCLUSAO ###");
	gotoxy(28,9);
	printf("Numero do telefone: ");
	fflush(stdin);
	gets(AuxTel);
	gotoxy(28,9);
	printf("                         ");
	pos=BuscaCliente(PtrCliente,AuxTel);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Cliente nao cadastrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	} 
	else 
	{
		fseek(PtrCliente,pos,0);
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
		gotoxy(40,23);
		printf("Cliente encontrado!");
		Sleep(600);
		LimpaTela();
		gotoxy(40,23);
		printf("                           ");
		gotoxy(28,8);
		printf("Telefone: %s",RegCliente.telefone);
		gotoxy(28,9);
		printf("Nome: %s",RegCliente.nome);
		gotoxy(28,10);
		printf("Endereco: %s",RegCliente.endereco);
		gotoxy(28,11);
		printf("Cidade: %s",RegCliente.cidade);
		gotoxy(28,12);
		printf("CEP: %s",RegCliente.cep);
		gotoxy(28,14);
		printf("Deseja continuar? (S/N)");
		gotoxy(28,15);
		printf("Opcao: ");
		fflush(stdin);
		scanf("%c",&op);
		op=toupper(op);
		if(op=='S') 
		{
			if(RegCliente.status == 'A')
			{
				LimpaTela();
				RegCliente.status = 'I';
				fseek(PtrCliente,pos,0);
				fwrite(&RegCliente,sizeof(TpCliente),1,PtrCliente);
				gotoxy(40,23);
				printf("Exclusao realizada!");
				Sleep(600);
				gotoxy(40,23);
				printf("                           ");
			}
			else
			{
				LimpaTela();
				gotoxy(40,23);
				printf("Cliente Inativo!");
				Sleep(600);
				gotoxy(40,23);
				printf("                           ");
			}
		} 
		else 
		{
			gotoxy(40,23);
			printf("Exclusao cancelada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
	}
	fclose(PtrCliente);
}

void ExcluirPizza () 
{
	TpPizza RegPizza;
	int pos,AuxCod;
	char op;
	FILE *PtrPizza = fopen("Pizzas.dat","rb+");
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### EXCLUSAO ###");
	gotoxy(28,9);
	printf("Codigo da pizza: ");
	scanf("%d",&AuxCod);
	gotoxy(28,9);
	printf("                         ");
	pos=BuscaPizza(PtrPizza,AuxCod);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Pizza nao cadastrada!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	} 
	else
	{
		fseek(PtrPizza,pos,0);
		fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
		gotoxy(40,23);
		printf("Pizza encontrada!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
		LimpaTela();
		gotoxy(28,8);
		printf("Cod: %d",RegPizza.cod);
		gotoxy(28,9);
		printf("Sabor: %s",RegPizza.descr);
		gotoxy(28,10);
		printf("Valor: R$ %.2f",RegPizza.valor);
		gotoxy(28,13);
		printf("Deseja continuar? (S/N)");
		gotoxy(28,15);
		printf("Opcao: ");
		fflush(stdin);
		scanf("%c",&op);
		op=toupper(op);
		if(op=='S') 
		{
			if(RegPizza.status == 'A')
			{
				LimpaTela();
				RegPizza.status = 'I';
				fseek(PtrPizza,pos,0);
				fwrite(&RegPizza,sizeof(TpPizza),1,PtrPizza);
				gotoxy(40,23);
				printf("Exclusao realizada!");
				Sleep(600);
				gotoxy(40,23);
				printf("                           ");
			}
			else
			{
				LimpaTela();
				gotoxy(40,23);
				printf("Pizza inativa!");
				Sleep(600);
				gotoxy(40,23);
				printf("                           ");
			}
		} 
		else 
		{
			gotoxy(40,23);
			printf("Exclusao cancelada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
	}
	fclose(PtrPizza);
}

void ExcluirMoto () 
{
	TpMoto RegMoto;
	FILE *PtrMoto = fopen("Motos.dat","rb+");
	int pos;
	char AuxCPF[15],op;
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### EXCLUSAO ###");
	gotoxy(28,9);
	printf("CPF: ");
	fflush(stdin);
	gets(AuxCPF);
	gotoxy(28,9);
	printf("                         ");
	pos=BuscaMoto(PtrMoto,AuxCPF);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Motoboy nao cadastrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	} 
	else 
	{
		fseek(PtrMoto,pos,0);
		fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
		gotoxy(40,23);
		printf("Motoboy encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
		LimpaTela();
		gotoxy(28,8);
		printf("CPF: %s",RegMoto.cpf);
		gotoxy(28,9);
		printf("Nome: %s",RegMoto.nome);
		gotoxy(28,10);
		printf("Endereco: %s",RegMoto.endereco);
		gotoxy(28,11);
		printf("Telefone: %s",RegMoto.telefone);
		gotoxy(28,12);
		printf("Data de Admissao: %d/%d%d",RegMoto.data.dia,RegMoto.data.mes,RegMoto.data.ano);
		gotoxy(28,14);
		printf("Deseja continuar? (S/N)");
		gotoxy(28,15);
		printf("Opcao: ");
		fflush(stdin);
		scanf("%c",&op);
		op=toupper(op);
		if(op=='S') 
		{
			LimpaTela();
			RegMoto.status = 'I';
			fseek(PtrMoto,pos,0);
			fwrite(&RegMoto,sizeof(TpMoto),1,PtrMoto);
			gotoxy(40,23);
			printf("Exclusao realizada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		} 
		else 
		{
			gotoxy(40,23);
			printf("Exclusao cancelada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
	}
	fclose(PtrMoto);
}

void ExcluirPedido () 
{
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb+");
	int pos,AuxPedido;
	char op;
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### EXCLUSAO ###");
	gotoxy(28,9);
	printf("Numero do pedido: ");
	scanf("%d",&AuxPedido);
	gotoxy(28,9);
	printf("                         ");
	pos=BuscaPedido(PtrPedido,AuxPedido);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Pedido nao cadastrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	} 
	else 
	{
		fseek(PtrPedido,pos,0);
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		gotoxy(40,23);
		printf("Pedido encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
		LimpaTela();
		gotoxy(28,8);
		printf("Numero do pedido: %d",RegPedido.numero);
		gotoxy(28,9);
		printf("Codigo da pizza: %d",RegPedido.cod);
		gotoxy(28,10);
		printf("Telefone: %s",RegPedido.telefone);
		gotoxy(28,11);
		printf("CPF do Motoboy: %s",RegPedido.cpf);
		gotoxy(28,12);
		printf("Data do pedido: %d/%d/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
		gotoxy(28,13);
		switch(RegPedido.situacao) 
		{
			case 1:
				printf("Situacao: Em preparo");
				break;
			case 2:
				printf("Situacao: A caminho");
				break;
			case 3:
				printf("Situacao: Entregue");
				break;
		}
		gotoxy(28,15);
		printf("Deseja continuar? (S/N)");
		gotoxy(28,16);
		printf("Opcao: ");
		fflush(stdin);
		scanf("%c",&op);
		op=toupper(op);
		if(op=='S') 
		{
			LimpaTela();
			RegPedido.status = 'I';
			fseek(PtrPedido,pos,0);
			fwrite(&RegPedido,sizeof(TpPedido),1,PtrPedido);
			gotoxy(40,23);
			printf("Exclusao realizada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		} 
		else 
		{
			gotoxy(40,23);
			printf("Exclusao cancelada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
	}
	fclose(PtrPedido);
}

char ExcluirPrincipal () 
{
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### EXCLUSAO ###");
	gotoxy(28,9);
	printf("[A] Clientes");
	gotoxy(28,10);
	printf("[B] Pizza");
	gotoxy(28,11);
	printf("[C] Motoboy");
	gotoxy(28,12);
	printf("[D] Pedidos");
	gotoxy(28,14);
	printf("Opcao: ");
	fflush(stdin);
	return toupper(getch());
}

// EXCLUSÃO FISICA

void ExcFisicaCliente ()
{
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	TpCliente RegCliente;
	textcolor(15);
	LimpaTela();
	
	if(PtrCliente == NULL)
	{
		gotoxy(40,23);
		printf("Erro de abertura!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
	}
	else
	{
		gotoxy(42,6);
		printf("### EXCLUSAO FISICA ###");
		gotoxy(28,9);
		printf("Deseja continuar com a exclusao?");
		gotoxy(28,10);
		printf("SIM // NAO  ( S / N )");
		gotoxy(28,11);
		printf("Opcao: ");
		if (toupper(getch())=='S')
		{
			FILE *PtrTemp = fopen("Temp.dat","wb");
			fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
			while (!feof(PtrCliente))
			{
				if(RegCliente.status=='A')
					fwrite(&RegCliente,sizeof(TpCliente),1,PtrTemp);
				fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
			}
			fclose(PtrCliente);
			fclose(PtrTemp);
			remove("Clientes.dat");
			rename("Temp.dat","Clientes.dat");
			gotoxy(40,23);
			printf("Dados eliminados!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
		else //fechando arquivo
			fclose(PtrCliente);
	}
}

void ExcFisicaPizza ()
{
	FILE *PtrPizza = fopen("Pizzas.dat","rb");
	TpPizza RegPizza;
	textcolor(15);
	LimpaTela();
	
	if(PtrPizza == NULL)
	{
		gotoxy(40,23);
		printf("Erro de abertura!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
	}
	else
	{
		gotoxy(42,6);
		printf("### EXCLUSAO FISICA ###");
		gotoxy(28,9);
		printf("Deseja continuar com a exclusao?");
		gotoxy(28,10);
		printf("SIM // NAO  ( S / N )");
		gotoxy(28,11);
		printf("Opcao: ");
		if (toupper(getch())=='S')
		{
			FILE *PtrTemp = fopen("Temp.dat","wb");
			fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
			while (!feof(PtrPizza))
			{
				if(RegPizza.status=='A')
					fwrite(&RegPizza,sizeof(TpPizza),1,PtrTemp);
				fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
			}
			fclose(PtrPizza);
			fclose(PtrTemp);
			remove("Pizzas.dat");
			rename("Temp.dat","Pizzas.dat");
			gotoxy(40,23);
			printf("Dados eliminados!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
		else //fechando arquivo
			fclose(PtrPizza);
	}
}

void ExcFisicaMoto ()
{
	FILE *PtrMoto = fopen("Motos.dat","rb");
	TpMoto RegMoto;
	textcolor(15);
	LimpaTela();
	
	if(PtrMoto == NULL)
	{
		gotoxy(40,23);
		printf("Erro de abertura!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
	}
	else
	{
		gotoxy(42,6);
		printf("### EXCLUSAO FISICA ###");
		gotoxy(28,9);
		printf("Deseja continuar com a exclusao?");
		gotoxy(28,10);
		printf("SIM // NAO  ( S / N )");
		gotoxy(28,11);
		printf("Opcao: ");
		if (toupper(getch())=='S')
		{
			FILE *PtrTemp = fopen("Temp.dat","wb");
			fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
			while (!feof(PtrMoto))
			{
				if(RegMoto.status=='A')
					fwrite(&RegMoto,sizeof(TpMoto),1,PtrTemp);
				fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
			}
			fclose(PtrMoto);
			fclose(PtrTemp);
			remove("Motos.dat");
			rename("Temp.dat","Motos.dat");
			gotoxy(40,23);
			printf("Dados eliminados!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
		else //fechando arquivo
			fclose(PtrMoto);
	}
}

void ExcFisicaPedido ()
{
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	TpPedido RegPedido;
	textcolor(15);
	LimpaTela();
	
	if(PtrPedido == NULL)
	{
		gotoxy(40,23);
		printf("Erro de abertura!");
		Sleep(600);
		gotoxy(40,23);
		printf("                           ");
	}
	else
	{
		gotoxy(42,6);
		printf("### EXCLUSAO FISICA ###");
		gotoxy(28,9);
		printf("Deseja continuar com a exclusao?");
		gotoxy(28,10);
		printf("SIM // NAO  ( S / N )");
		gotoxy(28,11);
		printf("Opcao: ");
		if (toupper(getch())=='S')
		{
			FILE *PtrTemp = fopen("Temp.dat","wb");
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
			while (!feof(PtrPedido))
			{
				if(RegPedido.status=='A')
					fwrite(&RegPedido,sizeof(TpPedido),1,PtrTemp);
				fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
			}
			fclose(PtrPedido);
			fclose(PtrTemp);
			remove("Pedidos.dat");
			rename("Temp.dat","Pedidos.dat");
			gotoxy(40,23);
			printf("Dados eliminados!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
		else //fechando arquivo
			fclose(PtrPedido);
	}
}

char ExcluirFisicaPrincipal () 
{
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### EXCLUSAO ###");
	gotoxy(28,9);
	printf("[A] Clientes");
	gotoxy(28,10);
	printf("[B] Pizza");
	gotoxy(28,11);
	printf("[C] Motoboy");
	gotoxy(28,12);
	printf("[D] Pedidos");
	gotoxy(28,14);
	printf("Opcao: ");
	fflush(stdin);
	return toupper(getch());
}

// CONSULTA

void Cliente () 
{
	TpCliente RegCliente;
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	int pos;
	char AuxTel[15];
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### CONSULTA ###");
	gotoxy(28,8);
	printf("Digite o numero: ");
	fflush(stdin);
	gets(AuxTel);
	pos = BuscaCliente(PtrCliente,AuxTel);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Numero nao cadastrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	} 
	else 
	{
		fseek(PtrCliente,pos,0);
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
		gotoxy(40,23);
		printf("Numero encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
		gotoxy(28,9);
		printf("Nome: %s",RegCliente.nome);
		gotoxy(28,10);
		printf("Endereco: %s",RegCliente.endereco);
		gotoxy(28,11);
		printf("Cidade: %s",RegCliente.cidade);
		gotoxy(28,12);
		printf("CEP: %s",RegCliente.cep);
		gotoxy(28,13);
		printf("Status : %c",RegCliente.status);
		getch();
	}
	fclose(PtrCliente);
}

void Pizza () 
{
	TpPizza RegPizza;
	FILE *PtrPizza = fopen("Pizzas.dat","rb");
	int pos,AuxCod;
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### CONSULTA ###");
	gotoxy(28,8);
	printf("Digite o cod: ");
	scanf("%d",&AuxCod);
	pos = BuscaPizza(PtrPizza,AuxCod);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Pizza nao cadastrada!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	}
	else
	{
		fseek(PtrPizza,pos,0);
		fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
		gotoxy(40,23);
		printf("Pizza encontrada!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
		gotoxy(28,9);
		printf("Sabor: %s",RegPizza.descr);
		gotoxy(28,10);
		printf("Valor: R$ %.2f",RegPizza.valor);
		gotoxy(28,11);
		printf("Status: %c",RegPizza.status);
		gotoxy(28,12);
		getch();
	}
	fclose(PtrPizza);
}
	
void Moto ()
{
	TpMoto RegMoto;
	FILE *PtrMoto = fopen("Motos.dat","rb");
	int pos;
	char AuxCPF[15];
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### CONSULTA ###");
	gotoxy(28,8);
	printf("Digite o CPF: "); fflush(stdin);
	gets(AuxCPF);
	pos = BuscaMoto(PtrMoto,AuxCPF);
	if(pos==-1)
	{
		gotoxy(40,23);
		printf("Motoboy nao encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	}
	else
	{
		fseek(PtrMoto,pos,0);
		fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
		gotoxy(40,23);
		printf("Motoboy encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
		gotoxy(28,9);
		printf("Nome: %s", RegMoto.nome);
		gotoxy(28,10);
		printf("Endereco: %s", RegMoto.endereco);
		gotoxy(28,11);
		printf("Telefone: %s", RegMoto.telefone);
		gotoxy(28,12);
		printf("Data de Admissao: %d/%d/%d", RegMoto.data.dia, RegMoto.data.mes, RegMoto.data.ano);
		gotoxy(28,13);
		printf("Status: %c",RegMoto.status);
		getch();
	}
	fclose(PtrMoto);
}

void Pedido ()
{
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	int pos,AuxPedido;
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### CONSULTA ###");
	gotoxy(28,8);
	printf("Numero do pedido: ");
	scanf("%d",&AuxPedido);
	pos = BuscaPedido(PtrPedido,AuxPedido);
	if(pos==-1)
	{
		gotoxy(40,23);
		printf("Pedido nao encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	}
	else
	{
		fseek(PtrPedido,pos,0);
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		gotoxy(40,23);
		printf("Pedido encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
		gotoxy(28,9);
		printf("Numero do cliente: %s",RegPedido.telefone);
		gotoxy(28,10);
		printf("Cod da Pizza: %d",RegPedido.cod);
		gotoxy(28,11);
		printf("CPF Motoboy: %s",RegPedido.cpf);
		gotoxy(28,12);
		printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
		gotoxy(28,13);
		switch(RegPedido.situacao) 
		{
			case 1:
				printf("Situacao: Em preparo");
				break;
			case 2:
				printf("Situacao: A caminho");
				break;
			case 3:
				printf("Situacao: Entregue");
				break;
		}
		gotoxy(28,14);
		printf("Status: %c",RegPedido.status);
		getch();
	}
	fclose(PtrPedido);
}

char ExibirConsulta ()
{
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### CONSULTA ###");
	gotoxy(28,9);
	printf("[A] Clientes");
	gotoxy(28,10);
	printf("[B] Pizza");
	gotoxy(28,11);
	printf("[C] Motoboy");
	gotoxy(28,12);
	printf("[D] Pedidos");
	gotoxy(28,14);
	printf("Opcao: ");
	fflush(stdin);
	return toupper(getch());
}

// ALTERAÇÃO
void AlterarCliente ()
{
	TpCliente RegCliente;
	FILE *PtrCliente = fopen("Clientes.dat","rb+");
	int pos;
	char AuxTel[15],op;
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### ALTERACAO ###");
	gotoxy(28,8);
	printf("Digite o numero: ");
	fflush(stdin);
	gets(AuxTel);
	pos = BuscaCliente(PtrCliente,AuxTel);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Numero nao cadastrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	}
	else
	{
		fseek(PtrCliente,pos,0);
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
		gotoxy(40,23);
		printf("Numero encontrado!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
		gotoxy(28,9);
		printf("Nome: %s",RegCliente.nome);
		gotoxy(28,10);
		printf("Endereco: %s",RegCliente.endereco);
		gotoxy(28,11);
		printf("Cidade: %s",RegCliente.cidade);
		gotoxy(28,12);
		printf("CEP: %s",RegCliente.cep);
		gotoxy(28,14);
		printf("Deseja continuar? (S/N)");
		gotoxy(28,15);
		printf("Opcao: ");
		fflush(stdin);
		scanf("%c",&op);
		op=toupper(op);
		if(op=='S')
		{
			fseek(PtrCliente,pos,0);
			LimpaTela();
			gotoxy(44,6);
			printf("### ALTERACAO ###");
			gotoxy(28,8);
			printf("Numero: %s",RegCliente.telefone);
			gotoxy(28,9);
			printf("Nome: ");
			fflush(stdin);
			gets(RegCliente.nome);
			gotoxy(28,10);
			printf("Endereco: ");
			fflush(stdin);
			gets(RegCliente.endereco);
			gotoxy(28,11);
			printf("Cidade: ");
			fflush(stdin);
			gets(RegCliente.cidade);
			gotoxy(28,12);
			printf("CEP: ");
			fflush(stdin);
			gets(RegCliente.cep);
			RegCliente.status = 'A';
			fwrite(&RegCliente,sizeof(TpCliente),1,PtrCliente);
			gotoxy(40,23);
			printf("Alteracao realizada!");
			gotoxy(40,23);
			printf("                             ");
		}
		else
		{
			gotoxy(40,23);
			printf("Alteracao cancelada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
	}
	fclose(PtrCliente);
}

void AlterarPizza ()
{
	TpPizza RegPizza;
	FILE *PtrPizza = fopen("Pizzas.dat","rb+");
	int pos,AuxCod;
	char op;
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### ALTERACAO ###");
	gotoxy(28,8);
	printf("Digite o cod: ");
	scanf("%d",&AuxCod);
	pos = BuscaPizza(PtrPizza,AuxCod);
	if(pos==-1) 
	{
		gotoxy(40,23);
		printf("Pizza nao cadastrada!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
	}
	else
	{
		fseek(PtrPizza,pos,0);
		fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
		gotoxy(40,23);
		printf("Pizza encontrada!");
		Sleep(600);
		gotoxy(40,23);
		printf("                             ");
		gotoxy(28,9);
		printf("Sabor: %s",RegPizza.descr);
		gotoxy(28,10);
		printf("Valor: R$ %.2f",RegPizza.valor);
		gotoxy(28,13);
		printf("Deseja continuar? (S/N)");
		gotoxy(28,15);
		printf("Opcao: ");
		fflush(stdin);
		scanf("%c",&op);
		op=toupper(op);
		if(op=='S')
		{
			fseek(PtrPizza,pos,0);
			LimpaTela();
			gotoxy(44,6);
			printf("### ALTERACAO ###");
			gotoxy(28,8);
			printf("Codigo: %d",RegPizza.cod);
			gotoxy(28,9);
			printf("Sabor: ");
			fflush(stdin);
			gets(RegPizza.descr);
			gotoxy(28,10);
			printf("Valor: ");
			scanf("%f",&RegPizza.valor);
			RegPizza.status = 'A';
			fwrite(&RegPizza,sizeof(TpPizza),1,PtrPizza);
			gotoxy(40,23);
			printf("Alteracao realizada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
		}
		else
		{
			gotoxy(40,23);
			printf("Alteracao cancelada!");
			Sleep(600);
			gotoxy(40,23);
			printf("                           ");
		}
	}
	fclose(PtrPizza);
}

void AlterarMoto ()
	{
		TpMoto RegMoto;
		FILE *PtrMoto = fopen("Motos.dat","rb+");
		int pos;
		char AuxCPF[15],op;
		textcolor(15);
		LimpaTela();
		gotoxy(44,6);
		printf("### ALTERACAO ###");
		gotoxy(28,8);
		printf("Digite o CPF: "); fflush(stdin);
		gets(AuxCPF);
		pos = BuscaMoto(PtrMoto,AuxCPF);
		if(pos==-1) 
		{
			gotoxy(40,23);
			printf("Motoboy nao encontrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
		}
		else
		{
			fseek(PtrMoto,pos,0);
			fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
			LimpaTela();
			gotoxy(44,6);
			printf("### ALTERACAO ###");
			gotoxy(40,23);
			printf("Motoboy encontrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			gotoxy(28,8);
			printf("CPF: %s",RegMoto.cpf);
			gotoxy(28,9);
			printf("Nome: %s", RegMoto.nome);
			gotoxy(28,10);
			printf("Endereco: %s", RegMoto.endereco);
			gotoxy(28,11);
			printf("Telefone: %s", RegMoto.telefone);
			gotoxy(28,12);
			printf("Data de Admissao: %d/%d/%d", RegMoto.data.dia, RegMoto.data.mes, RegMoto.data.ano);
			gotoxy(28,14);
			printf("Deseja continuar? (S/N)");
			gotoxy(28,15);
			printf("Opcao: ");
			fflush(stdin);
			scanf("%c",&op);
			op=toupper(op);
			if(op=='S')
			{
				fseek(PtrMoto,pos,0);
				LimpaTela();
				gotoxy(28,8);
				printf("CPF: %s",RegMoto.cpf);
				gotoxy(28,9);
				printf("Nome: ");
				fflush(stdin);
				gets(RegMoto.nome);
				gotoxy(28,10);
				printf("Endereco: ");
				fflush(stdin);
				gets(RegMoto.endereco);
				gotoxy(28,11);
				printf("Telefone: ");
				fflush(stdin);
				gets(RegMoto.telefone);
				gotoxy(28,12);
				printf("Data de Admissao: ");
				scanf("%d %d %d", &RegMoto.data.dia, &RegMoto.data.mes, &RegMoto.data.ano);
				RegMoto.status = 'A';
				fwrite(&RegMoto,sizeof(TpMoto),1,PtrMoto);
				gotoxy(40,23);
				printf("Alteracao realizada!");
				Sleep(600);
				gotoxy(40,23);
				printf("                             ");
			}
			else
			{
				gotoxy(40,23);
				printf("Alteracao cancelada!");
				Sleep(600);
				gotoxy(40,23);
				printf("                           ");
			}
		}
		fclose(PtrMoto);
	}

void AlterarPedido ()
	{
		TpPedido RegPedido;
		FILE *PtrCliente = fopen("Clientes.dat","rb");
		FILE *PtrPizza = fopen("Pizzas.dat","rb");
		FILE *PtrMoto = fopen("Motos.dat","rb");
		FILE *PtrPedido = fopen("Pedidos.dat","rb+");
		int AuxPedido,AuxCod,AuxSit,pos,posi;
		char op,AuxNum[15],AuxCPF[15];
		textcolor(15);
		LimpaTela();
		gotoxy(41,6);
		printf("### ALTERACAO ###");
		gotoxy(28,8);
		printf("Numero do pedido: ");
		scanf("%d",&AuxPedido);
		posi = BuscaPedido(PtrPedido,AuxPedido);
		if(posi==-1)
		{
			gotoxy(40,23);
			printf("Pedido nao encontrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
		}
		else
		{
			fseek(PtrPedido,posi,0);
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
			gotoxy(41,6);
			printf("### ALTERACAO ###");
			gotoxy(40,23);
			printf("Pedido encontrado!");
			Sleep(600);
			gotoxy(40,23);
			printf("                             ");
			gotoxy(28,9);
			printf("Numero do cliente: %s",RegPedido.telefone);
			gotoxy(28,10);
			printf("Cod da Pizza: %d",RegPedido.cod);
			gotoxy(28,11);
			printf("CPF Motoboy: %s",RegPedido.cpf);
			gotoxy(28,12);
			printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
			gotoxy(28,13);
			switch(RegPedido.situacao)
			{
				case 1:
					printf("Situacao: Em preparo");
					break;
				case 2:
					printf("Situacao: A caminho");
					break;
				case 3:
					printf("Situacao: Entregue");
					break;
			}
			gotoxy(28,15);
			printf("Deseja continuar? (S/N)");
			gotoxy(28,16);
			printf("Opcao: ");
			fflush(stdin);
			scanf("%c",&op);
			op=toupper(op);
			if(op=='S')
			{
				fseek(PtrPedido,posi,0);
				LimpaTela();
				gotoxy(28,8);
				printf("Numero do pedido: %d",RegPedido.numero);
				gotoxy(28,9);
				printf("Numero do cliente: ");
				fflush(stdin);
				gets(AuxNum);
				pos= BuscaCliente(PtrCliente,AuxNum);
				if(pos==-1) 
				{
					gotoxy(40,23);
					printf("Cliente nao cadastrado!");
					Sleep(600);
					gotoxy(40,23);
					printf("                             ");
				} 
				else 
				{
					gotoxy(40,23);
					printf("Cliente encontrado!");
					Sleep(600);
					gotoxy(40,23);
					printf("                             ");
					gotoxy(28,10);
					printf("Cod da Pizza: ");
					scanf("%d",&AuxCod);
					pos = BuscaPizza(PtrCliente,AuxCod);
					if(pos==-1)
					{
						gotoxy(40,23);
						printf("Pizza nao encontrada!");
						Sleep(600);
						gotoxy(40,23);
						printf("                             ");
					} 
					else
					{
						gotoxy(40,23);
						printf("Pizza encontrada!");
						Sleep(600);
						gotoxy(40,23);
						printf("                             ");
						gotoxy(28,11);
						printf("CPF do Motoboy:");
						fflush(stdin);
						gets(AuxCPF);
						pos = BuscaMoto(PtrMoto,AuxCPF);
						if(pos==-1)
						{
							gotoxy(40,23);
							printf("Motoboy nao encontrado!");
							Sleep(600);
							gotoxy(40,23);
							printf("                             ");
						} 
						else 
						{
							gotoxy(40,23);
							printf("Motoboy encontrado!");
							Sleep(600);
							gotoxy(40,23);
							printf("                             ");
							RegPedido.numero = AuxPedido;
							RegPedido.cod = AuxCod;
							strcpy(RegPedido.telefone,AuxNum);
							strcpy(RegPedido.cpf,AuxCPF);
							gotoxy(28,12);
							printf("Data do pedido: ");
							scanf("%d %d %d", &RegPedido.data.dia, &RegPedido.data.mes, &RegPedido.data.ano);
							gotoxy(28,14);
							printf("Situacao do pedido:");
							gotoxy(28,15);
							printf("[1] Em preparo");
							gotoxy(28,16);
							printf("[2] A caminho");
							gotoxy(28,17);
							printf("[3] Entregue");
							gotoxy(28,19);
							printf("Situacao: ");
							scanf("%d",&AuxSit);
							RegPedido.situacao=AuxSit;
							RegPedido.status = 'A';
							fwrite(&RegPedido,sizeof(TpPedido),1,PtrPedido);
							gotoxy(40,23);
							printf("Alteracao realizada!");
							Sleep(600);
							gotoxy(40,23);
							printf("                             ");
						}	
					}
				}
			}
			else
			{
				gotoxy(40,23);
				printf("Alteracao cancelada!");
				Sleep(600);
				gotoxy(40,23);
				printf("                           ");
			}
		}	
		fclose(PtrCliente);
		fclose(PtrPizza);
		fclose(PtrMoto);
		fclose(PtrPedido);
	}
	
char AlterarPrincipal()	
{
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### CONSULTA ###");
	gotoxy(28,9);
	printf("[A] Clientes");
	gotoxy(28,10);
	printf("[B] Pizza");
	gotoxy(28,11);
	printf("[C] Motoboy");
	gotoxy(28,12);
	printf("[D] Pedidos");
	gotoxy(28,14);
	printf("Opcao: ");
	fflush(stdin);
	return toupper(getch());
	}

// RELATORIOS DEMAIS

void UsuarioLetra ()
{
	TpCliente RegCliente;
	char Letra;
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	textcolor(15);
	LimpaTela();
	gotoxy(39,6);
	printf("### BUSCA POR LETRA ###");
	gotoxy(28,8);
	printf("Letra desejada: ");
	scanf("%c",&Letra);
	fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	while(!feof(PtrCliente))
	{
		if(toupper(Letra) == toupper(RegCliente.nome[0]))
		{
			LimpaTela();
			gotoxy(39,6);
			printf("### BUSCA POR LETRA ###");
			gotoxy(28,9);
			printf("Nome: %s",RegCliente.nome);
			gotoxy(28,10);
			printf("Endereco: %s",RegCliente.endereco);
			gotoxy(28,11);
			printf("Cidade: %s",RegCliente.cidade);
			gotoxy(28,12);
			printf("CEP: %s",RegCliente.cep);
			gotoxy(28,13);
			printf("Status : %c",RegCliente.status);
			getch();
		}
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	}
	fclose(PtrCliente);
}

void UsuarioTrecho ()
{
	int i=0;
	TpCliente RegCliente;
	char Trecho[15];
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	textcolor(15);
	LimpaTela();
	gotoxy(39,6);
	printf("### BUSCA POR TRECHO ###");
	gotoxy(28,8);
	printf("Trecho desejado: ");
	fflush(stdin);
	gets(Trecho);
	fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	while(!feof(PtrCliente))
	{
		while(Trecho[i] != '\0' && toupper(Trecho[i])== toupper(RegCliente.nome[i]))
			i++;
			
		if(Trecho[i]=='\0' && RegCliente.status == 'A')
		{
			LimpaTela();
			gotoxy(39,6);
			printf("### BUSCA POR TRECHO ###");
			gotoxy(28,9);
			printf("Nome: %s",RegCliente.nome);
			gotoxy(28,10);
			printf("Endereco: %s",RegCliente.endereco);
			gotoxy(28,11);
			printf("Cidade: %s",RegCliente.cidade);
			gotoxy(28,12);
			printf("CEP: %s",RegCliente.cep);
			gotoxy(28,13);
			printf("Status : %c",RegCliente.status);
			getch();
		}
		i=0;
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	}
	fclose(PtrCliente);
}
void RelAndamento ()
{
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	rewind(PtrPedido);
	fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	while(!feof(PtrPedido))
	{
		if(RegPedido.situacao == 1)
		{
			LimpaTela();
			textcolor(15);
			gotoxy(39,6);
			printf("### EM PREPARO ###");
			gotoxy(28,9);
			gotoxy(28,8);
			printf("Numero do pedido: %d",RegPedido.numero);
			gotoxy(28,9);
			printf("Numero do cliente: %s",RegPedido.telefone);
			gotoxy(28,10);
			printf("Cod da Pizza: %d",RegPedido.cod);
			gotoxy(28,11);
			printf("CPF Motoboy: %s",RegPedido.cpf);
			gotoxy(28,12);
			printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
			gotoxy(28,13);
			switch(RegPedido.situacao)
			{
				case 1:
					printf("Situacao: Em preparo");
					break;
				case 2:
					printf("Situacao: A caminho");
					break;
				case 3:
					printf("Situacao: Entregue");
					break;
			}
			getch();
		}
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	}
	fclose(PtrPedido);	
}

void RelCaminho ()
{
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	rewind(PtrPedido);
	fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	while(!feof(PtrPedido))
	{
		if(RegPedido.situacao == 2)
		{
			LimpaTela();
			textcolor(15);
			gotoxy(39,6);
			printf("### A CAMINHO ###");
			gotoxy(28,8);
			printf("Numero do pedido: %d",RegPedido.numero);
			gotoxy(28,9);
			printf("Numero do cliente: %s",RegPedido.telefone);
			gotoxy(28,10);
			printf("Cod da Pizza: %d",RegPedido.cod);
			gotoxy(28,11);
			printf("CPF Motoboy: %s",RegPedido.cpf);
			gotoxy(28,12);
			printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
			gotoxy(28,13);
			switch(RegPedido.situacao)
			{
				case 1:
					printf("Situacao: Em preparo");
					break;
				case 2:
					printf("Situacao: A caminho");
					break;
				case 3:
					printf("Situacao: Entregue");
					break;
			}
			getch();
		}
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	}
	fclose(PtrPedido);	
}

void RelEntregue ()
{
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	rewind(PtrPedido);
	fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	while(!feof(PtrPedido))
	{
		if(RegPedido.situacao == 3)
		{
			LimpaTela();
			textcolor(15);
			gotoxy(39,6);
			printf("### ENTREGUE ###");
			gotoxy(28,8);
			printf("Numero do pedido: %d",RegPedido.numero);
			gotoxy(28,9);
			printf("Numero do cliente: %s",RegPedido.telefone);
			gotoxy(28,10);
			printf("Cod da Pizza: %d",RegPedido.cod);
			gotoxy(28,11);
			printf("CPF Motoboy: %s",RegPedido.cpf);
			gotoxy(28,12);
			printf("Data do pedido: %d/%d%/%d",RegPedido.data.dia,RegPedido.data.mes,RegPedido.data.ano);
			gotoxy(28,13);
			switch(RegPedido.situacao)
			{
				case 1:
					printf("Situacao: Em preparo");
					break;
				case 2:
					printf("Situacao: A caminho");
					break;
				case 3:
					printf("Situacao: Entregue");
					break;
			}
			getch();
		}
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
	}
	fclose(PtrPedido);	
}
char RelatoriosPizza () 	
{
	textcolor(15);
	LimpaTela();
	gotoxy(44,6);
	printf("### RELATORIOS ###");
	gotoxy(28,9);
	printf("[A] Pizzas em andamento");
	gotoxy(28,10);
	printf("[B] Pizzas a caminho");
	gotoxy(28,11);
	printf("[C] Pizzas entregue");
	gotoxy(28,16);
	printf("Opcao: ");
	return toupper(getch());
}

void RelGasto ()
{
	TpCliente RegCliente;
	FILE *PtrCliente = fopen("Clientes.dat","rb");
	TpPedido RegPedido;
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	TpPizza RegPizza;
	FILE *PtrPizza = fopen("Pizzas.dat","rb");
	int ret,linha=9,pos,aux;
	float valor=0;
	textcolor(15);
	LimpaTela();
	rewind(PtrCliente);
	fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	while(!feof(PtrCliente))
	{
		LimpaTela();
		gotoxy(40,6);
		printf("### GASTO POR CLIENTE ###");
		gotoxy(28,8);
		printf("Cliente - %s:",RegCliente.nome);
		rewind(PtrPedido);
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		while(!feof(PtrPedido))
		{
			ret = strcmp (RegCliente.telefone,RegPedido.telefone);
			if(ret==0)
			{
				aux= RegPedido.cod;
				pos=BuscaPizza(PtrPizza,aux);
				fseek(PtrPizza,pos,0);
				fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
				gotoxy(28,linha);
				printf("Pizza: %s",RegPizza.descr);
				linha++;
				valor=valor + RegPizza.valor;
			}
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		}
		gotoxy(28,15);
		printf("Valor total: %.2f",valor);
		getch();
		valor=0;
		linha=9;
		fread(&RegCliente,sizeof(TpCliente),1,PtrCliente);
	}
	fclose(PtrCliente);
	fclose(PtrPedido);
	fclose(PtrPizza);
}

void OrdenaRank (FILE *PtrRank) // rank
{
	TpRank RegRank;
	TpRank RegAux;
	int i,maior,TL;
	fseek(PtrRank,0,2);
	TL = ftell(PtrRank) / sizeof(TpRank);
	
	while(TL>0)
	{
		maior = 0;
		for(i=1;i<TL;i++)
		{
			fseek(PtrRank,maior * sizeof(TpRank),0);
			fread(&RegRank,sizeof(TpRank),1,PtrRank);
			fseek(PtrRank,i*sizeof(TpRank),0);
			fread(&RegAux,sizeof(TpRank),1,PtrRank);
			if(RegAux.cont < RegRank.cont)
				maior = i;
		}
		if(maior < TL -1)
		{
			fseek(PtrRank,maior*sizeof(TpRank),0);
			fwrite(&RegAux,sizeof(TpRank),1,PtrRank);
			fseek(PtrRank,(TL-1)*sizeof(TpRank),0);
			fwrite(&RegRank,sizeof(TpRank),1,PtrRank);
		}
		TL--;
	}
}

void RankPizza ()
{
	FILE *PtrRank = fopen("Rank.dat","rb+");
	FILE *PtrPizza = fopen("Pizzas.dat","rb");
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	TpRank RegRank;
	TpPedido RegPedido;
	TpPizza RegPizza;
	int cont=0,linha=8,i=1;
	textcolor(15);
	rewind(PtrPizza);
	fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
	while(!feof(PtrPizza))
	{
		rewind(PtrPedido);
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		while(!feof(PtrPedido))
		{
			if(RegPizza.cod == RegPedido.cod)
				cont++;
				
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);	
		}
		RegRank.cont = cont;
		strcpy(RegRank.nome,RegPizza.descr);
		fwrite(&RegRank,sizeof(TpRank),1,PtrRank);
		
		cont=0;
		fread(&RegPizza,sizeof(TpPizza),1,PtrPizza);
	}
	OrdenaRank(PtrRank);
	rewind(PtrRank);
	fread(&RegRank,sizeof(TpRank),1,PtrRank);
	LimpaTela();
	gotoxy(38,6);
	printf("### RANKING DE PIZZA ###");
	while(!feof(PtrRank))
	{
		gotoxy(28,linha);
		printf("TOP %d - Pizza: %s || Quantidade : %d",i,RegRank.nome,RegRank.cont);
		fread(&RegRank,sizeof(TpRank),1,PtrRank);
		linha++;
		i++;
	}
	getch();
	fclose(PtrRank);
	fclose(PtrPedido);
	fclose(PtrPizza);
}

void MotoData ()
{
	TpMoto RegMoto;
	TpPedido RegPedido;
	FILE *PtrMoto = fopen("Motos.dat","rb");
	FILE *PtrPedido = fopen("Pedidos.dat","rb");
	int diaI,mesI,anoI,diaF,mesF,anoF,cont=0;
	textcolor(15);
	LimpaTela();
	gotoxy(38,6);
	printf("### ENTREGAS POR DATA ###");
	gotoxy(28,8);
	printf("Digite a data inicial: ");
	scanf("%d %d %d",&diaI, &mesI, &anoI);
	gotoxy(28,9);
	printf("Digite a data final: ");
	scanf("%d %d %d",&diaF, &mesF, &anoF);
	
	rewind(PtrMoto);
	fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
	while(!feof(PtrMoto))
	{
		rewind(PtrPedido);
		fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		while(!feof(PtrPedido))
		{
			if(RegPedido.data.ano >= anoI && RegPedido.data.mes >= mesI && RegPedido.data.dia >= diaI && RegPedido.data.ano <= anoF && RegPedido.data.mes <= mesF && RegPedido.data.dia <= diaF)
			{
				if(strcmp(RegPedido.cpf,RegMoto.cpf)==0)
					cont++;
			}
			fread(&RegPedido,sizeof(TpPedido),1,PtrPedido);
		}
		LimpaTela();
		gotoxy(38,6);
		printf("### ENTREGAS POR DATA ###");
		gotoxy(28,8);
		printf("Motoboy: %s",RegMoto.nome);
		gotoxy(28,9);
		printf("CPF: %s",RegMoto.cpf);
		gotoxy(28,10);
		printf("Quantidade de entregas: %d",cont);
		getch();
		cont=0;
		fread(&RegMoto,sizeof(TpMoto),1,PtrMoto);
	}
	
}
// MENU E EXECUTAR
char Menu (void)
{
	textcolor(12);
	gotoxy(3,5);
	printf("[A]Cadastro Clientes");
	gotoxy(3,6);
	printf("[B]Cadastro Pizzas");
	gotoxy(3,7);
	printf("[C]Cadastro Motoboy");
	gotoxy(3,8);
	printf("[D]Cadastro Pedido");
	gotoxy(3,9);
	printf("[E]Relatorios");
	gotoxy(3,10);
	printf("[F]Exclusao Logica");
	gotoxy(3,11);
	printf("[G]Exclusao Fisica");
	gotoxy(3,12);
	printf("[H]Consulta");
	gotoxy(3,13);
	printf("[I]Alterar Dados");
	gotoxy(3,14);
	printf("[J]Usuario Letra");
	gotoxy(3,15);
	printf("[K]Status Pizza");
	gotoxy(3,16);
	printf("[L]Gasto Cliente");
	gotoxy(3,17);
	printf("[M]Usuario Trecho");
	gotoxy(3,18);
	printf("[N]Ranking Pizza");
	gotoxy(3,19);
	printf("[O]Entregas Data");
	gotoxy(3,22);
	printf("[ESC]Sair");
	gotoxy(3,23);
	printf("Opcao: ");


	return toupper(getch());
}

void VerificaArquivo ()
{
	FILE *PtrCliente = fopen("Clientes.dat","ab");
	FILE *PtrPizza = fopen("Pizzas.dat","ab");
	FILE *PtrMoto = fopen("Motos.dat","ab");
	FILE *PtrPedido = fopen("Pedidos.dat","ab");
	FILE *PtrRank = fopen("Rank.dat","ab");
	fclose(PtrCliente);
	fclose(PtrPizza);
	fclose(PtrMoto);
	fclose(PtrPedido);
	fclose(PtrRank);
}
void Executar (void) 
{
	VerificaArquivo();
	Moldura(1,1,80,25);
	char op,aux;
	srand(time(NULL));
	do {
		LimpaTela();
		op=Menu();
		switch(op) 
		{
			case 'A':
				CADCliente();
				break;

			case 'B':
				CADPizza();	
				break;

			case 'C':
				CADMoto();
				break;

			case 'D':
				CADPedido();
				break;
			
			case 'E':
				aux=ConsultaPrincipal();
				switch(aux) {
					case 'A':
						ConsultaCliente();
						break;

					case 'B':
						ConsultaPizza();
						break;

					case 'C':
						ConsultaMoto();
						break;

					case 'D':
						ConsultaPedido();
						break;
				}
				break;
			
			case 'F':
				aux=ExcluirPrincipal();
				switch(aux) 
				{
					case 'A':
						ExcluirCliente();
						break;

					case 'B':
						ExcluirPizza();
						break;

					case 'C':
						ExcluirMoto();
						break;

					case 'D':
						ExcluirPedido();
						break;
				}
				break;
				
			case 'G':
				aux=ExcluirFisicaPrincipal();
				switch(aux) 
				{
					case 'A':
						ExcFisicaCliente();
						break;

					case 'B':
						ExcFisicaPizza();
						break;

					case 'C':
						ExcFisicaMoto();
						break;

					case 'D':
						ExcFisicaPedido();
						break;
				}
				break;
			
			case 'H': 
				aux=ExibirConsulta();
				switch(aux)
				{
					case 'A':
						Cliente();
					break;

					case 'B':
						Pizza();
					break;
	
					case 'C':
						Moto();
					break;
		
					case 'D':
						Pedido();
					break;
				}
				break;
			
			case 'I':
				aux=AlterarPrincipal();
				switch(aux)
				{
					case 'A':
						AlterarCliente();
					break;

					case 'B':
						AlterarPizza();
					break;
	
					case 'C':
						AlterarMoto();
					break;
		
					case 'D':
						AlterarPedido();
					break;
				}
				break;
			
			case 'J':
				UsuarioLetra();
				break;
				
			case 'K':
				aux=RelatoriosPizza();
				switch(aux)
				{
					case 'A':
						RelAndamento();
					break;

					case 'B':
						RelCaminho();
					break;
	
					case 'C':
						RelEntregue();
					break;
				}
				break;
			
			case 'L':
				RelGasto();
				break;
				
			case 'M':
				UsuarioTrecho ();
				break;
				
			case 'N':
				RankPizza();
				break;
				
			case 'O':
				MotoData();
				break;
		}
	} while(op!=27);
	gotoxy(80,25);
	printf("\n\n");
}
int main()
{
	Executar();
}
