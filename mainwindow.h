#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    //  Membuat SLOT
    void terimaBalasan(QNetworkReply* balasan);

private slots:
    void on_btnFetch_clicked();


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkAccess;
};

#endif // MAINWINDOW_H
