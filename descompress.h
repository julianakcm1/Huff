#ifndef DESCOMPRESS_H
#define DESCOMPRESS_H
#include "header.h"

// FUNCAO DE CRIAR UM NO

/** @param caracter: */
/** @param left: */
/** @param right: */
/** @return returns */
NODE_DESCOM* create_node(uchar caracter, NODE_DESCOM* left, NODE_DESCOM* right);

// FUNCAO QUE VERIFICA SE EH UMA FOLHA

/** @param current: */
/** @return returns */
bool is_leaf(NODE_DESCOM* current);

// FUNCAO DE MONTAR A ARVORE

/** @param str: a pointer to the */
/** @param i: a pointer to the */
/** @return returns */
NODE_DESCOM* construct_tree(uchar *str, int *i);

// FUNCAO DE DESCOMPRESSAO

void descompact();

// SETAR OS BITS

/** @param byte: */
/** @param i: */
/** @return returns */
bool is_bit_i_set(ushort byte, int i);

#endif