#include "securitydialog.h"
#include "ui_securitydialog.h"

SecurityDialog::SecurityDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SecurityDialog)
{
    ui->setupUi(this);
    // tab1
    connect(ui->EncBtn_1, SIGNAL(clicked()), this, SLOT(EncBtn_1_clicked()));
    connect(ui->DecBtn_1, SIGNAL(clicked()), this, SLOT(DecBtn_1_clicked()));
    connect(ui->SubBtn_1, SIGNAL(clicked()), this, SLOT(SubBtn_1_clicked()));

    // tab3
    connect(ui->EncBtn_3, SIGNAL(clicked()), this, SLOT(EncBtn_3_clicked()));
    connect(ui->DecBtn_3, SIGNAL(clicked()), this, SLOT(DecBtn_3_clicked()));
    connect(ui->SubBtn_3, SIGNAL(clicked()), this, SLOT(SubBtn_3_clicked()));

    // tab4
    connect(ui->GCDBtn_4, SIGNAL(clicked()), this, SLOT(GCDBtn_4_clicked()));

    // tab5
    connect(ui->A2BBtn_5, SIGNAL(clicked()), this, SLOT(A2BBtn_5_clicked()));
    connect(ui->B2ABtn_5, SIGNAL(clicked()), this, SLOT(B2ABtn_5_clicked()));
    connect(ui->clearBtn_5, SIGNAL(clicked()), this, SLOT(clearBtn_5_clicked()));

    // tab6
    connect(ui->A2BBtn_6, SIGNAL(clicked()), this, SLOT(A2BBtn_6_clicked()));
    connect(ui->B2ABtn_6, SIGNAL(clicked()), this, SLOT(B2ABtn_6_clicked()));
    connect(ui->clearBtn_6, SIGNAL(clicked()), this, SLOT(clearBtn_6_clicked()));

    // tab7
    // 设置tab7图片

    connect(ui->SubBtn_7, SIGNAL(clicked()), this, SLOT(SubBtn_7_clicked()));
    connect(ui->clearBtn_7, SIGNAL(clicked()), this, SLOT(clearBtn_7_clicked()));
}

SecurityDialog::~SecurityDialog()
{
    delete ui;
}

// Caesar
void SecurityDialog::Caesar(QString &input, int kspace, QString &output)
{
    // 定义密钥字典，26字母表
    QString lowDic = "abcdefghijklmnopqrstuvwxyz";
    QMap<QString, int> map;
    for (int i = 0; i < lowDic.size(); i++)
    {
        map[lowDic[i]] = i+1;
    }
    // 加密/解密
    for (int i = 0; i < input.size(); i++)
    {
        QString l = input[i];
        l = l.toLower();
//        qDebug() << input[i] << " " << l;

        if (!map.count(l))
        {
            output += l;
        }
        else
        {
            int j = map[l];
            j = (j+kspace) % 26;
            if (j == 0)
            {
                j = 26;
            }
            if (input[i].isUpper())
            {
                output += lowDic[j-1].toUpper();
            }
            else
            {
                output += lowDic[j-1];
            }
        }
    }
}
// Vigenere
void SecurityDialog::Vigenere(QString &input, QString key, QString &output)
{
    // 获取字符key对应的Caesar kspace
    QString lowDic = "abcdefghijklmnopqrstuvwxyz";
    QMap<QString, int> map;
    for (int i = 0; i < lowDic.size(); i++)
    {
        map[lowDic[i]] = i+1;
    }
    QVector<int> kspaceSeq;
    for (auto c:key)
    {
        if (map.count(c.toLower()))
        {
            // -1保证key为a时keyspace为1
            kspaceSeq.append(map[c.toLower()]-1);
        }
    }
//    qDebug() << "kspaceSeq" << kspaceSeq;

    int flag = 0;
    // 遍历每一个输入字符，循环使用得到的kspaceSeq进行Caesar运算
    for (QString c:input)
    {
//        qDebug() << "c" << c;
        if (flag == kspaceSeq.size())
        {
            flag = 0;
        }
        int kspace = kspaceSeq.at(flag);
        Caesar(c, kspace, output);
        flag++;
    }
}
// 求最大公约数
int SecurityDialog::Gcd(int a, int b)
{
    int temp;
    while (b)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


// 标签1，槽函数
void SecurityDialog::EncBtn_1_clicked()
{
    ui->CEdit_1->setReadOnly(true);
    ui->PEdit_1->setReadOnly(false);
}
void SecurityDialog::DecBtn_1_clicked()
{
    ui->PEdit_1->setReadOnly(true);
    ui->CEdit_1->setReadOnly(false);
}
void SecurityDialog::SubBtn_1_clicked()
{
    int kspace = ui->KEdit_1->text().toShort();
    QString input, output;

    if (ui->EncBtn_1->isChecked())
    {
        qDebug() << "Enc";
        if (kspace < 0)
        {
            kspace += 26;
        }
        input = ui->PEdit_1->text();
        Caesar(input, kspace, output);
        ui->CEdit_1->setText(output);
    }
    else if (ui->DecBtn_1->isChecked())
    {
        qDebug() << "Dec";
        kspace = -kspace;
        if (kspace < 0)
        {
            kspace += 26;
        }
        input = ui->CEdit_1->text();
        Caesar(input, kspace, output);
        ui->PEdit_1->setText(output);
    }
}


// 标签3槽函数
void SecurityDialog::EncBtn_3_clicked()
{
    ui->CEdit_3->setReadOnly(true);
    ui->PEdit_3->setReadOnly(false);
}
void SecurityDialog::DecBtn_3_clicked()
{
    ui->PEdit_3->setReadOnly(true);
    ui->CEdit_3->setReadOnly(false);
}
void SecurityDialog::SubBtn_3_clicked()
{
    QString key = ui->KEdit_3->text();

    QString input, output;

    if (ui->EncBtn_3->isChecked())
    {
        qDebug() << "Enc";
        input = ui->PEdit_3->text();
        Vigenere(input, key, output);
        ui->CEdit_3->setText(output);
    }
    else if (ui->DecBtn_3->isChecked())
    {
        qDebug() << "Dec";
        input = ui->CEdit_3->text();
        Vigenere(input, key, output);
        ui->PEdit_3->setText(output);
    }
}

// 标签4槽函数
void SecurityDialog::GCDBtn_4_clicked()
{
    int a = ui->AEdit_4->text().toInt();
    int b = ui->BEdit_4->text().toInt();
    int res = Gcd(a, b);
    ui->GCDEdit_4->setText(QString::number(res));
}

// 标签5槽函数
void SecurityDialog::A2BBtn_5_clicked()
{
    // 获取Bob的公钥(Bn, Be),私钥Bd
    int Bn, Bp, Bq, Be, Bd;
    if (ui->BnEdit_5->isModified())
    {
        Bn = ui->BnEdit_5->text().toShort();
        qDebug() << Bn;
    }
    else
    {
        Bp = ui->BpEdit_5->text().toShort();
        Bq = ui->BqEdit_5->text().toShort();
        ui->BnEdit_5->setReadOnly(true);
        qDebug() << Bp;
        qDebug() << Bq;
        Bn = Bp*Bq;
        ui->BnEdit_5->setText(QString::number(Bn));
    }
    qDebug() << "Bn" << Bn;

    Be = ui->BeEdit_5->text().toShort();
    qDebug() << "Be" << Be;

    Bd = ui->BdEdit_5->text().toShort();
    qDebug() << "Bd" << Bd;

    if (Bn == 0 || (ui->BeEdit_5->text().isEmpty() && ui->BdEdit_5->text().isEmpty()))
    {
        QMessageBox::critical(this, "ERROR", "Bob公钥(n,e),私钥d不能为空");
        ui->BnEdit_5->setReadOnly(false);
    }

    int Plaintext, Ciphertext;
    // 加密 and 解密
    if (ui->PlainEdit_5->text().isEmpty() && ui->CipherEdit_5->text().isEmpty())
    {
        QMessageBox::critical(this, "ERROR", "请输入Plaintext或者Ciphertext");
    }
    else if (!ui->PlainEdit_5->text().isEmpty()) // Encryption：P^e (mod n)
    {
        Plaintext = ui->PlainEdit_5->text().toShort();
        // 大数的pow运算会损失精度，问题还未解决，尝试输出字符串，使用win计算器计算
        QString str = QString("(%1 ^ %2) mod %3").arg(Plaintext).arg(Be).arg(Bn);
        ui->PlainEdit_5->setText(str);
    }
    else if (!ui->CipherEdit_5->text().isEmpty()) // Decryption：C^d (mod n)
    {
        Ciphertext = ui->CipherEdit_5->text().toShort();
        // 大数的pow运算会损失精度，问题还未解决，尝试输出字符串，使用win计算器计算
        QString str = QString("(%1 ^ %2) mod %3").arg(Ciphertext).arg(Bd).arg(Bn);
        ui->PlainEdit_5->setText(str);
    }
}
void SecurityDialog::B2ABtn_5_clicked()
{
    // 获取Alice的公钥(An, Ae),私钥Ad
    int An, Ap, Aq, Ae, Ad;
    if (ui->AnEdit_5->isModified())
    {
        An = ui->AnEdit_5->text().toShort();
        qDebug() << An;
    }
    else
    {
        Ap = ui->ApEdit_5->text().toShort();
        Aq = ui->AqEdit_5->text().toShort();
        ui->AnEdit_5->setReadOnly(true);
        qDebug() << Ap;
        qDebug() << Aq;
        An = Ap*Aq;
        ui->AnEdit_5->setText(QString::number(An));
    }
    qDebug() << "An" << An;

    Ae = ui->AeEdit_5->text().toShort();
    qDebug() << "Ae" << Ae;

    Ad = ui->AdEdit_5->text().toShort();
    qDebug() << "Ad" << Ad;

    if (An == 0 || (ui->AeEdit_5->text().isEmpty() && ui->AdEdit_5->text().isEmpty()))
    {
        QMessageBox::critical(this, "ERROR", "Alice公钥(n,e),私钥d不能为空");
        ui->AnEdit_5->setReadOnly(false);
    }

    int Plaintext, Ciphertext;
    // 加密 and 解密
    if (ui->PlainEdit_5->text().isEmpty() && ui->CipherEdit_5->text().isEmpty())
    {
        QMessageBox::critical(this, "ERROR", "请输入Plaintext或者Ciphertext");
    }
    else if (!ui->PlainEdit_5->text().isEmpty()) // Encryption：P^e (mod n)
    {
        Plaintext = ui->PlainEdit_5->text().toShort();
        // 大数的pow运算会损失精度，问题还未解决，尝试输出字符串，使用win计算器计算
        QString str = QString("(%1 ^ %2) mod %3").arg(Plaintext).arg(Ae).arg(An);
        ui->PlainEdit_5->setText(str);
    }
    else if (!ui->CipherEdit_5->text().isEmpty()) // Decryption：C^d (mod n)
    {
        Ciphertext = ui->CipherEdit_5->text().toShort();
        // 大数的pow运算会损失精度，问题还未解决，尝试输出字符串，使用win计算器计算
        QString str = QString("(%1 ^ %2) mod %3").arg(Ciphertext).arg(Ad).arg(An);
        ui->PlainEdit_5->setText(str);

    }
}
void SecurityDialog::clearBtn_5_clicked()
{
    ui->ApEdit_5->clear();
    ui->AqEdit_5->clear();
    ui->AnEdit_5->clear();
    ui->AeEdit_5->clear();
    ui->AdEdit_5->clear();
    ui->BpEdit_5->clear();
    ui->BqEdit_5->clear();
    ui->BnEdit_5->clear();
    ui->BeEdit_5->clear();
    ui->BdEdit_5->clear();
    ui->PlainEdit_5->clear();
    ui->CipherEdit_5->clear();
}

// 标签6槽函数
void SecurityDialog::A2BBtn_6_clicked()
{
    // 获取Alice的公钥(An, Ae),私钥Ad,用于签名
    int An, Ap, Aq, Ae, Ad;
    if (ui->AnEdit_6->isModified())
    {
        An = ui->AnEdit_6->text().toShort();
        qDebug() << An;
    }
    else
    {
        Ap = ui->ApEdit_6->text().toShort();
        Aq = ui->AqEdit_6->text().toShort();
        ui->AnEdit_6->setReadOnly(true);
        qDebug() << Ap;
        qDebug() << Aq;
        An = Ap*Aq;
        ui->AnEdit_6->setText(QString::number(An));
    }
    qDebug() << "An" << An;

    Ae = ui->AeEdit_6->text().toShort();
    qDebug() << "Ae" << Ae;

    Ad = ui->AdEdit_6->text().toShort();
    qDebug() << "Ad" << Ad;

    if (An == 0 || ui->AeEdit_6->text().isEmpty() || ui->AdEdit_6->text().isEmpty())
    {
        QMessageBox::critical(this, "ERROR", "Alice公钥(n,e),私钥d不能为空");
        ui->AnEdit_6->setReadOnly(false);
    }

    // 获取Bob的公钥(Bn, Be),私钥Bd,用于加密
    int Bn, Bp, Bq, Be, Bd;
    if (ui->BnEdit_6->isModified())
    {
        Bn = ui->BnEdit_6->text().toShort();
        qDebug() << Bn;
    }
    else
    {
        Bp = ui->BpEdit_6->text().toShort();
        Bq = ui->BqEdit_6->text().toShort();
        ui->BnEdit_6->setReadOnly(true);
        qDebug() << Bp;
        qDebug() << Bq;
        Bn = Bp*Bq;
        ui->BnEdit_6->setText(QString::number(Bn));
    }
    qDebug() << "Bn" << Bn;

    Be = ui->BeEdit_6->text().toShort();
    qDebug() << "Be" << Be;

    Bd = ui->BdEdit_6->text().toShort();
    qDebug() << "Bd" << Bd;

    if (Bn == 0 || (ui->BeEdit_6->text().isEmpty() && ui->BdEdit_6->text().isEmpty()))
    {
        QMessageBox::critical(this, "ERROR", "Bob公钥(n,e),私钥d不能为空");
        ui->BnEdit_6->setReadOnly(false);
    }
    QString Plaintext = ui->PlainEdit_6->text();

    // 使用Alice的私钥对明文进行签名
    QString Signature = QString("(%1 ^ %2) mod %3").arg(Plaintext).arg(Ad).arg(An);
    ui->SigEdit_6->setText(Signature);

    // 加密，使用Bob的公钥，对签名后的数据进行加密
    QString Ciphertext = QString("((%1) ^ %2) mod %3").arg(Signature).arg(Be).arg(Bn);
    ui->CipherEdit_6->setText(Ciphertext);
}
void SecurityDialog::B2ABtn_6_clicked()
{
    // 获取Alice的公钥(An, Ae),私钥Ad,用于加密
    int An, Ap, Aq, Ae, Ad;
    if (ui->AnEdit_6->isModified())
    {
        An = ui->AnEdit_6->text().toShort();
        qDebug() << An;
    }
    else
    {
        Ap = ui->ApEdit_6->text().toShort();
        Aq = ui->AqEdit_6->text().toShort();
        ui->AnEdit_6->setReadOnly(true);
        qDebug() << Ap;
        qDebug() << Aq;
        An = Ap*Aq;
        ui->AnEdit_6->setText(QString::number(An));
    }
    qDebug() << "An" << An;

    Ae = ui->AeEdit_6->text().toShort();
    qDebug() << "Ae" << Ae;

    Ad = ui->AdEdit_6->text().toShort();
    qDebug() << "Ad" << Ad;

    if (An == 0 || ui->AeEdit_6->text().isEmpty() || ui->AdEdit_6->text().isEmpty())
    {
        QMessageBox::critical(this, "ERROR", "Alice公钥(n,e),私钥d不能为空");
        ui->AnEdit_6->setReadOnly(false);
    }

    // 获取Bob的公钥(Bn, Be),私钥Bd,用于签名
    int Bn, Bp, Bq, Be, Bd;
    if (ui->BnEdit_6->isModified())
    {
        Bn = ui->BnEdit_6->text().toShort();
        qDebug() << Bn;
    }
    else
    {
        Bp = ui->BpEdit_6->text().toShort();
        Bq = ui->BqEdit_6->text().toShort();
        ui->BnEdit_6->setReadOnly(true);
        qDebug() << Bp;
        qDebug() << Bq;
        Bn = Bp*Bq;
        ui->BnEdit_6->setText(QString::number(Bn));
    }
    qDebug() << "Bn" << Bn;

    Be = ui->BeEdit_6->text().toShort();
    qDebug() << "Be" << Be;

    Bd = ui->BdEdit_6->text().toShort();
    qDebug() << "Bd" << Bd;

    if (Bn == 0 || (ui->BeEdit_6->text().isEmpty() && ui->BdEdit_6->text().isEmpty()))
    {
        QMessageBox::critical(this, "ERROR", "Bob公钥(n,e),私钥d不能为空");
        ui->BnEdit_6->setReadOnly(false);
    }
    QString Plaintext = ui->PlainEdit_6->text();

    // 使用Bob的私钥对明文进行签名
    QString Signature = QString("(%1 ^ %2) mod %3").arg(Plaintext).arg(Bd).arg(Bn);
    ui->SigEdit_6->setText(Signature);

    // 加密，使用Bob的公钥，对签名后的数据进行加密
    QString Ciphertext = QString("((%1) ^ %2) mod %3").arg(Signature).arg(Ae).arg(An);
    ui->CipherEdit_6->setText(Ciphertext);
}
void SecurityDialog::clearBtn_6_clicked()
{
    ui->ApEdit_6->clear();
    ui->AqEdit_6->clear();
    ui->AnEdit_6->clear();
    ui->AeEdit_6->clear();
    ui->AdEdit_6->clear();
    ui->BpEdit_6->clear();
    ui->BqEdit_6->clear();
    ui->BnEdit_6->clear();
    ui->BeEdit_6->clear();
    ui->BdEdit_6->clear();
    ui->PlainEdit_6->clear();
    ui->CipherEdit_6->clear();
}

// 标签7，槽函数
void SecurityDialog::SubBtn_7_clicked()
{
    int p, q, n, m;
    p = ui->pEdit_7->text().toInt();
    q = ui->qEdit_7->text().toInt();
    n = ui->nEdit_7->text().toInt();
    m = ui->mEdit_7->text().toInt();
    // Alice发送给Bob
    QString N = QString("(%1 ^ %2) mod %3").arg(q).arg(n).arg(p);
    ui->NEdit_7->setText(N);
    // Bob发送给Alice
    QString M = QString("(%1 ^ %2) mod %3").arg(q).arg(m).arg(p);
    ui->MEdit_7->setText(M);
    // 计算共享密钥
    QString A = QString("((%1) ^ %2) mod %3").arg(M).arg(n).arg(p);
    QString B = QString("((%1) ^ %2) mod %3").arg(N).arg(m).arg(p);
    ui->Akeylabel_7->setText(A);
    ui->Bkeylabel_7->setText(B);
}
void SecurityDialog::clearBtn_7_clicked()
{
    ui->pEdit_7->clear();
    ui->qEdit_7->clear();
    ui->nEdit_7->clear();
    ui->mEdit_7->clear();
    ui->NEdit_7->clear();
    ui->MEdit_7->clear();
    ui->Akeylabel_7->clear();
    ui->Bkeylabel_7->clear();
}

void SecurityDialog::paintEvent(QPaintEvent *)
{
    // 设置标签显示图片
    QImage image(":/res/DH.png");
    ui->Arrowlabel_7->setPixmap(QPixmap::fromImage(image));
}
