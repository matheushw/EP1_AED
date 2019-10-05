#include "filapreferencial.h"

PFILA criarFila(){
	PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
	res->inicio = NULL;
	res->fimPref = NULL;
	res->inicioNaoPref = NULL;
	res->fim = NULL;
	return res;
}

void debug (PFILA a) {
	printf("Inicio: %d, Inicio_NP: %d, Fim_FP: %d, Fim: %d\n", a->inicio, a->inicioNaoPref, a->fimPref, a->fim);
}

int tamanho(PFILA f){
	PONT atual = f->inicio;
	int tam = 0;
	while (atual) {

		atual = atual->prox;

		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->inicio;
	while (atual) {

		if (atual->id == id) return atual;

		atual = atual->prox;

	}
	return NULL;
}

PONT buscarID_2(PFILA f, int id){
	PONT atual = f->inicio;
	while (atual) {

		if (atual->prox->id == id) return atual;

		atual = atual->prox;

	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i] - Inicio:", numElementos);
	PONT atual = f->inicio;
	while (atual){
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->inicio;
	while (atual) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}


bool inserirPessoaNaFila(PFILA f, int id, int idade){

	if (idade < 0 || buscarID(f, id) != NULL) { 
		return false;
	}
	
	PONT pessoa = (PONT) malloc(sizeof(ELEMENTO));
	pessoa->prox = NULL;
	pessoa->id = id;
	pessoa->idade = idade;

	if (idade >= IDADEPREFERENCIAL) {
		if (f->fimPref == NULL) {
			if (f->inicio == NULL){
				f->inicio = pessoa;
			}

			else {
				pessoa->prox = f->inicio;
				f->inicio = pessoa;
			}

			if (f->fim == NULL) f->fim = pessoa;

		}
		
		else {
			PONT aux_troca = f->fimPref->prox; 
			f->fimPref->prox = pessoa;
			pessoa->prox = aux_troca;

			if (f->fim == f->fimPref) f->fim = pessoa;


		}
		
		f->fimPref = pessoa;
	}

	else {
		if (f->inicioNaoPref == NULL) {
			if (f->inicio == NULL){
				f->inicio = pessoa;
			}

			if (f->fim != NULL) {
				f->fimPref->prox = pessoa;
			}

			f->inicioNaoPref = pessoa;
		}

		else {
			f->fim->prox = pessoa;
		}

		f->fim = pessoa;
	}

	return true;

}

bool atenderPrimeiraDaFila(PFILA f, int* id){

	if (tamanho(f)==0) return false;

	*id = f->inicio->id;

	if(f->fimPref != NULL) {

		PONT aux_troca = f->inicio; 

		if (f->inicio == f->fimPref) {
			if(f->fimPref == f->fim) {
				f->inicioNaoPref = NULL;
				f->fimPref = NULL;
				f->inicio = NULL;
				f->fim = NULL;
			}

			else {
				f->inicio = f->inicioNaoPref;
				f->fimPref = NULL;
			}
		}

		else {
			f->inicio = f->inicio->prox;
		}

	}

	else {

		if(f->fim == f->inicio) {
			f->inicioNaoPref = NULL;
			f->inicio = NULL;
			f->fim = NULL;
		}

		else {
			PONT aux_troca = f->inicio->prox;
			f->inicio = aux_troca;
			f->inicioNaoPref = aux_troca;
		}

	}

	return true;
}


bool desistirDaFila(PFILA f, int id){

	PONT aux = buscarID(f, id);

	if (aux == NULL) return false;

	if (aux->idade >= IDADEPREFERENCIAL) {
		if (aux == f->inicio) {
			if (aux == f->fimPref) {
				if (aux == f->fim) {
					f->fim = NULL;
					f->fimPref = NULL;
					f->inicio = NULL;
					f->inicioNaoPref = NULL;
					return true;
				}
				else {
					f->inicio = f->inicioNaoPref;
					f->fimPref = NULL;
					return true;
				}
			}
			f->inicio = f->inicio->prox;
		}

		else if (aux == f->fim) {
			PONT aux2 = buscarID_2(f,id);
			f->fim = aux2;
			f->fimPref = aux2;
			aux2->prox = NULL;
		}

		else if (aux == f->fimPref) {
			PONT aux2 = buscarID_2(f,id);
			f->fimPref = f->inicioNaoPref;
			aux2->prox = f->inicioNaoPref;
		}

		else {
			printf("olar\n");
			PONT aux2 = buscarID_2(f,id);
			aux2->prox = aux->prox;
		}

	}

	else {
		if (aux == f->inicio) {
			if (aux == f->fim){
				f->inicio = NULL;
				f->fim = NULL;
			}
			else {
				f->inicio = f->inicio->prox;
			}
		}

		else if (aux == f->fim) {
			PONT aux2 = buscarID_2(f,id);
			f->fim = aux2;
			aux2->prox = NULL;

		}

		else {
			PONT aux2 = buscarID_2(f,id);
			aux2->prox = aux->prox;
		}

	}

	return true;
}

// int main() {

// 	// PFILA a = criarFila();

// 	// inserirPessoaNaFila(a, 65, 65);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 70, 70);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 20, 20);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 32, 32);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 30, 30);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 31, 31);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 10, 10);
// 	// debug(a);
// 	// inserirPessoaNaFila(a, 87, 87);
// 	// debug(a);
// 	// exibirLog(a);
// 	// debug(a);
// 	// desistirDaFila(a,30);
// 	// exibirLog(a);
// 	// debug(a);



// 	return 0;
// }
