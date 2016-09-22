#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audioplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sliderProgress_sliderMoved(int position);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 duration);

private:
    QString initDeviceID();

    Ui::MainWindow *ui;
    AudioPlayer *m_Player;
};

#endif // MAINWINDOW_H
