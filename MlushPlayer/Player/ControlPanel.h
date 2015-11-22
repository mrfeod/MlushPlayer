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

public slots:
	void SetTitle(const QString& title);
	void SetDuration(const qint64& duration);
	void SetPosition(const qint64& position);

signals:
	void play(bool toggled);
	void next();
	void prev();
	void positionChanged(const qint64& position);

private:
	Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
