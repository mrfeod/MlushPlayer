#include "VkManager.h"

#include <QNetworkAccessManager>
#include <QUrlQuery>

VkManager::VkManager(QObject *parent)
	: QObject(parent)
	, m_haveUserData(false)
{

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
	request.addQueryItem("v","5.37");

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
	QString result = m_reply->readAll();

	m_reply->close();

	emit success(result);
}
