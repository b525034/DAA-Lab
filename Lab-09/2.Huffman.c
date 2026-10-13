#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Node
{
    char symbol;
    int frequency;

    struct Node *left;
    struct Node *right;
};

struct MinHeap
{
    int size;
    struct Node *array[MAX];
};

/* Create a new Huffman node */
struct Node* createNode(char symbol, int frequency)
{
    struct Node *node =
        (struct Node *)malloc(sizeof(struct Node));

    node->symbol = symbol;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* Swap two heap elements */
void swap(struct Node **a, struct Node **b)
{
    struct Node *temp = *a;
    *a = *b;
    *b = temp;
}

/* Maintain min-heap property */
void minHeapify(struct MinHeap *heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size &&
        heap->array[left]->frequency <
        heap->array[smallest]->frequency)
    {
        smallest = left;
    }

    if (right < heap->size &&
        heap->array[right]->frequency <
        heap->array[smallest]->frequency)
    {
        smallest = right;
    }

    if (smallest != index)
    {
        swap(&heap->array[index],
             &heap->array[smallest]);

        minHeapify(heap, smallest);
    }
}

/* Insert node into min-heap */
void insertHeap(struct MinHeap *heap, struct Node *node)
{
    int i = heap->size;

    heap->array[i] = node;
    heap->size++;

    while (i != 0)
    {
        int parent = (i - 1) / 2;

        if (heap->array[parent]->frequency <=
            heap->array[i]->frequency)
        {
            break;
        }

        swap(&heap->array[parent],
             &heap->array[i]);

        i = parent;
    }
}

/* Remove minimum frequency node */
struct Node* extractMin(struct MinHeap *heap)
{
    struct Node *minNode = heap->array[0];

    heap->array[0] =
        heap->array[heap->size - 1];

    heap->size--;

    if (heap->size > 0)
        minHeapify(heap, 0);

    return minNode;
}

/* Generate Huffman codes */
void generateCodes(struct Node *root,
                   char code[],
                   int depth,
                   char symbols[],
                   char codes[][MAX],
                   int lengths[],
                   int *count)
{
    if (root == NULL)
        return;

    /* Leaf node */
    if (root->left == NULL &&
        root->right == NULL)
    {
        code[depth] = '\0';

        symbols[*count] = root->symbol;

        strcpy(codes[*count], code);

        lengths[*count] = depth;

        (*count)++;

        return;
    }

    code[depth] = '0';

    generateCodes(root->left,
                  code,
                  depth + 1,
                  symbols,
                  codes,
                  lengths,
                  count);

    code[depth] = '1';

    generateCodes(root->right,
                  code,
                  depth + 1,
                  symbols,
                  codes,
                  lengths,
                  count);
}

/* Compare codes according to canonical Huffman rules */
int compareCodes(const void *a, const void *b)
{
    int i = *(int *)a;
    int j = *(int *)b;

    if (lengthsGlobal[i] != lengthsGlobal[j])
        return lengthsGlobal[i] - lengthsGlobal[j];

    return symbolsGlobal[i] - symbolsGlobal[j];
}

/* Global arrays used for sorting */
char symbolsGlobal[MAX];
int lengthsGlobal[MAX];

/* Generate canonical codes */
void generateCanonicalCodes(
    char symbols[],
    int lengths[],
    int n)
{
    int order[MAX];

    for (int i = 0; i < n; i++)
        order[i] = i;

    /* Copy values to global arrays for comparator */
    for (int i = 0; i < n; i++)
    {
        symbolsGlobal[i] = symbols[i];
        lengthsGlobal[i] = lengths[i];
    }

    qsort(order, n, sizeof(int), compareCodes);

    unsigned int code = 0;

    printf("\nCanonical Huffman Codebook:\n");

    for (int i = 0; i < n; i++)
    {
        int index = order[i];

        if (i > 0)
        {
            int previous = order[i - 1];

            code++;

            code <<=
                (lengths[index] -
                 lengths[previous]);
        }

        printf("%c : ", symbols[index]);

        for (int bit = lengths[index] - 1;
             bit >= 0;
             bit--)
        {
            printf("%d",
                   (code >> bit) & 1);
        }

        printf("\n");
    }
}

int main()
{
    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    struct MinHeap heap;
    heap.size = 0;

    for (int i = 0; i < n; i++)
    {
        char symbol;
        int frequency;

        printf("Enter symbol and frequency: ");
        scanf(" %c %d",
              &symbol,
              &frequency);

        struct Node *node =
            createNode(symbol, frequency);

        insertHeap(&heap, node);
    }

    /* Construct Huffman tree */
    while (heap.size > 1)
    {
        struct Node *left =
            extractMin(&heap);

        struct Node *right =
            extractMin(&heap);

        struct Node *parent =
            createNode('$',
                       left->frequency +
                       right->frequency);

        parent->left = left;
        parent->right = right;

        insertHeap(&heap, parent);
    }

    struct Node *root =
        extractMin(&heap);

    char code[MAX];

    char symbols[MAX];
    char codes[MAX][MAX];
    int lengths[MAX];

    int count = 0;

    generateCodes(root,
                  code,
                  0,
                  symbols,
                  codes,
                  lengths,
                  &count);

    printf("\nHuffman Codes:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%c : %s\n",
               symbols[i],
               codes[i]);
    }

    generateCanonicalCodes(
        symbols,
        lengths,
        count);

    return 0;
}