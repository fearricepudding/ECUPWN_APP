#ifndef CODELOOKUP_H
#define CODELOOKUP_H

#include <QMainWindow>

namespace Ui {
class CodeLookup;
}

class CodeLookup : public QMainWindow
{
    Q_OBJECT

private slots:
    void exit_app();
    void lookupCode();

public:
    explicit CodeLookup(QWidget *parent = nullptr);
    ~CodeLookup();

private:
    Ui::CodeLookup *ui;
};

#endif // CODELOOKUP_H
