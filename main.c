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

// Função para encontrar o valor máximo em um array
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}


// Função de ordenação Counting Sort (auxiliar para o Radix Sort)
void countingSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Função de ordenação Radix Sort
void radixSort(int arr[], int n) {
    int max = findMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, n, exp);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
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
            printf("5 - Radix Sort\n");
            printf("6 - Insertion Sort\n");
            printf("7 - Merge Sort\n");
            printf("8 - Heap Sort\n");
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
            } else if (sorting_algorithm == 5) {
                radixSort(arr, tamanho);
                printf("Arquivo ordenado com sucesso usando Radix Sort.\n");
            } else if (sorting_algorithm == 6) {
                insertionSort(arr, tamanho);
                printf("Arquivo ordenado com sucesso usando Insertion Sort.\n");
            } else if (sorting_algorithm == 7) {
                mergeSort(arr, 0, tamanho - 1);
                printf("Arquivo ordenado com sucesso usando Merge Sort.\n");
            } else if (sorting_algorithm == 8) {
                heapSort(arr, tamanho);
                printf("Arquivo ordenado com sucesso usando Heap Sort.\n");
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
        }

        else if (opcao == 5) {
            printf("Saindo do programa.\n");
            break;
        } else {
            printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    }

    return 0;
}
