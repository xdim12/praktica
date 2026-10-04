#include <iostream>
#include <cstddef>


int** allow_matrix (const int n)
{
  try {
    return new int*[n];
  } catch (...) {
    std::cout << "Не удалось выделить память\n";
    return nullptr;
  }
}


int* allow_line (const int n)
{
  try {
    return new int[n];
  } catch (...) {
    std::cout << "Не удалось выделить память\n";
    return nullptr;
  }
}


int main()
{
  int column = 0, line = 0;
  std::cout << "Ведите количество столбцов, а затем количество строк\n";
  
  std::cin >> column >> line;
  
  if (std::cin.fail() || column <= 0 || line <= 0) {
    std::cout << "Ошибка ввода\n";
    return 1;
  }

  int** matrix = allow_matrix(line);
  if (matrix == nullptr){
    return 2;
  }

  int** t_matrix = allow_matrix(column);
  if (t_matrix == nullptr) {
    delete[] matrix;
    return 2;
  }

  for (size_t i = 0; i < line; ++i){
    matrix[i] = allow_line(column);
    if (matrix[i] == nullptr) {
      for (int j = 0; j < i; ++j) {
        delete[] matrix[j];
      }
      delete[] matrix;
      return 2;
    }
  }
  
  for (size_t i = 0; i < column; ++i){
    t_matrix[i] = allow_line(line);
    if (t_matrix[i] == nullptr) {
      for (int j = 0; j < i; ++j) {
        delete[] t_matrix[j];
      }
      delete[] t_matrix;
      for (size_t t = 0; t < line; ++t){
        delete[] matrix[t];
      }
      delete[] matrix;
      return 2;
    }
  }

  for (size_t i = 0; i < line; ++i) {
    for (size_t j = 0; j < column; ++j) {
      std::cout << "Введите элемент под номером " << j+1 << " " << i+1 << " матрицы:\n";
      std::cin >> matrix[i][j];
      if (std::cin.fail()) {
        std::cout << "Введены не целые числа\n";
        for (int t = 0; t < line; ++t){
          delete[] matrix[t];
        }
        delete[] matrix;

        for (int t = 0; t < column; ++t){
          delete[] t_matrix[t];
        }
        delete[] t_matrix;

        return 1;
      }
    }
  }

  for (size_t i = 0; i < column; ++i){
    for (size_t j = 0; j < line; ++j ){    
      t_matrix[i][j] = matrix[j][i];
      std::cout <<  t_matrix[i][j] << " ";
    }
    std::cout << "\n";
  }

  for (size_t i = 0; i < line; ++i){
    delete[] matrix[i];
  }
  delete[] matrix;

  for (size_t i = 0; i < column; ++i){
    delete[] t_matrix[i];
  }
  delete[] t_matrix;

  return 0;
}
