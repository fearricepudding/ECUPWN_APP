#ifndef CANLOGGER_H
#define CANLOGGER_H

#include "../CAN/CanQueue.h"

#include <QDialog>

namespace Ui {
class CanLogger;
}

class CanLogger : public QDialog
{
    Q_OBJECT

public slots:
    void addTest();
    void remoteStartLog();
    void newData(QString);
    void updateLogWindow();

signals:
    void startLog();

public:
    explicit CanLogger(CanQueue*);
    ~CanLogger();

private:
    Ui::CanLogger *ui;
    std::vector<std::string> canMessages;
    void renderCanLogs();
    int counter;
    int scrollLimit;
    CanQueue *canData;
};

#endif // CANLOGGER_H
