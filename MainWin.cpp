#include "MainWin.h"
#include "ui_MainWin.h"
#include <pcap.h>
#include <stdio.h>

MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    ui->capturedTv->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->capturedTv->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->capturedTv->setSelectionMode(QAbstractItemView::SingleSelection);

    log("Welcome to SquidSnatch 0.1 Beta");

    pcap_if_t *allDevsP = NULL, *it = NULL;
    char errBuff[1024];
    int rc;

    rc = pcap_findalldevs(&allDevsP, errBuff);
    if((rc < 0) || (NULL == allDevsP))
    {
        log("failed to find all devices !");
    }

    it = allDevsP;
    while(it)
    {
        ui->interfaceCb->addItem(it->name);
        it = it->next;
    }

    pcap_freealldevs(allDevsP);

    ui->toolLw->addItem(new QListWidgetItem(QIcon("resource/sniff.png"),"Sniffer"));
    ui->toolLw->addItem(new QListWidgetItem(QIcon("resource/net_mon.png"),"Network Monitor"));
    ui->toolLw->addItem(new QListWidgetItem(QIcon("resource/pack_gen.png"),"Packet Generator"));

    ui->startBtn->setIcon(QIcon("resource/start.png"));
    ui->stopBtn->setIcon(QIcon("resource/stop.png"));
}

MainWin::~MainWin()
{
    delete ui;
}

QString MainWin::getInterface()
{
    return ui->interfaceCb->currentText();
}

QString MainWin::getFilter()
{
    return ui->filterLe->text();
}

bool MainWin::getPromisc()
{
    return ui->promCbx->isChecked();
}

QPushButton* MainWin::getStartBtn()
{
    return ui->startBtn;
}

QPushButton* MainWin::getStopBtn()
{
    return ui->stopBtn;
}

QPlainTextEdit* MainWin::getTextTe()
{
    return ui->textTe;
}

QPlainTextEdit* MainWin::getLogTe()
{
    return ui->logTe;
}

QTableView* MainWin::getCapturedTv()
{
    return ui->capturedTv;
}

QCheckBox* MainWin::getPromCbx()
{
    return ui->promCbx;
}

QListWidget* MainWin::getToolsLw()
{
    return ui->toolLw;
}

QTreeWidget* MainWin::getFieldsTw()
{
    return ui->treeWidget;
}

QLabel* MainWin::getImgLabel()
{
    return ui->imgLabel;
}

void MainWin::log(const QString& msg)
{
    printf("%s\n", msg.toAscii().constData());
    fflush(stdout);
    ui->logTe->appendPlainText(msg);
}
