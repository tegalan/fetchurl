#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// Inspirasi Project
// http://stackoverflow.com/a/1053134/3086112

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fetch facebook URL");

    networkAccess = new QNetworkAccessManager(this);

    connect(networkAccess,SIGNAL(finished(QNetworkReply*)),this,SLOT(terimaBalasan(QNetworkReply*)));

    //  Set default URL line edit
    ui->lineURL->setText("showcheap");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnFetch_clicked()
{
    //  Mengambil url dari LineEdit
    QString userid = ui->lineURL->text();

    //  Setting api url
    QString apiUrl = "http://graph.facebook.com/";
    //  Menggabungkan api url dengan query / path, dalam hal ini adalah user name
    QString url = apiUrl+userid;

    //  Membuat GET request pada url di Line Edit
    networkAccess->get(QNetworkRequest(QUrl(url)));
    //  Fungsi ini akan melempar result QNetworkReply jika request sudah selesai
    //  sehingga signal finished(QnetworkReply*) sudah di emit (dipancarkan) dengan
    //  Mengirim data hasil request dari GET tadi.
}

void MainWindow::terimaBalasan(QNetworkReply* balasan){
    //  Karena signal finished() sudah di konekkan dengan slot terimaBalasan()
    //  Maka data yang dikirim pada fungsi sebelumnya akan diterima SLOT terimabalasan
    //  Dan datanya diproses pada fungsi ini

    // Ambil data reply dan simpan sebagai QString
    QString data = (QString)balasan->readAll();

    // Parse json format dari qstring ke objek jsondocument
    QJsonDocument replyJSON = QJsonDocument::fromJson(data.toUtf8());

    // parsing json document menjadi jsonobject (sesuai format json yang diterima)
    QJsonObject objectJSON = replyJSON.object();

    //  Membuat string untuk wadah parser JSON
    QString textResult;
    textResult.append("Nama Profile : "+objectJSON.value("first_name").toString()+" "+objectJSON.value("last_name").toString()+"<br/>");
    textResult.append("Gender : "+objectJSON.value("gender").toString()+"<br/>");
    textResult.append("User ID : "+objectJSON.value("id").toString()+"<br/>");
    //  Masukkan hasil parsing ke textedit (output), data ditampilkan di aplikasi, Selesai :p
    ui->textResult->setText(textResult);
}
