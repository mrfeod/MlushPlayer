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

QStringList VkManager::GetPlaylist(const QString& query)
{
	if(!m_haveUserData)
		return QStringList();

	QUrlQuery request("api.vk.com/method/audio.get?");

	request.addQueryItem("access_token",m_accessToken);
	request.addQueryItem("need_user", "0");
	request.addQueryItem("user_id", m_userID);
	request.addQueryItem("v","5.37");


	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	m_reply = manager->get(QNetworkRequest(request.toString()));
	QObject::connect(m_reply,SIGNAL(finished()),this, SLOT(slotDone()));

	return QStringList();
}

void VkManager::slotDone(bool error){
	if(error)
	   return;
	else{
		QStringList list; //list with mp3

	   QString str = m_reply->readAll();
	}

	m_reply->close();
}
