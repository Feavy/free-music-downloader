#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include <QMainWindow>

namespace Ui {
class GuiWindow;
}

class GuiWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuiWindow(QWidget *parent = 0);
    ~GuiWindow();

private:
    Ui::GuiWindow *ui;
};

#endif // GUIWINDOW_H
