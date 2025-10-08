#include <iostream>
#include <fstream>
using namespace std;

struct Book {
    char title[100];
    char author[50];
    int year;
    float rating;
};
Book books[1000];
int bookCount = 0;
int bookex = 0;
int main() {
    int choice;
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "Файл с данными не найдем. Создан новый\n";
    } else {
        file >> bookCount;
        file.ignore();
        for(int i = 0; i < bookCount; i++) {
            file.getline(books[i].title, 100);
            file.getline(books[i].author, 50);
            file >> books[i].year;
            file >> books[i].rating;
            file.ignore();
        }
        file.close();
        cout << "Данные загружены из файла! Загружено книг: " << bookCount << endl;
    }
    do {
        cout << "\nТрекер книг\n";
        cout << "1. Добавить книгу\n";
        cout << "2. Показать все книги\n";
        cout << "3. Показать статистику\n";
        cout << "4. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;
        if (choice==1) {
            cout <<"Добавить новую книгу \n";
            cout <<"\nВведите название книги: \n";
            cin.ignore();
            cin.getline(books[bookCount].title,100);
            cout <<"Введите автора: \n";
            cin.ignore();
            cin.getline(books[bookCount].author,100);
            cout <<"Введите год прочтения:\n";
            cin.ignore();
            cin >> books[bookCount].year;
            cout << "Ваша оценка по 10-балльной шкале:\n";
            cin >> books[bookCount].rating;
            bookCount++;
            cout <<"\nКнига добавлена!\n";
        } else if (choice==2) {
            cout << "\nСписок всех книг\n";
            for(int i = 0; i < bookCount; i++) {
                cout << i + 1 << ". \"" << books[i].title << "\" - "
                     << books[i].author << " (" << books[i].year
                     << ") Оценка: " << books[i].rating << endl;
            }
            if(bookCount == 0) {
                cout << "Книг пока нет.\n";
            }
        } else if (choice==3) {
            cout << "\nСтатистика за всё время\n";
            int booktotal = bookCount;
            if (booktotal == 0) {
                cout << "Книг пока нет.\n";
            } else {
                cout << "Количество прочитанный книг: \n" << booktotal << endl;
                float maxbookraiting = 0;
                float srrating = 0;
                float sumrating = 0;
                int bestbook = 0;
                for (int i = 0; i < booktotal; i++) {
                    sumrating += books[i].rating;
                }
                srrating = sumrating / booktotal;
                cout << "Средняя оценка: " << srrating << endl;
                for (int i = 0; i < booktotal;i++) {
                    if (books[i].rating > maxbookraiting) {
                        maxbookraiting = books[i].rating;
                        bestbook = i;
                    }
                }
                cout << "Самая высокая оценка: \""
             << books[bestbook].title << "\" - "
             << books[bestbook].author
             << " (Оценка: " << maxbookraiting << ")" << endl;
            }

        } else if (choice==4) {
            ofstream file("books.txt");

            if(!file.is_open()) {
                cout << "Ошибка открытия файла для записи!\n";
                return 1;
            }

            file << bookCount << endl;

            for(int i = 0; i < bookCount; i++) {
                file << books[i].title << endl;
                file << books[i].author << endl;
                file << books[i].year << endl;
                file << books[i].rating << endl;
            }

            file.close();
            cout << "Данные сохранены в файл!\n";
        }

    } while (choice !=3);
    return 0;
}
