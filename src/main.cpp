#include <QApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QTextDocument>
#include <QTextBlock>
#include <sstream>
#include <iostream>

#include "solve.h"

using namespace std;

struct LineData : QTextBlockUserData {
    Line line;
};

const QTextDocument *main_doc;
vector<Line*> lines;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;

    auto *layout = new QHBoxLayout(&window);
    auto *label = new QLabel("cool calculator");
    auto *input = new QPlainTextEdit();

    input->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    main_doc = input->document();

    layout->addWidget(input);
    layout->addWidget(label);

    QObject::connect(main_doc, &QTextDocument::contentsChange, [input, label](int position, int charsRemoved, int charsAdded) {
        QTextBlock start = main_doc->findBlock(position);

        for (QTextBlock b = start; b.isValid(); b = b.next()) {
            LineData *data = static_cast<LineData*>(b.userData());
            if (!data) {
                data = new LineData;
                b.setUserData(data);
            }
            string text = b.text().toStdString();
            bool changed = data->line.text != text;
            sync(data->line, b.blockNumber(), text, changed);
            
            int index = b.blockNumber();
            if (index >= (int)lines.size()) lines.resize(index + 1);
            lines[index] = &data->line;
        }

        if ((int)lines.size() > main_doc->blockCount()) {
            lines.resize(main_doc->blockCount());
        }

        eval_lines(lines);
        //int a = system("clear");

        stringstream result;
        for (QTextBlock b = main_doc->begin(); b.isValid(); b = b.next()) {
            LineData *data = static_cast<LineData*>(b.userData());
            result << data->line.answer << '\n';
            //cout << data->line.answer << '\n';
        }

        label->setText(QString::fromStdString(result.str()));
    });

    // QObject::connect(input, &QPlainTextEdit::textChanged, [input, label]() {
    //     std::string result = solve(input->toPlainText().toStdString());
    //     QString a = QString::fromStdString(result);
    //     label->setText(a);
    // });

    window.show();
    return app.exec();
}

Line* getLine(int num) {
    QTextBlock block = main_doc->findBlockByNumber(num);
    if (!block.isValid()) return nullptr;

    LineData *data = static_cast<LineData*>(block.userData());
    return &data->line;
}