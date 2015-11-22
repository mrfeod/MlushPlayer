#ifndef VKCOOKIEJAR_H
#define VKCOOKIEJAR_H

#include <QNetworkCookieJar>

class VkCookieJar : public QNetworkCookieJar
{
	Q_OBJECT

public:
	explicit VkCookieJar(QObject *parent) : QNetworkCookieJar(parent)
	{}

	QString SaveCookies();
	void LoadCookies(QString &source);
private:

};

#endif // VKCOOKIEJAR_H
