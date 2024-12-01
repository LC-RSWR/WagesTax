#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

// 引入 Qt 的 QDialog 类, 用于构建登录对话框
#include <QDialog>

// 预声明 Ui 命名空间下的 LoginDialog 类
namespace Ui {
    class LoginDialog;
}

// LoginDialog 类定义，继承自 QDialog
// 该类用于实现登录对话框功能
class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    // 构造函数，初始化 LoginDialog 对话框，parent 是父组件，默认为 nullptr
    explicit LoginDialog(QWidget* parent = nullptr);

    // 析构函数，清理资源
    ~LoginDialog();

    // 成功登录
    bool succeed = false;

   
    // 读取配置文件中的数据，返回指定键对应的值
   // 参数: key - 配置项的键
   // 返回值: 配置项对应的值（QString类型）
    QString loadConfigData(const QString& key);

    // 将登录日志写入日志文件
    // 参数: username - 登录的用户名
    //        success - 登录是否成功（true 表示成功，false 表示失败）
    void writeLoginLog(const QString& username, bool success);

    // 验证用户名的合法性
    // 参数: username - 需要验证的用户名
    // 返回值: 如果用户名合法则返回 true，否则返回 false
    bool isValidUsername(const QString& username);

    // 验证密码的合法性
    // 参数: password - 需要验证的密码
    // 返回值: 如果密码合法则返回 true，否则返回 false
    bool isValidPassword(const QString& password);

    // 重新执行登录逻辑（例如，清除错误提示信息，重置输入框等）
    void retryLogin();


private slots:
    // 点击取消按钮时的槽函数
    void on_cancel_clicked();

    // 点击登录按钮时的槽函数
    void on_login_clicked();

private:
    // Ui 指针，用于管理和操作界面控件
    Ui::LoginDialog* ui;
};

#endif // LOGINDIALOG_H
