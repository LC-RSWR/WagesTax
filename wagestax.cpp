#include "wagestax.h"
#include "ui_wagestax.h"
#include <QMessageBox>
#include <qdebug.h>
#include <stdexcept>

// WagesTax 构造函数
WagesTax::WagesTax(QWidget* parent)
    : QMainWindow(parent)    // 调用 QMainWindow 构造函数
    , ui(new Ui::WagesTax)   // 初始化 UI
{
    ui->setupUi(this);      // 设置 UI 界面
    

    sql.createSql();        // 初始化数据库连接或创建数据库
    on_query_clicked();     // 执行查询操作，展示员工信息

    // 连接信号和槽函数，当用户选择列表项时触发 onItemSelected() 槽函数
    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &WagesTax::onItemSelected);
}

// WagesTax 析构函数
WagesTax::~WagesTax()
{
    delete ui;  // 清理 UI 对象，释放资源
}

// 创建 SQL 连接或初始化 SQL 操作
void WagesTax::createSql()
{
    sql.createSql();  // 初始化数据库或其他 SQL 相关操作
}

// 槽函数：处理当列表项被选中时的操作
void WagesTax::onItemSelected() 
{
    // 获取当前选中的列表项
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();

    if (selectedItem)
    {
        // 获取该项关联的 QWidget（包含员工信息）
        QWidget* widget = ui->listWidget->itemWidget(selectedItem);

        if (widget)
        {
            // 获取自定义属性 "itemId"，表示员工的 ID
            QVariant idVariant = widget->property("itemId");

            // 将 QVariant 转换为整数类型的 ID
            int itemId = idVariant.toInt();

            // 根据 ID 查询员工信息
            auto result = sql.queryEmployeeByIdOrName(itemId);
            if (result.empty())
            {
                return;  // 如果没有找到对应的员工，返回
            }

            // 设置 UI 中的文本框为查询到的员工信息
            ui->name_edit->setText(std::get<1>(result.front()));  // 设置员工姓名
            ui->salary_edit_2->setText(QString::number(std::get<2>(result.front())));  // 设置员工薪资
        }
    }
}

// 槽函数：处理添加员工操作
void WagesTax::on_add_clicked()
{
    // 如果员工姓名或薪资为空，弹出警告框
    if (ui->name_edit->text().isEmpty() 
        ||
        ui->salary_edit_2->text().isEmpty())
    {
        QMessageBox::warning(this, QString::fromLocal8Bit("添加失败"), QString::fromLocal8Bit("员工姓名或薪资输入为空！"));
        return;
    }

    // 调用 SQL 添加员工信息
    sql.addEmployee(ui->name_edit->text(),
        ui->salary_edit_2->text().toDouble());

    // 查询所有员工并展示
    auto result = sql.queryEmployees();
    showResult(result);
}

// 槽函数：处理删除员工操作
void WagesTax::on_delete_2_clicked()
{
    // 获取当前选中的列表项
    QListWidgetItem* selectedItem = 
        ui->listWidget->currentItem();

    if (selectedItem) 
    {
        // 获取该项关联的 QWidget（包含员工信息）
        QWidget* widget = 
            ui->listWidget->itemWidget(selectedItem);

        if (widget) 
        {
            // 获取自定义属性 "itemId"，表示员工的 ID
            QVariant idVariant = widget->property("itemId");

            // 将 QVariant 转换为整数类型的 ID
            int itemId = idVariant.toInt();

            // 调用 SQL 删除该员工
            sql.deleteEmployee(itemId);

            // 刷新查询结果，更新列表
            on_query_clicked();

            // 弹出删除成功的提示框
            QMessageBox::warning(
                this, 
                QString::fromLocal8Bit("删除成功"),
                QString::fromLocal8Bit("员工已删除！"));

            // 输出日志信息，调试用
            qDebug() << "Selected Item ID:" << itemId;

            // 清除输入框的内容
            clearInput();
        }
    }
    else
    {
        // 如果未选择项，弹出警告框
        QMessageBox::warning(this,
            QString::fromLocal8Bit("删除失败"),
            QString::fromLocal8Bit("未选中！"));
    }
}

// 槽函数：处理修改员工信息操作
void WagesTax::on_modify_clicked()
{
    // 获取当前选中的列表项
    QListWidgetItem* selectedItem = 
        ui->listWidget->currentItem();

    if (selectedItem)
    {
        // 获取该项关联的 QWidget（包含员工信息）
        QWidget* widget
            =
            ui->listWidget->itemWidget(selectedItem);

        if (widget)
        {
            // 获取自定义属性 "itemId"，表示员工的 ID
            QVariant idVariant
                = 
                widget->property("itemId");

            // 将 QVariant 转换为整数类型的 ID
            int itemId = 
                idVariant.toInt();

            // 根据 ID 查询员工信息并获取结果
            auto result =
                sql.queryEmployeeByIdOrName(itemId, "").front();

            // 更新员工信息
            sql.updateEmployee(
                std::get<0>(result),
                ui->name_edit->text(),
                ui->salary_edit_2->text().toDouble());

            // 刷新查询结果，更新列表
            on_query_clicked();

            // 弹出修改成功的提示框
            QMessageBox::warning(this, 
                QString::fromLocal8Bit("修改成功"),
                QString::fromLocal8Bit("员工已修改！"));

            // 输出日志信息，调试用
            qDebug() << "Selected Item ID:" << itemId;
        }
    }
    else
    {
        // 如果未选择项，弹出警告框
        QMessageBox::warning(this, QString::fromLocal8Bit("修改失败"), QString::fromLocal8Bit("未选中！"));
    }
}

// 槽函数：处理查询员工操作
void WagesTax::on_query_clicked()
{
    // 如果查询框为空，显示所有员工
    if (ui->query_edit_6->text().isEmpty())
    {
        auto result = sql.queryEmployees();
        showResult(result);
    }
    else
    {
        // 获取输入框中的查询字符串
        QString input 
            = 
            ui->query_edit_6->text();

        // 检查输入的字符串是否为数字
        bool isNumber = false;
        int id = input.toInt(&isNumber); // 转换为整数，如果是数字，isNumber 为 true

        if (isNumber)
        {
            // 如果是数字，调用查询函数，按 ID 查询
            auto result
                =
                sql.queryEmployeeByIdOrName(id, QString());
            showResult(result);
        }
        else 
        {
            // 如果不是数字，按姓名查询
            auto result
                = 
                sql.queryEmployeeByIdOrName(-1, input);
            showResult(result);
        }
    }
}

// 显示查询结果
void WagesTax::showResult(std::vector<std::pair<int, QString>>& result)
{
    // 检查输入的结果列表是否为空
    if (result.empty())
    {
        qDebug() << "No results to display.";
        return; // 如果没有数据，直接返回
    }

    // 清空现有的列表项，为展示新的数据做准备
    ui->listWidget->clear();

    // 获取结果的总数，并通过调试输出进行记录
    int totalResults 
        =
        result.size();
    qDebug() << "Total number of results: " << totalResults;

    // 遍历结果集，每个元素包含员工的ID和姓名
    for (auto& it : result)
    {
        int employeeId 
            = 
            it.first;
        QString employeeName
            = 
            it.second;

        // 输入数据有效性检查
        if (employeeName.isEmpty())
        {
            qWarning() << "Employee name is empty for ID:" << employeeId;
            continue;  // 如果员工姓名为空，跳过该项
        }

        if (employeeId <= 0)
        {
            qWarning() << "Invalid employee ID:" << employeeId;
            continue;  // 如果员工ID无效，跳过该项
        }

        try
        {
            // 创建一个新的QWidget容器，用于显示该员工的信息
            QWidget* widget = new QWidget();
            if (!widget)
            {
                throw std::runtime_error("Failed to create widget for employee ID: " + std::to_string(employeeId));
            }

            // 创建一个水平布局管理器，将控件依次排列
            QHBoxLayout* layout = new QHBoxLayout(widget);
            if (!layout)
            {
                throw std::runtime_error("Failed to create layout for employee ID: " + std::to_string(employeeId));
            }

            // 创建标签并将员工姓名显示在该标签上
            QLabel* label = new QLabel(employeeName);
            if (!label)
            {
                throw std::runtime_error("Failed to create label for employee ID: " + std::to_string(employeeId));
            }
            layout->addWidget(label);

            // 为该员工项设置自定义的属性，用于后续的查找或操作
            widget->setProperty("itemId", employeeId);

            // 创建一个新的列表项，并将其添加到QListWidget中
            QListWidgetItem* listItem = new QListWidgetItem();
            if (!listItem)
            {
                throw std::runtime_error("Failed to create list item for employee ID: " + std::to_string(employeeId));
            }
            listItem->setSizeHint(widget->sizeHint());
            ui->listWidget->addItem(listItem);

            // 将自定义控件设置为该列表项的显示内容
            ui->listWidget->setItemWidget(listItem, widget);

            // 调试输出，查看当前员工的ID和姓名信息
            QString debugMessage = QString("Displaying employee with ID: %1, Name: %2")
                .arg(employeeId).arg(employeeName);
            qDebug() << debugMessage;

            // 假设的员工检查：例如，如果ID为偶数，则做进一步处理
            if (employeeId % 2 == 0)
            {
                qDebug() << "Employee with ID " << employeeId << " is an even-numbered employee.";
            }

            // 在输出中记录员工ID的特殊情况
            if (employeeId == 1001)
            {
                qDebug() << "Special case encountered: Employee ID " << employeeId;
            }
        }
        catch (const std::exception& ex)
        {
            // 捕获任何标准异常并输出错误信息
            qCritical() << "Error occurred: " << ex.what();
        }
        catch (...)
        {
            // 捕获未知异常
            qCritical() << "An unknown error occurred for employee ID:" << employeeId;
        }
    }
}



// 清除输入框内容和列表项选择
void WagesTax::clearInput()
{
    ui->name_edit->clear();  // 清除员工姓名输入框
    ui->salary_edit_2->clear();  // 清除薪资输入框
    ui->listWidget->clearSelection();  // 清除列表项选择
}
