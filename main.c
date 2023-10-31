#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_int(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void bubble_sort(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int partition(int *arr, int low, int high) {
  int pivot = rand() % (high - low + 1) + low;
  int i = low - 1;
  int j = high + 1;

  while (1) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j) {
      return j;
    }

    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void quicksort_hoare(int *arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quicksort_hoare(arr, low, pi - 1);
    quicksort_hoare(arr, pi + 1, high);
  }
}

int partition_lomuto(int *arr, int low, int high) {
  int pivot = rand() % (high - low + 1) + low;
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++;
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }

  int temp = arr[i + 1];
  arr[i + 1] = arr[high];
  arr[high] = temp;

  return i + 1;
}

void

quicksort_lomuto(int *arr, int low, int high) {
  if (low < high) {
    int pi = partition_lomuto(arr, low, high);
    quicksort_lomuto(arr, low, pi - 1);
    quicksort_lomuto(arr, pi + 1, high);
  }
}


void generate_file(const char *filename, int *arr, int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

void read_file(const char *filename, int *arr, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

int main() {
    srand(time(0));

    printf("Bem-vindo ao gerador e ordenador de arquivos!\n");

    while (1) {
        printf("\nEscolha uma opção:\n");
        printf("1 - Gerar arquivo ordenado\n");
        printf("2 - Gerar arquivo invertido\n");
        printf("3 - Gerar arquivo aleatório\n");
        printf("4 - Ordenar arquivos usando diferentes algoritmos de ordenação\n");
        printf("5 - Sair\n");

        int opcao;
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao == 1 || opcao == 2 || opcao == 3) {
            int tamanho;
            printf("Digite o tamanho da lista: ");
            scanf("%d", &tamanho);

            int *lista = (int *)malloc(tamanho * sizeof(int));

            // Inicie um cronômetro
            clock_t start_time = clock();

            if (opcao == 1) {
                for (int i = 0; i < tamanho; i++) {
                    lista[i] = i + 1;
                }
                generate_file("ordenado.txt", lista, tamanho);
                printf("Arquivo 'ordenado.txt' gerado com sucesso.\n");
            } else if (opcao == 2) {
                for (int i = 0; i < tamanho; i++) {
                    lista[i] = tamanho - i;
                }
                generate_file("invertido.txt", lista, tamanho);
                printf("Arquivo 'invertido.txt' gerado com sucesso.\n");
            } else if (opcao == 3) {
                for (int i = 0; i < tamanho; i++) {
                    lista[i] = random_int(1, tamanho);
                }
                generate_file("aleatorio.txt", lista, tamanho);
                printf("Arquivo 'aleatorio.txt' gerado com sucesso.\n");
            }

            free(lista);

            // Encerre o cronômetro e calcule o tempo decorrido
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("Tempo decorrido: %.2f segundos\n", elapsed_time);
        } else if (opcao == 4) {
            int tamanho;
            printf("Digite o tamanho da lista: ");
            scanf("%d", &tamanho);
            int *arr = (int *)malloc(tamanho * sizeof(int));

            char filename[50];
            printf("Digite o nome do arquivo a ser ordenado (por exemplo, ordenado.txt): ");
            scanf("%s", filename);
            read_file(filename, arr, tamanho);

            printf("Escolha o algoritmo de ordenação:\n");
            printf("1 - Bubble Sort\n");
            printf("2 - Selection Sort\n");
            printf("3 - Quick Sort (Hoare)\n");
            printf("4 - Quick Sort (Lomuto)\n");
            int sorting_algorithm;
            printf("Opção: ");
            scanf("%d", &sorting_algorithm);

            // Inicie um cronômetro
            clock_t start_time = clock();

            if (sorting_algorithm == 1) {
                bubble_sort(arr, tamanho);
                printf("Arquivo ordenado com sucesso usando Bubble Sort.\n");
            } else if (sorting_algorithm == 2) {
                selection_sort(arr, tamanho);
                printf("Arquivo ordenado com sucesso usando Selection Sort.\n");
            } else if (sorting_algorithm == 3) {
                quicksort_hoare(arr, 0, tamanho - 1);
                printf("Arquivo ordenado com sucesso usando Quick Sort (Hoare).\n");
            } else if (sorting_algorithm == 4) {
                quicksort_lomuto(arr, 0, tamanho - 1);
                printf("Arquivo ordenado com sucesso usando Quick Sort (Lomuto).\n");
            } else {
                printf("Opção de algoritmo de ordenação inválida.\n");
            }

            // Encerre o cronômetro e calcule o tempo decorrido
            clock_t end_time = clock();
            double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("Tempo decorrido: %.4f segundos\n", elapsed_time);

            generate_file("sorted.txt", arr, tamanho);
            printf("Arquivo 'sorted.txt' gerado como arquivo ordenado.\n");

            free(arr);
        } else if (opcao == 5) {
            printf("Saindo do programa.\n");
            break;
        } else {
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    }

    return 0;
}
