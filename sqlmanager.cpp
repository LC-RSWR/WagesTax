#include "sqlmanager.h"
#include <qsqldatabase.h>  // 用于与SQLite数据库交互的类
#include <QSqlQuery>        // 用于执行SQL查询的类
#include <qdebug.h>         // 用于调试输出
#include <QSqlError>        // 用于获取SQL错误信息
#include <QDebug>
#include <vector>
#include <tuple>
#include <QString>
#include <QVariant>

#include "taxcalccenter.h"  // 用于计算税费的类
#include <QMessageBox>

// SqlManager 构造函数，当前为空
SqlManager::SqlManager()
{

}

// 创建SQLite数据库及其表格
void SqlManager::createSql()
{
    // 使用SQLite数据库驱动连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // 设置数据库文件名
    db.setDatabaseName("tax_system.db");

    // 尝试打开数据库，判断是否成功
    if (!db.open())
    {
        // 如果打开失败，输出错误信息
        qDebug() << "Failed to open database!";
    }
    else 
    {
        // 如果打开成功，输出成功信息
        qDebug() << "Database opened successfully!";
    }

    // 创建员工表格（如果该表格不存在的话）
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS employees ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "  // 自增的员工ID
        "name TEXT NOT NULL, "                    // 员工姓名，不能为空
        "salary REAL NOT NULL, "                  // 员工薪水，不能为空
        "tax REAL NOT NULL);");                   // 员工税额，不能为空
}

// 添加新员工记录
void SqlManager::addEmployee(const QString& name, double salary)
{
    // 计算员工的税额
    double tax = TaxCalcCenter::calculateTax(salary);

    // 创建SQL查询对象并准备插入操作
    QSqlQuery query;
    query.prepare("INSERT INTO employees (name, salary, tax) VALUES (?, ?, ?)");

    // 绑定参数值
    query.addBindValue(name);    // 员工姓名
    query.addBindValue(salary);  // 员工薪水
    query.addBindValue(tax);     // 员工税额

    // 执行查询并检查是否成功
    if (!query.exec()) 
    {
        // 如果执行失败，输出错误信息
        qDebug() << "Error inserting employee:" << query.lastError().text();
    }
    else
    {
        // 如果成功，输出成功信息
        qDebug() << "Employee added successfully!";
        
       QMessageBox::information(nullptr, QString::fromLocal8Bit("添加成功"), QString::fromLocal8Bit("成功录入！"), QMessageBox::StandardButton::Ok);
    }
}

// 更新现有员工记录
void SqlManager::updateEmployee(int id, const QString& name, double salary) 
{
    // 计算新的税额
    double tax = TaxCalcCenter::calculateTax(salary);

    // 创建SQL查询对象并准备更新操作
    QSqlQuery query;
    query.prepare("UPDATE employees SET name = ?, salary = ?, tax = ? WHERE id = ?");

    // 绑定参数值
    query.addBindValue(name);    // 员工姓名
    query.addBindValue(salary);  // 员工薪水
    query.addBindValue(tax);     // 员工税额
    query.addBindValue(id);      // 员工ID，用于查找指定员工

    // 执行查询并检查是否成功
    if (!query.exec()) 
    {
        // 如果执行失败，输出错误信息
        qDebug() << "Error updating employee:" << query.lastError().text();
    }
    else 
    {
        // 如果成功，输出成功信息
        qDebug() << "Employee updated successfully!";
    }
}

// 删除员工记录
void SqlManager::deleteEmployee(int id) 
{
    // 创建SQL查询对象并准备删除操作
    QSqlQuery query;
    query.prepare("DELETE FROM employees WHERE id = ?");

    // 绑定员工ID作为删除条件
    query.addBindValue(id);

    // 执行查询并检查是否成功
    if (!query.exec()) 
    {
        // 如果执行失败，输出错误信息
        qDebug() << "Error deleting employee:" << query.lastError().text();
    }
    else 
    {
        // 如果成功，输出成功信息
        qDebug() << "Employee deleted successfully!";
    }
}

// 查询所有员工记录
std::vector<std::pair<int, QString>> SqlManager::queryEmployees()
{
    // 创建SQL查询对象，查询所有员工记录
    QSqlQuery query("SELECT * FROM employees");

    std::vector<std::pair<int, QString>> result;
    // 遍历查询结果
    while (query.next())
    {
        // 通过列索引获取查询结果
        int id = query.value(0).toInt();          // 获取员工ID
        QString name = query.value(1).toString(); // 获取员工姓名
        double salary = query.value(2).toDouble(); // 获取员工薪水
        double tax = query.value(3).toDouble();   // 获取员工税额


        // 将查询结果格式化为字符串
        QString employeeInfo = QString("%1    %2    %3    %4")
            .arg(id, 10)  // 设置宽度，确保对齐
            .arg(name, 15) // 设置宽度，确保对齐
            .arg(salary, 10, 'f', 2) // 设置宽度，保留2位小数
            .arg(tax, 10, 'f', 2);  // 设置宽度，保留2位小数
        // 输出员工信息
        qDebug() 
            << "ID:" 
            << id
            << "Name:" 
            << name 
            << "Salary:" 
            << salary 
            << "Tax:" 
            << tax;

        result.push_back(std::make_pair(id, employeeInfo));
    }

    return result;
}

std::vector<std::pair<int, QString>> SqlManager::queryEmployeeByIdOrName(int id, const QString& name) {
    // SQL查询字符串
    QString queryStr = "SELECT * FROM employees WHERE ";

    // 根据传入的参数决定查询条件
    bool hasCondition = false;

    if (id != -1)
    {
        queryStr += "id = :id";
        hasCondition = true;
    }

    if (!name.isEmpty())
    {
        // 如果已经有条件，用 AND 连接
        if (hasCondition) 
        {
            queryStr += " AND ";
        }
        queryStr += "name = :name";
        hasCondition = true;
    }

    // 如果没有条件，则查询全部员工
    if (!hasCondition)
    {
        queryStr = "SELECT * FROM employees";
    }

    // 创建SQL查询对象
    QSqlQuery query;
    query.prepare(queryStr);

    // 设置查询参数
    if (id != -1) 
    {
        query.bindValue(":id", id);
    }
    if (!name.isEmpty())
    {
        query.bindValue(":name", name);
    }

    // 执行查询
    if (!query.exec()) 
    {
        qDebug() << "Query failed:" << query.lastError().text();
        return {};  // 返回空结果
    }

    std::vector<std::pair<int, QString>> result;

    // 遍历查询结果
    while (query.next()) {
        int employeeId = query.value(0).toInt();          // 获取员工ID
        QString employeeName = query.value(1).toString(); // 获取员工姓名
        double salary = query.value(2).toDouble();        // 获取员工薪水
        double tax = query.value(3).toDouble();           // 获取员工税额


        // 将查询结果格式化为字符串
        QString employeeInfo = 
            QString("%1    %2    %3    %4")
            .arg(employeeId, 10)  // 设置宽度，确保对齐
            .arg(employeeName, 15) // 设置宽度，确保对齐
            .arg(salary, 10, 'f', 2) // 设置宽度，保留2位小数
            .arg(tax, 10, 'f', 2);  // 设置宽度，保留2位小数
        // 输出员工信息
        qDebug() 
            <<
            "ID:" 
            <<
            employeeId
            << 
            "Name:"
            << 
            employeeName
            << 
            "Salary:" 
            << 
            salary 
            << 
            "Tax:" 
            << 
            tax;

        result.push_back(std::make_pair(employeeId, employeeInfo));
    }

    return result;
}


std::vector<std::tuple<int, QString, double>>
SqlManager::queryEmployeeByIdOrName(int id) 
{
    // SQL查询字符串
    QString queryStr = "SELECT * FROM employees WHERE ";

    // 根据传入的参数决定查询条件
    bool hasCondition = false;

    if (id != -1)
    {
        queryStr += "id = :id";
        hasCondition = true;
    }

    QString name;
    if (!name.isEmpty()) 
    {
        // 如果已经有条件，用 AND 连接
        if (hasCondition)
        {
            queryStr += " AND ";
        }
        queryStr += "name = :name";
    }

    // 如果没有条件，则查询全部员工
    if (!hasCondition)
    {
        queryStr = "SELECT * FROM employees";
    }

    // 创建SQL查询对象
    QSqlQuery query;
    query.prepare(queryStr);

    // 设置查询参数
    if (id != -1) 
    {
        query.bindValue(":id", id);
    }
    if (!name.isEmpty()) 
    {
        query.bindValue(":name", name);
    }

    // 执行查询
    if (!query.exec())
    {
        qDebug() << "Query failed:" << query.lastError().text();
        return {};  // 返回空结果
    }

    std::vector<std::tuple<int, QString, double>> result;

    // 遍历查询结果
    while (query.next())
    {
        int employeeId = query.value(0).toInt();          // 获取员工ID
        QString employeeName = query.value(1).toString(); // 获取员工姓名
        double salary = query.value(2).toDouble();        // 获取员工薪水
        double tax = query.value(3).toDouble();           // 获取员工税额

       
        // 输出员工信息
        qDebug() << "ID:"
            <<
            employeeId
            <<
            "Name:"
            <<
            employeeName
            << 
            "Salary:" 
            << 
            salary;

        // 将查询结果作为 tuple 存储
        result.push_back(std::make_tuple(employeeId, employeeName, salary));
    }

    return result;
}


