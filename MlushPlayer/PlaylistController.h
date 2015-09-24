#ifndef PLAYLISTCONTROLLER_H
#define PLAYLISTCONTROLLER_H

#include <QObject>

#include <QVector>

struct PlaylistItemData
{
	QString artist;
	QString title;
	QString url;
	int duration;
};

class PlaylistController : public QObject
{
	Q_OBJECT
public:
	explicit PlaylistController(QObject *parent = 0);

public slots:
	void SetPlaylistFromJSON(const QString& jsonString);

private:
	QVector<PlaylistItemData> m_playlist;
};

#endif // PLAYLISTCONTROLLER_H
