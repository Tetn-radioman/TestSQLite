#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 1. Подключаем SQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");   // файл базы данных

    if (!db.open()) {
        qDebug() << "Ошибка открытия БД:" << db.lastError().text();
        return 1;
    }

    qDebug() << "# База данных открыта!";

    // 2. Создаём таблицу
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY, name TEXT)");// это запрос к бд если нет таблицы создай такую

    qDebug() << "# Готово! Файл test.db создан в папке с программой.";

    std::string str;
    QString Qstr;
    while(true){
        std::cout<<"Текущая Таблица:"<<std::endl;
        // 4. Читаем и выводим
        query.exec("SELECT * FROM people");
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            qDebug() << "> ID:" << id << "Имя:" << name;
        }

        std::cout<<"Добавить имя: ";
        std::getline(std::cin, str);        // читаем строку

        str = "INSERT INTO people (name) VALUES ('"+str+"')";
        query.exec(QString::fromStdString(str));// 3. Вставляем запись
        printf("\033c");
    }
    return 0;
}
