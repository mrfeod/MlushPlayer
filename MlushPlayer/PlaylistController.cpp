#include "PlaylistController.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QDebug>

PlaylistController::PlaylistController(QObject *parent) : QObject(parent)
{

}

void PlaylistController::SetPlaylistFromJSON(const QString& jsonString)
{
    QList<PlaylistItemData> data;
	QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
	QJsonArray items = doc.object().value("response").toObject().value("items").toArray();

	Q_FOREACH(auto item, items)
	{
		QJsonObject obj = item.toObject();
		PlaylistItemData itemData;
		itemData.artist   = obj.value("artist").toString();
		itemData.title    = obj.value("title").toString();
		itemData.url      = obj.value("url").toString();
		itemData.duration = obj.value("duration").toInt();

        data.append(itemData);
	}

	m_playlist = data;

    Q_FOREACH(auto item, m_playlist)
    {
        QMediaContent playlistItem(item.url);
        m_mediaPlaylist.append(playlistItem);
    }

	Q_FOREACH(auto item, m_playlist)
	{
		qDebug() << item.artist;
	}
}
