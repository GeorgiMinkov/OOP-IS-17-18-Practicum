Помните ли функции от по-висок ред? Не? Спокойно, сега ще си ги припомните. Да се напишат шаблонни функции `map`, `filter` и `reduce` за списъци (`reduce` работи като `foldl`, т.е. прилага се функция върху списъка отляво надясно).


Работа на примерен код:

    int increment(int x) {
      return x + 1;
    }

    bool filt(int x) {
      return x >= 2;
    }

    int add(int a, int b) {
      return a + b;
    }

    ...

    vector<int> arr;
    for (int i = 0; i < 5; i++)
      arr.push_back(i);

    vector<int> mapped = map(arr, &increment);
    // Ще изведе списъка 1, 2, 3, 4, 5
    for (int i = 0; i < mapped.size(); i++)
      cout << mapped[i] << " ";

    vector<int> filtered = filter(arr, &filt);
    // Ще изведе списъка 2, 3, 4
    for (int i = 0; i < filtered.size(); i++)
      cout << filtered[i] << " ";

    // Ще изведе 10, т.е. сумата на елементите, започвайки от начална стойност 0
    cout << reduce(arr, 0, &add);

