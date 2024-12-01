#ifndef WAGESTAX_H
#define WAGESTAX_H

// 包含 Qt 框架的头文件
#include <QMainWindow>
// 引入登录对话框和数据库管理类
#include "logindialog.h"
#include "sqlmanager.h"

// Qt 命名空间的开头部分
QT_BEGIN_NAMESPACE
namespace Ui { class WagesTax; }  // 声明 UI 类，WagesTax 用于存放界面元素
QT_END_NAMESPACE

// WagesTax 类继承自 QMainWindow，表示主窗口
// 税务计算主窗口
class WagesTax : public QMainWindow
{
    Q_OBJECT  // Qt 特性，用于提供信号和槽功能

public:
    // 构造函数：初始化 WagesTax 窗口，接受父级窗口指针（默认为 nullptr）
    WagesTax(QWidget* parent = nullptr);

    // 析构函数：清理和销毁 WagesTax 对象
    ~WagesTax();

    // 初始化数据库（创建 SQL 连接或相关设置）
    void createSql();

private slots:
    // 槽函数：当用户选择列表中的某一项时调用，处理选中项的操作
    void onItemSelected();

    // 槽函数：点击“添加”按钮时调用，处理添加员工操作
    void on_add_clicked();

    // 槽函数：点击“删除”按钮时调用，处理删除选中员工操作
    void on_delete_2_clicked();

    // 槽函数：点击“修改”按钮时调用，处理修改选中员工信息操作
    void on_modify_clicked();

    // 槽函数：点击“查询”按钮时调用，处理查询员工操作
    void on_query_clicked();

    // 槽函数：处理查询结果的显示，展示员工列表
    void showResult(std::vector<std::pair<int, QString>>& result);

    // 槽函数：清除输入框的内容和选择的列表项
    void clearInput();

private:
    

    // 数据库管理对象，用于执行与数据库的交互操作（如查询、插入、更新等）
    SqlManager sql;

    // Ui::WagesTax 指针，指向自动生成的 UI 类，用于管理 UI 元素
    Ui::WagesTax* ui;
};

#endif // WAGESTAX_H
