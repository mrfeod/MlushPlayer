#include "PlaylistController.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QDebug>

QList<PlaylistItemData> GetPlaylistFromJSON(const QString& jsonString)
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

	Q_FOREACH(auto item, data)
	{
		qDebug() << item.artist;
	}

	return data;
}
