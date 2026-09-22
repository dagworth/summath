#include <QApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QTextDocument>
#include <QTextBlock>

#include "solve.h"

struct LineData : QTextBlockUserData {
    Line line;
};

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

    QObject::connect(input->document(), &QTextDocument::contentsChange, [input](int position, int charsRemoved, int charsAdded) {
        QTextDocument *doc = input->document();
        QTextBlock start = doc->findBlock(position);

        for (QTextBlock b = start; b.isValid(); b = b.next()) {
            LineData *data = static_cast<LineData*>(b.userData());
            if (!data) {
                data = new LineData;
                b.setUserData(data);
            }
            std::string text = b.text().toStdString();
            bool changed = data->line.text != text;
            sync(data->line, b.blockNumber(), text, changed);
        }
    });

    // QObject::connect(input, &QPlainTextEdit::textChanged, [input, label]() {
    //     std::string result = solve(input->toPlainText().toStdString());
    //     QString a = QString::fromStdString(result);
    //     label->setText(a);
    // });

    window.show();
    return app.exec();
}