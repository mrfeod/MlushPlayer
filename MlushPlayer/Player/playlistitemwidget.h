#ifndef PLAYLISTITEMWIDGET_H
#define PLAYLISTITEMWIDGET_H

#include <QWidget>

namespace Ui {
class PlaylistItemWidget;
}

class PlaylistItemWidget : public QWidget
{
	Q_OBJECT

public:
	explicit PlaylistItemWidget(QWidget *parent = 0);
	~PlaylistItemWidget();

private:
	Ui::PlaylistItemWidget *ui;
};

#endif // PLAYLISTITEMWIDGET_H
