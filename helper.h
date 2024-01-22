typedef struct {
  long int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize);

void insertArray(Array *a, long int element);

void freeArray(Array *a);

long int *get_array_numbers(char *numbers,int size);

void fill_array_numbers(char *numbers,Array *myarr, size_t size);