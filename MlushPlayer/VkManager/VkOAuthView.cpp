#include "VkOAuthView.h"

#include <QUrl>
#include <QDebug>

VkOAuthView::VkOAuthView(QWidget *parent)
    : QWebView(parent),
      m_appID(1),
      m_permissions(None)
{
    connect(this, &VkOAuthView::urlChanged, this, &VkOAuthView::OnUrlChanged);
}

void VkOAuthView::OpenAuthPage()
{
    QUrlQuery url("https://oauth.vk.com/authorize?");
    url.addQueryItem("client_id", QString::number(m_appID));
    url.addQueryItem("scope", QString::number(m_permissions));
    url.addQueryItem("display", "mobile");
    url.addQueryItem("v", "5.37");
    url.addQueryItem("redirect_uri", "http://api.vkontakte.ru/blank.html");
    url.addQueryItem("response_type", "token");
    QString str = url.toString();
    qDebug() << "OLOLO  " << str;
    load(str);
}

void VkOAuthView::OnUrlChanged(const QUrl &newUrl)
{
    QUrlQuery url(newUrl.toString().replace("#","?"));
    qDebug() << "OLOLO2  " << newUrl.toString();
    if (url.hasQueryItem("error"))
    {
        emit AuthFail(url.queryItemValue("error"), url.queryItemValue("error_description"));
        return;
    }

    if (url.hasQueryItem("access_token"))
    {
        emit AuthSuccess(url.queryItemValue("access_token"), url.queryItemValue("expires_in").toInt(),
                url.queryItemValue("user_id").toInt());
        return;
    }
}
