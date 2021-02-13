#include <QGuiApplication>
#include <QQmlApplicationEngine>

/*
 * Предметная область: Обслуживание клиентов в бюро проката автомобилей (см. п. 9.2)
 * Метод хеширования: Закрытое хеширование с линейным опробованием
 * Метод сортировк: Быстрая (Хоара)
 * Вид списка: Линейный двунаправленный
 * Метод обхода дерева: Метод обхода дерева
 * Алгоритм поиска слова в тексте: Метод обхода дерева
 */

#include "LinkList.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
