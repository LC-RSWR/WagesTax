#include "wagestax.h"
// 引入登录对话框和数据库管理类
#include "logindialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <exception>
#include <stdexcept>
#include <QDateTime>
#include <QTimer>
#include <QThread>

// 日志记录函数
void logError(const QString& errorMessage)
{
    QFile logFile("application_log.txt");  // 日志文件
    if (logFile.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
            << " - ERROR: " << errorMessage << "\n";
    }
    else
    {
        qDebug() << "无法打开日志文件！";
    }
}

// 捕获并显示异常的函数
void handleException(const std::exception& e)
{
    QString errorMsg = "An exception occurred: ";
    errorMsg += e.what();
    logError(errorMsg);

    QMessageBox::critical(nullptr, "Critical Error", errorMsg, QMessageBox::Ok);
}

// 捕获并显示异常的函数 (Qt 异常类型)
void handleQtException(const QString& errorMsg)
{
    logError(errorMsg);
    QMessageBox::critical(nullptr, "Critical Error", errorMsg, QMessageBox::Ok);
}

// 模拟一些数据库操作
bool simulateDatabaseOperation()
{
    // 模拟可能的数据库错误
    int randomError = qrand() % 10;
    if (randomError < 3)
    {
        throw std::runtime_error("数据库连接失败");
    }
    return true;
}

// 模拟一些业务逻辑
bool performBusinessLogic()
{
    try
    {
        // 模拟读取数据库操作
        if (!simulateDatabaseOperation())
        {
            throw std::runtime_error("业务逻辑处理失败");
        }

        // 假设业务逻辑在此处执行成功
        qDebug() << "业务逻辑成功执行";
        return true;
    }
    catch (const std::exception& e)
    {
        handleException(e);
        return false;
    }
}

// 模拟网络请求
bool simulateNetworkRequest()
{
    int randomError = qrand() % 10;
    if (randomError < 5)
    {
        throw std::runtime_error("网络请求失败");
    }
    return true;
}

// 业务逻辑模拟函数，模拟更多不同情况
void simulateExtendedLogic()
{
    return;
    if (!performBusinessLogic())
    {
        logError("业务逻辑执行失败，正在尝试重新启动操作...");
        // 重试机制
        for (int i = 0; i < 3; ++i)
        {
            if (performBusinessLogic())
            {
                qDebug() << "重试成功";
                break;
            }
            else
            {
                qDebug() << "重试失败，第" << i + 1 << "次尝试";
            }
        }
    }

    // 模拟网络请求操作
    try
    {
        if (!simulateNetworkRequest())
        {
            throw std::runtime_error("网络请求失败");
        }
        qDebug() << "网络请求成功";
    }
    catch (const std::exception& e)
    {
        handleException(e);
    }
}

// 打印系统信息
void printSystemInfo()
{
    qDebug() << "当前操作系统：" << QSysInfo::prettyProductName();
    qDebug() << "当前时间：" << QDateTime::currentDateTime().toString();
    qDebug() << "当前Qt版本：" << QT_VERSION_STR;
}

// 延时任务模拟函数
void simulateDelayedTask()
{
    qDebug() << "任务开始";
    QThread::sleep(2);  // 模拟延时
    qDebug() << "任务完成";
}

// 捕获并处理系统级异常
void handleSystemException()
{
    QString sysError = "系统级异常发生！";
    logError(sysError);
    QMessageBox::critical(nullptr, "System Error", sysError, QMessageBox::Ok);
}

// 程序初始化函数
bool initializeApp()
{
    try
    {
        printSystemInfo();
        return true;
    }
    catch (const std::exception& e)
    {
        handleException(e);
        return false;
    }
}

// 设置定时器任务模拟
void setupTimers()
{
    QTimer* timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, []() {
        qDebug() << "定时任务已触发";
        });
    timer->start(5000);  // 每5秒触发一次
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    try
    {
        // 模拟应用程序初始化
        if (!initializeApp())
        {
            return -1;  // 如果初始化失败，退出程序
        }

        // 设置定时器
        setupTimers();

        // 登录对话框对象，用于管理登录界面的显示和交互
        LoginDialog login_dlg;

        // 弹出登录对话框，执行登录逻辑
        login_dlg.exec();

        if (login_dlg.succeed)
        {
            try
            {
                WagesTax w;
                w.show();

                // 模拟更多业务逻辑
                simulateExtendedLogic();

                return a.exec();
            }
            catch (const std::exception& e)
            {
                handleException(e);  // 捕获WagesTax相关的异常
                return -1;  // 程序出现异常，返回非0退出状态
            }
            catch (const std::exception* ex)
            {
                handleException(*ex);  // 捕获WagesTax相关的异常
                return -1;
            }
            catch (...)
            {
                QString unknownError = "未知错误发生在WagesTax界面加载时";
                handleQtException(unknownError);
                return -1;
            }
        }
        else
        {
            // 如果登录失败，输出失败信息并记录日志
            QString loginFailMsg = "用户登录失败：用户名或密码错误";
            logError(loginFailMsg);

            // 弹出消息框提示登录失败
            QMessageBox::warning(nullptr, "Login Failed", loginFailMsg, QMessageBox::Ok);
            QApplication::quit();  // 退出应用程序
            QCoreApplication::exit(0);  // 参数为退出状态码，0 通常表示正常退出
            QApplication::closeAllWindows();  // 关闭所有窗口
        }
    }
    catch (const std::exception& e)
    {
        // 捕获整个程序的异常并记录日志
        handleException(e);
        QApplication::quit();  // 如果捕获到异常，退出程序
    }
    catch (...)
    {
        // 捕获任何未知类型的异常
        QString unknownError = "程序发生未知错误";
        handleQtException(unknownError);
        QApplication::quit();  // 如果捕获到未知异常，退出程序
    }

    return 0;
}
