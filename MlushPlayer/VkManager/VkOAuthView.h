#ifndef VKOAUTHVIEW_H
#define VKOAUTHVIEW_H

#include <QtWebKitWidgets>

#include "VkCookieJar.h"

class VkOAuthView : public QWebView
{
	Q_OBJECT
public:
	enum Permission
	{
		None         = 0,
		Notify       = 1,
		Friends      = 2,
		Photos       = 4,
		Audio        = 8,
		Video        = 16,
		Offers       = 32,
		Questions    = 64,
		Pages        = 128,
		AddToMenu    = 256,
		Status       = 1024,
		Notes        = 2048,
		Messages     = 4096,
		Wall         = 8192,
		Ads          = 32768,
		Offline      = 65536,
		Docs         = 131072,
		Groups       = 262144,
		Notification = 524288,
		Stats        = 1048576
	};
	Q_DECLARE_FLAGS(Permissions, Permission)

	explicit VkOAuthView(QWidget *parent = 0);

	int appID() const { return m_appID; }
	Permissions permissions() const {return m_permissions; }
	void SetAppID(int appID) { m_appID = appID; }
	void SetPermissions(Permissions permissions) { m_permissions = permissions; }

	QString getCookies() { return m_cookies; }
	void setCookies(const QString& cookies);

	void OpenAuthPage();

signals:
	void AuthSuccess(const QString &accessToken, int expiresInSecs, int userID);
	void AuthFail(const QString &errorCode, const QString &errorDesc);

private slots:
	void OnUrlChanged(const QUrl &newUrl);

private:
	int m_appID = -1;
	Permissions m_permissions = None;

	QString m_cookies;
	VkCookieJar* m_cookieJar;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(VkOAuthView::Permissions)

#endif // VKOAUTHVIEW_H
