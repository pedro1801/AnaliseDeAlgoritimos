#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <set>
#define max x
using namespace std;

struct registro
{
    int chave;
    char nome[50];
};
void inserirauto(struct registro vet[], int max);
void inserir(struct registro vet[], int max);
void imprimir(struct registro vet[], int max);
void bubblesort(struct registro vet[], int max);
void buscaLinear(struct registro vetor[], int tam, int chave);
int buscaBinaria(struct registro vetor[], int tamanho, int chave);
void buscaNome(struct registro vet[], int max, char elem[50]);
void buscaLinearOrd(struct registro vetor[], int tamanho, int chave);
void IntercalaDoido(struct registro vetor[], int tamanho);
int partition(struct registro vetor[], int start, int end);
void quickSort(struct registro vetor[], int start, int end);
void Intercala(struct registro vetor[], int p, int q, int r);
void mergeSort(struct registro vetor[], int p, int r);

int main()
{
    int x, op, chavebusca;
    char nomebusca[50];
    cout << "Informe o tamanho da estrutura: ";
    cin >> x;
    struct registro *vet = (struct registro *)malloc(x * sizeof(struct registro));
    op = -1;
    while (op != 0)
    {
        cout << "0 - Finalizar\n1 - Inserir Automaticamente\n2 - Inserir\n3 - Imprimir\n4 - Buscar chave(Busca Binaria)\n5 - Buscar nome\n6 - Ordenar\n7 - Buscar chave(Busca Linear)\n8 - Buscar chave(Busca Linear Ordenada)\n9 - Max Elemento\n10 - Intercala\n";
        cout << "Escolha a sua opcao:";
        cin >> op;
        switch (op)
        {
        case 1:
            inserirauto(vet, x);
            system("cls");
            break;
        case 2:
            inserir(vet, x);
            system("cls");
            break;
        case 3:
            imprimir(vet, x);
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "Informe a chave a ser buscada:";
            cin >> chavebusca;
            bubblesort(vet, x);
            system("cls");
            chavebusca = buscaBinaria(vet, x, chavebusca);
            cout << "Nome: " << vet[chavebusca].nome << " Chave: " << vet[chavebusca].chave << endl;
            system("pause");
            system("cls");
            break;
        case 5:
            cout << "Informe o nome a ser buscado: ";
            cin >> nomebusca;
            buscaNome(vet, x, nomebusca);
            break;
        case 6:
            //quickSort(vet, 0, max - 1);
            bubblesort(vet, x);
            break;
        case 7:
            cout << "Informe a chave a ser buscada:";
            cin >> chavebusca;
            buscaLinear(vet, x, chavebusca);
            system("pause");
            system("cls");
            break;
        case 8:
            cout << "Informe a chave a ser buscada:";
            cin >> chavebusca;
            buscaLinearOrd(vet, x, chavebusca);
            system("pause");
            system("cls");
            break;
        case 9:
            chavebusca = x - 1;
            bubblesort(vet, x);
            cout << "Nome:" << vet[chavebusca].nome << " Chave:" << vet[chavebusca].chave << endl;
            system("Pause");
            system("cls");
        case 10:
            IntercalaDoido(vet,x);
            //mergeSort(vet, 0, x - 1);
            system("Pause");
            system("cls");
            break;
        default:
            break;
        }
    }
    free(vet);
    system("cls");
    return 0;
}

void inserirauto(struct registro vet[], int max)
{

    const char nomes[10][50] = {
        "Maria", "Joaquina", "Leticia", "Edivalda", "Romelia",
        "Pedro", "Thierry", "Leonardo", "Alex", "Jose"};
    int teste = max - 1;
    int posnome, poschave;
    set<int> chavesUsadas;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    uniform_int_distribution<> dis2(0, teste);
    for (int i = 0; i <= teste; i++)
    {
        // Gerar uma chave que ainda não foi usada
        posnome = dis(gen);
        do
        {
            poschave = dis2(gen);
        } while (chavesUsadas.count(poschave) > 0); // Verificar se a chave já foi usada
        chavesUsadas.insert(poschave);              // Adicionar a chave ao conjunto de chaves usadas
        strcpy(vet[i].nome, nomes[posnome]);
        vet[i].chave = poschave;
    }
}

void inserir(struct registro vet[], int max)
{
    for (int i = 0; i < max; i++)
    {
        cout << "insira o nome: ";
        cin >> vet[i].nome;
        cout << "insira a chave: ";
        cin >> vet[i].chave;
    }
}

void imprimir(struct registro vet[], int max)
{

    for (int i = 0; i < max; i++)
    {
        cout << "Nome: " << vet[i].nome << " Chave: " << vet[i].chave << endl;
    }
}

int buscaBinaria(struct registro vet[], int tamanho, int chave)
{
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        if (vet[meio].chave == chave)
        {
            return meio;
        }

        if (vet[meio].chave < chave)
        {
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1;
}

void buscaNome(struct registro vet[], int max, char elem[50])
{
    int indice = -1;
    for (int i = 0; i < max; i++)
    {
        if (strcmp(vet[i].nome, elem) == 0)
        {               // strcmp compara duas strings se for true, retorna 0
            indice = i; // atualizo o indice para a chave que tem o nome buscado
        }
    }
    if (indice != -1)
    {
        cout << "Chave encontrada!!!" << endl;
        cout << "Nome: " << vet[indice].nome << " Chave: " << vet[indice].chave << endl;
    }
    else
    {
        cout << "Chave não encontrada!" << endl;
    }
}

void bubblesort(struct registro vet[], int max)
{
    double time_spent = 0.0; // armazena o tempo de execução do código
    clock_t begin = clock();
    for (int i = 0; i < max - 1; i++)
    {
        for (int j = 0; j < max - i - 1; j++)
        {

            if (vet[j].chave > vet[j + 1].chave)
            {
                struct registro temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "Tempo de execucao: " << time_spent << "segundos" << endl;
}

void buscaLinear(struct registro vetor[], int tamanho, int chave)
{
    int i = 0;
    while ((i <= tamanho) && (vetor[i].chave != chave))
    {
        i++;
    }
    if ((i <= tamanho) && (vetor[i].chave == chave))
    {
        cout << "Chave encontrada!!" << endl;
        cout << "Nome: " << vetor[i].nome << " Chave: " << vetor[i].chave << endl;
    }
    else
        cout << "Chave não encontrada :(" << endl;
}

void buscaLinearOrd(struct registro vetor[], int tamanho, int chave)
{
    int i = 0;
    while ((i <= tamanho) && (vetor[i].chave <= chave))
    {
        i++;
    }
    if ((i <= tamanho) && (vetor[i].chave == chave))
    {
        cout << "Chave encontrada!!" << endl;
        cout << "Nome: " << vetor[i].nome << " Chave: " << vetor[i].chave << endl;
    }
    else
        cout << "Chave não encontrada :(" << endl;
}

void IntercalaDoido(struct registro vetor[], int tamanho){
    int tamanhoA=0,tamanhoB=0,opVetPrincipal=0,p=0,j=0,k=0,compara;
    int Ordenado1,Ordenado2;
    Ordenado1 = 1;
    Ordenado2 = 1;
    //processos = pro;
    //processos++;
    //pro = processos;
    compara = tamanho % 2;
    if(compara == 1)
    {
        tamanhoA = (tamanho / 2) + 1;
    }
    else
    {
        tamanhoA = (tamanho / 2);
    }
    tamanhoB = tamanho - tamanhoA;
    int veta[tamanhoA],vetb[tamanhoB];
    for(int i=0;i <tamanhoA;i++)
    {
        veta[i] = vetor[opVetPrincipal].chave;
        opVetPrincipal++;
    }
    for(int i=0;i <tamanhoB;i++)
    {
        vetb[i] = vetor[opVetPrincipal].chave;
        opVetPrincipal++;
    }
    
    for (int i = 0;i < tamanhoA-1;i++)
    {

        if (veta[i] > veta[i+1])
        {
           // cout<<veta[i]<<endl; 
            //cout<<veta[i+1]<<endl;
            //system("pause"); 
            swap(veta[i],veta[i+1]);
            Ordenado1 = 0;
            //break;
        }
        else
        {   
            //cout<<Ordenado1<<endl;
            //system("pause");
            if (Ordenado1 != 0)
            {
                Ordenado1 = 1;
                //cout<<Ordenado1<<endl;
                //system("pause");
            }
        }
    }

    for (int i = 0;i < tamanhoB-1;i++)
    {
        if (vetb[i] > vetb[i+1])
        {
            swap(vetb[i],vetb[i+1]);
            Ordenado2 = 0;
           //break;
        }
        else
        {
            if (Ordenado2 != 0)
            {    
                Ordenado2 = true;
                //cout<<Ordenado2;
                //system("pause");
            }
        }

    }
/*
    cout<<"VetA:";
    for (int i = 0;i<tamanhoA;i++)
    {
        cout<<veta[i]<<" ";
    }
    cout<<endl;
    cout<<"Vetb:";
    for (int i = 0;i<tamanhoB;i++)
    {
        cout<<vetb[i]<<" ";
    }
    //system("pause");*/
    if(Ordenado1 == 1 && Ordenado2 == 1)
    {
        //cout<<"Processos:"<<pro;
        //system("pause");
        while (p < tamanhoA && j < tamanhoB) {
            
            if (veta[p] < vetb[j]) {
                vetor[k++].chave = veta[p++];
            } else {
                vetor[k++].chave = vetb[j++];
            }
        }
        while (p < tamanhoA) {
            vetor[k++].chave = veta[p++];
        }

        while (j < tamanhoB) {
            vetor[k++].chave = vetb[j++];
        }
    }
    else
        {
            opVetPrincipal = 0;
            for (int i = 0;i < tamanhoA;i++)
            {
                vetor[opVetPrincipal].chave = veta[i];
                opVetPrincipal++;
            }
            for (int i = 0;i < tamanhoB;i++)
            {
                vetor[opVetPrincipal].chave = vetb[i];
                opVetPrincipal++;
            }
            //cout<<pro<<endl;
            IntercalaDoido(vetor,tamanho);
        }

} 

int partition(struct registro vetor[], int start, int end)
{

    int pivot = vetor[start].chave;

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (vetor[i].chave <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(vetor[pivotIndex].chave, vetor[start].chave);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (vetor[i].chave <= pivot)
        {
            i++;
        }

        while (vetor[j].chave > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(vetor[i++].chave, vetor[j--].chave);
        }
    }

    return pivotIndex;
}

void quickSort(struct registro vetor[], int start, int end)
{

    if (start >= end)
        return;

    int p = partition(vetor, start, end);

    quickSort(vetor, start, p - 1);

    quickSort(vetor, p + 1, end);
}

void Intercala(struct registro vetor[], int p, int q, int r)
{

    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = vetor[p + i].chave;
    for (int j = 0; j < n2; j++)
        M[j] = vetor[q + 1 + j].chave;

    int i, j, k;
    i = 0;
    j = 0;
    k = p;
 
    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            vetor[k].chave = L[i];
            i++;
        }
        else
        {
            vetor[k].chave = M[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        vetor[k].chave = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vetor[k].chave = M[j];
        j++;
        k++;
    }
}

void mergeSort(struct registro vetor[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(vetor, l, m);
        mergeSort(vetor, m + 1, r);

        Intercala(vetor, l, m, r);
    }
}
