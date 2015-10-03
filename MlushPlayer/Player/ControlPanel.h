#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	explicit ControlPanel(QWidget *parent = 0);
	~ControlPanel();

signals:
    void play(bool toggled);
    void next();
    void prev();

private:
	Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
