#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <bits/stdc++.h>
#include <stack>

const int N_MAX = 1000;
const int M_MAX = 1000;
const int K_MAX = 1000000;
const int C_MAX = 500;
const int L_MAX = 500;

// Criando estrutura que vai representar a mesa
typedef struct mesa
{
    int c = 0;
    int l = 0;
} me;

// Criando variáveis do problema
int n = 0;
int m = 0;
int k = 0;
int planta[N_MAX][M_MAX];
me mesa[K_MAX];

// Função recebe txt e extrai as informações para as variáveis correspondentes
void lerArquivo(std::string entrada)
{
    std::ifstream file;
    std::string lineFile;
    int idxLine = 0;
    int pos = 0;
    int tamanho = 0;
    // Abrindo arquivo
    file.open(entrada);
    if (file.is_open())
    {
        while (getline(file, lineFile))
        {
            // Pegando dados da primeira linha e armazenando nas variáveis n e m
            if (idxLine == 0)
            {
                pos = lineFile.find(" ");
                n = std::stoi(lineFile.substr(0, pos));

                tamanho = pos + 1;
                pos = lineFile.find(" ", pos + 1);
                m = std::stoi(lineFile.substr(tamanho, pos - tamanho));
                idxLine++;
                continue;
            }
            // Pegando dados das n proximas linhas e armazenando na matriz planta
            else if (idxLine > 0 && idxLine <= n)
            {
                for (int i = 0; i < m; i++)
                {
                    if (lineFile[i] == '#')
                    {
                        planta[(idxLine - 1)][i] = 0;
                    }
                    else
                    {
                        planta[(idxLine - 1)][i] = 1;
                    }
                }
                idxLine++;
                continue;
            }
            // Pegando dados de k que representa o tamanho da lista de mesas
            else if (idxLine == n + 1)
            {
                pos = lineFile.find(" ");
                k = std::stoi(lineFile.substr(0, pos));
                idxLine++;
                continue;
            }
            // Armazendo lista de mesa em um vetor de struct
            else
            {
                int idxMesa = idxLine - n - 2;
                pos = lineFile.find(" ");
                mesa[idxMesa].c = std::stoi(lineFile.substr(0, pos));

                tamanho = pos + 1;
                pos = lineFile.find(" ", pos + 1);
                mesa[idxMesa].l = std::stoi(lineFile.substr(tamanho, pos - tamanho));
                idxLine++;
                continue;
            }
        }
    }
    // Caso o arquivo não seja encontrado
    else
    {
        std::cout << "Arquivo não encontrado";
    }
    file.close();
}

void lerTerminal()
{
    std::string line;
    int pos = 0;
    int tamanho = 0;
    
    std::getline( std::cin, line );
    pos = line.find(" ");
    n = std::stoi(line.substr(0, pos));

    tamanho = pos + 1;
    pos = line.find(" ", pos + 1);
    m = std::stoi(line.substr(tamanho, pos - tamanho));

    // Fazendo a planta
    for (int i = 0; i < n; i++)
    {
        std::getline(std::cin, line);
        for (int j = 0; j < m; j++)
        {
            if (line[j] == '#')
            {
                planta[(i)][j] = 0;
            }
            else
            {
                planta[(i)][j] = 1;
            }
        }
    }

    //Pegando valor de k
    std::getline( std::cin, line);
    pos = line.find(" ");
    k = std::stoi(line.substr(0, pos));

    //Pegando valor das mesas
    for (int i = 0; i < k; i++)
    {
        std::getline(std::cin, line);
        int idxMesa = i;
        pos = line.find(" ");
        mesa[idxMesa].c = std::stoi(line.substr(0, pos));

        tamanho = pos + 1;
        pos = line.find(" ", pos + 1);
        mesa[idxMesa].l = std::stoi(line.substr(tamanho, pos - tamanho));

    }
}

int maxHist(int row[])
{
    // Crie uma pilha vazia. A pilha contém índices de
    // hist[] array / As barras armazenadas na pilha são sempre
    // em ordem crescente de suas alturas.
    std::stack<int> result;

    int top_val; // topo da pilha

    int max_area = 0; // inicializa a área máxima no atual
    // linha (ou histograma)

    int area = 0; // Inicializa a área com o topo atual

    // Percorre todas as barras de um determinado histograma(ou linha)
    int i = 0;
    while (i < m)
    {
        // Se esta barra for maior que a barra no topo da pilha,
        // empurra para empilhar
        if (result.empty() || row[result.top()] <= row[i])
            result.push(i++);

        else
        {
            // Se esta barra estiver abaixo do topo da pilha, então
            // calcule a área do retângulo com o topo da pilha como
            // a barra menor (ou altura mínima). 'i' é
            //'índice direito' para o topo e o elemento antes
            // o topo da pilha é o 'índice esquerdo'
            top_val = row[result.top()];
            result.pop();
            area = top_val * i;

            if (!result.empty())
                area = top_val * (i - result.top() - 1);
            max_area = std::max(area, max_area);
        }
    }

    // Agora retire as barras restantes da pilha e calcule
    // área com cada barra estourada como a menor barra
    while (!result.empty())
    {
        top_val = row[result.top()];
        result.pop();
        area = top_val * i;
        if (!result.empty())
            area = top_val * (i - result.top() - 1);
        max_area = std::max(area, max_area);
    }
    return max_area;
}

// Retorna a área do maior retângulo com todos os 1s em A[][]
void comprimentoLargura(int p[][M_MAX])
{
    // Calcule a área da primeira linha e inicialize-a como resultado
    int result = maxHist(p[0]);
    int aux = 0;
    int c, l;
    int c_, l_;

    //Achando o maior valor possivel da largura e comprimento da mesa
    int comprimentoMesaMax = 0;
    int larguraMesaMax = 0;
    int auxComprimentoMax = 0;
    int auxLarguraMax = 0;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(planta[i][j] == 1){
                auxLarguraMax++;
            }
            else{
                if(larguraMesaMax < auxLarguraMax){
                    larguraMesaMax = auxLarguraMax;
                }
                auxLarguraMax = 0;
            }
        }
        auxLarguraMax = 0;
    }

    for(int j = 0; j < n; j++){
        for(int i = 0; i < m; i++){
            if(planta[i][j] == 1){
                auxComprimentoMax++;
            }
            else{
                if(comprimentoMesaMax < auxComprimentoMax){
                    comprimentoMesaMax = auxComprimentoMax;
                }
                auxComprimentoMax = 0;
            }
        }
        auxComprimentoMax = 0;
    }

    // itere sobre a linha para encontrar a área retangular máxima
    // considerando cada linha como histograma
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)

            // se p[i][j] for 1, então adicione p[i -1][j]
            if (p[i][j])
                p[i][j] += p[i - 1][j];

        // Atualize o resultado se a área com a linha atual (como última linha) do retângulo) for maior
        result = std::max(result, maxHist(p[i]));
    }


    //Calculando o valor das áras das meses e selecionando a que tem a maior área 
    //Compátivel
    for (int i = 0; i < k; i++)
    {
        c = mesa[i].c;
        l = mesa[i].l;
        int areaMesa = l * c;
        
        if ((areaMesa <= result) && (areaMesa > aux) && 
            ((c <= comprimentoMesaMax &&  l <= larguraMesaMax) || 
            (l <= comprimentoMesaMax &&  c <= larguraMesaMax)))
        {
            c_ = c;
            l_ = l;
            aux = areaMesa;
            continue;
        }

        if((areaMesa <= result) && (areaMesa == aux) &&
            ((c <= comprimentoMesaMax && l <= larguraMesaMax) || 
            (l <= comprimentoMesaMax &&  c <= larguraMesaMax)))
        {
            if(l > l_){
                c_ = c;
                l_ = l;
            }
        }
    }
    std::cout << c_ << " " << l_;
}

int main(int argc, char *argv[])
{
    lerArquivo(argv[1]);
    //lerTerminal();

    comprimentoLargura(planta);

    return 0;
}