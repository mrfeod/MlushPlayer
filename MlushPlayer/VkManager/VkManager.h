#ifndef VKMANAGER_H
#define VKMANAGER_H

#include <QObject>

#include <QStringList>
#include <QNetworkReply>

class VkManager : public QObject
{
	Q_OBJECT
public:
	explicit VkManager(QObject *parent = 0);

public slots:
	void SetUserData(const QString &accessToken, int expiresInSecs, int userID);

	QStringList GetPlaylist(const QString& query = QString());

signals:
	void success(QStringList list);

private slots:
	void slotDone(bool error);

private:
	QString m_accessToken;
	QString m_userID;
	int m_expiresInSecs;

	QNetworkReply* m_reply;

	bool m_haveUserData;
};

#endif // VKMANAGER_H
