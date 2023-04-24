#include "Lab4Exmaple.h"
#include "ComplexMatrix.h"
#include "ComplexVector.h"
#include "MyAssoc.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

/* Задача 1.1.
Створити тип даних - клас VectorInt (вектор цілих чисел), який має вказівник на
int, число елементів size і змінну стану codeError. У класі визначити

o конструктор без параметрів( виділяє місце для одного елемента та інінціалізує
його в нуль);
o конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує
масив значенням нуль);
o конструктор із двома параметрами - розмір вектора та значення
ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує
значенням другого аргументу) ;
o конструктор копіювання;
o деструктор звільняє пам'ять;
o перевантаження операцій (операції перевантажувати через функції класу або
дружні функції, якщо не вказано яким чином це робити):
• унарних префіксних та постфіксних ++ та --: одночасно збільшує
(зменшує) значення елементів масиву на 1;
• унарної логічної ! (заперечення): повертає значення true, якщо
елементи якщо size не дорівнює – нулю, інакше false;
• унарної побітової ~ (заперечення): повертає побітове заперечення для
всіх елементів масиву класу вектор;
• унарний арифметичний - (мінус) : повертає всі елементи масиву
класу вектор з протилежним знаком;
• присвоєння =: копіює вектор(перевантажити через функцію класу);
• присвоєння з (перевантажити через функцію класу)
o += - додаванням векторів;
o -= - відніманням векторів;
o *= - множення, вектора на число типу int;
o /= - ділення, вектора на число типу int;
o %= - остача від ділення, вектора на число типу int;
o |= -побітове додаванням векторів;
o ^= - побітове додавання за модулем 2 векторів;
o &= - побітове по-елементне множення векторів;
• арифметичних бінарні:
o + - додавання векторів;
o – - віднімання векторів;
o * - множення, вектора на число типу int;
o / - ділення, вектора на число типу int;
o % - остача від ділення, вектора на число типу int;
• побітові бінарні
o | - побітове додавання векторів;
o ^ - побітове додавання за модулем 2 векторів;
o & - побітове по-елементне множення векторів;
• побітові операції зсувів, як дружні операції введення та виведення
вектора у потік (перевантажувати через дружні функції)
o введення >> (побітовий зсув право) ;
o введення << (побітовий зсув ліво);
• рівності == та нерівності!= , функція-операція виконує певні дії над
кожною парою елементів векторів за індексом;
• операцію індексації [] – функцію, яка звертається до елементу
масиву за індексом, якщо індекс невірний функція вказує на останній
елемент масиву та встановлює код помилки у змінну codeError;
• розподілу пам’яті new та delete;
• виклику функції ();
• порівняння (функція-операція виконує певні дії над кожною парою
елементів векторів за індексом), які повертають true або false:
o > (більше) для двох векторів;
o >= (більше рівне) для двох векторів;
o < (менше) для двох векторів;
o <=(менше рівне) для двох векторів.
У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за
межі масиву. Передбачити можливість підрахунку числа об'єктів даного типу.
Перевірити роботу цього класу.  */

enum codeError { None, BAD_INIT, BAD_DIV };

class VectorInt {
  int *point;
  int size;
  int codeError = None;

public:
  VectorInt() {
    size = 1;
    point = new int(size);
    point[0] = 0;
  }
  VectorInt(int len) {
    size = len;
    point = new int(size);
    for (int i = 0; i < size; i++) {
      point[i] = 0;
    }
  }

  VectorInt(int len, int value) {
    size = len;
    point = new int(size);
    for (int i = 0; i < size; i++) {
      point[i] = value;
    }
  }

  VectorInt(VectorInt &v) {
    size = v.size;
    if (v.point == nullptr) {
      codeError = BAD_INIT;
    }
    point = new int(v.size);
    for (int i = 0; i < v.size; i++) {
      point[i] = v.point[i];
    };
    codeError = v.codeError;
  }

  ~VectorInt() { delete[] point; }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << point[i] << " ";
    }
    cout << endl;
  };

  VectorInt operator++() {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] + 1;
    };
    return *this;
  };

  VectorInt operator--() {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] - 1;
    };
    return *this;
  };

  VectorInt &operator++(int) {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] + 1;
    };
    return *this;
  };

  VectorInt &operator--(int) {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] - 1;
    };
    return *this;
  };

  bool operator!() {
    if (size) {
      return true;
    }
    return false;
  }

  VectorInt operator~() {
    VectorInt result(*this);
    for (int i = 0; i < size; i++) {
      result.point[i] = ~point[i];
    };
    return result;
  }

  VectorInt operator-() {
    VectorInt result(*this);
    for (int i = 0; i < size; i++) {
      result.point[i] = -point[i];
    };
    return result;
  }

  VectorInt &operator=(const VectorInt &v) {
    if (this != &v) {
      delete[] point;
      point = new int[v.size];
      for (int i = 0; i < v.size; i++) {
        point[i] = v.point[i];
      }
      size = v.size;
      codeError = v.codeError;
    }
    return *this;
  }

  VectorInt &operator+=(const VectorInt &v) {
    if (size != v.size) {
      codeError = 1;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] += v.point[i];
    }
    return *this;
  }

  VectorInt &operator-=(const VectorInt &v) {
    if (size != v.size) {
      codeError = 1;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] -= v.point[i];
    }
    return *this;
  }

  VectorInt &operator*=(int value) {
    for (int i = 0; i < size; i++) {
      point[i] *= value;
    }
    return *this;
  }

  VectorInt &operator/=(int value) {
    if (value == 0) {
      codeError = 2;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] /= value;
    }
    return *this;
  }

  VectorInt &operator%=(int value) {
    if (value == 0) {
      codeError = 2;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] %= value;
    }
    return *this;
  }

  VectorInt &operator|=(const VectorInt &v) {
    if (size != v.size) {
      codeError = 1;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] |= v.point[i];
    }
    return *this;
  }

  VectorInt &operator^=(const VectorInt &v) {
    if (size != v.size) {
      codeError = 1;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] ^= v.point[i];
    }
    return *this;
  }

  VectorInt &operator&=(const VectorInt &v) {
    if (size != v.size) {
      codeError = 1;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] &= v.point[i];
    }
    return *this;
  }

  VectorInt operator+(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = 1;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] + v.point[i];
    }
    return result;
  }
  VectorInt operator-(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = 1;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] - v.point[i];
    }
    return result;
  }
  VectorInt operator*(int n) {
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] * n;
    }
    return result;
  }
  VectorInt operator/(int n) {
    if (n == 0) {
      VectorInt result;
      result.codeError = 2;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] / n;
    }
    return result;
  }
  VectorInt operator%(int n) const {
    if (n == 0) {
      VectorInt result;
      result.codeError = 2;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] %= n;
    }
    return result;
  }

  VectorInt operator|(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = 1;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] | v.point[i];
    }
    return result;
  }

  VectorInt operator^(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = 1;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] ^ v.point[i];
    }
    return result;
  }

  VectorInt operator&(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = 1;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] & v.point[i];
    }
    return result;
  }

  friend istream &operator>>(istream &input, VectorInt &vector);
  friend ostream &operator<<(ostream &output, const VectorInt &vector);

  bool operator==(const VectorInt &v) {
    if (size != v.size) {
      return false;
    }
    for (int i = 0; i < size; i++) {
      if (point[i] != v.point[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const VectorInt &v) {
    if (size != v.size) {
      return true;
    }
    for (int i = 0; i < size; i++) {
      if (point[i] != v.point[i]) {
        return true;
      }
    }
    return false;
  }

  int operator[](int index) {
    if (index < 0 || index > size) {
      index = size;
    }

    return point[index];
  }

  bool operator>(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 > length2) {
      return true;
    }
    return false;
  }

  bool operator>=(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 >= length2) {
      return true;
    }
    return false;
  }

  bool operator<(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 < length2) {
      return true;
    }
    return false;
  }

  bool operator<=(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 <= length2) {
      return true;
    }
    return false;
  }
};

istream &operator>>(istream &input, VectorInt &v) {
  for (int i = 0; i < v.size; i++) {
    input >> v.point[i];
  }
  return input;
}

ostream &operator<<(ostream &output, const VectorInt &v) {
  for (int i = 0; i < v.size; i++) {
    output << v.point[i] << '\t';
  }
  output << endl;
  return output;
}

int mainExample1() {
  VectorInt v1(3, 3);
  VectorInt v2(3, 5);
  VectorInt v3(3, 3);
  v3++;
  v3 = v3 + v1;
  v1++;
  v3 = -v3;
  v3.print();
  v1.print();
  cout << (v3 > v3);
  cout << v3[2];
  return 0;
};

/// <summary>
/// Задано : A,B,C,D,F  -  Матриці комплесних чисел
///          a,b,c  -  Вектори комплесних чисел
///          _a,_b,_c - комплексні числа.
/// Обчислити вираз : F = A+B*_a-B*_c+C/_b;
///                   c = F*a + D*b
/// </summary>
/// <returns></returns>

int mainExample2() {
  ComplexMatrix A(5), B(5), C(5), D(5), F(5);
  ComplexVector a(5), b(5), c(5);
  ComplexDouble _a(3.2, 5), _b(1, 2), _c = RandComplexDouble();

  A.RandComplexMatrix();
  B.RandComplexMatrix();
  C.RandComplexMatrix();
  D.RandComplexMatrix();
  a.RandComplexVector();
  b.RandComplexVector();
  c.RandComplexVector();

  cout << endl;
  cout << "Matrix A \n" << A;
  cout << "Matrix B \n" << B;
  cout << "Matrix C \n" << C;
  cout << "Matrix D \n" << D;
  cout << endl;
  cout << "Vector a \n" << a;
  cout << "Vector b \n" << b;
  cout << "Vector c \n" << c;

  /// Обчислити вираз : F = A+B*_a-B*_c+C/_b;
  ///                   c = F*a + D*b
  F = A + B * _a - B * _c + C / _b;
  cout << "Matrix F \n" << F;
  c = F * a + D * b;
  cout << "Vector c \n" << c;

  return 0;
}
int mainExample3() {
  cout << " End begin \n";
  uint Flight[5] = {12, 32, 23, 43, 43};
  MyTime MTime[5] = {{9, 10}, {10, 30}, {10, 30}, {10, 30}, {15, 35}};
  MyAssoc dbase(5, Flight, MTime);
  dbase.TableFlight();
  MyTime r = {10, 30}, ro;
  uint fli = 32;
  ro = dbase[fli];
  cout << " Test : MyTime operator[](uint&s  )  "
       << "Flight " << fli << " time   " << ro << endl;
  cout << " Test : uint	operator[](MyTime&s)  "
       << " time  " << r << " light  " << dbase[r] << endl;
  cout << " Flight with time :   9   to  11 \n";
  dbase(9, 11);
  cout << " End test \n";
  return 4;
}
