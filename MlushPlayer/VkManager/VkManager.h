#ifndef VKMANAGER_H
#define VKMANAGER_H

#include <QObject>

#include <QNetworkReply>

class VkManager : public QObject
{
	Q_OBJECT
public:
	explicit VkManager(QObject *parent = 0);

public slots:
	void SetUserData(const QString &accessToken, int expiresInSecs, int userID);

	void GetPlaylist();
	void GetPlaylistFromSearch(const QString &question);

private slots:
	void onReply();

signals:
	void success(QString result);

private:
	QString m_accessToken;
	QString m_userID;
	int m_expiresInSecs;

	QNetworkReply* m_reply;

	bool m_haveUserData;
};

#endif // VKMANAGER_H
