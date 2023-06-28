#include "Library.h"
#include <QApplication>
#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>


class PrintData : public Strategy {
public:
    // Виконує алгоритм друку даних.
    void executeAlgorithm() const override {
        qDebug() << "Printing data.";
    }
};


class SaveData : public Strategy {
public:
    // Виконує алгоритм зберігання даних.
    void executeAlgorithm() const override {
        qDebug() << "Saving data.";
    }
};

class UpdateObserver : public Observer {
public:

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

    Context context(std::make_unique<PrintData>());

    Subject subject;

    UpdateObserver observer;


    layout.addWidget(&comboBox);
    layout.addWidget(&button);
    window.setLayout(&layout);
    window.show();


    comboBox.addItem("Print", QVariant::fromValue(std::make_unique<PrintData>()));
    comboBox.addItem("Save", QVariant::fromValue(std::make_unique<SaveData>()));

    QObject::connect(&button, &QPushButton::clicked, [&]() {

        context.setStrategy(comboBox.currentData().value<std::unique_ptr<Strategy>>());

        context.executeStrategy();

        subject.attach(&observer);

        subject.notify();

        subject.detach(&observer);
    });

    return a.exec();
}
