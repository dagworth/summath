#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    auto *layout = new QVBoxLayout(&window);
    auto *label = new QLabel("cool calculator");
    auto *input = new QLineEdit();

    layout->addWidget(label);
    layout->addWidget(input);

    window.show();
    return app.exec();
}