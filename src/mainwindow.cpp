#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUuid>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_Player = new AudioPlayer(initDeviceID(), this);

    connect(&m_Player->getMediaPlayer(), SIGNAL(positionChanged(qint64)), SLOT(on_positionChanged(qint64)));
    connect(&m_Player->getMediaPlayer(), SIGNAL(durationChanged(qint64)), SLOT(on_durationChanged(qint64)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_Player->playNext();
}

void MainWindow::on_sliderProgress_sliderMoved(int position)
{
    m_Player->getMediaPlayer().setPosition(position);
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void MainWindow::on_durationChanged(qint64 duration)
{
    ui->sliderProgress->setMaximum(duration);
}

QString MainWindow::initDeviceID()
{
    QString uid = QUuid::createUuid().toString();
    uid.replace(QRegExp("(\\{|\\})"),"");
    ui->editDevID->setText(uid);

    uid = "12345678-1234-1234-1234-123456789012";

    return uid;
}
