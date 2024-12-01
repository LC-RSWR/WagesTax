/********************************************************************************
** Form generated from reading UI file 'wagestax.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAGESTAX_H
#define UI_WAGESTAX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WagesTax
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_2;
    QLabel *label_5;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *name_edit;
    QLineEdit *salary_edit_2;
    QPushButton *add;
    QPushButton *modify;
    QPushButton *delete_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLineEdit *query_edit_6;
    QPushButton *query;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WagesTax)
    {
        if (WagesTax->objectName().isEmpty())
            WagesTax->setObjectName(QString::fromUtf8("WagesTax"));
        WagesTax->resize(900, 800);
        WagesTax->setMinimumSize(QSize(900, 800));
        WagesTax->setMaximumSize(QSize(900, 800));
        centralwidget = new QWidget(WagesTax);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(35);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_2);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font1;
        font1.setPointSize(23);
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_6->addWidget(label_5);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_6->addWidget(listWidget);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        name_edit = new QLineEdit(centralwidget);
        name_edit->setObjectName(QString::fromUtf8("name_edit"));

        verticalLayout_2->addWidget(name_edit);

        salary_edit_2 = new QLineEdit(centralwidget);
        salary_edit_2->setObjectName(QString::fromUtf8("salary_edit_2"));

        verticalLayout_2->addWidget(salary_edit_2);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_2->addLayout(horizontalLayout);

        add = new QPushButton(centralwidget);
        add->setObjectName(QString::fromUtf8("add"));

        horizontalLayout_2->addWidget(add);

        modify = new QPushButton(centralwidget);
        modify->setObjectName(QString::fromUtf8("modify"));

        horizontalLayout_2->addWidget(modify);

        delete_2 = new QPushButton(centralwidget);
        delete_2->setObjectName(QString::fromUtf8("delete_2"));

        horizontalLayout_2->addWidget(delete_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        query_edit_6 = new QLineEdit(centralwidget);
        query_edit_6->setObjectName(QString::fromUtf8("query_edit_6"));

        horizontalLayout_6->addWidget(query_edit_6);

        query = new QPushButton(centralwidget);
        query->setObjectName(QString::fromUtf8("query"));

        horizontalLayout_6->addWidget(query);


        verticalLayout_5->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_7->addLayout(verticalLayout_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_7);

        WagesTax->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WagesTax);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 26));
        WagesTax->setMenuBar(menubar);
        statusbar = new QStatusBar(WagesTax);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WagesTax->setStatusBar(statusbar);

        retranslateUi(WagesTax);

        QMetaObject::connectSlotsByName(WagesTax);
    } // setupUi

    void retranslateUi(QMainWindow *WagesTax)
    {
        WagesTax->setWindowTitle(QCoreApplication::translate("WagesTax", "WagesTax", nullptr));
        label_2->setText(QCoreApplication::translate("WagesTax", "\344\270\252\344\272\272\346\211\200\345\276\227\347\250\216\350\256\241\347\256\227\347\263\273\347\273\237", nullptr));
        label_5->setText(QCoreApplication::translate("WagesTax", "<html><head/><body><p>ID   Name   Salary  Tax</p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("WagesTax", "\350\276\223\345\205\245\345\247\223\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("WagesTax", "\350\276\223\345\205\245\350\226\252\350\265\204", nullptr));
        add->setText(QCoreApplication::translate("WagesTax", "\346\267\273\345\212\240", nullptr));
        modify->setText(QCoreApplication::translate("WagesTax", "\344\277\256\346\224\271", nullptr));
        delete_2->setText(QCoreApplication::translate("WagesTax", "\345\210\240\351\231\244", nullptr));
        label_7->setText(QCoreApplication::translate("WagesTax", "\350\276\223\345\205\245ID\346\210\226\345\247\223\345\220\215", nullptr));
        query->setText(QCoreApplication::translate("WagesTax", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WagesTax: public Ui_WagesTax {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAGESTAX_H
