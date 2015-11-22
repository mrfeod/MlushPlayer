#include "VkCookieJar.h"

#include <QList>
#include <QString>
#include <QStringList>
#include <QNetworkCookie>

const QByteArray SEPARATOR = "#SPRT#";

QString VkCookieJar::SaveCookies()
{
	QByteArray strCookies;
	QList<QNetworkCookie> cookies = allCookies();

	Q_FOREACH(auto cookie, cookies)
		strCookies += cookie.toRawForm() + SEPARATOR;

	return strCookies;
}

void VkCookieJar::LoadCookies(QString &source)
{
	QStringList strCookies = source.split(SEPARATOR, QString::SkipEmptyParts);
	QList<QNetworkCookie> cookies;

	Q_FOREACH(auto cookie, strCookies)
		cookies << QNetworkCookie::parseCookies(cookie.toLatin1());

	this->setAllCookies(cookies);
}
