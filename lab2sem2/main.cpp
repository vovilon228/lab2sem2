#include "Library.h"
#include <QApplication>
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

// PrintData реалізує інтерфейс Strategy і надає алгоритм для друку даних.
class PrintData : public Strategy {
public:
    // Виконує алгоритм друку даних.
    void executeAlgorithm() const override {
        qDebug() << "Printing data.";
    }
};

// SaveData реалізує інтерфейс Strategy і надає алгоритм для зберігання даних.
class SaveData : public Strategy {
public:
    // Виконує алгоритм зберігання даних.
    void executeAlgorithm() const override {
        qDebug() << "Saving data.";
    }
};

// UpdateObserver реалізує інтерфейс Observer для реагування на оновлення від Subject.
class UpdateObserver : public Observer {
public:
    // Реагує на оновлення, відображаючи сповіщення.
    void update() override {
        qDebug() << "Operation performed.";
        QMessageBox::information(nullptr, "Notification", "Operation performed successfully!");
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QMainWindow window;
    QComboBox comboBox;
    QPushButton button("Execute");
    QVBoxLayout layout;

    // Контекст використовує об'єкти Strategy для виконання алгоритму.
    Context context(std::make_unique<PrintData>());
    // Subject керує спостерігачами.
    Subject subject;
    // Спостерігач реагує на оновлення від предмета.
    UpdateObserver observer;

    // Налаштовуємо розташування вікна
    layout.addWidget(&comboBox);
    layout.addWidget(&button);
    window.setLayout(&layout);
    window.show();

    // Додаємо елементи до комбінаторного поля з відповідною стратегією
    comboBox.addItem("Print", QVariant::fromValue(std::make_unique<PrintData>()));
    comboBox.addItem("Save", QVariant::fromValue(std::make_unique<SaveData>()));

    // Підключаємо сигнал натискання кнопки "Виконати" до лямбди, яка виконує обрану стратегію.
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        // Встановлюємо стратегію залежно від вибору в комбінаторному полі.
        context.setStrategy(comboBox.currentData().value<std::unique_ptr<Strategy>>());
        // Виконуємо обрану стратегію.
        context.executeStrategy();
        // Приєднуємо спостерігача до предмета.
        subject.attach(&observer);
        // Повідомляємо спостерігачів, що предмет оновлено.
        subject.notify();
        // Від'єднуємо спостерігача після сповіщення.
        subject.detach(&observer);
    });

    return a.exec();
}
