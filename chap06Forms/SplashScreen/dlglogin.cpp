#include "dlglogin.h"
#include "ui_dlglogin.h"

DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    ui->setupUi(this);
    setFixedSize(510,373);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlag(Qt::SplashScreen);
    ReadSettings();
}

DlgLogin::~DlgLogin()
{
    delete ui;
}
#include <QMessageBox>
void DlgLogin::on_btnOK_clicked()
{
    QString user = ui->editUser->text().trimmed();
    QString Password = ui->editPSWD->text().trimmed();
    if((user == m_User)&&(Encrypt(Password) == m_Password)){
        WriteSetting();
        accept();
    }else{
        m_TryCount++;
        if(m_TryCount>3){
            QMessageBox::warning(this,"error","密码错误太多次退出");
            reject();
        }else{
            QMessageBox::critical(this,"error","账号或密码错误");
        }
    }
//    QString user=ui->editUser->text().trimmed();//输入用户名
//    QString pswd=ui->editPSWD->text().trimmed(); //输入密码

//    QString encrptPSWD=Encrypt(pswd); //对输入密码进行加密

//    if ((user==m_User)&&(encrptPSWD==m_Password)) //如果用户名和密码正确
//    {
//        WriteSetting();//保存设置
//        this->accept(); //对话框 accept()，关闭对话框
//    }
//    else
//    {
//        m_TryCount++; //错误次数
//        if (m_TryCount>3)
//        {
//            QMessageBox::critical(this, "错误", "输入错误次数太多，强行退出");
//            this->reject(); //退出
//        }
//        else
//            QMessageBox::warning(this, "错误提示", "用户名或密码错误");
//    }
}
#include <QSettings>
void DlgLogin::ReadSettings()
{//读取存储的用户名和密码, 密码是经过加密的
    QString organization="WWB-Qt";//用于注册表，
    QString appName="samp6_5"; //HKEY_CURRENT_USER/Software/WWB-Qt/amp6_5

    QSettings   settings(organization,appName);//创建

    bool saved=settings.value("saved",false).toBool();//读取 saved键的值
    m_User=settings.value("Username", "user").toString();//读取 Username 键的值，缺省为“user”

    QString defaultPSWD=Encrypt("12345"); //缺省密码"12345"加密后的数据

    m_Password=settings.value("PSWD",defaultPSWD).toString();//读取PSWD 键的值，

    if (saved)
        ui->editUser->setText(m_User);

    ui->chkBoxSave->setChecked(saved);
}

void DlgLogin::WriteSetting()
{ //保存用户名，密码等设置
    QSettings   settings("WWB-Qt","samp6_5"); //注册表键组
    settings.setValue("Username",m_User); //用户名
    settings.setValue("PSWD",m_Password);   //密码，经过加密的
    settings.setValue("saved",ui->chkBoxSave->isChecked());
}
#include <QCryptographicHash>
QString DlgLogin::Encrypt(const QString &str)
{
    QByteArray btArray;

    btArray.append(str);//加入原始字符串

    QCryptographicHash hash(QCryptographicHash::Md5);  //Md5加密算法

    hash.addData(btArray);  //添加数据到加密哈希值

    QByteArray resultArray =hash.result();  //返回最终的哈希值

    QString md5 =resultArray.toHex();//转换为16进制字符串

    return  md5;
}

void DlgLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(m_MouseMoving&&(event->buttons()&&Qt::LeftButton)){
        move(event->globalPos()-m_LastPos);

        m_LastPos = event->globalPos()-pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void DlgLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_MouseMoving = true;
        m_LastPos = event->globalPos()-pos();
    }
    return QDialog::mousePressEvent(event);
}

void DlgLogin::mouseReleaseEvent(QMouseEvent *event)
{
    m_MouseMoving = false;
}

