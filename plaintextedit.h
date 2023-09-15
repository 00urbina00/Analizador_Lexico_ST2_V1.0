#ifndef PLAINTEXTEDIT_H
#define PLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QtWidgets>
#include <QTextCursor>

class LineNumberArea;

class PlainTextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    PlainTextEdit(QWidget* parent = nullptr);

    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void lineNumberAreaPaintEvent(QPaintEvent* event);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect& rect, int dy);
    void highlightCurrentLine();

private:
    QWidget* lineNumberArea;
    friend class LineNumberArea;
};

class LineNumberArea : public QWidget {
public:
    LineNumberArea(PlainTextEdit* editor);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    PlainTextEdit* codeEditor;
};

#endif // PLAINTEXTEDIT_H
