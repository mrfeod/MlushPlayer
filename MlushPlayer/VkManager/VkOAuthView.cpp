#include "VkOAuthView.h"

#include <QUrl>

VkOAuthView::VkOAuthView(QWidget *parent)
	: QWebView(parent)
	, m_cookieJar(new VkCookieJar(this))
{
	page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

	connect(this, &VkOAuthView::urlChanged, this, &VkOAuthView::OnUrlChanged);
}

void VkOAuthView::OpenAuthPage()
{
	page()->networkAccessManager()->setCookieJar(m_cookieJar);

	QUrlQuery url("https://oauth.vk.com/authorize?");
	url.addQueryItem("client_id", QString::number(m_appID));
	url.addQueryItem("scope", QString::number(m_permissions));
	url.addQueryItem("display", "mobile");
	url.addQueryItem("v", "5.40");
	url.addQueryItem("redirect_uri", "http://api.vkontakte.ru/blank.html");
	url.addQueryItem("response_type", "token");

	load(url.toString());
}

void VkOAuthView::OnUrlChanged(const QUrl &newUrl)
{
	QUrlQuery url(newUrl.toString().replace("#","&"));

	if (url.hasQueryItem("access_token"))
	{
		hide();
		m_cookies = m_cookieJar->SaveCookies();
		emit AuthSuccess(url.queryItemValue("access_token"),
						 url.queryItemValue("expires_in").toInt(),
						 url.queryItemValue("user_id").toInt());
	}
	else
	{
		show();
		if (url.hasQueryItem("error"))
		{
			emit AuthFail(url.queryItemValue("error"), url.queryItemValue("error_description"));
		}
	}
}

void VkOAuthView::setCookies(const QString &cookies)
{
	m_cookies = cookies;
	m_cookieJar->LoadCookies(m_cookies);
}
