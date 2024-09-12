#ifndef SPLASH_H
#define SPLASH_H

#include <QMainWindow>
#include "canworker.h"
#include "connectionsettings.h"
#include "CanQueue.h"
#include "ConnectionManager.h"
#include <map>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class Splash;
}
QT_END_NAMESPACE

class Splash : public QMainWindow
{
    Q_OBJECT

private slots:
    void exit_app();
    void lookup_code();
    void can_logger();
    void treeItemClicked(QTreeWidgetItem*, int);

public:
    Splash(QWidget *parent = nullptr);
    ~Splash();

private:
    Ui::Splash *ui;
    void setupPages();
    template <class Page>
    void addPage(std::string, std::string, Page*);
    std::map<std::string, std::map<std::string, int>> navigation;
    int navCount;
    void updateNavigation();
    std::map<std::string, int> findNavParent(std::string);
    int findNavItem(std::string, std::string);
    CanQueue _canQueue;
    ConnectionManager *conManager;
};
#endif // SPLASH_H
