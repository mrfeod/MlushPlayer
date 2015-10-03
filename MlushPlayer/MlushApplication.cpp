#include "MlushApplication.h"

#include "ObjectsConnector/MlushConnectorID.h"
#include "ObjectsConnector/ObjectsConnector.h"

void MlushApplication::Initialize()
{
	m_vkManager.reset(new VkManager(this));
	m_playlistController.reset(new PlaylistController(this));

	mainWindow()->GetAuthPage()->SetAppID(CONST_APP_ID);
	mainWindow()->GetAuthPage()->SetPermissions(VkOAuthView::Audio);

	connect(mainWindow()->GetAuthPage().data(), &VkOAuthView::AuthSuccess, [this](const QString &accessToken, int expiresInSecs, int userID)
	{
		m_vkManager->SetUserData(accessToken, expiresInSecs, userID);
		m_vkManager->GetPlaylist();
	});

    //ObjectsConnector::registerEmitter(MlushConnectorID::PLAYLIST_RECIEVED(), m_vkManager.data(), SIGNAL(success(QString)));
    //ObjectsConnector::registerReceiver(MlushConnectorID::PLAYLIST_RECIEVED(), m_playlistController.data(), SLOT(SetPlaylistFromJSON(QString)));

	connect(m_vkManager.data(), &VkManager::success, [this](const QString &playlist)
	{
		mainWindow()->SetPage(MainWindow::PagePlayer);
        m_playlistController->SetPlaylistFromJSON(playlist);
        mainWindow()->GetPlayerPage()->AddToPlaylist(m_playlistController->GetMediaPlaylist());
	});

	//@todo Делать это по кнопке
	mainWindow()->GetAuthPage()->OpenAuthPage();
}
