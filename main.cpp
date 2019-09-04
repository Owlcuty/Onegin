#define EOF 0

#include <stdio.h>
#include <assert.h>
#include <string>
#include <cstring>

const int Max_row = 6500;


// ----- Reading file --------------------------------------------------------------------------------------------------

int fread_string(std::string rows[], int max_num, FILE * inp) {

  std::string now = "";
  int cnt = 0; // num of words
  int cnt_in_row = 0;
  char c = 'c';
  int last_row = 0;

  while (c != EOF) {
    assert(last_row < max_num);

    c = fgetc(inp);

    if (c == '\n' || c == EOF) {
      if (!cnt_in_row) {
        continue;
      }
      rows[last_row++] = now;
      now = "";
      cnt_in_row = 0;
      cnt ++;
      continue;
    }

    now += c;
    cnt_in_row ++;
  }
  return cnt;
}

// ---------------------------------------------------------------------------------------------------------------------

// String comprasion ---------------------------------------------------------------------------------------------------

bool comparator(std::string a, std::string b) {
  char c1 = a[0];
  char c2 = b[0];

  int aLen = strlen(a.c_str());
  int bLen = strlen(b.c_str());

  int now = 0;

  while (c1 == c2 && now + 1 < (aLen < bLen) ? aLen : bLen) {
    c1 = a[now];
    c2 = b[now];
    if (a[now] < b[now]) {
      return true;
    }
    if (a[now] > b[now]) {
      return false;
    }
    now ++;
  }
  return (aLen < bLen);
}

// ---------------------------------------------------------------------------------------------------------------------

// Heap sort -----------------------------------------------------------------------------------------------------------

void heapify(std::string array[], int num_elem, int v)
{
    int largest = v;
    int left_child = 2 * v + 1;
    int right_child = 2 * v + 2;

    std::string temp = "";

    if (left_child < num_elem && !comparator(array[left_child], array[largest]))
        largest = left_child;

    if (right_child < num_elem && !(comparator(array[right_child], array[largest])))
        largest = right_child;

    if (largest != v)
    {
        temp = array[v];
        array[v] = array[largest];
        array[largest] = temp;

        heapify(array, num_elem, largest);
    }
}


void build_heap(std::string array[], int num_elem) {
    int ind = num_elem / 2 - 1;

    for (int i = ind; i >= 0; i --) {
        heapify(array, i, 0);
    }

//    for (int i = 0; i < num_elem; i ++) {
//        printf("%i ", array[i]);
//        if (i == num_elem - 1) printf("\n");
//    }
}

void heap_sort(std::string array[], int num_elem) {
    build_heap(array, num_elem);

    std::string temp = "";
    for (int i = num_elem - 1; i >= 0; i --) {
        temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0);
    }
}

// ----------------------------------------------------------------------------------------------------------------------


int main() {
  FILE * ftext  = fopen("Onegin.txt", "r");

  FILE * result = fopen("IdealOnegin.txt", "w");
  setvbuf(result, nullptr, _IONBF, 0);


  std::string rows[Max_row] = {};

  int num_rows = fread_string(rows, Max_row, ftext);

  printf("%i:: num of rows = %i" "\n", __LINE__, num_rows);

  heap_sort(rows, num_rows);

  for (int row = 0; row < num_rows; row ++) {
    fprintf(result, "%s" "\n", (rows[row]).c_str());
  }

  fclose(ftext);
  fclose(result);
}
