#include "VkManager.h"

#include <QNetworkAccessManager>
#include <QUrlQuery>

#include "ObjectsConnector/MlushConnectorID.h"
#include "ObjectsConnector/ObjectsConnector.h"

VkManager::VkManager(QObject *parent)
	: QObject(parent)
	, m_haveUserData(false)
{
	ObjectsConnector::registerReceiver(MlushConnectorID::PLAYLIST_REQUEST(), this, SLOT(GetPlaylist()));
	ObjectsConnector::registerReceiver(MlushConnectorID::SEARCH_REQUEST(), this, SLOT(GetPlaylistFromSearch(QString)));
}

void VkManager::SetUserData(const QString &accessToken, int expiresInSecs, int userID)
{
	m_accessToken   = accessToken;
	m_userID        = QString::number(userID);
	m_expiresInSecs = expiresInSecs;

	m_haveUserData = true;
}

void VkManager::GetPlaylist()
{
	if(!m_haveUserData)
		return;

	QUrlQuery request("https://api.vk.com/method/audio.get?");

	request.addQueryItem("access_token",m_accessToken);
	request.addQueryItem("need_user", "0");
	request.addQueryItem("user_id", m_userID);
	request.addQueryItem("v","5.40");

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	m_reply = manager->get(QNetworkRequest(request.toString()));
	connect(m_reply, &QNetworkReply::finished ,this, &VkManager::onReply);
}

void VkManager::GetPlaylistFromSearch(const QString& question)
{
	if(!m_haveUserData)
		return;

	QUrlQuery request("https://api.vk.com/method/audio.search?");

	request.addQueryItem("access_token",m_accessToken);
	request.addQueryItem("v","5.40");
	request.addQueryItem("q",question);
	request.addQueryItem("auto_complete","1"); // исправляет опечатки, неверную раскладку и немного судьбу запроса
	//@todo реализовать динамическую подгрузку списка при смещении до 300, т.к. поиск способен выдавать 1000 результатов
	request.addQueryItem("count","300"); // 300 - это максимум

	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	m_reply = manager->get(QNetworkRequest(request.toString()));
	connect(m_reply, &QNetworkReply::finished ,this, &VkManager::onReply);
}

struct PlaylistItemData
{
	QString artist;
	QString title;
	QString url;
	int duration;
};

void VkManager::onReply()
{
	//@todo отлавливать ошибки
	QString result = m_reply->readAll();

	m_reply->close();

	emit success(result);
}
