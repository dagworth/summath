#include <QApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QWidget>

#include "solve.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    auto *layout = new QHBoxLayout(&window);
    auto *label = new QLabel("cool calculator");
    auto *input = new QPlainTextEdit();

    input->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    layout->addWidget(input);
    layout->addWidget(label);

    QObject::connect(input, &QPlainTextEdit::textChanged, [input, label]() {
        std::string result = solve(input->toPlainText().toStdString());
        QString a = QString::fromStdString(result);
        label->setText(a);
    });

    window.show();
    return app.exec();
}