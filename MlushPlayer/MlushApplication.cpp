#include "MlushApplication.h"
#include "mainwindow.h"


void MlushApplication::Initialize()
{
	m_vkManager.reset(new VkManager(this));
	m_vkAuthView.reset(new VkOAuthView());

	m_vkAuthView->SetAppID(CONST_APP_ID);
	m_vkAuthView->SetPermissions(VkOAuthView::Audio);

	connect(m_vkAuthView.data(), &VkOAuthView::AuthSuccess, m_vkManager.data(), &VkManager::SetUserData);

	mainWindow()->PlaceWidget(m_vkAuthView.data());

	m_vkAuthView->OpenAuthPage();
}
