#include "iconhelper.h"
//设置 Label、PushButton 控件图标,方便管理
IconHelper* IconHelper::_instance = 0;
IconHelper::IconHelper(QObject*):
    QObject(qApp)
{
    int fontId = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");// 添加字体文件，返回字体id
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);// 获取字体名称
    iconFont = QFont(fontName);// 根据字体名称创建字体对象
}
// 设置QLabel的图标
void IconHelper::SetIcon(QLabel* lab, QChar c, int size)
{
    iconFont.setPointSize(size);// 设置字体大小
    lab->setFont(iconFont);// 设置标签的字体
    lab->setText(c);// 设置标签的文本为指定的字符
}
// 设置QPushButton的图标
void IconHelper::SetIcon(QPushButton* btn, QChar c, int size)
{
    iconFont.setPointSize(size);
    btn->setFont(iconFont);
    btn->setText(c);
}
