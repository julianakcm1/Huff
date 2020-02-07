#include "header.h"

void menu() {
    printf("\n======================================\n");
    printf("\n\tHUFFMAN\n");
    printf("\n======================================\n");

    while(1) {
        int choice, i;
        printf("Escolha uma opção:\n1 >> Compress\n2 >> Descompress\n3 >> Exit\n");
    
        scanf("%d", choice);

        char name[256];

        switch(choice) {
            case 1:
            {
                scanf("%s", name);

                FILE* file = fopen(name, "rb");

                if(file == NULL) {
                    printf("Empty file\n");
                    break;
                }

                lli frequence[256] = {0}; // ignoramos o indice zero.

                //create_freq_array(frequence);
                fill_freq_array(frequence);
            
                PRIORITY_QUEUE* queue = create_priority_queue();
                fill_priority_queue(frequence, queue);
                //print_queue(queue->head);
                NODE* tree = create_huff_tree(queue);

                HASH* hash = create_hash();
                new_codification(hash, tree, 0, 0); 
                
                //print_hash(hash);
                //print_tree(tree);

                uchar trash = get_trash(hash, frequence); // trash so ocupa 3 bits, por isso so alocamos 1 byte para guardar o lixo.
                ushort size_tree = get_size_tree(tree);

                // // COMENTARIOS USANDO O EXEMPLO DO MARCIO: PARA LIXO = 5 OU 0000 0101 (em binario)

                ushort header = 0; // zera os 16 bits (2 bytes): 00000000 00000000
                header |= trash;  // agora ficou assim: 000000 00000101 (ultimo byte eh o lixo em binario)
                header <<= 13;   //  para trazer o lixo pras 3 primeiras posicoes do primeiro byte: 10100000 00000000
                header = header | size_tree;  // inserir o restante da arvore (11 exemplo) nos 2 bits: 1010 0000 0000 1011 (header pronta!)
                
                // printf("trash %u\n", trash);
                // printf("header %u\n", header);
                
                FILE* file = fopen("bandeira.jpg.huff", "wb"); // arquivo de escrita compactado
                uchar byte_1 = header >> 8; // pega so o primeiro byte da header(que tem 2 bytes)
                uchar byte_2 = header; // nao precisa shiftar, como o byte 2 so tem 1 byte, ele pega o segundo byte da header.

                //printf("byte 1: %d\n", byte_1);
                //printf("byte 2: %d\n", byte_2);

                fputc(byte_1, file);
                fputc(byte_2, file);

                get_pre_order_tree(tree, file);

                compact_file(file, hash, trash);
                fclose(file);
                break;
            }

            case 2:
            {

            }

            case 3: { break; }
        }
    }
    return;   
}