#include <cstdio>
#include <climits>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Heap{
public:
  Heap();
  Heap(int n, int dados[]);
  ~Heap();
  void escreve_niveis();
  void escreve(const string& prefixo = "", int i = 0);
  void insere(int p);
  int consulta_maxima();
  int extrai_maxima();
  void altera_prioridade(int i, int p);

  
private:
  vector<int> S;

  int pai(int i);
  int esquerdo(int i);
  int direito(int i);
  void troca(int i, int j);
  void desce(int i);
  void sobe(int i);
};


int main(void){
  Heap h; // construtor Heap()
  
  for (int i = 1; i <= 10; i++)
    h.insere(i);
  printf("h:\n");
  h.escreve();
  exit(0);

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
  
  return 0;
}

/*

Heap h2(5, v);  // o construtor é usado para construir h2
Heap h3(h2);    // o construtor de cópia é usado para construir h3
Heap h4 = h3;   // o construtor de cópia é usado para inicializar um objeto quando há uma atribuição SIMULTÂNEA com a declaração
h = h2;         // o operador de atribuição (cópia) é utilizado (não algum construtor ou transferência)
h = Heap(5, v); // o construtor é usado para construir uma variável temporária, e depois o operação de atribuição (cópia?) é utilizado

** Quando são feitas cópias de objetos **

O C++ chama um construtor de cópia para fazer uma cópia de um objeto
conforme descrito nos casos acima. Se não houver um construtor de
cópias definido para a classe, o C ++ definirá um construtor de cópias
padrão, que copia cada campo (utilizando o construtor de cópia de cada
campo, se for o caso).


** Não escreva um construtor de cópias a menos que necessário **

Se o objeto não tiver ponteiros para a memória alocada dinâmicamente,
uma cópia "superficial" provavelmente será suficiente. Portanto, o
construtor de cópia padrão, o operador de atribuição padrão e o
destruidor padrão estão ok e você não precisa escrever seus próprios.


** Se você precisar de um construtor de cópias, também precisará de um **
** destruidor e um operador de atribuição (operator=) **

Se você precisa de um construtor de cópias, é porque precisa de algo
como uma cópia profunda ou algum outro gerenciamento de
recursos. Assim, é quase certo que você precisará definir um destruidor e
um operador de atribuição.


** Diferença entre construtor de cópia e atribuição **

Um construtor de cópia é usado para inicializar uma variável EM SUA
DECLARAÇÃO a partir de uma variável existente. É parecido com a
atribuição, mas mais simples:

1. Não há necessidade de testar para ver se ele está sendo inicializado por si mesmo
2. Não há necessidade de limpar (por exemplo, excluir) um valor existente (não há nenhum)
3. Uma referência a si mesma não é devolvida.


** Transferência **

Na maioria das vezes, o construtor de transferência ou o operador de
atribuição de trasnferência não são fornecidos pelo compilador. Se
forem, eles farão o mesmo que os construtores/operadores de cópia.

Regra: se você deseja um construtor de transferência e uma atribuição
de transferência que realmente realize a transferência de dados, você
terá que escrevê-los

*/


//*************************************
//*** IMPLEMENTAÇÕES DA CLASSE HEAP ***
//*************************************

Heap::Heap() {
}

Heap::Heap(int n, int dados[]) :
  S(dados, dados + n) {
  //TODO: implementar (constroi_max_heap)

}

Heap::~Heap() {
}

void Heap::escreve_niveis() {
  int escritos = 0, fim_nivel = 1;

  for(auto const& elemento: S) {
  // Equivalente a for (unsigned i = 0; i < S.size(); i++) { printf("%d ", S[i]);
    printf("%d ", elemento);
    if (++escritos == fim_nivel) {
      putchar('\n');
      fim_nivel *= 2;
      escritos = 0;
    }
  }
  putchar('\n');
}

void Heap::escreve(const string& prefixo, int i) {
  if (i < (int) S.size()) {
    bool ehEsquerdo = i % 2 != 0;
    bool temIrmao = i < (int) S.size()-1;
    
    printf(prefixo.c_str());
    printf(ehEsquerdo and temIrmao ? "├──" : "└──" );

    printf("%d\n", S[i]);
      
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), esquerdo(i));
    escreve(prefixo + (ehEsquerdo ? "│   " : "    "), direito(i));
  }
}

int Heap::pai(int i) {
  return (i - 1) / 2;
}

int Heap::esquerdo(int i) {
  return 2 * (i + 1) - 1;
}

int Heap::direito(int i) {
  return 2 * (i + 1);
}

void Heap::troca(int i, int j) {
  int aux = S[i];
  S[i] = S[j];
  S[j] = aux;
}

void Heap::desce(int i) {
  int n, e, d, maior;

  e = esquerdo(i);
  d = direito(i);
  n = S.size();

  if(e < n && S[e] > S[i])
    maior = e;
  else
    maior = i;
  if(d < n && S[d] > S[maior])
    maior = d;
  if(maior != i){
    troca(S[i], S[maior]);
    desce(maior);
  }
}

void Heap::sobe(int i) {
  while (S[pai(i)] < S[i]) {
    troca(i, pai(i));
    i = pai(i);
  }
}

void Heap::insere(int p){
  S.push_back(p);
  sobe(S.size()-1);
}

int Heap::consulta_maxima(){
  return S[0];
}

int Heap::extrai_maxima(){
  int n = 0, x = 0;

  x = S[0];
  n = S.size();
  S[0] = S[n-1];
  S.pop_back();
  desce(0);

  return x;
}

void Heap::altera_prioridade(int i, int p) {
  if(p < S[i])
    printf("ERRO\n");
  else{
    S[i] = p;
    sobe(i);
  }

}
