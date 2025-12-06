#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tformdoc.h"
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->setVisible(false);   // 不可显示
    ui->tabWidget->clear();  // 将原有的tab清掉
    ui->tabWidget->setTabsClosable(true);  // 关闭右上角的 X 号
    //setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actWidgetInsite_triggered()
{
    TFormDoc *formDoc=new TFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur=ui->tabWidget->addTab(formDoc,QString::asprintf("Doc %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);  //tab写成act
    connect(formDoc,&TFormDoc::titleChanged,this,&MainWindow::do_changeTabTitle);
}

void MainWindow::do_changeTabTitle(QString str)
{
    int index=ui->tabWidget->currentIndex();
    ui->tabWidget->setTabText(index,str);
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget(index)->close();
}

// 添加背景图片
// void MainWindow::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);
//     QPainter painter(this);
//     painter.drawPixmap(0,ui->mainToolBar->height(),
//                        width(),height()-ui->mainToolBar->height()-ui->statusbar->height(),
//                        QPixmap(":/icons/images/back2.jpg"));
// }

void MainWindow::on_actWidget_triggered()
{
    TFormDoc *formDoc=new TFormDoc();   //多加了this，导致独立的Widget窗口出现在主窗口的左上角且程序崩溃
                                        //但是主窗口删除后，父窗口必须得单独删除
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowTitle("基于QWidget的窗口，无parent");
    //formDoc->setWindowOpacity(0.8);
    formDoc->show();
}

#include "tformtable.h"
void MainWindow::on_actWindowInsite_triggered()
{
    TFormTable *formTable=new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int cur=ui->tabWidget->addTab(formTable,
                                    QString::asprintf("Table %d",ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void MainWindow::on_actWindow_triggered()
{
    TFormTable *formTable=new TFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("独立的MainWindow");
    formTable->show();
}

