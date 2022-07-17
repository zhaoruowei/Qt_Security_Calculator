#ifndef SECURITYDIALOG_H
#define SECURITYDIALOG_H

#include <QDialog>
#include <QMap>
#include <QVector>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class SecurityDialog; }
QT_END_NAMESPACE

class SecurityDialog : public QDialog
{
    Q_OBJECT

public:
    SecurityDialog(QWidget *parent = nullptr);
    ~SecurityDialog();
    // Caesar
    void Caesar(QString &input, int kspace, QString &output);
    // Vigenere
    void Vigenere(QString &input, QString key, QString &output);
    // 求最大公约数
    int Gcd(int a, int b);

private:
    void paintEvent(QPaintEvent *);

private slots:
    // 标签1槽函数
    void EncBtn_1_clicked();
    void DecBtn_1_clicked();
    void SubBtn_1_clicked();

    // 标签3槽函数
    void EncBtn_3_clicked();
    void DecBtn_3_clicked();
    void SubBtn_3_clicked();

    // 标签4槽函数
    void GCDBtn_4_clicked();

    // 标签5槽函数,RSA
    // Alice to Bob
    void A2BBtn_5_clicked();
    // Bob to Alice
    void B2ABtn_5_clicked();
    // 清空所有输入
    void clearBtn_5_clicked();

    //标签6槽函数, 基于RSA的数字签名, 使用发送者的私钥进行RSA加密, 达到签名作用. 再使用接收者的公钥进行RSA加密, 达到加密作用。
    // Alice to Bob, Alice private used signature, Bob public used enc.
    void A2BBtn_6_clicked();
    // Bob to Alice, Bob private used signature, Alice public used enc.
    void B2ABtn_6_clicked();
    void clearBtn_6_clicked();

    //标签7槽函数,Difﬁe-Hellman密钥交换协议
    void SubBtn_7_clicked();
    void clearBtn_7_clicked();

private:
    Ui::SecurityDialog *ui;
};
#endif // SECURITYDIALOG_H
