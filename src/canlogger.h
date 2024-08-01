#ifndef CANLOGGER_H
#define CANLOGGER_H

#include <QDialog>

namespace Ui {
class CanLogger;
}

class CanLogger : public QDialog
{
    Q_OBJECT

private slots:
    void addTest();
    void remoteStartLog();
    void newData(QString);

signals:
    void startLog();

public:
    explicit CanLogger(QWidget *parent = nullptr);
    ~CanLogger();

private:
    Ui::CanLogger *ui;
    std::vector<std::string> canMessages;
    void renderCanLogs();
    int counter;
    int scrollLimit;
};

#endif // CANLOGGER_H
