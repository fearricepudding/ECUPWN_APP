#ifndef SPLASH_H
#define SPLASH_H

#include <QMainWindow>
#include "connectionsettings.h"
#include "CAN/CanQueue.h"
#include "CAN/ConnectionManager.h"
#include "State.h"
#include "../include/json.hpp"

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
    void updateCanData();
    void treeItemClicked(QTreeWidgetItem*, int);
    void createConnection(std::string, std::string);

signals:
    void updateConnectionPage(nlohmann::json);

public:
    Splash(QWidget *parent = nullptr);
    ~Splash();

    CanQueue _canQueue;
    State *stateManager;
    nlohmann::json state;

private:
    Ui::Splash *ui;
    void setupPages();
    template <class Page>
    void addPage(std::string, std::string, Page*);
    template <class Page>
    void addPage(std::string, std::string, Page*, bool);
    std::map<std::string, std::map<std::string, int>> navigation;
    int navCount;
    void updateNavigation();
    std::map<std::string, int> findNavParent(std::string);
    int findNavItem(std::string, std::string);
    void saveState();
    void connectionClicked(std::string);
    nlohmann::json getConnectionData(std::string);
    ConnectionManager *conManager;
};
#endif // SPLASH_H
