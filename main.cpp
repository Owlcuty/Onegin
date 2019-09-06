#define EOF 0

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <cstring>
#include <algorithm>

const int Max_row = 6500;

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

bool is_letter(char c) {
  return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

// ----- Reading file --------------------------------------------------------------------------------------------------

int fread_string(std::string rows[], int max_num, FILE * inp) {

  std::string now = "";
  int cnt = 0; // num of words
  int cnt_in_row = 0;
  char c = 'c';
  int last_row = 0;
  int cnt_letter = 0;

  while (c != EOF) {
    assert(last_row < max_num);

    c = fgetc(inp);
    if (is_letter(c)) cnt_letter ++;

    if (c == '\n' || c == EOF) {
      if (!cnt_in_row || !cnt_letter) {
        continue;
      }
      rows[last_row++] = now;
      now = "";
      cnt_in_row = 0;
      cnt_letter = 0;
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

  int a_now = 0;
  int b_now = 0;

  for (int chr = 0; chr < aLen; chr ++) {
    if (is_letter(a[chr])) {
      a_now = chr;
      break;
    }
  }

  for (int chr = 0; chr < bLen; chr ++) {
    if (is_letter(b[chr])) {
      b_now = chr;
      break;
    }
  }

  c1 = a[a_now];
  c2 = b[b_now];

  if (c1 != c2) {
    // printf("%i:: %c != %c" "\t" "%s" "\n" "%s" "\n", __LINE__, c1, c2, a.c_str(), b.c_str());
    return c1 < c2;
  }
  while (c1 == c2 && a_now < aLen && b_now < bLen) {
    while (a_now < aLen && !is_letter(a[a_now])) {a_now ++;}
    while (b_now < bLen && !is_letter(b[b_now])) {b_now ++;}
    if (a_now >= aLen -1 || b_now >= bLen - 1) break;
    c1 = tolower(a[a_now++]);
    c2 = tolower(b[b_now++]);
    if (c1 < c2) {
      // printf("%i:: %c != %c" "\t" "%s" "\n" "%s" "\n", __LINE__, c1, c2, a.c_str(), b.c_str());
      return true;
    }
    if (c1 > c2) {
      // printf("%i:: %c != %c" "\t" "%s" "\n" "%s" "\n", __LINE__, c1, c2, a.c_str(), b.c_str());
      return false;
    }
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

    if (left_child < num_elem  && !comparator(array[left_child], array[largest]))
        largest = left_child;

    if (right_child < num_elem && !comparator(array[right_child], array[largest]))
        largest = right_child;

    if (largest != v)
    {
      array[v].swap(array[largest]);

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

    for (int i = num_elem - 1; i >= 0; i --) {
      array[0].swap(array[i]);

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

  // heap_sort(rows, num_rows);

  std::sort(rows, rows + num_rows, comparator);

  for (int row = 0; row < num_rows; row ++) {
    fprintf(result, "%s" "\n", (rows[row]).c_str());
  }

  fclose(ftext);
  fclose(result);
}
