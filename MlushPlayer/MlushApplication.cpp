#include "MlushApplication.h"

#include "ObjectsConnector/MlushConnectorID.h"
#include "ObjectsConnector/ObjectsConnector.h"

#include "PlaylistController.h"

void MlushApplication::Initialize()
{
    m_vkManager = new VkManager(this);

	mainWindow()->GetAuthPage()->SetAppID(CONST_APP_ID);
	mainWindow()->GetAuthPage()->SetPermissions(VkOAuthView::Audio);

    connect(mainWindow()->GetAuthPage(), &VkOAuthView::AuthSuccess, [this](const QString &accessToken, int expiresInSecs, int userID)
	{
		m_vkManager->SetUserData(accessToken, expiresInSecs, userID);
		m_vkManager->GetPlaylist();
	});

    //ObjectsConnector::registerEmitter(MlushConnectorID::PLAYLIST_RECIEVED(), m_vkManager.data(), SIGNAL(success(QString)));
    //ObjectsConnector::registerReceiver(MlushConnectorID::PLAYLIST_RECIEVED(), m_playlistController.data(), SLOT(SetPlaylistFromJSON(QString)));

    connect(m_vkManager, &VkManager::success, [this](const QString &playlist)
	{
		mainWindow()->SetPage(MainWindow::PagePlayer);
        mainWindow()->GetPlayerPage()->AddToPlaylist(GetPlaylistFromJSON(playlist));
	});

	//@todo Делать это по кнопке
	mainWindow()->GetAuthPage()->OpenAuthPage();
}
