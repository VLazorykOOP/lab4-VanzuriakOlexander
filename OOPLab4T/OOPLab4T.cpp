// OOPLab4T.cpp : Цей файл містить є шаблоном для
// виконання лаб. роботи №4.
// Він містинь функцію "main" з якої починається та закінчується виконання
// програми.
//

#include <fstream>
#include <iostream>
using namespace std;

// Ваші файли загловки
//
void ShowTaskMenu() {
  cout << "Exersices" << endl;
  cout << "1. Task 1" << endl;
  cout << "2. Task 2" << endl;
}

#include "Lab4Exmaple.h"
int main() {
  bool isSelected = false;
  while (!isSelected) {
    system("cls");
    ShowTaskMenu();
    int ch;
    cin >> ch;
    switch (ch) {
    case 1:
      exersice1();
      isSelected = true;
      break;
    case 2:
      exersice2();
      isSelected = true;
      break;
    default:
      break;
    }
  }
}