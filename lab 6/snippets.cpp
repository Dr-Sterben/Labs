#include <stdio.h>
#include <stdlib.h>

// конфиги
#define NORMAL   0
#define REVERSE  1

#define ALPHABET 0
#define LENGTH   1
#define VOWELS   2
#define CONSNTS  3

#define EXIT   0
#define HELP   1
#define REMOVE 2
#define INSERT 3
#define SORT   4
#define SORTx2 5
#define PRINT  9


typedef struct file {
  char *str;
  int size;
} file;

int file_size(FILE *file) {
  fseek(file, 0, SEEK_END);
	size_t fsize = ftell(file);
	fseek(file, 0, SEEK_SET);
	return fsize;
}

file *read_file(const char *path) {
  FILE *f = fopen(path, "r");
  if (f == NULL)
    perror("Error opening file");
  // read string from file
  size_t fsize = file_size(f);
  char *str = (char*) malloc(fsize * sizeof(char));
  for (size_t i = 0; i < fsize; i++)
    str[i] = fgetc(f);
  fclose(f);
  // create file structure
  file *temp_file = (file*) malloc(sizeof(file));
  temp_file -> str = str;
  temp_file -> size = fsize;
  return temp_file;
}

// list  ->  содержит указатель на начало связанного списка node
// node  ->  содержит ссылку на word и ссылки на пред/след элемент
// word  ->  содержит массив char и длину/кол-во глассных в слове

typedef struct word {
  char *arr;
  int size;
  int capacity;
  int vowels;
  int consnts;
} word;

typedef struct node {
  struct word *word;
  struct node *prev;
  struct node *next;
} node;

typedef struct list {
  node  *head;
  size_t size;
} list;

void init(list *list) {
  list -> head = NULL;
  list -> size = 0;
}

void destroy_word(word *word) {
  free(word -> arr);
  free(word);
}

void destroy_node(node *node) {
  destroy_word(node -> word);
  free(node);
}

void destroy(list *list) {
  node *curr = list -> head;
  node *prev = NULL;
  while (curr != NULL) {
    prev = curr;
    curr = curr -> next;
    destroy_node(prev);
  }
}

int len = 0;
char *read_str() {
  len = 0;
  int capacity = 1;
  char *s = (char *)malloc(sizeof(char));
  char c = getchar();
  while (c == '\n') c = getchar();
  while (c != '\n') {
    s[(len)++] = c;
    if (len >= capacity) {
      capacity *= 2;
      s = (char *)realloc(s, capacity * sizeof(char));
    }
    c = getchar();
  }
  s[len] = '\0';
  return s;
}

int strlen(char *str) {
  int count = 0;
  for (int i = 0; str[i] != 0; i++) count++;
  return count;
}

int vowels_count(char *str) {
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++)
    if ((str[i] == 'a' || str[i] == 'A')
    ||  (str[i] == 'e' || str[i] == 'E')
    ||  (str[i] == 'i' || str[i] == 'I')
    ||  (str[i] == 'o' || str[i] == 'O')
    ||  (str[i] == 'u' || str[i] == 'U')) count++;
  return count;
}

void upd_word(word *w) {
  w -> vowels = vowels_count(w -> arr);
  w -> consnts = w -> size - w -> vowels;
}

struct word *make_word(char *str, int capacity) {
  word *temp = (word*)malloc(sizeof(word));
  temp -> arr = str;
  temp -> size = strlen(str);
  temp -> capacity = capacity;
  upd_word(temp);
  return temp;
}

char lower(int ch) {
  return ch > 64 && ch < 91 ? ch + 32 : ch;
}

void push_back(list *list, char *str, int capacity) {
  word *w = make_word(str, capacity);
  node *n = (node*) malloc(sizeof(node));
  node *curr;

  n -> word = w;
  n -> next = NULL;

  if(list -> head == NULL) {
    n -> prev = NULL;
    list -> head = n;
  } else {
    curr = list -> head;
    while (curr -> next != NULL)
      curr = curr -> next;
    curr -> next = n;
    n -> prev = curr;
  }
  list -> size++;
}

void merge_lists(list *source, list *destination) {
  node *curr = source -> head;
  for (int i = 0; i < source -> size; i++) {
    word *temp_word = curr -> word;
    char *temp_str = (char*) malloc(temp_word -> size * sizeof(char));
    for (size_t i = 0; i < temp_word -> size; i++)
      temp_str[i] = temp_word -> arr[i];
    push_back(destination, temp_str, temp_word -> capacity);
    curr = curr -> next;
  }
}

struct word *get_word(list *list, int index) {
  int count = 0;
  node *curr = list -> head;
  word *result = curr -> word;
  while (count++ != index) {
    curr = curr -> next;
    result = curr -> word;
  }
  return result;
};

struct node *get_node(list *list, int index) {
  int count = 0;
  node *curr = list -> head;
  while (count++ != index)
    curr = curr -> next;
  return curr;
};

void print_list(list *list) {
  printf("---------------------\n");
  for (size_t i = 0; i < list -> size; i++) {
    word *temp = get_word(list, i);
    printf("%d -- %s\n", i, temp -> arr);
    printf("---------------------\n");
  }
}

int is_char(int ch) {
  return (int)
  ((97 <= ch && ch <= 122) ||
  (128 <= ch && ch <= 175) ||
  (224 <= ch && ch <= 239) ||
  (65  <= ch && ch <= 90));
}

int strcmp(char *s1, char *s2) {
  char c1, c2;
  while ((c1 = *s1++) == (c2 = *s2++))
    if (c1 == '\0')
      return 0;
  return c1 - c2;
}

void edit_word(list *list, int index, char *str, int cap) {
  node *temp = get_node(list, index);
  word *word = temp -> word;
  word -> arr = str;
  word -> size = strlen(str);
  word -> capacity = cap;
  upd_word(word);
}

void swap_nodes(node *n1, node *n2) {
  struct word *temp = n2 -> word;
  n2 -> word = n1 -> word;
  n1 -> word = temp;
}

void parse_str(char *temp, size_t size, list *list) {
  int capacity = 1, len = 0;
  char *str = (char*) malloc(sizeof(char));
  for (size_t i = 0; i < size; i++) {
    if (is_char(temp[i])) {
      str[len++] = temp[i];
      if (len >= capacity)
        str = (char*) realloc(str, (capacity *= 2) * sizeof(char));
      if (size - i == 1)
        goto word_end;
    } else {
      word_end:
      if (len) {
        str[len] = '\0';
        push_back(list, str, capacity);
        capacity = 1; len = 0;
        str = (char*) malloc(sizeof(char));
      }
    }
  }
}

list *parse_file(file *file) {
  list *temp_list = (list*) malloc(sizeof(list));
  init(temp_list);
  parse_str(file -> str, file -> size, temp_list);
  free(file -> str);
  free(file);
  return temp_list;
}

// новая функция сравнения слов
int compare_words(word *w1, word *w2, int order) {
  //  1 - порядок правильный
  //  0 - слова идентичны
  // -1 - порядок неправильный
  int min_size = w1 -> size < w2 -> size ? w1 -> size : w2 -> size;
  for (int i = 0; i < min_size; i++)
    if (w1 -> arr[i] != w2 -> arr[i])
      return order ^ (w1 -> arr[i] > w2 -> arr[i]) ? -1 : 1;
  if (w1 -> size == w2 -> size) return 0;
  else return order ^ (w1 -> size > w2 -> size) ? -1 : 1;
}

void insert(list *list, node *curr, char *str) {

  node *temp_node = (node*) malloc(sizeof(node));
  word *temp_word = make_word(str, strlen(str));
  temp_node -> word = temp_word;
  temp_node -> next = curr -> next;
  temp_node -> prev = curr;
  curr -> next -> prev = temp_node;
  curr -> next = temp_node;
  list -> size++;
}

// поиск слова (с начала / с конца / с оффсетом)
int find_word(list *list, char *str, int offset, int order) {
  word *tmp = make_word(str, 0);
  switch (order) {
    case NORMAL:
      for (int i = offset; i < list -> size; i++)
        if (compare_words(get_word(list, i), tmp, NORMAL) == 0) {
          destroy_word(tmp);
          return i;
        }
      break;
    case REVERSE:
      for (int i = list -> size - offset - 1; i >= 0; i--)
        if (compare_words(get_word(list, i), tmp, NORMAL) == 0) {
          destroy_word(tmp);
          return i;
        }
      break;
  }
  destroy_word(tmp);
  return -1;
}

void remove_node(list *list, int index) {
  node *curr = get_node(list, index);
  if (curr -> prev != NULL) curr -> prev -> next = curr -> next;
  if (curr -> next != NULL) curr -> next -> prev = curr -> prev;
  if (index == 0)
    if (list -> head -> next != NULL)
      list -> head = list -> head -> next;
    else
      list -> head = NULL;
  destroy_node(curr);
  list->size--;
}

void remove_nodes(list *list, int start, int end) {
  for (int i = 0; i < end - start; i++) // [start, end)
    remove_node(list, start);
}

void remove_duplicates(list *list) { // bug here
  for (int i = 0; i < list -> size - 1; i++) {
    int index;
    node *curr = get_node(list, i);
    while ((index = find_word(list, curr -> word -> arr, i + 1, NORMAL)) != -1)
      remove_node(list, index);
  }
}

// проверяет, нужно ли менять слова местами
int need_swap(word *w1, word *w2, int sort_type, int reverse) {
  //  1 - порядок правильный
  //  0 - слова идентичны
  // -1 - порядок неправильный
  switch (sort_type) {
    case ALPHABET:
      return compare_words(w1, w2, reverse);
    case LENGTH:
      if (w1 -> size == w2 -> size) return 0;
      else return (reverse ^ (w1 -> size > w2 -> size)) ? -1 : 1;
    case VOWELS:
      if (w1 -> vowels == w2 -> vowels) return 0;
      else return (reverse ^ (w1 -> vowels > w2 -> vowels)) ? -1 : 1;
    case CONSNTS:
      if (w1 -> consnts == w2 -> consnts) return 0;
      else return (reverse ^ (w1 -> consnts > w2 -> consnts)) ? -1 : 1;
    default:
      printf("Invalid sorting configuration!");
      return 0;
  }
}

// обычная сортировка
void sort_list(list *list, int sort_type, int reverse) {
  for (int i = 0; i < list -> size; i++) {
    for (int j = i+1; j < list -> size; j++) {
      struct node *node1 = get_node(list, i);
      struct node *node2 = get_node(list, j);
      if (need_swap(node1 -> word, node2 -> word, sort_type, reverse) < 0)
        swap_nodes(node1, node2);
    }
  }
}

// двойная сортировка
void double_sort(list *list, int sort_1, int sort_2, int order) {
  for (int i = 0; i < list -> size; i++) {
    for (int j = i+1; j < list -> size; j++) {
      struct node *node1 = get_node(list, i);
      struct node *node2 = get_node(list, j);
      int swap = need_swap(node1 -> word, node2 -> word, sort_1, order);
      switch (sort_1) { // оптимизировать
        case ALPHABET:
          if (swap >= 0)
            swap = need_swap(node1 -> word, node2 -> word, sort_2, order);
          break;
        case LENGTH:
        case VOWELS:
        case CONSNTS:
          if (!swap)
            swap = need_swap(node1 -> word, node2 -> word, sort_2, order);
          break;
        default:
          printf("Invalid sorting configuration!");
      }
      if (swap < 0) swap_nodes(node1, node2);
    }
  }
}

// новая версия двойной сортировки
void double_sort_2(list *list, int sort_1, int sort_2, int order) {
  for (int i = 0; i < list -> size; i++) {
    for (int j = i+1; j < list -> size; j++) {
      struct node *node1 = get_node(list, i);
      struct node *node2 = get_node(list, j);
      int swap = need_swap(node1 -> word, node2 -> word, sort_1, order);
      if ((sort_1 == ALPHABET && swap >= 0) || (sort_1 != ALPHABET && !swap))
        swap = need_swap(node1 -> word, node2 -> word, sort_2, order);
      if (swap < 0) swap_nodes(node1, node2);
    }
  }
}