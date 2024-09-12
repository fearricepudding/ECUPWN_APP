#include "splash.h"
#include "./codelookup.h"
#include "../ui/ui_splash.h"
#include "./canlogger.h"
#include "./connectionsettings.h"
#include "../candy/src/candy.h"
#include "ConnectionManager.h"
#include <QThread>
#include <QTreeWidgetItem>
#include <QTreeView>
#include <map>

Splash::Splash(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Splash)
{
    ui->setupUi(this);

    this->conManager = new ConnectionManager();
    this->navCount = 1;

    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exit_app()));
    connect(ui->codeLookup, SIGNAL(clicked()), this, SLOT(lookup_code()));
    connect(ui->canLogger, SIGNAL(clicked()), this, SLOT(can_logger()));
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *,int)), this, SLOT(treeItemClicked(QTreeWidgetItem *, int)));

    this->setupPages();
}

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
    for (auto& [key, value] : this->navigation) {
        QTreeWidgetItem * topLevel = new QTreeWidgetItem();
        topLevel->setText(0, QString::fromStdString(key));
        for (auto& [itemKey, itemValue] : value) {
            QTreeWidgetItem * item = new QTreeWidgetItem();
            item->setText(0, QString::fromStdString(itemKey));
            topLevel->addChild(item);
        }

        tree->addTopLevelItem(topLevel); 
    }
}

void Splash::treeItemClicked(QTreeWidgetItem *item, int index) {
    QTreeWidgetItem *parent = item->parent();
    if(!parent){
        return;
    }

    qDebug() << "Tree item clicked: " << item->text(0) << " - " << parent->text(0);

    std::string parentName = parent->text(0).toStdString();
    std::string itemName = item->text(0).toStdString();

    int navIndex = this->findNavItem(parentName, itemName);
    ui->stackedWidget->setCurrentIndex(navIndex);
    qDebug() << navIndex;
}

Splash::~Splash()
{
    delete ui;
}

void Splash::setupPages(){
    ui->stackedWidget->setCurrentIndex(0);

    ConnectionSettings* connPage = new ConnectionSettings;
    this->addPage("Connections", "+ connection", connPage);

    CanLogger *logPage = new CanLogger;
    this->addPage("Connections", "Connection 1", logPage);

   

    this->updateNavigation();

}

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
