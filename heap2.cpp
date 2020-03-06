#include <cstdio>
#include <climits>
#include <string>
#include <algorithm>

using std::string;

class Heap
{
public:
  Heap();
  Heap(const int n, const int dados[]);
  Heap(const Heap& outro);
  ~Heap();
  Heap& operator=(const Heap& outro);
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(int p);
  int consulta_maxima();
  int extrai_maxima();
  void altera_prioridade(int i, int p);

  
private:
  int *S;
  int n;
  int capacidade;
  static const int TAMANHO_INICIAL = 4;
  
  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};


int main(void)
{
  Heap h; // construtor Heap()
  
  for (int i = 1; i <= 10; i++)
    h.insere(i);
  printf("h:\n");
  h.escreve();

  h.extrai_maxima();
  h.altera_prioridade(0, -3);
  printf("h:\n");
  h.escreve();

  int v[] = {1,2,3,4,5};
  
  Heap h2(5, v); // construtor Heap(int n, int dados[])
  h2.insere(15);
  printf("h2:\n");
  h2.escreve();
    
  Heap h3(h2); // construtor de cópia padrão
  h2.insere(30);
  printf("h3:\n");
  h3.escreve();

  Heap h4 = h2; // construtor de cópia padrão
  h2.insere(40);
  printf("h4:\n");
  h4.escreve();
  
  h = h2; // operador de atribuição, sem constructor ou constructor de cópia
  h.insere(100);
  printf("h2:\n");
  h2.escreve();
  printf("h:\n");
  h.escreve();

  h = Heap(5, v); // construtor Heap(int n, int dados[]), seguido de atribuição (de cópia, não transferência (move))
  printf("h:\n");
  h.escreve();

  h.extrai_maxima();
  h.altera_prioridade(0, -2);
  printf("h:\n");
  h.escreve();
    
  return 0;
}
