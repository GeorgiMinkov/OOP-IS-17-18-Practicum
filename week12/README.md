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

    list<int> li;
    for (int i = 0; i < 5; i++)
      li.push_back(i);

    list<int> mapped = map(li, &increment);
    // Ще изведе списъка 1, 2, 3, 4, 5
    for (list<int>::iterator it = mapped.begin(); it != mapped.end(); it++)
      cout << *it << " ";

    list<int> filtered = filter(li, &filt);
    // Ще изведе списъка 2, 3, 4
    for (list<int>::iterator it = filtered.begin(); it != filtered.end(); it++)
      cout << *it << " ";

    // Ще изведе 10, т.е. сумата на елементите, започвайки от начална стойност 0
    cout << reduce(li, 0, &add);

