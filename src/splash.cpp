#include "splash.h"
#include "../ui/ui_splash.h"
#include "./utils/codelookup.h"
#include "./utils/canlogger.h"
#include "./connectionsettings.h"
#include "./existingconnection.h"
#include "../candy/src/candy.h"
#include "CAN/ConnectionManager.h"
#include "State.h"

#include <QThread>
#include <QTreeWidgetItem>
#include <QTreeView>
#include <map>

Splash::Splash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Splash)
{
    this->stateManager = new State("data.json");
    this->state = stateManager->load();

    ui->setupUi(this);

    this->conManager = new ConnectionManager();
    this->navCount = 1;

    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit_app()));
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(treeItemClicked(QTreeWidgetItem *, int)));

    this->setupPages();
}

void Splash::saveState() {
    this->stateManager->save(this->state);
};

template <class Page>
void Splash::addPage(std::string parent, std::string name, Page *page) {
    ui->stackedWidget->addWidget(page);

    std::map<std::string, int> navitems = this->findNavParent(parent);

    navitems[name] = this->navCount;
    this->navCount++;

    this->navigation[parent] = navitems;
}

std::map<std::string, int> Splash::findNavParent(std::string parentName) {
    std::map<std::string, int> parent;
    for (auto& [key, value] : this->navigation) {
        std::string name = (std::string) key;
        if (parentName.compare(name) == 0) {
            parent = value;
        };
    };
    return parent;
};

int Splash::findNavItem(std::string parentName, std::string itemName) {
    std::map<std::string, int> parent = this->findNavParent(parentName);
    for (auto& [key, value] : parent) {
        std::string name = (std::string) key;
        if (itemName.compare(name) == 0) {
            return (int) value;
        };
    };
    return 1;
};

void Splash::updateNavigation() {

    QTreeWidget * tree = ui->treeWidget;
    tree->clear();

    for (auto& [key, value] : this->navigation) {
        QTreeWidgetItem * topLevel = new QTreeWidgetItem();
        topLevel->setText(0, QString::fromStdString(key));
        for (auto& [itemKey, itemValue] : value) {
            QTreeWidgetItem * item = new QTreeWidgetItem();
            item->setText(0, QString::fromStdString(itemKey));
            topLevel->addChild(item);
        };

        tree->addTopLevelItem(topLevel); 
    }
}

void Splash::treeItemClicked(QTreeWidgetItem *item, int index) {
    QTreeWidgetItem *parent = item->parent();
    if(!parent){
        return;
    };

    std::string parentName = parent->text(0).toStdString();
    std::string itemName = item->text(0).toStdString();

    int navIndex = this->findNavItem(parentName, itemName);
    ui->stackedWidget->setCurrentIndex(navIndex);
};

Splash::~Splash()
{
    delete ui;
}

void Splash::setupPages(){
    ui->stackedWidget->setCurrentIndex(0);

    ExistingConnection *existingConnectionPage = new ExistingConnection();
    try {
        nlohmann::json connections = this->state["connections"];
        for (auto& [key, value] : connections.items()) {
            nlohmann::json connection = nlohmann::json(value);
            std::string name = connection["name"];
            this->addPage("Connections", name, existingConnectionPage);
        };
    } catch(nlohmann::json::parse_error &e) {
        std::cout << "No connections found" << std::endl;
    } catch(nlohmann::json::out_of_range &e) {
        std::cout << "No connections found" << std::endl;
    } catch(nlohmann::json::type_error &e) {
        std::cout << "No connections found" << std::endl;
    };

    ConnectionSettings* connPage = new ConnectionSettings;
    connect(connPage, SIGNAL(createConnection(std::string, std::string)), this, SLOT(createConnection(std::string, std::string)));
    this->addPage("ECUPWN", "Create connection", connPage);

    CanLogger *logPage = new CanLogger;
    this->addPage("Utils", "Can logger", logPage);

    CodeLookup *lookup = new CodeLookup;
    this->addPage("Utils", "DTC lookup", lookup);

    this->updateNavigation();
};

void Splash::exit_app()
{
    QApplication::exit();
}

void Splash::lookup_code(){
    CodeLookup *lookupWindow = new CodeLookup;
    lookupWindow->show();
}

void Splash::can_logger(){
    CanLogger *canLogger = new CanLogger;
    //connect(worker, SIGNAL(valueChanged(QString)), canLogger, SLOT(newData(QString)));
    connect(canLogger, SIGNAL(startLog()), this, SLOT(testLog()));
    canLogger->show();
}

void Splash::createConnection(std::string ip, std::string port) {
    std::cout << "Creating connection for: " << ip << " : " << port << std::endl;
    nlohmann::json newConnection;
    newConnection["ip"] = ip;
    newConnection["port"] = port;
    newConnection["name"] = "connection name";

    nlohmann::json connections = this->state["connections"];
    connections.push_back(newConnection);
    this->state["connections"] = connections;
    this->updateNavigation();
};