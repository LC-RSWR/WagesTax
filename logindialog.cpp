#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QException>
#include <stdexcept>
#include <qdatetime.h>

// 构造函数，初始化登录对话框
LoginDialog::LoginDialog(QWidget* parent) :
    QDialog(parent),  // 调用基类QDialog的构造函数
    ui(new Ui::LoginDialog)  // 创建UI对象
{
    try
    {
        ui->setupUi(this);  // 设置UI界面
        qDebug() << "UI setup completed successfully.";

        // 设置密码输入框为密码模式，输入内容将会被隐藏
        ui->passwordLineEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
        qDebug() << "Password input set to echo mode.";
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during LoginDialog constructor: " << e.what();
        QMessageBox::critical(this, "Initialization Error", "Failed to initialize the login dialog.");
        throw;
    }
}

// 析构函数，释放UI对象占用的内存
LoginDialog::~LoginDialog()
{
    try
    {
        qDebug() << "Destroying LoginDialog...";
        delete ui;  // 删除UI对象
        qDebug() << "UI object deleted successfully.";
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during LoginDialog destruction: " << e.what();
    }
}

// 取消按钮点击事件，退出程序
void LoginDialog::on_cancel_clicked()
{
    try
    {
        qDebug() << "Cancel button clicked, quitting application.";
        QApplication::quit();  // 退出应用程序
        QCoreApplication::exit(0);  // 参数为退出状态码，0 通常表示正常退出
        QApplication::closeAllWindows();  // 关闭所有窗口
        succeed = false;
        qDebug() << "Application closed successfully.";
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during cancel operation: " << e.what();
        QMessageBox::critical(this, "Cancel Operation Failed", "An error occurred while closing the application.");
    }
}

// 登录按钮点击事件，进行用户名和密码验证
void LoginDialog::on_login_clicked()
{
    try
    {
        qDebug() << "Login button clicked, starting login process.";

        // 获取用户输入的用户名和密码
        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        // 打印调试信息
        qDebug() << "Username entered: " << username;
        qDebug() << "Password entered: " << password;

        // 假设从配置文件中读取到的正确用户名和密码
        QString username_config = "admin";  // 配置文件中的用户名（示例）
        QString password_config = "admin";  // 配置文件中的密码（示例）

        qDebug() << "Configured username: " << username_config;
        qDebug() << "Configured password: " << password_config;

        // 比较用户输入的用户名和密码与配置文件中的信息
        if (username == username_config && password == password_config)
        {
            qDebug() << "Login successful!";
            hide();  // 隐藏登录窗口
            succeed = true;

            // 登录成功，关闭登录窗口并返回成功
            accept();  // 调用QDialog的accept()函数，关闭对话框并返回成功标志
        }
        else
        {
            qDebug() << "Login failed, incorrect username or password.";
            // 登录失败，弹出警告框提示用户
            QMessageBox::warning(this,
                QString::fromLocal8Bit("登录失败"),
                QString::fromLocal8Bit("用户名或密码错误，请重新输入！"));

            // 清空密码框和用户名框
            ui->passwordLineEdit->clear();
            ui->usernameLineEdit->clear();

            // 将焦点重新设置到用户名框，方便用户重新输入
            ui->usernameLineEdit->setFocus();

            // 重新执行登录对话框，直到用户输入正确的用户名和密码
            exec();
        }
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during login attempt: " << e.what();
        QMessageBox::critical(this, "Login Error", "An error occurred while trying to log in.");
    }
    catch (...)
    {
        qCritical() << "Unknown error during login process.";
        QMessageBox::critical(this, "Login Error", "An unknown error occurred while trying to log in.");
    }
}

// 模拟从文件中读取配置数据的函数
QString LoginDialog::loadConfigData(const QString& key)
{
    try
    {
        qDebug() << "Loading configuration data for key: " << key;

        QFile configFile("config.txt");  // 假设配置文件名为 config.txt
        if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            throw std::runtime_error("Failed to open config file.");
        }

        QTextStream in(&configFile);
        QString value;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (line.startsWith(key))
            {
                value = line.split("=").last().trimmed();
                break;
            }
        }

        configFile.close();
        return value;
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error loading config data: " << e.what();
        return QString();
    }
    catch (...)
    {
        qCritical() << "Unknown error occurred while loading configuration data.";
        return QString();
    }
}

// 模拟将用户登录记录写入日志文件
void LoginDialog::writeLoginLog(const QString& username, bool success)
{
    try
    {
        qDebug() << "Writing login attempt to log file.";
        QFile logFile("login_log.txt");
        if (!logFile.open(QIODevice::Append | QIODevice::Text))
        {
            throw std::runtime_error("Failed to open log file for writing.");
        }

        QTextStream out(&logFile);
        out << "Username: " << username << ", Success: " << (success ? "Yes" : "No") << ", Timestamp: " << QDateTime::currentDateTime().toString() << "\n";
        logFile.close();
        qDebug() << "Login log written successfully.";
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error writing login log: " << e.what();
    }
    catch (...)
    {
        qCritical() << "Unknown error occurred while writing login log.";
    }
}

// 验证用户名和密码的合法性
bool LoginDialog::isValidUsername(const QString& username)
{
    try
    {
        qDebug() << "Validating username: " << username;
        return !username.isEmpty() && username.length() >= 3;
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during username validation: " << e.what();
        return false;
    }
    catch (...)
    {
        qCritical() << "Unknown error occurred during username validation.";
        return false;
    }
}

// 验证密码的合法性
bool LoginDialog::isValidPassword(const QString& password)
{
    try
    {
        qDebug() << "Validating password.";
        return !password.isEmpty() && password.length() >= 6;
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during password validation: " << e.what();
        return false;
    }
    catch (...)
    {
        qCritical() << "Unknown error occurred during password validation.";
        return false;
    }
}

// 重新执行登录对话框的逻辑，模拟更多调试信息
void LoginDialog::retryLogin()
{
    try
    {
        qDebug() << "Retrying login...";
        exec();
    }
    catch (const std::exception& e)
    {
        qCritical() << "Error during login retry: " << e.what();
    }
    catch (...)
    {
        qCritical() << "Unknown error occurred during login retry.";
    }
}
