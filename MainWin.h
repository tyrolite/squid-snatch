#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTableView>
#include <QCheckBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QLabel>

namespace Ui {
    class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

    QString getInterface();

    QString getFilter();

    bool getPromisc();

    QPushButton* getStartBtn();

    QPushButton* getStopBtn();

    QPlainTextEdit* getTextTe();

    QPlainTextEdit* getLogTe();

    QTableView* getCapturedTv();

    QCheckBox* getPromCbx();

    QListWidget* getToolsLw();

    QTreeWidget* getFieldsTw();

    QLabel* getImgLabel();
private:
    Ui::MainWin *ui;

public slots:
    void log(const QString& msg);
};

#endif // MAINWIN_H
