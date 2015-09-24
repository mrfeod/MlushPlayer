#include "MlushApplication.h"

void MlushApplication::Initialize()
{
	m_vkManager.reset(new VkManager(this));
	m_playlistController.reset(new PlaylistController(this));

	mainWindow()->GetAuthPage()->SetAppID(CONST_APP_ID);
	mainWindow()->GetAuthPage()->SetPermissions(VkOAuthView::Audio);

	connect(mainWindow()->GetAuthPage(), &VkOAuthView::AuthSuccess, [this](const QString &accessToken, int expiresInSecs, int userID)
	{
		m_vkManager->SetUserData(accessToken, expiresInSecs, userID);
		m_vkManager->GetPlaylist();
	});

	connect(m_vkManager.data(), &VkManager::success, m_playlistController.data(), &PlaylistController::SetPlaylistFromJSON);

	//@todo Делать это по кнопке
	mainWindow()->GetAuthPage()->OpenAuthPage();
}
